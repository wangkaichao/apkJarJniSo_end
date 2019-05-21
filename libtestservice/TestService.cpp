#define LOG_NDEBUG 0
#define LOG_TAG "nativeTestService"
#include <utils/Log.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <cutils/atomic.h>
#include <cutils/properties.h> // for property_get
#include <utils/misc.h>

//#include <android_runtime/ActivityManager.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/MemoryHeapBase.h>
#include <binder/MemoryBase.h>
//#include <gui/SurfaceTextureClient.h>
#include <utils/Errors.h>  // for status_t
#include <utils/String8.h>
#include <utils/SystemClock.h>
#include <utils/Vector.h>
#include <cutils/properties.h>
#include <system/audio.h>
#include <private/android_filesystem_config.h>

#include <binder/Parcel.h>

#include <fcntl.h>
#include <dlfcn.h>

#include "TestService.h"
#ifndef LINUX_OS
#include "cutils/properties.h"  // for property_set
#endif

#define CMD_FACTORY_GET24GCONNECTSTATUS    0x9056    /**< 2.4G AMP*/
#define CMD_FACTORY_SET24GAMPENABLE        0x9054    /**< 2.4G AMP*/
#define CMD_FACTORY_SET24GUPGRADEPATH      0x9055    /**< 2.4G AMP*/

namespace android {

    typedef struct {
        const char* cmdString;
        int cmdId;
    } COMMAND;

    typedef struct {
        const char* cmdString;
        bool flag;
    } COMMAND1;

    COMMAND cmd[]= {
        {"getampconnectstatus",     CMD_FACTORY_GET24GCONNECTSTATUS},
        {"setampenable",            CMD_FACTORY_SET24GAMPENABLE},
        {"setampupgradefw",         CMD_FACTORY_SET24GUPGRADEPATH},
    };

    COMMAND1 cmd1[]= {
        {"true",        true},
        {"false",       false},
    };


    int findCmdIndex(char *input)
    {
        int i=0;
        int len;
        int cmdCnt=sizeof(cmd)/sizeof(COMMAND);
        int index=0;
        ALOGD("input string is %s\n",input);
        for(i=0; i<cmdCnt; i++)
        {
            ALOGD("cmd.cmdString is %s\n",cmd[i].cmdString);
            len=strlen(cmd[i].cmdString);
            if(!strncasecmp(cmd[i].cmdString,input,len))
            {
                index=cmd[i].cmdId;
                break;
            }
            else if(i==cmdCnt)
            {
                ALOGD("cmd.cmdString not find %d\n",i);
            }
        }

        ALOGD("cmd.cmdString match index = %d\n",index);
        return index;
    }

    TestService::TestService()
    {
        ALOGD("Test TestClient created");
    }

    TestService::~TestService()
    {
        ALOGD("TestClient destroyed");
    }

    void TestService::instantiate()
    {
        defaultServiceManager()->addService( String16("TestService"), new TestService());

        ALOGD("Test TestClient instantiate");
    }

    status_t TestService::connect(pid_t pid, const sp<ITestClient>& client)
    {
        //Mutex::Autolock lock(mLock);
        ALOGD("Test connect, client pid = %d",pid);
        mClients.add(client);
        ALOGD("Test mClients.size = %d ",mClients.size());
        return NO_ERROR;
    }


    status_t TestService::invoke(const Parcel& request, Parcel *reply)
    {
        //ALOGD("Test Enter [%s] ",__FUNCTION__);
        //ALOGD("Test invoke request =%d  arg = %d",request.readInt32(),request.readInt32());
        switch (request.readInt32())
        {
            case 520:
            {
               /* for(int i = 0; i< 1000;i++);
                ALOGD("Test invoke server 111");
                if(request.readInt32() == 425)
                    for(int i = 0; i< 1000;i++);
                ALOGD("Test invoke server 2222");
                sleep(2);
                ALOGD("Test invoke server 333");
                reply->writeInt32(0);
                reply->writeInt32(422);*/

                reply->writeInt32(0);
                reply->writeCString("hello call server success");
                break;
            }
        }
        return 0;
    }

} // namespace android

