#pragma once

#include "ShortcutManager.h"
#include "CheatFunctions.h"
#include "MainForm.h"
#include "Log.h"


void GodModeAction() {
	Dictionary<String^, Control^>^ controls = Timelapse::MainForm::ControlMap;
	CheckBox^ cb = (CheckBox^)controls["GodMode"];
	cb->Checked = !cb->Checked;
	toggleFullGodmode(cb);
	String^ state = cb->Checked ? "On" : "Off";
	Log::WriteLineToConsole(String::Format("DupeX was toggled {0}", state));
}

void RegisterGodMode() {
	ShortcutManager^ sm = ShortcutManager::Instance();
	sm->RegisterShortcut(VK_F1, gcnew ShortcutAction(GodModeAction));
}


void DupeXAction() {
	Dictionary<String^, Control^>^ controls = Timelapse::MainForm::ControlMap;
	CheckBox^ cbDupeX = (CheckBox^)controls["DupeX"];
	TextBox^ tbDupeXFoothold = (TextBox^)controls["DupexFoothold"];
	Button^ bDupeXGetFoothold = (Button^)controls["DupexGetFoothold"];

	BOOL isChecked = cbDupeX->Checked;
	cbDupeX->Checked = isChecked;
	cbDupeX->Checked = !cbDupeX->Checked;
	toggleDupeX();
	String^ state = cbDupeX->Checked ? "On" : "Off";
	Log::WriteLineToConsole(String::Format("DupeX was toggled {0}", state));
}

void RegisterDupeX() {
	ShortcutManager^ sm = ShortcutManager::Instance();
	sm->RegisterShortcut(VK_F1, gcnew ShortcutAction(DupeXAction));

}
//
void RegisterFMA() {
	Dictionary<String^, Control^>^ controls = Timelapse::MainForm::ControlMap;
	CheckBox^ cbFMA = (CheckBox^)controls["FMA"];
	BOOL isChecked = cbFMA->Checked;
	cbFMA->Checked = isChecked;
	cbFMA->Checked = !cbFMA->Checked;
	toggleFMA(cbFMA);
	String^ state = cbFMA->Checked ? "On" : "Off";
	Log::WriteLineToConsole(String::Format("FMA was toggled {0}", state));

}

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
	//RegisterGodMode();
	//RegisterDupeX();
	//RegisterMacros();
	RegisterGodMode();
	RegisterDupeX();
}


