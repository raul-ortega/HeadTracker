#include "led.h"
#include "io.h"
#include "defines.h"
#include "trackersettings.h"

uint32_t ledmode = 0;

void led_init()
{
    pinMode(LED_BUILTIN, GPIO_OUTPUT);
    pinMode(ARDUINO_LEDPWR, GPIO_OUTPUT);
    pinMode(LEDR, GPIO_OUTPUT);
    pinMode(LEDG, GPIO_OUTPUT);
    pinMode(LEDB, GPIO_OUTPUT);
    digitalWrite(ARDUINO_LEDPWR,HIGH);
    digitalWrite(LEDR,HIGH);
    digitalWrite(LEDG,HIGH);
    digitalWrite(LEDB,HIGH);
}

void led_Thread()
{
    bool led_is_on=false;
    int led_on_time=0;
    int led_off_time=0;

    uint32_t counter=0;
	while (1) {
        // External LED
        pinMode(D_TO_32X_PIN(13), GPIO_OUTPUT);
        if(ledmode & LED_GYROCAL) {
            led_on_time = 100;
            led_off_time = 0;
        } else if (ledmode & LED_BTCONNECTED) {
            led_on_time = 800;
            led_off_time = 200;
        } else {
            led_on_time = 20;
            led_off_time = 200;
        }
        if((!led_is_on && counter % led_off_time == 0) ||
            (led_is_on && counter % led_on_time == 0)) {
            led_is_on = !led_is_on;
            digitalWrite(LED_BUILTIN,led_is_on);
        }

        // RGB_LED Output
        if(ledmode & LED_BTCONNECTED) // Blue LED = Bluetooth connected
            digitalWrite(LEDB,LOW);
        else
            digitalWrite(LEDB,HIGH);

        if(ledmode & LED_GYROCAL) // Red LED Flashing = Gyro_in_calibration
            digitalWrite(LEDR,LOW);
        else
            digitalWrite(LEDR,HIGH);

        k_msleep(LED_PERIOD); // Reduce power, short flash
        counter+=LED_PERIOD;
	}
}

void setLEDFlag(uint32_t ledMode)
{
    ledmode |= ledMode;
}

void clearLEDFlag(uint32_t ledMode)
{
    ledmode &= ~ledMode;
}

void clearAllFlags(uint32_t ledMode)
{
    ledmode = 0;
}
