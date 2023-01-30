//
// Created by coret on 22/01/2023.
//

#ifndef THREE_PART_PROB_METHODS_H
#define THREE_PART_PROB_METHODS_H

void wypiszWektor(std::vector<int> v);
void wypiszWektorBezEndl(std::vector<int> v);
int fitness(std::vector<int> S, int T);
std::vector<int> bruteForce(std::vector<int> S, int T, int i, bool Iter, bool Result, bool FitAvg, bool FitCount, bool ResultFit, bool showDataForGraph);          //losowo grupuje w podzbiory i sprawdza jak dobre jest to rozwiązanie
std::vector<int> losoweProbkowanie(std::vector<int> S, int T, int i, bool Iter, bool Result, bool FitAvg, bool FitCount, bool ResultFit, bool showDataForGraph);   //losowo zmienia jedn
std::vector<int> wspinaczkaDeterm(std::vector<int> S, int T, int i, bool Iter, bool Result, bool FitAvg, bool FitCount, bool ResultFit, bool showDataForGraph);
std::vector<int> wspinaczkaLosowa(std::vector<int> S, int T, int i, bool Iter, bool Result, bool FitAvg, bool FitCount, bool ResultFit, bool showDataForGraph);
std::vector<int> TABU(std::vector<int> S, int T, int i, bool Iter, bool Result, bool FitAvg, bool FitCount, bool ResultFit, bool showDataForGraph);


#endif //THREE_PART_PROB_METHODS_H
