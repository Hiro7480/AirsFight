#pragma once

// ----------------------------
// 32bit���� POINTER_64 �𖳌���
// ----------------------------
#if !defined(POINTER_64) && !defined(_WIN64)
#define POINTER_64
#endif

// ----------------------------
// 32bit���� PVOID64 ���`
// ----------------------------
#if !defined(PVOID64) && !defined(_WIN64)
typedef void* PVOID64;
#endif

// ----------------------------
// �Â� TCHAR �n�֐��̈��S�Ή�
// ----------------------------
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <tchar.h>

