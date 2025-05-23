#include "Vector.h"
#include "cFunctions.h"
#include <chrono>
#include <vector>
#include <iostream>

void vectorTest()
{
    double timer = 0;
    std::vector<int> v;
    for (int i = 0; i < 5; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int a = 0; a < 10000; a++)
        {
            v.push_back(a);
        }
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
        timer+=duration.count();
        std::cout << v[0] << " " << v[1] << " " << v[2] << " " << v[v.size() - 1] << std::endl;
        v.clear();
    }
    std::cout << "std::vector uzpildyti 10000 uztruko: " << timer/5 <<std::endl;

    timer = 0;
    for (int i = 0; i < 5; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int a = 0; a < 100000; a++)
        {
            v.push_back(a);
        }
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
        timer+=duration.count();
        std::cout << v[0] << " " << v[1] << " " << v[2] << " " << v[v.size() - 1] << std::endl;
        v.clear();
    }
    std::cout << "std::vector uzpildyti 100 000 uztruko: " << timer/5 <<std::endl;

    timer = 0;
    for (int i = 0; i < 5; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int a = 0; a < 1000000; a++)
        {
            v.push_back(a);
        }
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
        timer+=duration.count();
        std::cout << v[0] << " " << v[1] << " " << v[2] << " " << v[v.size()  - 1] << std::endl;
        v.clear();
    }
    std::cout << "std::vector uzpildyti 1 000 000 uztruko: " << timer/5 <<std::endl;

    timer = 0;
    for (int i = 0; i < 5; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int a = 0; a < 10000000; a++)
        {
            v.push_back(a);
        }
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
        timer+=duration.count();
        std::cout << v[0] << " " << v[1] << " " << v[2] << " " << v[v.size()  - 1] << std::endl;
        v.clear();
    }
    std::cout << "std::vector uzpildyti 10 000 000 uztruko: " << timer/5 <<std::endl;

    timer = 0;
    for (int i = 0; i < 5; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int a = 0; a < 100000000; a++)
        {
            v.push_back(a);
        }
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
        timer+=duration.count();
        std::cout << v[0] << " " << v[1] << " " << v[2] << " " << v[v.size()  - 1] << std::endl;
        v.clear();
    }
    std::cout << "std::vector uzpildyti 100 000 000 uztruko: " << timer/5 <<std::endl;
}

void myVectorTest()
{
    double timer = 0;
    Vector<int> v;
    for (int i = 0; i < 5; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int a = 0; a < 10000; a++)
        {
            v.push_back(a);
        }
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
        timer+=duration.count();
        std::cout << v[0] << " " << v[1] << " " << v[2] << " " << v[v.size() - 1] << std::endl;
        v.clear();
    }
    std::cout << "Vector uzpildyti 10 000 uztruko: " << timer/5 <<std::endl;

    timer = 0;
    for (int i = 0; i < 5; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int a = 0; a < 100000; a++)
        {
            v.push_back(a);
        }
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
        timer+=duration.count();
        std::cout << v[0] << " " << v[1] << " " << v[2] << " " << v[v.size() - 1] << std::endl;
        v.clear();
    }
    std::cout << "Vector uzpildyti 100 000 uztruko: " << timer/5 <<std::endl;

    timer = 0;
    for (int i = 0; i < 5; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int a = 0; a < 1000000; a++)
        {
            v.push_back(a);
        }
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
        timer+=duration.count();
        std::cout << v[0] << " " << v[1] << " " << v[2] << " " << v[v.size() - 1] << std::endl;
        v.clear();
    }
    std::cout << "Vector uzpildyti 1 000 000 uztruko: " << timer/5 <<std::endl;

    timer = 0;
    for (int i = 0; i < 5; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int a = 0; a < 10000000; a++)
        {
            v.push_back(a);
        }
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
        timer+=duration.count();
        std::cout << v[0] << " " << v[1] << " " << v[2] << " " << v[v.size() - 1] << std::endl;
        v.clear();
    }
    std::cout << "Vector uzpildyti 10 000 000 uztruko: " << timer/5 <<std::endl;

    timer = 0;
    for (int i = 0; i < 5; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int a = 0; a < 100000000; a++)
        {
            v.push_back(a);
        }
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
        timer+=duration.count();
        std::cout << v[0] << " " << v[1] << " " << v[2] << " " << v[v.size() - 1] << std::endl;
        v.clear();
    }
    std::cout << "Vector uzpildyti 100 000 000 uztruko: " << timer/5 <<std::endl;
}

void reserveTest()
{
    Vector<int> v;
    int vCounter = 0, sCounter = 0;
    for (int a = 0; a < 100000000; a++)
    {
        if (v.size() == v.capacity())
            vCounter++;
        v.push_back(a);
    }
    v.clear();
    std::vector<int> s;
    for (int a = 0; a < 100000000; a++)
    {
        if (s.size() == s.capacity())
            sCounter++;
        s.push_back(a);
    }
    s.clear();
    std::cout << "Vector perskirste: " << vCounter << " kartu" << std::endl;
    std::cout << "std::vector perskirste: " << sCounter << " kartu" << std::endl;
}

void ContainerTest()
{
    int count = 1;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++)
    {
        DataProccess3<Vector<Stud>>("100 000 studentu.txt", "vidurkis", 1);
        DataProccess3<Vector<Stud>>("1 000 000 studentu.txt", "vidurkis", 1);
        DataProccess3<Vector<Stud>>("10 000 000 studentu.txt", "vidurkis", 1);
    }
    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Bendrai Vector uztruko " << (duration/count).count() << " sekundes.\n" << endl;


    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++)
    {
        DataProccess3<std::vector<Stud>>("100 000 studentu.txt", "vidurkis", 1);
        DataProccess3<std::vector<Stud>>("1 000 000 studentu.txt", "vidurkis", 1);
        DataProccess3<std::vector<Stud>>("10 000 000 studentu.txt", "vidurkis", 1);
    }
    duration = high_resolution_clock::now() - start;
    cout << "Bendrai std::vector uztruko " << (duration/count).count() << " sekundes.\n" << endl;
}

int main() {
    ContainerTest();
    return 0;
}