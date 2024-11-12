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

};
struct Doctor
{
    string idDoctor;
    string specializare;
    bool disponibilitate = true;
    int ora_disponibil = 9;
    int probleme_rezolvate = 0;
    vector <Problema> doctor_probleme;
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

    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;
        inFile >> timp;
        cout << name << ' ' << speciality << '\n';
        probleme.emplace_back(name, speciality,timp);
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> name;
        inFile >> speciality;
        cout << name << ' ' << speciality << '\n';
        doctori.emplace_back(name, speciality);
    }
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

  /*  for (auto& doctor : doctori)
    {
        auto it = find_if(begin(probleme), end(probleme), [&](Problema n) {
            if (doctor.specializare == n.specializare)
            {return true;}
            else
            { return false;} });
        if (it != end(probleme))
            cout <<doctor.idDoctor << " " << it->idProblema << "-Acceptat" << endl;
        else
            cout << doctor.idDoctor << " " << it->idProblema << "-Respins" << endl;
    }*/
    int counter = 9;
    while (counter <= 17)
    {
        for (auto& doctor : doctori)
        {
            auto it = find_if(begin(probleme), end(probleme), [&](Problema n) {
                if (doctor.specializare == n.specializare && doctor.ora_disponibil <= counter)
                {
                    return true;
                }
                else
                {
                    return false;
                } });
                if (it != end(probleme))
                {
                    doctor.doctor_probleme.emplace_back(*it);
                    doctor.ora_disponibil += it->timp;
                }
                    
        }
        counter++;
    }
    for (auto doctor : doctori)
    {
        cout << doctor.idDoctor << " " << doctor.probleme_rezolvate << " ";
        for (auto probleme_rezolvate : doctor.doctor_probleme)
        {
            cout << probleme_rezolvate.idProblema << " ";
        }
    }
    return 0;
}

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