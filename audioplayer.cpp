#include <string>
#include "FileWvIn.h"
#include "RtAudio.h"
#include "audioplayer.h"

#include <vector>
#include <signal.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;
using namespace stk;

int delayMilliseconds = 500;
int delaySamples = delayMilliseconds * 44.1; 
float decayCoef = 0.2f;
bool done = false;

AudioPlayer* AudioPlayer::instance = nullptr;

AudioPlayer::AudioPlayer() 
{
    format = (sizeof(StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    ind = 0;
}

int AudioPlayer::tick( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
        double streamTime, RtAudioStreamStatus status, void *userData )
{
    FileWvIn *input = (FileWvIn *) userData;
    register StkFloat *samples = (StkFloat *) outputBuffer;

    auto inst = AudioPlayer::getInstance;
    auto& frames = inst()->frames;
    auto& samplesIn = inst()->samplesIn;
    auto& samplesOut = inst()->samplesOut;
    auto& ind = inst()->ind;
    auto& done = inst()->done;

    input->tick( frames );

    for (int i = 0; i < frames.size(); i++) {
        samplesIn.push_back(frames[i]);
        samplesOut.push_back(frames[i]);
    }

    for ( unsigned int i=0; i<frames.size(); i++ ) {
        if (ind + i >= delaySamples)
            samplesOut[ind + i] += decayCoef * samplesOut[ind + i - delaySamples]; 
    }

    for (int i= 0; i < frames.size(); i++) {
        samples[i] = samplesOut[ind + i];
    }
    samples += frames.size();
    ind += frames.size();

    if ( input->isFinished() ) {
        done = true;
        return 1;
    }
    else
        return 0;
}

void AudioPlayer::loadSong(string filename)
{
    input.openFile(filename);
    rate = input.getFileRate() / Stk::sampleRate();
    input.setRate(rate);
    input.ignoreSampleRateChange();
    channels = input.channelsOut();

    // Figure out how many bytes in an StkFloat and setup the RtAudio stream.
}

void AudioPlayer::openStream() 
{
    bufferFrames = RT_BUFFER_SIZE;
    frames = StkFrames();
    frames.resize(bufferFrames, channels);
    samplesIn.clear();
    samplesOut.clear();
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = (channels == 1) ? 2 : channels; //  Play mono files as stereo.
    
    
    dac.openStream(&parameters, NULL, format, 
        (unsigned int)Stk::sampleRate(), &bufferFrames, &AudioPlayer::tick, (void *)&input);
}

void AudioPlayer::setSampleRate(StkFloat sampleRate)
{
    AudioPlayer::getInstance()->sampleRate = sampleRate;
    Stk::setSampleRate(sampleRate);
}

void AudioPlayer::play()
{
    openStream();
    dac.startStream();
}

void AudioPlayer::stop()
{
    dac.closeStream();
    dac = RtAudio();
}
