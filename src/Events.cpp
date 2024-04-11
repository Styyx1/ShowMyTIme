#include "Events.h"
#include "Settings.h"
#include "Utility.h"

namespace Events
{
    RE::BSEventNotifyControl InputSink::ProcessEvent(RE::InputEvent* const* eventPtr, RE::BSTEventSource<RE::InputEvent*>*)
    {
        if (!eventPtr)
            return RE::BSEventNotifyControl::kContinue;

        // Do stuff
        auto* event = *eventPtr;
        if (!event)
            return RE::BSEventNotifyControl::kContinue;

        if (event->GetEventType() == RE::INPUT_EVENT_TYPE::kButton) {
            auto* buttonEvent = event->AsButtonEvent();
            auto  dxScanCode  = buttonEvent->GetIDCode();
            auto  setting     = Settings::GetSingleton();
            if (dxScanCode == setting->setKey)
                Utility::PrintTime();
        }
        return RE::BSEventNotifyControl::kContinue;
    }

} // namespace Events
