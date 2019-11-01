#include <string>
#include <iostream>
#include <linux/can.h>
typedef unsigned char BYTE;
class Message
{
    protected:
    canid_t _canID;
    std::string _msgName;
    can_frame _frame;
    public:
    Message(std::string Msgname,canid_t canID,int datalength);
    can_frame* getframe();
    void setFieldData(BYTE* data);
    
};

