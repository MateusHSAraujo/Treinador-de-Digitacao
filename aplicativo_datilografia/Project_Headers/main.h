/*!
 *@file main.h
 *@brief Fluxo de controle principal do aplicativo
 *@author Mateus Henrique Silva Araujo
 *@date 22/06/2023
 */

#ifndef MAIN_H_
#define MAIN_H_

/**
 * @brief Fluxo de controle principal do programa. Nessa funcao, sao tratados os seguintes estados:
 * 	- ESPERA_INICIO: Neste estado, e renderizado a mensagem de entrada para o usuario. O sistema se mantem nesse estagio ateo usuario enviar o
 * 	caractere '\r'. Quando isto acontece, o sistema chaveia para o estado PREPARA_LCD;
 * 	- PREPARA_LCD: Neste estado, o nivel de jogo atual e mostrado no latch, a pilha aleatoria e produzida e uma contagem regressiva e configurada. 
 * 	Apos a configuracao da contagem regressiva, o sistema chaveia para o estado CONTAGEM_REGRESSIVA;
 * 	- CONTAGEM_REGRESSIVA:  Neste estado, o sistema executa uma contagem regressiva, imprimindo a passagem do tempo de forma decrescente no LCD.
 * 	Ao fim da contagem, a pilha inicial do nivel e impressa, o temporarizador correspondente ao nivel atual e configurado e iniciado. Por fim,
 * 	o sistema chaveia para o estado EXECUTA_LVL;
 *	- APAGA_LETRA: Neste estado, o sistema apaga uma letra da pilha associada ao LCD caso ela nao esteja vazia, chaveando de volta para o estado EXECUTA_LVL,
 *	apos isso. Se a pilha esta vazia, o sistema chaveia para o estado LVL_FINALIZADO;
 *	- ADICIONA_LETRA: Neste estado, o sistema adiciona uma letra a pilha associada ao LCD caso ela nao esteja cheia, chaveando de volta para o estado EXECUTA_LVL,
 *	apos isso. Se a pilha esta cheia, o sistema chaveia para o estado LVL_FINALIZADO;
 *	- LVL_FINALIZADO: Neste estado, o sistema realiza a impressao das mensagens de fim de nivel para o usuario. Apos a impressao da mensagem, o sistema configura o tempo no
 *	qual esta mensagem deve permanecer impressa e chaveia para o estado LEITURA;
 */
int main(void);

#endif /* MAIN_H_ */
