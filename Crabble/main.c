#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu();
void start();

// Déroulement partie
void play(int rows, int cols, char** grid, int** bag, char* lettersJ1, char* lettersJ2);
char** distribuate(int** bag, int isJ1, char** lettersJ2);
int askToPlay(int rows, int cols, char** grid, int** bag, int* score, char* letters);
char* chooseWord(/*char* letters*/);
int** best3Moves(int rGrid, int cGrid, int pos_r, int pos_c, int wordSize, char** grid, int* word);
void endgame(int rows, int cols, char** grid, int ** bag, char *lettersJ1, char *lettersJ2, int scoreJ1, int scoreJ2);

// Initialisation
char** initGrid(int rows, int cols, int doubleLetters, int tripleLetters, int doubleWords, int tripleWords, int negative);
char** fillGridWith(int rows, int cols, char**grid, char letter, int caseNumber);
char* initLetters(char* letters);
int** initBag();
int** initList();
int* initValue();
int* initPiece();

// Affichage
void printGrid(int rows, int cols, char** grid);
void printGridLine(int cols);
void printAllocError();
void printLetters(char* letters);

// Divers
void freeDoubleArrayC(int rows, int cols, char **array);
void freeDoubleArrayI(int rows, int cols, int **array);
void delay();
int checkOccurences(int** list, int index);
int** addLetterToList(int* size, int** list, char letter, int* index);
// int returnValueOfLetter(char* letter, int** array);
int returnValueOfLetter(char letter, int** array);
int calculateSizeLetters(char* letters);
char* removeLetters(char *letters, char* word, int sizeWord);

int main(int argc, char ** argv){
    menu();
    system("pause");
    return 0;
}

void menu(){
    int menuBool = 1;

    do{
        system("cls");
        printf( " =========================================================\n"
                "                   BIENVENUE AU CRABBLE\n"
                " =========================================================\n\n"
                " Taper :\n"
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
        }else{
            system("pause");
            exit(0);
        }
    }while(menuBool != 2);
}

void start(){
    int rows, cols, doubleLetters, tripleLetters, doubleWords, tripleWords, negative;

    char **grid = NULL;
    int **bag = NULL;
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

    // chooseWord();

    grid = initGrid(rows, cols, doubleLetters, tripleLetters, doubleWords, tripleWords, negative);
    bag = initBag();
    lettersJ1 = initLetters(lettersJ1);
    lettersJ2 = initLetters(lettersJ2);

    play(rows, cols, grid, bag, lettersJ1, lettersJ1);

    freeDoubleArrayC(rows, cols, grid);
    freeDoubleArrayI(2, 27, bag);
    if(lettersJ1){
        free(lettersJ1);
    }
    if(lettersJ2){
        free(lettersJ2);
    }

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

char* initLetters(char* letters){
    letters = malloc(sizeof(char) * 7);
    if(!letters){
        printAllocError();
    }
    return letters;
}

int** initList(){
    int i, j;
    int **list = NULL;

    list = malloc(sizeof(int*) * 3);
    if(!list){
        printAllocError();
    }

    for(i = 0; i < 3; i++){
        list[i] = malloc(sizeof(int) * 7);
        if(!list[i]){
            printAllocError();
        }
    }

    for(i = 0; i < 3; i++){
        for(j = 0; j < 7; j++){
            if(i == 0){
                list[i][j] = -1;
            }else{
                list[i][j] = 0;
            }
        }
        printf("%d %d", list[i], list[j]);
    }
    printf("\n");

    return list;
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

void freeDoubleArrayC(int rows, int cols, char **array){
    int i;

    for(i = 0; i < rows; i++){
        if(array[i]){
            free(array[i]);
            array[i] = NULL;
        }
    }
    if(array){
        free(array);
        array = NULL;
    }
}

void freeDoubleArrayI(int rows, int cols, int **array){
    int i;

    for(i = 0; i < rows; i++){
        if(array[i]){
            free(array[i]);
            array[i] = NULL;
        }
    }
    // if(array){
    //     free(array);
    //     array = NULL;
    // }
}

void printGrid(int rows, int cols, char** grid){
    int i, j;
    char letter;

    system("cls");
    printf( " =========================================================\n"
            "                       CRABBLE\n"
            " =========================================================\n\n");

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

void printLetters(char* letters){
    int i;
    int size = calculateSizeLetters(letters);

    printf("\n        ");
    for(i = 0; i < size; i++){
        printf("| %c | ", letters[i]);
    }
    printf("\n\n");
}

void printAllocError(){
    printf("\nErreur d'allocation\n");
    system("pause");
    exit(0);
}

int calculateSizeLetters(char* letters){
    int size = 0;

    // char 42 <=> '*' dans les cases vides
    while(size < 7 && letters[size] != 42){
        size++;
    }
    return size;
}

void delay(){
    int i, j;

    for (i = 0; i < 12345; i++){
        for (j = 0; j < 12345; j++){}
    }

}

void play(int rows, int cols, char** grid, int** bag, char* lettersJ1, char* lettersJ2){
    int scoreJ1, scoreJ2, isJ1;
    int continueGame;

    continueGame = 1;
    isJ1 = 1;
    scoreJ1 = 0;
    scoreJ2 = 0;
    while(continueGame){
        if(isJ1){
            // lettersJ1 = distribuate(bag, lettersJ1, calculateSizeLetters(lettersJ1));
        }else{
            // lettersJ2 = distribuate(bag, lettersJ2, calculateSizeLetters(lettersJ2));
        }
        continueGame = askToPlay(rows, cols, grid, bag, isJ1 ? &scoreJ1 : &scoreJ2, isJ1 ? lettersJ1 : lettersJ2);
        if(continueGame == 1){
            // checkEndGame();
        }else{
            endgame(rows, cols, grid, bag, lettersJ1, lettersJ2, scoreJ1, scoreJ2);
        }
        isJ1 = isJ1 ? 0 : 1;
        // printf("J :%d\n", isJ1);
    }
}

// char** distribuate(char** bag, char** letters, int size){

// }


int askToPlay(int rows, int cols, char** grid, int** bag, int* score, char* letters){
    int menuBool = 1;
    char* word = NULL;

    do{
        printGrid(rows, cols, grid);
        printLetters(letters);
        printf( "    Taper :\n"
                "       1) Pour passer votre tour\n"
                "       2) Pour poser un mot\n"
                "       3) Pour quitter la partie\n"
                );

        fflush(stdin);
        scanf("%d", &menuBool);

        while(menuBool != 1 && menuBool != 2 && menuBool != 3){
            system("cls");
            printGrid(rows, cols, grid);
            printLetters(letters);
            // printf("Taper 1 ou 3");
            printf("Taper 1, 2 ou 3");
            fflush(stdin);
            scanf("%d", &menuBool);
        }

        if(menuBool == 2){
            // word = chooseWord(letters);
            // meilleurCoup();
            // incrémentation score ???
        }else if(menuBool == 3){
            return 0;
        }
    }while(menuBool != 1);
    return 1;
}

void endgame(int rows, int cols, char** grid, int **bag, char *lettersJ1, char *lettersJ2, int scoreJ1, int scoreJ2){
    printGrid(rows, cols, grid);
    printf("        PARTIE TERMINEE !\n"
           "  -------------------------\n\n"
           );
    if(scoreJ1 != scoreJ2){
        printf( "        Le joueur J%d a gagne \\o/\n"
                "         J1 : %d Points\n"
                "         J2 : %d Points\n"
                , scoreJ1 > scoreJ2 ? 1 : 2, scoreJ1, scoreJ2);
    }else{
        printf( "        Score a egalite !\n"
                "         J1 : %d Points\n"
                "         J2 : %d Points\n"
                , scoreJ1, scoreJ2);
    }

    system("pause");

    freeDoubleArrayC(rows, cols, grid);
    freeDoubleArrayI(2, 27, bag);

    if(lettersJ1){
        free(lettersJ1);
        lettersJ1 = NULL;
    }
    if(lettersJ2){
        free(lettersJ2);
        lettersJ2 = NULL;
    }
    menu();
}

int returnValueOfLetter(char letter, int** array){
    int i;
    for(i = 0; i < 26; i++){
        if(letter == (char)(i + 65)){
            return array[0][i];
        }
    }
    return 0;
}

int checkOccurences(int** list, int index){
    return list[2][index] <= list[1][index];
}

int** addLetterToList(int* size, int** list, char letter, int* index){
    // List : Tableau où on stocke [0][i] => le code ascii de la lettre, [1][i] => nb dans letters, [2][i] => nb dans word
    int i, j;
    int found = 0;

    for(i = 0; i < *size; i++){
        printf("%d ", list[0][i]);
        if(list[0][i] == -1 && list[0][i] == (int)letter){
            list[1][i]++;
            list[2][i]++;
            *index = i;
            found = 1;
        }
    }

    if(found == 0){
        list[0][*size] = (int)letter;
        *index = *size;
        *size = *size + 1;
    }

    list;
}

char* chooseWord(/*char **letters*/){
    int i, j, scanOK, sizeTemp, found;
    char temp[8];
    char* word = NULL;
    int **list = NULL; // Tableau où on stocke [0][i] => le code ascii de la lettre, [1][i] => nb dans letters, [2][i] => nb dans word
    int sizeList = 0;
    int index;
    char letter;

    char letters[7] = {'A', 'B', 'C', '*', '*', '*', '*'};
    int size = calculateSizeLetters(letters);

    word = malloc(sizeof(char) * (size));
    if(!word){
        printAllocError();
    }

    list = initList();

    do{
        scanOK = 1;
        found = 0;

        printf("\n\nSaisissez votre mot:\n");
        fflush(stdin);
        scanf("%s", temp);

        sizeTemp = 0;
        while(temp[sizeTemp] != '\0'){
            sizeTemp++;
        }

        if(sizeTemp > size){
            scanOK = 0;
        }

        for(i = 0; i < size; i++){
            word[i] = temp[i];
            for(j = 0; j < size; j++){
                // printf("w :%c ", word[i]);
                if(word[i] == letters[j]){
                    found = 1;
                    // printf("list");
                    list = addLetterToList(&sizeList, list, word[i], &index);
                    if(!checkOccurences(list, index)){
                        scanOK = 0;
                    }
                }
            }
            if(found == 0){
                scanOK = 0;
            }
        }
    printf("s: %d | f: %d", scanOK, found);
    }while(!scanOK && !found);

    freeDoubleArrayI(3, 7, list);
    system("pause");
    // free list
    return word;
}

char* removeLetters(char *letters, char* word, int sizeWord){
    int i,j;
    int sizeLetters= calculateSizeLetters(letters);

    for(i = 0; i< sizeLetters; i++){
        for(j = 0; j < sizeWord; j++){
            if(word[i] == letters[j]){
                printf("%c\n", letters[j]);
                letters[j] = '*';
            }
        }
    }

    int temp = 0;
    for (i = 0; i < sizeLetters - 1; i++)
    {
        for (j = i + 1; j < sizeLetters; j++)
        {
            if (letters[i] == '*'){
                temp = letters[i];
                letters[i] = letters[j];
                letters[j] = temp;
            }        
        }
     }
    return letters;
}

int** best3Moves(int rGrid, int cGrid, int pos_r, int pos_c,int wordSize,char** grid, int* word){
    int size = wordSize-1;

    int cmpt_start1=0;
    int cmpt_start2=0;

    int rows_res = 0;
    int col_res = 0;

    int cmpt_word = 0;

    int MD = 0;
    int MT = 0;

    int MD_N = 0;
    int MT_N = 0;

    int max1 = 0;
    int max2 = 0;
    int max3 = 0;

    int** resu = NULL;
    int i, j;

    resu = malloc(sizeof(int*)*3);
    if(!resu){
        printAllocError();
    }

    for(i = 0; i < 3; i++){
        resu[i] = malloc(sizeof(int)*4);
        if(!resu[i]){
            printAllocError();
        }
    }

    // On cherche quand peut démarrer le tableau au minimum
    while(size<pos_r){
        cmpt_start1 +=1;
        size+=1;
    }
    printf("%d\n",cmpt_start1);

    size = wordSize-1;

    while(size<pos_c){
        cmpt_start2 +=1;
        size+=1;
    }
    printf("%d\n",cmpt_start2);

    //Parcours ligne du point pour max1

    for(j = 0; j < wordSize-1; j++){
        if(pos_r+j <= rGrid-1 && cmpt_start1+j <= pos_r){
            for(i = cmpt_start1+j; i<=cmpt_start1+(wordSize-1)+j;i++){
                if (grid[i][pos_c] == 49){
                    rows_res += word[cmpt_word]*2;
                }
                else if (grid[i][pos_c] == 50){
                    rows_res += word[cmpt_word]*3;
                }
                else if (grid[i][pos_c] == 51){
                    rows_res += word[cmpt_word];
                    MD += 1;
                }
                else if (grid[i][pos_c] == 52){
                    rows_res += word[cmpt_word];
                    MT += 1;
                }
                else if (grid[i][pos_c] == 53){
                    rows_res += word[cmpt_word] * (-2);
                }
                else if (grid[i][pos_c] == 54){
                    rows_res += word[cmpt_word]* (-3);
                }
                else if (grid[i][pos_c] == 55){
                    rows_res += word[cmpt_word];
                    MD_N +=1;
                }
                else if (grid[i][pos_c] == 56){
                    rows_res += word[cmpt_word];
                    MT_N +=1;
                }
                else if (grid[i][pos_c] == 45){
                    rows_res += word[cmpt_word]* (-1);

                }
                else{
                    rows_res += word[cmpt_word] ;
                }
                cmpt_word += 1;
            }

            while(MD>0){
                rows_res *= (2);
                MD--;
            }

            while(MT>0){
                rows_res *= (3);
                MT--;
            }

            while(MD_N>0){
                rows_res *= (-2);
                MD_N--;
            }

            while(MT_N>0){
                rows_res *= (-3);
                MT_N--;
            }

            printf("%d\n",rows_res);

            if(rows_res> max1){
                max1 = rows_res;
                resu[0][0] = cmpt_start1+j;
                resu[0][1] = pos_c;
                resu[0][2] = 0;
                resu[0][3] = max1;
            }
            rows_res = 0;
            cmpt_word=0;
        }
    }

    //Parcours colonne du point pour max 1

    for(j = 0; j < wordSize-1; j++){
        if(pos_c+j <= cGrid-1 && cmpt_start2+j <= pos_c){
            for(i = cmpt_start2+j; i<=cmpt_start2+(wordSize-1)+j;i++){
                if (grid[pos_r][i] == 49){
                    col_res += word[cmpt_word]*2;
                }
                else if (grid[pos_r][i] == 50){
                    col_res += word[cmpt_word]*3;
                }
                else if (grid[pos_r][i] == 51){
                    col_res += word[cmpt_word];
                    MD += 1;
                }
                else if (grid[pos_r][i] == 52){
                    col_res += word[cmpt_word];
                    MT += 1;
                }
                else if (grid[pos_r][i] == 53){
                    col_res += word[cmpt_word] * (-2);
                }
                else if (grid[pos_r][i] == 54){
                    col_res += word[cmpt_word]* (-3);
                }
                else if (grid[pos_r][i] == 55){
                    col_res += word[cmpt_word];
                    MD_N +=1;
                }
                else if (grid[pos_r][i] == 56){
                    col_res += word[cmpt_word];
                    MT_N +=1;
                }
                else if (grid[pos_r][i] == 45){
                    col_res += word[cmpt_word]* (-1);

                }
                else{
                    col_res += word[cmpt_word] ;
                }
                cmpt_word+=1;
            }

            while(MD>0){
                col_res *= (2);
                MD--;
            }

            while(MT>0){
                col_res *= (3);
                MT--;
            }

            while(MD_N>0){
                col_res *= (-2);
                MD_N--;
            }

            while(MT_N>0){
                col_res *= (-3);
                MT_N--;
            }

            if(col_res> max1){
                max1 = col_res;
                resu[0][0] = pos_r;
                resu[0][1] = cmpt_start2+j;
                resu[0][2] = 1;
                resu[0][3] = max1;
            }

            printf("%d\n",col_res);
            col_res = 0;
            cmpt_word=0;
        }
    }

    //Parcours ligne du point pour max2
    for(j = 0; j < wordSize-1; j++){
        if(pos_r+j <= rGrid-1 && cmpt_start1+j <= pos_r){
            for(i = cmpt_start1+j; i<=cmpt_start1+(wordSize-1)+j;i++){
                if (grid[i][pos_c] == 49){
                    rows_res += word[cmpt_word]*2;
                }
                else if (grid[i][pos_c] == 50){
                    rows_res += word[cmpt_word]*3;
                }
                else if (grid[i][pos_c] == 51){
                    rows_res += word[cmpt_word];
                    MD += 1;
                }
                else if (grid[i][pos_c] == 52){
                    rows_res += word[cmpt_word];
                    MT += 1;
                }
                else if (grid[i][pos_c] == 53){
                    rows_res += word[cmpt_word] * (-2);
                }
                else if (grid[i][pos_c] == 54){
                    rows_res += word[cmpt_word]* (-3);
                }
                else if (grid[i][pos_c] == 55){
                    rows_res += word[cmpt_word];
                    MD_N +=1;
                }
                else if (grid[i][pos_c] == 56){
                    rows_res += word[cmpt_word];
                    MT_N +=1;
                }
                else if (grid[i][pos_c] == 45){
                    rows_res += word[cmpt_word]* (-1);

                }
                else{
                    rows_res += word[cmpt_word] ;
                }
                cmpt_word += 1;
            }

            while(MD>0){
                rows_res *= (2);
                MD--;
            }

            while(MT>0){
                rows_res *= (3);
                MT--;
            }

            while(MD_N>0){
                rows_res *= (-2);
                MD_N--;
            }

            while(MT_N>0){
                rows_res *= (-3);
                MT_N--;
            }

            printf("%d\n",rows_res);

            if(rows_res != max1 && rows_res >max2){
                max2 = rows_res;
                resu[1][0] = cmpt_start1+j;
                resu[1][1] = pos_c;
                resu[1][2] = 0;
                resu[1][3] = max2;
            }
            rows_res = 0;
            cmpt_word=0;
        }

    }

    //Parcours colonne du point pour max2

    for(j = 0; j < wordSize-1; j++){
        if(pos_c+j <= cGrid-1 && cmpt_start2+j <= pos_c){
            for(i = cmpt_start2+j; i<=cmpt_start2+(wordSize-1)+j;i++){
                if (grid[pos_r][i] == 49){
                    col_res += word[cmpt_word]*2;
                }
                else if (grid[pos_r][i] == 50){
                    col_res += word[cmpt_word]*3;
                }
                else if (grid[pos_r][i] == 51){
                    col_res += word[cmpt_word];
                    MD += 1;
                }
                else if (grid[pos_r][i] == 52){
                    col_res += word[cmpt_word];
                    MT += 1;
                }
                else if (grid[pos_r][i] == 53){
                    col_res += word[cmpt_word] * (-2);
                }
                else if (grid[pos_r][i] == 54){
                    col_res += word[cmpt_word]* (-3);
                }
                else if (grid[pos_r][i] == 55){
                    col_res += word[cmpt_word];
                    MD_N +=1;
                }
                else if (grid[pos_r][i] == 56){
                    col_res += word[cmpt_word];
                    MT_N +=1;
                }
                else if (grid[pos_r][i] == 45){
                    col_res += word[cmpt_word]* (-1);
                }
                else{
                    col_res += word[cmpt_word] ;
            }
            cmpt_word+=1;
        }
            while(MD>0){
                col_res *= (2);
                MD--;
            }

            while(MT>0){
                col_res *= (3);
                MT--;
            }

            while(MD_N>0){
                col_res *= (-2);
                MD_N--;
            }

            while(MT_N>0){
                col_res *= (-3);
                MT_N--;
            }
            if(col_res != max1 && col_res> max2){
                max2 = col_res;
                resu[1][0] = pos_r;
                resu[1][1] = cmpt_start2+j;
                resu[1][2] = 1;
                resu[1][3] = max2;
            }

            printf("%d\n",col_res);
            col_res = 0;
            cmpt_word=0;
        }

        if(max2 == 0){
            resu[1][0] = -1;
            resu[1][1] = -1;
            resu[1][2] = -1;
            resu[1][3] = -1;
        }
    }

    //Parcours ligne du point pour max3

    for(j = 0; j < wordSize-1; j++){
        if(pos_r+j <= rGrid-1 && cmpt_start1+j <= pos_r){
            for(i = cmpt_start1+j; i<=cmpt_start1+(wordSize-1)+j;i++){
                if (grid[i][pos_c] == 49){
                    rows_res += word[cmpt_word]*2;
                }
                else if (grid[i][pos_c] == 50){
                    rows_res += word[cmpt_word]*3;
                }
                else if (grid[i][pos_c] == 51){
                    rows_res += word[cmpt_word];
                    MD += 1;
                }
                else if (grid[i][pos_c] == 52){
                    rows_res += word[cmpt_word];
                    MT += 1;
                }
                else if (grid[i][pos_c] == 53){
                    rows_res += word[cmpt_word] * (-2);
                }
                else if (grid[i][pos_c] == 54){
                    rows_res += word[cmpt_word]* (-3);
                }
                else if (grid[i][pos_c] == 55){
                    rows_res += word[cmpt_word];
                    MD_N +=1;
                }
                else if (grid[i][pos_c] == 56){
                    rows_res += word[cmpt_word];
                    MT_N +=1;
                }
                else if (grid[i][pos_c] == 45){
                    rows_res += word[cmpt_word]* (-1);

                }
                else{
                    rows_res += word[cmpt_word] ;
                }
                cmpt_word += 1;
            }

            while(MD>0){
                rows_res *= (2);
                MD--;

            }

            while(MT>0){
                rows_res *= (3);
                MT--;
            }

            while(MD_N>0){
                rows_res *= (-2);
                MD_N--;
            }

            while(MT_N>0){
                rows_res *= (-3);
                MT_N--;
            }

            printf("%d\n",rows_res);

            if(rows_res != max1 && rows_res != max2 && rows_res >max3){
                max3 = rows_res;
                resu[2][0] = cmpt_start1+j;
                resu[2][1] = pos_c;
                resu[2][2] = 0;
                resu[2][3] = max3;
            }
            rows_res = 0;
            cmpt_word=0;
        }

    }

    //Parcours colonne du point pour max2

    for(j = 0; j < wordSize-1; j++){
        if(pos_c+j <= cGrid-1 && cmpt_start2+j <= pos_c){
            for(i = cmpt_start2+j; i<=cmpt_start2+(wordSize-1)+j;i++){
                if (grid[pos_r][i] == 49){
                    col_res += word[cmpt_word]*2;
                }
                else if (grid[pos_r][i] == 50){
                    col_res += word[cmpt_word]*3;
                }
                else if (grid[pos_r][i] == 51){
                    col_res += word[cmpt_word];
                    MD += 1;
                }
                else if (grid[pos_r][i] == 52){
                    col_res += word[cmpt_word];
                    MT += 1;
                }
                else if (grid[pos_r][i] == 53){
                    col_res += word[cmpt_word] * (-2);
                }
                else if (grid[pos_r][i] == 54){
                    col_res += word[cmpt_word]* (-3);
                }
                else if (grid[pos_r][i] == 55){
                    col_res += word[cmpt_word];
                    MD_N +=1;
                }
                else if (grid[pos_r][i] == 56){
                    col_res += word[cmpt_word];
                    MT_N +=1;
                }
                else if (grid[pos_r][i] == 45){
                    col_res += word[cmpt_word]* (-1);

                }
                else{
                    col_res += word[cmpt_word] ;
            }

            cmpt_word+=1;
        }
            while(MD>0){
                col_res *= (2);
                MD--;
            }

            while(MT>0){
                col_res *= (3);
                MT--;
            }

            while(MD_N>0){
                col_res *= (-2);
                MD_N--;
            }

            while(MT_N>0){
                col_res *= (-3);
                MT_N--;
            }
            if(col_res != max1 && col_res != max2 && col_res> max3){
                max3 = col_res;
                resu[2][0] = pos_r;
                resu[2][1] = cmpt_start2+j;
                resu[2][2] = 1;
                resu[2][3] = max3;
            }

            printf("%d\n",col_res);
            col_res = 0;
            cmpt_word=0;
        }

        if(max3 == 0){
            resu[2][0] = -1;
            resu[2][1] = -1;
            resu[2][2] = -1;
            resu[2][3] = -1;
        }
    }
    return resu;
}
