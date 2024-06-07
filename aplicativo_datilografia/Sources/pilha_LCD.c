/*
 * pilha_LCD.c
 *
 *  Created on: Jun 16, 2023
 *      Author: ea871
 */

#include "stdint.h"
#include "pilha_LCD.h"
#include "GPIO_latch_lcd.h"
#include "TPM.h"
#include "derivative.h"
#include "util.h"

static char vct0[]={'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m','Q','W','E','R','T','Y','U','I','O','P','A','S','D','F','G','H','J','K','L','Z','X','C','V','B','N','M','q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m'};
static char vct1[]={'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m'};
static char* vct;
static uint8_t vctAtual=0;

void BP_init(BufferPilha_type *buffer) {
	vct = vct0;
	buffer->tail = -1;
	return;
}

void BP_resetConfig(){
	vct=vct0;
	vctAtual=0;
	TPM_config_especifica (2,77, 0b1111, 0, 0, 0, 0, 0, 0b0);
}

uint8_t BP_trocaCaracteres(){
	if (vctAtual){
		vct = vct0;
		vctAtual = 0;
		TPM_config_especifica (2,77, 0b1111, 0, 0, 0, 0, 0, 0b0);
		return 0;
	} else {
		vct = vct1;
		vctAtual = 1;
		TPM_config_especifica (2, 25, 0b1111, 0, 0, 0, 0, 0, 0b0);
		return 1;
	}
}

uint8_t LCD_printOffset(uint8_t idx){
	// O inicio da pilha e mapeado no ultimo endereco do LCD 
	// O topo da pilha e mapeado em direcao ao primeiro endereco do LCD 
	return (idx<16)? 0x4f-idx : 31-idx;
}

uint16_t calcMod(uint8_t idx){
	return 2505-((1253*idx)/31);
}

char BP_geraLetra(){
	return vct[TPM2_CNT & 0xFF];
}

void BP_geraPilhaInicial(BufferPilha_type *buffer){
	uint8_t i=1;
	while (i<=16){
		espera_5us((TPM0_CNT & 0b1111)+1);
		BP_add (buffer, BP_geraLetra(),0,0);
		i++;
	}
	
	return;
}

void BP_printaPilhaInicial(BufferPilha_type *buffer){
	uint8_t i =0;
	while (i <= buffer->tail){
		GPIO_escreveCharLCD(LCD_printOffset(i),buffer->dados[i]);
		i++;
	}
	GPIO_escreveCharLCD(LCD_printOffset(i++),0x1);
	while (i <= 31){
			GPIO_escreveCharLCD(LCD_printOffset(i),0x0);
			i++;
		}
	
	uint16_t mod = calcMod(15);
	TPM_config_especifica (1, mod, 0b1111, 0, 0, 0, 0, 0, 0b101);
	TPM_CH_config_especifica (1, 1, 0b1010, mod/2); //MS_ELS = 1010 -> EPWM high true
}

uint8_t BP_add (BufferPilha_type *buffer, char item, uint8_t print, uint8_t buzzerUp){
	uint8_t next = buffer->tail+1;
	
	if (next>=32) return -1; //Sem espaco no buffer
	
	if(print){
		GPIO_escreveCharLCD(LCD_printOffset(next),item);
		if (next<31) GPIO_escreveCharLCD(LCD_printOffset(next+1),0x1); // Printa a ponta da seta no próximo elemento
	}
	if(buzzerUp){
		uint16_t mod = calcMod(next);
		TPM_config_especifica (1, mod, 0b1111, 0, 0, 0, 0, 0, 0b101);
		TPM_CH_config_especifica (1, 1, 0b1010, mod/2); //MS_ELS = 1010 -> EPWM high true
	}
	
	(buffer->dados)[next] = item;
	buffer->tail=next;
	
	return 0;
}

uint8_t BP_del (BufferPilha_type *buffer, uint8_t print, uint8_t buzzerDown){
	int8_t prev = buffer->tail-1;
	
	if (prev<-1) return -1; //Sem item no buffer
	
	if (print){
		GPIO_escreveCharLCD(LCD_printOffset(buffer->tail),0x1); // Printa a ponta da seta no próximo elemento
		if (buffer->tail+1<31) GPIO_escreveCharLCD(LCD_printOffset(buffer->tail+1),0x0); // Printa o corpo da seta no próximo elemento
	}
	if(buzzerDown){
		uint16_t mod = calcMod(buffer->tail);
		TPM_config_especifica (1, mod, 0b1111, 0, 0, 0, 0, 0, 0b101);
		TPM_CH_config_especifica (1, 1, 0b1010, mod/2); //MS_ELS = 1010 -> EPWM high true
	}
	
	buffer->tail=prev;
	
	return 0;
}

uint8_t BP_get (BufferPilha_type *buffer, char* item){
	if (buffer->tail > -1){
		*item = buffer->dados[buffer->tail];
		return 0;
	}
	return -1;
}

uint8_t BP_isFull (BufferPilha_type *buffer){
	return ( buffer->tail == 31 )?  1:0;
}

uint8_t BP_isEmpty (BufferPilha_type *buffer){
	return ( buffer->tail == -1 )?  1:0;
}


void BP_reset(BufferPilha_type *buffer){
	buffer->tail=-1;
}

