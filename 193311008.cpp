/*
  193311008.cpp
  Created by Tarık ÇALIŞKAN on 4.11.2020.
*/

#include <vector>
#include <random>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <typeinfo>

using namespace std;

void print(vector<int> const &input)
{
    for (int i = 0; i < input.size(); i++)
    {
        cout << input.at(i) << ' ';
    }
}

template <typename T>
bool vectorContains(const T &element, const vector<T> &vector)
{
    return find(vector.begin(), vector.end(), element) != vector.end();
}

void pointCalculator(int *point, int *plus, int *minus, int *tour)
{
    *point = 10 * *plus + 5 * *minus + (1 / *tour) * 1000 - ((*plus * *minus) / (*plus + *minus));
}

vector<int> numberGenerator()
{
    vector<int> result;
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(0, 9);

    int i = 0;
    while (i < 4)
    {
        int randVal = distr(eng);
        if (i == 0 || randVal == 0)
            randVal = distr(eng);

        if (find(begin(result), end(result), randVal) == end(result))
        {
            result.push_back(randVal);
            ++i;
        }
    }

    return result;
}

void numberChecker(vector<int> inputNum, vector<int> generatedNum, int *plus, int *minus)
{
    int correctDigits = 0;
    int incorrectDigits = 0;
    int containDigitCount = 0;
    for (size_t i = 0; i < generatedNum.size(); i++)
    {
        if (vectorContains(inputNum[i], generatedNum))
        {
            containDigitCount++;
        }

        if (inputNum[i] == generatedNum[i])
        {
            *plus += 1;
            correctDigits++;
        }
        else
        {
            *minus -= 1;
            incorrectDigits++;
        }
    }

    cout << correctDigits << " -" << incorrectDigits << " girilen rakamlarin " << containDigitCount << " tanesi var, "
         << "" << correctDigits << " tanesi dogru yerde, " << incorrectDigits << " tanesi yanlis yerde." << endl;
}

bool compareScorePair(pair<string, int> &a, pair<string, int> &b)
{
    if (a.second > b.second)
    {
        return true;
    }
    if (a.second == b.second)
    {
        return a.first.compare(b.first) > 0;
    }
    return false;
}

int main()
{
    int inputNum;
    vector<int> generatedNum = numberGenerator();
    vector<int> inputNumDigits;

    int point = 0;
    int plus = 0;
    int minus = 0;
    int tour = 1;

    while (tour < 11)
    {
        print(generatedNum);
        cout << "\n";
        cout << "Sayi tahmininizi giriniz: ";
        cin >> inputNum;

        for (int i = log10(inputNum); i >= 0; i--)
        {
            inputNumDigits.push_back(inputNum / int(pow(10, i)) % 10);
        }

        if (inputNumDigits == generatedNum)
        {
            cout << tour << ". turda bildiniz." << endl;

            numberChecker(inputNumDigits, generatedNum, &plus, &minus);
            break;
        }

        tour++;
        numberChecker(inputNumDigits, generatedNum, &plus, &minus);

        cout << plus << " " << minus << endl;
        cout << 11 - tour << " hakkiniz kalmistir."
             << endl;

        inputNumDigits.clear();
    }

    pointCalculator(&point, &plus, &minus, &tour);
    cout << point << " puan aldiniz." << endl;
}
