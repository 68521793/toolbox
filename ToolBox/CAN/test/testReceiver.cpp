#include "utility.hpp"
#include "MessageReceiver.hpp"
#include "CANTransceiver.hpp"
int main()
{
    MessageReceiver* receiver = MessageReceiver::getMessageReceiver();
    receiver->addFilter(0x101,0x101);

    CANTransceiver can0(const_cast<char*>("can0"));


    BYTE* msg;
    receiver->recvFrame(can0.getCANfd(),msg,8*sizeof(BYTE));
    printf("the received msg: %s\n",msg);
    return 0;
}