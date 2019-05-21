#ifndef __ITVMANAGER_H__
#define __ITVMANAGER_H__

#include <utils/RefBase.h>
#include <utils/Errors.h>
#include <utils/Mutex.h>
#include <utils/String16.h>
#include <binder/Parcel.h>

namespace android {


    class ITestManager : virtual public RefBase
    {
    public:
        virtual status_t invoke(const Parcel& request, Parcel* reply) = 0;

        // test info
        virtual int getInfoFromServer(char *info) = 0;
    };

    class TestCreator
    {
    public:
        static sp<ITestManager> create();

    private:

        static sp<ITestManager> mTestManager;
        static Mutex mITestManagerLock;
    };

};

#endif
