/*
    STM32F103C8T6 BARE METAL
    DAINEL MCCORMACK Jan 2, 2025  

    -use "x << y" for writing to a register, where x is the binary or hex value
    and y is the specific bit location in the register
    -use a "mask" when wanting to read registers 
    - |= turns a bit on for a register
    - &= turns a bit off for a register
    - & 0b..111111 will read the value of the register by tracing the number
    
*/
#include <stdint.h>

//RCC Configuration 
#define RCC 0x40021000
#define RCC_CR (*(volatile uint32_t *)(RCC + 0x00))
#define RCC_CR_HSEON (1 << 16)
#define RCC_CFGR (*(volatile uint32_t *)(RCC + 0x04))
#define RCC_CFGR_SW (0b01 << 0)
#define RCC_CFGR_MCO (0b100 << 24)
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC + 0x18))
#define RCC_APB2ENR_IOPAEN (1 << 2)

//GPIO Configuration
#define GPIOA_BASE 0x40010800
#define GPIOA_CRH (*(volatile uint32_t *)(GPIOA_BASE + 0x04))
#define GPIOA_CRH_MODE(x) (0b1011 << ((x - 8) * 4))
#define GPIOA_MCO_PIN 8

void bootLoader()
{
    //Start HSE
    RCC_CR |= RCC_CR_HSEON;
    //Wait for HSE Ready flag
    while(((RCC_CR >> 17) & 1) != 1);
    //set system clock as the HSE clock
    RCC_CFGR |= RCC_CFGR_SW;
    //Wait for SysClock Ready flag
    while(((RCC_CFGR >> 2) & 0b11) != 0b01);
    //set MCO to SysClock
    RCC_CFGR |= RCC_CFGR_MCO;
    //start Port A GPIO Clock
    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;
    //Reset values for MCO/PA8 MODE and CNF
    GPIOA_CRH &= ~(0b1111 << 0);
    //Set PA8 as the MCO output with 50MHz max that is in push-pull
    GPIOA_CRH |= GPIOA_CRH_MODE(GPIOA_MCO_PIN);
}

int main()
{
    //Initialize device, set firmware codes, start on-board hardware
    bootLoader();
    //Main Program Loop
    while(1);
    return 0;
}
