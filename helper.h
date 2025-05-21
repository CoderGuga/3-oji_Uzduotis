#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <iomanip>
#include <string>
//#include <vector>
#include <sstream>
#include <optional>
#include <limits>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <exception>
#include <random>
#include <sstream>
#include <list>
#include <deque>
#include "Vector.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::cerr;
using std::getline;
using namespace std::chrono;
using std::sort;
using std::optional;
using std::stringstream;
using std::list;
using std::deque;


template <typename T>
optional<T> string_to(const string & s);

int CheckInt(const string& text, int max = 0);
int TypeInt(const string& text, int max = 0);
string TypeString(const string& prompt);
double Median(Vector<int> numbers);
double Average(Vector<int> numbers);

extern int MAX_GRADES;

class Zmogus {
    protected:
        string pavarde;
        string vardas;

    public:
        Zmogus() {pavarde = "Pavardenis"; vardas = "Vardenis";};
        Zmogus(const Zmogus& other) : pavarde(other.pavarde), vardas(other.vardas) {}
        Zmogus(Zmogus&& other) : pavarde(std::move(other.pavarde)), vardas(std::move(other.vardas)) {}
        virtual void KiekGavauIsEgz() = 0;
};

class Stud : public Zmogus {
private:
    int egz;
    Vector<int> ndVector;
    int* nd;
    int nd_count;
    float galutinisVid;
    float galutinisMed;

public:

    Stud();
    virtual ~Stud();

    //getters
    inline string getPavarde() const { return pavarde; }
    inline string getVardas() const { return vardas; }
    inline int getEgz() const { return egz; }
    inline Vector<int> getNdVector() const { return ndVector; }
    inline int* getNd() const { return nd; }
    inline int getNdCount() const { return nd_count; }
    inline float getGalutinisVid() const { return galutinisVid; }
    inline float getGalutinisMed() const { return galutinisMed; }

    //setters
    inline void setPavarde(const string& pavarde) { this->pavarde = pavarde; }
    inline void setVardas(const string& vardas) { this->vardas = vardas; }
    inline void setEgz(int egz) { this->egz = egz; }
    inline void setNdVector(const Vector<int>& ndVector) { this->ndVector = ndVector; }
    inline void setNd(int* nd, int count) {
        delete[] this->nd;
        this->nd = new int[count];
        std::copy(nd, nd + count, this->nd);
        this->nd_count = count;
    }
    inline void setGalutinisVid(float galutinisVid) { this->galutinisVid = galutinisVid; }
    inline void setGalutinisMed(float galutinisMed) { this->galutinisMed = galutinisMed; }

    void clearNdVector() {this->ndVector.clear(); }
    void addNd(int nd) {this->ndVector.push_back(nd); }

    //rule of 5
    Stud(const Stud& other);
    Stud& operator=(const Stud& other);
    Stud(Stud&& other) noexcept;
    Stud& operator=(Stud&& other) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Stud& stud);
    friend std::istream& operator>>(std::istream& is, Stud& student);

    void KiekGavauIsEgz() override {cout << "Is egzamino gavau" << egz << endl;}
};

void MethodTest();

#endif