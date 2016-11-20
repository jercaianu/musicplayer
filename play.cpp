/******************************************/
/*
   Example program to play an N channel
   soundfile.

   This program will load WAV, SND, AIF, and
   MAT-file formatted files of various data
   types.  If the audio system does not support
   the number of channels or sample rate of
   the soundfile, the program will stop.

   By Gary P. Scavone, 2000 - 2004.
   */
/******************************************/

#include "FileWvIn.h"
#include "RtAudio.h"

#include "mainwindow.h"
#include "audioplayer.h"
#include <vector>
#include <signal.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    auto instance = AudioPlayer::getInstance;
    instance()->setSampleRate(44100);
    instance()->loadSong("/Users/ajercaianu/Fac/PS/proiect/ring.wav");
    window.show();
    // Minimal command-line checking.
    /*
    if ( argc < 3 || argc > 4 ) usage();

    // Set the global sample rate before creating class instances.
    Stk::setSampleRate( (StkFloat) atof( argv[2] ) );

    // Initialize our WvIn and RtAudio pointers.
    RtAudio dac;
    FileWvIn input;

    // Try to load the soundfile.
    try {
        input.openFile( argv[1] );
    }
    catch ( StkError & ) {
        exit( 1 );
    }

    // Set input read rate based on the default STK sample rate.
    double rate = 1.0;
    rate = input.getFileRate() / Stk::sampleRate();
    if ( argc == 4 ) rate *= atof( argv[3] );
    input.setRate( rate );

    input.ignoreSampleRateChange();

    // Find out how many channels we have.
    int channels = input.channelsOut();
    cout << "Number of channels: " << channels << endl;

    // Figure out how many bytes in an StkFloat and setup the RtAudio stream.
    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = ( channels == 1 ) ? 2 : channels; //  Play mono files as stereo.
    RtAudioFormat format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    unsigned int bufferFrames = RT_BUFFER_SIZE;
    try {
        dac.openStream( &parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)&input );
    }
    catch ( RtAudioError &error ) {
        error.printMessage();
        goto cleanup;
    }

    // Install an interrupt handler function.
    (void) signal(SIGINT, finish);

    // Resize the StkFrames object appropriately.
    frames.resize( bufferFrames, channels );

    try {
        dac.startStream();
    }
    catch ( RtAudioError &error ) {
        error.printMessage();
        goto cleanup;
    }

    // Block waiting until callback signals done.
    while ( !done )
        Stk::sleep( 100 );

    // By returning a non-zero value in the callback above, the stream
    // is automatically stopped.  But we should still close it.
    try {
        dac.closeStream();
    }
    catch ( RtAudioError &error ) {
        error.printMessage();
    }

cleanup:
*/
    return app.exec();
}
