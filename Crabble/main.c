#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu();
void play();

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
    system("cls");
    printf("JOUER !!! ");
    system("pause");
}
