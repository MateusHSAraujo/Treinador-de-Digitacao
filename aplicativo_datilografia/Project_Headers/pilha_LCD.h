/*!
 *@file pilha_LCD.h
 *@brief Header para rotinas associadas ao buffer pilha do LCD
 *@author Mateus Henrique Silva Araujo
 *@date 22/06/2023
 */

#ifndef PILHA_LCD_H_
#define PILHA_LCD_H_
#include "stdint.h"

/**
 * @brief Struct que implementa um buffer em forma de pilha para a facilitar a comunicacao do aplicativo com o LCD
 */
typedef struct BufferPilha_tag
{
	char dados[32];  	 //<! buffer de dados
	int8_t tail;       //<! indice de leitura (head)
} BufferPilha_type;


/**
 * @brief Calcula o endereco de impressao no LCD correspondente a um determinado indice da pilha (considerando que a pilha cresce do canto inferior esquerdo do LCD ate o canto superior direito)
 * @param[in] idx indice da pilha desejado
 * @return endereco do LCD correspondente ao buffer
 */
uint8_t LCD_printOffset(uint8_t idx);

/**
 * @brief Calcula o modulo de contagem de TPM1 corrrespondente a nota musical do indice da pilha
 * @param[in] idx indice da pilha desejado
 * @return moulo correspondente a nota do indice
 */
uint16_t calcMod(uint8_t idx);

/**
 * @brief Inicializa um buffer em forma de pilha
 * @param[in] buffer apontador para o buffer a ser inicializado
 */
void BP_init(BufferPilha_type *buffer);

/**
 * @brief Adiciona um elemento na pillha
 * @param[in] buffer apontador para a pilha na qual deseja-se inseri o elemento
 * @param[in] item elemento a ser inserido
 * @param[in] print Se igual a 1, a insercao gera uma impressao no LCD. Se igual a 0, a insercao e feita sem impressao no LCD
 * @param[in] buzzerUp Se igual a 1, a insercao gera alteracao no buzzzer. Se igual a 0, a insercao e feita sem alteracao no buzzer
 * @return 0 se a insercao for bem-sucedida, -1 caso contrario
 */
uint8_t BP_add (BufferPilha_type *buffer, char item, uint8_t print, uint8_t buzzerUp);

/**
 * @brief Apaga um elemento na pillha
 * @param[in] buffer apontador para a pilha na qual deseja-se inseri o elemento
 * @param[in] print Se igual a 1, o apagamento gera uma impressao no LCD. Se igual a 0, o apagamento e feita sem impressao no LCD
 * @param[in] buzzerDown Se igual a 1, o apagamento gera alteracao no buzzzer. Se igual a 0, o apagamento e feita sem alteracao no buzzer
 * @return 0 se o o apagamento for bem-sucedida, -1 caso contrario
 */
uint8_t BP_del (BufferPilha_type *buffer, uint8_t print, uint8_t buzzerDown);

/**
 * @brief Imprime a pilha gerada no inicio do nivel no LCD
 * @param[in] buffer apontador para a pilha a ser impressa
 */
void BP_printaPilhaInicial(BufferPilha_type *buffer);

/**
 * @brief Gera os primeiros 16 elementos de uma pilha
 * @param[in] buffer apontador para a pilha a ser gerada
 */
void BP_geraPilhaInicial(BufferPilha_type *buffer);

/**
 * @brief Gera uma letra aleatoria no intervalo A-Z ou a-z
 * @returns letra aleatoria
 */
char BP_geraLetra();

/**
 * @brief Le o ultimo caractere da pilha passada como parametro
 * @param[in] buffer apontador para a pilha
 * @param[out] item apontador para ser inserido o ultimo caracter da pilha
 * @returns 0 se a leitura foi bem sucedida, -1 caso contrario
 */
uint8_t BP_get (BufferPilha_type *buffer, char* item);

/**
 * @brief Verifica se a pilha esta cheia
 * @param[in] buffer pilha para se verificar a condicao
 * @returns 1 se sim, 0 caso contrario
 */
uint8_t BP_isFull (BufferPilha_type *buffer);

/**
 * @brief Verifica se a pilha esta vazia
 * @param[in] buffer pilha para se verificar a condicao
 * @returns 1 se sim, 0 caso contrario
 */
uint8_t BP_isEmpty (BufferPilha_type *buffer);

/**
 * @brief Reinicia a pilha
 * @param[in] buffer pilha para ser reiniciada
 */
void BP_reset(BufferPilha_type *buffer);
uint8_t BP_trocaCaracteres();
void BP_resetConfig();
#endif /* PILHA_LCD_H_ */
