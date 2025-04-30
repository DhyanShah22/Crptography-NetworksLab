#include<iostream>

using namespace std;

void extendedEuclid(int a, int b){
    int r1 = a, r2 = b;
    int s1 = 1, s2 = 0;
    int t1 = 0, t2 = 1;

    int q, r, s, t;

    cout<<"Step-by-step calculations:\n";
    cout<<"q\tr1\tr2\tr\ts1\ts2\ts\tt1\tt2\tt\n";
    cout << "-\t" << r1 << "\t" << r2 << "\t-\t" << s1 << "\t" << s2 << "\t-\t" << t1 << "\t" << t2 << "\t-\n";

    while(r2>0){
        q = r1/r2;

        r = r1 - r2*q;
        r1=r2;
        r2=r;

        s = s1 - s2*q;
        s1 = s2;
        s2 = s;

        t = t1 - t2*q;
        t1 = t2;
        t2 = t;

        cout << q << "\t" << r1 << "\t" << r2 << "\t" << r << "\t" << s1 << "\t" << s2 << "\t" << s << "\t" << t1 << "\t" << t2 << "\t" << t << endl;
    }

    cout<<"GCD"<<"("<<a<<", "<<b<<") = "<<r1<<endl;
    cout<<"Coefficients "<<s1<<", "<<t1<<endl;

    if(r1==1){
        int modInverse = t1;
        int modInverse2 = a+ t2;
        cout<<"The modular inv of" << a << "%" << b << " is: " << modInverse << " or " << modInverse2;
    }
    else{
        cout<<"Modular inverse does not exist because GCD("<<a<<", "<<b<<") != 1\n";
    }
}
 int main(){
    int a,b;

    cout<<"Enter two numbers: "<<endl;
    cin>>a>>b;

    extendedEuclid(a,b);

    return 0;
 }