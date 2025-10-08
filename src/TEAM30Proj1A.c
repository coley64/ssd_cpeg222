// /****************************************************************
// * TEAM 30: N. WEST and H. COLLINS
// * CPEG222 Lab1_Blink, 9/10/25
// * NucleoF466RE CMSIS STM32F4xx example Demo1 Blink PA5
// ****************************************************************/

// #include "stm32f4xx.h" // Include the STM32F4xx CMSIS header file
// #define LED_PIN_0 0
// #define LED_PIN_1 1
// #define LED_PIN_6 6
// #define LED_PIN_7 7
// #define LED_PORT GPIOA



// void delay(volatile uint32_t count) { // Simple delay function
// while (count--) {// This function will block for a while, creating a delay
// }
// }

// int main(void) {

// // 1. Enable clock for GPIO port A
// RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

// // 2. Configure GPIO pin 2 (LED LD2 on Nucleo-F446RE) as output
// LED_PORT->MODER &= ~(0x3 << (LED_PIN_0 * 2)); // Clear mode bits
// LED_PORT->MODER &= ~(0x3 << (LED_PIN_1 * 2)); // Clear mode bits
// LED_PORT->MODER &= ~(0x3 << (LED_PIN_6 * 2)); // Clear mode bits
// LED_PORT->MODER &= ~(0x3 << (LED_PIN_7 * 2)); // Clear mode bits

// LED_PORT->MODER |= (0x1 << (LED_PIN_0 * 2)); // Set as General purpose output mode
// LED_PORT->MODER |= (0x1 << (LED_PIN_1 * 2)); // Set as General purpose output mode
// LED_PORT->MODER |= (0x1 << (LED_PIN_6 * 2)); // Set as General purpose output mode
// LED_PORT->MODER |= (0x1 << (LED_PIN_7 * 2)); // Set as General purpose output mode



// while (1) { // Main loop to toggle the LED continuously
// // LED_PORT->ODR ^= (1 << LED_PIN_2); // Toggle the LED 
// LED_PORT->ODR |= (1 << LED_PIN_0); // Turn on the LED
// delay(500000); // Simple delay
// LED_PORT->ODR &= ~(1 << LED_PIN_0); // Turn off the LED
// delay(500000); // Simple delay
// LED_PORT->ODR |= (1 << LED_PIN_1); // Turn on the LED
// delay(500000); // Simple delay
// LED_PORT->ODR &= ~(1 << LED_PIN_1); // Turn off the LED
// delay(500000); // Simple delay
// LED_PORT->ODR |= (1 << LED_PIN_6); // Turn on the LED
// delay(500000); // Simple delay
// LED_PORT->ODR &= ~(1 << LED_PIN_6); // Turn off the LED
// delay(500000); // Simple delay
// LED_PORT->ODR |= (1 << LED_PIN_7); // Turn on the LED
// delay(500000); // Simple delay
// LED_PORT->ODR &= ~(1 << LED_PIN_7); // Turn off the LED
// delay(500000); // Simple delay
// }
// return(0);
// } 