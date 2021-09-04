#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include "offsets.h"
#include "vars.h"


template<typename type>
type Read(uintptr_t address)
{
	if (reinterpret_cast<type*>(address) != nullptr)
		return *reinterpret_cast<type*>(address);
	else
		return type{};
}

template<typename type>
bool Write(uintptr_t address, const type& value)
{
	if (reinterpret_cast<type*>(address) != nullptr)
	{
		*reinterpret_cast<type*>(address) = value;
		return true;
	}

	return false;
}

uint64_t moduleBase = (uint64_t)GetModuleHandleA("GameAssembly.dll");

void misc()
{
	if (miscc::fov_Size)
	{
		uint64_t fov = Read<uint64_t>(moduleBase + 0x3298EE0); // "Name": "ConVar.Graphics_TypeInfo", "Signature": "ConVar_Graphics_c*"
		uint64_t instance = Read<uint64_t>(fov + 0xB8);

		Write<float>(instance + 0x18, miscc::fov_Changer);
	}
}