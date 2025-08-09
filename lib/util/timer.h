#include <chrono>
#include <iostream>

namespace Util
{
    class Timer
    {
    private:
        using clock = std::chrono::steady_clock;
        using time_point = clock::time_point;
        using duration = std::chrono::duration<float>;

        time_point startTime;
        time_point timeAtLastTick;

        float accumulatedTime = 0.0f;
        float tickSize;
        long timerTicks = 0;

    public:
        void Init(float tickSizeMs, long startTick = 0)
        {
            startTime = timeAtLastTick = clock::now();
            tickSize = tickSizeMs / 1000.0f;
            timerTicks = startTick;
        }

        float GetTotalElapsedTime() {
            auto current_time = clock::now();
            return std::chrono::duration_cast<duration>(current_time - startTime).count();
        }


        void Update() {
            time_point currentTime = clock::now();
            float deltaTime = std::chrono::duration_cast<duration>(currentTime - timeAtLastTick).count();
            timeAtLastTick = currentTime;

            accumulatedTime += deltaTime;
        }

        void TickTimer(std::function<void()> tickCallback, int maxTicks) {
            int _tickCount = 0;
            while (accumulatedTime >= tickSize && _tickCount < maxTicks) {
                tickCallback();
                accumulatedTime -= tickSize;
                _tickCount++;
                timerTicks++;
            }
        }

        float GetElapsedTimeSinceLastTick() {
            auto current_time = std::chrono::steady_clock::now();
            auto timeSinceLastTick = std::chrono::duration_cast<std::chrono::duration<float>>(current_time - timeAtLastTick).count();
            return timeSinceLastTick;
        }

        float GetTickSize() {
            return tickSize;
        }

        long GetTickCount() {
            return timerTicks;
        }
    };
}