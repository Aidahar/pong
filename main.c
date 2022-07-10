// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI
#include <stdio.h>

const int Bottom = 25;
const int Border = 80;
const int LeftRocket_x = 1;
const int RightRocket_x = 78;
const int speedBall = 1;

void gameField(void);
void printScore(int pl);
int leftRocket(int y, int leftRocketY);
int rightRocket(int y, int rightRocketY);
int ballPosition(int x, int y, int ballX, int ballY);
int moveRocket(int y_l, int y_r, char c);
int ballChangeOrient(int bolOrient, int ballX, int ballY, int leftRocketY,
                     int rightRocketY);
int moveBall(int bolOrient, int ballX, int ballY);

int main(void) {
  gameField();
  return 0;
}

void gameField(void) {
  int leftRocketY = 13;
  int rightRocketY = 13;
  int ballX = 39, ballY = 13;
  char input = '\n';
  int pos = 0;
  int bolOrient = 10;
  unsigned short playerOne = 0;
  unsigned short playerTwo = 0;

  while (input != 'q' && playerOne < 21 && playerTwo < 21) {
    for (int y = 0; y < Bottom; y++) {
      for (int x = 0; x < Border; x++) {
        if (y == 0 && x == 37) {
          printf("%d:%d", playerOne, playerTwo);
          if (playerOne >= 10 && playerTwo >= 10) {
            x += 4;
          } else if (playerOne >= 10 || playerTwo >= 10) {
            x += 3;
          } else {
            x += 2;
          }
        } else if (y == 0 || y == 24) {
          printf("-");
        } else if (x == 0 || x == 79) {
          printf("|");
        } else if (x == LeftRocket_x) {
          if ((leftRocket(y, leftRocketY) == 0) &&
              (ballPosition(x, y, ballX, ballY) == 0)) {
            printf(" ");
          }
        } else if (x == RightRocket_x) {
          if ((rightRocket(y, rightRocketY) == 0) &&
              (ballPosition(x, y, ballX, ballY) == 0)) {
            printf(" ");
          }
        } else if (ballPosition(x, y, ballX, ballY) == 0) {
          printf(" ");
        }
      }
      printf("\n");
    }
    scanf("%c", &input);
    pos = moveRocket(leftRocketY, rightRocketY, input);
    if ((ballX != 1 && ballY != leftRocketY + 1 && ballY != leftRocketY - 1) ||
        (ballX != 1 && ballY != rightRocketY + 1 &&
         ballY != rightRocketY - 1)) {
      if (pos / 100 < 23 && pos / 100 > 1) {
        leftRocketY = pos / 100;
      }
      if (pos % 100 < 23 && pos % 100 > 1) {
        rightRocketY = pos % 100;
      }
    }
    //      printf("%d\n", bolOrient);
    bolOrient =
        ballChangeOrient(bolOrient, ballX, ballY, leftRocketY, rightRocketY);
    pos = moveBall(bolOrient, ballX, ballY);
    ballX = pos / 100;
    ballY = pos % 100;
    if (ballX == 1) {
      playerTwo++;
    } else if (ballX == 78) {
      playerOne++;
    }
    printf("\033[H\033[J");
  }
  if (playerOne == 21) {
    printScore(playerOne);
  } else if (playerTwo == 21) {
    printScore(playerOne);
  }
}
int leftRocket(int y, int leftRocketY) {
  if (y == leftRocketY || y == leftRocketY + 1 || y == leftRocketY - 1) {
    printf("X");
    return 1;
  }
  return 0;
}

int rightRocket(int y, int rightRocketY) {
  if (y == rightRocketY || y == rightRocketY + 1 || y == rightRocketY - 1) {
    printf("X");
    return 1;
  }
  return 0;
}
int ballPosition(int x, int y, int ballX, int ballY) {
  if ((y == ballY) && (x == ballX)) {
    printf("*");
    return 1;
  }
  return 0;
}
int moveRocket(int y_l, int y_r, char c) {
  if (c == 'A' || c == 'a') {
    y_l--;
  } else if (c == 'Z' || c == 'z') {
    y_l++;
  } else if (c == 'K' || c == 'k') {
    y_r--;
  } else if (c == 'M' || c == 'm') {
    y_r++;
  }
  int sdf = y_l * 100 + y_r;
  return sdf;
}
int ballChangeOrient(int bolOrient, int ballX, int ballY, int leftRocketY,
                     int rightRocketY) {
  //   printf("BEFORE bolOrient = %d, ballX = %d, ballY= %d, leftRocketY = %d,
  //   rightRocketY = %d\n", bolOrient, ballX, ballY, leftRocketY,
  //   rightRocketY);
  if ((ballX == 1) || (ballX == 78)) {
    if (bolOrient / 10 == 1) {
      bolOrient -= 10;
    } else {
      bolOrient += 10;
    }
  }
  if ((ballY == 1) || (ballY == 23)) {
    if (bolOrient % 10 == 1) {
      bolOrient--;
    } else {
      bolOrient++;
    }
  }
  if (ballX == LeftRocket_x + 1 && bolOrient / 10 == 0) {
    if ((ballY == leftRocketY + 1) || (ballY == leftRocketY) ||
        (ballY == leftRocketY - 1)) {
      bolOrient += 10;
    }
    if ((ballY == leftRocketY + 2 && bolOrient % 10 == 0) ||
        (ballY == leftRocketY - 2 && bolOrient % 10 == 1)) {
      bolOrient += 10;
    }
  }
  if (ballX == RightRocket_x - 1 && bolOrient / 10 == 1) {
    if ((ballY == rightRocketY + 1) || (ballY == rightRocketY) ||
        (ballY == rightRocketY - 1)) {
      bolOrient -= 10;
    }
    if ((ballY == leftRocketY + 2 && bolOrient % 10 == 0) ||
        (ballY == leftRocketY - 2 && bolOrient % 10 == 1)) {
      bolOrient -= 10;
    }
  }
  return bolOrient;
}

int moveBall(int bolOrient, int ballX, int ballY) {
  int cord;
  if (bolOrient == 00) {
    ballX -= speedBall;
    ballY -= speedBall;
  } else if (bolOrient == 11) {
    ballX += speedBall;
    ballY += speedBall;
  } else if (bolOrient == 01) {
    ballX -= speedBall;
    ballY += speedBall;
  } else if (bolOrient == 10) {
    ballX += speedBall;
    ballY -= speedBall;
  }
  return cord = ballX * 100 + ballY;
}
void printScore(int pl) { printf("%d", pl); }
