#pragma warning(disable:4996)

#include <iostream>
using namespace std;

enum enChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Computer = 1, Player = 2, draw = 3 };

struct stGame {
	int GamesRound;
	int PlayerWonTimes;
	int ComputerWonTimes;
	int DrawTimes;
	enWinner FinalWinner;

};

struct stRound {
	enChoice PlayerChoice;
	enChoice ComputerChoice;
	enWinner RoundWinner;
};

int ReadNumberInRanger(int From, int To, string msg) {
	int number = 0;
	do {
		cout << msg << endl;
		cin >> number;
	} while (number < From || number > To);
	return number;
}

int RandomNumber(int From, int To) {

	int random = rand() % (To - From + 1) + From;
	return random;
}

enChoice GetPlayerChoice() {
	return (enChoice)ReadNumberInRanger(1, 3, "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors ?");
}

enWinner GetRoundWinner(enChoice PlayerChoice, enChoice ComputerChoice) {
	if (PlayerChoice == ComputerChoice) {
		return enWinner::draw;
	}

	if (PlayerChoice == enChoice::Stone && ComputerChoice == enChoice::Scissors)
		return enWinner::Player;

	if (PlayerChoice == enChoice::Paper && ComputerChoice == enChoice::Stone)
		return enWinner::Player;

	if (PlayerChoice == enChoice::Scissors && ComputerChoice == enChoice::Paper)
		return enWinner::Player;



	return enWinner::Computer;

}

string GetChoiceInString(enChoice choice) {
	switch (choice)
	{
	case Stone:
		return "Stone";
	case Paper:
		return "Paper";
	case Scissors:
		return "Scissors";
	default:
		return "ERROR";
	}
}

string GetWinnerName(enWinner winner) {
	switch (winner)
	{
	case Player:
		return "Player";
	case Computer:
		return "Computer";
	case draw:
		return "No Winner";
	default:
		return "ERROR";
	}
}

void PrintEachRoundStatus(enChoice PlayerChoice, enChoice ComputerChoice, enWinner winner, short RoundNumber) {

	cout << "\n\n___________________Round [" << RoundNumber << "] ___________________\n\n";
	cout << "Player   Choice: " << GetChoiceInString(PlayerChoice) << endl;
	cout << "Computer Choice: " << GetChoiceInString(ComputerChoice) << endl;
	cout << "Round Winner   : " << GetWinnerName(winner) << endl;
	cout << "________________________________________________\n\n";

}

enWinner GetFinalWinner(stGame game) {
	if (game.PlayerWonTimes > game.ComputerWonTimes) {
		return enWinner::Player;
	}
	else if (game.ComputerWonTimes > game.PlayerWonTimes) {
		return enWinner::Computer;
	}
	else
		return enWinner::draw;
}

enChoice GetComputerChoice() {
	return (enChoice)RandomNumber(1, 3);
}

stGame PlayGame(int GameRounds) {
	stRound Round;
	int PlayerWonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;
	for (short GameRound = 1; GameRound <= GameRounds; GameRound++) {
		cout << "\n\nRound " << "[" << GameRound << "]" << " begins:" << endl << endl;
		Round.PlayerChoice = GetPlayerChoice();
		Round.ComputerChoice = GetComputerChoice();
		Round.RoundWinner = GetRoundWinner(Round.PlayerChoice, Round.ComputerChoice);
		PrintEachRoundStatus(Round.PlayerChoice, Round.ComputerChoice, Round.RoundWinner, GameRound);
		switch (Round.RoundWinner)
		{
		case enWinner::draw:
			system("color 6F"); //turn screen to Yellow
			DrawTimes++;
			break;
		case enWinner::Player:
			system("color 2F"); //turn screen to Green
			PlayerWonTimes++;
			break;

		case enWinner::Computer:
			system("color 4F"); //turn screen to Red
			cout << '\a';
			ComputerWonTimes++;
			break;
		default:
			break;
		}
	}
	stGame game;
	game.GamesRound = GameRounds;
	game.PlayerWonTimes = PlayerWonTimes;
	game.ComputerWonTimes = ComputerWonTimes;
	game.DrawTimes = DrawTimes;
	game.FinalWinner = GetFinalWinner(game);

	return game;
}

void PrintGameResultsHeader() {
	cout << "\n\n\n" << "\t\t\t_______________________________________________________\n\n";
	cout << "\t\t\t                   +++ G a m e O v e r +++\n\n";
	cout << "\t\t\t_______________________________________________________\n\n";

}

void GameResults(stGame game) {
	PrintGameResultsHeader();
	cout << "\t\t\t____________________[Game Results]_____________________\n\n";
	cout << "\t\t\tGame Rounds         : " << game.GamesRound << endl;
	cout << "\t\t\tPlayer won times    : " << game.PlayerWonTimes << endl;
	cout << "\t\t\tComputer won times  : " << game.ComputerWonTimes << endl;
	cout << "\t\t\tdraw times          : " << game.DrawTimes << endl;
	cout << "\t\t\tFinal Winner        : " << GetWinnerName(game.FinalWinner) << endl;
	cout << "\t\t\t_______________________________________________________\n\n";

}

void ResetScreen() {
	system("cls");
	system("color 0F");

}


void GameStart() {
	char PlayAgain = 'y';
	do {
		ResetScreen();
		stGame game = PlayGame(ReadNumberInRanger(1, 10, "How Many Rounds 1 to 10 ? "));
		GameResults(game);
		cout << "Do you want to play again ? Y/N? : ";
		cin >> PlayAgain;

	} while (tolower(PlayAgain) == 'y');

}

int main() {
	srand((unsigned)time(NULL));
	GameStart();



	return 0;
}


