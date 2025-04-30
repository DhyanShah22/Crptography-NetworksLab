#include<iostream>
#include<cmath>

using namespace std;

long long modExp(long long base, long long exp, long long mod){
    long long result = 1;
    while(exp > 0){
        if(exp % 2 ==1){
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

bool isPrime(int num){
    if(num < 2) return false;
    for(int i = 2; i <= sqrt(num); i++){
        if(num % i == 0){
            return false;
        }
    }
    return true;
}

int gcd(int a, int b){
    while(b != 0){
        a %= b;
        swap(a,b);
    }
    return a;
}

int main(){
    long long p, q;
    cout<<"Enter two primes numbers p and q: ";
    cin>>p>>q;

    if(!isPrime(p) || !isPrime(q)){
        cerr<<"Both numbers must be prime.\n";
        return 1;
    }

    long long n = p*q;
    long long phi = (p-1)*(q-1);

    long long e;
    cout<<"Enter e such that 1 < e < "<<phi<<", gcd(e, "<<phi<<") = 1: ";
    cin>>e;

    while (gcd(e, phi) != 1) {
        cout << "Invalid e. Enter again: ";
        cin >> e;
    }

    long long d = modInverse(e, phi);

    long long M;
    cout<<"Enter message (integer < "<<n<<"): ";
    cin>>M;

    cout<<"Public Key (n, e): ("<<n<<", "<<e<<")"<<endl;
    cout<<"Private Key (n, d): ("<<n<<", "<<d<<")"<<endl;

    long long ciphertext = modExp(M, e, n);
    cout<<"Ciphertext: "<<ciphertext<<endl;

    long long X;
    cout<<"Enter a random X for CCA2: ";
    cin>>X;

    if (gcd(X, n) != 1) {
    cerr << "X and n are not coprime, inverse does not exist.\n";
    return 1;
    }
    long long X_inv = modInverse(X, n);

    long long modifiedCipher = (ciphertext * modExp(X, e, n)) % n;
    long long d_modified = modExp(modifiedCipher, d, n);
    long long recovered = (d_modified * X_inv) % n;

    if(recovered == M){
        cout<<"CCA2 attack successful! Recovered message: "<<recovered<<endl;
    }
    else{
        cout<<"CCA2 attack failed.\n";
    }

    return 0;
}