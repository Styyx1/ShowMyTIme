#pragma once
#include <Xinput.h>
#include "Settings.h"
#include "Utility.h"

namespace Events
{
    class InputSink : public RE::BSTEventSink<RE::InputEvent*>
    {
        InputSink()                            = default;
        InputSink(const InputSink&)            = delete;
        InputSink(InputSink&&)                 = delete;
        InputSink& operator=(const InputSink&) = delete;
        InputSink& operator=(InputSink&&)      = delete;

        static InputSink* GetSingleton()
        {
            static InputSink singleton;
            return &singleton;
        }

    public:
        RE::BSEventNotifyControl ProcessEvent(RE::InputEvent* const* eventPtr, RE::BSTEventSource<RE::InputEvent*>*)
        {
            if (!eventPtr)
                return RE::BSEventNotifyControl::kContinue;

            // Do stuff
            auto* event = *eventPtr;
            if (!event)
                return RE::BSEventNotifyControl::kContinue;

            for (RE::InputEvent* e = *eventPtr; e; e = e->next) {
                switch (e->eventType.get()) {
                case RE::INPUT_EVENT_TYPE::kButton:
                    auto             settings = Settings::GetSingleton();
                    RE::ButtonEvent* a_event  = e->AsButtonEvent();
                    uint32_t         keyMask  = a_event->idCode;
                    uint32_t         keyCode;

                    // Mouse
                    if (a_event->device.get() == RE::INPUT_DEVICE::kMouse) {
                        keyCode = SKSE::InputMap::kMacro_NumKeyboardKeys + keyMask;
                    }
                    // Gamepad
                    else if (a_event->device.get() == RE::INPUT_DEVICE::kGamepad) {
                        keyCode = SKSE::InputMap::GamepadMaskToKeycode(keyMask);
                    }
                    // Keyboard
                    else
                        keyCode = keyMask;

                    // Valid scancode?
                    if (keyCode >= SKSE::InputMap::kMaxMacros)
                        continue;

                    if (keyCode == settings->setKey) {
                        Utility::PrintTime();
                    }
                }
                return RE::BSEventNotifyControl::kContinue;
            }
            return RE::BSEventNotifyControl::kContinue;
        };

        static void Register()
        {
            RE::BSInputDeviceManager::GetSingleton()->AddEventSink(InputSink::GetSingleton());
            logger::info("Registered Input Event");
        }
    };

    

    
} // namespace Events
