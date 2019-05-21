LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES += \
    libutils \
    libtestclient\
    libgui
LOCAL_MODULE := testClinet
LOCAL_C_INCLUDES +=$(LOCAL_PATH)/../libtestservice/
LOCAL_SRC_FILES := test.cpp
include $(BUILD_EXECUTABLE)
