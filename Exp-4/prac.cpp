#include<iostream>

using namespace std;

int gcdVal;
int x, y;

void extendedEuclid(int a, int b){
    int r1 = a, r2 = b;
    int s1 = 1, s2 = 0;
    int t1 = 0, t2 = 1;

    int q,r,s,t;

    cout<<"Step-by-step calculations:\n";
    cout<<"q\tr1\tr2\tr\ts1\ts2\ts\tt1\tt2\tt\n";

    cout<<"-\t"<<r1<<"\t"<<r2<<"\t-\t"<<s1<<"\t"<<s2<<"\t-\t"<<t1<<"\t"<<t2<<"\t-\n";

    while(r2 > 0){
        q = r1/r2;

        r = r1 - q*r2;
        r1 = r2;
        r2 = r;
        
        s = s1 - q * s2;
        s1 = s2;
        s2 = s;

        t = t1 - q * t2;
        t1 = t2;
        t2 = t;

        cout<<"r\t"<<r1<<"\t"<<r2<<"\t"<<r<<"\t"<<s1<<"\t"<<s2<<"\t"<<s<<"\t"<<t1<<"\t"<<t2<<"\t"<<t<<endl;
    }

    gcdVal = r1;
    x = s1;
    y = t1;

    cout<<"\nGCD"<<"("<<a<<", "<<b<<") = "<<gcdVal<<endl;
    cout<<"coefficients"<<" "<<s1<<", "<<t1<<endl;

    if(gcdVal == 1){
        cout<<"The mod inv of "<< a << " mod " << b << " is: " << (s1 + b) % b << endl;
    }
    else{
        cout<<"Modular inverse does not exist because GCD("<<a<<", "<<b<<") != 1\n";
    }
}

void generateRSAKeys(long long& n, long long& e, long long& d){
    int p,q;

    cout<<"Enter two prime numbers p and q: ";
    cin>>p>>q;

    n = p*q;
    long long phi = (p-1)*(q-1);

    cout<<"Enter public key exponents e: "<<endl;
    cin >>e;
    
    extendedEuclid(e, phi);
    if(gcdVal != 1){
        cout<<"e must be coprime with phi(n). Please enter a valid e: ";
        cin>>e;
        extendedEuclid(e, phi);
    }

    d = (x % phi + phi) % phi;

    cout<<"Public key (n, e): ("<<n<<", "<<e<<")"<<endl;
    cout<<"Private key (n, d): ("<<n<<", "<<d<<")"<<endl;
}

long long modExpo(long long base, long long exp, long long mod){
    long long result = 1;
    while(exp > 0){
        if(exp % 2 ==1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}
long long encrypt(long long m, long long e, long long n){
    return modExpo(m, e, n);
}

long long decrypt(long long c, long long d, long long n){
    return modExpo(c, d, n);
}

int main(){
    long long n, e, d;
    generateRSAKeys(n, e, d);

    long long message;
    cout<<"Enter message to encrypt: ";
    cin>>message;

    long long encryptedMessage = encrypt(message, e, n);
    cout<<"Encrypted message: "<< encryptedMessage <<endl;

    long long decryptedMessage = decrypt(encryptedMessage, d, n);
    cout<<"Decrypted message: "<< decryptedMessage <<endl;

    return 0;
}