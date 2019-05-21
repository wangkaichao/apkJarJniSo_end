LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES:= \
    ITestService.cpp \
    ITestClient.cpp \
    TestClient.cpp \
	testManager.cpp \

LOCAL_CFLAGS := \
    -D_STLP_USE_NEWALLOC
	
SKY_dot:=.
SKY_SDKVER:= $(subst $(SKY_dot), ,$(PLATFORM_VERSION))
SKY_SDKVER_JUDGE1:= $(word 1,$(SKY_SDKVER))
SKY_SDKVER_JUDGE2:= $(word 2,$(SKY_SDKVER))
SKY_SDKVER_JUDGE:= $(join  $(SKY_SDKVER_JUDGE1),$(SKY_SDKVER_JUDGE2))
LOCAL_CFLAGS := -DSKY_PLATFORM_VERSION=$(SKY_SDKVER_JUDGE)
$(warning ###############SKY_SDKVER=$(SKY_SDKVER_JUDGE))
$(warning PLATFORM_VERSION=$(PLATFORM_VERSION))
ifeq (1,$(strip $(shell expr $(PLATFORM_VERSION) \>= 6.0)))
$(warning define SKY_BOARD_SDK_VERSION=23)
LOCAL_CFLAGS += -DSKY_BOARD_SDK_VERSION=23
endif

ifeq (1,$(strip $(shell expr $(PLATFORM_VERSION) \< 6.0)))
LOCAL_C_INCLUDES := \
    $(TOP)/$(TVOS_TOPDIR)/prebuilts/ndk/current/sources/cxx-stl/stlport/stlport/

LOCAL_C_INCLUDES +=\
    $(TOP)/$(TVOS_TOPDIR)/system/core/include/utils/ \
    $(TOP)/$(TVOS_TOPDIR)/external/skia/include/core \
    $(LOCAL_PATH)/../middleware/include/ \
    $(LOCAL_PATH)/../../skycommon/include/ \
    $(LOCAL_PATH)/../middleware/setting/dtvmiddle/inc
	
LOCAL_SHARED_LIBRARIES := \
    libstlport
endif

LOCAL_SHARED_LIBRARIES += \
    libbinder \
    libutils \
    libcutils \
    libandroid_runtime \
    libdl \
    libgui \
    liblog

LOCAL_MODULE:= libtestclient
LOCAL_32_BIT_ONLY    := true
LOCAL_MULTILIB := both
modules_to_install_db += libtestclient
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES:= \
    TestService.cpp   

LOCAL_CFLAGS := \
    -D_STLP_USE_NEWALLOC

LOCAL_C_INCLUDES :=\
    $(TOP)/$(TVOS_TOPDIR)/system/core/include/utils/ \
    $(TOP)/$(TVOS_TOPDIR)/external/skia/include/core \

LOCAL_SHARED_LIBRARIES := \
    libbinder \
    libutils \
    libcutils \
    libandroid_runtime \
    libdl \
    libtestclient \
    libgui \
    liblog

ifeq (1,$(strip $(shell expr $(PLATFORM_VERSION) \< 6.0)))
LOCAL_C_INCLUDES +=\
    $(TOP)/$(TVOS_TOPDIR)/prebuilts/ndk/current/sources/cxx-stl/stlport/stlport/ 
    
LOCAL_SHARED_LIBRARIES += \
    libstlport
    
endif
LOCAL_CFLAGS += $(CONFIG_CFLAG)
LOCAL_MODULE:= libtestservice
LOCAL_32_BIT_ONLY    := true
modules_to_install_db += libtestservice
include $(BUILD_SHARED_LIBRARY)
