
#include "Message.hpp"
#include "utility.hpp"

int createSocket()
{
    int canFD = socket(PF_CAN,SOCK_RAW,CAN_RAW);
    if(canFD == -1)
    {
        perror("socket() error");
        exit(-1);
    }
    return canFD;

}

int bindCANInterface(int fd,char* device)
{
    struct ifreq ifr;
    strcpy(ifr.ifr_name,device);
    ioctl(fd,SIOCGIFINDEX,&ifr);

    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if(bind(fd,(struct sockaddr*)&addr,sizeof(addr))<0)
    {
        printf("error occured at bind()\n");
        exit(-2);
    }
   
}

void testWrite(int fd,struct can_frame* pcanFrame)
{
    int wrbytes = write(fd,pcanFrame,sizeof(struct can_frame));
    if(wrbytes<0)
    {
        perror("write() error occured");
        exit(-1);
    }
    printf("%d bytes written to can channel\n",wrbytes);
}

void testRead(int fd)
{
    struct can_frame frame;
    frame.can_dlc = 2;
    frame.can_id = 0x101;
    frame.data[0] = 0x66;
    frame.data[1] = 0x88;
    int wrbytes = read(fd,&frame,sizeof(struct can_frame));
    if(wrbytes<0)
    {
        perror("write() error occured");
        exit(-1);
    }
    printf("data[0]: %x\n",frame.data[0]);
    printf("data[1]: %x\n",frame.data[1]);
}

void initCAN()
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

int main(int argc, char* argv[])
{
    if(argc<2)
    {
        printf("./socketCAN canName\n");
        exit(0);
    }
    initCAN();
    
    int canfd = createSocket();
    bindCANInterface(canfd,argv[1]);
    
    CAN frame_tx("Test",0x444,8);
    BYTE data[8] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
    frame_tx.setCANFieldData(data);

    testWrite(canfd,frame_tx.getCANFrame());
   // testRead(canfd);
    close(canfd);
    return 0;
}