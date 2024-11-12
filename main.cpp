#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
using namespace std;

struct Problema {
    string idProblema;
    string specializare;


};
struct Doctor
{
    string idDoctor;
    string specializare;
};
int main()
{
    ifstream inFile("input.txt");

    int no_problems, no_doctors;
    string name, speciality;
    vector <Problema> probleme;
    vector <Doctor> doctori;
    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;
        cout << name << ' ' << speciality << '\n';
        probleme.emplace_back(name, speciality);
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> name;
        inFile >> speciality;
        cout << name << ' ' << speciality << '\n';
        doctori.emplace_back(name, speciality);
    }

    for (auto problema : probleme)
    {
        bool accepted = false;
        for (auto doctor : doctori)
        {
            if (problema.specializare == doctor.specializare)
            {
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
    }
    return 0;
}\