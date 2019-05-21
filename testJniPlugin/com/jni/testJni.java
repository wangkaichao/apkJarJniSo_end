package com.jni;

import java.lang.ref.WeakReference;

import android.util.Log;

public class testJni{
    private static native final void native_init_test();

    private native final void native_setup_test(Object dtv_this);

    private native final String getInfoFromServerNative();

    public static testJni TestJni = null;

    //private TestManager mTestManager;

    public static final String TAG = "testJni";

    public long mNativeContext;

    public static synchronized testJni getInstance() {
        Log.d(TAG, "Test will new testJni");
    if((TestJni == null)) {
            TestJni = new testJni();
        }

        return TestJni;
    }

    static {
        Log.i(TAG, "Test 1111 loadLibrary");
        System.loadLibrary("testJniNative");
        Log.i(TAG, "Test 22222222 loadLibrary");
        native_init_test();
    }

    private testJni(){

        Log.i(TAG, "Test  new testJni success");
        native_setup_test(new WeakReference<testJni>(this));
        Log.i(TAG, "Test  mNativeContext:" + mNativeContext);

    }

    public long getNativeContext() {
        return mNativeContext;
    }

    public String getInfoFromServer()
    {
        return getInfoFromServerNative();
    }

}
