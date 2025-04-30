#include <iostream>
#include <vector>
#include <map>

using namespace std;

long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

vector<int> BBS(int seed, int p, int q, int numBits){
    vector<int>bits;
    int n = p * q;
    long long x = (seed * seed) % n;

    for(int i = 0; i < numBits; i++){
        x = modExp(x, 2, n);
        bits.push_back(x  % 2);
    }
    return bits;
}

vector<int> BM(int seed, int p, int g, int numBits){
    vector<int>bits;
    long long x = seed;

    for(int i = 0; i < numBits; i++){
        x = modExp(g,x,p);
        bits.push_back((x > p/2) ? 1 :  0);
    }
    return bits;
}

void patternDistribution(const vector<int>& numbers, const string& title){
    map<int, int>freq;
    for(int num : numbers){
        freq[num]++;
    }

    cout<< title << " Distribution: "<<endl;

    for(const auto& pair :  freq){
        cout<<pair.first << " -> " << pair.second << "\n";
    }
}

int main(){
    int choice;
    cout<<"Choose 1 for BBS and 2 for BM: ";
    cin>>choice;

    int numBits;
    cout<<"Enter no. of random bits to generate: ";
    cin>>numBits;

    if(choice == 1){
        int p, q;
        cout<<"Enter 2 prime numbers: ";
        cin>>p>>q;

        int seed;
        cout<<"Enter a seed such that it is co-prime to n: ";
        cin>>seed;

        vector<int> randomBits = BBS(seed, p, q, numBits);
        for(int bit : randomBits){
            cout<< bit;
        }
        cout<<endl;

        patternDistribution(randomBits, "Blum Blum Shub");
    }

    if(choice == 2){
        int p,g,seed;

        cout<<"Enter a prime number p: ";
        cin>>p;

        cout<<"Enter a generator g: ";
        cin>>g;

        cout<<"Enter a seed: ";
        cin>>seed;

        vector<int> randomBits = BM(seed, p, g, numBits);
        for(int bit : randomBits){
            cout<<bit;
        }
        cout<<endl;

        patternDistribution(randomBits, "Blum Micali");
    }

    return 0;
}