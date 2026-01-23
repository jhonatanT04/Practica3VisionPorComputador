cmake_minimum_required(VERSION 3.22.1)
project("appandroid")

set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/sdk/native/jni")
find_package(OpenCV REQUIRED)

# Definimos el nombre de la librería como "native-lib" para que coincida con Kotlin
add_library(native-lib SHARED
        native-lib.cpp
        shape_signature.cpp
)

target_include_directories(native-lib PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(native-lib
        ${OpenCV_LIBS}
        android
        jnigraphics
        log)