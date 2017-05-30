#include <jni.h>
#include <string>

extern "C"
{

int fibonnaci (int n) {
    if (n<=1) return 1;
    return (fibonnaci(n-1))+(fibonnaci(n-2));
}

JNIEXPORT jstring JNICALL
Java_fr_nicolasfonsat_hellotestndk_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT jint JNICALL
Java_fr_nicolasfonsat_hellotestndk_MainActivity_fibonnaciC(JNIEnv *env, jobject, jint n) {
    return fibonnaci(n);
}

JNIEXPORT void JNICALL
Java_fr_nicolasfonsat_hellotestndk_MainActivity_fibonnaciCallback(JNIEnv *env, jobject obj, jint n) {
    jclass clazz = env->FindClass("fr/nicolasfonsat/hellotestndk/MainActivity");
    jmethodID method = env->GetMethodID(clazz, "fibonnaciCallbackC", "(I)V");
    env->CallVoidMethod(obj, method, n);
    return;
}

}