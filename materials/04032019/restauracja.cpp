#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/*
    I. Trzymac aktualny kuchni(czyli jakie dania sa dostepne i ile kazdego nich jest na stanie)
    II. Oblusgiwac zakupy(ktos moze podac liste dan ktore chcialby zamowic i go podliczamy)
    III. Oblugiwac dostawy(czyli dodajemy nowe dania, oraz zwiekszamy ich dostawy)
*/

// danie_nazwa
vector<string> d_nazwa;
// danie_cena
vector<float> d_cena;
// danie_ilosc
vector<int> d_ilosc;

void wypisz_stan() {
    cout << "------ RESTAURACJA ------" << endl;
    cout << "-------------------------" << endl;
    cout << "  nazwa  | ilosc | cena " << endl;

    /*
        for i in range(len(d_nazwa)):
            print(d_nazwa[i], d_ilosc[i], d_cena[i])
    */
    for(int i = 0; i < d_nazwa.size(); ++i) {
        cout << d_nazwa[i] << "\t | " << d_ilosc[i] << "\t | " << d_cena[i] << endl;
    }
}


int main() {
    string n;
    float c;
    int i;
    ifstream info("_stan.info");
    while(info >> n >> i >> c) {
        d_nazwa.push_back(n);
        d_ilosc.push_back(i);
        d_cena.push_back(c);
    }
    info.close();

    wypisz_stan();

    while(true) {
        int q;
        cin >> q;

        if(q == 0) {
            ofstream infoz("_stan.info"); 
            for(int i = 0; i < d_nazwa.size(); ++i) {
                if(d_ilosc[i] > 0) {
                    infoz << d_nazwa[i] << " " << d_ilosc[i] << " " << d_cena[i] << endl;
                }
            }
            return 0;
        }

        if(q == 1) {
            cout << " NOWE ZAMOWIENIE " << endl;
            cout << "Podaj liczbe dan: " << endl;

            int l;
            cin >> l;

            string danie;
            float rachunek = 0;
            for(int i = 0; i < l; ++i) {
                cin >> danie;


                /*

                    k = ["siemka", "dwa", "trzy"]
                    .push_back(nazwa)
                    .append(nazwa)
                    len(k)
                */

                for(int j = 0; j < d_nazwa.size(); ++j) {
                    if(danie == d_nazwa[j]) {
                        if(d_ilosc[j] > 0) {
                            cout << "ZAMOWNIE PRZYJETE" << endl;

                            rachunek += d_cena[j];
                            d_ilosc[j] -= 1;
                        } else {
                            cout << "ZAMOWNIE ODRZUCONE. DANIE NIEDOSTEPNE" << endl;
                        }
                    }
                }
            }

            cout << "KOSZT ZAMOWIENIA: " << rachunek << endl;
        }

        if(q == 2) {
            cout << "DOSTAWA" << endl;

            cin >> n >> i >> c;
            int istnieje = 0;
            for(int i = 0; i < d_nazwa.size(); ++i) {
                if(d_nazwa[i] == n) {
                    istnieje = 1;
                    d_ilosc[i] += i;
                }
            }

            if(istnieje == 0) {
                d_nazwa.push_back(n);
                d_cena.push_back(c);
                d_ilosc.push_back(i);
            }
        }

        wypisz_stan();
    }

    return 0;
}
