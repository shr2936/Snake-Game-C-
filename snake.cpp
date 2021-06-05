/*
The controls used are as follows:
UP: W
DOWN: S
LEFT: A
RIGHT: D

The speed of game can be controlled by time in Sleep() function in main()

*/
#include<iostream>
#include<conio.h> // console input output
#include<windows.h>
using namespace std;

int snake[400][2];                                 // array to store the coordinates of snake as its length increases , snake[0][0] would be the starting point
int fruitX, fruitY;                                 // coordinates of fruit for snake
int length, score;                                 // length of snake and score of user
bool gameOver;                                     // to infinitely loop over the game until gameOver is false
bool gameComplete;
const int width = 7;                              // width of playing area
const int height = 7;                             // height of playing area
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;                                    // holds the direction of snake
eDirection previous;
int overReason;

void Setup() {
  // initial setup
  gameOver = false;
  gameComplete = false;
  overReason = 0;
  dir = STOP;
  previous = LEFT;
  snake[0][0] = width / 2;
  snake[0][1] = height / 2;
  fruitX = (rand() % (width - 2)) + 1;
  fruitY = (rand() % (height - 2)) + 1;
  length = 1;
  score = 0;
}

void Draw() {
  system("cls");
  // top wall
  for(int i = 0; i < width; i++)
    cout << "#";
  cout << endl;

  // left and right walls, middle empty area, the fruit 'F' and the snake 'oooooO'
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {

      if ( j == 0 || j == (height - 1))
        cout << "#";
      else if (i == fruitY && j == fruitX)
        cout << "F";
      else if (i == snake[0][1] && j == snake[0][0])
        cout << "O";
      else {
        int flag = 0;
        for (int k = 0; k < length; k++) {
          if (i == snake[k][1] && j == snake[k][0]) {
            cout << "o";
            flag = 1;
          }
        }
        if (flag == 0)
          cout << " ";
      }

    }
    cout << endl;
  }

  // bottom wall
  for(int i = 0; i < width; i++)
    cout << "#";

  cout << endl << "Score " << score << endl;
}

void Input() {
  if (_kbhit()) {
    switch(_getch()) {
      case 'a':
        if (previous != RIGHT) {
          dir = LEFT;
          previous = dir;
        }
        break;
      case 'w':
        if (previous != DOWN) {
          dir = UP;
          previous = dir;
        }
        break;
      case 's':
        if (previous != UP) {
          dir = DOWN;
          previous = dir;
        }
        break;
      case 'd':
        if (previous != LEFT) {
          dir = RIGHT;
          previous = dir;
        }
        break;
      case 'x':
        gameOver = true;
        break;
    }
  }
}

void Logic() {
  switch(dir) {
    case LEFT:
      for (int i = (length - 1); i > 0; i--) {
        snake[i][0] = snake[i-1][0];
        snake[i][1] = snake[i-1][1];
      }
      snake[0][0]--;
      break;
    case UP:
      for (int i = (length - 1); i > 0; i--) {
        snake[i][0] = snake[i-1][0];
        snake[i][1] = snake[i-1][1];
      }
      snake[0][1]--;
      break;
    case DOWN:
      for (int i = (length - 1); i > 0; i--) {
        snake[i][0] = snake[i-1][0];
        snake[i][1] = snake[i-1][1];
      }
      snake[0][1]++;
      break;
    case RIGHT:
      for (int i = (length - 1); i > 0; i--) {
        snake[i][0] = snake[i-1][0];
        snake[i][1] = snake[i-1][1];
      }
      snake[0][0]++;
      break;
  }
  for (int i = 1; i < length; i++) {
    if (snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1]) {
      gameOver = true;
      overReason = 1;
      return;
    }
  }
  if (snake[0][0] == (width - 1) || snake[0][0] == 0 || snake[0][1] == (height) || snake[0][1] < 0) {
    gameOver = true;
    overReason = 2;
  }
  if (snake[0][0] == fruitX && snake[0][1] == fruitY) {
    score += 10;

    // find the new values of fruitx and fruity that do not overlap with the snake
    int flag = 0;
    while (true) {
      fruitX = (rand() % (width - 2)) + 1;
      fruitY = (rand() % (height - 2)) + 1;
      flag = 0;
      for (int i = 0; i < length; i++) {
        if (snake[i][0] == fruitX && snake[i][1] == fruitY) {
          flag = 1;
          break;
        }
      }
      if (flag == 0)
        break;
    }

    switch(dir) {
      case LEFT:
        snake[length][0] = snake[length - 1][0] + 1;
        snake[length][1] = snake[length - 1][1];
        break;
      case RIGHT:
        snake[length][0] = snake[length - 1][0] - 1;
        snake[length][1] = snake[length - 1][1];
        break;
      case UP:
        snake[length][0] = snake[length - 1][0];
        snake[length][1] = snake[length - 1][1] + 1;
        break;
      case DOWN:
        snake[length][0] = snake[length - 1][0] + 1;
        snake[length][1] = snake[length - 1][1] - 1;
        break;
    }
    length++;
    if (length == height * width) {
      gameComplete = true;
      return;
    }
  }
}

int main() {
  Setup();
  while(!gameOver) {
    Draw();
    Input();
    Logic();
    Sleep(100); //to slow down the game
  }
  if (gameOver) {
    if (overReason == 1)
      cout << "Oops...the snake bit itself :(" << endl;
    else
      cout << "Oops...the snake hit the wall :(" << endl;
    cout << "GAME OVER";
  }
  else if (gameComplete)
    cout << "GAME COMPLETE , YOU WIN !! :)";
  return 0;
}
