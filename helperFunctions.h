#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H

#include "helper.h"

int RandInt(int min, int max);
int RandIntWSeed(int min, int max, std::mt19937 generator);
string GenName();
string GenSurname();
void GenFile(string filename, int amount);
void GenFiles();
int CountWordsInLine(const string& line);
void Pause();

#endif // HELPFUNCTIONS_H