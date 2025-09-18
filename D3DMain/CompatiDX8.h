#pragma once

// ----------------------------
// 32bitŠÂ‹«‚Å POINTER_64 ‚ğ–³Œø‰»
// ----------------------------
#if !defined(POINTER_64) && !defined(_WIN64)
#define POINTER_64
#endif

// ----------------------------
// 32bitŠÂ‹«‚Å PVOID64 ‚ğ’è‹`
// ----------------------------
#if !defined(PVOID64) && !defined(_WIN64)
typedef void* PVOID64;
#endif

// ----------------------------
// ŒÃ‚¢ TCHAR ŒnŠÖ”‚ÌˆÀ‘S‘Î‰
// ----------------------------
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <tchar.h>

