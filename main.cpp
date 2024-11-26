#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
//#include <concurrent_priority_queue.h>

using namespace std;


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//struct Point
//{
//    int x, y;
//};
//struct PointCompare
//{
//    bool operator() (const Point& a, const Point& b)
//    {
//        return a.x < b.x;
//    }
//};
//
//
//
//int main()
//{
//
//    auto pointCompare = [](const Point& a, const Point& b)
//        {
//            return a.x < b.x;
//        };
//    priority_queue<Point, vector<Point>,decltype(pointCompare)> pq(pointCompare);
//   // priority_queue<Point, vector<Point>, PointCompare> pq;
//    Point a = { 5,2 };
//    Point b = { 3,3 };
//    pq.push(a);
//    pq.push(b);
//    
//    pq.pop();
//}


struct Problema {
    string idProblema;
    string specializare;
    int timp;
    int prioritate;
    // Am nevoie de operator-ul == pentru functia erase,
    // altfel nu ar putea gasi pacientul
    //bool operator==(const Problema& other) const {
    //    return idProblema == other.idProblema && specializare == other.specializare && timp == other.timp;
    // }
    bool operator < (const Problema& other) const
    {
        return this->prioritate < other.prioritate;
    }
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

    ifstream inFile("input.txt");

    int no_problems, no_doctors;
    string name, speciality;
    int timp;
    //vector <Problema> probleme;
    vector <Doctor> doctori;
    inFile >> no_problems;
    priority_queue<Problema> coada;
    for (int i = 0; i < no_problems; i++)
    {
        int prioritate;
        inFile >> name;
        inFile >> speciality;
        inFile >> timp;
        inFile >> prioritate;
        cout << name << ' ' << speciality << " " << timp << '\n';
        // probleme.emplace_back(name, speciality, timp);
        Problema temp = { name,speciality,timp,prioritate };
        coada.push(temp);
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
    //rezolvare hands on


    while (no_problems > 0)
    {
        //auto pacient = coada.top();
        for (auto& doctor : doctori)
        {
            /*auto pacient = find_if(begin(probleme), end(probleme), [&](Problema pacienti) {
                if (doctor.specializare == pacienti.specializare && doctor.ora_disponibil + pacienti.timp < 17)
                {
                    return true;
                }
                else
                {
                    return false;
                } });*/
            
            
            // rezolvarea simpla dar nu foarte interesanta
            // doctor.probleme_doctor.emplace_back(*pacient);
            /* A doua iteratie, am o eroare aici din cauza doctor.probleme_doctor.begin()
            copy_if(probleme.begin(), probleme.end(), doctor.probleme_doctor.begin(), [&pacient](Problema& const copy_pacient)-> bool {
                if (copy_pacient.idProblema == pacient->idProblema && copy_pacient.specializare == pacient->specializare)
                    return true;
                return false;
                });*/
                // varianta finala si interesanta
           /* copy_if(probleme.begin(), probleme.end(), back_inserter(doctor.probleme_doctor), [&pacient](Problema& const copy_pacient)-> bool {
                if (copy_pacient.idProblema == pacient->idProblema && copy_pacient.specializare == pacient->specializare)
                    return true;
                return false;
                });*/
            if (coada.size() > 1)
            {
                auto pacient = coada.top();

                if (pacient.specializare == doctor.specializare && doctor.ora_disponibil + pacient.timp < 19)
                {
                    doctor.ora_disponibil += pacient.timp;
                    coada.pop();
                    doctor.probleme_doctor.push_back(pacient);
                }
            }

            //probleme.erase(remove(begin(probleme), end(probleme), *pacient), end(probleme)); overloaded ==
            /*probleme.erase(remove_if(begin(probleme), end(probleme), [&pacient](Problema const& pacientul) {
                if (pacientul.idProblema == pacient->idProblema && pacientul.specializare == pacient->specializare)
                    return true;
                else
                    return false;
                }), end(probleme));*/



        }
        no_problems--;
    }

    // rezolvare problema bonus



   /* while (no_problems > 0)
    {
        for (auto& doctor : doctori)
        {
            auto pacient = find_if(begin(probleme), end(probleme), [&](Problema pacienti) {
                if (doctor.specializare == pacienti.specializare && doctor.ora_disponibil + pacienti.timp < 17)
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
                        });
                        // varianta finala si interesanta
                    copy_if(probleme.begin(), probleme.end(), back_inserter(doctor.probleme_doctor), [&pacient](Problema& const copy_pacient)-> bool {
                        if (copy_pacient.idProblema == pacient->idProblema && copy_pacient.specializare == pacient->specializare)
                            return true;
                        return false;
                        });
                    doctor.ora_disponibil += pacient->timp;
                    //probleme.erase(remove(begin(probleme), end(probleme), *pacient), end(probleme)); overloaded ==
                    probleme.erase(remove_if(begin(probleme), end(probleme), [&pacient](Problema const& pacientul) {
                        if (pacientul.idProblema == pacient->idProblema && pacientul.specializare == pacient->specializare)
                            return true;
                        else
                            return false;
                        }), end(probleme));

                }

        }
        no_problems--;
    }*/



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
         /*
         struct song
         {
             int views;
             string name;
             bool operator < (const song& other) const
             {
                 return views < other.views;
             }
         };

         int main() {

             priority_queue<song> pq;
             pq.emplace(5000,"Carla's dreams");
             pq.emplace(1000, "Taylor");
             pq.emplace(2000, "Smiley");
             pq.emplace(3500, "The Weekend");

             while (!pq.empty())
             {
                 cout << pq.top().name << " , ";
                 pq.pop();
             }
         }*/

         //int main() { cada
         //    int k=3;
         //    vector<int> vec = { 1 ,2,1,0,9,1 };
         //    queue<int> coada;
         //    int suma = 0;
         //    for (auto iterator : vec)
         //    {
         //        suma += iterator;
         //        coada.push(iterator);
         //        if (coada.size() == k)
         //        {
         //            cout << suma << endl;
         //            int first = coada.front();
         //            suma -= first;
         //            coada.pop();
         //
         //        }
         //    }
         //    return 0;
         //}
         //    Stiva
         //bool isOperator(char c) {
         //    if( )
         //}
         //
         //int main() { 
         //
         //   
         //
         //    string expr;
         //    getline(cin, expr);
         //    stack<int> stiva;
         //    for (char c : stiva)
         //    {
         //
         //        if (c == ' ')
         //        {
         //            continue;
         //        }
         //        if (isOperator(c))
         //        {
         //            int operand2 = stiva.top();
         //            stiva.pop();
         //            int operand1 = stiva.top();
         //            stiva.pop();
         //            switch (c)
         //            {
         //            case '+':
         //                stiva.push(operand1 + operand2);
         //                    break;
         //            case '-':
         //                stiva.push(operand1 - operand2);
         //                break;
         //            }
         //
         //        }
         //    }
         //    cout << stiva.top();
         //    return 0;
         //}



         /*
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
                                 });
                                 // varianta finala si interesanta
         copy_if(probleme.begin(), probleme.end(), back_inserter(doctor.probleme_doctor), [&pacient](Problema& const copy_pacient)-> bool {
             if (copy_pacient.idProblema == pacient->idProblema && copy_pacient.specializare == pacient->specializare)
                 return true;
             return false;
             });
         doctor.ora_disponibil += pacient->timp;
         //probleme.erase(remove(begin(probleme), end(probleme), *pacient), end(probleme)); overloaded ==
         probleme.erase(remove_if(begin(probleme), end(probleme), [&pacient](Problema const& pacientul) {
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