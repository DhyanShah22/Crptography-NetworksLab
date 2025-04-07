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

vector<int> BBS(int seed, int p, int q, int numBits) {
    int n = p * q;
    vector<int> bits;
    long long x = (seed * seed) % n;

    for (int i = 0; i < numBits; i++) {
        x = modExp(x, 2, n);
        bits.push_back(x % 2);
    }
    return bits;
}

vector<int> BlumMicali(int seed, int g, int p, int numBits) {
    vector<int> bits;
    long long x = seed;

    for (int i = 0; i < numBits; i++) {
        x = modExp(g, x, p);
        bits.push_back((x > p / 2) ? 1 : 0);
    }
    return bits;
}

void printDistribution(const vector<int>& numbers, const string& title) {
    map<int, int> freq;
    for (int num : numbers) freq[num]++;
    
    cout << "\n" << title << " Distribution:\n";
    for (const auto& pair : freq) {
        cout << pair.first << " -> " << pair.second << "\n";
    }
}

int main() {
    int choice;
    cout << "Choose PRNG Method:\n1. Blum Blum Shub (BBS)\n2. Blum-Micali\nEnter choice: ";
    cin >> choice;

    int numBits;
    cout << "Enter number of random bits to generate: ";
    cin >> numBits;

    if (choice == 1) {
        int p, q, seed;
        do {
            cout << "Enter two prime numbers (p and q): ";
            cin >> p >> q;
            if (!isPrime(p) || !isPrime(q)) {
                cout << "Error: Both numbers must be prime!\n";
            }
        } while (!isPrime(p) || !isPrime(q));

        int n = p * q;

        do {
            cout << "Enter seed (must be coprime to " << n << "): ";
            cin >> seed;
            if (gcd(seed, n) != 1) {
                cout << "Error: Seed must be coprime to " << n << "!\n";
            }
        } while (gcd(seed, n) != 1);

        vector<int> randomBits = BBS(seed, p, q, numBits);
        cout << "BBS Random Bits: ";
        for (int bit : randomBits) cout << bit;
        cout << endl;
        
        printDistribution(randomBits, "BBS Random Bits");
    } 
    else if (choice == 2) {
        int p, g, seed;

        do {
            cout << "Enter a prime number (p): ";
            cin >> p;
            if (!isPrime(p)) {
                cout << "Error: p must be prime!\n";
            }
        } while (!isPrime(p));

        cout << "Enter a generator (g): ";
        cin >> g;
        cout << "Enter seed: ";
        cin >> seed;

        vector<int> randomBits = BlumMicali(seed, g, p, numBits);
        cout << "Blum-Micali Random Bits: ";
        for (int bit : randomBits) cout << bit;
        cout << endl;
        
        printDistribution(randomBits, "Blum-Micali Random Bits");
    } 
    else {
        cout << "Invalid choice! Exiting..." << endl;
    }

    return 0;
}
