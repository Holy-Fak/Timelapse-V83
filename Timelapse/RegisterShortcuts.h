#pragma once

#include "ShortcutManager.h"
#include "CheatFunctions.h"
#include "MainForm.h"
#include "ShortcutHelper.h"
#include "Log.h"
#include "CheatNames.h"


//void GodModeAction() {
//	Dictionary<String^, Control^>^ controls = Timelapse::MainForm::ControlMap;
//	CheckBox^ cb = (CheckBox^)controls["GodMode"];
//	cb->Checked = !cb->Checked;
//	toggleFullGodmode(cb);
//	String^ state = cb->Checked ? "On" : "Off";
//	Log::WriteLineToConsole(String::Format("DupeX was toggled {0}", state));
//}
//
//void RegisterGodMode() {
//	ShortcutManager^ sm = ShortcutManager::Instance();
//	sm->RegisterShortcut(VK_F1, gcnew ShortcutAction(GodModeAction));
//}


void DupeXAction() {
	ShortcutHelper::ToggleControl("DupeX", gcnew Action(toggleDupeX));
}

void FMAAction() {
	ShortcutHelper::ToggleControl("FMA", gcnew Action(toggleFMA));
}


void AutoAttackAction() {
	ShortcutHelper::ToggleControl("AutoAttack", gcnew Action(toggleAutoAttack));
}





void RegisterShortcuts() {
	ShortcutManager^ sm = ShortcutManager::Instance();
	sm->RegisterShortcut(VK_F1, gcnew ShortcutAction(DupeXAction));
	sm->RegisterShortcut(VK_F1, gcnew ShortcutAction(FMAAction));
	sm->RegisterShortcut(VK_F2, gcnew ShortcutAction(addItemToFilter));
	sm->RegisterShortcut(VK_F3, gcnew ShortcutAction(AutoAttackAction));

}


