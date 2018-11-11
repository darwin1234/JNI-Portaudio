#include <jni.h>        // JNI header provided by JDK
#include <stdio.h>      // C Standard IO Header
#include <math.h>
#include "AudioProcessor.h"   // Generated
#include "portaudio/portaudio.h"


#define SAMPLE_RATE         (44100)
#define PA_SAMPLE_TYPE      paFloat32
#define FRAMES_PER_BUFFER   (64)

/*****CONTROLS****/

double Cmin,Cmax;


typedef float SAMPLE;

float CubicAmplifier( float input );
static int AudioCallBack( const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData );

/* Non-linear amplifier with soft distortion curve. */
float CubicAmplifier( float input )
{
    float output, temp;
    if( input < 0.0 )
    {
        //temp = input + 1.0f;
        output = 0.0;
    }
    else
    {
        //temp = input - 1.0f;
	   
       output = input * Cmax;
    }

    return output;
}
#define ProcessAudio(x) CubicAmplifier(x)

static int gNumNoInputs = 0;





static int AudioCallBack( const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *userData )
{
    SAMPLE *out = (SAMPLE*)outputBuffer;
    const SAMPLE *in = (const SAMPLE*)inputBuffer;
    unsigned int i;
    (void) timeInfo; /* Prevent unused variable warnings. */
    (void) statusFlags;
    (void) userData;

    if( inputBuffer == NULL )
    {
        for( i=0; i<framesPerBuffer; i++ )
        {
            *out++ = 0;  /* left - silent */
            *out++ = 0;  /* right - silent */
        }
        gNumNoInputs += 1;
    }
    else
    {
        for( i=0; i<framesPerBuffer; i++ )
        {
            *out++ = ProcessAudio(*in++);  /* left - distorted */
            *out++ = ProcessAudio(*in++);          /* right - clean */
        }
    }
    
    return paContinue;
}


//i686-w64-mingw32-gcc -I "C:\Program Files\Java\jdk1.8.0_181\include" -I"C:\Program Files\Java\jdk1.8.0_181\include\win32" -shared -o AudioProcessor.dll AudioProcessor.c -I "portaudio" -L "lib/.libs"  -Wl,--add-stdcall-alias -lportaudio32bit
//x86_64-w64-mingw32-gcc -I "C:\Program Files\Java\jdk1.8.0_181\include" -I"C:\Program Files\Java\jdk1.8.0_181\include\win32" -shared -o AudioProcessor.dll AudioProcessor.c



JNIEXPORT void JNICALL Java_AudioProcessor_AudioStart(JNIEnv *env, jobject thisObj) {
	PaStreamParameters inputParameters, outputParameters;
    PaStream *stream;
    PaError err;

    err = Pa_Initialize();
    if( err != paNoError ) goto error;

    inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
    if (inputParameters.device == paNoDevice) {
      fprintf(stderr,"Error: No default input device.\n");
      goto error;
    }
    inputParameters.channelCount = 2;       /* stereo input */
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (outputParameters.device == paNoDevice) {
      fprintf(stderr,"Error: No default output device.\n");
      goto error;
    }
    outputParameters.channelCount = 2;       /* stereo output */
    outputParameters.sampleFormat = PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(
              &stream,
              &inputParameters,
              &outputParameters,
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              0, /* paClipOff, */  /* we won't output out of range samples so don't bother clipping them */
              AudioCallBack,
              NULL );
    if( err != paNoError ) goto error;

    err = Pa_StartStream( stream );
    if( err != paNoError ) goto error;

    printf("Hit ENTER to stop program.\n");
    getchar();
    err = Pa_CloseStream( stream );
    if( err != paNoError ) goto error;

    printf("Finished. gNumNoInputs = %d\n", gNumNoInputs );
    Pa_Terminate();
    return;

error:
    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    return;
	
    
  
   return;
}
JNIEXPORT void JNICALL Java_AudioProcessor_Volume (JNIEnv* env, jobject this_obj, jdouble min, jdouble max){
	Cmin = min;
	Cmax = max;
	
	printf("%f MIN: ", min);
	printf("\n");
	printf("%f MAX: ", max);
	return;
} 