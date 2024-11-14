#include "game.h"
#include "screen.h"
#include <stdlib.h>

void move_ball(Ball *ball, Paddle *p1, Paddle *p2) {
    ball->x += ball->dx;
    ball->y += ball->dy;

    // Colisão com o topo e fundo
    if (ball->y <= 0 || ball->y >= HEIGHT - 1) {
        ball->dy *= -1;
    }

    // Colisão com as paletas
    if ((ball->x == p1->x + 1 && ball->y >= p1->y && ball->y < p1->y + PADDLE_HEIGHT) ||
        (ball->x == p2->x - 1 && ball->y >= p2->y && ball->y < p2->y + PADDLE_HEIGHT)) {
        ball->dx *= -1;  // Inverte a direção horizontal
    }

    // Se a bola sair pela lateral
    if (ball->x <= 0 || ball->x >= WIDTH - 1) {
        ball->x = WIDTH / 2;
        ball->y = HEIGHT / 2;
        ball->dx = (rand() % 2 == 0) ? 1 : -1;  // A direção da bola será aleatória
        ball->dy = (rand() % 2 == 0) ? 1 : -1;
    }
}

void move_paddle(Paddle *paddle, int direction) {
    paddle->y += direction;

    // Limita o movimento da paleta dentro da tela
    if (paddle->y < 0) paddle->y = 0;
    if (paddle->y > HEIGHT - PADDLE_HEIGHT) paddle->y = HEIGHT - PADDLE_HEIGHT;
}

void screenDrawGame(Paddle *p1, Paddle *p2, Ball *ball) {
    // Desenha as paletas
    for (int i = 0; i < PADDLE_HEIGHT; i++) {
        screenGotoxy(p1->x, p1->y + i);
        printf("#");
        screenGotoxy(p2->x, p2->y + i);
        printf("#");
    }

    // Desenha a bola
    screenGotoxy(ball->x, ball->y);
    printf("O");

    screenUpdate();  // Atualiza a tela imediatamente
}
