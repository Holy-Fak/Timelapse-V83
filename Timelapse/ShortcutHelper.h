#pragma once

#pragma once
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

public ref class ShortcutHelper {
public:
    static void ToggleControl(String^ controlName, Action^ customAction, String^ logMessage);
};

