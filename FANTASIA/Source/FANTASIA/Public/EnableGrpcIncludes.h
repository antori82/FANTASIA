#define GRPC_USE_PROTO_LITE 1

#ifndef WORKAROUND_SYMBOL_MEMORY_BARRIER
#define WORKAROUND_SYMBOL_MEMORY_BARRIER
static void MemoryBarrier() {}
#endif

#pragma warning (disable : 4800) // forcing value to bool true or false
#pragma warning (disable : 4125) // decimal digit terminates octal escape sequence
#pragma warning (disable : 4647) // behavior change __is_pod has different value in previous version
#pragma warning (disable : 4668) // 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
#pragma warning (disable : 4582) // constructor is not implicitly called
#pragma warning (disable : 4583) // destructor is not implicitly called
#pragma warning (disable : 4946) // reinterpret_cast
#pragma warning (disable : 4005) // macro redefinition
#pragma warning (disable : 4005) // initializers put in library initialization area
#define  GOOGLE_PROTOBUF_NO_RTTI true
#ifndef __ANDROID__
#include "Windows/AllowWindowsPlatformTypes.h" 
#endif
#pragma intrinsic(_InterlockedCompareExchange64)
#define InterlockedCompareExchangeAcquire64 _InterlockedCompareExchange64
#define InterlockedCompareExchangeRelease64 _InterlockedCompareExchange64
#define InterlockedCompareExchangeNoFence64 _InterlockedCompareExchange64
#define InterlockedCompareExchange64 _InterlockedCompareExchange64