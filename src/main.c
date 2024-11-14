#include <stdlib.h>
#include <time.h>
#include "keyboard.h"
#include "screen.h"
#include "timer.h"

#define WIDTH 40
#define HEIGHT 20
#define PADDLE_HEIGHT 3
#define BALL_CHAR 'O'
#define PADDLE_CHAR '#'
#define BORDER_CHAR '*'

typedef struct {
    int x, y;
    int dy; 
} Paddle;

typedef struct {
    int x, y;
    int dx, dy; 
} Ball;

void initialize();
void draw(Paddle *p1, Paddle *p2, Ball *ball, int score1, int score2);
void move_ball(Ball *ball, Paddle *p1, Paddle *p2, int *score1, int *score2);
void move_paddle(Paddle *paddle, int direction);

int main() {
    Paddle player1 = {1, HEIGHT / 2 - 1, 0};
    Paddle player2 = {WIDTH - 2, HEIGHT / 2 - 1, 0};
    Ball ball = {WIDTH / 2, HEIGHT / 2, 1, 1};
    int score1 = 0, score2 = 0;

    
    keyboardInit();
    screenInit(1);  
    timerInit(100);  

    while (1) {
        
        screenClear();
        draw(&player1, &player2, &ball, score1, score2);

       
        move_ball(&ball, &player1, &player2, &score1, &score2);

        
        if (keyhit()) {
            int ch = readch();
            if (ch == 'w') move_paddle(&player1, -1);
            if (ch == 's') move_paddle(&player1, 1);
            if (ch == 'i') move_paddle(&player2, -1);
            if (ch == 'k') move_paddle(&player2, 1);
            if (ch == 'q') break;  
        }

        
        if (timerTimeOver()) {
            screenUpdate();
            timerUpdateTimer(100);  
        }
    }

    
    timerDestroy();
    screenDestroy();
    keyboardDestroy();
    return 0;
}

void draw(Paddle *p1, Paddle *p2, Ball *ball, int score1, int score2) {
    
    screenDrawBorders();

   
    for (int i = 0; i < PADDLE_HEIGHT; i++) {
        screenGotoxy(p1->x, p1->y + i);
        printf("%c", PADDLE_CHAR);
        screenGotoxy(p2->x, p2->y + i);
        printf("%c", PADDLE_CHAR);
    }

    
    screenGotoxy(ball->x, ball->y);
    printf("%c", BALL_CHAR);

  
    screenGotoxy(WIDTH / 4, 1);
    printf("Player 1: %d", score1);
    screenGotoxy(3 * WIDTH / 4 - 10, 1);
    printf("Player 2: %d", score2);
}

void move_ball(Ball *ball, Paddle *p1, Paddle *p2, int *score1, int *score2) {
    ball->x += ball->dx;
    ball->y += ball->dy;

    
    if (ball->y <= 1 || ball->y >= HEIGHT - 2) {
        ball->dy *= -1;
    }

   
    if ((ball->x == p1->x + 1 && ball->y >= p1->y && ball->y < p1->y + PADDLE_HEIGHT) ||
        (ball->x == p2->x - 1 && ball->y >= p2->y && ball->y < p2->y + PADDLE_HEIGHT)) {
        ball->dx *= -1; 
    }

  
    if (ball->x <= 0) {
        (*score2)++;
        ball->x = WIDTH / 2;
        ball->y = HEIGHT / 2;
        ball->dx = (rand() % 2 == 0) ? 1 : -1;
        ball->dy = (rand() % 2 == 0) ? 1 : -1;
    }

    if (ball->x >= WIDTH - 1) {
        (*score1)++;
        ball->x = WIDTH / 2;
        ball->y = HEIGHT / 2;
        ball->dx = (rand() % 2 == 0) ? 1 : -1;
        ball->dy = (rand() % 2 == 0) ? 1 : -1;
    }
}

void move_paddle(Paddle *paddle, int direction) {
    paddle->y += direction;

    if (paddle->y < 1) paddle->y = 1;
    if (paddle->y > HEIGHT - PADDLE_HEIGHT - 1) paddle->y = HEIGHT - PADDLE_HEIGHT - 1;
}
