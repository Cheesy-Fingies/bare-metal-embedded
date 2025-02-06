/*
    STM32F103C8T6 BARE METAL
    DAINEL MCCORMACK Jan 2, 2025  

    -use "x << y" for writing to a register, where x is the binary or hex value
    and y is the specific bit location in the register
    -use a "mask" when wanting to read registers 
    - |= 1 turns a bit on for a register
    - &= 0 turns a bit off for a register
    - &= ~(0b1..11) resets all bits for a multi bit control section
    - ^= toggles a bit on and off every loop cycle for a register
    - & 0b11..111111 will read the value of the register by tracing the number
*/

#include "STM32F103_RCC.h"  
#include "STM32F103_GPIO.h"  

/* RULES FOR WRITING REGISTERS AND THE BOOTLOADER
-adresses are to be written in hex
-a single control bit is written as 0 or 1
-a set of control bits is written in binary
-Write the base address and then all the associated registers in an ordered typedef structure
-write all changes to a register in a configuration section in bit order
*/

uint32_t _resetField(uint32_t FIELD_LENGTH, uint32_t FIELD_START_POSITION)
{
    uint32_t mask = ((1U << FIELD_LENGTH) - 1);
    mask = mask << FIELD_START_POSITION;
    return ~mask;
}

void delay(uint32_t delay_ms)
{
    for (uint32_t i = 0; i < (3200 * delay_ms); ++i) 
    {
        __asm__ volatile("nop");
    }
}

void _bootLoader()
{
    /*
    CLOCK CONFIGURATION
    */
    //Start HSE
    RCC->CR |= RCC_CR_HSEON_ON;
    //Wait for HSE Ready flag
    while(((RCC->CR >> RCC_CR_HSERDY) & 1) != RCC_CR_HSERDY_RDY);
    //set system clock as the HSE clock
    RCC->CFGR |= RCC_CFGR_SW_HSE;
    //Wait for SysClock Ready flag
    while(((RCC->CFGR >> RCC_CFGR_SWS) & 0b11) != RCC_CFGR_SWS_HSE);
    //set MCO to SysClock
    RCC->CFGR |= RCC_CFGR_MCO_SYSCLK;
    //start Port A GPIO Clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN_ENABLE;

    /*
    GPIO CONFIGURATION
    */
    //Reset values for PA8 MODE
    GPIOA->CRH &= _resetField(2, GPIOA_CRH_MODE(PA8));
    //Set PA8 as the output with 50MHz max 
    GPIOA->CRH |= GPIOA_CRH_MODE_OUTPUT_50MHz(PA8);
    //Reset values for PA8 CNF
    GPIOA->CRH &= _resetField(2, GPIOA_CRH_CNF(PA8));
    //Set as alternative function in push-pull
    GPIOA->CRH |= GPIOA_CRH_CNF_OUTPUT_ALTERNATIVE_PUSHPULL(PA8);
    //Reset values for PA9 MODE
    GPIOA->CRH &= _resetField(2, GPIOA_CRH_MODE(PA9));
    //Set PA9 as basic output 
    GPIOA->CRH |= GPIOA_CRH_MODE_OUTPUT_2MHz(PA9);
    //Reset values for PA9 CNF
    GPIOA->CRH &= _resetField(2, GPIOA_CRH_CNF(PA9));
    //Set as alternative function in push-pull
    GPIOA->CRH |= GPIOA_CRH_CNF_OUTPUT_GENERAL_PUSHPULL(PA9);
}

int main()
{
    //Initialize device, set firmware codes, start on-board hardware
    _bootLoader();
    //Main Program Loop
    while(1)
    {
        GPIOA->ODR ^= GPIOA_ODR(PA9);
        delay(500);
    }
    return 0;
}

//make it so you can send commands through serial to pick functions from a switch case
//make a delay function
//make a bit reset function
//learn cmake/make
//learn from book how to organize project into folders