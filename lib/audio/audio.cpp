#include <AL/al.h>
#include <AL/alc.h>
#include <cstdio>
#include "audio.h"

namespace Audio {

    void AudioManager::initAudio()
    {
        ALCdevice *device;
        
        device = alcOpenDevice(NULL);
        if (!device)
        {
            fprintf(stderr, "OpenAL Error: %s\n", "Error here");
            // handle errors
        }
    }
}