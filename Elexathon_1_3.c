#include <reg51.h>

sbit start_btn = P3^0;
sbit stop_btn = P3^2;

sbit output_pin_0 = P1^0;
sbit output_pin_1 = P1^2;
sbit output_pin_2 = P2^7;
sbit output_pin_3 = P3^1;
sbit output_pin_4 = P2^6;

sbit response_pin_0 = P2^0;
sbit response_pin_1 = P2^1;
sbit response_pin_2 = P2^2;
sbit response_pin_3 = P2^3;
sbit response_pin_4 = P2^4;

volatile unsigned long int system_time = 0;
volatile bit stop_flag = 0;

void check_stop_btn() {
    if(stop_btn == 0) { // Check if stop button is low (active low)
        stop_flag = 1; // Set stop flag when stop button is pressed
    }
}

void init() {
    // Set output pins as output
    output_pin_0 = 0;
    output_pin_1 = 0;
    output_pin_2 = 0;
    output_pin_3 = 0;
    output_pin_4 = 0;

    // Set response pins as output and initially set to 0
    response_pin_0 = 0;
    response_pin_1 = 0;
    response_pin_2 = 0;
    response_pin_3 = 0;
    response_pin_4 = 0;

    // Set start and stop buttons as input
    P3 = P3 | 0x05; // Set bits 0 and 2 of P3
}

void delay(unsigned int time) {
    unsigned int i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 9; j++); // Adjust this value for proper delay
}

void main() {
    init(); // Initialize ports

    // Wait for the start button to be pressed before proceeding
    while(start_btn == 1);

    system_time = 0; // Reset system time

    // Main super loop
    while(1) {
        // Increment system time
        system_time++;

        // Check stop button
        check_stop_btn();

        // Perform actions based on elapsed time for each process
        if (system_time >= 10000) { // 10 seconds
            output_pin_0 = 1; // Make P1.0 high
            if (system_time >= 11000) { // 11 seconds
                response_pin_0 = 1; // Make P2.0 high
            }
        }
        if (system_time >= 17000) { // 17 seconds
            output_pin_1 = 1; // Make P1.2 high
            if (system_time >= 18000) { // 18 seconds
                response_pin_1 = 1; // Make P2.1 high
            }
        }
        if (system_time >= 30000) { // 30 seconds
            output_pin_2 = 1; // Make P2.7 high
            if (system_time >= 31000) { // 31 seconds
                response_pin_2 = 1; // Make P2.2 high
            }
        }
        if (system_time >= 32000) { // 32 seconds
            output_pin_3 = 1; // Make P3.1 high
            if (system_time >= 33000) { // 33 seconds
                response_pin_3 = 1; // Make P2.3 high
            }
        }
        if (system_time >= 40000) { // 40 seconds
            output_pin_4 = 1; // Make P2.6 high
            if (system_time >= 41000) { // 41 seconds
                response_pin_4 = 1; // Make P2.4 high
            }
        }

        // Check if stop flag is set
        if (stop_flag) {
            // Reset outputs and break out of the loop
            output_pin_0 = 0;
            output_pin_1 = 0;
            output_pin_2 = 0;
            output_pin_3 = 0;
            output_pin_4 = 0;
            response_pin_0 = 0;
            response_pin_1 = 0;
            response_pin_2 = 0;
            response_pin_3 = 0;
            response_pin_4 = 0;
            break;
        }

        delay(8); // Delay
    }
}
