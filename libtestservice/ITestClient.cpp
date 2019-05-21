#define LOG_NDEBUG 0
#define LOG_TAG "ATVMW@ITestClient"

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

#include "ITestClient.h"

namespace android {

    enum {
        NOTIFY = IBinder::FIRST_CALL_TRANSACTION,
    };

    class BpTestClient: public BpInterface<ITestClient>
    {
    public:
        BpTestClient(const sp<IBinder>& impl)
            : BpInterface<ITestClient>(impl)
        {
        }
/*
        virtual void notify(unsigned int type, void* data, unsigned int len, void* prev)
        {
            Parcel request, reply;
            request.writeInterfaceToken(ITestClient::getInterfaceDescriptor());
            request.writeInt32(type);

            if (data && len > 0)
            {
                request.write(data, len);
            }

            remote()->transact(NOTIFY, request, &reply, IBinder::FLAG_ONEWAY);
        }*/
    };

    IMPLEMENT_META_INTERFACE(TestClient, "android.ITestClient");

// ----------------------------------------------------------------------
    //Mutex BnTestClient::mNotifyLock;

    status_t BnTestClient::onTransact(
        uint32_t code, const Parcel& request, Parcel* reply, uint32_t flags)
    {
        //Mutex::Autolock _l(mNotifyLock);
        switch(code) {
            case NOTIFY: {
                CHECK_INTERFACE(ITestClient, request, reply);

                int type = request.readInt32();
                int len = request.dataAvail();
                char* data = new char[len];
                request.read(data, len);

                //notify(type, data, len, NULL);

                return NO_ERROR;
            }
            break;
            default:
                return BBinder::onTransact(code, request, reply, flags);
        }
    }

};

