    /*
     * main.c
     *
     * Created: 9/17/2024
     * Author : Owen Hancock
     */ 

    /******************************************************************************
    *   This file invokes all the functions defined in the different source and header files
    *   It is used to show outputs flashed to the atmega324PB for each problem
    *******************************************************************************/

    #include "peripherals.h" // needed for gpio and pin definitions
    #include "board.h" // needed for port, ddr, and pin definitions
    #include <util/delay.h> // needed to implement default delay functions
    #include "led_1.h" // For CMSIS-based struct overlay (LED1)
    #include "led_2.h" // For inline functions (LED2)
    #include "led_3.h" // For OOP-based control (LED3)
    #include "gpio_3.h" // For OOP-based control (LED3)

    int main(void)
    {
    /******************************************************************************
    *   Method 1 initialization using direct addressing
    *
    * 
    *******************************************************************************/
        
        // Works
        
        // initialize PC7 as an output set to '1' (LED0) (off)
        PORTC|=LED0_PIN;
        DDRC|=LED0_PIN;

    /******************************************************************************
    *   Method 2 initialization using Device Driver layer (GPIO)
    *   & Hardware Abstraction Layer (LED)
    * 
    *******************************************************************************/
        
        // Works
        
        // Initialize LED1 on Port B, Pin 3
        LED_init(LED1_PORT, LED1_PIN); // Call LED initialization
        
    /******************************************************************************
    *   Method 3 initialization using static inline functions
    *   
    * 
    *******************************************************************************/
        
        // Works
        
        // Initialize LED2 (connected to Port E, Pin 4)
        LED_init_2(LED2_PORT, LED2_PIN);  // Call LED2 initialization
        
    /******************************************************************************
    *   Method 4 initialization using object oriented programming
    *   
    * 
    *******************************************************************************/
        
        // Works
        
        LED_t LED3; // Declare an instance for LED3
        
        // Initialize LED3 (connected to Port A, Pin 7, active low)
        LED_init_3(&LED3, LED3_PORT, LED3_PIN, 1, 0);  // 1 for Active low
        
        while (1) 
        {
            
            /******************************************************************************
            *   Method 1 LED on/off using direct addressing 
            *   
            *   Execution time for problem 7:
            *******************************************************************************/
            
            // Works
            
            // Blink LED0
            PORTC&=(~LED0_PIN);
            // _delay_ms(1000); // remove for problem 7
            PORTC|=LED0_PIN;
            // _delay_ms(1000); // remove for problem 7
            
            /******************************************************************************
            *   Method 2 LED on/off using Device Driver Layer (GPIO)
            *   & Hardware Abstraction Layer (LED)
            *   Execution time for problem 7:
            *******************************************************************************/
            
            // Works
            
            // Turn LED1 on
            LED_set_value(LED1_PORT, LED1_PIN, 0); // Turn on LED1
            // _delay_ms(1000); // remove for problem 7

            // Turn LED1 off
            LED_set_value(LED1_PORT, LED1_PIN, 1); // Turn off LED1
            // _delay_ms(1000); // remove for problem 7
            
            /******************************************************************************
            *   Method 3 LED using static inline functions
            *   
            *   Execution time for problem 7:
            *******************************************************************************/
            
            // Works
            
            // Turn LED2 on
            LED_set_value_2(LED2_PORT, LED2_PIN, 0); // Turn on LED2
            // _delay_ms(1000); // remove for problem 7

            // Turn LED2 off
            LED_set_value_2(LED2_PORT, LED2_PIN, 1); // Turn off LED2
            // _delay_ms(1000); // remove for problem 7
            
            /******************************************************************************
            *   Method 4 LED using object oriented programming
            *   
            *   Execution time for problem 7:
            *******************************************************************************/
            
            // Works
            
            // Turn LED3 on
            LED_set_value_3(&LED3, 0); // 0 for off (active low)
            // _delay_ms(1000); // remove for problem 7

            // Turn LED3 off
            LED_set_value_3(&LED3, 1); // 1 for on (active low)
            // _delay_ms(1000); // remove for problem 7
            
        }
    }






