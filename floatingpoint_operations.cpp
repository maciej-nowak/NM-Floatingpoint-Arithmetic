#include<iostream>
#include<string>
#include<sstream>
#include<math.h>
#include<cstdlib>
#include<cmath>

using namespace std;

//ZAMIENIANIE LICZBY W DOUBLE NA STRING------------------------------------------------------------------
string doubleToString(double a)
{
    string number;
    if(a < -14.00 || a > 15.00) //sprawdzamy zakres podanej liczby
    {
        number = "inf";
        return number;
    }
    else //liczba miesci sie w zakresie
    {
        stringstream os;
        os<<a;
        number = os.str();
        return number;
    }
}

//ZAMIENIANIE LICZBY W INT NA STRING---------------------------------------------------------------------
string intToString(int a)
{
    ostringstream ss;
    ss << a;
    string str = ss.str();
    return str;
}

//ZAMIENIANIE LICZBY W STRING NA DOUBLE------------------------------------------------------------------
 double stringToDouble(string s)
 {
     istringstream i(s);
     double x;
     if (!(i >> x)) return 0;
     return x;
 }

//ZAMIENIANIE LICZBY W STRING NA INT-----------------------------------------------------------------------
 int stringToInt(string a)
 {
     int i;
     istringstream iss(a);
     iss >> i;
     return i;
 }

//ZAMIENIANIE DZIESIETNEJ CZESCI CALKOWITEJ LICZBY NA DWOJKOWA CZESC CALKOWITA-----------------------------
 string integerPartToBinary(int a) //np.: 5 -> 101
 {
     string x, z;
     if(a == 0) z = "0"; //dla podanej liczby = 0, zwracamy 0 dwojkowo
     while(a >= 1) //dla pozostalych liczb standardowo wyliczamy postac binarna
     {
         if(a%2 == 0) x = x + "0";
         else x = x + "1";
         a = a/2;
     }

     for(int i=x.length()-1; i>=0; i--) z = z + x[i]; //otrzymany wynik nalezy jeszcze odwrocic
     return z;
 }

//ZAMIENIANIE DZIESIETNEJ CZESCI ULAMKOWEJ LICZBY NA DWOJKOWA CZESC ULAMKOWA-------------------------------
 string fractionPartToBinary(double a) //np.: 0.75 -> 0.11
 {
     double start;
     start = a;
     string x;
     for(int i=1; i<=10; i++) //standardowy sposob zamiany biarnej na ulamek
     {
         start = start * 2;
         if(start >= 1.00)
         {
             start = start - 1.0;
             x = x + "1";
         }
         else x = x + "0";
     }
     return x;
 }

//ZAMIENIANIE DWOJKOWEJ CZESCI CALKOWITEJ LICZBY NA DZIESIETNA CZESC CALKOWITA------------------------------
 int binToInt(string a) //np.: 5 -> 101
 {
     int suma = 0;
     int j = 0;
     for(int i=a.length()-1; i>=0; i--) //standardowa procedura zamiany
     {
         if(a[i] == '1') suma = suma + pow(2, j);
         j++;
     }
     return suma;
 }

//ZAMIENIANIE DWOJKOWEJ CZESCI ULAMKOWEJ LICZBY NA DZIESIETNA CZESC ULAMKOWA--------------------------------
 double binToFraction(string a, int p) //np.: 0.11 -> 0.75
 {
     double suma = 0.0;
     for(int i=0; i<10-p; i++) //standardowy sposob zamiany
     {
         if(a[i] == '1') suma = suma + pow(0.50, i+1);
     }
     return suma;
 }

//ZAMIENIANIE LICZBY DZIESIETNEJ NA BINARNY ZAPIS ARYTMETYKI (KODOWANIE)------------------------------------
string changeToString(double liczba)
{
    string a = doubleToString(liczba); //np.: 5.5 string
    string finalNumber = "";
    bool znakPlus = true;

    //jesli liczba jest ujemna, ustawiamy zmienna znaku, a ze stringa liczby ucinamy znak '-'
    if(a[0] == '-')
    {
        znakPlus = false;
        string b = a;
        a = "";
        for(int i=1; i<b.length(); i++)
        {
            a = a + b[i];
        }
    }

    //jesli liczba jest inf (tzn. spoza zakresu <-14, 15> konczymy dzialanie zwracajac inf
    if(a == "inf")
    {
        finalNumber = "inf";
        return finalNumber;
    }

    //jesli liczba jest z zakresu, dokonujemy przekstzalcen
    else
    {
        string integerPart = "", fractionPart = "0.", tempNumber = "", binaryNumber = "", mantysa = "", cecha = "", znak = "", finalNumber;
        size_t found = a.find("."); //indeks kropki dziesietnej

        //jesli liczba zawiera czesc ulamkowa
        if(found != string::npos)
        {
            //wydzielamy czesc calkowita, np.: 5.25 -> 5, a takze czesc ulamkowa np.: 5.25 -> 25
            for(int i=0; i<found; i++) integerPart = integerPart + a[i];
            for(int i=found+1; i<a.length(); i++) fractionPart = fractionPart + a[i];

            //konwertujemy otrzymane wyniki do stringa
            int integerPart2 = stringToInt(integerPart);
            double fractionPart2 = stringToDouble(fractionPart);

            //zamieniamy czesc calkowita do zapisu binarnego np.: 5 -> 101
            tempNumber = integerPartToBinary(integerPart2);

            //zamieniamy liczbe do postaci znormalizowanej np.: 101 -> 1.01
            //nastepnie rozszerzamy o czesc ulamkowa np.: ulamek = 11, calkowita znormalizowana 1.01, calosc -> 1.0111
            if(tempNumber != "0") binaryNumber = "1.";
            else binaryNumber = "0.";
            for(int i=1; i<=tempNumber.length()-1; i++) binaryNumber = binaryNumber + tempNumber[i];
            binaryNumber = binaryNumber + fractionPartToBinary(fractionPart2);

            //dla liczby z zakresu >=1
            int cechaTemp;
            if(binaryNumber[0] == '1')
            {
                //wyznaczamy mantyse np.: 1.0111000000 -> 0111000000
                for(int i=2; i<=11; i++) mantysa = mantysa + binaryNumber[i];

                //wyznaczamy ceche (dziesietnie) korzystajac z ilosci przesuniec
                //nastepnie zamieniamy na dwojkowo (ewentualnie uzupelniamy 0 z przodu)
                cechaTemp = 15 + tempNumber.length()-1;
                cecha = integerPartToBinary(cechaTemp);
                for(int i=1; i<=5 - cecha.length(); i++) cecha = "0" + cecha;

                //wyznaczamy bit znaku i zwracamy ostateczna liczbe w arytmetyce np.: 0 10001 0000000000
                if(znakPlus == true) znak = "0";
                else znak = "1";
                finalNumber = znak + cecha + mantysa;
            }

            //dla liczb z zakresu <1
            else if(binaryNumber[0] == '0')
            {
                //wyznaczamy mantyse np.: 0.0111000000 -> 0111000000
                size_t found = binaryNumber.find("1");
                for(int i=found+1; i<=11; i++) mantysa = mantysa + binaryNumber[i];

                //wyznaczamy ceche (dziesietnie) korzystajac z indeksu pierwszej 1
                //nastepnie zamieniamy na dwojkowo (ewentualnie uzupelniamy 0 z przodu)
                cechaTemp = 16 - found;
                cecha = integerPartToBinary(cechaTemp);
                for(int i=1; i<=5 - cecha.length(); i++) cecha = "0" + cecha;

                //wyznaczamy bit znaku i zwracamy ostateczna liczbe w arytmetyce np.: 0 01111 1000000000
                if(znakPlus == true) znak = "0";
                else znak = "1";
                finalNumber = znak + cecha + mantysa;
            }
            return finalNumber;
        }

        //jesli liczba nie zawiera czesci ulamkowej
        else
        {
            //ustawiamy czesci calkowite i ulamkowe
            integerPart = a;
            fractionPart = "0";

            //konwertujemy wyznaczone czesci do typow liczbowych
            double fractionPart2 = stringToDouble(fractionPart);
            int integerPart2 = stringToInt(integerPart);

            //zamieniamy czesc calkowita do zapisu binarnego np.: 5 -> 101
            tempNumber = integerPartToBinary(integerPart2);

            //zamieniamy liczbe do postaci znormalizowanej np.: 101 -> 1.01
            //nastepnie rozszerzamy o czesc ulamkowa = 0 np.: calkowita znormalizowana 1.01, calosc -> 1.010
            binaryNumber = "1.";
            for(int i=1; i<=tempNumber.length()-1; i++) binaryNumber = binaryNumber + tempNumber[i];
            binaryNumber = binaryNumber + fractionPartToBinary(fractionPart2);

            //wyznaczamy mantyse np.: 1.0111000000 -> 0111000000
            for(int i=2; i<=11; i++) mantysa = mantysa + binaryNumber[i];

            //wyznaczamy ceche (dziesietnie) korzystajac z ilosci przesuniec
            //nastepnie zamieniamy na dwojkowo (ewentualnie uzupelniamy 0 z przodu)
            int cechaTemp = 15 + tempNumber.length()-1;
            cecha = integerPartToBinary(cechaTemp);
            for(int i=1; i<=5 - cecha.length(); i++) cecha = "0" + cecha;

            //wyznaczamy bit znaku i zwracamy ostateczna liczbe w arytmetyce np.: 0 10001 0000000000
            if(znakPlus == true) znak = "0";
            else znak = "1";
            finalNumber = znak + cecha + mantysa;

            //szczegolne przypadki dla 0 i -0
            if(doubleToString(liczba) == "0") finalNumber = "0000000000000000";
            else if(doubleToString(liczba) == "-0") finalNumber = "1000000000000000";
            return finalNumber;
        }
    }
}

//ZAMIENIANIE LICZBY ZAPISANEJ W ARYTMETYCE NA LICZBE DZIESIETNA (DEKODOWANIE)-------------------------------
double changeToDouble(string liczba)
{
    string znak, cecha, mantysa, temp, calosc = "";
    int przesuniecie, jednosci;
    double ulamek, calkowita, koncowa;

    //dla liczby inf zwracamy wartosc INFINITY
    if(liczba == "inf")
    {
        koncowa = INFINITY;
        return koncowa;

    }

    //specjalne przypadki dla 0 oraz -0
    if(liczba == "0000000000000000")
    {
        koncowa = 0;
        return koncowa;
    }
    if(liczba == "1000000000000000")
    {
        koncowa = -0;
        return koncowa;
    }

    //dzielimy otrzymany lancuch na czesci: znak, ceche i mantyse oraz wyznaczamy przesuniecie
    znak = liczba[0];
    cecha = liczba.substr(1,5);
    mantysa = liczba.substr(6,10);
    przesuniecie = binToInt(cecha) - 15;

    //jesli przesuniecie nie jest ujemne, wowczas jest to liczba z zakresu >=1
    if(przesuniecie >= 0)
    {
        //wyznaczamy czesc calkowita korzystajac z bitow mantysy (ilosc przesuniec)
        //np.: 0 10001 0000000000, przesuniecie = 2 (10001 = 17 = 15 + 2), dwa pierwsze bity mantysy 00, calosc = 100
        temp = "1" + liczba.substr(6,przesuniecie);
        jednosci = binToInt(temp);

        //wyznaczamy czesc ulamkowa korzystajac z pozostalych bitow mantysy
        //np.: 0 10001 0000000000, przesuniecie = 2, zostaje = 00000000
        temp = "";
        temp = liczba.substr(6+przesuniecie, 10-przesuniecie);
        ulamek = binToFraction(temp, przesuniecie);

        //wyznaczamy znak i zwracamy koncowa liczbe
        if(znak == "1") calosc = "-";
        calkowita = jednosci + ulamek;
        calosc = calosc + doubleToString(calkowita);
        koncowa = stringToDouble(calosc);
        return koncowa;
    }

    //jesli przesuniecie jest ujemne, wowczas jest to liczba z zakresu <1
    else if(przesuniecie < 0)
    {
        //wyznaczamy tylko czesc ulamkowa powstala ze wszystkich bitow mantysy
        //np.: 0 01110 0000000000, przesuniecie = -2, mantysa = 0000000000, czesc ulamkowa 10000000000
        for(int i=-1; i>przesuniecie; i--) temp = temp + "0";
        temp = temp + "1" + liczba.substr(6,10);
        ulamek = binToFraction(temp, 0);

        //wyznaczamy znak i zwracamy koncowa liczbe
        if(znak == "1") calosc = "-";
        calkowita = 0 + ulamek;
        calosc = calosc + doubleToString(calkowita);
        koncowa = stringToDouble(calosc);
        return koncowa;
    }
}

//FUNKCJA NIE UZYWANA
/*string arythmeticToBinary(string liczba)
{
    string znak, cecha, mantysa, temp, calosc = "", koncowa, ulamek, calkowita = "", jednosci;
    int przesuniecie;

    if(liczba == "inf")
    {
        koncowa = "INFINITY";
        return koncowa;
    }

    znak = liczba[0];
    cecha = liczba.substr(1,5);
    mantysa = liczba.substr(6,10);
    przesuniecie = binToInt(cecha) - 15;
    temp = "1" + liczba.substr(6,przesuniecie);
    jednosci = temp;
    temp = "";
    temp = liczba.substr(6+przesuniecie, 10-przesuniecie);
    ulamek = temp;
    //if(znak == "1") calosc = "-";
    //calkowita = calosc + jednosci + "." + ulamek;
    calkowita = calosc + jednosci + "." + ulamek;
    return calkowita;
}
*/

//ZWYKLE DODAWANIE LICZB BINARNYCH O DLUGOSCI 11 ZNAKOW (1.MANTYSA) BEZ KROPKI
string add01(string a, string b)
{
    //uzywane zmienne
    int carry = 0, j = 0;
    int sumaKontrolna;
    string suma, sumaKoncowa;

    //dodawanie bit po bicie z uwzglednieniem przeniesienia
    for(int i=10; i>=0; i--)
    {
        //tworzenie i sprawdzanie sumy kontrolnej i ustawienie przeniesienia
        sumaKontrolna = 0;
        if(a[i] == '1') sumaKontrolna++;
        if(b[i] == '1') sumaKontrolna++;
        if(carry == 1) sumaKontrolna++;
        carry = 0;
        if(sumaKontrolna == 0) suma = suma + "0";
        else if(sumaKontrolna == 1) suma = suma + "1";
        else if(sumaKontrolna == 2) {suma = suma + "0"; carry = 1;}
        else if(sumaKontrolna == 3) {suma = suma + "1"; carry = 1;}
        j++;
    }

    //dodawanie ostatniego przeniesienia lub aktualizacja ostatniego indeksu, zapis liczb od tylu
    if(carry == 1) suma = suma + "1";
    else j = j-1;
    for(int i=j; i>=0; i--) sumaKoncowa = sumaKoncowa + suma[i];
    return sumaKoncowa;
}

//DODAWANIE DWOCH LICZB ZAPISANYCH W ARYTMETYCE
double add(string a, string b)
{
    //sprawdzamy czy liczba nie przekroczy zakresu
    double liczbaKoncowa;
    double A = changeToDouble(a); //uzywamy wczesniej stworzonej funkcji aby sprawdzic liczbe w typie double
    double B = changeToDouble(b);
    if(A+B > 15 || A+B < -14)
    {
        liczbaKoncowa = INFINITY;
        return liczbaKoncowa;
    }

    //specjalne przypadki dla 0 oraz -0
    if(a == "0000000000000000" || a == "1000000000000000")
    {
        liczbaKoncowa = B;
        return liczbaKoncowa;
    }
    else if(b == "0000000000000000" || b == "1000000000000000")
    {
        liczbaKoncowa = A;
        return liczbaKoncowa;
    }

    //dzielimy lancuchy na czesci: znak, ceche i mantyse oraz wyznaczamy przesuniecie (wykladnik)
    string koncowy, mantysaA, mantysaB;
    char znakA = a[0];
    string cechaA = a.substr(1,5);
    int przesuniecieA = binToInt(cechaA) - 15;
    mantysaA = "1" + a.substr(6,10);
    char znakB = b[0];
    string cechaB = b.substr(1,5);
    int przesuniecieB = binToInt(cechaB) - 15;
    mantysaB = "1" + b.substr(6,10);

    //jesli przesuniecie jednej z liczb jest mniejsze niz drugiej, wowczas sprowadzamy liczby (mantysy) do tego samego przesuniecia (wykladnika)
    //np.: A = 1.1 * 2^3    B = 1.0 * 2^5   -->     A = 0.011 * 2^5
    if(przesuniecieA - przesuniecieB < 0)
    {
        int przesuniecie = (przesuniecieA - przesuniecieB)*-1;
        for(int i=1; i<=przesuniecie; i++) mantysaA = "0" + mantysaA;
    }
    else if(przesuniecieA - przesuniecieB > 0)
    {
        int przesuniecie = przesuniecieA - przesuniecieB;
        for(int i=1; i<=przesuniecie; i++) mantysaB = "0" + mantysaB;
    }

    //ewentualnie dluzsze podciagi obcinamy do 11 bitow (utrata danych)
    mantysaA = mantysaA.substr(0,11);
    mantysaB = mantysaB.substr(0,11);

    //dodawanie liczby ujemnej do dodatniej
    if((a[0] == '1' && b[0] == '0') || (a[0] == '0' && b[0] == '1'))
    {
        //liczbe ujemna zamieniamy na U2 czyli zamieniamy bity i dodajemy 1
        //innymi slowy - znajdujemy pierwsza od konca 1 bitowa i do tego miejsca zamieniamy bity
        //np.: 1001010000 -> w U2: 0110110000
        if(a[0] == '1' && b[0] == '0') //zamieniamy pierwsza liczbe
        {
            int k;
            for(int i=10; i>=0; i--)
            {
                if(mantysaA[i] == '1')
                {
                    k = i;
                    break;
                }
            }
            for(int i=0; i<=k-1; i++)
            {
                if(mantysaA[i] == '1') mantysaA[i] = '0';
                else mantysaA[i] = '1';
            }
        }
        else if(a[0] == '0' && b[0] == '1') //zamieniamy druga liczbe
        {
            int k;
            for(int i=10; i>=0; i--)
            {
                if(mantysaB[i] == '1')
                {
                    k = i;
                    break;
                }
            }
            for(int i=0; i<=k-1; i++)
            {
                if(mantysaB[i] == '1') mantysaB[i] = '0';
                else mantysaB[i] = '1';
            }
        }

        //dodajemy liczby i ucinamy do 11 bitow (liczac od konca) uzyskujac postac 1.mantysa (bez kropki)
        koncowy = add01(mantysaA, mantysaB);

        //wstawiamy kropke dziesietna 11000000000  -->  1.1000000000
        string pomocniczy = koncowy.substr(koncowy.length() - 10, 10);
        koncowy = koncowy.substr(0, koncowy.length()-10);
        int przesuniecieDod = koncowy.length()-10;
        koncowy = koncowy + "." + pomocniczy;

        //wyznaczamy aktualne przesuniecie dwoch liczb (bierzemy wieksze i odejmujemy ilosc powstalych przesuniec po dodaniu)
        //ucinamy do 10 bitow, bez pierwszej jedynki uzyskujac nowa mantyse (brakujace bity uzupelniamy zerami)
        //znajdujemy pierwsza 1 po kropce - wyznacza nam ilosc dodatkowych powstalych przesuniec
        //np.: 1.00110011 ->  00110011  --> 1 na 2 indeksie, czyli na 3 miejscu, wiec do postaci znormalizowanej -3 przesuniecia
        int przesuniecie;
        if(przesuniecieA > przesuniecieB) przesuniecie = przesuniecieA;
        else przesuniecie = przesuniecieB;
        size_t found = pomocniczy.find("1");
        if(found > 11) found = 0;
        przesuniecie = przesuniecie - found - 1;
        koncowy = pomocniczy.substr(found+1, 10);
        for(int i=1; i<=10 - koncowy.length(); i++) koncowy = koncowy + "0";

        //wyznaczamy ceche bitowa
        przesuniecie = przesuniecie + 15;
        string cecha = integerPartToBinary(przesuniecie);
        for(int i=1; i<=5 - cecha.length(); i++) cecha = "0" + cecha;

        //ustawiamy znak liczby
        string znak;
        if(A+B < 0) znak = "1";
        else znak = "0";

        //sklejamy czesci bitowe liczby i konwertujemy liczbe do double
        string liczba = znak + cecha + koncowy;
        liczba = liczba.substr(0,16);
        liczbaKoncowa = changeToDouble(liczba);
    }

    //dodawanie liczb dwoch dodatnich lub dwoch ujemnych
    if((a[0] == '0' && b[0] == '0') || (a[0] == '1' && b[0] == '1'))
    {
        //dodajemy liczby bitowo
        koncowy = add01(mantysaA, mantysaB);

        //wstawiamy kropke dziesietna 11000000000  -->  1.1000000000
        string pomocniczy = koncowy.substr(koncowy.length() - 10, 10);
        koncowy = koncowy.substr(0, koncowy.length()-10);
        koncowy = koncowy + "." + pomocniczy;

        //wyznaczamy aktualne przesuniecie dwoch liczb
        //(bierzemy wieksze przesuniecie + 15 i dodajemy ilosc przesuniec powstalych po dodawaniu)
        int przesuniecie;
        if(przesuniecieA > przesuniecieB) przesuniecie = przesuniecieA + 15;
        else przesuniecie = przesuniecieB + 15;
        size_t found = koncowy.find(".");
        przesuniecie = przesuniecie + found - 1;

        //wyznaczamy ceche bitowa
        string cecha = integerPartToBinary(przesuniecie);
        for(int i=1; i<=5 - cecha.length(); i++) cecha = "0" + cecha;

        //ustawiamy znak liczby
        string znak;
        if(a[0] == '0') znak = "0";
        else znak = "1";

        //sklejamy czesci bitowe liczby i konwertujemy liczbe do double
        string pomocniczy2 = koncowy.substr(1, found - 1) + pomocniczy;
        string liczba = znak + cecha + pomocniczy2;
        liczba = liczba.substr(0,16);
        liczbaKoncowa = changeToDouble(liczba);
    }
    return liczbaKoncowa;
}

//DZIELENIE DWOCH LICZB ZAPISANYCH W ARYTMETYCE - NIEDOKONCZONE
double div(string a, string b)
{
    //sprawdzamy czy liczba nie przekroczy zakresu i czy nie dokonujemy dzielenia przez 0
    double liczbaKoncowa;
    double A = changeToDouble(a);
    double B = changeToDouble(b);
    if(B == 0)
    {
        liczbaKoncowa = NAN;
        return liczbaKoncowa;
    }

    if(A/B > 15 || A/B < -14)
    {
        liczbaKoncowa = INFINITY;
        return liczbaKoncowa;
    }

    //dzielimy lancuchy na czesci: znak, ceche i mantyse oraz wyznaczamy przesuniecie (wykladnik)
    string koncowy, mantysaA, mantysaB;
    char znakA = a[0];
    string cechaA = a.substr(1,5);
    int przesuniecieA = binToInt(cechaA) - 15;
    mantysaA = "1" + a.substr(6,10);
    char znakB = b[0];
    string cechaB = b.substr(1,5);
    int przesuniecieB = binToInt(cechaB) - 15;
    mantysaB = "1" + b.substr(6,10);

    //ewentualnie dluzsze podciagi obcinamy do 11 bitow (utrata danych)
    mantysaA = mantysaA.substr(0,11);
    mantysaB = mantysaB.substr(0,11);

    //wstawiamy kropke dziesietna 11000000000  -->  1.1000000000
    string pomocniczy = koncowy.substr(koncowy.length() - 10, 10);
    koncowy = koncowy.substr(0, koncowy.length()-10);
    int przesuniecieDod = koncowy.length()-10;
    koncowy = koncowy + "." + pomocniczy;

    //logika dzielenia - brak implementacji

    liczbaKoncowa = 1;
    return liczbaKoncowa;
}

//MNOZENIE DWOCH LICZB ZAPISANYCH W ARYTMETYCE
double mul(string a, string b)
{
    //sprawdzamy czy liczba nie przekroczy zakresu
    double liczbaKoncowa = 0;
    double A = changeToDouble(a);
    double B = changeToDouble(b);
    if(A*B > 15 || A*B < -14)
    {
        liczbaKoncowa = INFINITY;
        return liczbaKoncowa;
    }

    //specjalne przypadki dla 0 oraz -0 (nie ma sensu wtedy liczyc)
    if(a == "0000000000000000" || a == "1000000000000000" || b == "0000000000000000" || b == "1000000000000000")
    {
        liczbaKoncowa = 0;
        return liczbaKoncowa;
    }

    //dzielimy lancuchy na czesci: znak, ceche i mantyse oraz wyznaczamy przesuniecie (wykladnik)
    string koncowy, mantysaA, mantysaB;
    char znakA = a[0];
    string cechaA = a.substr(1,5);
    int przesuniecieA = binToInt(cechaA) - 15;
    mantysaA = "1" + a.substr(6,10);
    char znakB = b[0];
    string cechaB = b.substr(1,5);
    int przesuniecieB = binToInt(cechaB) - 15;
    mantysaB = "1" + b.substr(6,10);

    //tablica przechowujaca wyniki mnozenia (zerowana, a nastepnie uzupelniania w odpowiednich miejscach 1)
    int tab[11][21];
    for(int i=0; i<=10; i++)
    {
        for(int j=0; j<=20; j++) tab[i][j] = 0;
    }
    for(int i=10; i>=0; i--)
    {
        if(mantysaB[i] == '1')
        {
            for(int j=0; j<=10; j++) tab[10-i][i+10-j] = mantysaA[10-j] - 48;
        }
        else continue;
    }

    //sprowadzanie wymnozonych liczb w rzadku (tablica) do jednej liczby (bitowej)
    string koncowa;
    int suma, przesuniecie = 0, licznikPrzesuniec = 0;
    for(int i=20; i>=0; i--)
    {
        suma = 0;
        for(int j=0; j<=10; j++)
        {
            suma = suma + tab[j][i];
        }
        suma = suma + przesuniecie;
        przesuniecie = suma/2;
        koncowa = intToString(suma%2) + koncowa;
    }
    while(przesuniecie > 0)
    {
        licznikPrzesuniec++;
        koncowa = intToString(przesuniecie%2) + koncowa;
        przesuniecie = przesuniecie/2;
    }

    //dodajemy przesuniecia (wykladniki) i wyznaczamy znak
    string cechaAB =  integerPartToBinary(przesuniecieA + przesuniecieB + 15 + licznikPrzesuniec);
    for(int i=1; i<=5 - cechaAB.length(); i++) cechaAB = "0" + cechaAB;
    string znakAB;
    if((znakA == '0' && znakB == '0') || (znakA == '1' && znakB == '1')) znakAB = "0";
    else znakAB = "1";

    //zamiana otrzymanej liczby do arytmetyki, a nastepnie do double
    koncowa = znakAB + cechaAB + koncowa.substr(1,10);
    liczbaKoncowa = changeToDouble(koncowa);
    return liczbaKoncowa;
}

int main()
{
    double doubleA, doubleB;
    string stringA, stringB;

    while(true)
    {
        cout<<"The program supports adding and multiplication (division still not finished) activities on floating point arithmetic fl16"<<endl<<"Range of numbers supplied -14 : 15"<<endl;
        cout<<"GIVE NUMBERS: A i B"<<endl;
        cin>>doubleA>>doubleB;
        system("CLS");

        stringA = changeToString(doubleA);
        cout<<"INPUT: "<<doubleA<<endl;
        cout<<"ARITHMETIC: "<<stringA<<endl;
        doubleA = changeToDouble(stringA);
        cout<<"OUTPUT: "<<doubleA<<endl<<endl;

        stringB = changeToString(doubleB);
        cout<<"INPUT: "<<doubleB<<endl;
        cout<<"ARITHMETIC: "<<stringB<<endl;
        doubleB = changeToDouble(stringB);
        cout<<"OUTPUT: "<<doubleB<<endl<<endl;

        cout<<"ADDING: "<<add(stringA, stringB)<<endl;
        cout<<"MULTIPLICATION: "<<mul(stringA, stringB)<<endl;
    	//cout<<"DIVISION: "<<div(stringA, stringB)<<endl;
    }

    return 0;
}
