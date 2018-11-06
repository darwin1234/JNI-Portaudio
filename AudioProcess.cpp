// Save as "HelloJNI.c"
#include <jni.h>        // JNI header provided by JDK
#include <stdio.h>      // C Standard IO Header
#include "AudioProcessor.h"   // Generated
 
// Implementation of the native method sayHello()
JNIEXPORT void JNICALL Java_AudioProcessor_sinewave(JNIEnv *env, jobject thisObj) {
   printf("Hello World!\n");
   return;
} 