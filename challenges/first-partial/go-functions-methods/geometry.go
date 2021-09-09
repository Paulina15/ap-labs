package main

import (
	"math"
	"math/rand"
	"fmt"
	"os"
	"strconv"
	"sort"
)

type Point struct{ x, y float64 }

func (p Point) X() float64 {
	return p.x;
}

func (p Point) Y() float64 {
	return p.y;
}

// traditional function
func Distance(p, q Point) float64 {
	return math.Hypot(q.X()-p.X(), q.Y()-p.Y())
}

// same thing, but as a method of the Point type
func (p Point) Distance(q Point) float64 {
	return math.Hypot(q.X()-p.X(), q.Y()-p.Y())
}

//!-point

//!+path

// A Path is a journey connecting the points with straight lines.
type Path []Point

// Distance returns the distance traveled along the path.
func (path Path) Distance() float64 {
	sum := 0.0
	for i := range path {
		if i > 0 {
			sum += path[i-1].Distance(path[i])
		}
	}
	return sum
}

//!-path

func main() {
	if len(os.Args) == 2{
		if sides, err := strconv.Atoi(os.Args[1]); err == nil {
			if (sides > 2) {
				path := generateForm(sides) // Generate shape
				print_Form(path) 
			} else {
				fmt.Printf("ERROR Cant create a shape from %v side(s)\n", sides)	
			}
		} else {
			fmt.Println("ERROR Usage go run geometry.go <sides>")	
		}
	} else {
		fmt.Println("ERROR Usage go run geometry.go <sides>")	
	}
}

type orientationP Path

func (a orientationP) Len() int {
	 return len(a)
}
func (a orientationP) Swap(i, j int) { a[i], a[j] = a[j], a[i] }
func (a orientationP) Less(i, j int) bool { 
	return math.Atan2(a[i].Y(), a[i].X()) < math.Atan2(a[j].Y(), a[j].X()) 
}

func generateForm(sides int) Path{
	min := -100.00
	max := 100.00
	points := make([]Point, sides)
	closedForm := make([]Point, sides+1)

	for i := 0; i < sides; i++ {
		x := min + rand.Float64() * float64(max - min)
		y := min + rand.Float64() * float64(max - min)
		points[i] = Point{x, y}
	}
	sort.Sort(orientationP(points))
	copy(closedForm, points)
	closedForm[sides] = points[0];

	return closedForm
}

func print_Form(path Path) {
	fmt.Printf("- Generating a [%v] side figure\n", len(path)-1)
	fmt.Printf("- Vertices of the figure\n")
	for _, el := range path[:len(path)-1] {
		fmt.Printf("  - (%.2f,  %.2f)\n", el.X(), el.Y())
	}
	fmt.Printf("- Figure's Perimeter\n  - ")
	for i := range path {
		if i > 0 && i < len(path)-1 {
			fmt.Printf("%.2f + ", path[i-1].Distance(path[i]))
		}
	}
	fmt.Printf("%.2f = %.2f\n", path[len(path)-2].Distance(path[len(path)-1]), path.Distance())
}
