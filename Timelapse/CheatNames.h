#pragma once

using namespace System;

enum class ControlNames {
	DupeX,
	GodMode,
	FMA,
};

String^ EnumToString(ControlNames controlName) {
	switch (controlName) {
	case ControlNames::DupeX:
		return "DupeX";
	case ControlNames::GodMode:
		return "GodMode";
	case ControlNames::FMA:
		return "FMA";
	default:
		return nullptr;
	}
}