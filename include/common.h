#pragma once


#define pr_notice printf

#ifdef __INFO
#define pr_info(...)   do { if (info)  printf(__VA_ARGS__); } while (0)
#else
#define pr_info(...)
#endif

#ifdef __DEBUG
#define pr_debug(...)  do { if (debug) printf(__VA_ARGS__); } while (0)
#else
#define pr_debug(...)
#endif
