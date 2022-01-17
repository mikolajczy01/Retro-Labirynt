#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// czyszczenie terminala
void clear_moj()
{
    system("cls");
}

// losowy kolor napisu
void rcolor_start()
{
    int x;
    x = rand() % 4;
    switch (x)
    {
    case 0:
        printf("\033[0;31m");
        break;
    case 1:
        printf("\033[0;32m");
        break;
    case 2:
        printf("\033[0;33m");
        break;
    case 3:
        printf("\033[0;35m");
        break;
    }
}

// zatrzymanie losowego koloru napisu
void rcolor_stop()
{
    printf("\033[0m");
}

void napis_labirynt()
{
    rcolor_start();
    printf("   d8888b. d88888b d888888b d8888b.  .d88b.          db       .d8b.  d8888b. d888888b d8888b. db    db d8b   db d888888b\n");
    printf("   88  `8D 88'     `  88  ' 88  `8D .8P  Y8.         88      d8' `8b 88  `8D   `88'   88  `8D `8b  d8' 888o  88 `  88  '\n");
    printf("   88oobY' 88ooooo    88    88oobY' 88    88         88      88ooo88 88oooY'    88    88oobY'  `8bd8'  88V8o 88    88  \n");
    printf("   88`8b   88         88    88`8b   88    88         88      88   88 88   b.    88    88`8b      88    88 V8o88    88   \n");
    printf("   88 `88. 88.        88    88 `88. `8b  d8'         88booo. 88   88 88   8D   .88.   88 `88.    88    88  V888    88   \n");
    printf("   88   YD Y88888P    YP    88   YD  `Y88P'          Y88888P YP   YP Y8888P' Y888888P 88   YD    YP    VP   V8P    YP   \n");
    rcolor_stop();
}

void napis_ranking()
{
    rcolor_start();
    printf("                            d8888b.  .d8b.  d8b   db db   dD d888888b d8b   db  d888b\n");
    printf("                            88  `8D d8' `8b 888o  88 88 ,8P'   `88'   888o  88 88' Y8b \n");
    printf("                            88oobY' 88ooo88 88V8o 88 88,8P      88    88V8o 88 88      \n");
    printf("                            88`8b   88   88 88 V8o88 88`8b      88    88 V8o88 88  ooo \n");
    printf("                            88 `88. 88   88 88  V888 88 `88.   .88.   88  V888 88. ~8~ \n");
    printf("                            88   YD YP   YP VP   V8P YP   YD Y888888P VP   V8P  Y888P  \n");
    rcolor_stop();
}

void menu();

int czy_plik_istnieje(const char *filename)
{
    FILE *plik;
    if ((plik = fopen(filename, "r")))
    {
        fclose(plik);
        return 1;
    }
    return 0;
}

void menu_nowa_gra()
{
    int wielkosc;
    // wybor opcji w menu nowej gry
    do
    {
        clear_moj();

        napis_labirynt();

        printf("\n\n\033[0;36m                                       ####################################");
        printf("\n                                       ##         1. Plansza 9x9         ##");
        printf("\n                                       ##        2. Plansza 15x15        ##");
        printf("\n                                       ##        3. Plansza 23x23        ##");
        printf("\n                                       ##       4. Wybierz rozmiar       ##");
        printf("\n                                       ##            5. Powrot           ##");
        printf("\n                                       ####################################\033[0m\n");
        switch (getch())
        {
        case '1':
           
            return;
        case '2':
            
            return;
        case '3':
            
            return;
        case '4':
            do
            {

                clear_moj();
                napis_labirynt();
                printf("\n\n\033[0;36m                              ##########################################################");
                printf("\n                              ##                                                      ##");
                printf("\n                              ##  Wybierz wielkosc mapy w formacie AxA                ##");
                printf("\n                              ##  Gdzie A jest liczba nieparzysta z przedialu <9,35>  ##");
                printf("\n                              ##                                                      ##");
                printf("\n                              ##########################################################");
                printf("\n\n                                            Podaj wielkosc mapy:");

                scanf("%d", &wielkosc);

                if (wielkosc % 2 == 0 || wielkosc < 9 || wielkosc > 35)
                {
                    printf("Niepoprawne dane!");
                    getch();
                }
                else
                {
                    break;
                }
            } while (1);
            
            return;
        case '5':
            return;
        default:
            printf("\nNIEPOPRAWNY WYBOR!");
            getch();
        }
    } while (1);

    printf("\033[0m");

    
}

int main(){
    menu();
}

void menu()
{
    // wybor opcji menu glownego
    do
    {

        clear_moj();

        napis_labirynt();

        printf("\n\n\033[0;36m                                       ###################################");
        printf("\n                                       ##         1. Nowa gra           ##");
        printf("\n                                       ##          2.Ranking            ##");
        printf("\n                                       ##        3.Wczytaj gre          ##");
        printf("\n                                       ##            4.Wyjdz            ##");
        printf("\n                                       ###################################\033[0m\n");

        switch (getch())
        {
        case '1':
            menu_nowa_gra();
            break;
        case '2':
            napis_ranking();
            getch();
            break;
        case '3':
            break;
        case '4':
            return;
        default:
            printf("\nNIEPOPRAWNY WYBOR!");
            getch();
        }
    } while (1);
}

