/* <2048 double side>
Copyright (C) <2022>  <Muxuan Li>*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <termio.h>
#define clear() cout << "\033c" << flush
using namespace std;

int rd = 0;

class Board2048
{
public:
  int id = 1;
  int num[10][10];
  bool validMove = false;
  bool winorlost = false;
  
  void MoveUp() {
    validMove = false;
    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
  
        bool merge = false;
        if (num[i][j] != 0) {
          for (int k = i; k >= 2; k--) {
            if (num[k][j] == num[k - 1][j] && !merge) {
              num[k - 1][j] *= 2;
              num[k][j] = 0;
              merge = true;
              validMove = true;
            } else if (num[k - 1][j] == 0) {
              num[k - 1][j] = num[k][j];
              num[k][j] = 0;
              validMove = true;
            } else
              break;
          }
        }
      }
    }
  }
  
  void MoveDown() {
    validMove = false;
    for (int i = 4; i >= 1; i--) {
      for (int j = 1; j <= 4; j++) {
        bool merge = false;
        if (num[i][j] != 0) {
          for (int k = i; k <= 3; k++) {
            if (num[k][j] == num[k + 1][j] && !merge) {
              num[k + 1][j] *= 2;
              num[k][j] = 0;
              merge = true;
              validMove = true;
            } else if (num[k + 1][j] == 0) {
              num[k + 1][j] = num[k][j];
              num[k][j] = 0;
              validMove = true;
            } else
              break;
          }
        }
      }
    }
  }
  
  void MoveRight() {
    validMove = false;
    for (int i = 1; i <= 4; i++) {
      for (int j = 4; j >= 1; j--) {
        bool merge = false;
        if (num[i][j] != 0) {
          for (int k = j; k <= 3; k++) {
            if (num[i][k] == num[i][k + 1] && !merge) {
              num[i][k + 1] *= 2;
              num[i][k] = 0;
              merge = true;
              validMove = true;
            } else if (num[i][k + 1] == 0) {
              num[i][k + 1] = num[i][k];
              num[i][k] = 0;
              validMove = true;
            } else
              break;
          }
        }
      }
    }
  }
  
  void MoveLeft() {
    validMove = false;
    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
        bool merge = false;
        if (num[i][j] != 0) {
          for (int k = j; k >= 2; k--) {
            if (num[i][k] == num[i][k - 1] && !merge) {
              num[i][k - 1] *= 2;
              num[i][k] = 0;
              merge = true;
              validMove = true;
            } else if (num[i][k - 1] == 0) {
              num[i][k - 1] = num[i][k];
              num[i][k] = 0;
              validMove = true;
            } else
              break;
          }
        }
      }
    }
  }
  

  void full() {
    int x[20] = {}, y[20] = {}, cur = 0;
    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
        if (num[i][j] == 0) {
          cur++;
          x[cur] = i;
          y[cur] = j;
        }
      }
    }
  
    if (cur > 0) {
      srand(time(0)*id);
      int cc = rand() % cur + 1;
      int v = (rand() % 2 + 1) * 2;
      num[x[cc]][y[cc]] = v;
    }
    cout << "\033c" << flush;
  }
  void checkonnum() {
    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
        if (num[i][j] >= 2048){
          winorlost = true;
          return;
        }
      }
    }
  }

  void drawBoard() {
    if (winorlost == true){
      cout << "status: win" <<endl;
      }
    else{
      cout << "status: ongoing" <<endl;
    }
      cout << "  ╔";
    for (int i = 1; i <= 4 - 1; i++)
      cout << "════╤";
    cout << "════╗\n";
  
    for (int i = 1; i <= 4; i++) {
      cout << "  ║";
      for (int j = 1; j <= 4; j++) {
        if (num[i][j] > 0) {
          cout << setw(4) << num[i][j];
        } else
          cout << "    ";
        if (j != 4)
          cout << "│";
        else
          cout << "║";
      }
      cout << " \n";
  
      if (i != 4) {
        cout << "  ╟";
        for (int i = 1; i <= 4 - 1; i++)
          cout << "────┼";
        cout << "────╢\n";
      } else {
        cout << "  ╚";
        for (int i = 1; i <= 4 - 1; i++)
          cout << "════╧";
        cout << "════╝\n";
      }
    }
  }
  

  bool gameOver() {
    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
        if (num[i][j] == 0)
          return false;
        if (i > 1) {
          if (num[i - 1][j] == num[i][j])
            return false;
        }
        if (j > 1) {
          if (num[i][j - 1] == num[i][j])
            return false;
        }
      }
    }
  
    return true;
  }
};
Board2048 board1;
Board2048 board2;

void Lose() {
  cout << "**********************************" << endl;
  cout << "——————————— ROUND:" << rd << " ————————————" << endl;
  cout << "——————————— player lost！ ———————" << endl;
  cout << "**********************************" << endl << endl;
  exit(0);
}

void Win() {
  cout << "**********************************" << endl;
  cout << "——————————— ROUND:" << rd << " ————————————" << endl;
  cout << "——————————— player wins！ ———————" << endl;
  cout << "**********************************" << endl << endl;
  exit(0);
}


int getch() {
  struct termios nts, ots;

  if (tcgetattr(0, &ots) < 0)
    return EOF;

  nts = ots;
  cfmakeraw(&nts);

  if (tcsetattr(0, TCSANOW, &nts) < 0)
    return EOF;

  int cr;
  cr = getchar();
  if (tcsetattr(0, TCSANOW, &ots) < 0)
    return EOF;
  return cr;
}

void game() {
  cout << "\033c" << flush;
  cout << "**********************************" << endl;
  cout << "—————————— Ready Go～ ————————————" << endl;
  cout << "**********************************" << endl;
  board1.drawBoard();
  board2.drawBoard();

  char ch = 0;
  while (!board1.gameOver() && !board2.gameOver()) {
    cout << "Tips：" << endl;
    cout << "w —— move up, ";
    cout << "s —— move down ";
    cout << "a —— move left " << endl;
    cout << "d —— move right ";
    cout << "e —— exit the game ";
    cout << "r —— new game" << endl;
    cout << "Select the above command" << endl;

    ch = getch();
    rd++;
    if (ch == 'w') {
      board1.MoveUp();
      board2.MoveUp();
    }
    else if (ch == 's') {
      board1.MoveDown();
      board2.MoveDown();
    }
    else if (ch == 'a') {
      board1.MoveLeft();
      board2.MoveLeft();
    }
    else if (ch == 'd') {
      board1.MoveRight();
      board2.MoveRight();
    }
    else if (ch == 'e') 
      exit(0);
    
    else if (ch == 'r') {
      rd = 0;
      memset(board1.num, 0, sizeof(board1.num));
      memset(board2.num, 0, sizeof(board2.num));
      return;
    } else {
      cout << endl
           << "———————Incorrect input, please re-enter the command———————-"
           << endl
           << endl;
      continue;
    }
    if (board1.validMove)
      board1.full();
    if (board2.validMove)
      board2.full();
    cout << "\033c" << flush;
    board1.drawBoard();
    board2.drawBoard();
  }
  if (board1.winorlost == true || board2.winorlost == true)
    Win();
  else
    Lose();
}

void intro() {
  cout << "***********************************************************" << endl;
  cout << "Welcome to the 2048 game~" << endl;
  cout << "In this game there will be a 4*4 table, in each square will "
          "randomly generate 2 or 4."
       << endl;
  cout << "You can choose w, s, a, d, slide up and down, left and right, if "
          "you encounter the same number, multiply the number by 2."
       << endl;
  cout << "When all 16 squares are full and you can no longer slide, the game "
          "is over!"
       << endl;
  cout << "1. When any number exceeds 2048, the player wins!" << endl;
  cout << "2. When all number is less than 2048, the game fails!"
       << endl;
  cout << "Click【ENTER】to start the game" << endl;
  cout << "Click【ESC】to exit the game" << endl;
  cout << "***********************************************************" << endl;
}



int main() {
  board1.id = 1;
  board2.id = 2;

  while (true) {
    intro();
    char ch;
    ch = getch();
    if (ch == '\r') {
      board1.full();
      board2.full();
      game();
    } else if (ch == 27) {
      cout << "Exit the game successfully!" << endl;
      break;
    } else
      cout << "Incorrect input, please input again." << endl;
  }
  return 0;
}
