#include "helper.h"
#include "helperFunctions.h"
#include "cFunctions.h"

template <typename Container>
void ReadFromFile(Container& students, const string& filename)
{
    auto start = high_resolution_clock::now();
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Nepavyko atidaryti failo (ar teisingai ivedete pavadinima?): " << filename << endl;
        return;
    }

    string line;
    // Skip the first line
    if (std::getline(file, line)) {
        // First line is skipped
    }

    const size_t bufferSize = 8192; // 8 KB buffer size
    Vector<char> buffer(bufferSize);
    stringstream ss;

    while (file.read(buffer.data(), bufferSize) || file.gcount() > 0) {
        ss.write(buffer.data(), file.gcount());
    }

    while (std::getline(ss, line)) {
        std::istringstream stream(line);
        Stud student;
        string vardas, pavarde;
        stream >> vardas >> pavarde;
        student.setVardas(vardas);
        student.setPavarde(pavarde);

        int grade;
        student.clearNdVector();
        while (stream >> grade) {
            student.addNd(grade);
        }

        // The last element in ndVector is actually the egz score
        if (!student.getNdVector().empty()) {
            student.setEgz(student.getNdVector().back());
            student.getNdVector().pop_back();
            student.setGalutinisVid(student.getEgz() * 0.6 + Average(student.getNdVector()) * 0.4);
            student.setGalutinisMed(student.getEgz() * 0.6 + Median(student.getNdVector()) * 0.4);
            students.push_back(student);
        }
    }

    file.close();

    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Failo nuskaitymas uztruko " << duration.count() << " sekundes." << endl;
}

template <typename Container>
void WriteToFile(const Container& students, const string& filename)
{
    ofstream file(filename);
    std::ostringstream output;

    auto start = high_resolution_clock::now();

    // Write the header line
    output << std::left << std::setw(15) << "Vardas"
         << std::setw(15) << "Pavarde"
         << std::setw(15) << "Galutinis (Vid.)"
         << std::setw(15) << "Galutinis (Med.)"
         << endl;
    output << "-------------------------------------------------------------" << endl;

    // Write each student's data
    for (const auto& student : students) {
        output << std::left << std::setw(15) << student.getVardas()
             << std::setw(15) << student.getPavarde()
             << std::setw(15) << std::fixed << std::setprecision(2) << student.getGalutinisVid()
             << std::setw(15) << std::fixed << std::setprecision(2) << student.getGalutinisMed()
             << endl;
    }

    file << output.str();
    file.close();

    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Irasymas i faila "<<filename<<" uztruko " << duration.count() << " sekundes." << endl;
}

template <typename Container>
auto SortOutput(const std::string& sortType, Container students) -> Container
{
    if constexpr (std::is_same_v<typename std::iterator_traits<typename Container::iterator>::iterator_category, std::random_access_iterator_tag>) {
        if (sortType == "vardas") {
            std::sort(students.begin(), students.end(), [](const Stud& a, const Stud& b) {
                return a.getVardas() < b.getVardas();
            });
        } else if (sortType == "pavarde") {
            std::sort(students.begin(), students.end(), [](const Stud& a, const Stud& b) {
                return a.getPavarde() < b.getPavarde();
            });
        } else if (sortType == "vidurkis") {
            std::sort(students.begin(), students.end(), [](const Stud& a, const Stud& b) {
                return a.getGalutinisVid() < b.getGalutinisVid();
            });
        } else if (sortType == "mediana") {
            std::sort(students.begin(), students.end(), [](const Stud& a, const Stud& b) {
                return a.getGalutinisMed() < b.getGalutinisMed();
            });
        }
    } else {
        if (sortType == "vardas") {
            students.sort([](const Stud& a, const Stud& b) {
                return a.getVardas() < b.getVardas();
            });
        } else if (sortType == "pavarde") {
            students.sort([](const Stud& a, const Stud& b) {
                return a.getPavarde() < b.getPavarde();
            });
        } else if (sortType == "vidurkis") {
            students.sort([](const Stud& a, const Stud& b) {
                return a.getGalutinisVid() < b.getGalutinisVid();
            });
        } else if (sortType == "mediana") {
            students.sort([](const Stud& a, const Stud& b) {
                return a.getGalutinisMed() < b.getGalutinisMed();
            });
        }
    }

    return students;
}

template <typename Container>
void PrintToTerminal(Container students)
{
    string galutinisTipasVid = "Galutinis (Vid.)";
    string galutinisTipasMed = "Galutinis (Med.)";
            
    cout << std::left << std::setw(15) << "Vardas" 
        << std::setw(15) << "Pavarde" 
        << std::setw(15) << galutinisTipasVid 
        << std::setw(15) << galutinisTipasMed << endl;
    cout << "-------------------------------------------------------------" << endl;

    // Print the student data
    for (const auto& student : students) {
        cout << std::left << std::setw(15) << student.getVardas() 
            << std::setw(15) << student.getPavarde() 
            << std::setw(15) << std::fixed << std::setprecision(2) << student.getGalutinisVid() 
            << std::setw(15) << std::fixed << std::setprecision(2) << student.getGalutinisMed() << endl;
    }
}

Stud CreateStudent(int stCon)
{
    Stud student;
    (stCon == 3) ? student.setVardas(GenName()) : student.setVardas(TypeString("Studento vardas: "));
    (stCon == 3) ? student.setPavarde(GenSurname()) : student.setPavarde(TypeString("Studento pavarde: "));
    (stCon == 1) ? student.setEgz(CheckInt("Egzamino pazymys: ", 10)) : student.setEgz(RandInt(1, 10));
    cout << "egzaminas: " << student.getEgz() << endl;
    string con = TypeString("Prideti namu darbp pazymi? y/n  ");
    student.clearNdVector();
    while (con == "y")
    {
        int nd = RandInt(1, 10);
        nd = (stCon == 1) ? CheckInt("Namu darbu pazymys: ", 10) : RandInt(1, 10);
        if (stCon != 1) cout<<"Pazymis: "<< nd<<endl;
        student.addNd(nd);
        con = TypeString("Prideti namu darbp pazymi? y/n  ");
    }
    return student;
}

template <typename Container>
void SortStudent(Container& students, Container& islaike, Container& neislaike)
{
    auto start = high_resolution_clock::now();
    for (const auto& student : students)
    {
        if (student.getGalutinisVid() < 5.0)
            neislaike.push_back(student);
        else
            islaike.push_back(student);
    }
    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Rusiavimas uztruko " << duration.count() << " sekundes." << endl;
}

template <typename Container>
void SortStudentOneContainerList(Container& students, Container& neislaike)
{
    auto start = high_resolution_clock::now();
    auto it = students.begin();
    while (it != students.end()) {
        if (it->getGalutinisVid() < 5.0) {
            neislaike.push_back(*it);
            it = students.erase(it); // Erase returns the next iterator
        } else {
            ++it;
        }
    }
    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Rusiavimas uztruko " << duration.count() << " sekundes." << endl;
}

template <typename Container>
void SortStudentOneContainer(Container& students, Container& neislaike)
{
    auto start = std::chrono::high_resolution_clock::now();

    // Use remove_if and erase for std::vector and std::deque
    auto it = std::remove_if(students.begin(), students.end(), [&](const auto& student) {
        if (student.getGalutinisVid() < 5.0) {
            neislaike.push_back(student);
            return true; // Mark for removal
        }
        return false;
    });
    students.erase(it, students.end());

    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
    std::cout << "Rusiavimas uztruko " << duration.count() << " sekundes." << std::endl;
}

template <typename Container>
void SortStudentOneContainerListADV(Container& students, Container& neislaike)
{
    auto start = high_resolution_clock::now();
    auto it = std::stable_partition(students.begin(), students.end(), [](const auto& student) {
        return student.getGalutinisVid() >= 5.0;
    });

    // Move the students who failed to the neislaike container
    neislaike.insert(neislaike.end(), it, students.end());

    // Erase the students who failed from the students container
    students.erase(it, students.end());

    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Rusiavimas uztruko " << duration.count() << " sekundes." << endl;
}

template <typename Container>
void SortStudentOneContainerADV(Container& students, Container& neislaike)
{
    auto start = std::chrono::high_resolution_clock::now();

    auto it = std::partition(students.begin(), students.end(), [](const auto& student) {
        return student.getGalutinisVid() >= 5.0;
    });

    // Move the students who failed to the neislaike container
    neislaike.insert(neislaike.end(), it, students.end());

    // Erase the students who failed from the students container
    students.erase(it, students.end());

    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
    std::cout << "Rusiavimas uztruko " << duration.count() << " sekundes." << std::endl;
}

template <typename Container>
void DataProccess1(string filename, string sortType, bool writeToFile = true)
{
    Container students;
    Container islaike;
    Container neislaike;

    cout<<filename<<endl;

    auto start = high_resolution_clock::now();

    ReadFromFile(students, filename);
    SortStudent(students, islaike, neislaike);

    string islaikeFile = "Islaike" + std::to_string(students.size()) + ".txt";
    string neislaikeFile = "Neislaike" + std::to_string(students.size()) + ".txt";

    auto start2 = high_resolution_clock::now();
    islaike = SortOutput(sortType, islaike);
    neislaike = SortOutput(sortType, neislaike);
    std::chrono::duration<double> duration2 = high_resolution_clock::now() - start2;
    cout << "Rikiavimas uztruko " << duration2.count() << " sekundes." << endl;

    if (writeToFile){
    WriteToFile(islaike, islaikeFile);
    WriteToFile(neislaike, neislaikeFile);}

    students.clear();
    islaike.clear();
    neislaike.clear();

    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Bendrai uztruko " << duration.count() << " sekundes." << endl;
}

template <typename Container>
void DataProccess2(string filename, string sortType, int containerType)
{
    // 1 - vector, 2 - list, 3 - deque
    Container students;
    Container neislaike;

    cout<<filename<<endl;

    auto start = high_resolution_clock::now();

    ReadFromFile(students, filename);
    if (containerType == 2)
        SortStudentOneContainerList(students, neislaike);
    else
        SortStudentOneContainer(students, neislaike);

    auto start2 = high_resolution_clock::now();
    students = SortOutput(sortType, students);
    neislaike = SortOutput(sortType, neislaike);
    std::chrono::duration<double> duration2 = high_resolution_clock::now() - start2;
    cout << "Rikiavimas uztruko " << duration2.count() << " sekundes." << endl;

    string studCount = std::to_string(students.size() + neislaike.size());
    WriteToFile(students, "islaike " +  studCount);
    WriteToFile(neislaike, "neislaike " + studCount);

    students.clear();
    neislaike.clear();

    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Bendrai uztruko " << duration.count() << " sekundes." << endl;
}

template <typename Container>
void DataProccess3(string filename, string sortType, int containerType)
{
    // 1 - vector, 2 - list, 3 - deque
    Container students;
    Container neislaike;

    cout<<filename<<endl;

    auto start = high_resolution_clock::now();

    ReadFromFile(students, filename);
    if (containerType == 2)
        SortStudentOneContainerListADV(students, neislaike);
    else
        SortStudentOneContainerADV(students, neislaike);

    auto start2 = high_resolution_clock::now();
    students = SortOutput(sortType, students);
    neislaike = SortOutput(sortType, neislaike);
    std::chrono::duration<double> duration2 = high_resolution_clock::now() - start2;
    cout << "Rikiavimas uztruko " << duration2.count() << " sekundes." << endl;

    string studCount = std::to_string(students.size() + neislaike.size());
    WriteToFile(students, "islaike " +  studCount);
    WriteToFile(neislaike, "neislaike " + studCount);

    students.clear();
    neislaike.clear();

    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Bendrai uztruko " << duration.count() << " sekundes." << endl;
}

void FullDataProccess(string filename1, string filename2, string filename3, string filename4, string filename5)
{
    string sortType;
    string filenames[5] = {filename1, filename2, filename3, filename4, filename5};
    cout << "Rikiavimo tipas? (Vardas - vardas / Pavarde - pavarde / Galutinis pagal vidurki - vidurkis / Galutinis pagal mediana - mediana): ";
    cin >> sortType;
    while (sortType != "vardas" && sortType != "pavarde" && sortType != "vidurkis" && sortType != "mediana")
    {
        cout << "Iveskite 'vardas', 'pavarde', 'vidurkis' arba 'mediana': ";
        cin >> sortType;
    }
    for (int i = 0; i < 5; i++)
    {
        DataProccess1<Vector<Stud>>(filenames[i], sortType);
    }
}

void FullContainerTest(string filename1, string filename2, string filename3, string filename4, string filename5)
{
    string sortType = "vidurkis";
    double vectorTime = 0, listTime = 0, dequeTime = 0;
    string filenames[5] = {filename1, filename2, filename3, filename4, filename5};
    int times = 5;

    int stratNum = TypeInt("Pasirinkite strategija (1-3): ", 3);

    for (int i = 0; i < times; i++){
    //vector test
    cout<<"Vector konteinerio testavimas\n ---------------------------------------------------------------------------\n";
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 5; i++)
    {
        if (stratNum == 1)
            DataProccess1<Vector<Stud>>(filenames[i], sortType, false);
        else if (stratNum == 2)
            DataProccess2<Vector<Stud>>(filenames[i], sortType, 1);
        else if (stratNum == 3)
            DataProccess3<Vector<Stud>>(filenames[i], sortType, 1);
    }
    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Bendrai vector uztruko " << duration.count() << " sekundes.\n" << endl;
    vectorTime+=duration.count();

    //list test
    cout<<"List konteinerio testavimas\n ---------------------------------------------------------------------------\n";
    start = high_resolution_clock::now();
    for (int i = 0; i < 5; i++)
    {
        if (stratNum == 1)
            DataProccess1<list<Stud>>(filenames[i], sortType, false);
        else if (stratNum == 2)
            DataProccess2<list<Stud>>(filenames[i], sortType, 2);
        else if (stratNum == 3)
            DataProccess3<list<Stud>>(filenames[i], sortType, 2);
    }
    duration = high_resolution_clock::now() - start;
    cout << "Bendrai deque uztruko " << duration.count() << " sekundes." << endl;
    dequeTime+=duration.count();

    }

    cout << "Vidutiniskai vector uztruko " << vectorTime/times << " sekundes." << endl;
    cout << "Vidutiniskai list uztruko " << listTime/times << " sekundes." << endl;
    cout << "Vidutiniskai deque uztruko " << dequeTime/times << " sekundes." << endl;


}

void QuickTest(string filename1, string filename2)
{
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 5; i++)
    {
        DataProccess3<Vector<Stud>>(filename1, "vidurkis", 1);
        DataProccess3<Vector<Stud>>(filename2, "vidurkis", 1);
    }
    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Bendrai vector uztruko " << (duration/5).count() << " sekundes.\n" << endl;
}
