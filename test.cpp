#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "helper.h"
#include <algorithm>
#include <numeric>
#include <stdexcept>

TEST_CASE("Vector: Construction") {
    Vector<int> defaultVec;
    REQUIRE(defaultVec.empty());

    Vector<int> fillVec(5, 42);
    REQUIRE(fillVec.size() == 5);
    REQUIRE(std::all_of(fillVec.begin(), fillVec.end(), [](int v) { return v == 42; }));

    Vector<int> copyVec(fillVec);
    REQUIRE(copyVec == fillVec);

    Vector<int> moveVec(std::move(copyVec));
    REQUIRE(moveVec.size() == 5);

    Vector<int> initListVec = {1, 2, 3};
    REQUIRE(initListVec[1] == 2);
}

TEST_CASE("Vector: Element Access") {
    Vector<int> vec = {10, 20, 30};

    REQUIRE(vec[0] == 10);
    REQUIRE(vec.at(1) == 20);
    REQUIRE_NOTHROW(vec.at(2));
    REQUIRE_THROWS_AS(vec.at(5), std::out_of_range);

    REQUIRE(vec.front() == 10);
    REQUIRE(vec.back() == 30);
    REQUIRE(vec.data() != nullptr);
}

TEST_CASE("std::vector: Iterators") {
    Vector<int> vec = {1, 2, 3};

    REQUIRE(std::distance(vec.begin(), vec.end()) == 3);
    REQUIRE(std::accumulate(vec.begin(), vec.end(), 0) == 6);

    Vector<int> reversed(vec.rbegin(), vec.rend());
    REQUIRE(reversed.front() == 3);
}

TEST_CASE("Simple Vector") {
    Vector<int> vec;
    REQUIRE(vec.empty());
    vec.push_back(1);
    REQUIRE(vec.size() == 1);
}

TEST_CASE("Vector: Capacity") {
    Vector<int> vec;

    REQUIRE(vec.empty());
    vec.reserve(100);
    REQUIRE(vec.capacity() >= 100);

    vec.push_back(1);
    REQUIRE(vec.size() == 1);

    vec.shrink_to_fit();
    REQUIRE(vec.capacity() >= vec.size());
}

TEST_CASE("Vector: Modifiers") {
    Vector<int> vec = {1, 2, 3};

    vec.push_back(4);
    REQUIRE(vec.back() == 4);

    vec.pop_back();
    REQUIRE(vec.size() == 3);

    vec.insert(vec.begin() + 1, 99);
    REQUIRE(vec[1] == 99);

    vec.erase(vec.begin() + 1);
    REQUIRE(vec[1] == 2);

    vec.clear();
    REQUIRE(vec.empty());

    vec.assign(3, 5);
    REQUIRE(vec == Vector<int>({5, 5, 5}));

    vec.resize(5, 9);
    REQUIRE(vec[4] == 9);

    Vector<int> swapVec = {1, 2};
    vec.swap(swapVec);
    REQUIRE(vec == Vector<int>({1, 2}));
}

TEST_CASE("Vector: Comparison Operators") {
    Vector<int> a = {1, 2, 3};
    Vector<int> b = {1, 2, 3};
    Vector<int> c = {1, 2, 4};

    REQUIRE(a == b);
    REQUIRE(a != c);
    REQUIRE(a < c);
    REQUIRE(c > b);
    REQUIRE(a <= b);
    REQUIRE(c >= a);
}

struct CtorCounter {
    static int defaultCount, copyCount;
    CtorCounter() { ++defaultCount; }
    CtorCounter(const CtorCounter&) { ++copyCount; }
};
int CtorCounter::defaultCount = 0;
int CtorCounter::copyCount = 0;

TEST_CASE("Vector: push_back only constructs as needed") {
    CtorCounter::defaultCount = 0;
    CtorCounter::copyCount = 0;
    Vector<CtorCounter> v;
    for (int i = 0; i < 10; ++i)
        v.push_back(CtorCounter());
    REQUIRE(v.size() == 10);
}

TEST_CASE("Vector: size and capacity management") {
    Vector<int> v;
    size_t lastCapacity = v.capacity();
    for (int i = 0; i < 1000; ++i) {
        v.push_back(i);
        REQUIRE(v.size() <= v.capacity());
        if (v.capacity() != lastCapacity) {
            REQUIRE(v.capacity() >= lastCapacity);
            lastCapacity = v.capacity();
        }
    }
}

TEST_CASE("Vector: operator[] and at() bounds checking") {
    Vector<int> v(5, 42);
    REQUIRE_NOTHROW(v.at(4));
    REQUIRE_THROWS_AS(v.at(5), std::out_of_range);
}

struct MoveCopyCounter {
    static int copyCount, moveCount;
    MoveCopyCounter() = default;
    MoveCopyCounter(const MoveCopyCounter&) { ++copyCount; }
    MoveCopyCounter(MoveCopyCounter&&) noexcept { ++moveCount; }
    MoveCopyCounter& operator=(const MoveCopyCounter&) { ++copyCount; return *this; }
    MoveCopyCounter& operator=(MoveCopyCounter&&) noexcept { ++moveCount; return *this; }
};
int MoveCopyCounter::copyCount = 0;
int MoveCopyCounter::moveCount = 0;

TEST_CASE("Vector: Move semantics on reallocation") {
    MoveCopyCounter::copyCount = 0;
    MoveCopyCounter::moveCount = 0;
    Vector<MoveCopyCounter> v;
    for (int i = 0; i < 10; ++i)
        v.push_back(MoveCopyCounter());
    // Now force a reallocation
    size_t oldCapacity = v.capacity();
    v.push_back(MoveCopyCounter());
    REQUIRE(MoveCopyCounter::moveCount > 0); // Now moves should have happened
}

TEST_CASE("Vector: Handles zero and large allocations") {
    Vector<int> v0(0);
    REQUIRE(v0.size() == 0);

    // Large allocation (may need to adjust size for your system)
    Vector<int> vbig(1000000, 1);
    REQUIRE(vbig.size() == 1000000);
    REQUIRE(vbig[999999] == 1);
}

TEST_CASE("Vector<Stud>: Basic Operations") {
    Vector<Stud> students;
    Stud s1;
    s1.setVardas("Jonas");
    s1.setPavarde("Jonaitis");
    s1.setEgz(8);

    students.push_back(s1);
    REQUIRE(students.size() == 1);
    REQUIRE(students[0].getVardas() == "Jonas");
    REQUIRE(students[0].getEgz() == 8);

    students.pop_back();
    REQUIRE(students.empty());
}

TEST_CASE("Vector<Stud>: Initializer List") {
    Stud s1, s2;
    s1.setVardas("A");
    s2.setVardas("B");
    Vector<Stud> group = {s1, s2};

    REQUIRE(group.size() == 2);
    REQUIRE(group[1].getVardas() == "B");
}

TEST_CASE("Vector<Stud>: Copy and Move") {
    Stud s;
    s.setVardas("CopyTest");
    Vector<Stud> v1;
    v1.push_back(s);

    Vector<Stud> v2 = v1; // Copy
    REQUIRE(v2.size() == 1);
    REQUIRE(v2[0].getVardas() == "CopyTest");

    Vector<Stud> v3 = std::move(v1); // Move
    REQUIRE(v3.size() == 1);
    REQUIRE(v3[0].getVardas() == "CopyTest");
}

TEST_CASE("Vector<Stud>: Element Access and Modification") {
    Stud s;
    s.setVardas("Mod");
    Vector<Stud> v(3, s);

    v[1].setVardas("Changed");
    REQUIRE(v[1].getVardas() == "Changed");
    REQUIRE(v.at(0).getVardas() == "Mod");
}

TEST_CASE("Stud: NdVector Interaction") {
    Stud s;
    s.addNd(10);
    s.addNd(20);

    REQUIRE(s.getNdVector().size() == 2);
    REQUIRE(s.getNdVector()[1] == 20);
}

TEST_CASE("Vector<Stud>: Iterators") {
    Stud s1, s2;
    s1.setVardas("A");
    s2.setVardas("B");
    Vector<Stud> v = {s1, s2};

    auto it = v.begin();
    REQUIRE(it->getVardas() == "A");
    ++it;
    REQUIRE(it->getVardas() == "B");
}