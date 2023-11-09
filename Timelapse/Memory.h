#pragma once
#include <excpt.h>
#include <memoryapi.h>
#include <winbase.h>
#include <msclr/marshal_cppstd.h>

#define NewThread(threadFunc) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&threadFunc, NULL, NULL, NULL);

#pragma region General Functions
static bool MakePageWritable(ULONG_PTR ulAddress, SIZE_T ulSize) {
	MEMORY_BASIC_INFORMATION mbi;
	// Instead of allocating MEMORY_BASIC_INFORMATION on the heap, we use the stack

	// Securely initialize mbi with the result of VirtualQuery
	if (VirtualQuery(reinterpret_cast<LPCVOID>(ulAddress), &mbi, sizeof(mbi)) == 0) {
		// Handle error if VirtualQuery failed
		// Log with GetLastError() for diagnostics
		return false;
	}

	// Check if the current protection already allows for write access
	if (mbi.Protect & PAGE_EXECUTE_READWRITE) {
		return true; // No action needed
	}

	DWORD flOldProtect;
	// Use VirtualProtect to change the page protection, checking for success
	if (!VirtualProtect(reinterpret_cast<LPVOID>(ulAddress), ulSize, PAGE_EXECUTE_READWRITE, &flOldProtect)) {
		// Handle error if VirtualProtect failed
		// Log with GetLastError() for diagnostics
		return false;
	}

	return true; // Success
}

static void Jump(ULONG ulAddress, PVOID Function, unsigned Nops) {
	MakePageWritable(ulAddress, Nops + 5);
	*(UCHAR*)ulAddress = 0xE9;
	*(ULONG*)(ulAddress + 1) = (int)(((int)Function - (int)ulAddress) - 5);
	memset((PVOID)(ulAddress + 5), 0x90, Nops);
}


static void SetupReturnJump(ULONG returnAddress, ULONG originalAddress, unsigned Nops) {
	MakePageWritable(returnAddress, Nops + 5);
	*(UCHAR*)returnAddress = 0xE9; // Jump instruction
	*(ULONG*)(returnAddress + 1) = (int)((originalAddress - returnAddress) - 5); // Relative offset
	memset((PVOID)(returnAddress + 5), 0x90, Nops); // NOPs for padding
}

static ULONG ReadPointer(ULONG ulBase, int iOffset) {
	__try { return *(ULONG*)(*(ULONG*)ulBase + iOffset); }
	__except (EXCEPTION_EXECUTE_HANDLER) { return 0; }
}

static LONG ReadPointerSigned(ULONG ulBase, int iOffset) {
	__try { return *(LONG*)(*(ULONG*)ulBase + iOffset); }
	__except (EXCEPTION_EXECUTE_HANDLER) { return 0; }
}

static int ReadPointerSignedInt(ULONG ulBase, int iOffset) {
	ULONG* basePtr = (ULONG*)ulBase;

	if (basePtr == NULL || *basePtr == 0) {
		// Log or handle
		return 0;
	}

	LONG* valuePtr = (LONG*)(*basePtr + iOffset);

	if (valuePtr == NULL || *valuePtr == 0) {
		// Log or handle
		return 0;
	}

	return *valuePtr;
}

static double ReadPointerDouble(ULONG ulBase, int iOffset) {
	__try { return *(double*)(*(ULONG*)ulBase + iOffset); }
	__except (EXCEPTION_EXECUTE_HANDLER) { return NULL; }
}

static LPCSTR ReadPointerString(ULONG ulBase, int iOffset) {
	__try { return (LPCSTR)(*(ULONG*)ulBase + iOffset); }
	__except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
}

static UINT8 readCharValueZtlSecureFuse(int at) {
	// Check if the address is null
	if (at == 0) {
		return 0;
	}

	// Attempt to read UCHAR value from the address
	PUCHAR ptr1 = (PUCHAR)at;
	if (ptr1 == NULL || *ptr1 == 0) {
		return 0;
	}
	UCHAR v2 = *ptr1;

	// Move to the next address and attempt to read UCHAR value from there
	PUINT8 ptr2 = (PUINT8)(at + 1);
	if (ptr2 == NULL || *ptr2 == 0) {
		return 0;
	}
	at = *ptr2;

	// Return the XOR'ed value
	return at ^ v2;
}

static INT16 readShortValueZtlSecureFuse(int a1) {
	PUINT8 v2 = (PUINT8)(a1 + 2);

	if (*((PUINT8)(a1 + 2)) == 0) {
		return 0;
	}

	DWORD v4 = (DWORD)&a1 - a1;

	try {
		v2[v4] = *v2 ^ *(v2 - 2);
		v2++;
		v2[v4] = *v2 ^ *(v2 - 2);
	}
	catch (...) { return 0; }
	return HIWORD(a1);
}

inline unsigned int readLongValueZtlSecureFuse(ULONG* a1) {
	if (a1 == NULL || *a1 == 0) {
		return 0;
	}
	try {
		return *a1 ^ _rotl(a1[1], 5);
	}
	catch (...) { return 0; }
}

#pragma unmanaged
bool isValidReadPtr(void* ptr) {
	__try {
		// Attempt to read the pointer.
		volatile auto value = *static_cast<LONG_PTR*>(ptr);
		(void)value; // To avoid unused variable warning.
		return true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return false;
	}
}

static LONG_PTR ReadMultiPointerSigned(LONG_PTR ulBase, int level, ...) {
	LONG_PTR ulResult = 0;
	va_list vaarg;
	va_start(vaarg, level);

	__try {
		if (ulBase != 0 && isValidReadPtr(reinterpret_cast<void*>(ulBase))) {
			ulBase = *reinterpret_cast<LONG_PTR*>(ulBase);
			for (int i = 0; i < level; i++) {
				const int offset = va_arg(vaarg, int);
				if (ulBase == 0 || !isValidReadPtr(reinterpret_cast<void*>(ulBase + offset))) {
					throw std::runtime_error("Invalid memory access detected.");
				}
				ulBase = *reinterpret_cast<LONG_PTR*>(ulBase + offset);
			}
			ulResult = ulBase;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		ulResult = 0; // In case of an exception, set the result to 0 or some sentinel value.
	}

	va_end(vaarg);
	return ulResult;
}



static PCHAR ReadMultiPointerString(LONG_PTR ulBase, int level, ...) {
	PCHAR ulResult = nullptr;
	va_list vaarg;
	va_start(vaarg, level);

	if (!IsBadReadPtr((PVOID)ulBase, sizeof(LONG_PTR))) {
		ulBase = *(LONG_PTR*)ulBase;
		for (int i = 0; i < level; i++) {
			const int offset = va_arg(vaarg, int);
			if (IsBadReadPtr((PVOID)(ulBase + offset), sizeof(LONG_PTR))) {
				va_end(vaarg);
				return nullptr;
			}
			ulBase = *(LONG_PTR*)(ulBase + offset);
		}
		ulResult = (PCHAR)ulBase;
	}

	va_end(vaarg);
	return ulResult;
}

static void WriteMemory(ULONG ulAddress, ULONG ulAmount, ...) {
	va_list va;
	va_start(va, ulAmount);

	MakePageWritable(ulAddress, ulAmount);
	for (ULONG ulIndex = 0; ulIndex < ulAmount; ulIndex++)
		*(UCHAR*)(ulAddress + ulIndex) = va_arg(va, UCHAR);

	va_end(va);
}

#pragma managed
static bool WritePointer(ULONG ulBase, int iOffset, int iValue) {
	__try { *(int*)(*(ULONG*)ulBase + iOffset) = iValue; return true; }
	__except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}
#pragma endregion