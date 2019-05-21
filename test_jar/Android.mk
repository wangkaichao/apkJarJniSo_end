LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES := $(call all-subdir-java-files)
LOCAL_MODULE := testJar
//LOCAL_JAVA_LIBRARIES := testJni
LOCAL_DEX_PREOPT := false
LOCAL_STATIC_JAVA_LIBRARIES := SkyFramework testJni
include $(BUILD_JAVA_LIBRARY)