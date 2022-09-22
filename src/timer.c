#include <stdio.h>
#include "driver/ledc.h"
#include "esp_err.h"
#include "driver/timer.h"
#include "driver/gpio.h"

#define TIMER_DIVIDER   16
#define TIMER_SCALE     (TIMER_BASE_CLK / TIMER_DIVIDER)
#define TIMER_INTERVAL0_SEC     (3.4179)
#define TIMER_INTERVAL1_SEC     (5.78)
#define WITHOUT_RELOAD     0
#define WITH_RELOAD        1
#define timer_idx   TIMER_0

#define CONFIG_BUTTON_PIN 12

int64_t time_step = 1.41;

void IRAM_ATTR timer_group0_isr(void *para) {

    printf("Interrupt");
    uint32_t timer_intr = timer_group_get_intr_status_in_isr(TIMER_GROUP_0);

    if (timer_intr & TIMER_INTR_T0) {

        timer_group_clr_intr_status_in_isr(TIMER_GROUP_0, TIMER_0);
        timer_group_enable_alarm_in_isr(TIMER_GROUP_0, timer_idx);

    }

    if (gpio_get_level(CONFIG_BUTTON_PIN)) {
        gpio_set_level(CONFIG_BUTTON_PIN, 0);
    }
    else {
        gpio_set_level(CONFIG_BUTTON_PIN, 1);
    }

}

void config_timer() {
        
        timer_config_t timer = {
        .divider = TIMER_DIVIDER,
        .counter_dir = TIMER_COUNT_UP,
        .counter_en = TIMER_PAUSE,
        .alarm_en = TIMER_ALARM_EN,
        .auto_reload = WITH_RELOAD,

    };

        timer_init(TIMER_GROUP_0, timer_idx, &timer);

        timer_set_counter_value(TIMER_GROUP_0, timer_idx, 0x00000000ULL);
        
        timer_set_alarm_value(TIMER_GROUP_0, timer_idx, time_step * TIMER_SCALE);
        timer_enable_intr(TIMER_GROUP_0, timer_idx);
        timer_isr_register(TIMER_GROUP_0, timer_idx, timer_group0_isr, (void *) timer_idx, ESP_INTR_FLAG_IRAM, NULL);
        timer_start(TIMER_GROUP_0, timer_idx);
}

void app_main() {

    gpio_pad_select_gpio(CONFIG_BUTTON_PIN);
    gpio_set_direction(CONFIG_BUTTON_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(CONFIG_BUTTON_PIN, 0);
    config_timer();

}
