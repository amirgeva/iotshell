#include <config.h>

#ifdef USE_AUDIO

#include <audio_stream.h>

#ifndef USE_WIFI
#error Audio requires wifi
#endif

#include <Arduino.h>
#include <WiFi.h>
#include <Audio.h>

Audio audio;

void audio_setup()
{
    audio.setPinout(AUDIO_BCLK, AUDIO_LRC, AUDIO_DOUT);
    audio.setVolume(21);
    audio.connecttohost("https://playerservices.streamtheworld.com/api/livestream-redirect/WQLZFM.mp3?dist");
}

void audio_set_volume(int volume)
{
    audio.setVolume(volume);
}

void audio_loop()
{
    audio.loop();
}

void audio_play(const char* url)
{
    audio.connecttohost(url);
}


#else

void audio_setup(){}
void audio_loop(){}
void audio_play(const char* url){}
void audio_set_volume(int volume){}

#endif // USE_AUDIO