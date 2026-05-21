package main

import (
	"fmt"
)

func findCandidateIndex(candidates []string, name string) int {
	for i, candidate := range candidates {
		if candidate == name {
			return i
		}
	}

	return -1
}

func getPosition(vote []int, candidate int) int {
	for i, value := range vote {
		if value == candidate {
			return i
		}
	}

	return -1
}

func main() {
	var n int
	var k int

	fmt.Print("Введите количество кандидатов: ")
	fmt.Scan(&n)

	fmt.Print("Введите количество избирателей: ")
	fmt.Scan(&k)

	candidates := make([]string, n)

	fmt.Println("Введите имена кандидатов:")

	for i := range candidates {
		fmt.Scan(&candidates[i])
	}

	votes := make([][]int, k)

	fmt.Println("Введите предпочтения каждого избирателя от лучшего к худшему:")

	for i := 0; i < k; i++ {
		votes[i] = make([]int, n)

		fmt.Printf("Избиратель %d: ", i+1)

		for j := 0; j < n; j++ {
			var name string
			fmt.Scan(&name)

			index := findCandidateIndex(candidates, name)

			if index == -1 {
				fmt.Println("Ошибка: кандидат не найден:", name)
				return
			}

			votes[i][j] = index
		}
	}

	// Метод Борда
	bordaScores := make([]int, n)

	for _, vote := range votes {
		for position, candidate := range vote {
			bordaScores[candidate] += n - 1 - position
		}
	}

	bordaWinner := 0

	for i := 1; i < n; i++ {
		if bordaScores[i] > bordaScores[bordaWinner] {
			bordaWinner = i
		}
	}

	fmt.Println("\nРезультаты по методу Борда:")

	for i := 0; i < n; i++ {
		fmt.Printf("%s: %d баллов\n", candidates[i], bordaScores[i])
	}

	fmt.Println("Победитель по Борду:", candidates[bordaWinner])

	// Метод Кондорсе
	condorcetWinner := -1

	for candidate := 0; candidate < n; candidate++ {
		winsAgainstAll := true

		for opponent := 0; opponent < n; opponent++ {
			if candidate == opponent {
				continue
			}

			candidateWins := 0
			opponentWins := 0

			for _, vote := range votes {
				candidatePosition := getPosition(vote, candidate)
				opponentPosition := getPosition(vote, opponent)

				if candidatePosition < opponentPosition {
					candidateWins++
				} else {
					opponentWins++
				}
			}

			if candidateWins <= opponentWins {
				winsAgainstAll = false
				break
			}
		}

		if winsAgainstAll {
			condorcetWinner = candidate
			break
		}
	}

	fmt.Println("\nРезультат по методу Кондорсе:")

	if condorcetWinner == -1 {
		fmt.Println("Победитель по Кондорсе не определен")
	} else {
		fmt.Println("Победитель по Кондорсе:", candidates[condorcetWinner])
	}

	if condorcetWinner != -1 && condorcetWinner != bordaWinner {
		fmt.Println("\nМетоды дали разных победителей.")
	}

	if condorcetWinner == -1 {
		fmt.Println("\nПо методу Кондорсе победитель может не существовать, если нет кандидата, который выигрывает у всех остальных в парных сравнениях.")
	}
}