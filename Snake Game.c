// ID: 318670668
// Name: Daniel Sionov

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

#define UP 72  // Up Arrow 
#define DOWN 80 // Down Arrow 
#define LEFT 75  // Left Arrow 
#define RIGHT 77  // Right Arrow 
#define ESC 27  // Escape Key
#define ROWS 25 // size of rows
#define COLS 75 // size of cols
#define MAXSIZE 20 // max size of snake parts
#define RESET 73 // case of a loss i want the snake to stop is movement until the user presses new key;
#define EXIT 5 // when user wants to get out of game he presses 0 and system prints out exit with code 5; 

typedef struct {
	int x;
	int y;
}Cordinate;

void gotoxy(int y, int x);
int getKey();
void printMenu();
void printLine(int count, char ch);
void printTable(int rows, int cols);
void setNewRandomFood(Cordinate* food, int rows, int cols);
void setSnakeToStartLocation(Cordinate startLocation, Cordinate snake[], int snakeSize);
void printGameOver();
void printWinMessege();
bool updateSnakeValues(Cordinate snake[], Cordinate tmp, int snakeSize);
bool checkIfSnakeAteHimself(Cordinate snake[], int snakeSize, bool gameOver);

void main()
{
	int choice_of_level, checkInput, snakeSize = 10, foodCounter;
	bool valid_level = false;
	char key = '0', check = '0';
	Cordinate startPoint, tmp1;
	startPoint.x = 40;
	startPoint.y = 12;
	Cordinate snake[MAXSIZE];
	Cordinate food = { 100,100 };
	bool snakeIsBig = false, gameOver;

	while (!valid_level)
	{
		gameOver = false;
		printMenu();
		checkInput = scanf("%d", &choice_of_level);

		if (choice_of_level > 1 || choice_of_level < 0)
			continue;

		switch (choice_of_level)
		{
		case 1:
			system("cls");
			break;
		case 0:
			exit(EXIT);
		}

		printTable(ROWS, COLS);
		setNewRandomFood(&food, ROWS, COLS);
		gotoxy(0, 81);

		setSnakeToStartLocation(startPoint, snake, snakeSize); // here we initialize the snake cells to be in the middle of the screen;
		check = RESET;
		key = RESET;
		foodCounter = 0;
		snakeSize = 10;

		while (key != ESC)
		{
			Sleep(500);

			tmp1.x = snake[0].x;
			tmp1.y = snake[0].y;

			if (_kbhit())
				check = getKey();
			if (check == RIGHT || check == DOWN || check == LEFT || check == UP || check == ESC)
				key = check;
			switch (key)
			{
			case RIGHT:
				snake[0].x++;
				break;
			case DOWN:
				snake[0].y++;
				break;
			case LEFT:
				snake[0].x--;
				break;
			case UP:
				snake[0].y--;
				break;
			default:
				continue;
			}
			// check if snake ate the food;
			if (snake[0].x == food.x && snake[0].y == food.y)
			{
				snakeSize++;
				setNewRandomFood(&food, ROWS, COLS);
				foodCounter++;
			}
			// check if game ended with victory;
			if (foodCounter == 10)
			{
				system("cls");
				printWinMessege();
				break;
			}
			// check is snake hited a wall;
			if (snake[0].x == 0 || snake[0].x == 76 || snake[0].y == 0 || snake[0].y == 26) // check if snake's head touches to border; 
			{
				system("cls");
				printGameOver();
				break;
			}

			// check is snake ate himself;
			gameOver = checkIfSnakeAteHimself(snake, snakeSize, gameOver);
			if (gameOver)
				break;

			// delete last cell of snake;
			if (snakeIsBig)
			{
				gotoxy(snake[snakeSize - 1].x, snake[snakeSize - 1].y);
				printf(" ");
				gotoxy(0, 81);
			}
			// update snake cells every step;
			snakeIsBig = updateSnakeValues(snake, tmp1, snakeSize);

			// print snake head;
			gotoxy(snake[0].x, snake[0].y);
			printf("@");
			gotoxy(0, 81);
			// check game exit key;
		}
		if (key == ESC)
		{
			system("cls");
			printGameOver();
		}
	}
}
// this function go to a point on the screen;
void gotoxy(int y, int x) {
	printf("\x1b[%d;%df", x + 1, y + 1);
}
// this function gets the key user pressed on keyboard;
int getKey()
{
	char KeyStroke = _getch();
	if (KeyStroke == 0 || KeyStroke == -32)
		KeyStroke = _getch();
	return (KeyStroke);
}
// this function prints a line of chars;
void printLine(int count, char ch)
{
	int i;

	for (i = 0; i < count; i++)
		printf("%c", ch);

	printf("\n");
}
// this function pprints the game borders;
void printTable(int rows, int cols)
{
	printLine(77, '#');
	for (int row = 0; row < rows; row++)
	{
		printf("%c", '#');
		for (int col = 0; col < cols; col++)
		{
			printf("%c", ' ');
		}
		printf("%c", '#');
		printf("\n");
	}
	printLine(77, '#');
}
// this function generates the food on the game board;
void setNewRandomFood(Cordinate* food, int rows, int cols)
{
	srand(time(NULL));
	food->x = (rand() % cols) + 1;
	food->y = (rand() % rows) + 1;
	gotoxy(food->x, food->y);
	printf("$");
}
// this function prints the main menu at start;
void printMenu()
{
	printLine(55, '*');
	printf("* Pick Your Level, to exit press 0\n");
	printf("* 0 - Exit\n");
	printf("* 1 - Basic Level\n");
	printf("* 2 - Intermidiate Level\n");
	printf("* 3 - Advanced Level\n");
	printLine(55, '*');
}
// this function sets the snake cells to be initialized at a single point;
void setSnakeToStartLocation(Cordinate startLocation, Cordinate snake[], int snakeSize)
{
	for (int i = 0; i < snakeSize; i++)
	{
		snake[i].x = startLocation.x;
		snake[i].y = startLocation.y;
	}
}
// this function prints the gameover messege;
void printGameOver()
{
	printLine(35, '#');
	printf("           GAME OVER\n");
	printLine(35, '#');
}
// this function prints the win messege;
void printWinMessege()
{
	printLine(35, '#');
	printf("           YOU WIN\n");
	printLine(35, '#');
}
// this function update the values of the body of the snake 
bool updateSnakeValues(Cordinate snake[], Cordinate tmp, int snakeSize)
{
	bool snake_is_big = false;
	for (int i = 2; i < snakeSize - 1; i++) // this loop update the values of the snake when it's size is below 10; (first 10 secs of game)
	{
		if (i == 8)
			snake_is_big = true;
		if (snake[i].x == snake[i + 1].x && snake[i].y == snake[i + 1].y)
		{
			for (i; i > 1; i--)
			{
				snake[i].x = snake[i - 1].x;
				snake[i].y = snake[i - 1].y;
			}
			snake[1].x = tmp.x;
			snake[1].y = tmp.y;
			return snake_is_big;
		}
		else
		{
			continue;
		}
	}

	for (int i = snakeSize - 1; i > 1; i--)
		if (snake_is_big)
		{
			snake[i].x = snake[i - 1].x;
			snake[i].y = snake[i - 1].y;
		}
	snake[1].x = tmp.x;
	snake[1].y = tmp.y;

	return snake_is_big;
}
// this function checks if the snake head ate his body;
bool checkIfSnakeAteHimself(Cordinate snake[], int snakeSize, bool gameOver)
{
	for (int i = 1; i < snakeSize - 1; i++)  // check if snake ate himself;
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			system("cls");
			printGameOver();
			gameOver = true;
			break;
		}
	return gameOver;
}
