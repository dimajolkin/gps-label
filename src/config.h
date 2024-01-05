#pragma once

#define LED_PIN PC_13


#define TFT_CS PB_10
#define TFT_RST PB_1
#define TFT_DC PB_0

#define SPI_MOSI PA_7
#define SPI_MISO PA_6
#define SPI_SCK PA_5

#define RADIO_SPI_MOSI PB_15
#define RADIO_SPI_MISO PB_14
#define RADIO_SPI_SCK PB_13

#define RADIO_CE PA_9
#define RADIO_CSP PA_8
#define RADIO_IRQ PA_12
 
#define EEPROM_SDA PB_9
#define EEPROM_SCL PB_8

#define GPS_TX PB_6
#define GPS_RX PB_7

#define BTN_RIGHT PA_4
#define BTN_LEFT PA_0
#define BTN_UP PC_15
#define BTN_DOWN PA_3
#define BTN_OK PC_14

#define BATTERY_PIN PA_1
#define BATTERY_MIN_VOLTAGE 3300
#define BATTERY_MAX_VOLTAGE 4700
#define BATTERY_REF_VOLTAGE 4700
#define BATTERY_DIVIDER_RATION 2

#define BACKGROUND_COLOR ST7735_GREEN