#include "com_example_ndk_MainActivity.h"

jstring Java_com_example_ndk_MainActivity_getStringFromJni
  (JNIEnv *env, jobject){
	return env->NewStringUTF("hello ndk.");
}
