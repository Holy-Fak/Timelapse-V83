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


//
//void RegisterFMA() {
//	Dictionary<String^, Control^>^ controls = Timelapse::MainForm::ControlMap;
//	CheckBox^ cbFMA = (CheckBox^)controls["FMA"];
//	BOOL isChecked = cbFMA->Checked;
//	cbFMA->Checked = isChecked;
//	cbFMA->Checked = !cbFMA->Checked;
//	toggleFMA(cbFMA);
//	String^ state = cbFMA->Checked ? "On" : "Off";
//	Log::WriteLineToConsole(String::Format("FMA was toggled {0}", state));
//
//}

//void RegisterMacros() {
//	ShortcutManager& sm = ShortcutManager::Instance();
//	sm.RegisterShortcut(VK_F2, [] {
//		CheckBox^ cbAttack = (CheckBox^)Timelapse::MainForm::ControlMap["AutoAttack"];
//		CheckBox^ cbLoot = (CheckBox^)Timelapse::MainForm::ControlMap["AutoLoot"];
//		BOOL isChecked = cbAttack->Checked || cbLoot->Checked;
//		cbAttack->Checked = isChecked;
//		cbLoot->Checked = isChecked;
//		cbAttack->Checked = !cbAttack->Checked;
//		cbLoot->Checked = !cbLoot->Checked;
//		});
//}


void RegisterShortcuts() {
	ShortcutManager^ sm = ShortcutManager::Instance();
	sm->RegisterShortcut(VK_F1, gcnew ShortcutAction(DupeXAction));
	sm->RegisterShortcut(VK_F2, gcnew ShortcutAction(addItemToFilter));

}


