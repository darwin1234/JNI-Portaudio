#include <jni.h>        // JNI header provided by JDK
#include <stdio.h>      // C Standard IO Header



//compile command
//

//i686-w64-mingw32-gcc -I "C:\Program Files\Java\jdk1.8.0_181\include" -I"C:\Program Files\Java\jdk1.8.0_181\include\win32" -shared -o AudioProcessor.dll AudioProcessor.cpp

// Implementation of the native method sayHello()
JNIEXPORT void JNICALL Java_AudioProcessor_sinewave(JNIEnv *env, jobject thisObj) {
 
	
   printf("Hello World! from C\n");
   return;
} 