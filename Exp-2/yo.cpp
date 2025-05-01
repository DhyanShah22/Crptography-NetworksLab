#include <iostream>
#include <vector>
#include <bitset>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace chrono;

vector<int> P10{2,4,1,6,3,9,0,8,7,5}, P8{5,2,6,3,7,4,9,8};
vector<int> IP{1,5,2,0,3,7,4,6}, IP_INV{3,0,2,4,6,1,7,5};
vector<int> EP{3,0,1,2,1,2,3,0}, P4{1,3,2,0};
vector<vector<int>> S0{{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
vector<vector<int>> S1{{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};

void permute(const vector<int>& in, vector<int>& out, const vector<int>& table) {
    out.resize(table.size());
    for (int i = 0; i < table.size(); i++) out[i] = in[table[i]];
}

void shift(vector<int>& k, int s) {
    rotate(k.begin(), k.begin() + s, k.end());
}

void keys(const vector<int>& k, vector<int>& k1, vector<int>& k2) {
    vector<int> p, l, r, c(10);
    permute(k, p, P10);
    l.assign(p.begin(), p.begin() + 5);
    r.assign(p.begin() + 5, p.end());

    shift(l, 1); shift(r, 1);
    copy(l.begin(), l.end(), c.begin());
    copy(r.begin(), r.end(), c.begin() + 5);
    permute(c, k1, P8);

    shift(l, 2); shift(r, 2);
    copy(l.begin(), l.end(), c.begin());
    copy(r.begin(), r.end(), c.begin() + 5);
    permute(c, k2, P8);
}

void f(const vector<int>& r, const vector<int>& k, vector<int>& out) {
    vector<int> e, x(8), s(4);
    permute(r, e, EP);
    for (int i = 0; i < 8; i++) x[i] = e[i] ^ k[i];

    int row = x[0] * 2 + x[3], col = x[1] * 2 + x[2], v = S0[row][col];
    s[0] = (v >> 1) & 1; s[1] = v & 1;

    row = x[4] * 2 + x[7], col = x[5] * 2 + x[6], v = S1[row][col];
    s[2] = (v >> 1) & 1; s[3] = v & 1;

    permute(s, out, P4);
}

void sdes(const vector<int>& pt, const vector<int>& k1, const vector<int>& k2, vector<int>& ct, bool rev) {
    vector<int> ip, l, r, fk;
    permute(pt, ip, IP);
    l.assign(ip.begin(), ip.begin() + 4);
    r.assign(ip.begin() + 4, ip.end());

    f(r, rev ? k2 : k1, fk);
    for (int i = 0; i < 4; i++) l[i] ^= fk[i];
    swap(l, r);

    f(r, rev ? k1 : k2, fk);
    for (int i = 0; i < 4; i++) l[i] ^= fk[i];

    vector<int> merged;
    merged.insert(merged.end(), l.begin(), l.end());
    merged.insert(merged.end(), r.begin(), r.end());

    permute(merged, ct, IP_INV);
}

void brute(const vector<int>& ct, const vector<int>& pt) {
    vector<int> k(10), k1, k2, test;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 1024; i++) {
        bitset<10> b(i);
        for (int j = 0; j < 10; j++) k[j] = b[9 - j];
        keys(k, k1, k2);
        sdes(ct, k1, k2, test, true);
        if (test == pt) {
            auto end = high_resolution_clock::now();
            cout << "Key found: ";
            for (int bit : k) cout << bit;
            cout << "\nTime: " << duration_cast<milliseconds>(end - start).count() << " ms\n";
            return;
        }
    }
    cout << "Key not found\n";
}

int main() {
    vector<int> k(10), pt(8), ct, dec, k1, k2;
    string ks, ps;
    cout << "Enter 10-bit key: "; cin >> ks;
    cout << "Enter 8-bit plaintext: "; cin >> ps;

    for (int i = 0; i < 10; i++) k[i] = ks[i] - '0';
    for (int i = 0; i < 8; i++) pt[i] = ps[i] - '0';

    keys(k, k1, k2);
    sdes(pt, k1, k2, ct, false);

    cout << "Ciphertext: ";
    for (int b : ct) cout << b;
    cout << "\n";

    sdes(ct, k1, k2, dec, true);
    cout << "Decrypted: ";
    for (int b : dec) cout << b;
    cout << "\nBrute-forcing...\n";
    brute(ct, pt);
}
