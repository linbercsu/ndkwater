# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

LOCAL_C_INCLUDE := $(JNI_H_INCLUDE)

include $(CLEAR_VARS)
LOCAL_LDLIBS    := -ljnigraphics -llog -L$(NDK_PLATFORMS_ROOT)/$(TARGET_PLATFORM)/arch-arm/usr/lib -L$(LOCAL_PATH)
LOCAL_MODULE    := utilswater

LOCAL_SRC_FILES := jni_call.cpp CWaterRoutine.cpp

include $(BUILD_SHARED_LIBRARY)

