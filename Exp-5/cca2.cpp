#include <iostream>
#include <cmath>
using namespace std;

long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

bool is_prime(int number) {
    if (number < 2) return false;
    for (int i = 2; i <= sqrt(number); ++i)
        if (number % i == 0) return false;
    return true;
}

int gcd(int a, int b) {
    while (b != 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    long long p, q;
    cout << "Enter two prime numbers (p and q): ";
    cin >> p >> q;

    if (!is_prime(p) || !is_prime(q)) {
        cerr << "Both numbers must be prime.\n";
        return 1;
    }

    long long n = p * q;
    long long phi_n = (p - 1) * (q - 1);

    long long M;
    cout << "Enter message (integer < " << n << "): ";
    cin >> M;

    if (M >= n) {
        cerr << "Message must be smaller than n!\n";
        return 1;
    }

    long long e;
    cout << "Enter public exponent e (1 < e < " << phi_n << ", gcd(e, " << phi_n << ") = 1): ";
    cin >> e;

    while (gcd(e, phi_n) != 1) {
        cout << "Invalid e. Enter again: ";
        cin >> e;
    }

    long long d = modExp(e, phi_n - 2, phi_n); 

    cout << "\nPublic Key (e, n): (" << e << ", " << n << ")\n";
    cout << "Private Key (d, n): (" << d << ", " << n << ")\n";

    long long ciphertext = modExp(M, e, n);
    cout << "Ciphertext: " << ciphertext << "\n";

    cout << "\n[Simulating CCA2 Attack]\n";

    long long X;
    cout << "Enter a random nonzero integer X (1 < X < " << n << "): ";
    cin >> X;

    if (X <= 1 || X >= n) {
        cerr << "Invalid X!\n";
        return 1;
    }

    long long modified_cipher = (ciphertext * modExp(X, e, n)) % n;
    long long decrypted_M_prime = modExp(modified_cipher, d, n);
    long long recovered_M = (decrypted_M_prime * modExp(X, n-2, n)) % n;

    cout << "Recovered Message: " << recovered_M << "\n";

    if (recovered_M == M)
        cout << "Success: Original message recovered!\n";
    else
        cout << "Failure: Messages do not match.\n";

    return 0;
}
