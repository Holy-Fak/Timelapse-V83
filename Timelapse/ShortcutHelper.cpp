#include "ShortcutHelper.h"
#include "ShortcutManager.h"
#include "MainForm.h"
#include "Log.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;


void ToggleAndLog(String^ controlName) {
	Dictionary<String^, Control^>^ controls = Timelapse::MainForm::ControlMap;
	CheckBox^ cb = (CheckBox^)controls[controlName];
	cb->Checked = !cb->Checked;
	String^ state = cb->Checked ? "on" : "off";
	Log::WriteLineToConsole(String::Format("{0} was toggled {1}", controlName, state));
}

void ShortcutHelper::ToggleControl(String^ controlName, Action^ additionalAction) {
	ToggleAndLog(controlName);
	additionalAction();
}
