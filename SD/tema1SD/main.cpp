/*Copyright Vidrasc Maria 2019*/
#include <iostream>
#include <fstream>
#include <string>
#define N 1000
// #define debug
struct s1 {
    int id;
    int timp;
};
class Concurent 
{
    public:
    int id;
    int punctaj;
    int ultimul_loc;
};
class Clasament 
{ 
    public:
    int n;  // numar concurenti
    Concurent concurenti[N];  // matricea clasament
    Clasament(int n) {
        this->n = n;
        for (int i = 0; i < N; ++i) {
            this->concurenti[i].id = i+1;
            this->concurenti[i].punctaj = 0;
            this->concurenti[i].ultimul_loc = 0;
        }
    }
    // operator= egaleaza 2 structuri Clasament
    void operator=(Clasament& other) {
        this->n = other.n;
        for (int i = 0; i < other.n; i++) {
            this->concurenti[i].id = other.concurenti[i].id;
            this->concurenti[i].punctaj = other.concurenti[i].punctaj;
            this->concurenti[i].ultimul_loc = other.concurenti[i].ultimul_loc;
        }
    }
    ~Clasament() {}
    static void initiere(Clasament& clasament) {
        int n = clasament.n;
        for (int i = 0; i < n; i++) {
            clasament.concurenti[i].id = i+1;
            clasament.concurenti[i].punctaj = 0;
            clasament.concurenti[i].ultimul_loc = 0;
        }
    }
    static void competitie(int timpi[], Clasament& clasament) {
        int n = 0;
        n = clasament.n;
        int pozitii_initiale[N] = {0};
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < n+1; j++) {
                if (clasament.concurenti[i].id == j) {
                    pozitii_initiale[j] = i;
                }
            }
        }
        int p = 0;
        for (int i = 0; i < n; i++) {
            if (timpi[i] != 0) {
                p++;
            }
        }
        struct s1 max[N] = {};
        int a = 0;
        for (int i = 0; i < n; i++) {
            if (timpi[i] != 0) {
                max[a].timp = timpi[i];
                max[a].id = i+1;
                a++;
            }
        }
        for (int i = 0; i < p; i++) {
            for (int j = i+1; j < p; j++) {
                if (max[i].timp > max[j].timp) {
                    struct s1 aux = max[i];
                    max[i] = max[j];
                    max[j] = aux;
                }
            }
        }
        for (int i = p; i < n; i++) {
            max[i].timp = 0;
        }
        for (int i = 0; i < p; i++) {
            if (max[i].timp == max[i + 1].timp) {
                int k = i;
                int e = i;
                while (max[k].timp == max[e+1].timp) {
                    e++;
                }
                for (int i2 = k; i2 < e; i2++) {
                    for (int j2 = i2+1; j2 < e +1; j2++) {
                        if (pozitii_initiale[max[i2].id] >
                        pozitii_initiale[max[j2].id]) {
                            int aux = max[i2].id;
                            max[i2].id = max[j2].id;
                            max[j2].id = aux;
                        }
                    }
                }
            }
        }
        a = 0;
        int punctaj_cursa[N] = {0};
        if (p%2 == 0) {
            int i = 0;
            while (a != p/2) {
                punctaj_cursa[i] = p/2 - a;
                a++;
                i++;
            }
            a++;
            while (i != p) {
                punctaj_cursa[i] = p/2 - a;
                a++;
                i++;
            }
        } else {
            for (int i = 0; i < p; i++) {
                if (max[i].timp < max[i+1].timp) {
                    punctaj_cursa[i] = p/2 - a;
                    a++;
                } else if (max[i].timp == max[i+1].timp) {
                    punctaj_cursa[i] = p/2 - a;
                    a++;
                }
            }
            punctaj_cursa[p-1] = p/2 - a;
        }
        for (int i = p; i < n; i++) {
            punctaj_cursa[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            clasament.concurenti[pozitii_initiale[
            max[i].id]].punctaj = clasament.concurenti[
            pozitii_initiale[max[i].id]].punctaj +
            punctaj_cursa[i];
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (clasament.concurenti[i].punctaj <
                clasament.concurenti[j].punctaj) {
                    int aux = clasament.concurenti[i].id;
                    clasament.concurenti[i].id =
                    clasament.concurenti[j].id;
                    clasament.concurenti[j].id = aux;
                    aux = clasament.concurenti[i].punctaj;
                    clasament.concurenti[i].punctaj =
                    clasament.concurenti[j].punctaj;
                    clasament.concurenti[j].punctaj = aux;
                    aux = clasament.concurenti[i].ultimul_loc;
                    clasament.concurenti[i].ultimul_loc =
                    clasament.concurenti[j].ultimul_loc;
                    clasament.concurenti[j].ultimul_loc = aux;
                } else if (clasament.concurenti[i].punctaj ==
                clasament.concurenti[j].punctaj) {
                    if (clasament.concurenti[i].id >
                    clasament.concurenti[j].id) {
                        int aux = clasament.concurenti[i].id;
                        clasament.concurenti[i].id =
                        clasament.concurenti[j].id;
                        clasament.concurenti[j].id = aux;
                        aux = clasament.concurenti[i].punctaj;
                        clasament.concurenti[i].punctaj =
                        clasament.concurenti[j].punctaj;
                        clasament.concurenti[j].punctaj = aux;
                        aux = clasament.concurenti[i].ultimul_loc;
                        clasament.concurenti[i].ultimul_loc =
                        clasament.concurenti[j].ultimul_loc;
                        clasament.concurenti[j].ultimul_loc = aux;
                    }
                }
            }
        }
    }
    static void Calculeaza_ultimul_loc(Clasament& clasament,
    Clasament& clasament_vechi, int primul_print) {
        int n = 0;
        n = clasament.n;
        if (primul_print == 1) {
/*vectorul locuri pastreaza pe al catelea loc statea in
clasament_vechi jucatorul cu id corespunzator indicelui vectorului
la care se afla cifra clasamentului sau*/
            int locuri_vechi[N];
            for (int i = 0; i < n; i++) {
                for (int j = 1; j < n+1; j++) {
                    if (clasament_vechi.concurenti[i].id == j) {
                        locuri_vechi[j] = i;
                    }
                }
            }
            #ifdef debug
            cout << "\n" << "locuri_vechi " << "\n";
            for (int i = 1; i < n+1; i++) {
                cout << locuri_vechi[i] << "\n";
            }
            cout << "end" << "\n";
            #endif
/*vectorul locuri pastreaza pe al catelea loc sta in 
clasament jucatorul cu id corespunzator indicelui vectorului 
la care se afla cifra clasamentului sau*/
                int locuri_noi[N];
                for (int i = 0; i < n; i++) {
                    for (int j = 1; j < n+1; j++) {
                        if (clasament.concurenti[i].id == j) {
                            locuri_noi[j] = i;
                        }
                    }
                }
            #ifdef debug
            cout << "\n" << "locuri_noi " << "\n";
            for (int i = 1; i < n+1; i++) {
                cout << locuri_noi[i] << "\n";
            }
            cout << "end" << "\n";
            #endif
            for (int i = 0; i < n; i++) {
                clasament.concurenti[i].ultimul_loc =
                locuri_vechi[clasament.concurenti[i].id] -
                locuri_noi[clasament.concurenti[i].id];
            }
        }
            #ifdef debug
        cout << "\n" << "clasament.concurenti[i].ultimul_loc " << "\n";
        for (int i = 1; i < n+1; i++)
        {
            cout << clasament.concurenti[i].ultimul_loc << "\n";
        }
            #endif
    }
};
int main() {
    std::ifstream input;
    input.open("races.in", std::ifstream::in);
    std::ofstream output;
    output.open("races.out");
    int n = 0, m = 0, k = 0;
    input >> n >> m >> k;
    // cout << n <<" "<< m <<" "<< k;
    // n = numarul de competitori,
    // m = numarul de curse,
    // k = numarul de print-uri
    int timpi[N] = {0};
    int primul_print = 0;
    Clasament clasament(n);
    Clasament clasament_vechi(n);
    std::string line = "";
    input.ignore();
    input.ignore();
    while (input >> line) {
        // cout <<"-"<< line << "-\n";
        if (line == "print") {
            Clasament::Calculeaza_ultimul_loc(clasament,
            clasament_vechi, primul_print);
            for (int i = 0; i < n; i++) {
                output << clasament.concurenti[i].id << " ";
                output << clasament.concurenti[i].punctaj << " ";
                output << clasament.concurenti[i].ultimul_loc << "\n";
            }
            primul_print = 1;
            clasament_vechi = clasament;
            output << "\n";
        } else {
            timpi[0] = std::stoi(line);
            for (int i = 1; i < n; i++) {
                input >> timpi[i];
            }
            // for(int i = 0; i < n; i++)
            // {
            //     cout << timpi[i] << " ";
            // }
            // cout << "\n";
            input.ignore();
            input.ignore();
            Clasament::competitie(timpi, clasament);
        }
    }
    output.close();
    input.close();
    return 0;
}
