//
// Created by coret on 22/01/2023.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "methods.h"

auto rng = std::default_random_engine{};

void wypiszWektor(std::vector<int> v)
{
    for (int y = 0; y < v.size(); y++)
    {
        std::cout << v.at(y) << " ";
    }
    std::cout << std::endl;
}

void wypiszWektorBezEndl(std::vector<int> v)
{
    for (int y = 0; y < v.size(); y++)
    {
        std::cout << v.at(y) << " ";
    }
}

int fitness(std::vector<int> S, int T)
{
    std::vector<std::vector<int>> collection;
    for (int i = 0; i < S.size() / 3; i++)
    {
        std::vector<int> temp1;
        for (int j = 0; j < 3; j++)
        {
            temp1.push_back(S.at(j + (i * 3)));
        }

        collection.push_back(temp1);
    }

    int error = 0;
    int collectionErrorSum = 0;

    for (std::vector<int> subset : collection)
    {
        // wypiszWektorBezEndl(subset);
        // std::cout << " ";
        int suma = 0;
        for (int a : subset)
        {
            suma += a;
        }
        error = T - suma;
        // std::cout << error << " ";
        collectionErrorSum += abs(error);
    }
    // std::cout << " " << collectionErrorSum << std::endl;
    return collectionErrorSum;
}



std::vector<int> bruteForce(std::vector<int> S, int T, int i, bool Iter, bool Result, bool FitAvg, bool FitCount, bool ResultFit)
{
    std::vector<int> best;
    int bestError = -1;
    int iter = 0;
    double avgFit = 0.0;
    int fitCount = 0;

    do
    {
        int collectionErrorSum = fitness(S, T);
        avgFit = avgFit + collectionErrorSum;
        fitCount = fitCount + 1;

        if (bestError > collectionErrorSum || bestError == -1)
        {
            bestError = collectionErrorSum;
            best = S;
        }
        if(Iter) {
            std::cout << "\n"
                      << "iter: " << iter << std::endl;
        }
        if(Result) {
            wypiszWektor(S);
        }
        if(ResultFit) {
            std::cout << "error score: " << collectionErrorSum << ", current best: " << bestError << std::endl;
        }
        if(bestError == 0) {
            if(FitAvg) {
                avgFit = avgFit/iter;
                std::cout << "Avg Fit: " << avgFit << std::endl;
            }
            if(FitCount) {
                std::cout << "Fit count: " << fitCount << std::endl;
            }
            return best;
        }
        iter++;
        i--;
    } while (std::next_permutation(S.begin(), S.end()) && i > 0);

    if(FitAvg) {
        avgFit = avgFit/iter;
        std::cout << "Avg Fit: " << avgFit << std::endl;
    }
    if(FitCount) {
        std::cout << "Fit count: " << fitCount << std::endl;
    }
    return best;
}

std::vector<int> losoweProbkowanie(std::vector<int> S, int T, int i, bool Iter, bool Result, bool FitAvg, bool FitCount, bool ResultFit)
{
    std::vector<int> best;
    int bestError = -1;
    int iter = 0;
    double avgFit = 0;
    int fitCount = 0;
    do
    {
        int collectionErrorSum = fitness(S, T);
        avgFit = avgFit + collectionErrorSum;
        fitCount = fitCount + 1;

        if (bestError > collectionErrorSum || bestError == -1)
        {
            bestError = collectionErrorSum;
            best = S;
        }
        if(Iter) {
            std::cout << "\n"
                      << "iter: " << iter << std::endl;
        }
        if(Result) {
            wypiszWektor(S);
        }
        if(ResultFit) {
            std::cout << "error score: " << collectionErrorSum << ", current best: " << bestError << std::endl;
        }
        if(bestError == 0) {
            if(FitAvg) {
                avgFit = avgFit/iter;
                std::cout << "Avg Fit: " << avgFit << std::endl;
            }
            if(FitCount) {
                std::cout << "Fit count: " << fitCount << std::endl;
            }
            return best;
        }
        iter++;
        i--;
        std::shuffle(std::begin(S), std::end(S), rng);

    } while (i > 0);
    if(FitAvg) {
        avgFit = avgFit/iter;
        std::cout << "Avg Fit: " << avgFit << std::endl;
    }
    if(FitCount) {
        std::cout << "Fit count: " << fitCount << std::endl;
    }
    return best;
}

std::vector<int> wspinaczkaDeterm(std::vector<int> S, int T, int i, bool Iter, bool Result, bool FitAvg, bool FitCount, bool ResultFit)
{
    double avgFit = 0.0;
    int fitCount = 0;
    std::vector<int> best;
    int bestError = -1;
    int iter = 0;
    int iterTemp = 0;
    int temp = 0;
    do
    {
        int collectionErrorSum = fitness(S, T);
        avgFit = avgFit + collectionErrorSum;
        fitCount = fitCount + 1;

        if (bestError > collectionErrorSum || bestError == -1)
        {
            bestError = collectionErrorSum;
            best = S;
        }


        if(Iter) {
            std::cout << "\n"
                      << "iter: " << iter << std::endl;
        }
        if(Result) {
            wypiszWektor(S);
        }
        if(ResultFit) {
            std::cout << "error score: " << collectionErrorSum << ", current best: " << bestError << std::endl;
        }
        if(bestError == 0) {
            if(FitAvg) {
                avgFit = avgFit/iter;
                std::cout << "Avg Fit: " << avgFit << std::endl;
            }
            if(FitCount) {
                std::cout << "Fit count: " << fitCount << std::endl;
            }
            return best;
        }
        for (int a = 0; a < S.size(); a++)
        {
            iterTemp = iter % S.size();
            temp = S[iterTemp];
            S[iterTemp] = S[iterTemp + a];
            S[iterTemp + a] = temp;

            int tempScore = fitness(S, T);
            fitCount = fitCount + 1;

            if (tempScore < collectionErrorSum) { }
            else
            {
                temp = S[iterTemp];
                S[iterTemp] = S[iterTemp + a];
                S[iterTemp + a] = temp;
            }
        }

        iter++;
        i--;

    } while (i > 0);
    if(FitAvg) {
        avgFit = avgFit/iter;
        std::cout << "Avg Fit: " << avgFit << std::endl;
    }
    if(FitCount) {
        std::cout << "Fit count: " << fitCount << std::endl;
    }
    return best;
}

std::vector<int> wspinaczkaLosowa(std::vector<int> S, int T, int i, bool Iter, bool Result, bool FitAvg, bool FitCount, bool ResultFit)
{
    std::shuffle(std::begin(S), std::end(S), rng);
    std::vector<int> best;
    int bestError = -1;
    int iter = 0;
    double avgFit = 0;
    int fitCount = 0;
    do
    {
        int collectionErrorSum = fitness(S, T);
        avgFit = avgFit + collectionErrorSum;
        fitCount = fitCount + 1;

        if (bestError > collectionErrorSum || bestError == -1)
        {
            bestError = collectionErrorSum;
            best = S;
        }
        if(Iter) {
            std::cout << "\n"
                      << "iter: " << iter << std::endl;
        }
        if(Result) {
            wypiszWektor(S);
        }
        if(ResultFit) {
            std::cout << "error score: " << collectionErrorSum << ", current best: " << bestError << std::endl;
        }
        if(bestError == 0) {
            if(FitAvg) {
                avgFit = avgFit/iter;
                std::cout << "Avg Fit: " << avgFit << std::endl;
            }
            if(FitCount) {
                std::cout << "Fit count: " << fitCount << std::endl;
            }
            return best;
        }
        int r = rand() % S.size();
        int r2 = rand() % S.size();

        int temp = S[r];
        S[r] = S[r2];
        S[r2] = temp;

        iter++;
        i--;

    } while (i > 0);
    if(FitAvg) {
        avgFit = avgFit/iter;
        std::cout << "Avg Fit: " << avgFit << std::endl;
    }
    if(FitCount) {
        std::cout << "Fit count: " << fitCount << std::endl;
    }
    return best;
}

std::vector<int> TABU(std::vector<int> S, int T, int i, bool Iter, bool Result, bool FitAvg, bool FitCount, bool ResultFit)
{
    std::shuffle(std::begin(S), std::end(S), rng);
    int tabu = 25;
    std::vector<std::vector<int>> t;
    std::vector<int> best;
    int tabuCount = 0;
    int fitCount = 0;
    int bestError = -1;
    int flag = -1;
    int iter = 0;
    double avgFit = 0;

    do
    {

        int collectionErrorSum = fitness(S, T);
        avgFit = avgFit + collectionErrorSum;
        fitCount = fitCount + 1;

        if (bestError > collectionErrorSum || bestError == -1)
        {
            bestError = collectionErrorSum;
            best = S;
        }

        int r = rand() % S.size();
        int r2 = rand() % S.size();
        std::cout << "index 1: " << r << ", index 2: " << r2 << std::endl;

        if (!std::count(t.begin(), t.end(), S)) {
            flag = -1;
        }

        if (flag == -1)
        {
            flag = 0;
            if(Iter) {
                std::cout << "\n"
                          << "iter: " << iter << std::endl;
            }
            if(Result) {
                wypiszWektor(S);
            }
            if(ResultFit) {
                std::cout << "error score: " << collectionErrorSum << ", current best: " << bestError << std::endl;
            }
            if(bestError == 0) {
                if(FitAvg) {
                    avgFit = avgFit/iter;
                    std::cout << "Avg Fit: " << avgFit << std::endl;
                }
                if(FitCount) {
                    std::cout << "Fit count: " << fitCount << std::endl;
                }
                return best;
            }
            t.push_back(S);
            int temp = S[r];
            S[r] = S[r2];
            S[r2] = temp;
        }
        else
        {
            tabuCount++;
            if(tabuCount>=25) {
                t.erase(t.begin());
            }

            if(Iter) {
                std::cout << "\n"
                          << "iter: " << iter << std::endl;
            }
            if(Result) {
                wypiszWektor(S);
            }
            if(ResultFit) {
                std::cout << "error score: " << collectionErrorSum << ", current best: " << bestError << std::endl;
            }

            if(bestError == 0) {
                if(FitAvg) {
                    avgFit = avgFit/iter;
                    std::cout << "Avg Fit: " << avgFit << std::endl;
                }
                if(FitCount) {
                    std::cout << "Fit count: " << fitCount << std::endl;
                }
                return best;
            }

            int temp = S[r];
            S[r] = S[r2];
            S[r2] = temp;
        }
        std::cout << tabuCount << std::endl;
        iter++;
        i--;

    } while (i > 0);
    if(FitAvg) {
        avgFit = avgFit/iter;
        std::cout << "Avg Fit: " << avgFit << std::endl;
    }
    if(FitCount) {
        std::cout << "Fit count: " << fitCount << std::endl;
    }
    return best;
}
