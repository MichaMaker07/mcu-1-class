/*
 * module.h
 *
 *  Created on: 10.08.2023
 *      Author: kepler440b
 */

#ifndef INCLUDE_MODULE_H_
#define INCLUDE_MODULE_H_

/*
 * @brief Common definitions for modules
 */

#include <limits.h>

// Error codes.
#define MOD_ERR_ARG				-1
#define MOD_ERR_RESOURCE		-2
#define MOD_ERR_STATE			-3
#define MOD_ERR_BAD_CMD			-4
#define MOD_ERR_OVERRUN			-5
#define MOD_ERR_BAD_INSTANCE	-6

// Get size of and array
#define ARRAY_SIZE(x)	(sizeof(x) / sizeof((x[0]))

// Increment a uint16_t, saturating at the maximum value.
#define INC_SAT_U16(a) do { (a) += ((a) == UINT16_MAX ? 0 : 1); } while (0)

// Clamp a numeric value between a lower and upper limit, inclusive.
#define CLAMP(a, low, high) ((a) <= (low) ? (low) : ((a) > (high) ? (high) : (a)))

#endif /* INCLUDE_MODULE_H_ */
