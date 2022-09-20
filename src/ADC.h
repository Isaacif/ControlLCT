#include "driver/adc.h"

#define ADC_RESOLUTION ADC_WIDTH_12Bit
#define ADC_CHANNEL ADC_CHANNEL_6
#define ADC_ATTEN ADC_ATTEN_11db


void config_adc() {
    
    adc1_config_width(ADC_RESOLUTION);
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN);

}

int16_t adc_read(int16_t result) {
    
    result = adc1_get_raw(ADC_CHANNEL);
    return result;
}

