package main

import (
	"fmt"
	"os"
	"strconv"
)

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)
func calc(operator int, values []int) int {
	cont := values[0]
	fmt.Printf("%d", values[0])
	for i := 1; i < len(values); i++ {
		if operator == 1 {
			fmt.Printf(" + %d", values[i])
			cont += values[i]
		} else if operator == 2 {
			fmt.Printf(" - %d", values[i])
			cont -= values[i]
		} else {
			fmt.Printf(" * %d", values[i])
			cont *= values[i]
		}
	}
	
	return cont
}

func main() {
	operator := 0
	if os.Args[1] == "add" {
		operator = 1
	} else if os.Args[1] == "sub" {
		operator = 2
	} else if os.Args[1] == "mult" {
		operator = 3
	} else {
		fmt.Printf("operacion no valida, vuelve a intentarlo\n")
	}

	nValues := len(os.Args) - 2
	arr := make([]int, nValues)
	pos := 0

	for i := 2; i < len(os.Args); i++ {
		num, err := strconv.Atoi(os.Args[i])
		if err == nil {
			arr[pos] = num
			pos++

		} else {
			fmt.Print("operacion no valida, vuelve a intentarlo\n")
		}

	}
	result := calc(operator, arr)
	fmt.Printf(" = %d\n", result)
	return
}
