#include <Arduino.h>
#include <config.h>
#include <iotshell.h>
#include <wifi_config.h>
#include <wifi_client.h>
#include <ota.h>
#include <tft.h>
#include <audio_stream.h>
#include <flash.h>

bool wifi_config_mode=false;

/*
static bool did_serial_init=false;
void serial_init()
{
    if (!did_serial_init)
    {
        did_serial_init=true;
        Serial.begin(115200);
        while (!Serial) delay(10);
    }
}
*/

struct Module
{
    function setup_function, loop_function;
    bool setup()
    {
        if (!setup_function) return false;
        setup_function();
        return true;
    }
    bool loop()
    {
        if (!loop_function) return false;
        loop_function();
        return true;
    }
};

static Module g_Modules[MODULE_LIMIT];

bool register_module(function setup_function, function loop_function)
{
    if (setup_function && loop_function)
    {
        //serial_init();
        for(int i=0;i<MODULE_LIMIT;++i)
        {
            Module& m=g_Modules[i];
            if (!m.setup_function)
            {
                m.setup_function=setup_function;
                m.loop_function=loop_function;
                return true;
            }
        }
    }
    return false;
}

void setup()
{
    Serial.begin(115200);
    while (!Serial) delay(10);
    flash_init(FLASH_SIZE);
    Serial.println("Starting iotshell");
    pinMode(GPIO_WIFI_CONFIG,INPUT_PULLUP);
    delay(100);
    tft_setup();
    wifi_config_mode = (digitalRead(GPIO_WIFI_CONFIG)==LOW);
    if (wifi_config_mode)
        wifi_config_setup();
    else
    {
        wifi_setup();
        ota_setup();
    }
    audio_setup();
    user_setup();
    for(int i=0;i<MODULE_LIMIT;++i)
    {
        if (!g_Modules[i].setup()) break;
        Serial.print("Setup module ");
        Serial.println(i);
    }
}


void loop()
{
    if (wifi_config_mode)
        wifi_config_loop();
    else
    {
        wifi_loop();
        ota_loop();
    }
    tft_loop();
    audio_loop();
    user_loop();
    for(int i=0;i<MODULE_LIMIT;++i)
        if (!g_Modules[i].loop()) break;
}


