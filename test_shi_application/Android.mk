LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_STATIC_JAVA_LIBRARIES :=FactoryPluginSDK FactorySDK android-support-v4 zxing PluginSDK testJar testJni android-support-v7

LOCAL_DEX_PREOPT := false

LOCAL_PROGUARD_ENABLED := disabled

LOCAL_CERTIFICATE := platform

LOCAL_MULTILIB := 32

LOCAL_MODULE_TARGET_ARCH := arm 

LOCAL_JNI_SHARED_LIBRARIES := libtestJniNative

LOCAL_PACKAGE_NAME := test_shi_application

ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)

include $(BUILD_PACKAGE)

