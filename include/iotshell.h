#pragma once

#include <functional>

class UserModule
{
public:
    virtual void setup() = 0;
    virtual void loop() = 0;
};

typedef std::function<void()> function;
bool register_module(function setup_function, function loop_function);
bool register_module(UserModule* module);

void user_setup();
void user_loop();