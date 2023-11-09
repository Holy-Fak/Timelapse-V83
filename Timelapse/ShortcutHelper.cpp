#include "ShortcutHelper.h"
#include "ShortcutManager.h"
#include "MainForm.h"
#include "Log.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

public delegate void ToggleAndLogDelegate(CheckBox^ cb);

void ToggleAndLog(CheckBox^ cb) {
	ShortcutHelper::ManualToggleCheckBox(cb);
	String^ state = cb->Checked ? "on" : "off";
	Log::WriteLineToConsole(String::Format("{0} was toggled {1}", cb->Name, state));
}

void ShortcutHelper::ManualToggleCheckBox(CheckBox^ cb) {
	cb->Checked = !cb->Checked;
}

void ShortcutHelper::ToggleControl(String^ controlName, Action^ additionalAction) {
	auto controls = Timelapse::MainForm::ControlMap;
	CheckBox^ cb = (CheckBox^)controls[controlName];
	cb->Invoke(gcnew ToggleAndLogDelegate(ToggleAndLog), cb);
	additionalAction();
}
