package com.example.appandroid


import android.graphics.Bitmap

object NativeLib {

    init {
        System.loadLibrary("native-lib")
    }

    external fun classify(bitmap: Bitmap): String
}
