#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <dirent.h>

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

void generowanie_planszy(char *mapa, int a, int start, int kierunek, int licznik)
{
    int ruch;

    // sprawdzenie czy nie zostaly juz przejrzane wszystkie kierunki
    if (licznik > 3)
    {
        return;
    }

    // wybor jednego z 4 kiernkow
    switch (kierunek)
    {
    case 0:
        ruch = 1;
        break;
    case 1:
        ruch = -1;
        break;
    case 2:
        ruch = -a;
        break;
    case 3:
        ruch = a;
        break;
    }

    // warunek sprawdzajacy czy mozna utworzyc sciezke
    if ((start + ruch) % a != 0 && (start + ruch) % a != a - 1 && (start + ruch) > a && (start + ruch) < a * a - a && mapa[start + ruch] != 0 && mapa[start + 2 * ruch] != 0 && (start + ruch * 2) % a != 0 && (start + ruch * 2) % a != a - 1 && (start + ruch * 2) > a && (start + ruch * 2) < a * a - a)
    {
        // jesli tak to tworzy sie sciezka oraz wywolujemy funkcje dla nastepnego polozenia
        mapa[start + ruch] = 0;
        mapa[start + 2 * ruch] = 0;
        generowanie_planszy(mapa, a, start + ruch * 2, rand() % 4, 0);
    }

    // jesli nie mozna utowrzyc sciezki wybieramy inny kierunek sprawdzania i wywolujemy funkcje
    generowanie_planszy(mapa, a, start, (kierunek + 1) % 4, licznik + 1);
}

void zapis_wyniku(char *nick, int pkt, int tryb)
{
    char nick_inne[20];
    int pkt_inne, i = 0;
    char *nazwa_pliku;
    char c;

    // otwieramy strumienie plikow
    FILE *plik_w, *plik_r;

    // wybieramy odpowiedni plik do nadpisania
    switch (tryb)
    {
    case 9:
        nazwa_pliku = "ranking/ranking9x9.txt";
        break;
    case 15:
        nazwa_pliku = "ranking/ranking15x15.txt";
        break;
    case 23:
        nazwa_pliku = "ranking/ranking23x23.txt";
        break;
    default:
        return;
    }

    plik_r = fopen(nazwa_pliku, "r");

    fseek(plik_r, 0, SEEK_END);

    // patrzymy czy plik jest pusty
    if (ftell(plik_r) == 0)
    {
        plik_w = fopen(nazwa_pliku, "w");
        fprintf(plik_w, "%s %d\n", nick, pkt);
        fclose(plik_r);
        fclose(plik_w);
        return;
    }

    fseek(plik_r, 0, SEEK_SET);

    // tworzymy plik tymczasowy aby moc posortowac wyniki
    plik_w = fopen("tmp.txt", "w+");

    while (1)
    {
        // odczytujemy dane z pliku ktory istanial
        fscanf(plik_r, "%s %d", nick_inne, &pkt_inne);

        if (feof(plik_r))
        {
            if (i == 0)
            {
                // kopiujemy dane do pliku tymczasowego
                fprintf(plik_w, "%s %d\n", nick, pkt);
            }
            break;
        }

        // warunek sprawdzajacy kto ma wiecej punktow
        if (pkt_inne < pkt && i == 0)
        {

            fprintf(plik_w, "%s %d\n", nick, pkt);
            i = 1;
        }

        // kopiowanie wynikow reszty graczy
        fprintf(plik_w, "%s %d\n", nick_inne, pkt_inne);
    }

    fclose(plik_r);

    fclose(plik_w);

    plik_w = fopen(nazwa_pliku, "w+");

    plik_r = fopen("tmp.txt", "r");

    // kopiowanie posrtowanych danych do odpowiedniego pilku
    while ((c = fgetc(plik_r)) != EOF)
    {
        fputc(c, plik_w);
    }

    fclose(plik_w);

    fclose(plik_r);

    remove("tmp.txt");
}

void zapis_gry(char *mapa, int a, int czas)
{
    // otwieranie strumienia pliku z zapisem gry
    FILE *plik = fopen("save/lastsave.txt", "w");

    // kopiowanie wielkosci mapy (pierwsza liczba w pliku)
    fprintf(plik, "%d ", a);

    // kopiowanie mapy (ciag 0, 1 oraz jedna 2)
    for (int i = 0; i < a * a; i++)
    {
        fprintf(plik, "%d ", mapa[i]);
    }

    // kopiowanie czasu ktory uplynal
    fprintf(plik, "%d", czas);

    fclose(plik);
}

void wyswietalnie_planszy(char *mapa, int a)
{
    clear_moj();

    printf("\033[0;36m");

    // podmiana 0 na sciany, 1 na przejscia, 2 na gracza, oraz 4 na sciezke przy rozwiazaniu labiryntu automatycznie
    for (int i = 0; i < a * a; i++)
    {
        switch (mapa[i])
        {
        case 1:
            printf("[-]");
            break;
        case 0:
            printf("   ");
            break;
        case 2:
            printf("\033[0;33m");
            printf("\\o/");
            printf("\033[0;36m");
            break;
        case 3:
            printf("\033[0;33m");
            printf("XXX");
            printf("\033[0;36m");
            break;
        case 4:
            printf("   ");
            break;
        }
        if (i % a == a - 1)
        {
            printf("\n");
        }
    }

    printf("\033[0;32m");

    printf("\nINSTRUKCJA: ");
    printf("\nPoruszanie sie - strzalki");
    printf("\nZapis i wyjscie - x");
    printf("\nWyjscie bez zapisu - v");
    printf("\nRozwiazanie labiryntu - n\n");

    printf("\033[0m");
}

int przejdz_labirynt(char *mapa, int a, int start, int stop, int kierunek, int licznik)
{
    int ruch;

    // powrot funkcji gdy w kazdym z 4 kierunkow nie ma przejscia
    if (licznik > 3)
    {
        return 0;
    }

    // jesli dojdziemy do konca funkcja zwraca jeden i zapelnia sciezke rozwiazaniem
    if (start == stop)
    {
        mapa[start] = 3;
        return 1;
    }

    // wybor kierunku
    switch (kierunek)
    {
    case 0:
        ruch = 1;
        break;
    case 1:
        ruch = -1;
        break;
    case 2:
        ruch = -a;
        break;
    case 3:
        ruch = a;
        break;
    }

    // warunek sprawdzajacy czy jest sciezka ktora da sie przejsc
    if (mapa[start + ruch] == 0)
    {
        // stawianie niewidzialnych scian na rozdroazach
        mapa[start + ruch] = 4;

        // warunek ktory znalezc droga od startu do stopu w labiryncie
        if (przejdz_labirynt(mapa, a, start + ruch * 2, stop, rand() % 4, 0) == 1)
        {
            mapa[start + ruch] = 3;
            mapa[start] = 3;
            return 1;
        }
    }

    // sprawdzanie innych kierunkow
    przejdz_labirynt(mapa, a, start, stop, (kierunek + 1) % 4, licznik + 1);
}

char *utworzenie_planszy(int a)
{

    char *mapa;
    int start = rand() % a + a;

    // alokacja pamieci na mape
    mapa = (char *)malloc(a * a * sizeof(char));

    // zapelnianie jedynkami(scianami) tablicy ktora reprezentuje mape
    for (int i = 0; i < a * a; i++)
    {
        mapa[i] = 1;
    }

    // generowanie miejsca startowego losowo
    if (start % 2 == 1)
    {
        start += 1;
    }
    if (start == 2 * a)
    {
        start -= 2;
    }
    if (start == 2 * a - 1)
    {
        start -= 1;
    }
    if (start == a)
    {
        start += 1;
    }

    mapa[start] = 0;

    // generowanie mapy
    generowanie_planszy(mapa, a, start, rand() % 4, 0);

    // generowanie miejsca koncowego
    int stop;

    do
    {
        stop = rand() % a + a * (a - 2);
        if (stop % 2 == 1)
        {
            stop += 1;
        }
        if (stop == a * (a - 1))
        {
            stop -= 2;
        }
        if (stop == a * (a - 1) - 1)
        {
            stop -= 1;
        }
    } while (mapa[stop] == 1);

    // ustawianie gracza na pozycji startowej
    mapa[start - a] = 2;

    // utworzenie wyjscia
    mapa[stop + a] = 0;

    return mapa;
}

void nowa_gra(char *mapa, int a, int czas_zapis)
{
    int ruch, punkty;
    int start, stop;
    char klawisz;
    char imie[20];
    clock_t czas;

    clear_moj();

    wyswietalnie_planszy(mapa, a);

    czas = clock();

    // znalezienie pozycji gracza
    for (int i = 0; i < a * a; i++)
    {
        if (mapa[i] == 2)
        {
            ruch = i;
            break;
        }
    }

    // Sterowanie
    while (ruch < a * a - a)
    {

        // oblsuga strzalek jako chodzenie po labiryncie
        klawisz = getch();
        if (klawisz != 224)
        {
            switch (klawisz)
            {

            // strzalka w dol
            case 72:
                if (mapa[ruch - a] == 0)
                {
                    mapa[ruch] = 0;
                    mapa[ruch - a] = 2;
                    ruch -= a;
                    wyswietalnie_planszy(mapa, a);
                }
                break;

            // strzalka w lewo
            case 75:
                if (mapa[ruch - 1] == 0)
                {
                    mapa[ruch] = 0;
                    mapa[ruch - 1] = 2;
                    ruch -= 1;
                    wyswietalnie_planszy(mapa, a);
                }
                break;

            // strzalka w prawo
            case 77:
                if (mapa[ruch + 1] == 0)
                {
                    mapa[ruch] = 0;
                    mapa[ruch + 1] = 2;
                    ruch += 1;
                    wyswietalnie_planszy(mapa, a);
                }
                break;

            // strzalka w gore
            case 80:
                if (mapa[ruch + a] == 0)
                {
                    mapa[ruch] = 0;
                    mapa[ruch + a] = 2;
                    ruch += a;
                    wyswietalnie_planszy(mapa, a);
                }
                break;

            // zapis i wyjscie z gry
            case 'x':
                zapis_gry(mapa, a, czas);
                free(mapa);
                return;

            // wyjscie z gry bez zapisu
            case 'v':
                free(mapa);
                return;

            // przejscie labiryntu
            case 'n':
                // usuniecie awatara gracza z mapy
                mapa[ruch] = 0;

                // znalezienie wejscia
                for (int i = 0; i < a; i++)
                {
                    if (mapa[i] == 0)
                    {
                        start = i;
                    }
                }

                // znalezienie wyjscia
                for (int i = a * a - a; i < a * a; i++)
                {
                    if (mapa[i] == 0)
                    {
                        stop = i;
                    }
                }

                // podmiana wejscia i wyjscia na sciany
                mapa[start] = 1;
                mapa[stop] = 1;

                // sprawdzenie czy da sie przejsc labirynt
                if (przejdz_labirynt(mapa, a, start + a, stop - a, rand() % 4, 0) == 0)
                {
                    printf("ERROR 404");
                    getchar();
                }

                // podmiana wyjsc na rozwiazanie labiryntu
                mapa[start] = 3;
                mapa[start + a] = 3;
                mapa[stop] = 3;

                wyswietalnie_planszy(mapa, a);
                free(mapa);
                getch();

                return;
            }
        }
    }

    // punktacja
    czas = clock() - czas + czas_zapis;

    // punktacja 5.2s to (1/5.2)*10000 punktow
    punkty = (int)((1 / (((float)czas) / CLOCKS_PER_SEC)) * 10000);

    clear_moj();

    // zapis nazwy gracza do rankingu dla rankingowych wersji gry oraz wyswietlenie wyniku niestandarodwych map
    if (a == 9 || a == 15 || a == 23)
    {
        napis_labirynt();

        printf("\n\n\033[0;36m                                       ####################################");
        printf("\n                                       ##                                ##");
        printf("\n                                            Czas przejscia: %.2f s", ((float)czas) / CLOCKS_PER_SEC);
        printf("\n                                       ##                                ##");
        printf("\n                                            Punkty: %d pkt", punkty);
        printf("\n                                       ##                                ##");
        printf("\n                                       ####################################");
        printf("\n\n                                          Nazwa gracza (max 20 znakow): \033[0m");
        scanf("%s", imie);
    }
    else
    {
        napis_labirynt();

        printf("\n\n\033[0;36m                                       ####################################");
        printf("\n                                       ##                                ##");
        printf("\n                                            Czas przejscia: %.2f s", ((float)czas) / CLOCKS_PER_SEC);
        printf("\n                                       ##                                ##");
        printf("\n                                            Punkty: %d pkt", punkty);
        printf("\n                                       ##                                ##");
        printf("\n                                       ####################################\033[0m\n");
        getch();
    }

    // zwolnienie pamieci po przejsciu mapy
    free(mapa);

    zapis_wyniku(imie, punkty, a);
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
            nowa_gra(utworzenie_planszy(9), 9, 0);
            return;
        case '2':
            nowa_gra(utworzenie_planszy(15), 15, 0);
            return;
        case '3':
            nowa_gra(utworzenie_planszy(23), 23, 0);
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
            nowa_gra(utworzenie_planszy(wielkosc), wielkosc, 0);
            return;
        case '5':
            return;
        default:
            printf("\nNIEPOPRAWNY WYBOR!");
            getch();
        }
    } while (1);

    printf("\033[0m");

    nowa_gra(utworzenie_planszy(wielkosc), wielkosc, 0);
}

void tworzenie_plikow()
{
    // otwarcie strumienia dla folderow
    DIR *folder;

    // sprawdzenie czy dane foldery istnieja jesli nie to utowrzenie ich
    if ((folder = opendir("ranking")) == NULL)
    {
        system("mkdir ranking");
    }
    closedir(folder);
    if ((folder = opendir("save")) == NULL)
    {
        system("mkdir save");
    }
    // closedir(folder);
    if ((folder = opendir("custommaps")) == NULL)
    {
        system("mkdir custommaps");
    }
    closedir(folder);

    // otwarcie strumienia dla plikow
    FILE *plik;

    // sprawdzenie czy dane pliki istnieja jesli nie to utworzenie ich
    if (!czy_plik_istnieje("ranking/ranking9x9.txt"))
    {
        plik = fopen("ranking/ranking9x9.txt", "w+");
        fclose(plik);
    }
    if (!czy_plik_istnieje("ranking/ranking15x15.txt"))
    {
        plik = fopen("ranking/ranking15x15.txt", "w+");
        fclose(plik);
    }
    if (!czy_plik_istnieje("ranking/ranking23x23.txt"))
    {
        plik = fopen("ranking/ranking23x23.txt", "w+");
        fclose(plik);
    }
}

int main()
{
    // ustawienie poczatkowe liczb pseudolosowych
    srand(time(NULL));

    // sprawdzenie czy pliki potrzebne do dzialania programu istnieja
    tworzenie_plikow();

    // wyswietlenie menu glownego
    menu();

    return 0;
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
            menu_nowa_gra(0);
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
