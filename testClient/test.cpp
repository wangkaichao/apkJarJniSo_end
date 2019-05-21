#include <stdio.h>
#include "ShiBoClient.h"
static int pthreadInited = -1;
int main()
{
    printf("shibo    into main!\n");
    int getFormServer = 0;
    while(1)
    {
        if(pthreadInited == -1)
        {
            android::ShiBoClient::instance()->connect();
            pthreadInited = 0;
        }
        if(pthreadInited ==0)
        {
            //printf("shibo will test communite");
            getFormServer = android::ShiBoClient::instance()->exeCmdGet(520, 425);
            if(getFormServer == 422)
            {
                printf("shibo getFormServer = %d\n",getFormServer);
                pthreadInited = -2;
            }
        }
    }
    printf("shibo out main");
    return 0;
}
