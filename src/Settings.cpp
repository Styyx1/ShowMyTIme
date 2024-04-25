#include "Settings.h"
#include <ClibUtil/simpleINI.hpp>

void Settings::LoadSettings() noexcept
{
    logger::info("Loading settings");

    CSimpleIniA ini;

    ini.SetUnicode();
    ini.LoadFile(R"(.\Data\SKSE\Plugins\ShowMyTime.ini)");

    setKey  = std::stoi(ini.GetValue("General", "iKeycode", "210"));
    msgTime = ini.GetValue("General", "msgTime", "It is");

    debug_logging = ini.GetBoolValue("Log", "Debug");

    if (debug_logging) {
        spdlog::get("Global")->set_level(spdlog::level::level_enum::debug);
        logger::debug("Debug logging enabled");
    }

    // Load settings

    logger::info("Loaded settings");
}
