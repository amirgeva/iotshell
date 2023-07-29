#pragma once

void flash_init(unsigned size);
unsigned flash_allocate(unsigned len);
unsigned flash_write(unsigned address, const char* buffer, int len);
unsigned flash_read(unsigned address, char* buffer, int len);
bool flash_commit();

template<typename T>
inline unsigned flash_write(unsigned address, const T& t)
{
    return flash_write(address,reinterpret_cast<const char*>(&t),sizeof(T));
}

template<typename T>
inline unsigned flash_read(unsigned address, T& t)
{
    return flash_read(address,reinterpret_cast<char*>(&t),sizeof(T));
}
