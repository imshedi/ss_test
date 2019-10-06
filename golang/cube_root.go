package main

import (
	"fmt"
	"math/big"
)

func croot(num big.Int) big.Int {
	var first big.Int
	var last big.Int

	if num < big.Int(2) {
		return big.NewInt(num)
	}

	/*
	 * Cube root of a number can't exceed 2^(n/2)
	 * Example:
	 * (999 * 999 * 999)  = 997,002,999 [0011 1011 0110 1101 0000 1110 1111 0111]
	 * Heighest set bit is 29, so cube root can't exceed 2^(29/2) = (1 << 14)
	 * This is an optimization, by seeing 8(1000 in binary) cuberoot being 2(0010)
	 */
	var bc uint16
	for bc = 31; (num & (1 << bc)) == 0; bc-- {
	}
	last = 1 << (bc >> 1)

	for first = big.NewInt(2); first <= last; {
		var mid big.Int
		var cube big.Int

		mid = (first + last) >> 1 // Try using uint32_t for mid, magic.
		cube = mid * mid * mid

		if cube == num {
			return mid
		}

		if cube > num {
			last = mid - 1
		} else {
			first = mid + 1
		}
	}

	return big.Int(0)
}

func main() {
	var i big.Int

	fmt.Println("\n*** Cube Root using Binary Search ***\n")
	for i = 0; i < 1001; i++ {
		var n big.Int
		var res big.Int

		n = i * i * i
		res = croot(n)

		fmt.Printf("Cube root of (%d)%d is: %d\n", i, n, res)
		if res != i {
			break
		}
	}
}
