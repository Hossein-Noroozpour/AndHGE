LOCAL_PATH := $(call my-dir)
#Beginning of LibPNG
include $(CLEAR_VARS)
LOCAL_MODULE    := libpng
LOCAL_SRC_FILES := ../../../../../Libraries/LibPNG/StaticLib/$(TARGET_ARCH_ABI)/libpng.a
include $(PREBUILT_STATIC_LIBRARY)
#End of LibPNG
include $(CLEAR_VARS)
LOCAL_STATIC_LIBRARIES += png
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../Libraries/LibPNG/Source
LOCAL_LDLIBS += -lGLESv2
LOCAL_LDLIBS += -lz
LOCAL_LDLIBS += -llog
LOCAL_LDLIBS += -landroid
LOCAL_CPPFLAGS  := -std=c++11
LOCAL_MODULE    := hge
LOCAL_SRC_FILES :=  hge-camera-unit.cpp \
					hge-chunk-stream.cpp \
					hge-director.cpp \
					hge-geometry-unit.cpp \
					hge-main-window.cpp \
					hge-main.cpp \
					hge-mesh-unit.cpp \
					hge-model-unit.cpp \
					hge-perspective-unit.cpp \
					hge-protocol.cpp \
					hge-resource-manager.cpp \
					hge-scene-unit.cpp \
					hge-serializable.cpp \
					hge-shader-engine.cpp \
					hge-shader-unit.cpp \
					hge-skybox-shader-unit.cpp \
					hge-skybox-unit.cpp \
					hge-stream.cpp \
					hge-sun-shader.cpp \
					hge-system-access.cpp \
					hge-terrain-sun-shader.cpp \
					hge-terrain-unit.cpp \
					hge-terrain-unlit-shader.cpp \
					hge-terrain-white-shader.cpp \
					hge-texture-unit.cpp \
					hge-unlit-shader.cpp \
					hge-white-shader.cpp
include $(BUILD_SHARED_LIBRARY)
