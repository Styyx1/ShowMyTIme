#pragma once
#include "Settings.h"

class Utility : public Singleton<Utility>
{
public:
    static std::string ShowTime()
    {
        std::ostringstream ssHourOut;
        std::ostringstream ssMinOut;
        size_t       range         = 2;
        auto         settings      = Settings::GetSingleton();
        auto        timeSingleton = RE::Calendar::GetSingleton();
        float        testTime      = timeSingleton->GetHour();
        int          testHour      = static_cast<int>(testTime);
        int          testMin       = static_cast<int>((testTime - testHour) * 60);
        std::string  hourOut       = std::to_string(testHour);
        std::string  minOut        = std::to_string(testMin);

        ssHourOut << std::setw(range) << std::setfill('0') << hourOut;
        ssMinOut << std::setw(range) << std::setfill('0') << minOut;

        std::string timeHourOut = ssHourOut.str();
        std::string timeMinOut  = ssMinOut.str();

        std::string testTimestr = settings->msgTime + " " + timeHourOut + ":" + timeMinOut;

        return testTimestr;
    };

    static void PrintTime() { RE::DebugNotification(ShowTime().c_str()); }
};
