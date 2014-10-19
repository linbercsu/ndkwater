#include <jni.h>
#include "com_utils_water_Water.h"
#include "CWaterRoutine.h"
#include <android/bitmap.h>
#include <pthread.h>
#include "Port_droid.h"
#include "log_android.h"

jobject g_src = NULL;
jobject g_tar = NULL;
uint32_t* g_src_data = NULL;
uint32_t* g_offscreen_data = NULL;
CWaterRoutine* water = NULL;
uint32_t g_size = 0;

JavaVM *g_jvm = NULL;
pthread_mutex_t mMutex;

void* thread_fun(void* d) {

	JNIEnv *env;

	if (g_jvm->AttachCurrentThread(&env, NULL) != JNI_OK) {
		return NULL;
	}
	while (true) {

		//pthread_mutex_lock(&mMutex);
		water->Render((DWORD*) g_src_data, (DWORD*) g_offscreen_data);
		water->Render((DWORD*) g_src_data, (DWORD*) g_offscreen_data);
//		water->Render((DWORD*) g_src_data, (DWORD*) g_offscreen_data);
		//pthread_mutex_unlock(&mMutex);


		 //flush
		 uint32_t* tar;
		 if (AndroidBitmap_lockPixels(env, g_tar, (void**)(&tar)) < 0) {
		 break;
		 }

		 memcpy((void*)tar, (const void*)g_offscreen_data, g_size);

		 if (AndroidBitmap_unlockPixels(env, g_tar) < 0){
		 break;
		 }


	}
	if (g_jvm->DetachCurrentThread() != JNI_OK) {
		return NULL;
	}

	LOGe("jni", "error");

}

void Java_com_utils_water_Water_flush(JNIEnv *env, jobject t) {
	uint32_t* tar;
	if (AndroidBitmap_lockPixels(env, g_tar, (void**) (&tar)) < 0) {
		return;
	}

	//pthread_mutex_lock(&mMutex);
	memcpy((void*) tar, (const void*) g_offscreen_data, g_size);
	//pthread_mutex_unlock(&mMutex);

	if (AndroidBitmap_unlockPixels(env, g_tar) < 0) {

	}

}

void Java_com_utils_water_Water_doHeightBlob(JNIEnv *env, jobject t, jint ptr,
		jint x, jint y, jint radius, jint height) {
	CWaterRoutine* water = (CWaterRoutine*) ptr;
	pthread_mutex_lock(&mMutex);
	water->HeightBlob(x, y, radius, height, water->m_iHpage);
	pthread_mutex_unlock(&mMutex);
}

/*
 * Class:     com_utils_water_Water
 * Method:    doFree
 * Signature: (I)V
 */
void Java_com_utils_water_Water_doFree(JNIEnv *env, jobject, jint ptr) {
	CWaterRoutine* water = (CWaterRoutine*) ptr;
	delete water;

	AndroidBitmap_unlockPixels(env, g_src);

	env->DeleteGlobalRef(g_src);
	env->DeleteGlobalRef(g_tar);

	delete[] g_offscreen_data;
}

/*
 * Class:     com_utils_water_Water
 * Method:    doStart
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;)I
 */
jint Java_com_utils_water_Water_doStart(JNIEnv *env, jobject t, jobject src,
		jobject tar) {

	AndroidBitmapInfo infocolor;
//	void* pixelscolor;
	AndroidBitmapInfo tarinfo;
	void* pixelstar;
	int ret = -1;

	if ((ret = AndroidBitmap_getInfo(env, src, &infocolor)) < 0) {
		return 0;
	}
	if ((ret = AndroidBitmap_getInfo(env, tar, &tarinfo)) < 0) {
		return 0;
	}

	if (infocolor.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
		return 0;
	}
	if (tarinfo.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
		return 0;
	}

	if ((ret = AndroidBitmap_lockPixels(env, src, (void**) (&g_src_data)))
			< 0) {
		return 0;
	}
	if ((ret = AndroidBitmap_lockPixels(env, tar, &pixelstar)) < 0) {
		return 0;
	}

	g_src = env->NewGlobalRef(src);
	g_tar = env->NewGlobalRef(tar);

	env->GetJavaVM(&g_jvm);

	g_offscreen_data = new uint32_t[tarinfo.height * tarinfo.width];
	g_size = tarinfo.height * tarinfo.width * sizeof(uint32_t);
	memcpy(g_offscreen_data, pixelstar, g_size);

//	 	water->Render((DWORD*)pixelscolor, (DWORD*)pixelsgray);

//	AndroidBitmap_unlockPixels(env, src);
	AndroidBitmap_unlockPixels(env, tar);

	water = new CWaterRoutine();
	water->Create(infocolor.width, infocolor.height);

	pthread_mutex_init(&mMutex, NULL);

	pthread_t thread;
	pthread_create(&thread, NULL, thread_fun, NULL);

	return (jint) water;

}

JNIEXPORT jint JNICALL Java_com_utils_water_Water_doCreate(JNIEnv *env, jobject,
		jint w, jint h) {

//	CheckCer(env);

	CWaterRoutine* ret = new CWaterRoutine();
	ret->Create(w, h);
	return (jint) ret;
}

