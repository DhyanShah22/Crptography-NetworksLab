#include <iostream>
#include <cmath>
using namespace std;

int gcdVal, x, y;

void extendedEuclid(int a, int b) {
    int r1 = a, r2 = b;
    int s1 = 1, s2 = 0;
    int t1 = 0, t2 = 1;

    int q, r, s, t;

    cout << "\nStep-by-step Extended Euclidean Algorithm:\n";
    cout << "q\tr1\tr2\tr\ts1\ts2\ts\tt1\tt2\tt\n";
    cout << "-\t" << r1 << "\t" << r2 << "\t-\t" << s1 << "\t" << s2 << "\t-\t" << t1 << "\t" << t2 << "\t-\n";

    while (r2 > 0) {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;

        s = s1 - q * s2;
        s1 = s2;
        s2 = s;

        t = t1 - q * t2;
        t1 = t2;
        t2 = t;

        cout << q << "\t" << r1 << "\t" << r2 << "\t" << r << "\t" << s1 << "\t" << s2 << "\t" << s << "\t" << t1 << "\t" << t2 << "\t" << t << endl;
    }

    gcdVal = r1;
    x = s1;
    y = t1;

    cout << "\nGCD(" << a << ", " << b << ") = " << gcdVal << endl;
    cout << "Coefficients: x = " << s1 << ", y = " << t1 << endl;
    cout << "Verification: " << a << " * " << s1 << " + " << b << " * " << t1 << " = " << gcdVal << endl;

    if (gcdVal == 1) {
        cout << "Modular inverse of " << a << " modulo " << b << " is: " << (t1 + b) % b << endl;
    } else {
        cout << "Modular inverse does not exist because GCD(" << a << ", " << b << ") != 1\n";
    }
}

long long modExpo(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

void generateRSAKeys(long long &n, long long &e, long long &d) {
    long long p, q;

    cout << "Enter two prime numbers (p and q): ";
    cin >> p >> q;

    n = p * q;
    long long phi = (p - 1) * (q - 1);

    cout << "Enter public key exponent e (should be coprime with " << phi << "): ";
    cin >> e;

    extendedEuclid(e, phi);
    while (gcdVal != 1) {
        cout << "Invalid e. Enter another value for e: ";
        cin >> e;
        extendedEuclid(e, phi);
    }

    d = (x % phi + phi) % phi;
    cout << "\nPublic Key: (n = " << n << ", e = " << e << ")\n";
    cout << "Private Key: (n = " << n << ", d = " << d << ")\n";
}

long long encrypt(long long message, long long e, long long n) {
    return modExpo(message, e, n);
}

long long decrypt(long long cipher, long long d, long long n) {
    return modExpo(cipher, d, n);
}

int main() {
    long long n, e, d;
    generateRSAKeys(n, e, d);

    long long message;
    cout << "\nEnter a number to encrypt (message): ";
    cin >> message;

    long long encryptedMessage = encrypt(message, e, n);
    cout << "Encrypted Message: " << encryptedMessage << endl;

    long long decryptedMessage = decrypt(encryptedMessage, d, n);
    cout << "Decrypted Message: " << decryptedMessage << endl;

    return 0;
}