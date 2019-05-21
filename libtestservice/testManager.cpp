#define TAG "ATVMW@SkyTVManager"

#include "testManager.h"

#include <utils/Log.h>

namespace android {

    sp<ITestManager> TestCreator::mTestManager = NULL;
    Mutex TestCreator::mITestManagerLock;

    status_t TestManager::invoke(const Parcel& request, Parcel *reply)
    {
        Parcel writedata;

        writedata.writeInterfaceToken(Test_INTERFACE_NAME);
        writedata.appendFrom(&request, 0, request.dataSize());

        if (mClient.get() != NULL)
        {
            if (EXCUTE_CMD_SUCCESS != mClient->invoke(writedata, reply))
            {
                ALOGE("[%d]invoke failure\n", __LINE__);
            }
            else
            {
                return reply->readInt32();
            }
        }

        return EXCUTE_CMD_FAILURE;
    }

    int TestManager::getInfoFromServer(char * info)
    {
        Parcel colortempDebugInfo;
        int ret;
        ret = mClient->exeCmdGet(520, colortempDebugInfo);
        const char* colortempDebugInfoStr = colortempDebugInfo.readCString();
        strcpy(info,colortempDebugInfoStr);
        return ret;
    }

};

