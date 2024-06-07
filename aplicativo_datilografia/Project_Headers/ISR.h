/*!
 *@file ISR.h
 *@brief Header para rotinas e variaveis associadas a ISR
 *@author Mateus Henrique Silva Araujo
 *@date 22/06/2023
 */

#ifndef ISR_H_
#define ISR_H_
#include "stdint.h"
#include "song.h"
#endif /* ISR_H_ */

/** 
 * @brief Enumeracao para os estados do sistema
 */
typedef enum estado_tag{
	ESPERA_INICIO, //!< Estado para preaparacao do inicio do jogo e espera pela comunicacao do usuario
	PREPARA_LCD, //!< Estado de geracao da pilha aleatoria
	CONTAGEM_REGRESSIVA, //<! Estado para realizacao da contagem regressiva
	EXECUTA_LVL, //!< Estado de execucao do jogo 
	APAGA_LETRA, //!< Estado de apagamento de uma letra
	ADICIONA_LETRA, //!< Estado de adicao de uma letra
	LVL_FINALIZADO, //!< Estado de transicao para o proximo LVL ou fim de jogo
	LEITURA, //!< Estado para leitura da mensagem de transicao
} tipo_estado;

/**
 * @brief Inicializa o buffer em forma de pilha associado ao LCD
 */
void ISR_inicializaBP();

/**
 * @brief Preenche a pilha inicial com 16 letras aleatorias
 */
void ISR_geraPilhaInicial();

/**
 * @brief Imprime as letras aleatorias geradas no inicio do nivel. Alem disso, tambem ativa o buzzer
 */
void ISR_printaPilhaInicial();

/**
 * @brief Verifica se a pilha esta cheia
 * @return 1 se a pilha estiver cheia e 0, caso contrario
 */
uint8_t ISR_pilhaCheia();

/**
 * @brief Verifica se a pilha esta vaiza
 * @return 1 se a pilha estiver vazia e 0, caso contrario
 */
uint8_t ISR_pilhaVazia();

/**
 * @brief Reinicia a pilha, apagando todos os seus elementos
 */
void ISR_resetaPilha();

/**
 * @brief Apaga uma letra da pilha
 * @return 0 se o apagamento foi bem sucedido, -1 caso contrario
 */
uint8_t ISR_apagaLetra();

/**
 * @brief Adiciona uma letra da pilha
 * @return 0 se o apagamento foi bem sucedido, -1 caso contrario
 */
uint8_t ISR_adicionaLetra();

/**
 * @brief Le o estado do sistema
 * @return estado atual
 */
tipo_estado ISR_LeEstado ();

/**
 * @brief Altera o estado do sistema
 * @param[in] novo estado para o qual o sistema deve ir
 */
void ISR_escreveEstado (tipo_estado novo);

/**
 * @brief Le os segundos que faltam serem transcorreridos em uma temporarizacao
 * @return segundos restantes
 */
uint8_t ISR_getSegundosLeitura();

/**
 * @brief Define a quntidade de segundos que uma temporarizacao deve durar
 */
void ISR_setSegundosLeitura(uint8_t seg);

/**
 * @brief Le o nivel atual do jogo
 * @return nivel atual do jogo
 */
uint8_t ISR_getLVL();

/**
 * @brief Reinicia o nivel do jogo
 */
void ISR_resetLVL();

/**
 * @brief Aumenta o nivel do jogo
 */
void ISR_aumentaLVL();

/**
 * @brief Ajusta o contador utilizado para gerar o intervalo de tempo para a adiciao de uma nova letra, de modo com que ele corresponda ao nivel de jogo atual
 */
void ISR_ajustaContadorParaLVL();

/**
 * @brief Rotina de interrucao responsavel pelo tratamento das interrupcoes de TPM0. Nela, o seguinte comportamento e implementado:
 * 	- Durante o estado CONTAGEM_REGRESSIVA, a rotina implementa a passagem de um periodo de tempo definido pela variavel segundosLeitura
 * 	- Durante o estado LEITURA, a rotina implementa a passagem de um periodo de tempo definido pela variavel segundosLeitura. Quando esse periodo se esgotar, o sistema pode 
 * 	ser chaveado para os estados PREPARA_LCD (no caso de haver um proximo nivel) ou ESPERA_INICIO (no caso de fim de jogo)
 * 	- Durante o estado EXECUTA_LVL, a rotina implementa a passagem de um periodo de tempo definido pela variavel contador. Quando esse periodo se esgotar, o sistema chaveia para 
 * 	o estado ADICIONA_LETRA
 */
void FTM0_IRQHandler ();

/**
 * @brief Rotina de interrucao responsavel pelo tratamento das interrupcoes de UART0. Nela, o seguinte comportamento e implementado:
 * 	- Durante os estados ESPERA_INICIO e EXECUTA_LVL, os caracteres digitados pelo usuario sao ecoados no terminal
 * 	- Durante o estado ESPERA_INICIO, caso o usuario envie o caractere '\r', o sistema chaveia para o estado PREPARA_LCD
 * 	- Durante o estado EXECUTA_LVL, se o usuario digitar o caractere que corresponde ao ultimo elemento da pilha, o sistema chaveia para o estado APAGA_LETRA
 */
void UART0_IRQHandler();
void UART2_IRQHandler();
void ISR_inicializaMusicas();
void ISR_setSongToPlay(musicas_disponiveis song);
void ISR_resetConfigs();
// void ISR_setLVL(uint8_t nvLvl); //DEBBUG
