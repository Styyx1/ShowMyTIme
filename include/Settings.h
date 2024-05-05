#pragma once

class Settings : public Singleton<Settings>
{
public:
    static void LoadSettings() noexcept;

    inline static uint32_t    setKey;
    inline static std::string msgTime;

    inline static bool debug_logging{};
};
