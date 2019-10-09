#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu();
void start();

char** initGrid(int rows, int cols, int doubleLetters, int tripleLetters, int doubleWords, int tripleWords, int negative);
char** fillGridWith(int rows, int cols, char**grid, char letter, int caseNumber);

void freeDoubleArray(int rows, int cols, char **array);
void delay();

// Affichage
void printGrid(int rows, int cols, char** grid);
void printGridLine(int cols);
void printAllocError();

int main(int argc, char ** argv){
    menu();
    system("pause");
    return 0;
}


void menu(){
    int menuBool = 1;

    do{
        printf( "=========================================================\n"
                "                   BIENVENUE AU CRABBLE\n"
                "=========================================================\n\n"
                "Taper :\n"
                "   1) Pour jouer\n"
                "   2) Pour quitter\n"
                );

        fflush(stdin);
        scanf("%d", &menuBool);

        while(menuBool != 1 && menuBool != 2){
            system("cls");
            printf("Taper 1 ou 2");
            fflush(stdin);
            scanf("%d", &menuBool);
        }

        if(menuBool == 1){
            start();
        }
    }while(menuBool != 2);
}

void start(){
    char **grid = NULL;
    int rows, cols, doubleLetters, tripleLetters, doubleWords, tripleWords, negative;

    // A SCANNER ET VERIFIER
    // =======================
    rows = 6;
    cols = 6;
    doubleLetters = 1;
    tripleLetters = 1;
    doubleWords = 1;
    tripleWords = 1;
    negative = 1;
    // =======================

    grid = initGrid(rows, cols, doubleLetters, tripleLetters, doubleWords, tripleWords, negative);

    system("cls");
    printGrid(rows, cols, grid);
    printf("\nJOUER !!! ");
    
    system("pause");

    freeDoubleArray(rows, cols, grid);
}

char** initGrid(int rows, int cols, int doubleLetters, int tripleLetters, int doubleWords, int tripleWords, int negative){
    int i, j;
    char ** grid = NULL;

    grid = malloc(sizeof(char*) * rows);
    if(!grid){
        printAllocError();
    }

    for(i = 0; i < rows; i++){
        grid[i] = malloc(sizeof(char) * cols);
        if(!grid[i]){
            printAllocError();
        }
    }

    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            grid[i][j] = 32; // ESPACE
        }
    }

    // Remplir la grille avec les cases spéciales
    grid = fillGridWith(rows, cols, grid, 49, doubleLetters);
    grid = fillGridWith(rows, cols, grid, 50, tripleLetters);
    grid = fillGridWith(rows, cols, grid, 51, doubleWords);
    grid = fillGridWith(rows, cols, grid, 52, tripleWords);
    grid = fillGridWith(rows, cols, grid, 45, negative);
    grid = fillGridWith(rows, cols, grid, 42, 1);
    return grid;
}

char** fillGridWith(int rows, int cols, char**grid, char letter, int caseNumber){
    int i, j, x, y, hasChanged;
    time_t timeForRandom;

    // Initialise le générateur aléatoire sur le temps
    srand((unsigned) time(&timeForRandom));

    while(caseNumber > 0){
        do{
            hasChanged = 0;
            if(letter == 45){
                // Modifier le générateur aléatoire pour ne pas avoir toujours les mêmes case négatives
                delay();
                srand((unsigned) time(&timeForRandom));
            }
            y = rand() % rows;
            x = rand() % cols;

            if(grid[y][x] == 32){
                grid[y][x] = letter;
                caseNumber--;
                hasChanged = 1;
            }else if(letter == 45 && grid[y][x] != 32 && grid[y][x] != 45 && grid[y][x] != 42){
                grid[y][x] = grid[y][x] + 4;
                caseNumber--;
                hasChanged = 1;
            }
        }while(hasChanged == 0);
    }
    return grid;
}

void freeDoubleArray(int rows, int cols, char **array){
    int i, j;

    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            free(*array);
        }
    }
    free(array);
}

void printGrid(int rows, int cols, char** grid){
    int i, j;
    char letter;
    
    printf( "=========================================================\n"
            "                       CRABBLE\n"
            "=========================================================\n\n");

    for(i = 0; i < rows; i++){
        printGridLine(rows);
        printf("    ");
        for(j = 0; j < cols; j++){
            letter = grid[i][j];
            if(letter == 32 || letter == 42 || letter == 45){
                printf("| %c ", letter);
            }else if(letter == 49){
                printf("| LD");
            }else if(letter == 50){
                printf("| LT");
            }else if(letter == 51){
                printf("| MD");
            }else if(letter == 52){
                printf("| MT");
            }else if(letter == 53){
                printf("|-LD");
            }else if(letter == 54){
                printf("|-LT");
            }else if(letter == 55){
                printf("|-MD");
            }else if(letter == 56){
                printf("|-MT");
            }
        }
        printf("|\n");
    }
    printGridLine(rows);
}

void printGridLine(int cols){
    int i;

    printf("    ");
    for(i = 0; i < cols; i++){
        printf("----");
    }
        printf("-\n");
}

void printAllocError(){
    printf("\nErreur d'allocation\n");
    system("pause");
    exit(0);
}

void delay(){
    int i, j;
   
    for (i = 0; i < 12345; i++){
        for (j = 0; j < 12345; j++){} 
    }
       
}