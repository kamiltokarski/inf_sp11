#include <conio.h>
#include <Windows.h>
#include <iostream>
using namespace std;

void wyp_srod(string s, int sr) {
    for(int i = 0; i < (sr - s.size() / 2); ++i)
        cout << " ";
    cout << s << endl;
}

int main() {
    // magiczne wartosci
    int wcisniecie = 0x8000;

    // tytul okienka
    SetConsoleTitle("Kolko czy Krzyzyk");

    // rozmiary okienka
    CONSOLE_SCREEN_BUFFER_INFO okno;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &okno);
    int szer = okno.srWindow.Right - okno.srWindow.Left + 1;
    int wys = okno.srWindow.Bottom - okno.srWindow.Top + 1;

    // co aktualnie robimy w programie
    // 0 = menu
    // 1 = PvP
    // 2 = PvPC
    int ekran = 0;

    // menu
    // ktora opcje aktualnie zaznaczamy
    int zaz_opcja = 1;

    // czy powinnismy rysowac ekran
    bool rysuj = true;
    bool konczmy = false;
    while(true) {
        if(GetKeyState('Q') & wcisniecie)
            konczmy = true;
        if(GetKeyState(VK_DOWN) & wcisniecie) {
            if(ekran == 0) {
                zaz_opcja = zaz_opcja + 1;
                if(zaz_opcja > 3)
                    zaz_opcja = 1;
                rysuj = true;
            }
        }
        if(GetKeyState(VK_UP) & wcisniecie) {
            if(ekran == 0) {
                zaz_opcja = zaz_opcja - 1;
                if(zaz_opcja < 1)
                    zaz_opcja = 3;
                rysuj = true;
            }
        }
        if(GetKeyState(VK_SPACE) & wcisniecie) {
            if(ekran == 0) {
                if(zaz_opcje == 1) {
                    ekran = 1;
                    rysuj = true;
                }

                if(zaz_opcja == 2) {
                    konczmy = true;
                }
                if(zaz_opcja == 3) {
                    konczmy = true;
                }
            }
        }

        if(ekran == 0) {
            if(rysuj == true) {
                string opt1 = "PvP";
                string opt2 = "PvPC(losowe)";
                string opt3 = "PvPC(harde)";

                if(zaz_opcja == 1)
                    opt1 = "*_* " + opt1 + " *_*";
                if(zaz_opcja == 2)
                    opt2 = "*_* " + opt2 + " *_*";
                if(zaz_opcja == 3)
                    opt3 = "*_* " + opt3 + " *_*";

                system("cls");

                cout << " menu";
                for(int i = 0; i < (wys / 2 - 2); ++i) {
                    cout << endl;
                }

                wyp_srod(opt1, szer / 2); 
                wyp_srod(opt2, szer / 2); 
                wyp_srod(opt3, szer / 2); 

                rysuj = false;
                Sleep(50);
            }
        }

        if(konczmy) {
            // czyscimy ekran
            system("cls");

            // rysujemy na srodku wiadomosc koncowa
            for(int i = 0; i < (wys / 2); ++i)
                cout << endl;
            wyp_srod("do zobaczenia.", szer / 2);

            Sleep(2000);
            system("cls");
            return 0;
        }
    }

    return 0;
}
