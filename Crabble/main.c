#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu();
void start();

// Déroulement partie
void play(int rows, int cols, char** grid, char** bag/*, char* lettersJ1, char* lettersJ2*/);
char** distribuate(char** bag, int isJ1, char** lettersJ2);

// Initialisation
char** initGrid(int rows, int cols, int doubleLetters, int tripleLetters, int doubleWords, int tripleWords, int negative);
char** fillGridWith(int rows, int cols, char**grid, char letter, int caseNumber);
//char*  initLetters(*char letters);
int** initBag();
int* initValue();
int* initPiece();

// Affichage
void printGrid(int rows, int cols, char** grid);
void printGridLine(int cols);
void printAllocError();

// Divers
void freeDoubleArray(int rows, int cols, char **array);
void delay();

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
    int rows, cols, doubleLetters, tripleLetters, doubleWords, tripleWords, negative;

    char **grid = NULL;
    char **bag = NULL;
    char *lettersJ1 = NULL;
    char *lettersJ2 = NULL;
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
    bag = initBag();
    // lettersJ1 = initLetters(lettersJ1);
    // lettersJ2 = initLetters(lettersJ2);
    system("pause");
    printGrid(rows, cols, grid);
    play(rows, cols, grid, bag);

    system("pause");
    printf("\nJOUER !!! ");

    system("pause");

    freeDoubleArray(rows, cols, grid);
    freeDoubleArray(2, 27, bag);
    // free(lettersJ1);
    // free(lettersJ2);
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

int* initValue(){
    int i;
    int tabTemp[27] = {1 , 3 , 3 , 2 , 1 , 4 , 2 , 4 , 1 , 8 , 10 , 1 , 2 , 1 , 1 , 3 , 8 , 1 , 1 , 1 , 1 , 4 , 10 , 10 , 10 , 10, 0};
    int *value = NULL;
    value = malloc(sizeof(int) * 27);
    if(!value){
        printAllocError();
    }

    for(i = 0; i < 27; i++){
        value[i] = tabTemp[i];
    }
    return value;
}

int* initPiece(){
    int i;
    int tabTemp[27] = {9 , 2 , 2 , 3 , 15 , 2 , 2 , 2 , 8 , 1 , 1 , 5 , 3 , 6 , 6 , 2 , 1 , 6 , 6 , 6 , 6 , 2 , 1 , 1 , 1 , 1 , 2};
    int *piece = NULL;
    piece = malloc(sizeof(int) * 27);
    if(!piece){
        printAllocError();
    }
    for(i = 0; i < 27; i++){
        piece[i] = tabTemp[i];
    }
    return piece;
}

int** initBag(){
    int i;
    int** array = NULL;

    array = malloc(sizeof(int*) * 2);
    if(!array){
        printAllocError();
    }
    for(i =0; i < 27; i++){
        array[i] = malloc(sizeof(int) * 27);
        if(!array[i]){
            printAllocError();
        }
    }

    array[0] = initValue();
    array[1] = initPiece();

    return array;
}

char** fillGridWith(int rows, int cols, char**grid, char letter, int caseNumber){
    int x, y, hasChanged;
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

    system("cls");
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

void play(int rows, int cols, char** grid, char** bag/*, char* lettersJ1, char* lettersJ2*/){
    int scoreJ1, scoreJ2, isJ1;
    int continueGame;

    continueGame = 1;
    isJ1 = 1;
    scoreJ1 = 0;
    scoreJ2 = 0;
    // while(continueGame){
    //     if(isJ1){
    //         // lettersJ1 = distribuate(/*bag*/, &isJ1, &lettersJ1);
    //     }else{
    //         // lettersJ2 = distribuate(/*bag*/, &isJ1, &lettersJ2);
    //     }
    //     // printHand()
    //     // askToPlay(rows, cols, grid, &isJ1, isJ1 ? &scoreJ1 : &scoreJ2, isJ1 ? &lettersJ1 : &lettersJ2);
    //     // continueGame = checkEndGame();
    // }
}

char** distribuate(char** bag, int isJ1, char** lettersJ2){

}

void askToPlay(int rows, int cols, char** grid, int isJ1, int* score, char* letters){
    // pass()
    // write()
    // endGame()
}
