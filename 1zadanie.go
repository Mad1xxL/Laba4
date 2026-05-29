package main

import (
	"fmt"
	"math"
)

const EPS = 1e-4

func f(x float64) float64 {
	return 2*x + math.Cos(x)
}

func df(x float64) float64 {
	return 2 - math.Sin(x)
}

func phi(x float64) float64 {
	return -math.Cos(x) / 2
}

func sqrtNaOtrezke(a, b float64) {
	fmt.Println("\nМетод половинного деления")
	fmt.Printf("%5s%15s%15s%15s\n", "N", "a(n)", "b(n)", "b(n)-a(n)")

	n := 0

	for math.Abs(b-a) > EPS {
		seredina := (a + b) / 2

		if f(a)*f(seredina) <= 0 {
			b = seredina
		} else {
			a = seredina
		}

		n++
		fmt.Printf("%5d%15.6f%15.6f%15.6f\n",
			n, a, b, math.Abs(b-a))
	}

	fmt.Printf("Корень: %.6f\n", (a+b)/2)
}

func newton(x0 float64) {
	fmt.Println("\nМетод Ньютона")
	fmt.Printf("%5s%15s%15s%15s\n", "N", "x(n)", "x(n+1)", "x(n+1)-x(n)")

	n := 0

	for {
		x1 := x0 - f(x0)/df(x0)

		fmt.Printf("%5d%15.6f%15.6f%15.6f\n",
			n, x0, x1, math.Abs(x1-x0))

		if math.Abs(x1-x0) <= EPS {
			fmt.Printf("Корень: %.6f\n", x1)
			break
		}

		x0 = x1
		n++
	}
}

func simpleIterations(x0 float64) {
	fmt.Println("\nМетод простых итераций")
	fmt.Printf("%5s%15s%15s%15s\n", "N", "x(n)", "x(n+1)", "x(n+1)-x(n)")

	n := 0

	for {
		x1 := phi(x0)

		fmt.Printf("%5d%15.6f%15.6f%15.6f\n",
			n, x0, x1, math.Abs(x1-x0))

		if math.Abs(x1-x0) <= EPS {
			fmt.Printf("Корень: %.6f\n", x1)
			break
		}

		x0 = x1
		n++
	}
}

func main() {
	a := -1.0
	b := 0.0

	sqrtNaOtrezke(a, b)
	newton(-1)
	simpleIterations(-1)
}