#pragma once

class Settings : public Singleton<Settings>
{
public:
    static void LoadSettings() noexcept;

    uint32_t    setKey  = 210;
    std::string msgTime = "It is";

    inline static bool debug_logging{};
};
