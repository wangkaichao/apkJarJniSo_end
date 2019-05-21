LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE:= libtestJniNative
LOCAL_MODULE_TAGS := optional
LOCAL_MULTILIB := both
LOCAL_SRC_FILES:=android_testJni_test.cpp

LOCAL_SHARED_LIBRARIES := \
    libandroid_runtime \
    libnativehelper \
    libutils \
    libcutils \
    libbinder \
    libtestclient \
    libgui \
    liblog
	
LOCAL_C_INCLUDES := \
    $(TOP)/$(TVOS_TOPDIR)/frameworks/base/core/jni \
    $(PV_INCLUDES) \
    $(JNI_H_INCLUDE) \
    $(LOCAL_PATH)/../libtestservice \
    $(TOP)/$(TVOS_TOPDIR)/system/core/include/utils

ifeq (1,$(strip $(shell expr $(PLATFORM_VERSION) \< 6.0)))
LOCAL_SHARED_LIBRARIES += \
    libstlport 
    
include $(TOP)/$(TVOS_TOPDIR)/external/stlport/libstlport.mk
endif
	
include $(BUILD_SHARED_LIBRARY)