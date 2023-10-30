#pragma once
#include <unordered_map>
#include <functional>
#include <windows.h>

using namespace System::Collections;
using namespace System::Collections::Generic;

public delegate void ShortcutAction();


public ref class ShortcutManager
{
private:
	static ShortcutManager^ instance;
	Dictionary<int, List<ShortcutAction^>^>^ shortcuts;

	ShortcutManager();
public:
	static ShortcutManager^ Instance();
	void RegisterShortcut(int key, ShortcutAction^ action);
	void ExecuteShortcut(int key);
};


LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
