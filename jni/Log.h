/*
 * Port_droid.h
 *
 *  Created on: 2013-12-5
 *      Author: dell
 */

#ifndef LOG_H_____
#define LOG_H_____

#include <android/log.h>

#define LOGD(TAG, ...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)


#endif /* PORT_DROID_H_ */
