#ifndef __ITVSERVICE_H__
#define __ITVSERVICE_H__

#include <utils/Errors.h>  // for status_t
#include <utils/KeyedVector.h>
#include <utils/RefBase.h>
#include <utils/String8.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <utils/String16.h>
#include "ITestClient.h"

namespace android {

    class ITestService: public IInterface
    {
    public:
        DECLARE_META_INTERFACE(TestService);

        virtual status_t connect(pid_t pid, const sp<ITestClient>& client) = 0;
        virtual status_t invoke(const Parcel& request, Parcel *reply) = 0;
    };

    class BnTestService: public BnInterface<ITestService>
    {
    public:
        virtual status_t    onTransact( uint32_t code,
                                        const Parcel& data,
                                        Parcel* reply,
                                        uint32_t flags = 0);
    };

}; // namespace android

#endif // __ITVSERVICE_H__

