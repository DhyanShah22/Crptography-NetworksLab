#include <iostream>
#include <ctime>

using namespace std;

#define A 1664525
#define C 1013904223
#define M 4294967296

unsigned long long seed;

void initSeed(unsigned long long s){
    seed = s;
}

unsigned int getRandom(){
    seed = (A * seed + C) % M;
    return static_cast<unsigned int>(seed);
}

unsigned int getRandomInRange(unsigned int min, unsigned int max){
    return min + (getRandom() % (max - min + 1));
}

int main(){
    initSeed(static_cast<unsigned long long>(time(nullptr)));
    for(int i = 0; i < 5; ++i){
        cout << getRandomInRange(1, 100) << endl;
    }
    return 0;
}