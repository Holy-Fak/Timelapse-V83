#include "ShortcutHelper.h"
#include "MainForm.h"
#include "Log.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

void ShortcutHelper::ToggleControl(String^ controlName, Action^ customAction, String^ logMessage) {
    Dictionary<String^, Control^>^ controls = Timelapse::MainForm::ControlMap;
    Control^ ctrl = controls[controlName];
    if (CheckBox^ cb = dynamic_cast<CheckBox^>(ctrl)) {
        cb->Checked = !cb->Checked;
        customAction();
        String^ state = cb->Checked ? "On" : "Off";
        Log::WriteLineToConsole(String::Format(logMessage, state));
    }
}