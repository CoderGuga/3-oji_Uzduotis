#include "helper.h"
#include "helperFunctions.h"
#include "cFunctions.h"

int main()
{
    
    try {
        string menu = "1 - ranka irasyti viska, 2 - generuoti pazymius, 3 - generuoti ir pazymius ir studentu vardus, pavardes, 4 - irasyti duomenis is failo, 5 - generuoti studentu failus, 6 - ruosiuoti sugeneruotus studentu failus, 7 - visu konteineriu testavimas, 8 - greitas testas, 9 - metodu testavimas, 10 - baigti darba: ";

        int paskutinis = 11;

        int stCon = CheckInt(menu, paskutinis);
        Vector<Stud> students;

        while (stCon < 5)
        {
            if (stCon == 4) {
                string filename;
                cout << "Iveskite failo pavadinima: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(cin, filename);

                auto start = high_resolution_clock::now();
                try {
                    ReadFromFile(students, filename);
                } catch (const std::exception& e) {
                    cerr << "Nepavyko nuskaityti is failo: " << e.what() << endl;
                    continue;
                }
                auto end = high_resolution_clock::now();
                auto duration = duration_cast<milliseconds>(end - start);
                cout << "Skaitymas is failo uztruko " << duration.count() << " milisekundes." << endl;
            }
            
            if (stCon == 1 || stCon == 2 || stCon == 3)
            {
                try {
                    Stud student = CreateStudent(stCon);
                    students.push_back(student);
                } catch (const std::exception& e) {
                    cerr << "Nepavyko sukurti studento: " << e.what() << endl;
                    continue;
                }
            }

            
            stCon = CheckInt(menu, paskutinis);

            
        }
        if (stCon == paskutinis)
        {
            string sortType;
            cout << "Rikiavimo tipas? (Vardas - vardas / Pavarde - pavarde / Galutinis pagal vidurki - vidurkis / Galutinis pagal mediana - mediana): ";
            cin >> sortType;
            while (sortType != "vardas" && sortType != "pavarde" && sortType != "vidurkis" && sortType != "mediana")
            {
                cout << "Iveskite 'vardas', 'pavarde', 'vidurkis' arba 'mediana': ";
                cin >> sortType;
            }

            // Calculate final grades
            for (auto& student : students) {
                double average = 0;
                double median = 0;
                if (!student.getNdVector().empty()) {
                    average = Average(student.getNdVector());
                    median = Median(student.getNdVector());
                }

                student.setGalutinisVid(student.getEgz() * 0.6 + average * 0.4);
                student.setGalutinisMed(student.getEgz() * 0.6 + median * 0.4);
            }

            // Sort students based on the user's choice
            students = SortOutput(sortType, students);

            string outputType;
            cout << "Isvesti i terminala 't', ar faila 'f': ";
            cin >> outputType;
            while (outputType != "t" && outputType != "f")
            {
                cout << "Iveskite 't' arba 'f': ";
                cin >> outputType;
            }
            auto start = high_resolution_clock::now();
            if (outputType == "t")
            {
                PrintToTerminal(students);
            }
            else {
                try {
                    WriteToFile(students, "output.txt");
                } catch (const std::exception& e) {
                    cerr << "Nepavyko irasyti i faila: " << e.what() << endl;
                }
            }

            students.clear();

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);
            cout << "Israsymas truko " << duration.count() << " milisekundes." << endl;
        }

    if(stCon == 5)
    {
        cout << "Generuojami failai"<<endl;
        GenFiles();
    }

    if (stCon == 6)
        FullDataProccess("1 000 studentu.txt", "10 000 studentu.txt", "100 000 studentu.txt", "1 000 000 studentu.txt", "10 000 000 studentu.txt");

    if (stCon == 7)
        FullContainerTest("1 000 studentu.txt", "10 000 studentu.txt", "100 000 studentu.txt", "1 000 000 studentu.txt", "10 000 000 studentu.txt");

    if (stCon == 8)
        QuickTest("100 000 studentu.txt", "1 000 000 studentu.txt");

    if (stCon == 9)
        MethodTest();

    if (stCon == 10)
        ARetartedTest();

    } catch (const std::exception& e) {
        cerr << "Ivyko klaida: " << e.what() << endl;
    }

    cout<<"Programos pabaiga"<<endl;

    Pause();

    return 0;
}