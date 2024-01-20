/*
    MEHMET KAHYA - 230603035
    10.01.2024
    11.01.2024

    C++ Telefon Rehberi Uygulaması
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <windows.h>
using namespace std;


// Kullanıcı bilgileri için struct
struct kayit
{
    string isim;
    string soyad;
    string telno;
};

void toLowercase(string &str)
{
    for (char &c : str)
    {
        c = static_cast<char>(tolower(c));
    }
}

void telEkle()
{
    kayit k;

    cout << "isim: ";
    cin >> k.isim;
    toLowercase(k.isim);

    cout << "soyad: ";
    cin >> k.soyad;
    toLowercase(k.soyad);

    cout << "telefon numarasi: ";
    cin >> k.telno;

    ofstream dosya("rehber.txt", ios::app);
    if (dosya.is_open())
    {
        dosya << k.isim << " " << k.soyad << " " << k.telno << endl;
        dosya.close();
        cout << "Kisi eklendi." << endl;
    }
    else
    {
        cout << "Dosya acilamadi." << endl;
    }
}

void telListele()
{
    cout << endl
         << "REHBER" << endl;
    cout << "--------------------------------" << endl;

    ifstream dosya("rehber.txt");
    if (dosya.is_open())
    {
        string line;
        while (getline(dosya, line))
        {
            cout << line << '\n';
        }
        dosya.close();
    }
    else
    {
        cout << "Dosya acilamadi." << endl;
    }
}

void kisiGuncelle()
{
    string isim;
    cout << "Guncellemek istediginiz kisinin adini girin: ";
    cin >> isim;

    string soyad;
    cout << "Guncellemek istediginiz kisinin soyadini girin: ";
    cin >> soyad;

    string line;
    string tempLine;
    ifstream dosya("rehber.txt");
    ofstream temp("temp.txt");

    while (getline(dosya, line))
    {
        string currentName = line.substr(0, line.find(" "));

        if (currentName == isim)
        {
            string newIsim, newSoyad, newTelno;
            cout << "Yeni isim girin: ";
            cin >> newIsim;
            cout << "Yeni soyad girin: ";
            cin >> newSoyad;
            cout << "Yeni telefon numarasi girin: ";
            cin >> newTelno;
            tempLine = newIsim + " " + newSoyad + " " + newTelno;
            temp << tempLine << endl;
            cout << "Kisi Guncellendi." << endl;
        }
        else
        {
            temp << line << endl;
        }
    }

    dosya.close();
    temp.close();
    remove("rehber.txt");
    rename("temp.txt", "rehber.txt");
}

void telSil()
{
    string isim;
    cout << "Silmek istediginiz kisinin adini girin: ";
    cin >> isim;

    string line;
    ifstream dosya("rehber.txt");
    ofstream temp("temp.txt");

    while (getline(dosya, line))
    {
        string currentName = line.substr(0, line.find(" "));
        if (currentName != isim)
        {
            temp << line << endl;
        }
    }

    dosya.close();
    temp.close();
    remove("rehber.txt");
    rename("temp.txt", "rehber.txt");

    cout << "Kisi Silindi." << endl;
}

void telAra()
{
    string isim;
    cout << "Aranacak kisinin adini girin: ";
    cin >> isim;

    string line;
    ifstream dosya("rehber.txt");

    bool found = false;
    while (getline(dosya, line))
    {
        string currentName = line.substr(0, line.find(" "));
        if (currentName == isim)
        {
            cout << "Kisi bulundu: " << line << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Kisi bulunamadi." << endl;
    }

    dosya.close();
}

void menu()
{
    int choice;
    cout << "MENU" << endl;
    cout << "--------------------------------" << endl;
    cout << "1. Kisi Ekle" << endl;
    cout << "2. Rehber Goruntule" << endl;
    cout << "3. Kisi Guncelle" << endl;
    cout << "4. Kisi Sil" << endl;
    cout << "5. Kisi Ara" << endl;
    cout << "6. Cikis" << endl;
    cout << "--------------------------------" << endl;
    cout << "Tercihiniz: ";

    cin >> choice;

    if (choice == 1)
    {
        telEkle();
    }
    else if (choice == 2)
    {
        telListele();
    }
    else if (choice == 3)
    {
        kisiGuncelle();
    }
    else if (choice == 4)
    {
        telSil();
    }
    else if (choice == 5)
    {
        telAra();
    }
    else if (choice == 6)
    {
        cout << "Cikis yapiliyor..." << endl;
        return; // Instead of exit(0);
    }
    else
    {
        cout << "Hatali giris yaptiniz. Tekrar deneyin." << endl;
        menu();
    }
}
int main()
{
    menu();
    system("pause");

    return 0;
}