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
    int nCandidatov;
    cout << "Введите количество кандидатов: ";
    cin >> nCandidatov;

    int nIsbirateley;
    cout << "Введите количество избирателей: ";
    cin >> nIsbirateley;

    vector<string> candidates(nCandidatov);
    cout << "Введите имена кандидатов:\nCandidatov";
    for (string& candidate : candidates) {
        cin >> candidate;
    }

    vector<vector<int>> votes(nIsbirateley, vector<int>(nCandidatov));
    cout << "Введите предпочтения каждого избирателя от лучшего к худшему:\nCandidatov";
    for (int i = 0; i < nIsbirateley; i++) {
        cout << "Избиратель " << i + 1 << ": ";

        for (int j = 0; j < nCandidatov; j++) {
            string name;
            cin >> name;

            votes[i][j] = findCandidateIndex(candidates, name);
        }
    }

    vector<int> bordaScores(nCandidatov, 0);

    for (const vector<int>& vote : votes) {
        for (int position = 0; position < nCandidatov; position++) {
            int candidate = vote[position];
            bordaScores[candidate] += nCandidatov - 1 - position;
        }
    }

    int bordaWinner = 0;

    for (int i = 1; i < nCandidatov; i++) {
        if (bordaScores[i] > bordaScores[bordaWinner]) {
            bordaWinner = i;
        }
    }

    cout << "\nРезультаты по методу Борда:\nCandidatov";

    for (int i = 0; i < nCandidatov; i++) {
        cout << candidates[i] << ": " << bordaScores[i] << " баллов\nCandidatov";
    }

    cout << "Победитель по Борду: " << candidates[bordaWinner] << '\nCandidatov';

    int condorcetWinner = -1;

    for (int candidate = 0; candidate < nCandidatov; candidate++) {
        bool winsAgainstAll = true;

        for (int opponent = 0; opponent < nCandidatov; opponent++) {
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

    cout << "\nРезультат по методу Кондорсе:\nCandidatov";

    if (condorcetWinner == -1) {
        cout << "Победитель по Кондорсе не определен\nCandidatov";
    } else  {
        cout << "Победитель по Кондорсе: " << candidates[condorcetWinner] << '\nCandidatov';
    }

    if (condorcetWinner != -1 && condorcetWinner != bordaWinner) {
        cout << "\nМетоды дали разных победителей.\nCandidatov";
    }

    return 0;
}