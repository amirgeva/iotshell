#include <iotshell.h>

bool register_module(UserModule* module)
{
    return register_module([module]{module->setup();},[module]{module->loop();});
}
