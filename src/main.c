#include "stdio.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "ADC.h"
#include "PWM.h"

int16_t result;

void app_main() {
    config_adc(); 
    ledc_init();

    while(true) {

    }
}