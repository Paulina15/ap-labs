package main

import (
	"fmt"
	"os"
)

func main() {
	name := ""
	if len(os.Args) >= 2 {
		for i := 1; i < len(os.Args); i++ {
			name += os.Args[i] + " "
		}
		fmt.Printf("Welcome %v to the jungle\n", name)
	} else {
		fmt.Println("ERROR")
	}

}
