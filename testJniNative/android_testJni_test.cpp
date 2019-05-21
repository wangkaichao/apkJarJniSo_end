#include "utils/Log.h"
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <utils/threads.h>
#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"
#include "android_runtime/android_view_Surface.h"
#include "utils/Errors.h"  // for status_t
#include "utils/KeyedVector.h"
#include "utils/String8.h"
#include "android_util_Binder.h"
#include "ITestManager.h"
#include "testManager.h"
#include "android_os_Parcel.h"
#include "binder/Parcel.h"

using namespace android;

typedef struct tarFIELD_S
{
    jfieldID    context;
    jmethodID   post_event;
} FIELDS_S;

FIELDS_S sFields;
static Mutex sLock;


sp<ITestManager> getTest(JNIEnv* env, jobject thiz)
{
    ALOGD("Test 222222222222222222222\n");
    Mutex::Autolock l(sLock);
    ITestManager* mTest = (ITestManager*)(env->GetLongField(thiz, sFields.context));
    return sp<ITestManager>(mTest);
}

static sp<ITestManager> setTest(JNIEnv* env, jobject thiz, const sp<ITestManager>& mTest)
{
    Mutex::Autolock l(sLock);
    ALOGD("Test 111111111111111111\n");
    sp<ITestManager> old = (ITestManager*)(env->GetLongField(thiz, sFields.context));
    if (mTest.get())
    {
        mTest->incStrong(thiz);
    }
    if (old != NULL)
    {
        old->decStrong(thiz);
    }

    env->SetLongField(thiz, sFields.context, (long)mTest.get());

    return old;
}

static void android_testJni_native_setup_test(JNIEnv* env, jobject thiz, jobject weak_this)
{
    ALOGD("Test INFO: android_testJni_native_setup_test enter!\n");
    sp<ITestManager> mTest = TestCreator::create();
    if (mTest == NULL)
    {
        jniThrowException(env, "java/lang/RuntimeException", "Out of memory");
        return;
    }

    setTest(env, thiz, mTest);
}

static void android_testJni_native_init_test(JNIEnv* env)
{
    ALOGD("Test INFO: android_testJni_native_init_test enter\n");

    jclass clazz;

    clazz = env->FindClass("com/jni/testJni");
    if (clazz == NULL)
    {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/jni/testJni");
        return;
    }

    sFields.context = env->GetFieldID(clazz, "mNativeContext", "J");
    if (sFields.context == NULL)
    {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find testJni.mNativeContext");
        return;
    }

}

/*
* Class:     com_test_android_getInfoFromServer
* Method:    getInfoFromServer
* Signature: ()I
*/
JNIEXPORT jstring JNICALL android_test_getInfoFromServer(JNIEnv* env, jobject thiz)
{
    sp<ITestManager> test = getTest(env, thiz);
    if (NULL == test.get())
    {
        jniThrowException(env, "java/lang/RuntimeException", "no test manager");
        return NULL;
    }
    char getStr[255] = "";
    test->getInfoFromServer(getStr);
    jstring rtstr = env->NewStringUTF(getStr);
    return rtstr;
}


static JNINativeMethod gMethods[] =
{
    {"native_init_test", "()V", (void*)android_testJni_native_init_test},
    {"native_setup_test", "(Ljava/lang/Object;)V", (void*)android_testJni_native_setup_test},

    {"getInfoFromServerNative", "()Ljava/lang/String;", (void*)android_test_getInfoFromServer},
};

// This function only registers the native methods
static int register_android_testJni(JNIEnv* env)
{
    return AndroidRuntime::registerNativeMethods(env, "com/jni/testJni", gMethods, NELEM(gMethods));
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;

    ALOGD("Test JNI_OnLoad");

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
    {
        ALOGE("Test ERROR: GetEnv failed\n");
        goto bail;
    }
    assert(env != NULL);

    if (register_android_testJni(env) < 0)
    {
        ALOGE("Test ERROR: Client native registration failed\n");
        goto bail;
    }
    ALOGD("Test INFO: Client native registration Ok\n");

    /* success -- return valid version number */
    result = JNI_VERSION_1_4;

bail:
    return result;
}

