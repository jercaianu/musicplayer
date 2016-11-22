#include <string>
#include "FileWvIn.h"
#include "RtAudio.h"
#include "audioplayer.h"
#include "delayeffect.h"
#include "phasereffect.h"

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
    //effect = new DelayEffect();
    format = (sizeof(StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    ind = 0;
    currentEffect = 0;
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
    auto& currentEffect = inst()->currentEffect;

    input->tick( frames );
    for (int i = 0; i < frames.size(); i++) {
        samplesIn.push_back(frames[i]);
        samplesOut.push_back(frames[i]);
    }

    if (currentEffect & 1)
        inst()->phaserEffect.applyEffect(samplesOut, ind, ind + frames.size());
    if (currentEffect & 2)
        inst()->delayEffect.applyEffect(samplesOut, ind, ind + frames.size());
    /*
    for ( unsigned int i=0; i<frames.size(); i++ ) {
        if (ind + i >= delaySamples)
            samplesOut[ind + i] += decayCoef * samplesOut[ind + i - delaySamples]; 
    }

    */

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
    initInput.openFile(filename);
    rate = initInput.getFileRate() / Stk::sampleRate();
    initInput.setRate(rate);
    initInput.ignoreSampleRateChange();
    channels = initInput.channelsOut();
    samplesIn.clear();
    samplesOut.clear();
    // Figure out how many bytes in an StkFloat and setup the RtAudio stream.
    openStream();
}

void AudioPlayer::openStream() 
{
    bufferFrames = RT_BUFFER_SIZE;
    frames = StkFrames();
    frames.resize(bufferFrames, channels);
    input = initInput;
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
    dac.startStream();
}

void AudioPlayer::stop()
{
    dac.stopStream();  
}
