#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int modExp(int base, int exp, int mod) {
    int result = 1;
    for (int i = 0; i < exp; ++i) {
        result = (result * base) % mod;
    }
    return result;
}

bool is_prime(int number) {
    if (number < 2) return false;
    for (int i = 2; i <= sqrt(number); ++i) {
        if (number % i == 0) return false;
    }
    return true;
}

pair<int, int> solve(int r1, int r2, int t1, int t2, int s1, int s2) {
    while (r2 != 0) {
        int q = r1 / r2;        
        int r = r1 % r2;         
        int t = t1 - q * t2;
        int s = s1 - q * s2;

        t1 = t2;
        t2 = t;
        s1 = s2;
        s2 = s;
        r1 = r2;
        r2 = r;
    }
    return {t1, r1};
}

int gcd(int a, int b) {
    return solve(a, b, 1, 0, 0, 1).second;
}

int mod_inverse(int e, int phi) {
    pair<int, int> result = solve(phi, e, 0, 1, 1, 0);
    int d = result.first;
    if (d < 0) {
        d += phi;
    }
    return d;
}

int main() {
    int p, q;

    cout << "Enter a prime number p: ";
    cin >> p;
    cout << "Enter a prime number q: ";
    cin >> q;

    if (!is_prime(p) || !is_prime(q)) {
        cerr << "Both p and q need to be prime numbers." << endl;
        return 1;
    }

    int n = p * q;
    int phi_n = (p - 1) * (q - 1);

    int M;
    cout << "Enter your message (as an integer less than " << n << "): ";
    cin >> M;
    if (M >= n) {
        cerr << "Message must be less than n (" << n << ")!" << endl;
        return 1;
    }

    int e;
    cout << "Enter a value for public key 'e' such that 1 < e < " << phi_n << " and gcd(e, phi_n) = 1: ";
    cin >> e;

    while (gcd(e, phi_n) != 1) {
        cout << "The value of e must satisfy gcd(e, " << phi_n << ") = 1. Enter another e: ";
        cin >> e;
    }

    int d = mod_inverse(e, phi_n);

    cout << "Public Key (e, n): (" << e << ", " << n << ")" << endl;
    cout << "Private Key (d, n): (" << d << ", " << n << ")" << endl;
    cout << "n: " << n << endl;
    cout << "Phi of n (phi(n)): " << phi_n << endl;

    // Encrypt: c = M^e mod n
    long long ciphertext = modExp(M, e, n);
    cout << "Ciphered message c: " << ciphertext << endl;

    // CCA2 ATTACK
    cout << "\n[Performing CCA2 Attack]\n";
    
    int X;
    cout << "Enter a nonzero random integer X (less than " << n << "): ";
    cin >> X;

    // Ensure X is valid
    if (X <= 1 || X >= n) {
        cerr << "Invalid X. It should be greater than 1 and less than " << n << "." << endl;
        return 1;
    }

    // Compute C' = (C * X^e) mod n
    long long modified_ciphertext = (ciphertext * modExp(X, e, n)) % n;
    cout << "Modified Ciphertext (C') for attack: " << modified_ciphertext << endl;

    // Decryption oracle (decrypt C')
    long long decrypted_M_prime = modExp(modified_ciphertext, d, n);
    cout << "Decryption Oracle Output (M'): " << decrypted_M_prime << endl;

    // Compute X^(-1) mod n
    int X_inv = mod_inverse(X, n);
    if (X_inv == 0) {
        cerr << "Error: Could not compute modular inverse of X!" << endl;
        return 1;
    }

    // Recover original message M = (M' * X^(-1)) mod n
    long long recovered_M = (decrypted_M_prime * X_inv) % n;
    cout << "Recovered Original Message M: " << recovered_M << endl;
    if(recovered_M == M){
        cout << "Match found!";
    }else{
        cout << "Match not found!";
    }

    return 0;
}