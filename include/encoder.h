#pragma once

#ifdef USE_ENCODERS

#include <iotshell.h>

class RotaryEncoder
{
    int index;
    int max_value;
    bool circular;
    bool last_click;
    function on_click;
    void setup();
    void loop();
public:
    RotaryEncoder(int a_, int b_, int sw_=-1, bool circular_=false, int max_value_=100);

    bool is_changed() const;
    int  read() const;
    bool is_clicked() const;
    void set_onclick(function cb);
};

#endif // USE_ENCODERS