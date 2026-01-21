#include "audio/audio.h"

#include "core/log.h"

#include <iostream>

namespace Audio {
AudioManager::AudioManager() {
    initAudio();
    PianoCore::Log::Info("Finished Init Audio\n");
}

void AudioManager::initAudio() {
    ALCdevice *device;

    device = alcOpenDevice(NULL);
    if (!device) {
        PianoCore::Log::Error("OpenAL Error: %s\n", "Error here");
    }
}
}  // namespace Audio