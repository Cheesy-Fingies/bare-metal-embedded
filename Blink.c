/*
DANIEL MCCORMACK
BARE-METAL STM32F103 BLINK EXAMPLE
*/

#include "STM32F103_RCC.h"  
#include "STM32F103_GPIO.h" 

uint32_t _resetField(uint32_t FIELD_LENGTH, uint32_t FIELD_START_POSITION)
{
    uint32_t mask = ((1U << FIELD_LENGTH) - 1);
    mask = mask << FIELD_START_POSITION;
    return ~mask;
}

#define HSE_SPEED 16 //16MHz

void delay(uint32_t delay_ms)
{
    for (uint32_t i = 0; i < (200 * HSE_SPEED * delay_ms); ++i) 
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
    //start Port A GPIO Clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN_ENABLE;

    /*
    GPIO CONFIGURATION
    */
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
    //Initialize device, start on-board hardware
    _bootLoader();
    //Main Program Loop
    while(1)
    {
        //Toggle pin PA9 on and off
        GPIOA->ODR ^= GPIOA_ODR(PA9);
        delay(500);
    }
    return 0;
}
