#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int findCandidateIndex(const vector<string>& candidates, const string& name) {
    for (size_t i = 0; i < candidates.size(); i++) {
        if (candidates[i] == name) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

int getPosition(const vector<int>& vote, int candidate) {
    for (size_t i = 0; i < vote.size(); i++) {
        if (vote[i] == candidate) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

int main() {
    int n;
    cout << "Введите количество кандидатов: ";
    cin >> n;

    int nIsbirateley;
    cout << "Введите количество избирателей: ";
    cin >> nIsbirateley;

    vector<string> candidates(n);
    cout << "Введите имена кандидатов:\n";
    for (string& candidate : candidates) {
        cin >> candidate;
    }

    vector<vector<int>> votes(nIsbirateley, vector<int>(n));
    cout << "Введите предпочтения каждого избирателя от лучшего к худшему:\n";
    for (int i = 0; i < nIsbirateley; i++) {
        cout << "Избиратель " << i + 1 << ": ";

        for (int j = 0; j < n; j++) {
            string name;
            cin >> name;

            votes[i][j] = findCandidateIndex(candidates, name);
        }
    }

    vector<int> bordaScores(n, 0);

    for (const vector<int>& vote : votes) {
        for (int position = 0; position < n; position++) {
            int candidate = vote[position];
            bordaScores[candidate] += n - 1 - position;
        }
    }

    int bordaWinner = 0;

    for (int i = 1; i < n; i++) {
        if (bordaScores[i] > bordaScores[bordaWinner]) {
            bordaWinner = i;
        }
    }

    cout << "\nРезультаты по методу Борда:\n";

    for (int i = 0; i < n; i++) {
        cout << candidates[i] << ": " << bordaScores[i] << " баллов\n";
    }

    cout << "Победитель по Борду: " << candidates[bordaWinner] << '\n';

    int condorcetWinner = -1;

    for (int candidate = 0; candidate < n; candidate++) {
        bool winsAgainstAll = true;

        for (int opponent = 0; opponent < n; opponent++) {
            if (candidate == opponent) {
                continue;
            }

            int candidateWins = 0;
            int opponentWins = 0;

            for (const vector<int>& vote : votes) {
                int candidatePosition = getPosition(vote, candidate);
                int opponentPosition = getPosition(vote, opponent);

                if (candidatePosition < opponentPosition) {
                    candidateWins++;
                } else {
                    opponentWins++;
                }
            }
            
            if (candidateWins <= opponentWins) {
                winsAgainstAll = false;
                break;
            }
        }

        if (winsAgainstAll) {
            condorcetWinner = candidate;
            break;
        }
    }

    cout << "\nРезультат по методу Кондорсе:\n";

    if (condorcetWinner == -1) {
        cout << "Победитель по Кондорсе не определен\n";
    } else  {
        cout << "Победитель по Кондорсе: " << candidates[condorcetWinner] << '\n';
    }

    if (condorcetWinner != -1 && condorcetWinner != bordaWinner) {
        cout << "\nМетоды дали разных победителей.\n";
    }

    return 0;
}