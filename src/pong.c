#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 40
#define HEIGHT 20
#define PADDLE_HEIGHT 3
#define PADDLE_WIDTH 1

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

    initialize();

    while (1) {
        clear();
        draw(&player1, &player2, &ball, score1, score2);

        move_ball(&ball, &player1, &player2, &score1, &score2);

        int ch = getch();
        if (ch == 'w') move_paddle(&player1, -2);
        if (ch == 's') move_paddle(&player1, 2);
        if (ch == 'i') move_paddle(&player2, -2);
        if (ch == 'k') move_paddle(&player2, 2);
        if (ch == 'q') break; 

        usleep(100000);
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

void draw(Paddle *p1, Paddle *p2, Ball *ball, int score1, int score2) {
   
    for (int i = 0; i < WIDTH; i++) {
        mvprintw(0, i, "-"); 
        mvprintw(HEIGHT - 1, i, "-"); 
    }
    for (int i = 0; i < HEIGHT; i++) {
        mvprintw(i, 0, "|"); 
        mvprintw(i, WIDTH - 1, "|"); 
    }

 
    for (int i = 0; i < PADDLE_HEIGHT; i++) {
        mvprintw(p1->y + i, p1->x, "|"); 
        mvprintw(p2->y + i, p2->x, "|"); 
    }

   
    mvprintw(ball->y, ball->x, "O");

    mvprintw(1, WIDTH + 2, "Player 1: %d", score1);
    mvprintw(2, WIDTH + 2, "Player 2: %d", score2);

    refresh();
}

void move_ball(Ball *ball, Paddle *p1, Paddle *p2, int *score1, int *score2) {
    ball->x += ball->dx;
    ball->y += ball->dy;

   
    if (ball->y <= 0 || ball->y >= HEIGHT - 1) {
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

    if (paddle->y < 0) paddle->y = 0;
    if (paddle->y > HEIGHT - PADDLE_HEIGHT) paddle->y = HEIGHT - PADDLE_HEIGHT;
}
