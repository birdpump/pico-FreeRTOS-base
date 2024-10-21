#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdio>

#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include "queue.h"

using namespace std;

QueueHandle_t xStatusQueue;

void led_task(void *pvParameters) {
    // Configure LED pin for output
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    while (true) {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        printf("LED ON\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 100 ms

        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        printf("LED OFF\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 100 ms
    }
}

void setup() {
    // Add any setup code here, if needed
}

int main() {
    stdio_init_all(); // Initialize standard I/O

    setup();

    // Create LED task
    if (xTaskCreate(led_task, "led_task", 256, NULL, 1, NULL) != pdPASS) {
        printf("Failed to create LED task\n");
        while (1); // Halt if task creation failed
    }

    // Start FreeRTOS scheduler
    vTaskStartScheduler();

    // Should never reach here
    printf("Scheduler failed to start\n");
    while (1);
}
