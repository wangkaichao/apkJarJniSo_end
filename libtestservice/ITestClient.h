#ifndef __ITestClient_H__
#define __ITestClient_H__

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
//#include <Thread.h>

namespace android {

    class ITestClient: public IInterface
    {
    public:
        DECLARE_META_INTERFACE(TestClient);

        //virtual void notify(unsigned int type, void* data, unsigned int len, void* prev) = 0;
    };

// ----------------------------------------------------------------------------

    class BnTestClient: public BnInterface<ITestClient>
    {
    public:
        virtual status_t    onTransact( uint32_t code,
                                        const Parcel& request,
                                        Parcel* reply,
                                        uint32_t flags = 0);
    private:
       //static Mutex mNotifyLock;
    };

}; // namespace android

#endif // __ITestClient_H__

