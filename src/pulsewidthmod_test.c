/****************************************************************
* TEAM 30: N. WEST and H. COLLINS
* CPEG222 Lab1_Blink, 9/10/25
* NucleoF466RE CMSIS STM32F4xx example Demo2 SSD
****************************************************************/

#include "stm32f4xx.h" // Include the STM32F4xx CMSIS header file
#include <stdbool.h> // Needed to define true and false Booleans

#define SEG_AA_PA5 5 // PA5

void SysTick_Handler();

// global
// turned_on = false;

// void SysTick_Handler(void) {
//     if (turned_on) {
//         turned_on = false;
//         GPIOA->ODR &= ~(1 << SEG_AA_PA5);
//     } else {
//         turned_on = true;
//         GPIOA->ODR |= (1 << SEG_AA_PA5);
//     }
// }


int main(void) {
    // 1. Enable clocks
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;   // GPIOA
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;    // TIM2

    // 2. Set PA5 to Alternate Function (AF1 = TIM2_CH1)
    GPIOA->MODER &= ~(0x3 << (5 * 2));
    GPIOA->MODER |=  (0x2 << (5 * 2));     // AF mode
    GPIOA->AFR[0] |= (0x1 << (5 * 4));     // AF1 for PA5

    // 3. Configure TIM2
    TIM2->PSC = 16 - 1;     // Prescaler: 16 MHz /16 = 1 MHz
    TIM2->ARR = 10000 - 1;   // Auto-reload: 1000 counts → 1 kHz PWM
    TIM2->CCR1 = 100;       // Compare: 500/1000 = 50% duty

    // 4. PWM mode on CH1
    TIM2->CCMR1 &= ~TIM_CCMR1_OC1M;
    TIM2->CCMR1 |= (6 << TIM_CCMR1_OC1M_Pos); // PWM mode 1
    TIM2->CCMR1 |= TIM_CCMR1_OC1PE;           // Preload enable
    TIM2->CCER  |= TIM_CCER_CC1E;             // Enable output

    // 5. Enable counter
    TIM2->CR1 |= TIM_CR1_CEN;
    
    while (1) { // Main loop to toggle through LED every second
    // # No need to update LED_STATUS here, it's handled in SysTick_Handler
    }
    return(0);
} 