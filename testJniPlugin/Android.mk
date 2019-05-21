LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES := $(call all-subdir-java-files)
LOCAL_MODULE := testJni
LOCAL_JAVA_LIBRARIES := framework core-libart ext
LOCAL_PROGUARD_ENABLED := disabled
LOCAL_MODULE_TAGS := optional
include $(BUILD_JAVA_LIBRARY)