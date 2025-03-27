#ifndef __SCL_ASSERT_H_mlzlVSWW
#define __SCL_ASSERT_H_mlzlVSWW

#include <stdlib.h>

#define assert_exit(cond, code) do { if (!(cond)) exit(code); } while (0)
#define _assert(cond) assert_exit(cond, EXIT_FAILURE)

#endif
