#ifdef __ANDROID__
#include <jni.h>
#include <android/log.h>
#include <string>
#include "runtime.hpp"

#define LOG_TAG "SelauraClient"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern "C" {

JNIEXPORT void JNICALL
Java_com_selaura_client_MainActivity_initNative(JNIEnv* env, jobject thiz) {
    LOGI("Selaura Client v%s initializing on Android", RUNTIME_VERSION);
    LOGI("Branch: %s", GIT_BRANCH);
    LOGI("Native library loaded successfully");
    
    try {
        auto* ctx = new selaura::runtime_context{};
        selaura::runtime_instance = std::make_unique<selaura::runtime>(*ctx);
        selaura::runtime_instance->start();
        
        LOGI("Runtime initialized successfully");
        LOGI("Ready to hook into Minecraft Bedrock Edition");
        LOGI("Supports both paid and cracked MCPE versions");
    } catch (const std::exception& e) {
        LOGE("Failed to initialize runtime: %s", e.what());
    }
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    
    LOGI("Selaura Runtime JNI loaded");
    return JNI_VERSION_1_6;
}

}

#endif
