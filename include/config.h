#pragma once

// Pin number for wifi config boot mode
// Connect a push button between it and ground.
// Press while booting to enter a mode of hotspot
// for configuring wifi credentials
constexpr int GPIO_WIFI_CONFIG = 33;

// Number of bytes to allocate for storage of
// non-volatile data
constexpr unsigned FLASH_SIZE = 4096;

// Length of ssid, password strings
constexpr unsigned WIFI_SIZE = 16;

// Limit of number of user defined modules to run
#define MODULE_LIMIT 32

// Host name for the device
#define OTA_HOSTNAME "esp32iot"

// Empty string means to authentication
#define OTA_PASSWORD ""

// Provide facility to configure and connect to a wifi network
// If enabled, the GPIO_WIFI_CONFIG pin should have a push button
// to enable setup mode on boot
#define USE_WIFI

// Provide facility to program the module over wifi
#define USE_OTA

// Use non-volatile memory to store information
// FLASH_SIZE defines how many bytes to use
#define USE_FLASH

// Use rotary encoders
//#define USE_ENCODERS

// Define USE_TFT for using the Arduino_GFX display using SPI
//#define USE_TFT

#ifdef USE_TFT
    #include <Arduino_GFX_Library.h>
    #define TFT_SCK    18 // Hardware SCK
    #define TFT_MOSI   23 // Hardware MOSI
    #define TFT_MISO   19 // Hardware MISO
    #define TFT_CS     16 // configurable
    #define TFT_DC     17 // configurable
    #define TFT_RESET  21 // configurable
    // Select your display model
    #define TFT_MODEL  Arduino_ILI9341
    extern TFT_MODEL display;
#endif


//#define USE_AUDIO

#ifdef USE_AUDIO
    #define AUDIO_DOUT 25
    #define AUDIO_LRC  26
    #define AUDIO_BCLK 27
#endif
