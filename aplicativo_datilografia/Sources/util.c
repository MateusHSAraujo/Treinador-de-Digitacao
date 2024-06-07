/**
 * @file util.c
 * @brief Definicao das funcoes uteis do projeto
 * @date 19/05/2023
 * @author Mateus Henrique Silva Araujo   
 */
//Inclusao dos tipos de dados padronizados pelo ISO C99
#include "stdint.h"


void espera_5us (uint32_t multiplos)
{

		__asm__ (
				"iteracao: \n\t"
					"mov r2, #4 \n\t"
				"laco: \n\t" 
					"mov r3, #5 \n\t"
					"orr r3, r0 \n\t"
					"and r3, r0 \n\t"     
					"lsr r3, #1 \n\t"
					"asr r3, #1 \n\t"
					"and r3, r0 \n\t"
					"lsr r3, #1 \n\t"
					"asr r3, #1 \n\t"
					"asr r3, #1 \n\t"   
					"and r3, r0 \n\t"     
					"lsr r3, #1 \n\t"     
					"asr r3, #1 \n\t" 
					"asr r3, #1 \n\t"    
					"and r3, r0 \n\t"     
					"lsr r3, #1 \n\t"     
					"asr r3, #1 \n\t" 
					"asr r3, #1 \n\t"    
					"and r3, r0 \n\t"     
					"lsr r3, #1 \n\t"     
					"asr r3, #1 \n\t" 
					"asr r3, #1 \n\t"
					"sub r2, #1 \n\t"					 
					"cmp r2, #0 \n\t"
					"bne laco \n\t"
					"rev r3,r3 \n\t"
					"lsl r3,#0 \n\t"
					"sub %0,#1 \n\t"
					"cmp %0, #0 \n\t"
					"bne iteracao \n\t"
				 :
				 : "r" (multiplos)
				 : "r2","r3","cc"
		);
}


