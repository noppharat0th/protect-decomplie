#include <windows.h>
#include <intrin.h>
#include <iostream>

template <size_t N, char KEY>

class security {

private:
	char buffer[N];
	constexpr char encrypt(char c) const { return c ^ KEY; }

public:
	template <size_t... I>
	constexpr ObfuscatedString(const char(&str)[N], std::index_sequence<I...>)
		: buffer{ encrypt(str[I])... } {
	}

	__forceinline bool detectDebugger()
	{	
		#ifdef _WIN64
			unsigned char* peb = (unsigned char*)__readgsqword(0x60);
			return peb[2] != 0;
		#else
			return false;
		#endif
	}
};