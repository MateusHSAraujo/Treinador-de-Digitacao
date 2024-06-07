/*!
 * @file util.h
 * @brief Prototipos, macros e tipos de dados de util.c
 * @date 22/06/2023
 * @author Mateus Henrique Silva Araujo
 */

#ifndef UTIL_H_
#define UTIL_H_

#define GPIO_PIN(x)  ((1)<<(x))


/**
 * @brief espera em multiplos de 5us
 * @param[in] multiplos de 5us
 */
void espera_5us (uint32_t multiplos);


#endif /* UTIL_H_ */
