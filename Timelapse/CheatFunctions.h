#pragma once
#include "Memory.h"
#include "Addresses.h"
#include "ShortcutManager.h"

using namespace Timelapse;

void toggleFullGodmode(System::Windows::Forms::CheckBox^ cb) {
	if (cb->Checked)
		WriteMemory(fullGodmodeAddr, 2, 0x0F, 0x84); // je 009596F7 [first 2 bytes]
	else
		WriteMemory(fullGodmodeAddr, 2, 0x0F, 0x85); // jne 009596F7 [first 2 bytes]
}

void toggleDupeX() {
	Dictionary<String^, Control^>^ controls = Timelapse::MainForm::ControlMap;
	CheckBox^ cbDupeX = (CheckBox^)controls["DupeX"];
	TextBox^ tbDupeXFoothold = (TextBox^)controls["DupexFoothold"];
	Button^ bDupeXGetFoothold = (Button^)controls["DupexGetFoothold"];

	if (cbDupeX->Checked)
	{
		tbDupeXFoothold->Enabled = false;
		bDupeXGetFoothold->Enabled = false;
		Jump(dupeXAddr, Assembly::DupeXHook, 1);
	}
	else
	{
		tbDupeXFoothold->Enabled = true;
		bDupeXGetFoothold->Enabled = true;
		WriteMemory(dupeXAddr, 6, 0x89, 0xBE, 0x14, 0x01, 0x00, 0x00);
	}
}

void toggleFMA(CheckBox^ cbFullMapAttack) {
	if (cbFullMapAttack->Checked)
		WriteMemory(fullMapAttackAddr, 2, 0x90, 0x90); // nop; nop;
	else
		WriteMemory(fullMapAttackAddr, 2, 0x74, 0x22); // je 006785EE
}


