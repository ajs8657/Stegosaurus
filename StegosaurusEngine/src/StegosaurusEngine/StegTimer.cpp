#include <stegosaurus_pch.h>

#include "StegTimer.h"

#include <iostream>

namespace Steg {

    std::array<std::chrono::steady_clock::time_point, StegTimer::TimerLabel::TOTAL + 1> StegTimer::timers;

    std::array<std::chrono::milliseconds, StegTimer::TimerLabel::TOTAL + 1> StegTimer::elapsed;

    void StegTimer::StartTimer(TimerLabel timer) {
        timers[timer] = std::chrono::steady_clock::now();
    }

    void StegTimer::EndTimer(TimerLabel timer) {
        auto now = std::chrono::steady_clock::now();
        elapsed[timer] = std::chrono::duration_cast<std::chrono::milliseconds>(now - timers[timer]);
    }

    void StegTimer::PrintTimers() {
        for (int i = 0; i <= TimerLabel::TOTAL; i++) {
            auto timer = static_cast<TimerLabel>(i);
            auto durationMillis = elapsed.at(i).count();
            if (durationMillis != 0) {
                std::cout << GetTimerName(timer) << ": " << durationMillis << "ms" << std::endl;
            }
        }
    }

    std::string StegTimer::GetTimerName(TimerLabel timer) {
        switch (timer) {
        case ENCODE:
            return "Encode";
        case ENCRYPT:
            return "Encrypt";
        case DECODE:
            return "Decode";
        case DECRYPT:
            return "Decrypt";
        case TOTAL:
            return "Total";
        default:
            return "Unknown Timer";
        }
    }

}
