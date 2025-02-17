#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>

using namespace std;

long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long modInverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
    if (m == 1) return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

vector<long long> findGenerators(long long p) {
    vector<long long> generators;
    set<long long> uniqueElements;
    
    for (long long g = 2; g < p; g++) {
        uniqueElements.clear();
        bool isGenerator = true;

        for (long long power = 1; power < p; power++) {
            long long val = modExp(g, power, p);
            if (uniqueElements.find(val) != uniqueElements.end()) {
                isGenerator = false;
                break;
            }
            uniqueElements.insert(val);
        }

        if (isGenerator) {
            generators.push_back(g);
        }
    }
    return generators;
}

int main() {
    srand(time(0));

    long long p;
    cout << "Enter a prime number (p): ";
    cin >> p;

    vector<long long> generators = findGenerators(p);
    cout << "Generators of " << p << " are: ";
    for (long long g : generators) {
        cout << g << " ";
    }
    cout << endl;

    long long g;
    cout << "Select a generator from the above list: ";
    cin >> g;

    long long x;
    cout << "Enter private key (1 ≤ x ≤ p-2): ";
    cin >> x;

    long long y = modExp(g, x, p);

    cout << "\nPublic Key (p, g, y): (" << p << ", " << g << ", " << y << ")\n";
    cout << "Private Key (x): " << x << "\n";

    long long m;
    cout << "\nEnter message (as an integer < p): ";
    cin >> m;

    long long k = rand() % (p - 2) + 1;
    long long c1 = modExp(g, k, p);
    long long c2 = (m * modExp(y, k, p)) % p;

    cout << "Ciphertext (c1, c2): (" << c1 << ", " << c2 << ")\n";

    long long s = modExp(c1, x, p);
    long long s_inv = modInverse(s, p);
    long long decrypted_m = (c2 * s_inv) % p;

    cout << "Decrypted Message: " << decrypted_m << "\n";

    return 0;
}
