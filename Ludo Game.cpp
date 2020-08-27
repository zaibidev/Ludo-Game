#include<iostream>
#include<iomanip>		// for setw()... width set krne k liye
#include<time.h>		 // srand function..time input k liye
#include<Windows.h>			//color changeing use
using namespace std;

void initializeBoard();

void displayBoard();

bool checkEndGame();

int dice();

bool checkPlayerWin(int);

void domove(int dice);

void pickUpGoti(int gotiNum);

char route[72];			//path of goti to move 

int turn;		// global variable using....

int players[4][4];

int main()

{
	srand(time(NULL));

	initializeBoard();

	displayBoard();

	turn = 0;

	while (checkEndGame() == false)

	{

		if (checkPlayerWin(turn) == false)

		{

			domove(dice());

			turn = (turn + 1) % 4;

			displayBoard();

		}

		else

			turn = (turn + 1) % 4;
	}

	system("pause");

	return 0;

}

int dice()
{
	cout << " Press any key to roll the dice: ";

	system("pause");

	return  (rand() % 6) + 1;

}

void initializeBoard()
{

	route[52] = ' ';

	route[0] = '*';

	route[13] = '*';

	route[26] = '*';

	route[39] = '*';


	for (int i = 0; i < 5; i++)
	{
		route[57 + i] = '*';

		route[62 + i] = '*';

		route[52 + i] = '*';

		route[67 + i] = '*';

	}

	for (int i = 0; i < 4; i++)

		for (int j = 0; j < 4; j++)

			players[i][j] = -1;

}

void displayBoard()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//to add color in board ludo

	cout << setw(12) << "Green Player" << route[23] << route[24] << route[25] << setw(12) << "Blue Player" << endl;

	cout << " ";

	for (int i = 1; i<30; i++)

		cout << "=";

	cout << endl;

	for (int i = 22, j = 0, k = 26; j < 5; i--, j++, k++)

		cout << "|" << setw(12) << "|" << route[i] << "|" << route[62 + j] << "|" << route[k] << "|" << setw(12) << "|" << endl;


	for (int i = 12; i < 18; i++)

		cout << "|" << route[i];

	cout << "|" << setw(6) << "|";

	for (int i = 31; i < 37; i++)

		cout << route[i] << "|";


	cout << endl << "|" << route[11];

	for (int i = 0; i < 5; i++)

		cout << "|" << route[57 + i];

	cout << "|" << setw(6) << "|";

	for (int i = 4; i >= 0; i--)

		cout << route[67 + i] << "|";

	cout << route[37] << "|" << endl;


	for (int i = 10; i >= 5; i--)

		cout << "|" << route[i];

	cout << "|" << setw(6) << "|";

	for (int i = 43; i >= 38; i--)

		cout << route[i] << "|";

	cout << endl;

	for (int i = 4, j = 4, k = 44; j >= 0; i--, j--, k++)

		cout << "|" << setw(12) << "|" << route[i] << "|" << route[52 + j] << "|" << route[k] << "|" << setw(12) << "|" << endl;

	cout << " ";

	for (int i = 1; i<30; i++)

		cout << "=";

	cout << endl;

	cout << setw(12) << "Red Player " << route[51] << route[50] << route[49] << setw(12) << "Yellow Player" << endl << endl << endl;


	cout << "TOKEN" << setw(15) << " 1  2  3  4" << endl;

	for (int i = 0; i < 4; i++)

	{

		cout << "Player " << i + 1 << " ";

		for (int j = 0; j < 4; j++) {

			cout << players[i][j] << " ";

		}

		if (turn == i)

			cout << "This IS your turn";

		cout << endl;

	}
}

bool checkPlayerWin(int player)
{

	for (int j = 0; j < 4; j++)

		if (players[player][j] != -2)

			return false;

	return true;

}

bool checkEndGame()
{

	int x = 0;

	for (int i = 0; i < 4; i++)

		if (checkPlayerWin(i))

			x++;

	if (x == 3)

		return true;

	else

		return false;

}

bool anyOpen(int player)

{
	for (int j = 0; j < 4; j++)

		if (players[player][j] >= 0)

			return true;

	return false;

}


void OpenAny(int player)
{
	for (int j = 0; j < 4; j++)

		if (players[player][j] != -2)

		{
			players[player][j] = 0;

			route[player * 13] = static_cast <char>(player + 1);

			return;

		}
}

void pickUpGoti(int gotiNum)

{
	if ((turn * 13) + players[turn][gotiNum] == 0)

		route[0] = 'R';

	else if ((turn * 13) + players[turn][gotiNum] == 13)

		route[13] = 'G';

	else if ((turn * 13) + players[turn][gotiNum] == 26)

		route[26] = 'Y';

	else if ((turn * 13) + players[turn][gotiNum] == 39)

		route[39] = 'B';

	else

		route[(turn * 13) + players[turn][gotiNum]] = ' ';

}

void domove(int dice)
{

	system("cls");

	int gotiNum;

	cout << "You got " << dice << endl;

	if (!anyOpen(turn) && dice == 6)
		OpenAny(turn);
	else if (anyOpen(turn))
	{
		do

		{
			displayBoard();

			cout << "Select your goti to move from 1 to 4";

			cin >> gotiNum;

		} while ((gotiNum > 4 || gotiNum < 1) && !(players[turn][gotiNum - 1] == -1 && dice == 6) && !players[turn][gotiNum - 1] >= 0);

		pickUpGoti(gotiNum - 1);

		if (players[turn][gotiNum - 1] == -1 && dice == 6)
		{

			players[turn][gotiNum - 1] = 0;

			route[turn * 13] = static_cast <char>(turn + 1);

		}

		else

		{

			if (players[turn][gotiNum - 1] + dice < 51)

			{
				players[turn][gotiNum - 1] = players[turn][gotiNum - 1] + dice;

				route[((turn * 13) + players[turn][gotiNum - 1]) % 52] = static_cast <char>(turn + 1);

			}

		}

	}

	system("pause");

}