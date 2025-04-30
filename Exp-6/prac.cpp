#include<iostream>

using namespace std;

long long modExp(long long base, long long exp, long long mod){
    long long result = 1;
    while(exp > 0){
        if(exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// long long modInverse(long long a, long long m) {
//     long long m0 = m, t, q;
//     long long x0 = 0, x1 = 1;
//     if (m == 1) return 0;

//     while (a > 1) {
//         q = a / m;
//         t = m;
//         m = a % m, a = t;
//         t = x0;
//         x0 = x1 - q * x0;
//         x1 = t;
//     }
//     if (x1 < 0) x1 += m0;
//     return x1;
// }

long long modInverse(long long a, long long m){
    int r1 = a, r2 = m;
    int s1 = 1, s2 = 0;
    int t1 = 0, t2 = 1;

    int q, r, s, t;

    while(r2 > 0){
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
    }

    if(r1 != 1)
        return -1; 
    else
        return (s1 + m) % m; 
}

int main(){
    long long p,g;

    cout<<"Enter a prime number p: ";
    cin>>p;

    cout<<"Enter the generator (g): ";
    cin>>g;

    int x;
    cout<<"Enter the public key x: ";
    cin>>x;

    long long y = modExp(g, x, p);

    cout<<endl;
    cout<<"Public Key: "<< "("<<p<<", "<<g<<", "<<y<<")"<<endl;
    cout<<"Private Key: "<<x<<endl; 

    long long m;
    cout <<"Enter the message to encrypt: ";
    cin>> m;

    long long k = rand() % (p- 2) + 1;
    long long c1 = modExp(g, k, p);
    long long c2 = m * modExp(y, k, p) % p;

    cout<<"Cipertext pairs: "<< "(" <<c1<<", "<<c2<< ")"<<endl;

    long long s = modExp(c1, x, p);
    long long s_inv = modInverse(s, p);
    long long m_decrypted = (c2 * s_inv) % p;

    cout<<"Decrypted message: "<<m_decrypted<<endl;

    return 0;
}