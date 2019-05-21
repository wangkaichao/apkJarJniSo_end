LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= \
	test_server.cpp

LOCAL_SHARED_LIBRARIES := \
	libtestservice \
	libutils \
	libbinder 

LOCAL_MODULE_TAGS := optional

LOCAL_C_INCLUDES := \
		$(LOCAL_PATH)/../libtestservice \
		$(TOP)/$(TVOS_TOPDIR)/bionic/libc/include \
		$(TOP)/$(TVOS_TOPDIR)/system/core/include/utils
		
ifeq (1,$(strip $(shell expr $(PLATFORM_VERSION) \< 6.0)))
LOCAL_SHARED_LIBRARIES += \
	libstlport
 include $(TOP)/$(TVOS_TOPDIR)/external/stlport/libstlport.mk
endif
LOCAL_MODULE:= testserver
LOCAL_32_BIT_ONLY    := true

modules_to_install_db += testserver

include $(BUILD_EXECUTABLE)
