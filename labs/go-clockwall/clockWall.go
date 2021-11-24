package main

import (
	"net"
	"os"
	"strings"
	"time"
	"bufio"
	"fmt"
	"io"
	"log"
)

type clock struct {
	nombre, host string
}

func (c *clock) watch(w io.Writer, r io.Reader) {
	s := bufio.NewScanner(r)
	for s.Scan() {
		fmt.Fprintf(w, "%s: %s\n", c.nombre, s.Text())
	}
	fmt.Println(c.nombre, "hecho")
	if s.Err() != nil {
		log.Printf("no puedo leer de %s: %s", c.nombre, s.Err())
	}
}

func main() {
	if len(os.Args) == 1 {
		fmt.Fprintln(os.Stderr, "usage: clockwall NAME=HOST ...")
		os.Exit(1)
	}
	clocks := make([]*clock, 0)
	for _, a := range os.Args[1:] {
		fields := strings.Split(a, "=")
		if len(fields) != 2 {
			fmt.Fprintf(os.Stderr, "mal argumento: %s\n", a)
			os.Exit(1)
		}
		clocks = append(clocks, &clock{fields[0], fields[1]})
	}
	for _, c := range clocks {
		conn, err := net.Dial("tcp", c.host)
		if err != nil {
			log.Fatal(err)
		}
		defer conn.Close()
		go c.watch(os.Stdout, conn)
	}
	for {
		time.Sleep(time.Minute)
	}
}
