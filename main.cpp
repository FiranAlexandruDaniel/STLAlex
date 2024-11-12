#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Problema {
    string idProblema;
    string specializare;
    int timp;
    // Am nevoie de operator-ul == pentru functia erase,
    // altfel nu ar putea gasi pacientul
    //bool operator==(const Problema& other) const {
    //    return idProblema == other.idProblema && specializare == other.specializare && timp == other.timp;
    // }
};
struct Doctor
{
    string idDoctor;
    string specializare;
    bool disponibilitate = true;
    int ora_disponibil = 9;
    vector <Problema> probleme_doctor;
};
int main()
{
    
    ifstream inFile("input4_bonus.txt");

    int no_problems, no_doctors;
    string name, speciality;
    int timp;
    vector <Problema> probleme;
    vector <Doctor> doctori;
    inFile >> no_problems;

    for (int i = 0; i <= no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;
        inFile >> timp;
        cout << name << ' ' << speciality << " " << timp << '\n';
        probleme.emplace_back(name, speciality,timp);
    }
    cout << endl;
    inFile >> no_doctors;
    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> name;
        inFile >> speciality;
        cout << name << ' ' << speciality << '\n';
        doctori.emplace_back(name, speciality);
    }
    cout << endl;
    // rezolvare problema bonus

    while (no_problems > 0)
    {
        for (auto& doctor : doctori)
        {
            auto pacient = find_if(begin(probleme), end(probleme), [&](Problema pacienti) {
                if (doctor.specializare == pacienti.specializare && doctor.ora_disponibil + pacienti.timp < 17 )
                {
                    return true;
                }
                else
                {
                    return false;
                } });
                if (pacient != end(probleme))
                {

                    // rezolvarea simpla dar nu foarte interesanta
                    // doctor.probleme_doctor.emplace_back(*pacient);
                    /* A doua iteratie, am o eroare aici din cauza doctor.probleme_doctor.begin()
                    copy_if(probleme.begin(), probleme.end(), doctor.probleme_doctor.begin(), [&pacient](Problema& const copy_pacient)-> bool {
                        if (copy_pacient.idProblema == pacient->idProblema && copy_pacient.specializare == pacient->specializare)
                            return true;
                        return false;
                        });*/
                    // varianta finala si interesanta
                    copy_if(probleme.begin(), probleme.end(), back_inserter(doctor.probleme_doctor), [&pacient](Problema& const copy_pacient)-> bool {
                        if (copy_pacient.idProblema == pacient->idProblema && copy_pacient.specializare == pacient->specializare)
                            return true;
                        return false;
                        });
                    doctor.ora_disponibil += pacient->timp;
                   //probleme.erase(remove(begin(probleme), end(probleme), *pacient), end(probleme)); overloaded ==
                    probleme.erase(remove_if(begin(probleme), end(probleme), [&pacient](Problema const &pacientul) {
                        if (pacientul.idProblema == pacient->idProblema && pacientul.specializare == pacient->specializare)
                            return true;
                        else
                            return false;
                        }), end(probleme));

                }
                    
        }
        no_problems--;
    }
    // output doctori
    for (auto doctor : doctori)
    {
        cout << doctor.idDoctor << " " << doctor.probleme_doctor.size() << " ";
        for (auto probleme_rezolvate : doctor.probleme_doctor)
        {
            cout << probleme_rezolvate.idProblema << " ";
        }
        cout << endl;
    }
    return 0;
}

// problema veche 
/*
for (auto problema : probleme)
{
    bool accepted = false;
    for (auto doctor : doctori)
    {
        if (problema.specializare == doctor.specializare && doctor.disponibilitate == true)
        {
            doctor.disponibilitate = false;
            accepted = true;
            break;
        }
    }
    if (accepted)
    {
        cout << problema.idProblema << "-Acceptat" << endl;

    }
    else
    {
        cout << problema.idProblema << "-Respins" << endl;

    }
}*/
// clasa 2
/*vector <int> arr = vector<int>{ 1,2,3,4,5,6,7,4,8,9,98 };
    auto it = find(begin(arr), end(arr), 7);

    it = find_if(begin(arr), end(arr), [](int n) {return n > 10; });

    if (it == arr.end())
    {
        cout << "Nu am gasit elementul";
    }
    else
    {
        cout << "Am gasit elementul";
    }

    sort(begin(arr),end(arr));
    it = lower_bound(begin(arr), end(arr), 4);
    it = upper_bound(begin(arr), end(arr), 3);

    if (it == arr.end())
    {
        cout << "Nu am gasit elementul";
    }
    else
    {
        cout << "Am gasit elementul";
    } 
    vector < int> arr2 = vector<int>{ 1,2,3,4,4,6,7,8,9,10,11,12,13,3,3,3,3 };
    //transform(begin(arr), end(arr), begin(arr2), [](int n) {return n * 2; });
    sort(begin(arr2), end(arr2));
    auto it = unique(begin(arr), end(arr));
    arr2.erase(it, end(arr2));
    for (const int& n : arr)
    {
        cout << n << " ";
    }

    cout << endl;
    for (const int& n: arr2)
    {
        cout << n << " ";
    }
    cout << endl;
         return 0;*/