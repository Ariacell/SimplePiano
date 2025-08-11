#include "audio.h"

#include <AL/al.h>
#include <AL/alc.h>

#include <cstdio>

namespace Audio {

void AudioManager::initAudio() {
    ALCdevice *device;

    device = alcOpenDevice(NULL);
    if (!device) {
        fprintf(stderr, "OpenAL Error: %s\n", "Error here");
    }
}
}  // namespace Audio