#define LOG_NDEBUG 0
#define LOG_TAG "ATVMW@ITestService"

#include <stdint.h>
#include <sys/types.h>
#include <binder/Parcel.h>
#include <binder/IMemory.h>
#include <utils/Errors.h>  // for status_t
#include "utils/Log.h"

#include "ITestService.h"

namespace android {

    enum {
        CONNECT = IBinder::FIRST_CALL_TRANSACTION,
        INVOKE
    };

    class BpTestService: public BpInterface<ITestService>
    {
    public:
        BpTestService(const sp<IBinder>& impl)
            : BpInterface<ITestService>(impl)
        {
        }

        virtual status_t connect(pid_t pid, const sp<ITestClient>& client)
        {
            ALOGE("%s, %d!", __FUNCTION__, __LINE__);

            Parcel data, reply;
            data.writeInterfaceToken(ITestService::getInterfaceDescriptor());
            data.writeInt32(pid);
#if (SKY_BOARD_SDK_VERSION >= 23)
            data.writeStrongBinder(client->asBinder(client));
#else
            data.writeStrongBinder(client->asBinder());
#endif

            int i = remote()->transact(CONNECT, data, &reply);

            ALOGI("%s, %d, %d!", __FUNCTION__, __LINE__, i);

            return reply.readInt32();
        }

        status_t invoke(const Parcel& request, Parcel *reply)
        {
            //ALOGI("%s, %d!", __FUNCTION__, __LINE__);

            return remote()->transact(INVOKE, request, reply);
        }

    };

    IMPLEMENT_META_INTERFACE(TestService, "android.ITestService");

// ----------------------------------------------------------------------

    status_t BnTestService::onTransact(
        uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
    {
        switch(code) {
            case CONNECT: {
                ALOGI("Test CONNECT!");
                CHECK_INTERFACE(ITestService, data, reply);
                pid_t pid = data.readInt32();
                sp<ITestClient> client = interface_cast<ITestClient>(data.readStrongBinder());
                reply->writeInt32(connect(pid,client));
                return NO_ERROR;
            }
            break;

            case INVOKE: {

                ALOGI("Test INVOKE!");
                CHECK_INTERFACE(ITestService, data, reply);
                status_t result = invoke(data, reply);
                return result;
            }
            break;

            default:
                return BBinder::onTransact(code, data, reply, flags);
        }
    }

// ----------------------------------------------------------------------------

}; // namespace android

