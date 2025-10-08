// /****************************************************************
// * TEAM 30: N. WEST and H. COLLINS
// * CPEG222 Lab1_Blink, 9/10/25
// * NucleoF466RE CMSIS STM32F4xx example Demo1 Blink PA5
// ****************************************************************/

// #include "stm32f4xx.h" // Include the STM32F4xx CMSIS header file
// #include <stdbool.h> // Needed to define true and false Booleans
// #define BTN_PIN (13) // Assuming User Button is connected to GPIOC pin 13
// #define BTN_PORT (GPIOC)
// #define LED_PIN_0 0
// #define LED_PIN_1 1
// #define LED_PIN_6 6
// #define LED_PIN_7 7
// #define LED_PORT GPIOA
// #define FREQUENCY 16000000UL // 16 MHz

// // function headers
// void SysTick_Handler();
// void EXTI15_10_IRQHandler(void);

// // define global variables (im sorry)
// bool PAUSE = false; // Global variable to track pause state
// bool SHIFT_LEFT = true; // Global variable to track shift direction
// volatile uint8_t led_state = 0;


// void EXTI15_10_IRQHandler(void) {
//     if (EXTI->PR & (1 << BTN_PIN)) { // Check if the interrupt is from BTN_PIN
//         EXTI->PR |= (1 << BTN_PIN); // Clear the pending interrupt
//     }
//     if (!PAUSE) { // Toggle PAUSE and SHIFT_LEFT states
//         PAUSE = true; // Pause the sequence
//     } else {
//         PAUSE = false; // Resume the sequence
//         SHIFT_LEFT = !SHIFT_LEFT; // Toggle direction
//     }
// }

// void SysTick_Handler(void) {
//     if (PAUSE == true) {
//         // Advance state only when running
//         if (SHIFT_LEFT) {
//             led_state = (led_state + 1) % 4;
//         } else {
//             led_state = (led_state - 1 + 4) % 4;
//         }

//         // Clear all LEDs
//         LED_PORT->ODR &= ~((1 << LED_PIN_0) | 
//                            (1 << LED_PIN_1) | 
//                            (1 << LED_PIN_6) | 
//                            (1 << LED_PIN_7));

//         // Light only the current LED
//         switch (led_state) {
//             case 0: LED_PORT->ODR |= (1 << LED_PIN_0); break;
//             case 1: LED_PORT->ODR |= (1 << LED_PIN_1); break;
//             case 2: LED_PORT->ODR |= (1 << LED_PIN_6); break;
//             case 3: LED_PORT->ODR |= (1 << LED_PIN_7); break;
//         }
//     }
// }

// int main(void) {

// // 1. Enable clock for GPIO ports C and SysTick external interrupt clock
// RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
// RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // Enable SYSCFG clock for EXTI

// // Enable clock for GPIO port A
// RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

// // Configure GPIO pins -> clear mode bits
// LED_PORT->MODER &= ~(0x3 << (LED_PIN_0 * 2)); // Clear mode bits
// LED_PORT->MODER &= ~(0x3 << (LED_PIN_1 * 2)); // Clear mode bits
// LED_PORT->MODER &= ~(0x3 << (LED_PIN_6 * 2)); // Clear mode bits
// LED_PORT->MODER &= ~(0x3 << (LED_PIN_7 * 2)); // Clear mode bits

// // Configure GPIO pins -> Output
// LED_PORT->MODER |= (0x1 << (LED_PIN_0 * 2)); // Set as General purpose output mode
// LED_PORT->MODER |= (0x1 << (LED_PIN_1 * 2)); // Set as General purpose output mode
// LED_PORT->MODER |= (0x1 << (LED_PIN_6 * 2)); // Set as General purpose output mode
// LED_PORT->MODER |= (0x1 << (LED_PIN_7 * 2)); // Set as General purpose output mode

// // Configure SysTick timer
// SysTick->LOAD = FREQUENCY / 4 - 1; // Load value for 250 ms at 16 MHz
// SysTick->VAL = 0; // Clear current value
// SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
// NVIC_SetPriority(SysTick_IRQn, 1); // Set the SysTick priority (optional)

// // Set up interrupts for the button here if needed
// EXTI->IMR |= (1 << BTN_PIN); // Unmask EXTI line 13
// EXTI->FTSR |= (1 << BTN_PIN); // Trigger on falling edge
// //EXTI->RTSR |= (1 << BTN_PIN); // Trigger on rising edge
// SYSCFG->EXTICR[3] &= ~(0xF << (1 * 4)); // Clear EXTI13 bits
// SYSCFG->EXTICR[3] |= (2 << (1 * 4)); // Map EXTI13 to PC13
// NVIC_SetPriority(EXTI15_10_IRQn, 0); // Set priority
// NVIC_EnableIRQ(EXTI15_10_IRQn); // Enable EXTI line[15:10] interrupts in NVIC


// while (1) { // Main loop to toggle through LED every 250 ms/ .25 second
//     // # No need to update LED_STATUS here, it's handled in SysTick_Handler
//     // # No need to check button state here, it's handled in EXTI handler
// }  
// return(0);
// } 