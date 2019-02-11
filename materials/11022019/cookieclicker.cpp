#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // magiczne wartosci Windowsa
    int wcisnieto = 1;
    int wcisniete = 0x8000;

    // zmieniamy tytuł okienka
    SetConsoleTitle("Ciasteczkowy Klikacz");

    // pytamy sie o rozmiary naszego okienka
    CONSOLE_SCREEN_BUFFER_INFO csbi;    
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int szerokosc = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int wysokosc = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    
    string ciastko = "ciastko";
    int multiplier = 11;

    int wynik = 0;
    // staramy sie wczytac poprzedni wynik
    ifstream wynik_plik_in("_wynik.txt");
    if(!(wynik_plik_in >> wynik))
        wynik = 0;
    wynik_plik_in.close();
    
    bool trzeba_odrysowac = true;
    bool zalicz_wcisniecie = false;
    // mamy nieskończoną pętle
    while(true) {
        // konczymy
        if(GetKeyState('Q') & wcisniete) {
            // wypisujemy wiadomosc
            // czyscimy ekran
            system("cls");
            // chcemy narysowac to na srodku
            for(int i = 0; i < (wysokosc / 2); ++i)
                cout << endl;
            
            ciastko = "do zobaczenia.";

            // i na srodku srodka
            for(int i = 0; i < (szerokosc / 2 - ciastko.size() / 2); ++i)
                cout << " ";
            cout << ciastko << endl;

            // wciskamy klawisz na koniec byle jaki
            _getch(); _getch();
            system("cls"); // znowu czyscimy
            return 0;
        }

        // kiedy wcisniemy spacje to aktualizujemy wynik
        if(GetKeyState(VK_SPACE) & wcisniete) {
            if(zalicz_wcisniecie == true) {
                wynik += multiplier;
                // zapisujemy nowy wynik
                ofstream wynik_plik_out("_wynik.txt");
                wynik_plik_out << wynik;
                wynik_plik_out.close();

                ciastko = "_*ciastko*_";

                // cout << "SPACJA" << endl;
                trzeba_odrysowac = true;
                zalicz_wcisniecie = false;
            }
        } else if(!zalicz_wcisniecie) {
            ciastko = "ciastko";

            trzeba_odrysowac = true;
            zalicz_wcisniecie = true;
        }

        // rysujemy wszystko
        if(trzeba_odrysowac) {
            // czyscimy ekran
            system("cls");
            // chcemy narysowac to na srodku
            for(int i = 0; i < (wysokosc / 2); ++i)
                cout << endl;
            
            // i na srodku srodka
            for(int i = 0; i < (szerokosc / 2 - ciastko.size() / 2); ++i)
                cout << " ";
            cout << ciastko << endl;

            int dlugosc_wynik = 0;
            int tmp = wynik;
            while(tmp) {
                dlugosc_wynik += 1;
                tmp /= 10;
            }

            for(int i = 0; i < (szerokosc / 2 - (7 + dlugosc_wynik) / 2); ++i)
                cout << " ";
            cout << "wynik: " << wynik << endl;

            trzeba_odrysowac = false;
        }
    }

    

    return 0;
}