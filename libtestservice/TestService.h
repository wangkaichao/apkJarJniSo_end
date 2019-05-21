#ifndef ANDROID_TVSERVICE_H
#define ANDROID_TVSERVICE_H

#include <utils/Log.h>
#include <utils/threads.h>
#include <utils/List.h>
#include <utils/Errors.h>
#include <utils/KeyedVector.h>
#include <utils/String8.h>
#include <utils/Vector.h>
#include <system/audio.h>
#include <binder/Parcel.h>
#include "ITestService.h"


namespace android {

    class TestService : public BnTestService
    {

    public:
        TestService();
        virtual   ~TestService();

        static void instantiate();

        status_t connect(pid_t pid, const sp<ITestClient>& client);
        status_t invoke(const Parcel& request, Parcel *reply);
       // virtual void notifyReceived(unsigned int type, void* data, unsigned int len, void* prev) ;

    private:

        //Mutex mNotifyLock;
        SortedVector< sp<ITestClient> >  mClients;
        //mutable Mutex mLock;

    };

}; // namespace android

#endif

