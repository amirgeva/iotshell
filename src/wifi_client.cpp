#include <config.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <flash.h>

#ifdef USE_WIFI

void wifi_setup()
{
  unsigned address=flash_allocate(2*WIFI_SIZE);
  char wifi_ssid[WIFI_SIZE];
  char wifi_password[WIFI_SIZE];
  address=flash_read(address,wifi_ssid,WIFI_SIZE);
  address=flash_read(address,wifi_password,WIFI_SIZE);
  wifi_ssid[WIFI_SIZE-1]=0;
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  Serial.println("Connected");
}

void wifi_loop()
{

}

#else

void wifi_setup(){}
void wifi_loop(){}


#endif // USE_WIFI