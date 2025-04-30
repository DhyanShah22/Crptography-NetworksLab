#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

long long mod_exp(long long base, long long exp, long long mod) {
    long long res = 1;
    while (exp) {
        if (exp % 2) res = res * base % mod;
        base = base * base % mod;
        exp /= 2;
    }
    return res;
}

long long mod_inverse(long long a, long long m) {
    long long m0 = m, y = 0, x = 1;
    while (a > 1) {
        long long q = a / m, t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    return (x + m0) % m0;
}

long long gcd(long long a, long long b) {
    return b ? gcd(b, a % b) : a;
}

bool is_prime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i*i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

int main(){
    long long p, g, x, hashM;
    cout<<"Enter a prime number p: "<<endl;
    cin>>p;
    if(!is_prime(p)){
        cerr<<"Not a prime, try again!"<<endl;
        return 0;
    } 
    cout<<"Enter the primitive root (g): "<<endl;
    cin>>g;

    cout<<"Enter x, private key: ";
    cin>>x;

    cout<<"Enter hash message: "<<endl;
    cin>>hashM;

    long long y = mod_exp(g, x, p);

    cout<<"Public Key: "<< "(" << p << "," << g << "," << y << ")"<<endl;
    long long k;
    do {k = rand() % (p-2) + 1;} while(gcd(k, p-1) != 1);
    long long r = mod_exp(g, k, p);
    long long s = mod_inverse(k, p-1) * (hashM - x*r + (p+1)) % p-1;

    cout<<"Digital Signature: " << "(" << r << "," << s << ")"<<endl;

    long long v1 = (mod_exp(y, r, p) * mod_exp(r, s, p)) % p;
    long long v2 = mod_exp(g, hashM, p);

    if(v1 == v2){
        cout<<"Signature is valid!"<<endl;
    }
    else{
        cout<<"Signature is invalid!"<<endl;
    }

    return 0;
}