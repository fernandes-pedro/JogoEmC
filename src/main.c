#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "game.h"  
#include <stdlib.h>
#include <time.h>

int main() {
    Paddle player1 = {1, HEIGHT / 2 - 1, 0};
    Paddle player2 = {WIDTH - 2, HEIGHT / 2 - 1, 0};
    Ball ball = {WIDTH / 2, HEIGHT / 2, 1, 1};

    screenInit(1);        
    keyboardInit();       
    timerInit(100);       
    srand(time(NULL));    

    while (1) {
        screenDrawGame(&player1, &player2, &ball);  
        move_ball(&ball, &player1, &player2);       

        
        if (keyhit()) {
            int ch = readch();
            if (ch == 'w') move_paddle(&player1, -1);
            if (ch == 's') move_paddle(&player1, 1);
            if (ch == 'i') move_paddle(&player2, -1);
            if (ch == 'k') move_paddle(&player2, 1);
            if (ch == 'q') break; 
        }

       
        while (!timerTimeOver());
    }

    screenDestroy();      
    keyboardDestroy();    
    return 0;
}
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "game.h"  
#include <stdlib.h>
#include <time.h>

int main() {
    Paddle player1 = {1, HEIGHT / 2 - 1, 0};
    Paddle player2 = {WIDTH - 2, HEIGHT / 2 - 1, 0};
    Ball ball = {WIDTH / 2, HEIGHT / 2, 1, 1};

    screenInit(1);        
    keyboardInit();      
    timerInit(100);       
    srand(time(NULL));    

    while (1) {
        screenDrawGame(&player1, &player2, &ball);  
        move_ball(&ball, &player1, &player2);       

    
        if (keyhit()) {
            int ch = readch();
            if (ch == 'w') move_paddle(&player1, -1);
            if (ch == 's') move_paddle(&player1, 1);
            if (ch == 'i') move_paddle(&player2, -1);
            if (ch == 'k') move_paddle(&player2, 1);
            if (ch == 'q') break; 
        }

      
        while (!timerTimeOver());
    }

    screenDestroy();      
    keyboardDestroy();    
    return 0;
}
