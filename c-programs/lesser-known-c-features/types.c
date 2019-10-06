/*
 * Types with defined size
 * Have a look at the header file stdint.h.
 * There are typedefined types like (where N is in {8, 16, 32, 64})
 *
 * intN_t - signed integers with exactly specified width
 * int_leastN_t - signed integers with a width of at least N
 * int_fastN_t - fastest signed integers with a width of at least N
 * Unsigned variants have prefix "u".
 *
 * Be careful when using printf functions. Since you do not know which C type
 * are behind these typedefs, you have to use predefined constants from
 * inttypes.h. Constants starts with PRI followed by type character
 * (one of diouxX), modificator LEAST or FAST or nothing, and number of bits.
 * For example, 32 bit fast integer would take the form PRIdFAST32.
 *
 * For more info.
 * https://en.wikibooks.org/wiki/C_Programming/stdint.h
 * https://en.wikibooks.org/wiki/C_Programming/inttypes.h
 * https://en.cppreference.com/w/cpp/types/integer
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

int main(void)
{
	int8_t i8;
	int16_t i16;
	int32_t i32;
	int64_t i64;
	printf("%" PRId64 "\n", i64);

	uint8_t ui8;
	uint16_t ui16;
	uint32_t ui32;
	uint64_t ui64;

	int_least8_t il8;
	int_least16_t il16;
	int_least32_t il32;
	int_least64_t il64;

	uint_least8_t uil8;
	uint_least16_t uil16;
	uint_least32_t uil32;
	uint_least64_t uil64;

	int_fast8_t if8;
	int_fast16_t if16;
	int_fast32_t if32;
	int_fast64_t if64;

	uint_fast8_t uif8;
	uint_fast16_t uif16;
	uint_fast32_t uif32;
	uint_fast64_t uif64;

	intptr_t ip;
	uintptr_t uip;

	intmax_t im;
	uintmax_t uim;

	return 0;
}
