#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;
const int MAXN = 10000;

string nazwy[MAXN];
float ceny[MAXN];


void czysc_ekran() {
    for(int i = 0; i < 100; ++i)
        cout << endl;
}

int main() {
    // podstawowe zmienne
    float koszt_przeszly = 0;
    int ilosc_przedmiotow = 0;
    float koszt_sumaryczny = 0;

    string np = "";
    float cp = 0;


    // wczytywanie informacji
    ifstream wejscie("_list.tmp");
    cout << "MEGA SYSTEM ZAKUPOWv2" << endl;
    while(wejscie >> np >> cp) {
        // hura, kolejne pozycje
        cout << ilosc_przedmiotow << ". " << np << " \t\t" << cp << endl;

        nazwy[ilosc_przedmiotow] = np;
        ceny[ilosc_przedmiotow] = cp;

        koszt_sumaryczny += cp;
        ilosc_przedmiotow += 1;
    }
    cout << "\t\tKoszt sumaryczny: " << koszt_sumaryczny << endl;
    wejscie.close();

    // główna pętla
    char opcja = 0;

    while(true) {
        // pytamy sie co uzytkownik chce zrobic
        cin >> opcja;

        // jezeli wpisze -1 to konczymy
        if(opcja == 'q') {
            ofstream wyjscie("_list.tmp");
            for(int i = 0; i < ilosc_przedmiotow; i++) {
                wyjscie << nazwy[i] << " " << ceny[i] << endl;
            }
            return 0;
        }

        // jezeli wpisze 1 to dodajemy nową rzecz
        if(opcja == '+') {
            cin >> np >> cp;

            koszt_sumaryczny += cp;
            nazwy[ilosc_przedmiotow] = np;
            ceny[ilosc_przedmiotow] = cp;

            ilosc_przedmiotow += 1;

            // czyscimy ekran
            system("cls");

            cout << "MEGA SYSTEM ZAKUPOWv2" << endl;
            for(int i = 0; i < ilosc_przedmiotow; ++i) {
                cout << i << ". " << nazwy[i] << " \t\t" << ceny[i] << endl;
            }
            cout << "\t\tKoszt sumaryczny: " << koszt_sumaryczny << endl;
        }
    }


    // to pomincie
    return 0;
}