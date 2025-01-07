#ifndef STM32F103_GPIO_H
#define STM32F103_GPIO_H

#ifndef __IO  
#define __IO volatile

#endif

//GPIO CONTROL REGISTERS
typedef struct
{
    __IO uint32_t CRL;
    __IO uint32_t CRH;
    __IO uint32_t IDR;
    __IO uint32_t ODR;
    __IO uint32_t BSRR;
    __IO uint32_t BRR;
    __IO uint32_t LCKR;
} GPIO_TypeDef;

//PORT A BASE ADDRESS 
#define GPIOA ((GPIO_TypeDef *) 0x40010800)

//PORT A PINS
#define PA8 8
#define PA9 9 

//PORT A CRH CONFIGURATION 
#define GPIOA_CRH_MODE(x) ((x - 8) * 4)
#define GPIOA_CRH_MODE_INPUT(x) (0b00 << ((x - 8) * 4))
#define GPIOA_CRH_MODE_OUTPUT_10MHz(x) (0b01 << ((x - 8) * 4))
#define GPIOA_CRH_MODE_OUTPUT_2MHz(x) (0b10 << ((x - 8) * 4))
#define GPIOA_CRH_MODE_OUTPUT_50MHz(x) (0b11 << ((x - 8) * 4))
#define GPIOA_CRH_CNF(x) ((((x - 8) * 4) + 2))
#define GPIOA_CRH_CNF_INPUT_ANALOG(x) (0b00 << ((((x - 8) * 4) + 2)))
#define GPIOA_CRH_CNF_INPUT_FLOATING(x) (0b01 << ((((x - 8) * 4) + 2)))
#define GPIOA_CRH_CNF_INPUT_PUPD(x) (0b10 << ((((x - 8) * 4) + 2)))
#define GPIOA_CRH_CNF_OUTPUT_GENERAL_PUSHPULL(x) (0b00 << (((x - 8) * 4) + 2))
#define GPIOA_CRH_CNF_OUTPUT_GENERAL_OPENDRAIN(x) (0b01 << (((x - 8) * 4) + 2))
#define GPIOA_CRH_CNF_OUTPUT_ALTERNATIVE_PUSHPULL(x) (0b10 << (((x - 8) * 4) + 2))
#define GPIOA_CRH_CNF_OUTPUT_ALTERNATIVE_OPENDRAIN(x) (0b11 << (((x - 8) * 4) + 2))

//PORT A ODR CONFIGURATIONS
#define GPIOA_ODR(x) (1U << x)

#endif