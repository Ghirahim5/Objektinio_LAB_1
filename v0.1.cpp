#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

struct Studentas {
    string v;
    string p;
    double egz_rez;
    int n;
    double* nd_rez;
    double nd_sum = 0;
    double nd_vid;
    double rez;
    double mediana;
};

int main() {

    int m;
    string pasirinkimas;

    // Studentu skaiciaus ivestis

    cout << "Iveskite studentu skaiciu" << endl;
    while (!(cin >> m) || cin.peek() != '\n' || m <= 0) {
        cout << "Neteisinga ivestis, prasome ivesti skaiciu" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Studentas* Duomenys = new Studentas[m];

    // Vardo ivestis

    for (int i = 0; i < m; i++) {

        cout << "Koks jusu vardas?" << endl;
        bool valid_v = true;
        do {
            if (!(cin >> Duomenys[i].v)) {
                valid_v = false;
            }
            else {
                valid_v = true;
                for (char c : Duomenys[i].v) {
                    if (!isalpha(c)) {
                        valid_v = false;
                        break;
                    }
                }
            }
            if (!valid_v) {
                cout << "Neteisinga ivestis, prasome ivesti savo varda sudaryta tik is raidziu" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (!valid_v);

        // Pavardes ivestis

        cout << "Kokia jusu pavarde?" << endl;
        bool valid_p = true;
        do {
            if (!(cin >> Duomenys[i].p)) {
                valid_p = false;
            }
            else {
                valid_p = true;
                for (char c : Duomenys[i].p) {
                    if (!isalpha(c)) {
                        valid_p = false;
                        break;
                    }
                }
            }
            if (!valid_p) {
                cout << "Neteisinga ivestis, prasome ivesti savo pavarde sudaryta tik is raidziu" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (!valid_p);

        // Egzamino rezultato ivestis

        cout << "Koks buvo jusu egzamino rezultatas?" << endl;
        while (!(cin >> Duomenys[i].egz_rez) || Duomenys[i].egz_rez < 0 || Duomenys[i].egz_rez > 10) {
            cout << "Neteisinga ivestis, prasome ivesti skaiciu 10-baleje sistemoje" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Namu darbu skaiciaus ivestis

        cout << "Kiek namu darbu atlikote?" << endl;
        while (!(cin >> Duomenys[i].n) || Duomenys[i].n > 0) {
            cout << "Neteisinga ivestis, prasome ivesti skaiciu" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        Duomenys[i].nd_rez = new double[Duomenys[i].n];

        // Namu darbu rezultatu ivedimas ir sumos skaiciavimas

        for (int j = 0; j < Duomenys[i].n; j++) {
            cout << "Koks buvo " << j + 1 << "-o namu darbo vertinimas?" << endl;
            while (!(cin >> Duomenys[i].nd_rez[j]) || Duomenys[i].nd_rez[j] <= 0 || Duomenys[i].nd_rez[j] > 10 || cin.peek() != '\n') {
                cout << "Neteisinga ivestis, prasome ivesti skaiciu 10-baleje sistemoje" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Koks buvo " << i + 1 << "-o namu darbo vertinimas?" << endl;
            }
            Duomenys[i].nd_sum += Duomenys[i].nd_rez[j];
        }

        // Namu darbu masyvo rusiavimas

        sort(Duomenys[i].nd_rez, Duomenys[i].nd_rez + Duomenys[i].n);

        // Medianos skaiciavimas

        if (Duomenys[i].n % 2 == 0) {
            Duomenys[i].mediana = (Duomenys[i].nd_rez[Duomenys[i].n / 2 - 1] + Duomenys[i].nd_rez[Duomenys[i].n / 2]) / 2.0;
        }
        else {
            Duomenys[i].mediana = Duomenys[i].nd_rez[Duomenys[i].n / 2];
        }
    }
    
    // Rezultatu spausdinimas pasirenkant Vid. arba Med.

    cout << "Kaip norite matyti savo galutini bala? Irasykite viena is dvieju pasirinkimu: (Vid. / Med.)" << endl;
    cin >> pasirinkimas;
    cout << endl;

    while (pasirinkimas != "Vid." && pasirinkimas != "Med.") {
        cout << "Pasirinkite arba 'Vid.' arba 'Med.'" << endl;
        cin >> pasirinkimas;
    }

        if (pasirinkimas == "Vid.") {
            cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Vid.)" << endl;
            cout << "-----------------------------------------------" << endl;
        }
        else if (pasirinkimas == "Med.") {
            cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Med.)" << endl;
            cout << "-----------------------------------------------" << endl;
        }

    for (int i = 0; i < m; i++) {
        if (pasirinkimas == "Vid.") {
            Duomenys[i].nd_vid = Duomenys[i].nd_sum / Duomenys[i].n;
            Duomenys[i].rez = 0.4 * Duomenys[i].nd_vid + 0.6 * Duomenys[i].egz_rez;
            cout << left << setw(15) << Duomenys[i].v << setw(15) << Duomenys[i].p << fixed << setprecision(2) << setw(15) << Duomenys[i].rez << endl;
        }
        else if (pasirinkimas == "Med.") {
            Duomenys[i].rez = 0.4 * Duomenys[i].mediana + 0.6 * Duomenys[i].egz_rez;
            cout << left << setw(15) << Duomenys[i].v << setw(15) << Duomenys[i].p << fixed << setprecision(2) << setw(15) << Duomenys[i].rez << endl;
        }
    }

    for (int i = 0; i < m; i++) {
        delete[] Duomenys[i].nd_rez;
    }
    delete[] Duomenys;

    return 0;
}
