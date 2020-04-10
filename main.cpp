#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
struct Uzytkownik {
    string loginUzytkownika, hasloUzytkownika;
    int numerPorzadkowyUzytkownika;

};

struct Adresat {
    string imieAdresata, nazwiskoAdresata, numerTelefonu, adresEmail, adresZamieszkania;
    int numerPorzadkowy, numerPorzadkowyUzytkownika;

};
void WyborOpcji ( vector<Adresat> &adresaci, int iloscAdresatow, int numerPorzadkowyUzytkownika);
int main();

int WczytajDaneZPliku ( vector<Adresat> &adresaci, int iloscAdresatow, int numerUzytkownikaNaLiscie) {

    adresaci.clear();
    string imieAdresata, nazwiskoAdresata, numerTelefonu, adresEmail, adresZamieszkania, numerPorzadkowy, numerPorzadkowyUzytkownika;
    Adresat nowy;
    int pozycja,  numerUzytkownika;
    string linia;
    fstream plik;
    plik.open("ksiazkaAdresowa.txt",ios::in);
    if (plik.good()) {
        while(getline(plik,linia)) {


            pozycja=linia.find("|");
            numerPorzadkowy=linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);
            pozycja=linia.find("|");
            numerPorzadkowyUzytkownika=linia.substr(0,pozycja);
            numerUzytkownika=atoi(numerPorzadkowyUzytkownika.c_str());
            linia.erase(0,pozycja+1);
            pozycja=linia.find("|");
            imieAdresata=linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);
            pozycja=linia.find("|");
            nazwiskoAdresata=linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);
            pozycja=linia.find("|");
            adresZamieszkania=linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);
            pozycja=linia.find("|");
            numerTelefonu=linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);
            pozycja=linia.find("|");
            adresEmail=linia.substr(0,pozycja);

            if (numerUzytkownika==numerUzytkownikaNaLiscie) {
                nowy.numerPorzadkowy=atoi(numerPorzadkowy.c_str());
                nowy.numerPorzadkowyUzytkownika=numerUzytkownika;
                nowy.imieAdresata=imieAdresata;
                nowy.nazwiskoAdresata=nazwiskoAdresata;
                nowy.adresZamieszkania=adresZamieszkania;
                nowy.numerTelefonu=numerTelefonu;
                nowy.adresEmail=adresEmail;
                adresaci.push_back(nowy);

            }
        }
        plik.close();

        iloscAdresatow=atoi(numerPorzadkowy.c_str());
    }
    return iloscAdresatow;
}
void WyswietlenieDanychAdresata ( vector<Adresat> &adresaci,vector <Adresat> :: iterator itr) {
    cout<<itr-> numerPorzadkowy<<" ";
    cout<<itr-> imieAdresata<<" ";
    cout<<itr-> nazwiskoAdresata<<" ";
    cout<<itr-> adresZamieszkania<<" ";
    cout<<itr-> numerTelefonu<<" ";
    cout<<itr-> adresEmail<<endl;
}
void UsuwanieIZapisywanieDoPliku(  vector<Adresat>&adresaci, vector <Adresat> :: iterator &itr) {

    string linijka;
    fstream pliktymczasowy,plik;
    int  numerPorzadkowy, pozycja;
    string PierwszyNumerLinii;

    plik.open("KsiazkaAdresowa.txt",ios::in);
    if(plik.good()) {
        pliktymczasowy.open("KsiazkaAdresowa_plikTymczasowy.txt",ios::trunc|ios::out);
        if(pliktymczasowy.good()) {
            do {
                getline(plik,linijka);
                if(!plik.eof()) {
                    pozycja=linijka.find("|");
                    PierwszyNumerLinii=linijka.substr(0,pozycja);
                    numerPorzadkowy= atoi(PierwszyNumerLinii.c_str());
                    if (itr->numerPorzadkowy!=numerPorzadkowy) {
                        linijka.append("\n");
                        pliktymczasowy.write(&linijka[0],(unsigned int)linijka.length());
                        pliktymczasowy.flush();
                    } else {

                    }
                }
            } while(!plik.eof());
            pliktymczasowy.close();
        }
        plik.close();
    }
    adresaci.erase(itr);
    remove("KsiazkaAdresowa.txt");
    rename("KsiazkaAdresowa_plikTymczasowy.txt", "KsiazkaAdresowa.txt");
}

void NowaOsoba ( vector<Adresat> &adresaci, int iloscAdresatow, int numerPorzadkowyUzytkownika) {

    system ("cls");
    vector<Adresat> :: reverse_iterator itr;
    Adresat dane;
    string imieAdresata, nazwiskoAdresata, numerTelefonu, adresEmail, adresZamieszkania;
    int numerPorzadkowy;
    numerPorzadkowy=iloscAdresatow+1;
    cout<<"Imie:"<<endl;
    cin>>imieAdresata;
    cout<<"Nazwisko:"<<endl;
    cin>>nazwiskoAdresata;
    cout<<"Numer telefonu:"<<endl;
    cin>>numerTelefonu;
    cout<<"Adres e-mail:"<<endl;
    cin>>adresEmail;
    cin.sync();
    cout<<"Adres zamieszkania"<<endl;
    getline(cin, adresZamieszkania);

    dane.numerPorzadkowy=numerPorzadkowy;
    dane.numerPorzadkowyUzytkownika=numerPorzadkowyUzytkownika;
    dane.imieAdresata=imieAdresata;
    dane.nazwiskoAdresata=nazwiskoAdresata;
    dane.adresZamieszkania=adresZamieszkania;
    dane.numerTelefonu=numerTelefonu;
    dane.adresEmail=adresEmail;
    adresaci.push_back(dane);
    iloscAdresatow=numerPorzadkowy;
    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::out | ios::app);
    if (plik.good()) {
        plik << numerPorzadkowy <<"|";
        plik << numerPorzadkowyUzytkownika <<"|";
        plik << imieAdresata<<"|" ;
        plik << nazwiskoAdresata<<"|";
        plik << adresZamieszkania<<"|";
        plik << numerTelefonu<<"|" ;
        plik << adresEmail<<"|"<<endl ;
    }
    plik.close();
    cout<<"Zapisano!"<<endl;
    Sleep(2000);
    WyborOpcji(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);
}
void WyszukajPoImieniu (vector<Adresat> &adresaci, int iloscAdresatow, int numerPorzadkowyUzytkownika) {
    system("cls");
    string imieSzukanegoAdresata;
    cout<<"Podaj imie szukanego adresata:"<<endl;
    cin>>imieSzukanegoAdresata;
    int iloscZnalezionychOsob=0;

    for (vector <Adresat> :: iterator itr =adresaci.begin(), koniec=adresaci.end(); itr!=koniec; ++itr) {
        if (imieSzukanegoAdresata==itr->imieAdresata) {
            WyswietlenieDanychAdresata(adresaci, itr);
            iloscZnalezionychOsob++;
        }
    }
    if (iloscZnalezionychOsob==0) {
        cout<<"Nie znaleziono adresata"<<endl;
    }
    system("pause");
    WyborOpcji(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);
}
void WyszukajPoNazwisku (vector<Adresat> &adresaci, int iloscAdresatow,  int numerPorzadkowyUzytkownika) {
    system("cls");
    string nazwiskoSzukanegoAdresata;
    cout<<"Podaj nazwisko szukanego adresata:"<<endl;
    cin>>nazwiskoSzukanegoAdresata;
    int iloscZnalezionychOsob=0;

    for (vector <Adresat> :: iterator itr =adresaci.begin(), koniec=adresaci.end(); itr!=koniec; ++itr) {
        if (nazwiskoSzukanegoAdresata==itr->nazwiskoAdresata) {
            WyswietlenieDanychAdresata(adresaci, itr);
            iloscZnalezionychOsob++;
        }
    }
    if (iloscZnalezionychOsob==0) {
        cout<<"Nie znaleziono adresata"<<endl;
    }
    system("pause");
    WyborOpcji(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);
}
void WyswietlListeAdresatow(vector<Adresat> &adresaci,int iloscAdresatow,  int numerPorzadkowyUzytkownika) {
    system("cls");
    int iloscAdresatowWektorze=0;
    for (vector <Adresat> :: iterator itr =adresaci.begin(), koniec=adresaci.end(); itr!=koniec; ++itr) {

        {
            WyswietlenieDanychAdresata(adresaci, itr);
            iloscAdresatowWektorze++;
        }
    }
    if (iloscAdresatowWektorze==0) {
        cout<<"Brak zapisanych adresatow"<<endl;
    }
    system("pause");
    WyborOpcji(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);
}
void UsuwanieAdresata (vector<Adresat> &adresaci, int iloscAdresatow,  int numerPorzadkowyUzytkownika) {
    system("cls");
    int numerPorzadkowyAdresataDoUsuniecia;
    string linia, tekstDoUsuniecia;
    char wybor;
    int iloscZnalezionychAdresatow=0;
    cout<<"Podaj numer ID adresata, ktorego chcesz usunac"<<endl;
    cin>>numerPorzadkowyAdresataDoUsuniecia;
    for (vector <Adresat> :: iterator itr =adresaci.begin(), koniec=adresaci.end(); itr!=koniec; itr++) {
        if (numerPorzadkowyAdresataDoUsuniecia==itr->numerPorzadkowy) {
            system("cls");
            WyswietlenieDanychAdresata(adresaci, itr);
            iloscZnalezionychAdresatow++;
            cout<<"Czy chcesz usunac adreasata?"<<endl;
            cout<<"1. t-Tak"<<endl;
            cout<<"2. n-Nie"<<endl;
            cin>>wybor;
            switch(wybor) {
            case 't':
                UsuwanieIZapisywanieDoPliku(adresaci, itr);
                cout<<"Dane adresata zostaly usuniete"<<endl;
                iloscAdresatow=0;
                iloscAdresatow=WczytajDaneZPliku(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);
                system("pause");
                break;

            case 'n':
                break;
            }
        }
    }
    if (iloscZnalezionychAdresatow==0) {
        cout<<"Nie znaleziono adresata"<<endl;
        system("pause");
    }
    WyborOpcji(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);
}
void WczytajEdycjeDanychDoPliku (vector<Adresat> &adresaci, vector <Adresat> :: iterator &itr) {
    string linijka;
    fstream pliktymczasowy,plik;
    int  numerPorzadkowy, pozycja;
    string PierwszyNumerLinii;

    plik.open("KsiazkaAdresowa.txt",ios::in);
    if(plik.good()) {
        pliktymczasowy.open("KsiazkaAdresowa_plikTymczasowy.txt",ios::trunc|ios::out);
        if(pliktymczasowy.good()) {
            do {
                getline(plik,linijka);
                if(!plik.eof()) {

                    pozycja=linijka.find("|");
                    PierwszyNumerLinii=linijka.substr(0,pozycja);
                    numerPorzadkowy= atoi(PierwszyNumerLinii.c_str());
                    if (itr->numerPorzadkowy!=numerPorzadkowy) {
                        linijka.append("\n");
                        pliktymczasowy.write(&linijka[0],(unsigned int)linijka.length());
                        pliktymczasowy.flush();
                    } else {
                        pliktymczasowy << itr->numerPorzadkowy <<"|";
                        pliktymczasowy << itr->numerPorzadkowyUzytkownika <<"|";
                        pliktymczasowy << itr->imieAdresata<<"|" ;
                        pliktymczasowy << itr->nazwiskoAdresata<<"|";
                        pliktymczasowy << itr->adresZamieszkania<<"|";
                        pliktymczasowy << itr->numerTelefonu<<"|" ;
                        pliktymczasowy << itr->adresEmail<<"|"<<endl ;
                    }
                }
            } while(!plik.eof());
            pliktymczasowy.close();
        }
        plik.close();
    }
    remove("KsiazkaAdresowa.txt");
    rename("KsiazkaAdresowa_plikTymczasowy.txt", "KsiazkaAdresowa.txt");
}

int ZmianaDanychAdresata(vector<Adresat> &adresaci, vector <Adresat> :: iterator &itr, int iloscAdresatow, int numerPorzadkowyUzytkownika) {

    char wybor;
    string noweDane;
    do {
        system("cls");
        cout<<"Wybierz dane jakie chcesz edytowac"<<endl;
        cout<<"1. imie"<<endl;
        cout<<"2. nazwisko"<<endl;
        cout<<"3. adres"<<endl;
        cout<<"4. numer telefonu"<<endl;
        cout<<"5. adres email"<<endl;
        cout<<"6. wyjdz"<<endl;
        cin>>wybor;
        switch(wybor) {
        case '1':
            system("cls");
            cout<<"Podaj nowe imie"<<endl;
            cin>>noweDane;
            itr->imieAdresata=noweDane;
            WczytajEdycjeDanychDoPliku(adresaci, itr);
            system("pause");
            break;
        case '2':
            system("cls");
            cout<<"Podaj nowe nazwisko"<<endl;
            cin>>noweDane;
            itr->nazwiskoAdresata=noweDane;
            WczytajEdycjeDanychDoPliku(adresaci, itr);
            system("pause");
            break;
        case '3':
            system("cls");
            cin.sync();
            cout<<"Podaj nowy adres zamieszkania"<<endl;
            getline(cin, noweDane);
            itr->adresZamieszkania=noweDane;
            WczytajEdycjeDanychDoPliku(adresaci, itr);
            system("pause");
            break;
        case '4':
            system("cls");
            cout<<"Podaj nowy numer telefonu"<<endl;
            cin>>noweDane;
            itr->numerTelefonu=noweDane;
            WczytajEdycjeDanychDoPliku(adresaci, itr);
            system("pause");
            break;
        case '5':
            system("cls");
            cout<<"Podaj nowy adres email"<<endl;
            cin>>noweDane;
            itr->adresEmail=noweDane;
            WczytajEdycjeDanychDoPliku(adresaci, itr);
            system("pause");
            break;
        case '6':
            WyborOpcji(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);
            break;
        }
    } while (wybor!='6');
}
void EdytujDane(vector<Adresat> &adresaci,int iloscAdresatow, int numerPorzadkowyUzytkownika) {
    system("cls");
    string nazwisko;
    char wybor;
    int iloscZnalezionychAdresatow=0;
    cout<<"Podaj nazwisko adresata dla ktorego chcesz edytowac dane"<<endl;
    cin>>nazwisko;
    for (vector <Adresat> :: iterator itr =adresaci.begin(), koniec=adresaci.end(); itr!=koniec; itr++) {
        if (nazwisko==itr->nazwiskoAdresata) {
            system("cls");
            WyswietlenieDanychAdresata(adresaci, itr);
            iloscZnalezionychAdresatow++;
            cout<<"Czy chcesz edytowac dane tego adresata?"<<endl;
            cout<<"1. Tak"<<endl;
            cout<<"2. Nie"<<endl;
            cout<<"3. Anuluj"<<endl;
            cin>>wybor;

            if (wybor=='1') {
                ZmianaDanychAdresata(adresaci,itr,iloscAdresatow, numerPorzadkowyUzytkownika);

            } else if (wybor=='2') {

            } else if (wybor=='3')
                break;
        }
    }
    if (iloscZnalezionychAdresatow==0) {
        cout<<"Nie znaleziono adresatow o podanym nazwisku"<<endl;
        system("pause");
    }
    WyborOpcji(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);
}

void WyborOpcji(vector<Adresat>&adresaci, int iloscAdresatow, int numerPorzadkowyUzytkownika) {
    system("cls");
    char wybor;
    while (true) {
        system("cls");
        cout << "MENU GLOWNE" << endl;
        cout<<endl;
        cout<<"1. Dodaj adresata"<<endl;
        cout<<"2. Wyszukaj po imieniu"<<endl;
        cout<<"3. Wyszukaj po nazwisku"<<endl;
        cout<<"4. Wyswietl wszytskich adresatow"<<endl;
        cout<<"5. Usun adresata"<<endl;
        cout<<"6. Edytuj adresata"<<endl;
        cout<<"9. Wyloguj"<<endl;
        cout<<endl;
        cout<<"Wybierz opcje:"<<endl;
        cin>>wybor;
        switch(wybor) {
        case '1':
            NowaOsoba(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);
            break;
        case '2':
            WyszukajPoImieniu(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);

            break;
        case '3':
            WyszukajPoNazwisku(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);
            break;

        case '4':
            WyswietlListeAdresatow(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);
            break;

        case '5':
            UsuwanieAdresata(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);
            break;
        case '6':
            EdytujDane(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);
            break;
        case '9':
            main();
            break;
        }
    }

}
void WczytajUzytkownikow (vector<Uzytkownik> &uzytkownicy) {
    string loginUzytkownika, hasloUzytkownika, numerPorzadkowyUzytkownika;
    Uzytkownik nowy;
    int pozycja;
    string linia;
    fstream plik;
    plik.open("listaUzytkownikow.txt",ios::in);
    if (plik.good()) {
        while(getline(plik,linia)) {

            pozycja=linia.find("|");
            numerPorzadkowyUzytkownika=linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);
            pozycja=linia.find("|");
            loginUzytkownika=linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);
            pozycja=linia.find("|");
            hasloUzytkownika=linia.substr(0,pozycja);

            nowy.numerPorzadkowyUzytkownika=atoi(numerPorzadkowyUzytkownika.c_str());
            nowy.loginUzytkownika=loginUzytkownika;
            nowy.hasloUzytkownika=hasloUzytkownika;
            uzytkownicy.push_back(nowy);
        }
        plik.close();
    }
}

void RejestracjaNowegoUzytkownika(vector<Uzytkownik>& uzytkownicy, vector<Adresat> &adresaci, int iloscAdresatow) {
    system("cls");
    string loginUzytkownika, hasloUzytkownika;
    int numerPorzadkowyUzytkownika;
    vector<Uzytkownik> :: reverse_iterator it;
    Uzytkownik nowy;
    if (uzytkownicy.empty()) {
        numerPorzadkowyUzytkownika=1;
    } else {
        it=uzytkownicy.rbegin();
        numerPorzadkowyUzytkownika=it->numerPorzadkowyUzytkownika+1;
    }
    cout<<"Podaj login "<<endl;
    cin>>loginUzytkownika;
    cout<<"Podaj haslo"<<endl;
    cin>>hasloUzytkownika;
    nowy.numerPorzadkowyUzytkownika=numerPorzadkowyUzytkownika;
    nowy.loginUzytkownika=loginUzytkownika;
    nowy.hasloUzytkownika=hasloUzytkownika;
    uzytkownicy.push_back(nowy);

    fstream plik;
    plik.open("listaUzytkownikow.txt", ios::out | ios::app);
    if (plik.good()) {
        plik << numerPorzadkowyUzytkownika <<"|";
        plik << loginUzytkownika<<"|" ;
        plik << hasloUzytkownika<<"|"<<endl;

    }
    plik.close();
    cout<<"Zapisano!"<<endl;
    Sleep(2000);
    iloscAdresatow=0;
    iloscAdresatow=WczytajDaneZPliku(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);
    WyborOpcji(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);

}

void LogowanieUzytkownika(vector<Uzytkownik>& uzytkownicy, vector<Adresat> &adresaci, int iloscAdresatow) {
    string loginUzytkownika, hasloUzytkownika;
    int numerPorzadkowyUzytkownika, iloscZnalezionychUzytkownikow=0;
    for(int i=3; i>0; i--) {
        system("cls");
        cout<<"Podaj login "<<endl;
        cin>>loginUzytkownika;
        cout<<"Podaj haslo"<<endl;
        cin>>hasloUzytkownika;
        for (vector <Uzytkownik> :: iterator itr =uzytkownicy.begin(), koniec=uzytkownicy.end(); itr!=koniec; ++itr) {
            if (loginUzytkownika==itr->loginUzytkownika && hasloUzytkownika==itr->hasloUzytkownika) {
                cout<<"Zalogowano!"<<endl;
                Sleep(1500);
                numerPorzadkowyUzytkownika=itr->numerPorzadkowyUzytkownika;
                iloscZnalezionychUzytkownikow++;
                i=0;
                iloscAdresatow=0;
                iloscAdresatow=WczytajDaneZPliku(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);
                WyborOpcji(adresaci, iloscAdresatow, numerPorzadkowyUzytkownika);
            }
        }
        if (iloscZnalezionychUzytkownikow==0) {
            cout<<"Bledny login lub haslo zostalo Ci "<<i-1<<" prob"<<endl;
            Sleep(1500);
        }
    }

}

int main() {
    vector<Adresat> adresaci;
    vector<Uzytkownik> uzytkownicy;
    char wybor;
    WczytajUzytkownikow(uzytkownicy);
    int iloscAdresatow=0;
    while (true) {
        system("cls");
        cout<<"1. Rejestracja"<<endl;
        cout<<"2. Logowanie"<<endl;
        cout<<"3. Zamknij program"<<endl;

        cout<<"Wybierz opcje"<<endl;
        cin>>wybor;

        switch (wybor) {
        case '1':
            RejestracjaNowegoUzytkownika(uzytkownicy, adresaci, iloscAdresatow);
            break;
        case '2':
            LogowanieUzytkownika(uzytkownicy, adresaci, iloscAdresatow);
            break;
        case '3':
            exit(0);
            break;
        }
    }
    return 0;
}


