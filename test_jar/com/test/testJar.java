package com.test;

import android.util.Log;
import com.jni.testJni;

public class testJar{
    public static final String TAG = "testJar";
    public testJni callJni = null;
    public  String retValue = "call jar success";
    public String test(){
        Log.d(TAG,"Test the application call jar");
       //callJni = testJni.getInstance();
        //if(callJni == null)
        //    return "new testJni flase";
        //        else
          // retValue = callJni.getInfoFromServer();
        return retValue;
    }
}
