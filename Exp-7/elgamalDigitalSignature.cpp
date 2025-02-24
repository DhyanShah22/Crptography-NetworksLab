#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

bool is_prime(long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

long long mod_exp(long long base, long long exp, long long mod) {
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

long long gcd(long long a, long long b) {
    return (b == 0) ? a : gcd(b, a % b);
}

long long mod_inverse(long long a, long long m) {
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

vector<long long> find_prime_factors(long long n) {
    vector<long long> factors;
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }
    for (long long i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 2) factors.push_back(n);
    return factors;
}

bool is_primitive_root(long long g, long long p) {
    long long phi = p - 1;  
    vector<long long> factors = find_prime_factors(phi);

    for (long long factor : factors) {
        if (mod_exp(g, phi / factor, p) == 1) {
            return false;  
        }
    }
    return true;
}

int main() {
    long long p, g, x, hash_m;
    
    do {
        cout << "Enter a prime number (p): ";
        cin >> p;
        if (!is_prime(p)) {
            cout << "Error: p must be a prime number. Try again.\n";
        }
    } while (!is_prime(p)); 

    do {
        cout << "Enter a primitive root of p (g): ";
        cin >> g;
        if (!is_primitive_root(g, p)) {
            cout << "Error: g is not a valid primitive root of p. Try again.\n";
        }
    } while (!is_primitive_root(g, p));

    cout << "Enter private key (x): ";
    cin >> x;
    cout << "Enter message hash value: ";
    cin >> hash_m;
    
    long long y = mod_exp(g, x, p); 
    
    cout << "Public Key (p, g, y): (" << p << ", " << g << ", " << y << ")\n";
    cout << "Private Key (x): " << x << "\n";
    
    long long k;
    do {
        k = rand() % (p - 2) + 1;
    } while (gcd(k, p - 1) != 1); 
    
    long long r = mod_exp(g, k, p);
    long long k_inv = mod_inverse(k, p - 1);
    long long s = (k_inv * (hash_m - x * r)) % (p - 1);
    if (s < 0) s += (p - 1);
    
    cout << "Digital Signature (r, s): (" << r << ", " << s << ")\n";
    
    long long v1 = mod_exp(y, r, p) * mod_exp(r, s, p) % p;
    long long v2 = mod_exp(g, hash_m, p);
    
    if (v1 == v2)
        cout << "Signature is valid!" << endl;
    else
        cout << "Signature is invalid!" << endl;
    
    return 0;
}