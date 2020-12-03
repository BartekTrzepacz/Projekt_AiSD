#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;
int String_to_int(string str)//funkcja zmieniaj¹ca zmienne typu string na int
{
    int numer = 0, symb_to_int;
    for(int i = 0; i<str.length(); i++)
    {
        symb_to_int = str[i]; // przetwarzanie kodu ASSCI od symbolu str[i] do zmiennej typu int
        {
        if(symb_to_int<58 && symb_to_int>47) // jeżeli 47 < ASCII < 58 -> symb_to_int - to liczba
            numer+=(symb_to_int-48)*pow(10, str.length()-i-1); // zapisywanie duzych liczb typu string jako int np. 532=10^2*5+10*3+10^0+1
        }
    }
    if(str[0]=='-') // sprawdzamy czy liczba jest ujemna, jeżeli tak to mnożymy ją przez samą siebie aby była dodatnia
        numer -= 2*numer;
    return numer;
}
void rozwiaz_problem(string path_in, string path_out)
{
    string line, ten_numer="";
    ifstream in(path_in); // otwieramy plik wejściowy typu path_in
    ofstream out(path_out); // otwieramy plik wyjściowy typu path_out
    cout << endl;
    int symb_to_int, n=0, m=0;
    while(getline(in, line)) // idziemy po każdej lini pliku "in" i liczymy ilość wierszy w tym pliku
        m++;
    in.clear(); // po zliczeniu ilości wierszy przechodzimy do początku pliku
    in.seekg(0);
    bool started = false;
    while(!in.eof()) // sprawdzamy każdy znak z pliku "in"
    {
        string x;
        in >> x;
        if(x=="|" && started==false) // jeżeli pierwszym znakiem jest " | " oznacza to rozpoczęcie wiersza
        {
            started = true;
            continue;
        }
        if(x=="|" && started==true) // jeżeli drugi raz w tym samym wierszu spotkamy znak " | " oznacza to jego koniec
            break; // wychodzimy z pętli
        n++;
    }
    cout << "m : "<< m << endl << "n : " << n << endl; // otrzymujemy liczbe kolumn i wierszy
    in.clear(); // przechodzimy do początku pliku "in"
    in.seekg(0);
    int i =0, j=0;
    int macierz[m][n];
    while(getline(in, line)) // kolejny raz wczytujemy każdy wiersz z pliku "in"
    {
        for(int a = 0; a<line.length(); a++) // przechodzimy po każdym symbolu danego wierszy
        {
            symb_to_int = line[a];
            if(symb_to_int<58 && symb_to_int>47 || symb_to_int==45) // jeżeli 47 < ASCII < 58 -> symb_to_int - to liczba, dodatkowo może być ujemna
            {
                ten_numer+=line[a]; // zwiększamy ten_numer o symbol line[a] jeżeli jest liczbą lub "-"
            }
            else
                if (ten_numer!="") // jeżeli ten_numer jest liczbą lub "-" zapisujemy do w macierzy
                {
                    macierz[i][j] = String_to_int(ten_numer);
                    j++;
                    ten_numer = ""; // przetwarzamy puste pole do zmiennej ten_numer
                }
                if(symb_to_int==10) // jeżeli symb_to_int==10 czyli "\n" tworzymy nowy wiersz w macierzy
                    i++;
        }
    }
    cout << endl << endl;
    for(int i=0; i<m; i++) // poniżej wypisujemy macierz w programie tak samo jak w pliku wejściowym
    {
        for(int j=0; j<n; j++)
        cout << setw(3) << macierz[i][j];
        cout << endl;
    }
    i=0; j=-1;
    int alfa = 0, k=0;
    string output;
    int wszystkie_kierunki[][2] = {{0,1},{1,0},{0,-1},{-1,0}}; // wektory kierunków po których bedziemy się przemieszczać
    int obecny_kierunek;
    while(alfa < m && alfa < n)
    {
        alfa+=k%2; // zwiększamy alfe co każde 2 zmiany kierunku o resztę z dzielenia przez 2
        obecny_kierunek = k%4; // zmieniamy kierunek
        int dlugosc[2]={0,0};
        while(dlugosc[0]<m-alfa && dlugosc[1]<n-alfa)
        {
            i=i+wszystkie_kierunki[obecny_kierunek][0];
            j+=wszystkie_kierunki[obecny_kierunek][1];
            dlugosc[0]+=abs(wszystkie_kierunki[obecny_kierunek][0]);    //rozwijanie macierzy po spirali
            dlugosc[1]+=abs(wszystkie_kierunki[obecny_kierunek][1]);
            output +=to_string(macierz[i][j]) + " ";
            cout << setw(3) << macierz[i][j];
        }
        k++;
    }
    if(m>n && n-alfa == 0) // ten warunek jest potrzebny do wypisania ostatnich liczb z macierzy w przypadku gdy liczba wierszy jest większa od liczby kolumn
    {
        int dlugosc[2]={0,0};
        while(dlugosc[0]<m-alfa)
        {
            i=i+wszystkie_kierunki[obecny_kierunek][0];
            j+=wszystkie_kierunki[obecny_kierunek][1];
            dlugosc[0]+=abs(wszystkie_kierunki[obecny_kierunek][0]); // rozwijanie macierzy po spirali
            dlugosc[1]+=abs(wszystkie_kierunki[obecny_kierunek][1]);
            cout << setw(3) << macierz[i][j];
            output +=to_string(macierz[i][j]) + " ";
        }
    }
    out << output; // wypisywanie do pliku out
}
int main()
{
    rozwiaz_problem("input.txt", "output.txt"); // funkcja ktora rozwiązuje główny problem. Przyjmuje ona dwa argumenty "input.txt" oraz "output.txt"
    return 0;
}

