#pragma once
#include "Settings.h"

class Utility : public Singleton<Utility>
{
public:
    static std::string ShowTime()
    {
        auto timeSingleton = RE::Calendar::GetSingleton();
        auto testTime      = timeSingleton->GetHour();
        auto testHour      = static_cast<int>(testTime);
        auto testMin       = static_cast<int>((testTime - testHour) * 60);
        std::string testTimestr = "it is " + std::to_string(testHour) + ":" + std::to_string(testMin);

        return testTimestr;
    };

    static void PrintTime()
    {
        RE::DebugNotification(ShowTime().c_str());
    }

};
