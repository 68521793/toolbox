#include "MessageReceiver.hpp"
#include "utility.hpp"
MessageReceiver* MessageReceiver::_receiver=NULL;
int MessageReceiver::addFilter(canid_t can_id,canid_t can_mask)
{
    if (_filterCounter>=FILTERMASKMAX)
    {
        printf("message filter out of boundary");
        return E_OUT_OF_BOUNDARY;
    }
    _filter[_filterCounter].can_id = can_id;
    _filter[_filterCounter].can_mask = can_mask;
    _filterCounter++;
    return 0;
}

MessageReceiver* MessageReceiver::getMessageReceiver()
{
    if (_receiver==NULL)
    {
        _receiver = new MessageReceiver();
    }
    return _receiver;
}

MessageReceiver::MessageReceiver()
{
    _frameBuffer = new std::queue<can_frame>();
    _filterCounter = 0;
    _filter = new struct can_filter[FILTERMASKMAX];
    
}

int MessageReceiver::recvFrame(int fd,BYTE* buf,int length)
{
    setsockopt(fd,SOL_CAN_RAW,CAN_RAW_FILTER,_filter,_filterCounter*sizeof(struct can_filter));
    fd_set fd_read;
    FD_ZERO(&fd_read);
    FD_SET(fd,&fd_read);
    int ret_select; 
    bool intr_flag = false;
    do{
        
        intr_flag=false;
        ret_select = select((int)fd+1,&fd_read,NULL,NULL,NULL);
        if ((ret_select==-1)&&(errno==EINTR))
        {
            intr_flag=true;
        }
        else if(ret_select==-1)
        {
            perror("select(): signal interrupted");
            return E_SIGNAL_INTERRUPT;
        }
    }while(intr_flag==true);
    int ret = read(fd,buf,length);
    if (ret==-1)
    {
        perror("read error occured");
        return E_IO_READ;
    }
    return ret;
  
}
