// Stone_Paper_Scissor_Game_Project.cpp
// This is a console-based game for Stone-Paper-Scissors.
// The user competes against the computer in a number of rounds.

#include <iostream>
#include <cstdlib>
#include <ctime>   // For time()
#include <string>
using namespace std;

// Prompt the user for number of rounds to play
int getNumberOfRounds() {
    int number = 0;
    do {
        cout << "How many rounds do you want to play?\n";
        cin >> number;
    } while (number <= 0); // must be positive
    return number;
}

// Convert numeric choice to string for display
string choiceToString(int number) {
    switch (number) {
    case 1: return "Stone";
    case 2: return "Paper";
    case 3: return "Scissor";
    default: return "Invalid";
    }
}

// Determine the winner for one round and update counters
string determineRoundWinner(int user, int computer, int& countComputer, int& countUser, int& countEqual) {
    if (user == computer) {
        countEqual++;
        system("color 6f"); // Yellow
        return "Equal";
    }
    else if (
        (user == 1 && computer == 3) || // Stone beats Scissor
        (user == 2 && computer == 1) || // Paper beats Stone
        (user == 3 && computer == 2)    // Scissor beats Paper
        ) {
        countUser++;
        system("color 2f"); // Green
        return "User";
    }
    else {
        countComputer++;
        system("color 4f"); // Red
        cout << "\a"; // Beep sound
        return "Computer";
    }
}

// Generate random number in a given range [from, to]
int getRandomNumber(int to, int from) {
    return rand() % (to - from + 1) + from;
}

// Determine overall game winner
string getFinalWinner(int counterUser, int counterComputer) {
    if (counterUser > counterComputer) return "User Won!";
    else if (counterComputer > counterUser) return "Computer Won!";
    else return "It's a Tie!";
}

// Display final result summary
void displayGameResult(int countUser, int countComputer, int equal, int totalRounds) {
    cout << "\n\n\n";
    cout << "\t\t\t======================================================================\n";
    cout << "\t\t\t===                          Game Over                            ====\n";
    cout << "\t\t\t======================================================================\n\n";

    cout << "\t\t\t============================ Game Result =============================\n";
    cout << "\t\t\tTotal Rounds Played     : " << totalRounds << endl;
    cout << "\t\t\tUser Wins               : " << countUser << endl;
    cout << "\t\t\tComputer Wins           : " << countComputer << endl;
    cout << "\t\t\tDraws                   : " << equal << endl;
}

// Core game logic
void playGame() {
    int userChoice = 0, computerChoice = 0;
    int rounds = getNumberOfRounds();
    int countUser = 0, countComputer = 0, countEqual = 0;

    for (int i = 1; i <= rounds; i++) {
        computerChoice = getRandomNumber(3, 1); // Random choice: 1 to 3
        cout << "\n----------------------- Round [" << i << "] -----------------------\n";
        cout << "Enter your choice: [1] Stone, [2] Paper, [3] Scissor\n";
        cin >> userChoice;

        // Validate user input
        if (userChoice < 1 || userChoice > 3) {
            cout << "Invalid input! Skipping this round.\n";
            continue;
        }

        // Show choices
        cout << "User choice     : " << choiceToString(userChoice) << endl;
        cout << "Computer choice : " << choiceToString(computerChoice) << endl;

        // Determine round winner
        string roundResult = determineRoundWinner(userChoice, computerChoice, countComputer, countUser, countEqual);
        cout << "Round Winner    : [" << roundResult << "]\n";
    }

    // Display overall results
    displayGameResult(countUser, countComputer, countEqual, rounds);
    cout << "\n\n\t\t\tFinal Winner: " << getFinalWinner(countUser, countComputer) << endl;
}

// Handles game start and replay option
void startGame() {
    char restart;
    bool playAgain = true;

    while (playAgain) {
        system("cls");       // Clear screen
        system("color 07");  // Reset color
        playGame();

        // Ask user if they want to play again
        while (true) {
            cout << "\n\n\n\t\t\tDo you want to play again? (Y/N): ";
            cin >> restart;

            if (restart == 'y' || restart == 'Y') {
                break; // Continue outer loop
            }
            else if (restart == 'n' || restart == 'N') {
                playAgain = false;
                break; // Exit both loops
            }
            else {
                cout << "\t\t\tInvalid input!\n";
            }
        }
    }
}

// Entry point of the program
int main() {
    srand((unsigned)time(NULL)); // Seed for randomness
    startGame();
    return 0;
}
