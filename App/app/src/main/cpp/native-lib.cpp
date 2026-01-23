#include <jni.h>
#include <string>
#include "shape_signature.h"
#include <android/bitmap.h>
#include <opencv2/opencv.hpp>
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_appandroid_NativeLib_classify(
        JNIEnv* env,
        jobject,
        jobject bitmap) {

    AndroidBitmapInfo info;
    void* pixels = nullptr;

    if (AndroidBitmap_getInfo(env, bitmap, &info) < 0) {
        return env->NewStringUTF("Error: info");
    }

    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        return env->NewStringUTF("Formato no soportado");
    }

    if (AndroidBitmap_lockPixels(env, bitmap, &pixels) < 0) {
        return env->NewStringUTF("Error: lock");
    }

    cv::Mat matRGBA(info.height, info.width, CV_8UC4, pixels);
    cv::Mat matBGR;
    cv::cvtColor(matRGBA, matBGR, cv::COLOR_RGBA2BGR);

    std::string result = clasificacionFigura(matBGR);

    AndroidBitmap_unlockPixels(env, bitmap);
    return env->NewStringUTF(result.c_str());
}
