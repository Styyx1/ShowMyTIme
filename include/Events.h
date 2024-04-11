#pragma once

namespace Events
{
    class InputSink : public RE::BSTEventSink<RE::InputEvent*>
    {
        InputSink()                              = default;
        InputSink(const InputSink&)              = delete;
        InputSink(InputSink&&)                   = delete;
        InputSink&  operator=(const InputSink&)  = delete;
        InputSink& operator=(InputSink&&)        = delete;

        static InputSink* GetSingleton()
        {
            static InputSink singleton;
            return &singleton;
        }
    
    public:
        RE::BSEventNotifyControl ProcessEvent(RE::InputEvent* const* eventPtr, RE::BSTEventSource<RE::InputEvent*>*);

        static void Register()
        {
            RE::BSInputDeviceManager::GetSingleton()->AddEventSink(InputSink::GetSingleton());
            logger::info("Registered Input Event");
        }
    };
} // namespace Events
