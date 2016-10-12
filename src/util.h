#pragma once

//
// Useful preprocessor directives
//

#define EXPAND( x ) x

#define FASTCALL(method)        void __fastcall method
#define FASTCALL_(type,method)  type __fastcall method

#define STDCALL(method)         HRESULT STDMETHODCALLTYPE method
#define STDCALL_(type,method)   type STDMETHODCALLTYPE method

#define NAKED                   __declspec(naked)

#define NOINLINE                __declspec(noinline)
#define NOTHROW                 __declspec(nothrow)
#define NOVTABLE                __declspec(novtable)

// short-hand for NOINLINE
#define NO_INL                  NOINLINE

// hooked __thiscall functions require a 'this' pointer parameter
#define _THIS                   void *This
#define _THIS_                  _THIS,

#define FNPTR(t,m)              t (*m)
#define FNPTR_(t,d,m)           t (d *m)
#define FNPTR_CDECL(t,m)        FNPTR_(t,__cdecl,m)
#define FNPTR_FASTCALL(t,m)     FNPTR_(t,__fastcall,m)
#define FNPTR_STDCALL(t,m)      FNPTR_(t,__stdcall,m)
#define FNPTR_THISCALL(t,m)     FNPTR_(t,__thiscall,m)

//
// Macros for classes with virtual tables
//

#define PUSH_VTABLE_(x)         DWORD x = *(DWORD*)this
#define POP_VTABLE_(x)          *(DWORD*)this = x
#define PUSH_VTABLE()           PUSH_VTABLE_(vtbl)
#define POP_VTABLE()            POP_VTABLE_(vtbl)

//
// Pointer macros for data types
//

#define _PTR(p)                 (DWORD*)p
#define _PTR_(t,p)              (t*)p

#define _OFFPTR(p,o)            (*_PTR(p) + o)

#define PTR(p)                  (DWORD*)p
#define PTR_(p,o)               PTR(((BYTE*)p + o))

//
// Console color macros
//

#define FOREGROUND_PINK (FOREGROUND_BLUE | FOREGROUND_RED)
#define FOREGROUND_TEAL (FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

#define BACKGROUND_PINK (BACKGROUND_BLUE | BACKGROUND_RED)
#define BACKGROUND_TEAL (BACKGROUND_BLUE | BACKGROUND_GREEN)
#define BACKGROUND_YELLOW (BACKGROUND_RED | BACKGROUND_GREEN)
#define BACKGROUND_WHITE (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)

//
// Pointer templates
//

struct auto_ptr
{
    union {
        const DWORD dwHandler;
        const LPVOID lpHandler;
    };

    template<typename T>
    constexpr auto_ptr(T ptr)
        : dwHandler(*(DWORD*)&ptr) {};

    constexpr auto_ptr(DWORD ptr)
        : dwHandler(ptr) {};

    constexpr operator LPVOID() const {
        return lpHandler;
    };

    constexpr operator DWORD() const {
        return dwHandler;
    };
};

template <typename TR = void>
constexpr inline TR* getPtr(LPVOID p, int offset) {
    return (TR*)((BYTE*)p + offset);
};

template <typename TR = void, class TC>
constexpr inline TR* getPtr(const TC *p, int offset) {
    return (TR*)getPtr((LPVOID)p, offset);
};

template <typename TV>
constexpr inline void setPtr(LPVOID p, int offset, TV value) {
    *(TV*)((BYTE*)p + offset) = value;
};

template <class TC, typename TV>
constexpr inline void setPtr(const TC *p, int offset, TV value) {
    *(TV*)((BYTE*)p + offset) = value;
};

//
// Pointer macros for assembler directives
//

#define __PTR(src)              ptr[src]
#define __PTR_DS(src)           ptr ds:[src]

#define __PTR_(t,src)           t __PTR(src) // <t> ptr[src]
#define __PTR_DS_(t,src)        t __PTR_DS(src) // <t> ptr ds:[src]

#define __BPTR(src)             __PTR_(byte,src) // byte ptr[src]
#define __BPTR_DS(src)          __PTR_DS_(byte,src) // byte ptr ds:[src]

#define __WPTR(src)             __PTR_(word,src) // word ptr[src]
#define __WPTR_DS(src)          __PTR_DS_(word,src) // word ptr ds:[src]

#define __DWPTR(src)            __PTR_(dword,src) // dword ptr[src]
#define __DWPTR_DS(src)         __PTR_DS_(dword,src) // dword ptr ds:[src]

//
// Debugging utilities
//

inline void debug(LPCSTR lpOutputStr) {
    OutputDebugStringA(lpOutputStr);
};

void debugf(const char *format, ...);

//
// Empty function templates
//

void    NullSub(void);

int     ReturnNullOrZero(void);
bool    ReturnFalse(void);

//
// Useful helper functions
//

bool LoadSystemLibrary(LPCSTR lpDllName, HMODULE *out);
bool GetHookProcAddress(HMODULE hModule, LPCSTR lpProcName, FARPROC *out);

inline bool file_exists(LPCSTR filename) {
    if (auto file = fopen(filename, "r")) {
        fclose(file);
        return true;
    }
    return false;
}