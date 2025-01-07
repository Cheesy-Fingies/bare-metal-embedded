#ifndef STM32F103_RCC_H
#define STM32F103_RCC_H

#include <stdint.h>

#ifndef __IO  
#define __IO volatile

#endif

//RCC CONTROL REGISTERS 
typedef struct 
{
    __IO uint32_t CR;
    __IO uint32_t CFGR;
    __IO uint32_t CIR;
    __IO uint32_t APB2RSTR;
    __IO uint32_t APB1RSTR;
    __IO uint32_t AHBENR;
    __IO uint32_t APB2ENR;
    __IO uint32_t APB1ENR;
    __IO uint32_t BDCR;
    __IO uint32_t CSR;
} RCC_TypeDef; 

//BASE ADDRESS
#define RCC ((RCC_TypeDef *) 0x40021000)

//CR CONFIGURATIONS
#define RCC_CR_HSEON 16
#define RCC_CR_HSEON_OFF (0 << RCC_CR_HSEON)
#define RCC_CR_HSEON_ON (1 << RCC_CR_HSEON)
#define RCC_CR_HSERDY 17
#define RCC_CR_HSERDY_NORDY 0
#define RCC_CR_HSERDY_RDY 1

//CFGR CONFIGURATIONS
#define RCC_CFGR_SW 0
#define RCC_CFGR_SW_HSI (0b00 << RCC_CFGR_SW)
#define RCC_CFGR_SW_HSE (0b01 << RCC_CFGR_SW)
#define RCC_CFGR_SW_PLL (0b10 << RCC_CFGR_SW)
#define RCC_CFGR_SWS 2
#define RCC_CFGR_SWS_HSI 0b00 
#define RCC_CFGR_SWS_HSE 0b01 
#define RCC_CFGR_SWS_PLL 0b10
#define RCC_CFGR_MCO_NOCLK (0b000 << 24)
#define RCC_CFGR_MCO_SYSCLK (0b100 << 24)
#define RCC_CFGR_MCO_HSI (0b101 << 24)
#define RCC_CFGR_MCO_HSE (0b110 << 24)
#define RCC_CFGR_MCO_PLL (0b111 << 24)

//APB2ENR CONFIGURATIONS 
#define RCC_APB2ENR_IOPAEN_ENABLE (1 << 2)

#endif