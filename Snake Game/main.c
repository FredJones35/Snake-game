#include <stdio.h>
#include <stdbool.h>
#include "snake.h"
#include "windows.h"
void display_game(){
    while(isRunning()){
        getInput();
        moveSnake();
        update_food_condition();
        setGamegrid();
        set_snake_on_grid();
        set_food_on_grid();
        grow_snake();
        update_score();
        printGame();
        print_score();
        Sleep(500);
        system("cls");
    }
}

int main() {
    //initial conditions for game
    initiate_srand();
    setGamegrid();
    initiateSnake();
    init_food();
    // main game loop
    display_game();

    return 0;
}
