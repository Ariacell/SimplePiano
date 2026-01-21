#pragma once

#include <AL/al.h>
#include <AL/alc.h>

namespace Audio {
class AudioManager {
public:
    AudioManager();

private:
    void initAudio();

    ALCdevice* device;
};

}  // namespace Audio