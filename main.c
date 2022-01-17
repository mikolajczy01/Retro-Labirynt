#include <stdio.h>
#include <stdlib.h>

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

int main(){
    clear_moj();
    napis_labirynt();
    getchar();
    napis_ranking();
    getchar();
    clear_moj;
}

