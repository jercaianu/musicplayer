#include <string>
#include "FileWvIn.h"
#include "RtAudio.h"
#include "audioplayer.h"
#include "delayeffect.h"
#include "phasereffect.h"
#include "flangereffect.h"

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

AudioPlayer* AudioPlayer::instance = nullptr;

AudioPlayer::AudioPlayer() : finishSem(0)
{
    dac = new RtAudio(RtAudio::MACOSX_CORE);
    done = false;
    isOpen = false;
    format = (sizeof(StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    ind = 0;
    currentEffect = 0;
}

int AudioPlayer::tick( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
        double streamTime, RtAudioStreamStatus status, void *userData )
{
    //cout << "inside tick" << endl;
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
    if (currentEffect & 8)
        inst()->flangerEffect.applyEffect(samplesOut, ind, ind + frames.size());

    for (int i= 0; i < frames.size(); i++) {
        samples[i] = samplesOut[ind + i];
    }
    samples += frames.size();
    ind += frames.size();
    
    /*
    if (inst()->done) {
        inst()->done = false;
        inst()->closeStream();
        return 1;
    }

    if ( input->isFinished() ) {
        return 1;
    }
    else
        return 0;
        */
}

static bool isPlaying = false;

void AudioPlayer::loadSong(string filename)
{
    initInput.openFile(filename);
    rate = initInput.getFileRate() / Stk::sampleRate();
    initInput.setRate(rate);
    initInput.ignoreSampleRateChange();
    channels = initInput.channelsOut();
    //samplesIn.clear();
    //samplesOut.clear();

    cout << "Prepared input" << endl;

    /*if (isOpen) {
        done = true;
        cout << "Waiting to acquire semaphore" << endl;
        if (!isPlaying) {
            closeStream();
        } else {
            finishSem.acquire();
        }
        cout << "Acquired semaphore" << endl;
        dac = new RtAudio(RtAudio::MACOSX_CORE);
    }*/
    cout << "Preparing to open stream" << endl;
    openStream();
    isPlaying = false;
    isOpen = true;
}

void AudioPlayer::openStream() 
{
    bufferFrames = RT_BUFFER_SIZE;
    if (!isOpen) {
        frames = StkFrames();
        frames.resize(bufferFrames, channels);
    }
    input = initInput;
    parameters.deviceId = dac->getDefaultOutputDevice();
    parameters.nChannels = (channels == 1) ? 2 : channels;
    if (isOpen) {
        closeStream();
        Stk::sleep(100);
        cout << "Stream successfully closed" << endl;
    }
    dac->openStream(&parameters, NULL, format, 
         (unsigned int)Stk::sampleRate(), &bufferFrames, &AudioPlayer::tick, (void *)&input);
    cout << "Opened stream" << endl;
}

void AudioPlayer::setSampleRate(StkFloat sampleRate)
{
    AudioPlayer::getInstance()->sampleRate = sampleRate;
    Stk::setSampleRate(sampleRate);
}

void AudioPlayer::play()
{ 
    if (!isOpen) {
        cout << "Open a file" << endl;
        return ;
    }
    isPlaying = true;
    dac->startStream();
    cout << "Play" << endl;
}

void AudioPlayer::stop()
{
    if (!isOpen)
        return ;
    dac->stopStream(); 
    cout << "Pause" << endl;
    isPlaying = false;
}

void AudioPlayer::setupDelayEffect(QSlider* delayDecay, QSlider* delayTimeDelay)
{
    delayEffect.delayDecay = delayDecay;
    delayEffect.delayTimeDelay = delayTimeDelay;
}

void AudioPlayer::setupPhaserEffect(
    QSlider* phaserStages, QSlider* phaserFeedback, QSlider* phaserLFO, 
    QSlider* phaserRange, QSlider* phaserDepth)
{
    phaserEffect.phaserStages = phaserStages;
    phaserEffect.phaserFeedback = phaserFeedback;
    phaserEffect.phaserLFO = phaserLFO;
    phaserEffect.phaserRange = phaserRange;
    phaserEffect.phaserDepth = phaserDepth;
}

void AudioPlayer::setupFlangerEffect(
    QSlider* flangerDelay, 
    QSlider* flangerPeriod, 
    QSlider* flangerDepth)
{
    flangerEffect.flangerDelay = flangerDelay;
    flangerEffect.flangerPeriod = flangerPeriod;
    flangerEffect.flangerDepth = flangerDepth;
}

void AudioPlayer::closeStream() 
{
    cout << "closing stream" << endl;
    dac->closeStream();
    isPlaying = false;
    //delete dac;
    //finishSem.release();
}
