#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

struct historia
{
    char tab[6][6];
};

struct gracz
{
    char g;
};

void rysuj_plansze(char tab[][6], gracz* pionek)
{
    for (int i = 0; i < 6; i++)
    {
        cout << endl;
        cout << char(186) << "------------------------------------------------" << char(186) << endl << char(186);
        for (int j = 0; j < 6; j++)
        {
            cout << "\t";
            if (tab[i][j] == 'O') cout << pionek[0].g;
            else if (tab[i][j] == 'X') cout << pionek[1].g;
            else cout << tab[i][j];

            cout << char(186);
        }
    }
    cout << endl << char(186) << "------------------------------------------------" << char(186) << endl;
}

char sprawdz_poziom(char tab[][6])
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (tab[i][j] == 'X' && tab[i][j + 1] == 'X' && tab[i][j + 2] == 'X' && tab[i][j + 3] == 'X' && tab[i][j + 4] == 'X')
                return 'X';
            if (tab[i][j] == 'O' && tab[i][j + 1] == 'O' && tab[i][j + 2] == 'O' && tab[i][j + 3] == 'O' && tab[i][j + 4] == 'O')
                return 'O';
        }
    }
    return ' ';
}
char sprawdz_pion(char tab[][6])
{
    for (int j = 0; j < 6; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            if (tab[i][j] == 'X' && tab[i + 1][j] == 'X' && tab[i + 2][j] == 'X' && tab[i + 3][j] == 'X' && tab[i + 4][j] == 'X')
                return true;
            if (tab[i][j] == 'O' && tab[i + 1][j] == 'O' && tab[i + 2][j] == 'O' && tab[i + 3][j] == 'O' && tab[i + 4][j] == 'O')
                return true;
        }
    }
    return ' ';
}

char sprawdz_skos(char tab[][6])
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (tab[i][j] == 'X' && tab[i + 1][j + 1] == 'X' && tab[i + 2][j + 2] == 'X' && tab[i + 3][j + 3] == 'X' && tab[i + 4][j + 4] == 'X')
                return true;
            if (tab[i][j] == 'O' && tab[i + 1][j + 1] == 'O' && tab[i + 2][j + 2] == 'O' && tab[i + 3][j + 3] == 'O' && tab[i + 4][j + 4] == 'O')
                return true;
        }
    }
    return ' ';
}
char sprawdz_skos2(char tab[][6])
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 5; j > 3; j--)
        {
            if (tab[i][j] == 'X' && tab[i + 1][j - 1] == 'X' && tab[i + 2][j - 2] == 'X' && tab[i + 3][j - 3] == 'X' && tab[i + 4][j - 4] == 'X')
                return true;
            if (tab[i][j] == 'O' && tab[i + 1][j - 1] == 'O' && tab[i + 2][j - 2] == 'O' && tab[i + 3][j - 3] == 'O' && tab[i + 4][j - 4] == 'O')
                return true;
        }
    }
    return ' ';
}

bool wygrana(char tab[][6])
{
    cout << endl;
    if (sprawdz_poziom(tab) == 'O' || sprawdz_pion(tab) == 'O' || sprawdz_skos(tab) == 'O' || sprawdz_skos2(tab) == 'O')
    {
        cout << "\tWygral gracz 1";
        return true;
    }
    else if (sprawdz_poziom(tab) == 'X' || sprawdz_pion(tab) == 'X' || sprawdz_skos(tab) == 'X' || sprawdz_skos2(tab) == 'X')
    {
        cout << "\tWygral gracz 2";
        return true;
    }
    else return false;

    int licznik = 0;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            if (tab[i][j] != ' ')
                licznik++;

    if (licznik == 36)
    {
        cout << "REMIS";
        return true;
    }
    return false;
}

void pokaz_historie(historia* h, gracz* pionek, int licznik)
{
    int a = 0;
    rysuj_plansze(h[a].tab, pionek);
    char ad;
    for (int i = 0; i < licznik; i++)
    {
        cout << "a d";
        cin >> ad;
        if (ad == 'a')
            a++;
        else if (ad == 'd')
            a--;

        rysuj_plansze(h[a].tab, pionek);
    }
}

void undo(historia* h, char tab[][6], gracz* pionek, int licznik)
{
    int cofnij, ile;
    if (licznik - 4 > 0)
        cofnij = licznik - 4;
    else if (licznik - 3 > 0)
        cofnij = licznik - 3;
    else cofnij = licznik - 2;

    for (int i = licznik - 1; i > cofnij; i--) {
        rysuj_plansze(h[i].tab, pionek);
        system("pause");
    }

    do {
        cout << "Ile ruchow cofnac? 1...4: ";
        cin >> ile;
    } while (ile > 4);

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            tab[i][j] = h[licznik - ile].tab[i][j];
        }
    }
}

int main()
{
    char predef[6][6] = { {' ','X',' ',' ','O',' '},
                                          {'O','O','X','O','X',' '},
                                          {' ','O',' ',' ',' ',' '},
                                          {'O','O',' ',' ',' ',' '},
                                          {'X','O','O',' ','X',' '},
                                          {' ','X',' ',' ','X','X'} };

    historia* h = new historia[36];

    double czas_gry;

    char tab[6][6];
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            tab[i][j] = ' ';
        }
    }

    clock_t start, stop;
    string imie1, imie2;
    cout << "Imie gracza 1: "; cin >> imie1;
    cout << "Imie gracza 2: "; cin >> imie2;
  
    gracz* pionek = new gracz[2];
    //pionek[0].g = 'O';
    //pionek[1].g = 'X';
    cout << "Pionek gracza pierwszego: "; cin >> pionek[0].g;
    cout << "Pionek gracza drugiego: "; cin >> pionek[1].g;
    while (pionek[0].g == pionek[1].g)
    {
        cout << "Zetony: ";
        cin >> pionek[0].g >> pionek[1].g;

    }
  
    cout << "Podaj czas calej rozgrywki w sekundach: ";
    cin >> czas_gry;

    double c[2] = { czas_gry,czas_gry };

    int pion = 0;
    char opcja;
    cout << "\t1. Pentago" << endl;
    cout << "\t2. Kolko i krzyzyk" << endl;
    cin >> opcja;
    while (opcja != '1' && opcja != '2')
    {
        cout << "\t1. Pentago" << endl;
        cout << "\t2. Kolko i krzyzyk" << endl;
        cin >> opcja;
    };


    int licznik_historia = 0;

    for (;;)
    {
        if (pion == 0)
        {
            cout << "\t" << pionek[pion].g << "\t" << imie1 << "\t" << c[pion] << endl;
        }
        else
            cout << "\t" << pionek[pion].g << "\t" << imie2 << "\t" << c[pion] << endl;
        start = clock();
        cout << "Wpisz miejsce gdzie wstawic gracza" << endl;
        char miejsce, liczba;
        int nLiczba;
        int wiersz = 10, kolumna = 10;

        do
        {
            rysuj_plansze(tab, pionek);
            cout << "Podaj pole 1...9 w wybranej czesci planszy: ";
            cin >> liczba;
            while (liczba < '1' || liczba >'9')
            {
                cout << "Podaj pole od 1 do 9 w wybranej czesci: ";
                cin >> liczba;
            };
            cout << "Wybierz cwiartke q/w/a/s : " << endl;
            cout << " MENU: " << endl;
            cout << " 1. Zmiana zetonu[m]" << endl;
            cout << " 2. Pauza[p]" << endl;
            cout << " 3. Opis programu[h]" << endl;
            cout << " 4. Undo - cofniecie ruchu[u]" << endl;
            cout << " 5. Wyswietl przykladowa plansze[o]" << endl;
          
            cin >> miejsce;
            nLiczba = (int)liczba - 48;

            switch (miejsce)
            {
            case 'q':
                wiersz = (nLiczba - 1) / 3;
                kolumna = (nLiczba - 1) % 3;
                break;
            case 'w':
                wiersz = (nLiczba - 1) / 3;
                kolumna = ((nLiczba - 1) % 3) + 3;
                break;
            case 'a':
                wiersz = ((nLiczba - 1) / 3) + 3;
                kolumna = (nLiczba - 1) % 3;
                break;
            case 's': wiersz = ((nLiczba - 1) / 3) + 3;
                kolumna = ((nLiczba - 1) % 3) + 3;
                break;
            case 'o':

                for (int i = 0; i < 6; i++)
                {
                    for (int j = 0; j < 6; j++)
                    {
                        tab[i][j] = predef[i][j];
                    }
                }
                rysuj_plansze(tab, pionek);

                break;

            case 'm':
            {
              
                cout << "Zmien zetony: ";
                cin >> pionek[0].g >> pionek[1].g;
                while (pionek[0].g == pionek[1].g)
                {
                    cout << "Zetony: ";
                    cin >> pionek[0].g >> pionek[1].g;
                   
                }
                break;
            }
            case 'p': system("cls"); system("pause"); rysuj_plansze(tab, pionek); break;
            case 'h': cout << "Opis programu: Celem obu graczy jest ulozenie w rzędzie lub po skosie 5 kulek swojego koloru, analogicznie do gry kolko i krzyzyk. Gracze po kolei oddaja ruch składajacy się z 2 elementow: dolozenia nowej kulki oraz obrocenia czesci planszy o 90 stopni w dowolnym kierunku. Plansza sklada się z 4 ruchomych części, ktore mozna obracac." << endl; break;
            case 'u': undo(h, tab, pionek, licznik_historia); break;
            default: cout << "Bledne dane";
            }
        } while ((wiersz == 10 && kolumna == 10) || tab[wiersz][kolumna] != ' ');

        if (pion == 0)
        {
            pion++;
            tab[wiersz][kolumna] = 'O';
        }
        else
        {
            pion--;
            tab[wiersz][kolumna] = 'X';
        }

        //jesli pentago (obroc plansze)
        if (opcja == '1')
        {
            rysuj_plansze(tab, pionek);
            char strona;
            cout << "Wybierz cwiartke q/w/a/s ktora chcesz obrocic: ";
            cin >> miejsce;
            while (miejsce != 'q' && miejsce != 'w' && miejsce != 'a' && miejsce != 's')
            {
                switch (miejsce)
                {
                case 'q':
                    wiersz = 0;
                    kolumna = 0;
                    break;
                case 'w':
                    wiersz = 0;
                    kolumna = 3;
                    break;
                case 'a':
                    wiersz = 3;
                    kolumna = 0;
                    break;
                case 's': wiersz = 3;
                    kolumna = 3;
                    break;
                default: cin >> miejsce;
                }
            };
            cout << "Strona obrotu z - zgodnie ze wskazowkami zegara, x - przeciwnie: ";
            cin >> strona;
            while (strona != 'z' && strona != 'x')
            {
                cout << "Strona obrotu z lub x: ";
                cin >> strona;
            };

            int obrotowa[3][3];
            for (int i = wiersz; i < wiersz + 3; i++)
            {
                for (int j = kolumna; j < kolumna + 3; j++)
                {
                    obrotowa[i - wiersz][j - kolumna] = tab[i][j];

                }
            }

            if (strona == 'z')
            {
                int n = 3, temp;
                for (int i = 0; i < n / 2; i++)
                {
                    for (int j = i; j < n - i - 1; j++)
                    {
                        temp = obrotowa[n - j - 1][i];
                        obrotowa[n - j - 1][i] = obrotowa[n - i - 1][n - j - 1];
                        obrotowa[n - i - 1][n - j - 1] = obrotowa[j][n - i - 1];
                        obrotowa[j][n - i - 1] = obrotowa[i][j];
                        obrotowa[i][j] = temp;
                    }
                }
            }
            else
            {
                int N = 3;
                for (int x = 0; x < N / 2; x++)
                {
                    for (int y = x; y < N - x - 1; y++)
                    {
                        int temp = obrotowa[x][y];
                        obrotowa[x][y] = obrotowa[y][N - 1 - x];
                        obrotowa[y][N - 1 - x] = obrotowa[N - 1 - x][N - 1 - y];
                        obrotowa[N - 1 - x][N - 1 - y] = obrotowa[N - 1 - y][x];
                        obrotowa[N - 1 - y][x] = temp;
                    }
                }
            }


            for (int i = wiersz; i < wiersz + 3; i++)
            {
                for (int j = kolumna; j < kolumna + 3; j++)
                {
                    tab[i][j] = obrotowa[i - wiersz][j - kolumna];

                }
            }
        }

        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 6; j++)
                h[licznik_historia].tab[i][j] = tab[i][j];

        licznik_historia++;




        if (wygrana(tab))
            pokaz_historie(h, pionek, licznik_historia);
        rysuj_plansze(tab, pionek);
        stop = clock();
        c[pion] -= (double)(stop - start) / CLOCKS_PER_SEC;
        if (c[pion] <= 0)
            cout << "KONIEC GRY\tPRZEGRAL:  " << pionek[pion].g;
    }


    return 0;
}