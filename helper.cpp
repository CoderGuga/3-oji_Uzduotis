#include "helper.h"

template <typename T>
optional<T> string_to(const string & s) {
    stringstream ss(s);
    T result;
    if (ss >> result)
        return result;
    return std::nullopt;
}

int CheckInt(const string& text, int max) {
    cout << text;
    while (true) {
        string input;
        cin >> input;
        try {
            auto result = string_to<int>(input);
            if (result) {
                if (max == 0 || result <= max)
                    return *result;
                else
                    cout << "Per didelis skaicius" << endl;
            } else {
                throw std::invalid_argument("Neteisinga ivestis");
            }
        } catch (const std::invalid_argument&) {
            cout << "Ivestas ne sveikas skaicius. Bandykite dar karta." << endl;
        } catch (const std::exception& e) {
            cerr << "Klaida: " << e.what() << endl;
        }
    }
}

int TypeInt(const string& text, int max) {
    cout << text;
    string input;
    while (true) {
        cin >> input;
        auto result = string_to<int>(input);
        if (result) {
            if (max == 0 || result <= max)
                return *result;
            else
                cout << "Per didelis skaicius" << endl;
        } else {
            cout << "Irasykite sveika skaiciu" << endl;
        }
    }
}

string TypeString(const string& prompt) {
    string output;
    cout << prompt;
    while (!(cin >> output)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid string: ";
    }
    return output;
}

double Median(Vector<int> numbers) {
    Vector<int> sorted = numbers;
    sort(sorted.begin(), sorted.end());
    double median = 0.0;
    if (sorted.size() > 0)
    {
        if (sorted.size() % 2 == 0)
            median = (sorted[sorted.size() / 2 - 1] + sorted[sorted.size() / 2]) / 2.0;
        else
            median = sorted[sorted.size() / 2];
    }
    return median;
}

double Average(Vector<int> numbers) {
    double sum = 0;
    for (int grade : numbers) {
        sum += grade;
    }
    double average = 0;
    if (numbers.size() > 0)
        average = sum / numbers.size();
    return average;
}

int MAX_GRADES = 10;

Stud::Stud() : Zmogus(), egz(10), nd(nullptr), nd_count(0), galutinisVid(0.0f), galutinisMed(0.0f) {
    // Initialization code (if any)
    //cout << "constructor"<<endl;
}

Stud::~Stud() {
    delete[] nd;
    nd = nullptr;

    ndVector.clear();

    nd_count = 0;
    galutinisVid = 0.0f;
    galutinisMed = 0.0f;
}

Stud::Stud(const Stud& other) :
        Zmogus(other),
      egz(other.egz),
      ndVector(other.ndVector),
      nd_count(other.nd_count),
      galutinisVid(other.galutinisVid),
      galutinisMed(other.galutinisMed) {
    if (other.nd) {
        nd = new int[nd_count];
        std::copy(other.nd, other.nd + nd_count, nd);
    } else {
        nd = nullptr;
    }
    //cout << "copy constructor"<<endl;
}

Stud& Stud::operator=(const Stud& other) {
    if (this == &other) return *this; // Self-assignment check

    // Clean up existing resources
    delete[] nd;

    // Copy data
    pavarde = other.pavarde;
    vardas = other.vardas;
    egz = other.egz;
    ndVector = other.ndVector;
    nd_count = other.nd_count;
    galutinisVid = other.galutinisVid;
    galutinisMed = other.galutinisMed;

    // Deep copy the dynamic array
    if (other.nd) {
        nd = new int[nd_count];
        std::copy(other.nd, other.nd + nd_count, nd);
    } else {
        nd = nullptr;
    }
    //cout << "copy assignment operator"<<endl;

    return *this;
}

Stud::Stud(Stud&& other) noexcept
    : Zmogus(std::move(other)),
      egz(other.egz),
      ndVector(std::move(other.ndVector)),
      nd(other.nd),
      nd_count(other.nd_count),
      galutinisVid(other.galutinisVid),
      galutinisMed(other.galutinisMed) {
        other.nd = nullptr;
        other.nd_count = 0;
        other.egz = 0;
        other.galutinisMed = 0;
        other.galutinisVid = 0;
    //cout << "move constructor"<<endl;
}

Stud& Stud::operator=(Stud&& other) noexcept {
    if (this == &other) return *this; // Self-assignment check

    // Clean up existing resources
    delete[] nd;

    // Transfer ownership of resources
    pavarde = std::move(other.pavarde);
    vardas = std::move(other.vardas);
    egz = other.egz;
    ndVector = std::move(other.ndVector);
    nd = other.nd;
    nd_count = other.nd_count;
    galutinisVid = other.galutinisVid;
    galutinisMed = other.galutinisMed;

    // Leave the source object in a valid state
    other.nd = nullptr;
    other.nd_count = 0;
    other.egz = 0;
    other.galutinisMed = 0;
    other.galutinisVid = 0;

    //cout << "move assignment operator"<<endl;

    return *this;
}


std::ostream& operator<<(std::ostream& os, const Stud& stud) {
    if (os.rdbuf() == std::cout.rdbuf()) {
        // Output for terminal
        os << "Terminal output:\n";
        os << "Vardas: " << stud.vardas << "\n";
        os << "Pavarde: " << stud.pavarde << "\n";
        os << "Egzaminas: " << stud.egz << "\n";
        os << "ND Vector: ";
        for (const auto& nd : stud.ndVector) {
            os << nd << " ";
        }
        os << "\nGalutinis Vidurkis: " << stud.galutinisVid << "\n";
        os << "Galutinis Mediana: " << stud.galutinisMed << "\n";
    } else {
        os << stud.getVardas() << " " << stud.getPavarde() << " ";
        for (int nd : stud.getNdVector())
        {
            os << nd << " ";
        }
        os << stud.getEgz();
    }
    return os;
}


std::istream& operator>>(std::istream& is, Stud& student) {
    if (is.rdbuf() == std::cin.rdbuf()) {
        // Input from terminal (interactive)
        student.setVardas(TypeString("Studento vardas: "));
        student.setPavarde(TypeString("Studento pavarde: "));
        student.setEgz(CheckInt("Egzamino pazymys: ", 10));
        std::cout << "egzaminas: " << student.getEgz() << std::endl;

        std::string con = TypeString("Prideti namu darba? y/n  ");
        student.clearNdVector();
        while (con == "y") {
            int nd = CheckInt("Namu darbu pazymys: ", 10);
            student.addNd(nd);
            con = TypeString("Prideti dar viena? y/n  ");
        }
    } else {
        // Input from file or stream
        student.clearNdVector();
        is >> student.vardas >> student.pavarde;
        int grade;
        while (is >> grade) {
            student.addNd(grade);
        }

        // The last number is egzaminas, pop it from ndVector and set it as egz
        if (!student.ndVector.empty()) {
            student.egz = student.ndVector.back();
            student.ndVector.pop_back();
        }
    }

    // Recalculate grades
    student.galutinisVid = student.egz * 0.6 + 0.4 * Average(student.ndVector);
    student.galutinisMed = student.egz * 0.6 + 0.4 * Median(student.ndVector);

    return is;
}

bool operator==(const Stud& lhs, const Stud& rhs) {
    return lhs.getPavarde() == rhs.getPavarde() &&
           lhs.getVardas() == rhs.getVardas() &&
           lhs.getEgz() == rhs.getEgz() &&
           lhs.getNdVector() == rhs.getNdVector() &&
           lhs.getNdCount() == rhs.getNdCount() &&
           lhs.getGalutinisVid() == rhs.getGalutinisVid() &&
           lhs.getGalutinisMed() == rhs.getGalutinisMed();
}

bool operator!=(const Stud& lhs, const Stud& rhs) {
    return !(lhs == rhs);
}

void MethodTest()
{
    Stud s1;
    s1.setVardas("Jonas");
    s1.setEgz(10);
    cout << "s1 vardas " << s1<<endl;
    Stud s2(s1);
    cout << "s2 vardas " << s2<<endl;
    s1.setVardas("Tadas");
    cout << "s2 vardas " << s2<<endl;
    s2 = s1;
    cout << "s2 vardas " << s2<<endl;
    s1.setVardas("Pranas");
    Stud s3 (std::move(s1));
    cout << "s1 vardas " << s1<<endl;
    cout << "s3 vardas " << s3<<endl;
    s3 = std::move(s2);
    cout << "s2 vardas " << s2<<endl;
    cout << "s3 vardas " << s3<<endl;

    Stud s4;
    cin >> s4;
    //cout << s4;
    std::ofstream ofile("test.txt");
    ofile << s4;
    ofile.close();
    std::ifstream ifile("test.txt");
    Stud s5;
    ifile >> s5;
    ifile.close();
    cout << s5;
}

