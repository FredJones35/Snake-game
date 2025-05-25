#include "stdlib.h"
#include "time.h"
#include <stdbool.h>
#include "stdio.h"
#include "conio.h"
#include "snake.h"
#define GRID_ROW_SIZE 30
#define GRID_COL_SIZE 60
#define MAX_SNAKE_LENGTH 100
#define SNAKE_HEAD_INDEX 0
#define SNAKE_HEAD 'O'
#define SNAKE_BODY 'o'
#define FOOD '*'
#define DEFAULT_FOOD_X 27;
#define DEFAULT_FOOD_Y 15;
#define INITIAL_SCORE 0;
int score = INITIAL_SCORE;
struct food_coordinates{
    int x;
    int y;
};
typedef struct food_coordinates food_coordinates;
food_coordinates foodCoord;
enum global_food_condition {EXISTS, EATEN};
enum global_food_condition globalFoodCondition = EXISTS;
enum direction {UP, DOWN, RIGHT, LEFT};
enum direction current_direction = RIGHT;
int x_coordinate[MAX_SNAKE_LENGTH];
int y_coordinate[MAX_SNAKE_LENGTH];
char gamegrid[GRID_ROW_SIZE][GRID_COL_SIZE];
int snake_lenght = 2;
void initiate_srand(){
    srand(time(NULL));
}
void setGamegrid(){
    for (int row = 0; row < GRID_ROW_SIZE; ++row) {
        for (int col = 0; col < GRID_COL_SIZE; ++col) {
            if(row == 0 || row == GRID_ROW_SIZE-1 || col == 0 || col == GRID_COL_SIZE-1){
                gamegrid[row][col] = '#';
            }else{
                gamegrid[row][col] = ' ';
            }
        }
    }
}
void printGame(){
    for (int row = 0; row < GRID_ROW_SIZE; ++row) {
        for (int col = 0; col < GRID_COL_SIZE; ++col) {
            printf("%c",gamegrid[row][col]);
        }
        printf("\n");
    }
}
void initiateSnake(){
    x_coordinate[SNAKE_HEAD_INDEX] = 30;
    y_coordinate[SNAKE_HEAD_INDEX] = 15;
    x_coordinate[SNAKE_HEAD_INDEX+1] = 31;
    y_coordinate[SNAKE_HEAD_INDEX+1] = 15;
    /*
    x_coordinate[SNAKE_HEAD_INDEX+2] = 32;
    y_coordinate[SNAKE_HEAD_INDEX+2] = 15;
    x_coordinate[SNAKE_HEAD_INDEX+3] = 33;
    y_coordinate[SNAKE_HEAD_INDEX+3] = 15;
    x_coordinate[SNAKE_HEAD_INDEX+4] = 34;
    y_coordinate[SNAKE_HEAD_INDEX+4] = 15;
    */
}
void set_snake_on_grid(){
    gamegrid[y_coordinate[SNAKE_HEAD_INDEX]][x_coordinate[SNAKE_HEAD_INDEX]] = SNAKE_HEAD;
    for (int i = 1; i < snake_lenght; ++i) {
        gamegrid[y_coordinate[i]][x_coordinate[i]] = SNAKE_BODY;
    }
}
void moveSnake(){
    for (int i = snake_lenght; i > SNAKE_HEAD_INDEX; --i) {
        x_coordinate[i] = x_coordinate[i-1];
        y_coordinate[i] = y_coordinate[i-1];
    }
    if(current_direction == RIGHT){
        x_coordinate[SNAKE_HEAD_INDEX] -= 1;
    }else if(current_direction == LEFT){
        x_coordinate[SNAKE_HEAD_INDEX] += 1;
    }else if(current_direction == UP){
        y_coordinate[SNAKE_HEAD_INDEX] -= 1;
    }else if(current_direction == DOWN){
        y_coordinate[SNAKE_HEAD_INDEX] += 1;
    }
}
void getInput(){
    if(kbhit()){//check if a key has been pressed
        char c = (char)getch();
        if(c == 'w'){
            current_direction = (current_direction != DOWN) ? UP : DOWN;
        }
        if(c == 's'){
            current_direction = (current_direction != UP) ? DOWN : UP;
        }
        if(c == 'a'){
            current_direction = (current_direction != LEFT) ? RIGHT : LEFT;
        }
        if(c == 'd'){
            current_direction = (current_direction != RIGHT) ? LEFT : RIGHT;
        }
    }
}
bool isEdge(int row, int col){
    if((row==0 || row==GRID_ROW_SIZE-1) || (col==0 || col==GRID_COL_SIZE-1)){
        return true;
    }
    return false;
}
bool isSelf(int row, int col){
    for (int i = 1; i < snake_lenght; ++i) {
        if(row == y_coordinate[i] && col == x_coordinate[i]){
            return true;
        }
    }
    return false;
}
bool is_on_snake(){
    for (int i = 0; i < snake_lenght; ++i) {
        if (foodCoord.x == x_coordinate[i] && foodCoord.y == y_coordinate[i]){
            return true;
        }
    }
    return false;
}
bool isRunning(){
    if(isEdge(y_coordinate[SNAKE_HEAD_INDEX],x_coordinate[SNAKE_HEAD_INDEX])|| isSelf(y_coordinate[SNAKE_HEAD_INDEX],x_coordinate[SNAKE_HEAD_INDEX])){
        return false;
    }
    return true;
}
void update_food_condition(){
    if(foodCoord.x == x_coordinate[SNAKE_HEAD_INDEX] && foodCoord.y == y_coordinate[SNAKE_HEAD_INDEX]){
        globalFoodCondition = EATEN;
    }
    else{
        globalFoodCondition = EXISTS;
    }
}
void set_food_on_grid(){
    if(globalFoodCondition == EATEN){
        do {
            foodCoord.x = (rand() % GRID_COL_SIZE-1) - 1;
            foodCoord.y = (rand() % GRID_ROW_SIZE-1) - 1;
        } while (is_on_snake());
    }
    gamegrid[foodCoord.y][foodCoord.x] = FOOD;
}
void init_food(){
    foodCoord.x = DEFAULT_FOOD_X;
    foodCoord.y = DEFAULT_FOOD_Y;
}
void grow_snake(){
    if (globalFoodCondition == EATEN){
        x_coordinate[snake_lenght] = x_coordinate[snake_lenght-1];
        y_coordinate[snake_lenght] = y_coordinate[snake_lenght-1];
        snake_lenght+=1;
    }
}
void update_score(){
    if (globalFoodCondition == EATEN){
        score+=10;
    }
}
void print_score(){
    printf("SCORE: %d", score);
}