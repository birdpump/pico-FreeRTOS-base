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
        vTaskDelay(pdMS_TO_TICKS(100));

        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(800));
    }
}


void serial_task(void *pvParameters) {
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(100); // Frequency of 100 ms

    xLastWakeTime = xTaskGetTickCount();

    while (true) {
        // Get the current tick count
        TickType_t currentTick = xTaskGetTickCount();

        // Convert ticks to milliseconds
        uint32_t timeInMs = currentTick * portTICK_PERIOD_MS;
        uint32_t seconds = timeInMs / 1000;
        uint32_t milliseconds = timeInMs % 1000;

        // Print the current time in seconds and milliseconds
        printf("Time: %lu.%03lu seconds - Serial Test\n", seconds, milliseconds);

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
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

    if (xTaskCreate(serial_task, "serial_task", 256, NULL, 2, NULL) != pdPASS) {
        printf("Failed to create LED task\n");
        while (1); // Halt if task creation failed
    }

    // Start FreeRTOS scheduler
    vTaskStartScheduler();

    // Should never reach here
    printf("Scheduler failed to start\n");
    while (1);
}
