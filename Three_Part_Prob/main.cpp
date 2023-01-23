#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include "tp_args.hpp"
#include <fstream>
#include <chrono>
#include "methods.h"

auto RNG = std::default_random_engine{};

int main(int argc, char **argv)
{
    using namespace tp::args;
    using namespace std;

    int iterations_t;
    std::string method_t;
    std::string link_t;
    bool showIter;
    bool showResult;
    bool showResultFit;
    bool showFitAvg;
    bool showTime;
    bool showFitCount;
    int shuffleData;


    map<string, function<vector<int>(std::vector<int>, int, int, bool, bool, bool, bool, bool)>> methods = {
            {"bruteForce", bruteForce},
            {"losoweProbkowanie", losoweProbkowanie},
            {"wspinaczkaDeterm", wspinaczkaDeterm},
            {"wspinaczkaLosowa", wspinaczkaLosowa},
            {"TABU", TABU}
            //{"annealing",[](Problem p,int i,bool a, bool b, bool c){return SolveAnnealing(p,i,a,b,c,annealTemp,tempMap.at(tempMethod));}},
            //{"genetic",[](Problem p,int i, bool a, bool b, bool c){return SolveGenetic(p,i,a,b,c,p_cross,p_mutation,pSize,useElites);}}
    };

    auto help = arg(argc, argv, "help", false);

    iterations_t = arg(argc, argv, "iterations", 1000, "Maximum number of iterations.");
    method_t = arg(argc, argv, "method", std::string("bruteForce"),"Method Available are: bruteForce TABU losoweProbkowanie wspinaczkaDeterm wspinaczkaLosowa.");
    link_t = arg(argc,argv,"link", std::string("..\\data.txt"), "Path to the input file");
    showIter = arg(argc, argv, "showIterations", false, "Whether to show the Iteration number.");
    showFitAvg = arg(argc, argv, "showFitAvg", false, "Whether to show the method's fitness");
    showFitCount = arg(argc, argv,"showFitCount", false, "Whether to show the count of fitness algorithm");
    showResult = arg(argc, argv, "showResult", false, "Whether to show the results.");
    showResultFit = arg(argc, argv,"showResultFit", false, "Whether to show the result fitness.");
    showTime = arg(argc, argv, "showTime", false, "Whether to show the time for the method to reach it's results.");
    shuffleData = arg(argc, argv, "shuffleData", 0, "Whether to shuffle data beforehand.");

    if (help) {
        std::cout << "help screen.." << std::endl;
        args_info(std::cout);
        return 0;
    }

    std::vector<int> multiset;
    ifstream f(link_t);
    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            multiset.push_back(stoi(line));
        }
        f.close();
    }else {
        cout<<"error, failed to load file: ";
        cout<<link_t<<endl;
        return 0;
    }

    int sumS = 0;          // suma całego zbioru S
    int m = 1;             // liczba możliwych 3-elementowych podzbiorów
    int T = 1;             // suma liczb w każdym podzbiorze

    std::vector<int> temp; // vektor do tymczasowego zbierania podzbiorów
    int x = multiset.size();
    for (int i = 0; i < x; i++)
    {
        sumS = sumS + multiset[i];
    };
    if(sumS==0)sumS=1;
    m = x / 3;
    if(m==0)m=1;
    T = sumS / m;

    for(int i = 0; i != shuffleData; i++) {
        std::shuffle(std::begin(multiset), std::end(multiset), RNG);
    }

    auto start = std::chrono::steady_clock::now();
    vector<int> result = methods.at(method_t)(multiset, T, iterations_t, showIter, showResult, showFitAvg, showFitCount, showResultFit);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    if(showTime) {
        cout << "Time elapsed: " << elapsed_seconds.count() << "s.";
    }

    return 0;
}