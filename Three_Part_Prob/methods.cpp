//
// Created by coret on 22/01/2023.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
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



std::vector<int> bruteForce(std::vector<int> S, int T, int i, bool Iter, bool Result, bool FitAvg, bool FitCount, bool ResultFit, bool showDataForGraph)
{
    auto start = std::chrono::steady_clock::now();
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

        if(Result) {
            wypiszWektor(S);
        }
        if(showDataForGraph) {
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::cout << iter << "\t" << elapsed_seconds.count() << "\t" << fitCount << "\t" << bestError << "\t" << std::endl;
        }
        if(bestError == 0) {
            if(FitAvg) {
                avgFit = avgFit/iter;
                std::cout << "Avg Fit: " << avgFit << std::endl;
            }
            if(FitCount) {
                std::cout << "Fit count: " << fitCount << std::endl;
            }
            if(Iter) {
                std::cout << "\n"
                          << "iter: " << iter << std::endl;
            }
            if(ResultFit) {
                std::cout << "error score: " << collectionErrorSum << ", current best: " << bestError << std::endl;
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

std::vector<int> losoweProbkowanie(std::vector<int> S, int T, int i, bool Iter, bool Result, bool FitAvg, bool FitCount, bool ResultFit, bool showDataForGraph)
{
    auto start = std::chrono::steady_clock::now();
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
        if(showDataForGraph) {
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::cout << iter << "\t" << elapsed_seconds.count() << "\t" << fitCount << "\t" << bestError << "\t" << std::endl;
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
        std::vector<int> sTemp = S;
        std::shuffle(std::begin(sTemp), std::end(sTemp), rng);
        int tempScore = fitness(sTemp, T);
        fitCount = fitCount + 1;

        if (tempScore < collectionErrorSum)
        {
            S = sTemp;
        }

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

std::vector<int> wspinaczkaDeterm(std::vector<int> S, int T, int i, bool Iter, bool Result, bool FitAvg, bool FitCount, bool ResultFit, bool showDataForGraph)
{
    auto start = std::chrono::steady_clock::now();
    double avgFit = 0.0;
    int fitCount = 0;
    std::vector<int> best;
    int bestError = -1;
    int iter = 0;
    int iterTemp = iter % S.size();
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
        if(showDataForGraph) {
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::cout << iter << "\t" << elapsed_seconds.count() << "\t" << fitCount << "\t" << bestError << "\t" << std::endl;
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

        std::vector<int> sTemp = S;
        int bestTempScore = 99;
        int index = 0;

        for(int a = 0; a < sTemp.size(); a++) {
            temp = sTemp[iterTemp];
            sTemp[iterTemp] = sTemp[(iterTemp + a) % sTemp.size()];
            sTemp[(iterTemp + a) % sTemp.size()] = temp;
            int tempScoreLoop = fitness(sTemp, T);

            fitCount = fitCount + 1;
            if(tempScoreLoop < bestTempScore ) {
                bestTempScore = tempScoreLoop;
                index = a;

            }
            sTemp = S;
        }

        temp = S[iterTemp];
        S[iterTemp] = S[(iterTemp + index) % S.size()];
        S[(iterTemp + index) % S.size()] = temp;

        int tempScore = fitness(S, T);
        fitCount = fitCount + 1;

        if (tempScore > collectionErrorSum)
        {
            temp = S[iterTemp];
            S[iterTemp] = S[(iterTemp + index)% S.size()];
            S[(iterTemp + index)% S.size()] = temp;
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

std::vector<int> wspinaczkaLosowa(std::vector<int> S, int T, int i, bool Iter, bool Result, bool FitAvg, bool FitCount, bool ResultFit, bool showDataForGraph)
{
    auto start = std::chrono::steady_clock::now();
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
        if(showDataForGraph) {
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::cout << iter << "\t" << elapsed_seconds.count() << "\t" << fitCount << "\t" << bestError << "\t" << std::endl;
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

std::vector<int> TABU(std::vector<int> S, int T, int i, bool Iter, bool Result, bool FitAvg, bool FitCount, bool ResultFit, bool showDataForGraph)
{
    auto start = std::chrono::steady_clock::now();
    std::shuffle(std::begin(S), std::end(S), rng);
    int tabu = 25;
    std::vector<std::vector<int>> t;
    std::vector<int> best;
    int fitCount = 0;
    int bestError = -1;
    int flag = -1;
    int iter = 0;
    double avgFit = 0;
    int iterTemp = iter % S.size();
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

        t.push_back(S);
        std::vector<int> sTemp = S;
        int bestTempScore = 99;
        int index = 0;

        for(int a = 0; a < sTemp.size(); a++) {
            temp = sTemp[iterTemp];
            sTemp[iterTemp] = sTemp[(iterTemp + a) % sTemp.size()];
            sTemp[(iterTemp + a) % sTemp.size()] = temp;

            if (!std::count(t.begin(), t.end(), sTemp)) {
                int tempScoreLoop = fitness(sTemp, T);
                fitCount = fitCount + 1;
                if (tempScoreLoop < bestTempScore) {
                    bestTempScore = tempScoreLoop;
                    index = a;
                }
            }
            sTemp = S;
        }

        temp = S[iterTemp];
        S[iterTemp] = S[(iterTemp + index) % S.size()];
        S[(iterTemp + index) % S.size()] = temp;
        t.push_back(S);

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
        }
        else
        {
            if(t.size()>=25) {
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
            if(showDataForGraph) {
                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds = end-start;
                std::cout << iter << "\t" << elapsed_seconds.count() << "\t" << fitCount << "\t" << bestError << "\t" << std::endl;
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
