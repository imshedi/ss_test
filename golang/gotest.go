package main

import (
	"bufio"
	"bytes"
	"fmt"
	"math"
	"math/rand"
	"os"
	"runtime"
	"strings"
	"time"
	"unsafe"
)

func WhereAmI() {
	pc, fileName, fileLine, ok := runtime.Caller(1)
	details := runtime.FuncForPC(pc)
	if ok && details != nil {
		fmt.Printf("\n< Function: %s > < File: %s > < Line: %d >\n", details.Name(), fileName, fileLine)
	}
}

func showbits(num int, totalBits uint) {
	for i := totalBits - 1; i < totalBits; i-- {
		fmt.Printf("%d", (num>>i)&1)
		if (i % 4) == 0 {
			fmt.Printf(" ")
		}
	}
	fmt.Println("")
}

func readEx() {
	WhereAmI()

	fmt.Println("--- Readstring ---")
	reader := bufio.NewReader(os.Stdin)
	fmt.Printf("Enter text: ")
	text, _ := reader.ReadString('\n')
	fmt.Println(text)

	fmt.Println("--- Scanln ---")
	fmt.Println("Enter text: ")
	text2 := ""
	fmt.Scanln(&text2)
	fmt.Println(text2)

	fmt.Println("--- Scanf ---")
	ln := ""
	fmt.Scanf("%s", &ln)
	fmt.Println(ln)
}

func randomEx() {
	WhereAmI()
	rand.Seed(time.Now().UnixNano())
	fmt.Println("Random Number:", rand.Intn(3000)+1000)
}

func pow10Ex() {
	WhereAmI()
	fmt.Println("Pow10(2):", math.Pow10(2))
}

func bytesEx() {
	WhereAmI()
	fmt.Println(bytes.Count([]byte("cheese"), []byte("e")))
	fmt.Println(bytes.Count([]byte("five"), []byte("")))
}

func stringEx() {
	WhereAmI()
	fmt.Println("Contains:  ", strings.Contains("test", "es"))
	fmt.Println("Count:     ", strings.Count("test", "t"))
	fmt.Println("HasPrefix: ", strings.HasPrefix("test", "te"))
	fmt.Println("HasSuffix: ", strings.HasSuffix("test", "st"))
	fmt.Println("Index:     ", strings.Index("test", "e"))
	fmt.Println("Join:      ", strings.Join([]string{"a", "b"}, "-"))
	fmt.Println("Repeat:    ", strings.Repeat("a", 5))
	fmt.Println("Replace:   ", strings.Replace("foo", "o", "0", -1))
	fmt.Println("Replace:   ", strings.Replace("foo", "o", "0", 1))
	fmt.Println("Split:     ", strings.Split("a-b-c-d-e", "-"))
	fmt.Println("ToLower:   ", strings.ToLower("TEST"))
	fmt.Println("ToUpper:   ", strings.ToUpper("test"))
	fmt.Println()
	fmt.Println("Len: ", len("hello"))
	fmt.Println("Char:", "hello"[1])
}

func rightRotEx() {
	var num = 0x1234
	var shiftBy = uint(4)
	var totalBits = uint(unsafe.Sizeof(num)) * 8

	WhereAmI()
	fmt.Printf("Type & Sizeof num --> %T %d bytes\n", num, unsafe.Sizeof(num))

	showbits(num, totalBits)
	num = (num >> shiftBy) | (num << (totalBits - shiftBy))
	fmt.Printf("Res: 0x%X\n", num)
	showbits(num, totalBits)
}

func swap(x int, y int) (int, int) {
	WhereAmI()
	fmt.Println("Before swap(x, y):", x, y)
	x, y = y, x
	fmt.Println("After swap(x, y):", x, y)
	return x, y
}

func main() {
	//rightRotEx()
	//pow10Ex()
	//randomEx()
	//bytesEx()
	//stringEx()
	//readEx()
	swap(10, 20)
}
