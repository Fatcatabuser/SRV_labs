#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>


int main(int argc,char* argv)
{
    char rmessage[30] = {"SergeiSisoevI993"};
    char valid[30]={"Message is valid"};
    char not_valid[30] = {"Message is not valid"};
    int rcvid;
    int chid;
    char message[30];
    printf("Prog server \n");
    printf("Server start working/n");
    chid = ChannelCreate(0);
    printf("Chanel id : %d \n", chid);
    printf("Pid: %d \n", getpid());

    while (1)
    {
        rcvid = MsgReceive(chid, message, sizeof(message), NULL);
        printf("Polychili soobshenie, rcid %X \n", rcvid);
        printf("Soobshenie takoe : \"%s\".\n", message);
        if(!strcmp(rmessage,message)){
            MsgReply(rcvid, EOK, valid, sizeof(valid));
        }
        else{
        MsgReply(rcvid, EOK, not_valid, sizeof(not_valid));
        }
        printf("\"%s\". \n", message);
    }
    sleep(5);
    return (1);
}
