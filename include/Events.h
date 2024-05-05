#pragma once
#include "Settings.h"
#include "Utility.h"
#include <Xinput.h>

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

            for (RE::InputEvent* evnt = *eventPtr; evnt; evnt = evnt->next) {
                switch (evnt->eventType.get()) {
                case RE::INPUT_EVENT_TYPE::kButton:
                    Settings*        settings = Settings::GetSingleton();
                    RE::ButtonEvent* a_event  = evnt->AsButtonEvent();
                    uint32_t         mask     = a_event->idCode;
                    uint32_t         key_code;

                    if (a_event->GetDevice() == RE::INPUT_DEVICE::kMouse) {
                        key_code = SKSE::InputMap::kMacro_NumKeyboardKeys + mask;
                    }

                    else if (a_event->GetDevice() == RE::INPUT_DEVICE::kGamepad) {
                        key_code = SKSE::InputMap::GamepadMaskToKeycode(mask);
                    }

                    else
                        key_code = mask;

                    if (key_code >= SKSE::InputMap::kMaxMacros)
                        continue;

                    if (key_code == settings->setKey) {
                        Utility::PrintTime();
                    }
                }
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
