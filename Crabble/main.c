#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu();
void play();
char** initGrid(int rows, int cols, int doubleLetters, int tripleLetters, int doubleWords, int tripleWords, int negative);
void freeDoubleArray(int rows, int cols, char **array);


// Affichage
void printGrid(int rows, int cols, char** grid);
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
                "               BIENVENUE AU CRABBLE\n"
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
            play();
        }
    }while(menuBool != 2);
}

void play(){
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


    printf("JOUER !!! ");
    // printGrid();
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
            // grid[i][j] = 32;
            grid[i][j] = 97;
        }
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

    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            printf("%c ",grid[i][j]);
        }
        printf("\n");
    }
}

void printAllocError(){
    printf("\nErreur d'allocation\n");
    system("pause");
    exit(0);
}

