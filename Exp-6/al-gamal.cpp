#include <iostream>

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

int main() {
    srand(time(0));

    long long p, g;
    cout << "Enter a prime number (p): ";
    cin >> p;

    cout << "Enter a generator (g) for the group modulo p: ";
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
    long long s_inv = modExp(s, p - 2, p);
    long long decrypted_m = (c2 * s_inv) % p;

    cout << "Decrypted Message: " << decrypted_m << "\n";

    return 0;
}
