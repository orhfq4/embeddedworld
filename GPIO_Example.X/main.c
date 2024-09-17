    /*
     * main.c
     *
     * Created: 9/17/2024
     * Author : Owen Hancock
     */ 

    /******************************************************************************
    *   This application blinks the LEDs (LED0, LED1, LED2, and LED3) on and then
    *   off to demonstrate the execution time of various methods of GPIO control.
    *
    *******************************************************************************/

    #include "peripherals.h" // needed for gpio and pin definitions
    #include "board.h" // needed for port, ddr, and pin definitions
    #include <util/delay.h> // needed to implement default delay functions


    int main(void)
    {
    /******************************************************************************
    *   Method 1 initialization using direct addressing
    *
    * 
    *******************************************************************************/
        
        // initialize PC7 as an output set to '1' (LED0) (off)
        PORTC|=LED0_PIN;
        DDRC|=LED0_PIN;
        // initialize PB3 as an output set to '1' (LED1) (off)
        PORTB|=LED1_PIN;
        DDRB|=LED1_PIN;
        // initialize PE4 as an output set to '1' (LED2) (off)
        PORTE|=LED2_PIN;
        DDRE|=LED2_PIN;
        // initialize PA7 as an output set to '1' (LED3) (off)
        PORTA|=LED3_PIN;
        DDRA|=LED3_PIN;

    /******************************************************************************
    *   Method 2 initialization using Device Driver layer (GPIO)
    *   & Hardware Abstraction Layer (LED)
    * 
    *******************************************************************************/
        
        // Initialize LED0 on Port C, Pin 7
        LED_init(LED0_PORT, LED0_PIN); // Call LED initialization
        // Initialize LED1 on Port B, Pin 3
        LED_init(LED1_PORT, LED1_PIN); // Call LED initialization
        // Initialize LED2 on Port E, Pin 4
        LED_init(LED2_PORT, LED2_PIN); // Call LED initialization
        // Initialize LED3 on Port A, Pin 7
        LED_init(LED3_PORT, LED3_PIN); // Call LED initialization
        
    /******************************************************************************
    *   Method 3 initialization using 
    *   
    * 
    *******************************************************************************/
        
    /******************************************************************************
    *   Method 4 initialization using 
    *   
    * 
    *******************************************************************************/
        
    /******************************************************************************
    *   Method 5 initialization using 
    *   
    * 
    *******************************************************************************/
        
        while (1) 
        {
            
            /******************************************************************************
            *   Method 1 LED on/off using direct addressing 
            *   
            * 
            *******************************************************************************/
            
            // Blink LED0
            PORTC&=(~LED0_PIN);
            _delay_ms(1000);
            PORTC|=LED0_PIN;
            _delay_ms(1000);


            // Blink LED1
            PORTB&=(~LED1_PIN);
            _delay_ms(1000);
            PORTB|=LED1_PIN;
            _delay_ms(1000);

            // Blink LED2
            PORTE&=(~LED2_PIN);
            _delay_ms(1000);
            PORTE|=LED2_PIN;
            _delay_ms(1000);

            // Blink LED3
            PORTA&=(~LED3_PIN);
            _delay_ms(1000);
            PORTA|=LED3_PIN;
            _delay_ms(1000);
            
            /******************************************************************************
            *   Method 2 LED on/off using Device Driver Layer (GPIO)
            *   & Hardware Abstraction Layer (LED)
            * 
            *******************************************************************************/
            
            // Turn LED0 on
            LED_set_value(LED0_PORT, LED0_PIN, 0); // Turn on LED0
            _delay_ms(1000);

            // Turn LED0 off
            LED_set_value(LED0_PORT, LED0_PIN, 1); // Turn off LED0
            _delay_ms(1000);
            
            // Turn LED1 on
            LED_set_value(LED1_PORT, LED1_PIN, 0); // Turn on LED1
            _delay_ms(1000);

            // Turn LED1 off
            LED_set_value(LED1_PORT, LED1_PIN, 1); // Turn off LED1
            _delay_ms(1000);
            
            // Turn LED2 on
            LED_set_value(LED2_PORT, LED2_PIN, 0); // Turn on LED2
            _delay_ms(1000);

            // Turn LED2 off
            LED_set_value(LED2_PORT, LED2_PIN, 1); // Turn off LED2
            _delay_ms(1000);
            
            // Turn LED3 on
            LED_set_value(LED3_PORT, LED3_PIN, 0); // Turn on LED3
            _delay_ms(1000);

            // Turn LED3 off
            LED_set_value(LED3_PORT, LED3_PIN, 1); // Turn off LED3
            _delay_ms(1000);

        }
    }






