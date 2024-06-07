/*!
 * @file GPIO_latch_lcd.h
 * @brief Prototipos, macros e tipos de dados de GPIO_latch_lcd
 * @author Wu Shin Ting
 * @author Matues Henrique Silva Araujo
 * @date 22/05/2023
 */

#ifndef GPIO_LATCH_LCD_H_
#define GPIO_LATCH_LCD_H_
//Inclusao dos tipos de dados padronizados pelo ISO C99
#include "stdint.h"

/**
 * @brief Funcao do byte enviado para LCD
 */
typedef enum lcd_RS_tag {
	COMANDO,  //!< Comando (0) 
	DADO	  //!< Dado (1) 
} tipo_lcd_RS;

/*!
 * @brief Habilita conexao entre mcu e LCD/Latch.
 */
void GPIO_ativaConLatchLCD ();

/*!
 * @brief Seta o tipo de informacao enviada para LCD.
 * @param[in] i (COMANDO = 0; DADO = 1)
 */
void GPIO_setRS (tipo_lcd_RS i);

/*!
 * @brief Transfere um byte para LCD.
 * @param[in] c byte
 * @param[in] t tempo de processamento em us
 */
void GPIO_escreveByteLCD(uint8_t c, uint16_t t);

/*!
 * @brief Inicializa LCD
 */
void GPIO_initLCD ();

/*!
 * @brief Escreve uma string de caracteres a partir de um endereco 
 * @param[in] end endereco DDRAM
 * @param[in] str endereco inicial da string
 */
void GPIO_escreveStringLCD (uint8_t end, uint8_t *str);

/*!
 * @brief Escreve um unico caracter em um endereco especifico
 * @param[in] end endereco DDRAM
 * @param[in] chr caracter a ser escrito 
 */
void GPIO_escreveCharLCD (uint8_t end, uint8_t chr);

/*!
 * @brief Transfere o endereco DDRAM
 * @param[in] end endereco da memoria DDRAM
 * 
 * @note Consulta os enderecos de cada celula das duas linhas na 
 * @note secao 11 em ftp://ftp.dca.fee.unicamp.br/pub/docs/ea079/datasheet/AC162A.pdf
 */
void GPIO_setEndDDRAMLCD (uint8_t end);

/*!
 * @brief Constroi um bitmap em CGRAM a partir do endereco end*8 mapeado em end de CGROM
 * @param[in] end CGROM
 * @param[in] bitmap endereco de 8 bytes que definem o bitmap
 */
void GPIO_escreveBitmapLCD (uint8_t end, uint8_t *bitmap);

/*!
 * @brief escreve um byte nos LEDs vermelhos do Latch
 * @param[in] c byte a ser escrito
 */
void GPIO_escreveByteLatch(uint8_t c);
void GPIO_initSwitches(uint8_t NMI_IRQC, uint8_t IRQA5_IRQC, uint8_t IRQA12_IRQC, uint8_t prioridade);
#endif /* GPIO_LATCH_LCD_H_ */
