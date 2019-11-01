#include "CANTransceiver.hpp"

CANTransceiver::CANTransceiver(const char* device)
{
    _initHW();
    _fd = socket(PF_CAN,SOCK_RAW,CAN_RAW);
    if(_fd == -1)
    {
        perror("socket() error");
        exit(E_SOCKETCREATION);
    }

    strcpy(_ifr.ifr_name,device);
    ioctl(_fd,SIOCGIFINDEX,&_ifr);
    _addr.can_family = AF_CAN;
    _addr.can_ifindex = _ifr.ifr_ifindex;
    if(bind(_fd,(struct sockaddr*)&_addr,sizeof(_addr))<0)
    {
        printf("error occured at bind()\n");
        close(_fd);
        exit(E_SOCKETBINDEN);
    }

}

int CANTransceiver::getCANfd()
{
    return _fd;
}

void CANTransceiver::_initHW()
{
    int ret = system("./initCAN.sh");
    if(ret==-1)
    {
        printf("system() error\n");
        exit(-1);
    }
    else if(WIFEXITED(ret))
    {
        if(WEXITSTATUS(ret)!=0)
        {
            printf("system() child process terminated, shell execution has failure code %x\n",WEXITSTATUS(ret));
            exit(-1);
        }
        printf("system() child process terminated, sheel execution completed without error\n");
    }
    else
    {
        printf("system() child process abnormally terminated\n");
        exit(-1);
    }
}

