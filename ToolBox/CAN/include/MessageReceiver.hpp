#include "utility.hpp"
#include <queue>
typedef unsigned char BYTE;
class MessageReceiver
{
    private:
    struct can_filter* _filter;
    int _filterCounter;
    std::queue<can_frame>* _frameBuffer;
    static MessageReceiver* _receiver;

    public:
    int addFilter(canid_t can_id,canid_t can_mask);
    static MessageReceiver* getMessageReceiver();
    int recvFrame(int fd,BYTE* buf,int length);

    private:    
    MessageReceiver();
    
};





