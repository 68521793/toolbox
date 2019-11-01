#include "utility.hpp"
class CANTransceiver
{
    private:
    int _fd;
    struct ifreq _ifr;
    struct sockaddr_can _addr;
    void _initHW();

    public:
    CANTransceiver(const char* device);
    int getCANfd();

};

