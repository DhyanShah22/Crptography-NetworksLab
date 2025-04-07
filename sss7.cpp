#include <iostream>
#include <vector>

using namespace std;

int modInverse(int a, int mod) {
    int result = 1;
    int exp = mod - 2;
    while (exp) {
        if (exp % 2) result = (result * a) % mod;
        a = (a * a) % mod;
        exp /= 2;
    }
    return result;
}

int evaluatePolynomial(vector<int>& coeffs, int x, int mod) {
    int result = 0, term = 1;
    for (int coef : coeffs) {
        result = (result + coef * term) % mod;
        term = (term * x) % mod;
    }
    return result;
}

int reconstructSecret(vector<pair<int, int>>& shares, int mod) {
    int secret = 0;
    for (int i = 0; i < shares.size(); i++) {
        int xi = shares[i].first, yi = shares[i].second;
        int li = 1;
        for (int j = 0; j < shares.size(); j++) {
            if (i != j) {
                int xj = shares[j].first;
                li = (li * (mod - xj)) % mod;
                li = (li * modInverse(xi - xj + mod, mod)) % mod;
            }
        }
        secret = (secret + (yi * li) % mod) % mod;
    }
    return secret;
}

int main() {
    int mod = 13;
    vector<int> coeffs(4);
    cout << "Enter 4 coefficients (first is the secret): ";
    for (int i = 0; i < 4; i++) {
        cin >> coeffs[i];
    }

    cout << "\nThreshold (k): 4";
    cout << "\nTotal Shares (n): 6";
    cout << "\nPrime Modulo: " << mod << "\n";
    cout << "Coefficients: ";
    for (int coef : coeffs) {
        cout << coef << " ";
    }
    cout << "\n";

    vector<pair<int, int>> shares;

    cout << "\nGenerated Shares:\n";
    for (int x = 1; x <= 6; x++) {
        int y = evaluatePolynomial(coeffs, x, mod);
        shares.push_back({x, y});
        cout << "Share (" << x << ", " << y << ")\n";
    }

    vector<pair<int, int>> selectedShares = {shares[0], shares[1], shares[2], shares[3]};

    cout << "\nSelected Shares for Reconstruction:\n";
    for (const auto& share : selectedShares) {
        cout << "(" << share.first << ", " << share.second << ")\n";
    }

    int recoveredSecret = reconstructSecret(selectedShares, mod);
    cout << "\nReconstructed Secret: " << recoveredSecret << endl;

    return 0;
}