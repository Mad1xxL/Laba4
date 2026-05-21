package main

import (
	"fmt"
	"math"
)

const eps = 1e-4

func f(x float64) float64 {
	return 2*x + math.Cos(x)
}

func df(x float64) float64 {
	return 2 - math.Sin(x)
}

func phi(x float64) float64 {
	return -math.Cos(x) / 2
}

func bisection(a, b float64) {
	fmt.Println("\nМетод половинного деления")
	fmt.Printf("%-5s %-15s %-15s %-15s\n", "N", "an", "bn", "bn - an")

	n := 0

	for math.Abs(b-a) > eps {
		c := (a + b) / 2

		if f(a)*f(c) <= 0 {
			b = c
		} else {
			a = c
		}

		n++

		fmt.Printf(
			"%-5d %-15.6f %-15.6f %-15.6f\n",
			n,
			a,
			b,
			math.Abs(b-a),
		)
	}

	root := (a + b) / 2
	fmt.Printf("Корень методом половинного деления: %.6f\n", root)
	fmt.Printf("Количество итераций: %d\n", n)
}

func newton(x0 float64) {
	fmt.Println("\nМетод Ньютона")
	fmt.Printf("%-5s %-15s %-15s %-15s\n", "N", "xn", "xn+1", "xn+1 - xn")

	n := 0

	for {
		x1 := x0 - f(x0)/df(x0)
		diff := math.Abs(x1 - x0)

		fmt.Printf(
			"%-5d %-15.6f %-15.6f %-15.6f\n",
			n,
			x0,
			x1,
			diff,
		)

		if diff <= eps {
			fmt.Printf("Корень методом Ньютона: %.6f\n", x1)
			fmt.Printf("Количество итераций: %d\n", n+1)
			break
		}

		x0 = x1
		n++
	}
}

func simpleIterations(x0 float64) {
	fmt.Println("\nМетод простых итераций")
	fmt.Printf("%-5s %-15s %-15s %-15s\n", "N", "xn", "xn+1", "xn+1 - xn")

	n := 0

	for {
		x1 := phi(x0)
		diff := math.Abs(x1 - x0)

		fmt.Printf(
			"%-5d %-15.6f %-15.6f %-15.6f\n",
			n,
			x0,
			x1,
			diff,
		)

		if diff <= eps {
			fmt.Printf("Корень методом простых итераций: %.6f\n", x1)
			fmt.Printf("Количество итераций: %d\n", n+1)
			break
		}

		x0 = x1
		n++
	}
}

func main() {
	a := -1.0
	b := 0.0

	fmt.Println("Уравнение: 2x + cos(x) = 0")
	fmt.Println("Начальный отрезок: [-1; 0]")
	fmt.Printf("f(-1) = %.6f\n", f(-1))
	fmt.Printf("f(0) = %.6f\n", f(0))

	bisection(a, b)
	newton(-1)
	simpleIterations(-1)

	fmt.Println("\nИтог:")
	fmt.Println("Метод Ньютона сходится быстрее всего.")
	fmt.Println("Метод простых итераций сходится медленнее.")
	fmt.Println("Метод половинного деления самый устойчивый, но требует больше итераций.")
}