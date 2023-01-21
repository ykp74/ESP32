#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
//#include "led_strip.h"
#include "sdkconfig.h"

#define CONFIG_BLINK_PERIOD 1000

static const char *TAG = "example";
static uint8_t s_led_state = 0;
#define BLINK_GPIO 2


static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}


void led_task(void *p)
{
    while(true){
        ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
        /* Set the GPIO level according to the state (LOW or HIGH)*/
        gpio_set_level(BLINK_GPIO, s_led_state);

        /* Toggle the LED state */
        s_led_state = !s_led_state;
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    /* Configure the peripheral according to the LED type */
    configure_led();

    xTaskCreate(led_task, "LED_Task 1", 4096, NULL, 5, NULL);
}