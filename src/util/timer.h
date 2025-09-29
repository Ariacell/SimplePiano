#pragma once

#include <chrono>
#include <iostream>

namespace Util {
class Timer {
private:
    using clock = std::chrono::steady_clock;
    using time_point = clock::time_point;
    using duration = std::chrono::duration<float>;

    time_point startTime;
    time_point timeAtLastTick;

    float accumulatedTime = 0.0f;
    float tickSizeMs;
    long timerTicks = 0;

public:
    Timer(float targetTicksPerSecond = 60.0f) {
        tickSizeMs = (1.0f / targetTicksPerSecond) * 1000.0f;
    }

    void Init(long startTick = 0) {
        startTime = timeAtLastTick = clock::now();
        timerTicks = startTick;
    }

    float GetTotalElapsedTime() {
        auto current_time = clock::now();
        return std::chrono::duration_cast<duration>(current_time - startTime)
            .count();
    }

    void Update() {
        time_point currentTime = clock::now();
        float deltaTime =
            std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - timeAtLastTick)
                .count();
        timeAtLastTick = currentTime;

        accumulatedTime += deltaTime;
    }

    void TickTimer(std::function<void()> tickCallback, int maxTicks) {
        int _tickCount = 0;
        while (accumulatedTime >= tickSizeMs && _tickCount < maxTicks) {
            tickCallback();
            accumulatedTime -= tickSizeMs;
            _tickCount++;
            timerTicks++;
        }
    }

    float GetElapsedTimeSinceLastTick() {
        auto current_time = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<duration>(current_time -
                                                    timeAtLastTick)
            .count();
        ;
    }

    float GetTickSizeSeconds() {
        return tickSizeMs / 1000.0f;
    }

    long GetTickCount() {
        return timerTicks;
    }
};
}  // namespace Util