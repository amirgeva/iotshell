#include <config.h>

#ifdef USE_TFT

#include <tft.h>

Arduino_ESP32SPI bus = Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO);
TFT_MODEL display(&bus, TFT_RESET);

void tft_setup()
{
    display.begin();
    display.fillScreen(BLACK);
    //display.setCursor(10,10);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    //display.print("Ready");
}

void tft_loop()
{

}

uint16_t tft_width() { return display.width(); }
uint16_t tft_height() { return display.height(); }

#else

void tft_setup() {}
void tft_loop() {}

#endif // USE_TFT