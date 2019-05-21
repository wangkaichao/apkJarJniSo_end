#define LOG_NDEBUG 0
#define LOG_TAG "ATVMW@TestClient"

#include <utils/Log.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/MemoryBase.h>
#include <utils/String8.h>

#include "TestClient.h"

namespace android {

    sp<ITestService> gTestService;
    Mutex gServiceLock;

    class DeathNotifier : public IBinder::DeathRecipient
    {
    public:
        DeathNotifier() {}

        virtual void binderDied(const wp<IBinder>& who)
        {
            ALOGW("Test service died!");
            Mutex::Autolock _l(gServiceLock);
            gTestService.clear();
        }
    };

    sp<DeathNotifier>         gDeathNotifier;

    const sp<ITestService>& TestClient::getTestService()
    {
        Mutex::Autolock _l(gServiceLock);
        if(gTestService.get() == 0)
        {
            sp<IServiceManager> sm = defaultServiceManager();
            sp<IBinder> binder ;
            do
            {
                binder = sm->getService(String16("TestService"));
                if (binder != 0)
                {
                    break;
                }

                ALOGD("Test service not published...");
                usleep(500*1000);
            } while(true);
            if (gDeathNotifier == NULL) {
                gDeathNotifier = new DeathNotifier();
            }
            binder->linkToDeath(gDeathNotifier);
            gTestService = interface_cast<ITestService>(binder);
            if(gTestService.get() != 0)
            {
                gTestService->connect(getpid(), this);
            }
        }

        return gTestService;
    }

    TestClient::TestClient()
    {
        ALOGD("Test constructor");
    }

    TestClient::~TestClient()
    {
        ALOGD("Test destructor");
    }

    status_t TestClient::connect()
    {
        int ret = -1;
        ALOGD("Test connect TestService");

        const sp<ITestService>& ps = getTestService();
#if 0
        if(ps.get() != 0)
        {
            ret = ps->connect(getpid(), this);
        }
#endif
        ret = 0;
        return  ret;
    }

    status_t TestClient::invoke(const Parcel& request, Parcel *reply)
    {
        int ret = -1;
        const sp<ITestService>& ps = getTestService();
        ALOGD("Test TestClient::invoke");
        if(ps != 0)
        {
            //ALOGD("enter invoke,client pid=%d",getpid());
            ret = ps->invoke(request, reply);
        }

        return  ret;
    }

    status_t TestClient::exeCmdGet(int cmd, int arg1)
    {
        const sp<ITestService>& ps = getTestService();
        Parcel request;
        Parcel reply;

        request.writeInterfaceToken(Test_INTERFACE_NAME);
        request.writeInt32(cmd);

        request.writeInt32(arg1);

        if (EXCUTE_CMD_SUCCESS == ps->invoke(request, &reply)
            && EXCUTE_CMD_SUCCESS == reply.readInt32())
        {
            return reply.readInt32();
        }

        return EXCUTE_CMD_FAILURE;
    }

    status_t TestClient::exeCmdGet(int cmd, Parcel &result)
    {
        const sp<ITestService>& ps = getTestService();
        Parcel request;
        Parcel reply;

        request.writeInterfaceToken(Test_INTERFACE_NAME);
        request.writeInt32(cmd);

        if (EXCUTE_CMD_SUCCESS == ps->invoke(request, &reply)
            && EXCUTE_CMD_SUCCESS == reply.readInt32())
        {
            result.setData(reply.data() + sizeof(int), reply.dataSize() - sizeof(int));
            return EXCUTE_CMD_SUCCESS;
        }

        return EXCUTE_CMD_FAILURE;
    }
}; // namespace android

