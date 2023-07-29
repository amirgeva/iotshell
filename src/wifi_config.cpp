#include <config.h>
#ifdef USE_WIFI

#include <Arduino.h>
#include <WiFi.h>
#include <flash.h>

static WiFiServer server(0x5e79);

static const char* setup_ssid="setup";
static const char* setup_pass="";
static char wifi_ssid[WIFI_SIZE];
static char wifi_password[WIFI_SIZE];

void wifi_save_credentials()
{
    unsigned address=flash_allocate(2*WIFI_SIZE);
    address=flash_write(address,wifi_ssid,WIFI_SIZE);
    address=flash_write(address,wifi_password,WIFI_SIZE);
    flash_commit();
}

void wifi_config_setup()
{
    WiFi.softAP(setup_ssid, setup_pass);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    server.begin();
}

enum State { INITIAL, GET_SSID, GET_PASS, DONE };

void wifi_config_loop()
{
    WiFiClient client = server.available();
    if (client)
    {
        long start_time=millis();
        State state=INITIAL;
        int pos=0;
        char* target=0;
        bool ignore_lf=false;
        while (client.connected())
        {
            long cur_time=millis();
            if ((cur_time-start_time)<2000)
            {
                if (client.available())
                {
                    char c=client.read();
                    Serial.print("Ignoring ");
                    Serial.println(int(c));
                }
                continue;
            }
            if (state==INITIAL)
            {
                client.write("SSID:");
                state=GET_SSID;
                pos=0;
                target=wifi_ssid;
            }
            if (client.available())
            {
                char c = client.read();
                Serial.print("Received: ");
                Serial.println(int(c));
                if (c==10 || c==13)
                {
                    if (c==13) ignore_lf=true;
                    if (c==10 && ignore_lf)
                    {
                        ignore_lf=false;
                        continue;
                    }
                    if (state==GET_SSID)
                    {
                        Serial.println("Received SSID");
                        delay(1000);
                        client.write("\nPASS:");
                        delay(1000);
                        state=GET_PASS;
                        delay(1000);
                        target=wifi_password;
                        delay(1000);
                        pos=0;
                        delay(1000);
                        continue;
                    }
                    if (state==GET_PASS)
                    {
                        state=DONE;
                        wifi_save_credentials();
                        client.write("Done.  Please reboot.\n\n");
                        while (true);
                    }
                }
                else
                if (pos<15)
                {
                    client.write(c);
                    target[pos]=c;
                    target[pos+1]=0;
                    Serial.println(target);
                    ++pos;
                }
            }
        }
    }
}

#else

void wifi_config_setup(){}
void wifi_config_loop(){}

#endif // USE_WIFI