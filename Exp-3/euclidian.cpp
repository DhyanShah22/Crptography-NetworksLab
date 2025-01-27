#include <iostream>
using namespace std;

void extendedEuclid(int a, int b) {
    int r1 = a, r2 = b;
    int s1 = 1, s2 = 0;
    int t1 = 0, t2 = 1;

    int q, r, s, t;

    cout << "Step-by-step calculations:\n";
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

    cout << "\nGCD(" << a << ", " << b << ") = " << r1 << endl;
    cout << "Coefficients: s = " << s1 << ", t = " << t1 << endl;
    cout << "Verification: " << a << " * " << s1 << " + " << b << " * " << t1 << " = " << r1 << endl;
    
     // modular inverse 
    if (r1 == 1) {
        int modInverse = t1; 
        int modInverse2= a+t1;
        printf("Modular inverse of %d modulo %d is: %d or %d", a, b, modInverse, modInverse2);
    } else {
        printf("Modular inverse does not exist because GCD(%d, %d) != 1\n", a, b);
    }

}

int main() {
    int a, b;

    cout << "Enter two integers: ";
    cin >> a >> b;

    extendedEuclid(a, b);


    return 0;
}