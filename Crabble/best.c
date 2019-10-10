#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


int** best3Moves(int rGrid, int cGrid, int pos_x, int pos_y,int wordSize,char** Grid, int* word);
char** fillGridWith(int rows, int cols, char**grid, char letter, int caseNumber);

void delay();

void printAllocError();



char** initGrid(int rows, int cols, int doubleLetters, int tripleLetters, int doubleWords, int tripleWords, int negative);


int main(int argc, char* argv[])
{
	char** grid;

    int** resu;

    grid = initGrid(9,9,1,1,1,1,1);

    for(int i = 0; i<9; i++){
        for(int j = 0; j<9; j++){
            printf("%c",grid[i][j]);
        }
        printf("\n");
    }

    int test[5] = {1,2,1,2,1};

    resu = best3Moves(9,9,2,6,5,grid,test);

	

	
	return 0;
}



char* removeLetters(char *letters, char* word){


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

    int resu[3][4];

    int resu** = malloc(sizeof(int*)*3);

    for(int i = 0; i < 3; i++){
        resu[i] = malloc(sizeof(int)*4);
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

    for(int j = 0; j < wordSize-1; j++){
        if(pos_r+j <= rGrid-1 && cmpt_start1+j <= pos_r){
            for(int i = cmpt_start1+j; i<=cmpt_start1+(wordSize-1)+j;i++){
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

    for(int j = 0; j < wordSize-1; j++){
        if(pos_c+j <= cGrid-1 && cmpt_start2+j <= pos_c){
            for(int i = cmpt_start2+j; i<=cmpt_start2+(wordSize-1)+j;i++){
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
    for(int j = 0; j < wordSize-1; j++){
        if(pos_r+j <= rGrid-1 && cmpt_start1+j <= pos_r){
            for(int i = cmpt_start1+j; i<=cmpt_start1+(wordSize-1)+j;i++){
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

    for(int j = 0; j < wordSize-1; j++){
        if(pos_c+j <= cGrid-1 && cmpt_start2+j <= pos_c){
            for(int i = cmpt_start2+j; i<=cmpt_start2+(wordSize-1)+j;i++){
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

    for(int j = 0; j < wordSize-1; j++){
        if(pos_r+j <= rGrid-1 && cmpt_start1+j <= pos_r){
            for(int i = cmpt_start1+j; i<=cmpt_start1+(wordSize-1)+j;i++){
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

    for(int j = 0; j < wordSize-1; j++){
        if(pos_c+j <= cGrid-1 && cmpt_start2+j <= pos_c){
            for(int i = cmpt_start2+j; i<=cmpt_start2+(wordSize-1)+j;i++){
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
            grid[i][j] = 'v'; // ESPACE
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

            if(grid[y][x] == 'v'){
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

void delay(){
    int i, j;

    for (i = 0; i < 12345; i++){
        for (j = 0; j < 12345; j++){}
    }

}

void printAllocError(){
    printf("\nErreur d'allocation");
    system("pause");
    exit(0);
}