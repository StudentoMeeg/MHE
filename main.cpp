#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

void wypiszWektor(std::vector<int> v) {
    for(int y=0; y<v.size(); y++) {
    std::cout << v.at(y) << " ";
    }
    std::cout << std:: endl;
}

int main(int argc, char **argv) {

std::vector<std::string> consoleInput(argv, argv + argc);               //zbiór wejściowy
//0, 1, 2, 5, 10, 12, 14, 20, 20, 24, 45, 47
std::vector<int> S;                                                     //konwersja string input do int
std::vector<int> temp;                                                  //vektor do tymczasowego zbierania podzbiorów
int sumS = 0;                                                           //suma całego zbioru S
int m = 0;                                                              //liczba możliwych 3-elementowych podzbiorów
int T = 0;                                                              //suma liczb w każdym podzbiorze

for(int a = 1; a<consoleInput.size(); a++) {
    int b = std::stoi(consoleInput.at(a));
    S.push_back(b);
}

int x = S.size();
for (int i=0; i<x; i++) {
    sumS = sumS + S[i];
};

m = x/3;
T = sumS/m;

std::cout << "Zbiór wejściowy: "; wypiszWektor(S);
std::cout << "Długość Zbioru S: " << x << std::endl;
std::cout << "Suma Zbioru S: " << sumS << std::endl;
std::cout << "Ilość 3-elementowych podzbiorów: " << m << std::endl;
std::cout << "Suma elementów w każdym z podzbiorów: " << T << std::endl;



try {
std::cout << "Możliwe podzbiory: " << std::endl;
for(int i = 0; i<m; i++) {
    std::cout << i+1 << ": ";
    if(temp.empty()) {
        temp.push_back(S.at(0));

        if(temp.size()<3) {

            for(int i=1; i<S.size(); i++) {
                temp.push_back(S.at(i)); //2gi element

                for(int j=i+1; j<S.size(); j++) {
                    temp.push_back(S.at(j)); //3ci element
                    if(temp.at(0)+temp.at(1)+temp.at(2)!=T) {
                        temp.erase(std::remove(temp.begin(), temp.end(), temp.back()), temp.end());
                    } else {
                        wypiszWektor(temp);
                        while(!temp.empty()) {
                            S.erase(std::remove(S.begin(), S.end(), temp.back()), S.end());
                            temp.erase(std::remove(temp.begin(), temp.end(), temp.back()), temp.end());
                        }
                        break;
                    }
                }
                if(temp.size()==2) {
                    temp.erase(std::remove(temp.begin(), temp.end(), temp.back()), temp.end());
                } else {
                    break;
                }
            }
        }
    }
}
} catch (std::out_of_range aor) {
    std::cout << "Nie da się utworzyć z podanych liczb 3-elementowych zbiorów o równej sumie wykorzystując cały zbiór.";
}
    return 0;
}