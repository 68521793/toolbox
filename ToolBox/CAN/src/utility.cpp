#include "utility.hpp"

void delay_ms(const unsigned int interval)
{
    struct timespec time_interval;
    time_interval.tv_sec = interval/1000;
    time_interval.tv_nsec = (interval%1000)*1000000;
    nanosleep(&time_interval,NULL);
}