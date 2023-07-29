#include <config.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <flash.h>

#ifdef USE_FLASH

unsigned allocation_position=0;

void flash_init(unsigned size)
{
    EEPROM.begin(size);
}

unsigned flash_allocate(unsigned len)
{
    unsigned res=allocation_position;
    allocation_position+=len;
    return res;
}

unsigned flash_write(unsigned address, const char* buffer, int len)
{
    for(int i=0;i<len;++i)
        EEPROM.write(address++,*buffer++);
    return address;
}

unsigned flash_read(unsigned address, char* buffer, int len)
{
    for(int i=0;i<len;++i)
        *buffer++ = EEPROM.read(address++);
    return address;
}

bool flash_commit()
{
    return EEPROM.commit();
}

#else

void flash_init(unsigned size){}
unsigned flash_write(unsigned address, const char* buffer, int len) { return 0; }
unsigned flash_read(unsigned address, char* buffer, int len) { return 0; }
bool flash_commit() { return false; }

#endif // USE_FLASH