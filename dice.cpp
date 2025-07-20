#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

// Player class
class Player {
public:
    string name;
    int totalScore;

    Player(string n) {
        name = n;
        totalScore = 0;
    }
};

// Dice class
class Dice {
public:
    // API to roll the dice (returns number between 1 to 6)
    int rollDice() {
        return (rand() % 6) + 1;
    }
};

// Struct to store history entry
struct HistoryEntry {
    int round;
    string playerName;
    int score;
};

// Compare function for priority queue (max-heap)
struct Compare {
    bool operator()(pair<int, string> a, pair<int, string> b) {
        return a.first < b.first; // higher score comes first
    }
};

// DiceGame class
class DiceGame {
private:
    unordered_map<string, Player*> players; // hash map for player lookup
    vector<HistoryEntry> history;           // history of all rounds
    Dice dice;
    int round;

public:
    DiceGame() {
        round = 1;
        srand(time(0)); // Seed random number generator
    }

    // API to add a new player
    void addPlayer(const string& name) {
        players[name] = new Player(name);
    }

    // API to play one round
    void playRound() {
        cout << "\n=========================================\n";
        cout << "               ROUND " << round << "\n";
        cout << "=========================================\n";

        int maxRoll = 0;
        string roundWinner;

        for (auto& it : players) {
            int roll = dice.rollDice();
            it.second->totalScore += roll;
            history.push_back({round, it.first, roll});
            cout << it.first << " rolled: " << roll << " (Total Score: " << it.second->totalScore << ")\n";

            if (roll > maxRoll) {
                maxRoll = roll;
                roundWinner = it.first;
            }
        }

        cout << "\n🏆 Winner of Round " << round << ": " << roundWinner << " with a roll of " << maxRoll << "!\n";
        round++;
    }

    // API to play multiple rounds
    void playRounds(int totalRounds) {
        for (int i = 0; i < totalRounds; i++) {
            playRound();
        }
    }

    // API to print the history
    void printHistory() {
        cout << "\n=========================================\n";
        cout << "              GAME HISTORY\n";
        cout << "=========================================\n";
        for (auto& h : history) {
            cout << "Round " << h.round << ": " << h.playerName << " rolled " << h.score << "\n";
        }
    }

    // API to show leaderboard using priority queue
    void showLeaderBoard() {
        cout << "\n=========================================\n";
        cout << "              LEADERBOARD\n";
        cout << "=========================================\n";
        priority_queue<pair<int, string>, vector<pair<int, string>>, Compare> pq;

        for (auto& it : players) {
            pq.push({it.second->totalScore, it.first});
        }

        int rank = 1;
        while (!pq.empty()) {
            auto p = pq.top(); pq.pop();
            cout << "#" << rank << ": " << p.second << " with score " << p.first << "\n";
            rank++;
        }
    }
};

// Main Function
int main() {
    DiceGame game;
    int numPlayers, numRounds;
    string name;

    cout << "🎲 Welcome to Dice Game Simulator 🎲\n\n";
    cout << "Enter number of players: ";
    cin >> numPlayers;

    for (int i = 1; i <= numPlayers; i++) {
        cout << "Enter name for Player " << i << ": ";
        cin >> name;
        game.addPlayer(name);
    }

    cout << "Enter number of rounds to play: ";
    cin >> numRounds;

    game.playRounds(numRounds);
    game.printHistory();
    game.showLeaderBoard();

    return 0;
}
