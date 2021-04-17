#include <iostream>
#include "windows.h" 
#include <ctime>
#include <stdio.h>


int GRID_WIDTH = 40;
int GRID_HEIGHT = GRID_WIDTH/2;

//TODO: Flatten array
void print_grid_values(int **grid){
    for (int i = 0; i < GRID_HEIGHT; i++){
        for (int j = 0; j < GRID_WIDTH; j++){
            std::cout << grid[i][j] << ",";
        }
        std::cout << std::endl;
    }
    return;
}

void print_grid_ascii(int **grid){
    char ascii[10] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};
    std::string output = "";

    for (int i = 0; i < GRID_HEIGHT; i++){
        for (int j = 0; j < GRID_WIDTH; j++){
            // print char from " .:-=+*#%@" based on value from 0-9

            if ( 0 <= grid[i][j] && grid[i][j] < 10){
                output += ascii[grid[i][j]];
            }
            else {
                std::cout << "Error, invalid value: " << grid[i][j] << " Exiting:";
                exit(1);
            }
        }
        output += "\n";
    }
    std::cout << output << std::flush;
    return;
}

void point_increment(int **grid, int x, int y){
    
    int temp= 0;
    //TODO choose wrapping or ignoring for out of bounds indcies 
    // Wrapping
    temp = grid[y % GRID_HEIGHT][x % GRID_WIDTH];
    temp ++;
    grid[y % GRID_HEIGHT][x % GRID_WIDTH] = temp % 10;
    return;

    //Ignoring
    // if (0 <= x && x < GRID_WIDTH && 0 <= y && y < GRID_HEIGHT){
    //     grid[y][x]
    // }
    // return
}

void star_increment(int **grid, int x, int y){
    int temp= 0;
    //TODO choose wrapping or ignoring for out of bounds indcies 
    point_increment(grid, x-1,y);
    point_increment(grid, x,y-1);
    point_increment(grid, x,y);
    point_increment(grid, x+1,y);
    point_increment(grid, x,y+1);
    return;
}

int** init_grid(){
    int **grid;
    grid = new int *[GRID_HEIGHT];
    for(int i = 0; i < GRID_HEIGHT; i++){
        grid[i] = new int[GRID_WIDTH];
    }
    for (int i = 0; i < GRID_HEIGHT; i++){
        for (int j = 0; j < GRID_WIDTH; j++){
            grid[i][j] = 0;
        }
    }
    return grid;
}



int main() {

    int **grid = init_grid();
    int x_1,x_2,y_1,y_2 = 0;

    std::srand((unsigned) time(0));



    print_grid_values(grid);
    print_grid_ascii(grid);
     
    std::cout << "Hit enter to simulate:" << std::endl;
    std::cin.ignore();
    x_1 = x_2 = rand() % GRID_WIDTH;
    y_1 = y_2 = rand() % GRID_HEIGHT;

    for (int i = 0; i < 1000; i++){
        printf("\033[2J");
        printf("\033[%d;%dH", 0, 0);


        point_increment(grid, x_1,y_1);

        star_increment(grid, x_2,y_2);
        print_grid_ascii(grid);
        //print_grid_values(grid);
        x_1++;
        y_1++;
        x_2 += 5;
        y_2 +=2;
        Sleep(10);

    }
    
    return 0;

}