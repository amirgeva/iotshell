#include <config.h>

#ifdef USE_ENCODERS

#include <Arduino.h>
#include <AiEsp32RotaryEncoder.h>
#include <encoder.h>
#include <iotshell.h>

static AiEsp32RotaryEncoder* encoders[4]={0,0,0,0};
static uint8_t last[] = {0,0,0,0};
static uint8_t values[] = {0,0,0,0};
#define DECLARE_ISR(x) void IRAM_ATTR isr##x()\
{ encoders[x]->readEncoder_ISR(); values[x]=encoders[x]->readEncoder(); }
DECLARE_ISR(0)
DECLARE_ISR(1)
DECLARE_ISR(2)
DECLARE_ISR(3)
#undef DECLARE_ISR

RotaryEncoder::RotaryEncoder(int a_, int b_, int sw_, bool circular_, int max_value_)
: index(-1)
, circular(circular_)
, max_value(max_value_)
, last_click(false)
{
    for(int i=0;i<4;++i)
    {
        if (!encoders[i])
        {
            index=i;
            encoders[i]=new AiEsp32RotaryEncoder(a_, b_, sw_);
            register_module([this]{ this->setup(); }, [this]{this->loop();});
            break;
        }
    }
}

void RotaryEncoder::setup()
{
    if (index>=0)
    {
        encoders[index]->begin();
        #define ISR_SETUP(x) if (index==x) encoders[x]->setup(isr##x);
        ISR_SETUP(0);
        ISR_SETUP(1);
        ISR_SETUP(2);
        ISR_SETUP(3);
        #undef ISR_SETUP
        encoders[index]->setBoundaries(0,max_value,circular);
        encoders[index]->setAcceleration(25);
    }
}

void RotaryEncoder::loop()
{
    bool clicked=is_clicked();
    if (clicked && !last_click && on_click)
        on_click();
    last_click=clicked;
}

bool RotaryEncoder::is_changed() const
{
    if (index<0 || last[index]==values[index]) return false;
    return true;
}

int RotaryEncoder::read() const
{
    if (index<0) return 0;
    last[index]=values[index];
    return values[index];
}

bool RotaryEncoder::is_clicked() const
{
    if (index<0) return false;
    return encoders[index]->isEncoderButtonClicked();
}

void RotaryEncoder::set_onclick(function cb)
{
    on_click=cb;
}

#endif // USE_ENCODERS