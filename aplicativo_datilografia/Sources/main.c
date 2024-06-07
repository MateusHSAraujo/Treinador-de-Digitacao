/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "stdint.h"
#include "GPIO_latch_lcd.h"
#include "ISR.h"
#include "SIM.h"
#include "UART.h"
#include "TPM.h"
#include "derivative.h" /* include peripheral declarations */
#include "song.h"


int main(void){
	
	//Inicializa conexao com LCD e roda as rotinas de inicializacao recomendadas
	GPIO_ativaConLatchLCD ();
	GPIO_initLCD ();
	
	//Habilitar MCGFLLCLK 20971520 Hz
	SIM_setaOUTDIV4 (0b000);
	SIM_setaFLLPLL (0);              //seta FLL
		
	 //Configurar sinais de relogio e pinos
	UART2_config_basica();
			
	//Configura o modulo UART2 
	//MCGFLLCLK em 20971520 Hz
	UART2_config_especifica (20971520, 38400); // baud_rate = 38400 ;
	
	
	//Configura sinais de relogio para contadores TPM
	SIM_setaTPMSRC(1); //Fornece MCGFLLCLK aos modulos TPM
		
	//Habilita e aloca pinos para TPM0 e TPM1
	TPM0TPM1TPM2_PTE21_config_basica ();
		
	//Inicializa modulos TPM0 e TPM1
	TPM_config_especifica (0, 40960, 0b1111, 0, 0, 0, 0, 0, 0b111); // TPM0 com preescaler de 128 (2**7) e periodo 128*40960/20971520 = 0.25
	TPM_config_especifica (1, 1489, 0b1111, 0, 0, 0, 0, 0, 0b101); // TPM1 com preescaler de 32 (2**5) e frequencia 20971520/1489*32 = 440
	TPM_config_especifica (2, 77, 0b1111, 0, 0, 0, 0, 0, 0b0);
		
	//Inicializa canais usados (desabilitados):
	TPM_CH_config_especifica (0, 0, 0b0000, 0); // TPM0_CH0 -> Realizar temporarizacoes necessarias
	TPM_CH_config_especifica (1, 1, 0b0000, 0); // TPM1_CH1 -> EPWM para o buzzer

	//Habilita as interrupcoes relevantes
	TPM_habilitaNVICIRQ(17,1); //Habilita interrupcoes de TPM0
	TPM_habilitaNVICIRQ(18,1); //Habilita interrupcoes de TPM1
	TPM_habilitaInterrupCH(0,0); //Habilita interrupcoes de TPM0_CH0  (OC para contagem)
	
	UART2_habilitaNVICIRQ14(0b0);//Habilita tratamento de interrupcoes de UART2
	UART2_habilitaInterruptRxTerminal();//Habilita interrupcoes de recebimento
	
	
	//Inicializa botoeiras NMI, IRQA5 e IRQA12 com borda de descida como evento de interrupcao (0b1010)
	//e prioridade=3
	GPIO_initSwitches(0b1010,0b1010,0b1010, 2);
	
	
	//Incializa pilha do LCD
	ISR_inicializaBP();
	ISR_inicializaMusicas();
	
	//Cria bitmap e configura bitmap para ser usado no fim do jogo
	char eComAcento[8]={0b00010,0b00100,0b00000,0b01110,0b10001,0b11111,0b10000,0b01110};
	char pontaSeta[8] ={0b01000,0b01100,0b01110,0b11111,0b11111,0b01110,0b01100,0b01000};
	char corpoSeta[8]={0b0,0b0,0b0,0b11111,0b11111,0b00000,0b00000,0b00000};
	GPIO_escreveBitmapLCD (0x00, (uint8_t *)corpoSeta);
	GPIO_escreveBitmapLCD (0x01, (uint8_t *)pontaSeta);
	GPIO_escreveBitmapLCD (0x02, (uint8_t *)eComAcento);
	char parabens[] = {'P','A','R','A','B',0x2,'N','S','\0'};
	
	uint8_t segundos_atual, segundos_anterior, ledsLVL;
	ISR_escreveEstado(ESPERA_INICIO);
	
	for(;;){
		switch(ISR_LeEstado()){
					case ESPERA_INICIO:
						if(ISR_getLVL()==0){
							//Renderiza mensagem de boas vindas
							GPIO_escreveStringLCD(0x00,(uint8_t *)"  Digitando!!!  ");
							GPIO_escreveStringLCD(0x41,(uint8_t *)"->Tecle ENTER<-");
							
							//Produz o valor a ser inserido no latch
							ledsLVL = 1<<7;
							
							//Aumenta para o nivel 1
							ISR_aumentaLVL();
						}
						
						//Aguarda ate que ENTER seja pressionado 
						
						break;
						
					case PREPARA_LCD:
						//Indica LVL nos LEDs vermelhos
						ledsLVL |= 1<<(8-ISR_getLVL());
						GPIO_escreveByteLatch(ledsLVL);
						
						//Gera as letras aleatorias da pilha
						ISR_geraPilhaInicial();
						
						//Renderiza mensagem para indicar inicio do LVL
						GPIO_escreveStringLCD(0x00,(uint8_t *)"Iniciando LVL ");
						GPIO_escreveCharLCD(0x0E, ISR_getLVL()+'0');
						GPIO_escreveCharLCD(0x0F, ' ');
						GPIO_escreveStringLCD(0x40,(uint8_t *) "     em 5 s     ");
						
						//Configura o canal TPM0_CH0 para gerar um intervalo de 5 segundos
						TPM_CH_config_especifica (0, 0, 0b0111, TPM0_CNT); //MS_ELS = 0111 -> OC set output on match
						segundos_atual = 5;
						segundos_anterior = 5;
						ISR_setSegundosLeitura(5); // Configura 5 segundos para a contagem regressiva
						
						//Chaveia para o estado de contagem regressiva
						ISR_escreveEstado(CONTAGEM_REGRESSIVA);
						break;
							
					case CONTAGEM_REGRESSIVA:
						segundos_atual = ISR_getSegundosLeitura(); // Coleta o tempo em segundos atual
						if (segundos_atual != segundos_anterior){ // Verifica se o tempo coletado e novo
							if (segundos_atual != 0){
								// Aletra o valor da contagem regressiva
								GPIO_escreveCharLCD(0x48, segundos_atual+'0');
								
								// Atualiza o valor de tempo registrado
								segundos_anterior = segundos_atual;						
							}
							else { // Quando o tempo da contagem atingir 0
								// Apaga a primeira linha toda
								GPIO_escreveStringLCD(0x0,(uint8_t *)"               ");
								
								//Imprime a pilha inicial
								ISR_printaPilhaInicial();
								
								//Ajusta o tempo de adicicao de letras para corresponder ao nivel
								ISR_ajustaContadorParaLVL();
								
								//Liga o temporarizador e chaveia para o estado de execucao do nivel
								TPM_CH_config_especifica (0, 0, 0b0111, TPM0_CNT); //MS_ELS = 0111 -> OC set output on match
								ISR_escreveEstado(EXECUTA_LVL);
							}
						}
						
						break;
						
					case APAGA_LETRA:
						//Apaga a letra
						ISR_apagaLetra();
						
						//Checa se a pilha esta vazia
						if(ISR_pilhaVazia()){
							// Se a pilha esta vazia, progride para o proximo nivel
							TPM_CH_config_especifica (1, 1, 0b0000, 0);; //MS_ELS = 0000 -> EPWM desativado
							TPM_CH_config_especifica (0, 0, 0b0000, TPM0_CNT); //MS_ELS = 0000 -> Temporarizador dessligado
							ISR_escreveEstado(LVL_FINALIZADO);
						} else {
							//Se nao, continua em execucao
							ISR_escreveEstado(EXECUTA_LVL);
						}
						
						break;
						
					case ADICIONA_LETRA:
						//Checa se a pilha está cheia
						if(ISR_pilhaCheia()){
							//Se a ppilha estiver cheia, finaliza o jogo
							TPM_CH_config_especifica (1, 1, 0b0000, 0); //MS_ELS = 0000 -> EPWM desativado
							TPM_CH_config_especifica (0, 0, 0b0000, TPM0_CNT); //MS_ELS = 0000 -> Temporarizador dessligado
							ISR_escreveEstado(LVL_FINALIZADO);
						} else{
							// Se a pilha não está cheia, adiciona uma letra	
							ISR_adicionaLetra();
							ISR_escreveEstado(EXECUTA_LVL);
						}
						
						break;
					
					case LVL_FINALIZADO:
						if(ISR_pilhaVazia() && ISR_getLVL()!= 8){ //Jogador finalizou um nivel normal
							//Renderiza mensagem de parabenizacao
							GPIO_escreveStringLCD(0x1,(uint8_t *)"LVL ");
							GPIO_escreveCharLCD(0x05, ISR_getLVL()+'0');
							GPIO_escreveStringLCD(0x06,(uint8_t *)" completo");
							GPIO_escreveStringLCD(0x43,(uint8_t *)"Muito bem!");
							
							//Aumenta a dificuldade
							ISR_aumentaLVL();
							
							//Configura um tempo de leitura de 3 segundos e chaveia para o estado de leitura
							//ISR_setSegundosLeitura(3); // Configura 3 segundos para a contagem regressiva
							TPM_CH_config_especifica (0, 0, 0b0111, TPM0_CNT); //MS_ELS = 0111 -> OC set output on match
							ISR_setSongToPlay(VICTORY_FANFARE);
							ISR_escreveEstado(LEITURA);
						} 
						else{
							if (ISR_pilhaVazia() && ISR_getLVL()==8){ //Jogador finalizou o ultimo nivel
								//Renderiza mensagem de parabenizacao
								GPIO_escreveStringLCD(0x0,(uint8_t *)"Jogo finalizado!");
								GPIO_escreveStringLCD(0x40, "    ");
								GPIO_escreveStringLCD(0x44,(uint8_t *) parabens);
								GPIO_escreveStringLCD(0x4C, "    ");
								ISR_setSongToPlay(WINNER_SONG);
							} else{
								//Renderiza mensagem de GAME OVER
								GPIO_escreveStringLCD(0x0,(uint8_t *)"Tela preenchida!");
								GPIO_escreveStringLCD(0x40,(uint8_t *) "  GAME OVER :(  ");
								ISR_resetaPilha(); //Reseta a pilha pois ela se encontra cheia
								ISR_setSongToPlay(LOOSER_SONG);
							}
							//Zera o nível de dificuldade
							ISR_resetLVL();
							//Configura um tempo de leitura de 4 segundos e chaveia para o estado de leitura
							//ISR_setSegundosLeitura(4); // Configura 4 segundos para a contagem regressiva
							TPM_CH_config_especifica (0, 0, 0b0111, TPM0_CNT); //MS_ELS = 0111 -> OC set output on match
							ISR_resetConfigs();
							ISR_escreveEstado(LEITURA);
														
						}
						
						
					default:
						//Estados EXECUTA_LVL e LEITURA
						break;
				}
		
		
		
	}	
	
	return 0;
}
