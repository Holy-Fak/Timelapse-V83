#pragma once
#include "ShortcutManager.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

public ref class ShortcutHelper {
public:
	static void ToggleControl(String^ controlName, Action^ additionalAction);
};
	

