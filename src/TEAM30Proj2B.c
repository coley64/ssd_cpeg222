/****************************************************************
* TEAM 30: N. WEST and H. COLLINS
* CPEG222 Lab1_Blink, 9/10/25
* NucleoF466RE CMSIS STM32F4xx 
Project 2B SSD with Interrupts
****************************************************************/

#include "stm32f4xx.h" // Include the STM32F4xx CMSIS header file
#include <stdbool.h> // Needed to define true and false Booleans

#define SEG_AA_PA5 5 // PA5
#define SEG_AB_PA6 6 // PA6
#define SEG_AC_PA7 7 // PA7
#define SEG_AD_PB6 6 // PB6
#define SEG_AE_PC7 7 // PC7
#define SEG_AF_PA9 9 // PA9
#define SEG_AG_PA8 8 // PA8

#define BTN_PIN (13) // Assuming User Button is connected to GPIOC pin 13
#define BTN_PORT (GPIOC)
#define LED_PIN_0 0
#define LED_PIN_PORT GPIOC

#define FREQUENCY 16000000UL // 16 MHz

bool PAUSE = false; // Global variable to track pause state
int tim_count = 0;

// function headers
void SysTick_Handler();
void TIM2_IRQHandler(void);

// global
int ones = 0;
int tens = 0;
bool digitSelect = true; // true for first digit, false for second digit

void SEG_AA_on(void) {
    GPIOA->ODR |= (1 << SEG_AA_PA5);
}
void SEG_AB_on(void) {
    GPIOA->ODR |= (1 << SEG_AB_PA6);
}
void SEG_AC_on(void) {
    GPIOA->ODR |= (1 << SEG_AC_PA7);
}
void SEG_AD_on(void) {
    GPIOB->ODR |= (1 << SEG_AD_PB6);
}
void SEG_AE_on(void) {
    GPIOC->ODR |= (1 << SEG_AE_PC7);
}
void SEG_AF_on(void) {
    GPIOA->ODR |= (1 << SEG_AF_PA9);
}
void SEG_AG_on(void) {
    GPIOA->ODR |= (1 << SEG_AG_PA8);
}

void clear_all_segments(void) {
    // PA5, PA6, PA7, PA9, PA8 are on port A
    GPIOA->ODR &= ~((1<<5) | (1<<6) | (1<<7) | (1<<9) | (1<<8));
    // PB6 is on port B
    GPIOB->ODR &= ~(1<<6);
    // PC7 is on port C
    GPIOC->ODR &= ~(1<<7);
}

void SysTick_Handler(void) {
    ones += 1;
    if (ones == 10) {
        tens += 1;
        ones = 0;
        if (tens == 10) {
            tens = 0;
            ones = 0;
        }
    }
}

void displayNumber(int num){
    clear_all_segments(); // Turn off all segments first
    if (num == 0){
        SEG_AA_on(); SEG_AB_on(); SEG_AC_on(); SEG_AD_on(); SEG_AE_on(); SEG_AF_on();
    }
    if (num == 1){
        SEG_AB_on(); SEG_AC_on();
    }
    if (num == 2){
        SEG_AA_on(); SEG_AB_on(); SEG_AD_on(); SEG_AE_on(); SEG_AG_on();
    }
    if (num == 3){
        SEG_AA_on(); SEG_AB_on(); SEG_AC_on(); SEG_AD_on(); SEG_AG_on();
    }
    if (num == 4){
        SEG_AB_on(); SEG_AC_on(); SEG_AF_on(); SEG_AG_on();
    }
    if (num == 5){
        SEG_AA_on(); SEG_AC_on(); SEG_AD_on(); SEG_AF_on(); SEG_AG_on();
    }
    if (num == 6){
        SEG_AA_on(); SEG_AC_on(); SEG_AD_on(); SEG_AE_on(); SEG_AF_on(); SEG_AG_on();
    }
    if (num == 7){
        SEG_AA_on(); SEG_AB_on(); SEG_AC_on();
    }
    if (num == 8){
        SEG_AA_on(); SEG_AB_on(); SEG_AC_on(); SEG_AD_on(); SEG_AE_on(); SEG_AF_on(); SEG_AG_on();
    }
    if (num == 9){
        SEG_AA_on(); SEG_AB_on(); SEG_AC_on(); SEG_AD_on(); SEG_AF_on(); SEG_AG_on();
    }
}

void TIM2_IRQHandler(void){
    tim_count++;
    if(TIM2->SR & TIM_SR_UIF){ // Check if the update interrupt flag is set
        if (digitSelect) { // If digitSelect is true, update the first digit
            GPIOB->ODR |= (1 << 10); // set cat to high
            if (tens == 0) {
                clear_all_segments();
            } else {
            displayNumber(tens);
            }
        } else { // If digitSelect is false, update the second digit`
            GPIOB->ODR &= ~(1 << 10); // set cat to low
            displayNumber(ones);
        }
    }
    digitSelect = !digitSelect; // Toggle digitSelect for next interrupt
    TIM2->SR &= ~TIM_SR_UIF; // Clear the update interrupt flag
}

void EXTI15_10_IRQHandler(void) {
    static volatile int last_press_time = 0;       // for debounce
    static volatile int last_double_press_time = 0; // for double-press

    // Check interrupt source
    if (EXTI->PR & (1 << BTN_PIN)) {
        EXTI->PR |= (1 << BTN_PIN); // Clear pending interrupt
    }

    int current_time = tim_count;

    // --- Debounce: ignore presses within 20ms ---
    if (current_time - last_press_time < 100) return;
    last_press_time = current_time;

    // --- Double-press logic: within 500ms ---
    if (current_time - last_double_press_time <= 1000000) {
        SysTick->VAL = 0;                          // restart counter
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  // enable SysTick
    }
    last_double_press_time = current_time;

    // --- Toggle PAUSE ---
    if (PAUSE) {
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  // Enable SysTick
        PAUSE = false;
    } else {
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // Disable SysTick
        PAUSE = true;
    }
}


int main(void) {
    
    // Enable clock for GPIO ports A, B, C ✅
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // Enable SYSCFG clock for EXTI

    // Configure GPIO pins -> clear mode bits
    GPIOA->MODER &= ~(0x3 << (SEG_AA_PA5 * 2));
    GPIOA->MODER &= ~(0x3 << (SEG_AB_PA6 * 2));
    GPIOA->MODER &= ~(0x3 << (SEG_AC_PA7 * 2));
    GPIOA->MODER &= ~(0x3 << (SEG_AG_PA8 * 2));
    GPIOA->MODER &= ~(0x3 << (SEG_AF_PA9 * 2));
    GPIOB->MODER &= ~(0x3 << (SEG_AD_PB6 * 2));
    GPIOC->MODER &= ~(0x3 << (SEG_AE_PC7 * 2));
    GPIOB->MODER &= ~(0x3 << (10 * 2));
    GPIOB->MODER &= ~(0x3 << (4 * 2));


    // Configure GPIO pins -> general purpose output mode
    GPIOA->MODER |= (0x1 << (SEG_AA_PA5 * 2));
    GPIOA->MODER |= (0x1 << (SEG_AB_PA6 * 2));
    GPIOA->MODER |= (0x1 << (SEG_AC_PA7 * 2));
    GPIOA->MODER |= (0x1 << (SEG_AG_PA8 * 2));
    GPIOA->MODER |= (0x1 << (SEG_AF_PA9 * 2));
    GPIOB->MODER |= (0x1 << (SEG_AD_PB6 * 2));
    GPIOC->MODER |= (0x1 << (SEG_AE_PC7 * 2));
    GPIOB->MODER |= (0x1 << (10 * 2));
    GPIOB->MODER |= (0x1 << (4 * 2));


    // Configure TIM2 for XX microseconds interrupt (assuming 16MHz HSI clock)
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Enable TIM2 clock
    TIM2->PSC = 15; // Prescaler: (16MHz/(15+1) = 1MHz, 1usec period)
    TIM2->ARR = 10000 - 1; // Auto-reload when CNT = XX: (period = XX usec) 
    // setting timer for 10 us, if you want 60 hz then 1/60 = 0.0166667 sec = 16667 us

    TIM2->DIER |= TIM_DIER_UIE; // Enable update interrupt
    TIM2->SR &= ~TIM_SR_UIF; // Clear any pending interrupt
    NVIC_EnableIRQ(TIM2_IRQn); // Enable TIM2 interrupt in NVIC
    NVIC_SetPriority(TIM2_IRQn, 1); // Set priority for TIM2
    TIM2->CR1 = TIM_CR1_CEN; // Enable TIM

    // Set up interrupts for the button here if needed
    EXTI->IMR |= (1 << BTN_PIN); // Unmask EXTI line 13
    EXTI->FTSR |= (1 << BTN_PIN); // Trigger on falling edge
    //EXTI->RTSR |= (1 << BTN_PIN); // Trigger on rising edge
    SYSCFG->EXTICR[3] &= ~(0xF << (1 * 4)); // Clear EXTI13 bits
    SYSCFG->EXTICR[3] |= (2 << (1 * 4)); // Map EXTI13 to PC13
    NVIC_SetPriority(EXTI15_10_IRQn, 0); // Set priority
    NVIC_EnableIRQ(EXTI15_10_IRQn); // Enable EXTI line[15:10] interrupts in NVIC

    // Configure SysTick timer
    SysTick->LOAD = FREQUENCY / 4 - 1; // Load value for 250 ms at 16 MHz
    SysTick->VAL = 0; // Clear current value
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
    NVIC_SetPriority(SysTick_IRQn, 1); // Set the SysTick priority (optional)
    
    while (1) { // Main loop to toggle through LED every second
    // # No need to update LED_STATUS here, it's handled in SysTick_Handler
    }
    return(0);
} 