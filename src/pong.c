#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../include/keyboard.h"
#include "../include/timer.h"
#include "../include/screen.h"

#define WIDTH 40
#define HEIGHT 20
#define PADDLE_HEIGHT 3

typedef struct {
    int x, y;
    int dy; 
} Paddle;

typedef struct {
    int x, y;
    int dx, dy; 
} Ball;

void initialize();
void draw(Paddle *p1, Paddle *p2, Ball *ball, int score1, int score2, int elapsed_time);
void move_ball(Ball *ball, Paddle *p1, Paddle *p2, int *score1, int *score2, int *speed, time_t *start_time);
void move_paddle(Paddle *paddle, int direction);

int main() {
    Paddle player1 = {1, HEIGHT / 2 - 1, 0};
    Paddle player2 = {WIDTH - 2, HEIGHT / 2 - 1, 0};
    Ball ball = {WIDTH / 2, HEIGHT / 2, 1, 1};
    int score1 = 0, score2 = 0;
    int speed = 100000; 
    time_t start_time = time(NULL);

    initialize();
    while (1) {
        time_t current_time = time(NULL);
        int elapsed_time = (int)(current_time - start_time);

        
        if (elapsed_time % 15 == 0 && elapsed_time != 0) {
            speed = (speed > 20000) ? speed - 10000 : 20000; 
        }

        clear();
        draw(&player1, &player2, &ball, score1, score2, elapsed_time);

        move_ball(&ball, &player1, &player2, &score1, &score2, &speed, &start_time);

        int ch = getch();
        if (ch == 'w') move_paddle(&player1, -1);
        if (ch == 's') move_paddle(&player1, 1);
        if (ch == 'i') move_paddle(&player2, -1);
        if (ch == 'k') move_paddle(&player2, 1);
        if (ch == 'q') break; 

        usleep(speed);
    }
    endwin();
    return 0;
}

void initialize() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    srand(time(NULL));
}

void draw(Paddle *p1, Paddle *p2, Ball *ball, int score1, int score2, int elapsed_time) {
    
    for (int i = 0; i < HEIGHT; i++) {
        mvprintw(i, 0, "|"); 
        mvprintw(i, WIDTH - 1, "|");  
    }
    for (int i = 0; i < WIDTH; i++) {
        mvprintw(0, i, "-");  
        mvprintw(HEIGHT - 1, i, "-");  
    }

   
    for (int i = 0; i < PADDLE_HEIGHT; i++) {
        mvprintw(p1->y + i, p1->x, "#");
        mvprintw(p2->y + i, p2->x, "#");
    }

    
    mvprintw(ball->y, ball->x, "O");

   
    mvprintw(HEIGHT, WIDTH / 2 - 10, "Player 1: %d | Player 2: %d | Time: %d s", score1, score2, elapsed_time);

    refresh();
}

void move_ball(Ball *ball, Paddle *p1, Paddle *p2, int *score1, int *score2, int *speed, time_t *start_time) {
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
        *speed = 100000;        
        *start_time = time(NULL); 
    }
    if (ball->x >= WIDTH - 1) {
        (*score1)++;  
        ball->x = WIDTH / 2;
        ball->y = HEIGHT / 2;
        ball->dx = (rand() % 2 == 0) ? 1 : -1;
        ball->dy = (rand() % 2 == 0) ? 1 : -1;
        *speed = 100000;        
        *start_time = time(NULL); 
    }
}

void move_paddle(Paddle *paddle, int direction) {
    paddle->y += direction;

    if (paddle->y < 1) paddle->y = 1;
    if (paddle->y > HEIGHT - PADDLE_HEIGHT - 1) paddle->y = HEIGHT - PADDLE_HEIGHT - 1;
}
