#include "Message.hpp"
#include <linux/can.h>
Message::Message(std::string Msgname,canid_t canID,int datalength)
{
    frame.can_id = canID;
    this->msgName = Msgname;
    frame.can_dlc = datalength;
}

can_frame* CAN::getframe()
{
    return &frame;
}

void Message::setFieldData(BYTE* data)
{
    for (size_t i = 0; i < frame.can_dlc; i++)
    {
        frame.data[i] = data[i];
    }
    
}
