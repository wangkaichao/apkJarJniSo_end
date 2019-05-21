#ifndef __TestClient_H__
#define __TestClient_H__

#include <binder/IMemory.h>
#include <utils/KeyedVector.h>
#include <utils/String8.h>
#include <utils/String16.h>
#include "ITestService.h"
namespace android {

    static const String16 Test_INTERFACE_NAME("android.ITestService");
    static const int   EXCUTE_CMD_FAILURE = -1;
    static const int   EXCUTE_CMD_SUCCESS = 0;

    class TestClient : public BnTestClient
    {
    public:
        TestClient();
        virtual ~TestClient();
        static void instantiate();
        status_t connect();
        status_t invoke(const Parcel& request, Parcel *reply);
        status_t exeCmdGet(int cmd, int arg1);
        status_t exeCmdGet(int cmd, Parcel &result);
        static TestClient* instance();
    private:

        const sp<ITestService> & getTestService();
    };

inline TestClient* TestClient::instance()
{
    TestClient* mTestClient = new TestClient();
    return mTestClient;
}

};
#endif // __TestClient_H__

