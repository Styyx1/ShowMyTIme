#pragma once

class Settings : public Singleton<Settings>
{
public:
    static void LoadSettings() noexcept;

    uint32_t         setKey = 210;

    inline static bool debug_logging{};

};
