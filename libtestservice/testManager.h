#ifndef __TVMANAGER_H__
#define __TVMANAGER_H__

#define TAG "ATVMW@TestManager"

#include "ITestManager.h"
#include "TestClient.h"

#include <utils/String16.h>
#include <utils/Log.h>

namespace android {

    class TestManager : virtual public ITestManager
    {
    public:

        status_t invoke(const Parcel& request, Parcel *reply);

        virtual int getInfoFromServer(char *info);

        TestManager();
        ~TestManager();

    private:

        sp<TestClient>   mClient;
        Mutex          mLock;

    };

    inline TestManager::TestManager()
    {
        mClient = new TestClient();
    }

    inline TestManager::~TestManager()
    {

    }

    inline sp<ITestManager> TestCreator::create()
    {
        Mutex::Autolock lock(mITestManagerLock);
        if (NULL == mTestManager.get())
        {
            mTestManager = new TestManager();
        }
        return mTestManager;
    }

};
#endif

