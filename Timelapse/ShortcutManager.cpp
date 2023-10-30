#include "ShortcutManager.h"

ShortcutManager::ShortcutManager()
{
    shortcuts = gcnew Dictionary<int, List<ShortcutAction^>^>();
}

ShortcutManager^ ShortcutManager::Instance()
{
    if (instance == nullptr)
    {
        instance = gcnew ShortcutManager();
    }
    return instance;
}

void ShortcutManager::RegisterShortcut(int key, ShortcutAction^ action)
{
    if (!shortcuts->ContainsKey(key))
    {
        shortcuts[key] = gcnew List<ShortcutAction^>();
    }
    shortcuts[key]->Add(action);
}

void ShortcutManager::ExecuteShortcut(int key)
{
    List<ShortcutAction^>^ actions;
    if (shortcuts->TryGetValue(key, actions))
    {
        for each (ShortcutAction ^ action in actions)
        {
            action->Invoke();  // Execute each action
        }
    }
}



LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION && wParam == WM_KEYDOWN)
    {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
        int vkCode = p->vkCode;  // Directly use the virtual key code
        ShortcutManager::Instance()->ExecuteShortcut(vkCode);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

