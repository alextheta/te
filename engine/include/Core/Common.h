#pragma once

#ifdef TE_IMPORT
#define TE_API __declspec(dllexport)
#else
#define TE_API __declspec(dllimport)
#endif