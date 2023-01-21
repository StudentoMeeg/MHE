#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>

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

std::vector<int> bruteForce(std::vector<int> S, int T, int i)
{
    std::vector<int> best;
    int bestError = -1;
    int iter = 0;
    do
    {
        int collectionErrorSum = fitness(S, T);

        if (bestError > collectionErrorSum || bestError == -1)
        {
            bestError = collectionErrorSum;
            best = S;
        }
        std::cout << "\n"
                  << "iter: " << iter << std::endl;
        wypiszWektor(S);
        std::cout << "error score: " << collectionErrorSum << ", current best: " << bestError << std::endl;
        iter++;
        i--;
    } while (std::next_permutation(S.begin(), S.end()) && i > 0);
    return best;
}

std::vector<int> losoweProbkowanie(std::vector<int> S, int T, int i)
{
    std::vector<int> best;
    int bestError = -1;
    int iter = 0;
    do
    {
        int collectionErrorSum = fitness(S, T);

        if (bestError > collectionErrorSum || bestError == -1)
        {
            bestError = collectionErrorSum;
            best = S;
        }

        std::cout << "\n"
                  << "iter: " << iter << std::endl;
        wypiszWektor(S);
        std::cout << "error score: " << collectionErrorSum << ", current best: " << bestError << std::endl;
        iter++;
        i--;
        std::shuffle(std::begin(S), std::end(S), rng);
        std::shuffle(std::begin(S), std::end(S), rng);
    } while (i > 0);
    return best;
}

std::vector<int> wspinaczkaDeterm(std::vector<int> S, int T, int i)
{
    std::shuffle(std::begin(S), std::end(S), rng);
    if (i > S.size())
    {
        i = S.size();
    }
    std::vector<int> best;
    int bestError = -1;
    int iter = 0;
    int temp = 0;
    do
    {
        int collectionErrorSum = fitness(S, T);

        if (bestError > collectionErrorSum || bestError == -1)
        {
            bestError = collectionErrorSum;
            best = S;
        }
        std::cout << "\n"
                  << "iter: " << iter << std::endl;
        wypiszWektor(S);
        std::cout << "error score: " << collectionErrorSum << ", current best: " << bestError << std::endl;

        for (int a = 0; a < S.size(); a++)
        {
            temp = S[iter];
            if ((iter + 1) > S.size())
            {
                break;
            }
            else
            {
                S[iter] = S[iter + 1];
            }
            S[iter + 1] = temp;

            int tempScore = fitness(S, T);
            if (tempScore < collectionErrorSum)
            {
            }
            else
            {
                temp = S[iter];
                if ((iter + 1) > S.size())
                {
                    break;
                }
                else
                {
                    S[iter] = S[iter + 1];
                }
                S[iter + 1] = temp;
            }
        }

        iter++;
        i--;

    } while (i > 0);
    return best;
}

std::vector<int> wspinaczkaLosowa(std::vector<int> S, int T, int i)
{

    std::vector<int> best;
    int bestError = -1;
    int iter = 0;
    do
    {
        int collectionErrorSum = fitness(S, T);

        if (bestError > collectionErrorSum || bestError == -1)
        {
            bestError = collectionErrorSum;
            best = S;
        }
        std::cout << "\n"
                  << "iter: " << iter << std::endl;
        wypiszWektor(S);
        std::cout << "error score: " << collectionErrorSum << ", current best: " << bestError << std::endl;

        int r = rand() % S.size();
        int r2 = rand() % S.size();

        int temp = S[r];
        S[r] = S[r2];
        S[r2] = temp;

        iter++;
        i--;

    } while (i > 0);
    return best;
}

std::vector<int> TABU(std::vector<int> S, int T, int i, int tabu)
{
    std::vector<std::vector<int>> t;
    std::vector<int> best;
    int tabuCount = 0;
    int bestError = -1;
    int flag = -1;
    int iter = 0;

    do
    {

        int collectionErrorSum = fitness(S, T);

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
            std::cout << "\n"
                      << "iter: " << iter << std::endl;
            wypiszWektor(S);
            std::cout << "error score: " << collectionErrorSum << ", current best: " << bestError << std::endl;

            t.push_back(S);
            int temp = S[r];
            S[r] = S[r2];
            S[r2] = temp;
        }
        else
        {   
            tabuCount++;
            std::cout << "\n"
                      << "iter: " << iter << std::endl;
            wypiszWektor(S);
            std::cout << "error score: " << collectionErrorSum << ", current best: " << bestError << std::endl;
            
            int temp = S[r];
            S[r] = S[r2];
            S[r2] = temp;
        }
        std::cout << tabuCount << std::endl;
        iter++;
        i--;

    } while (i > 0 && tabuCount<tabu);
    return best;
}

int main(int argc, char **argv)
{

    std::vector<std::string> consoleInput(argv, argv + argc); // zbiór wejściowy

    std::vector<int> S;    // konwersja string input do int
    std::vector<int> temp; // vektor do tymczasowego zbierania podzbiorów
    int sumS = 0;          // suma całego zbioru S
    int m = 0;             // liczba możliwych 3-elementowych podzbiorów
    int T = 0;             // suma liczb w każdym podzbiorze

    for (int a = 1; a < consoleInput.size(); a++)
    {
        int b = std::stoi(consoleInput.at(a));
        S.push_back(b);
    }

    int x = S.size();
    for (int i = 0; i < x; i++)
    {
        sumS = sumS + S[i];
    };

    m = x / 3;
    T = sumS / m;

    std::cout << "Zbiór wejściowy: ";
    wypiszWektor(S);
    std::cout << "Długość Zbioru S: " << x << std::endl;
    std::cout << "Suma Zbioru S: " << sumS << std::endl;
    std::cout << "Ilość 3-elementowych podzbiorów: " << m << std::endl;
    std::cout << "Suma elementów w każdym z podzbiorów: " << T << std::endl;

    // try {
    // std::cout << "Możliwe podzbiory: " << std::endl;
    // for(int i = 0; i<m; i++) {
    //     std::cout << i+1 << ": ";
    //     if(temp.empty()) {
    //         temp.push_back(S.at(0));
    //
    //         if(temp.size()<3) {
    //
    //             for(int i=1; i<S.size(); i++) {
    //                 temp.push_back(S.at(i)); //2gi element
    //
    //                 for(int j=i+1; j<S.size(); j++) {
    //                     temp.push_back(S.at(j)); //3ci element
    //                     if(temp.at(0)+temp.at(1)+temp.at(2)!=T) {
    //                         temp.erase(std::remove(temp.begin(), temp.end(), temp.back()), temp.end());
    //                     } else {
    //                         wypiszWektor(temp);
    //                         while(!temp.empty()) {
    //                             S.erase(std::remove(S.begin(), S.end(), temp.back()), S.end());
    //                             temp.erase(std::remove(temp.begin(), temp.end(), temp.back()), temp.end());
    //                         }
    //                         break;
    //                     }
    //                 }
    //                 if(temp.size()==2) {
    //                     temp.erase(std::remove(temp.begin(), temp.end(), temp.back()), temp.end());
    //                 } else {
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    // }
    // } catch (std::out_of_range aor) {
    //     std::cout << "Nie da się utworzyć z podanych liczb 3-elementowych zbiorów o równej sumie wykorzystując cały zbiór.";
    // }
    int c = 0;
    int iterations = 0;
    int tabu = 0;
    std::cout << "Wybierz metodę obliczeń: \n 1.Pełen przegląd \n 2.Losowe Próbkowanie \n 3.Wspinaczkowy deterministyczny \n 4. Wspinaczkowy losowy \n 5. Tabu" << std::endl;
    std::cin >> c;
    std::cout << "Podaj liczbę iteracji: " << std::endl;
    std::cin >> iterations;

    switch (c)
    {
    case 1:
        bruteForce(S, T, iterations);
        break;
    case 2:
        losoweProbkowanie(S, T, iterations);
        break;
    case 3:
        wspinaczkaDeterm(S, T, iterations);
        break;
    case 4:
        wspinaczkaLosowa(S, T, iterations);
        break;
    case 5:
        std::cout << "Podaj rozmiar tabu: " << std::endl;
        std::cin >> tabu;
        TABU(S, T, iterations, tabu);
        break;
    default:
        std::cout << "Niepoprawny input." << std::endl;
    }

    return 0;
}