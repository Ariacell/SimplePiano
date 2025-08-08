#include <chrono>
#include <iostream>

namespace Util
{
    class Timer
    {
    private:
        std::chrono::time_point<std::chrono::steady_clock> startTime;
        std::chrono::time_point<std::chrono::steady_clock> timeAtLastTick;
        float tickSize;
        long timerTicks;

    public:
        void Init(float tickSize, long startTick = 0)
        {
            this->startTime = this->timeAtLastTick = std::chrono::steady_clock::now();
            this->tickSize = tickSize;
            this->timerTicks = startTick;
        }

        float GetTotalElapsedTime() {
            auto current_time = std::chrono::steady_clock::now();
            return std::chrono::duration_cast<std::chrono::duration<float>>(current_time - startTime).count();
        }

        void TickTimer() {
            auto durationToAdd = std::chrono::duration<float, std::milli>(tickSize);
            this->timeAtLastTick += std::chrono::duration_cast<std::chrono::steady_clock::duration>(durationToAdd);
            timerTicks++;
        }

        float GetElapsedTimeSinceLastTick() {
            auto current_time = std::chrono::steady_clock::now();
            auto timeSinceLastTick = std::chrono::duration_cast<std::chrono::duration<float>>(current_time - timeAtLastTick).count();
            return timeSinceLastTick;
        }

        float GetTickSize() {
            return tickSize;
        }

        long GetTickCount(){
            return timerTicks;
        }
    };
}