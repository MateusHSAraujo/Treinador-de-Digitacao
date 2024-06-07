#include "ISR.h"
#include "stdint.h"
#include "TPM.h"
#include "pilha_LCD.h"
#include "derivative.h"
#include "song.h"
#include "GPIO_latch_lcd.h"

static tipo_estado estado;
static uint8_t dificuldadeAtual=0;
static uint8_t tempoDificil[] = {20,16,12,8,6,5,4,3};
static uint8_t tempoMedio[] = {20,18,16,14,12,10,8,6};
static uint8_t* tempoLvls=tempoDificil; 
//static uint8_t tempoLvls[] = {140,140,140,140,140,140,140,140}; //DEBBUG
static uint8_t  lvl=0,contador,segundosLeitura;
static BufferPilha_type pilha;
static Song_type* songToPlay;
static Song_type victoryFanfare;
static Song_type winnerSong;
static Song_type looserSong;
static uint8_t counterResetAtual = 0;

void ISR_resetConfigs(){
	counterResetAtual=0;
	tempoLvls=tempoDificil;
	dificuldadeAtual=0;
	BP_resetConfig();
}

void ISR_trocaCounterReset(){
	if (counterResetAtual){
		counterResetAtual = 0;
		GPIO_escreveCharLCD(0x0D, '!');
	}
	else{
		counterResetAtual = 1;
		GPIO_escreveCharLCD(0x0D, '*');
	}
}

void ISR_inicializaBP(){ //Incializa pilha do LCD
	BP_init(&pilha);
}

void ISR_geraPilhaInicial(){ // Gera a pilha com letras aleatorias do inicio do jogo
	BP_geraPilhaInicial(&pilha);
}

void ISR_printaPilhaInicial(){ // Printa a pilha do inicio do level e ativa o buzzer
	BP_printaPilhaInicial(&pilha);
}

uint8_t ISR_pilhaCheia(){
	return BP_isFull (&pilha);
}

uint8_t ISR_pilhaVazia(){
	return BP_isEmpty (&pilha);
}

void ISR_resetaPilha(){
	BP_reset(&pilha);
}

uint8_t ISR_apagaLetra(){
	return BP_del (&pilha, 1, 1);
}

uint8_t ISR_adicionaLetra(){
	char nv_letra = BP_geraLetra();
	return BP_add(&pilha,nv_letra,1,1);
}

void ISR_trocaCaracteres(){
	if (BP_trocaCaracteres()){	
		GPIO_escreveCharLCD(0x0C, '*');
	}
	else{
		GPIO_escreveCharLCD(0x0C, '!');
	}
}

tipo_estado ISR_LeEstado () {
	return estado;
}

void ISR_escreveEstado (tipo_estado novo) {
	estado = novo;
	return;
}

uint8_t ISR_getSegundosLeitura(){
	return segundosLeitura;
}

void ISR_setSegundosLeitura(uint8_t seg){
	segundosLeitura = seg;
	contador = 0;
}

uint8_t ISR_getLVL(){
	return lvl;
}
void ISR_resetLVL(){
	lvl = 0;
}

void ISR_aumentaLVL(){
	lvl++;
}

void ISR_iniciaDificuldade(){
	tempoLvls = tempoDificil;
}

void ISR_trocaDificuldade(){
	if (dificuldadeAtual){
		tempoLvls=tempoDificil;
		GPIO_escreveCharLCD(0x0B, '!');
		dificuldadeAtual=0;
	}
	else{
		tempoLvls=tempoMedio;
		GPIO_escreveCharLCD(0x0B, '*');
		dificuldadeAtual=1;
	}
}

void ISR_ajustaContadorParaLVL(){
	contador = tempoLvls[lvl-1];
}

void ISR_inicializaMusicas(){
	initSong(&victoryFanfare, VICTORY_FANFARE);
	initSong(&winnerSong, WINNER_SONG);
	initSong(&looserSong, LOOSER_SONG);
}

void ISR_setSongToPlay(musicas_disponiveis song){
	switch (song){
			case VICTORY_FANFARE:
				songToPlay = &victoryFanfare;
				break;
			
			case WINNER_SONG:
				songToPlay = &winnerSong;
				break;
			
			case LOOSER_SONG:
				songToPlay = &looserSong;
				break;	
			
			default:
				break;
		}
	
		songToPlay->noteToPlay=0;
}

void FTM0_IRQHandler () {
	
		if (TPM0_STATUS & TPM_STATUS_CH0F_MASK){ // Canal de temporarizacao 
				TPM0_C0SC |= TPM_CnSC_CHF_MASK; //Limpa flag
				
				if (estado==CONTAGEM_REGRESSIVA){
					contador++;
					if (contador%4==0) segundosLeitura--; //Se o contador formultiplo de 4, passaram-se 1 segundo
					if (segundosLeitura==0){//Se o tempo setado em segundos para contagem zerar, desabilita o canal de temporarizacao
						TPM_CH_config_especifica (0, 0, 0b0000, 0);
					}
				}
				else if(estado == LEITURA){
					if (songToPlay->noteToPlay==0){
						TPM_config_especifica (0, (songToPlay->mod) * (songToPlay->fstTick) , 0b1111, 0, 0, 0, 0, 0, 0b111);
						TPM_CH_config_especifica (0, 0, 0b0111, TPM0_CNT); //MS_ELS = 0111 -> OC set output on match
					}
					if (nextNote(songToPlay)==-1){
							if (lvl == 0) estado = ESPERA_INICIO;
							else estado = PREPARA_LCD;
					}
				}
				else if( estado==EXECUTA_LVL){
					contador--;
					if (contador == 0){
						ISR_ajustaContadorParaLVL();
						estado = ADICIONA_LETRA;
					}
				}
				
		}
		
	return;
}

void UART2_IRQHandler(){
	char item;
	if (UART2_S1 & UART_S1_RDRF_MASK) {
		
		item = UART2_D;
		
		if (estado != ESPERA_INICIO && estado != EXECUTA_LVL) return;
		
		UART2_D = item;
		
		if (item == '\r' && estado==ESPERA_INICIO) {
			while (!(UART2_S1 & UART_S1_TDRE_MASK));
			UART2_D = '\n';
			estado = PREPARA_LCD;
		}
		
		if (estado == EXECUTA_LVL){
			char letra_atual;
			if (BP_get(&pilha,&letra_atual)==0 && letra_atual == item){
				estado = APAGA_LETRA;
				if(counterResetAtual) ISR_ajustaContadorParaLVL();
			}
		}
	}
}

void PORTA_IRQHandler () {
	
	if(PORTA_PCR4 & PORT_PCR_ISF_MASK){
		PORTA_PCR4 |= PORT_PCR_ISF_MASK; //limpa flag
		if (estado != ESPERA_INICIO) return;
		ISR_trocaDificuldade();
		
	}
	else if (PORTA_PCR5 & PORT_PCR_ISF_MASK){
		PORTA_PCR5 |= PORT_PCR_ISF_MASK;
		if (estado != ESPERA_INICIO) return;
		ISR_trocaCaracteres();
	}
	else if(PORTA_PCR12 & PORT_PCR_ISF_MASK){
		PORTA_PCR12 |= PORT_PCR_ISF_MASK;
		if (estado != ESPERA_INICIO) return;
		ISR_trocaCounterReset();
	}
	
	
}

