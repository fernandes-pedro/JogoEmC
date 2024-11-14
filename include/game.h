#ifndef __GAME_H__
#define __GAME_H__

#define WIDTH 40
#define HEIGHT 20
#define PADDLE_HEIGHT 3

typedef struct {
    int x, y;
    int dy; // Direção do movimento vertical da paleta
} Paddle;

typedef struct {
    int x, y;
    int dx, dy; // Direção do movimento da bola
} Ball;

// Funções do jogo
void move_ball(Ball *ball, Paddle *p1, Paddle *p2);
void move_paddle(Paddle *paddle, int direction);
void screenDrawGame(Paddle *p1, Paddle *p2, Ball *ball);

#endif /* __GAME_H__ */
