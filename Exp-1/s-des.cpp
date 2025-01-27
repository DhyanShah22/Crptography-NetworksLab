#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> P10 = {2, 4, 1, 6, 3, 9, 0, 8, 7, 5};
vector<int> P8 = {5, 2, 6, 3, 7, 4, 9, 8};
vector<int> IP = {1, 5, 2, 0, 3, 7, 4, 6};
vector<int> IP_INV = {3, 0, 2, 4, 6, 1, 7, 5};
vector<int> EP = {3, 0, 1, 2, 1, 2, 3, 0};
vector<int> P4 = {1, 3, 2, 0};

vector<vector<int>> S0 = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};

vector<vector<int>> S1 = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};

void permute(const vector<int>& input, vector<int>& output, const vector<int>& table) {
    for (size_t i = 0; i < table.size(); i++) {
        output[i] = input[table[i]];
    }
}

void left_shift(vector<int>& key, int shifts) {
    int n = key.size();
    vector<int> temp(shifts);
    for (int i = 0; i < shifts; i++) {
        temp[i] = key[i];
    }
    for (int i = 0; i < n - shifts; i++) {
        key[i] = key[i + shifts];
    }
    for (int i = 0; i < shifts; i++) {
        key[n - shifts + i] = temp[i];
    }
}

void generate_keys(const vector<int>& key, vector<int>& subkey1, vector<int>& subkey2) {
    vector<int> permuted(10), left(5), right(5), combined(10);

    permute(key, permuted, P10);

    copy(permuted.begin(), permuted.begin() + 5, left.begin());
    copy(permuted.begin() + 5, permuted.end(), right.begin());

    left_shift(left, 1);
    left_shift(right, 1);

    copy(left.begin(), left.end(), combined.begin());
    copy(right.begin(), right.end(), combined.begin() + 5);
    permute(combined, subkey1, P8);

    left_shift(left, 2);
    left_shift(right, 2);

    copy(left.begin(), left.end(), combined.begin());
    copy(right.begin(), right.end(), combined.begin() + 5);
    permute(combined, subkey2, P8);
}

void f_function(const vector<int>& right, const vector<int>& subkey, vector<int>& output) {
    vector<int> expanded(8), xor_result(8), sbox_output(4);

    permute(right, expanded, EP);

    for (size_t i = 0; i < expanded.size(); i++) {
        xor_result[i] = expanded[i] ^ subkey[i];
    }

    int row = xor_result[0] * 2 + xor_result[3];
    int col = xor_result[1] * 2 + xor_result[2];
    int s0_value = S0[row][col];
    sbox_output[0] = (s0_value >> 1) & 1;
    sbox_output[1] = s0_value & 1;

    row = xor_result[4] * 2 + xor_result[7];
    col = xor_result[5] * 2 + xor_result[6];
    int s1_value = S1[row][col];
    sbox_output[2] = (s1_value >> 1) & 1;
    sbox_output[3] = s1_value & 1;

    permute(sbox_output, output, P4);
}

void s_des_rounds(const vector<int>& plaintext, const vector<int>& subkey1, const vector<int>& subkey2, vector<int>& ciphertext, bool reverse_keys) {
    vector<int> ip(8), left(4), right(4), fk_output(4), temp(4);

    permute(plaintext, ip, IP);

    copy(ip.begin(), ip.begin() + 4, left.begin());
    copy(ip.begin() + 4, ip.end(), right.begin());

    f_function(right, reverse_keys ? subkey2 : subkey1, fk_output);
    for (size_t i = 0; i < left.size(); i++) {
        temp[i] = left[i] ^ fk_output[i];
    }
    left = right;
    right = temp;

    f_function(right, reverse_keys ? subkey1 : subkey2, fk_output);
    for (size_t i = 0; i < left.size(); i++) {
        left[i] ^= fk_output[i];
    }

    copy(left.begin(), left.end(), ip.begin());
    copy(right.begin(), right.end(), ip.begin() + 4);
    permute(ip, ciphertext, IP_INV);
}

int main() {
    vector<int> key(10), plaintext(8), ciphertext(8), decrypted(8);
    vector<int> subkey1(8), subkey2(8);
    string key_input, plaintext_input;

    cout << "Enter 10-bit key: ";
    cin >> key_input;

    for (size_t i = 0; i < key.size(); i++) {
        key[i] = key_input[i] - '0';
    }

    cout << "Enter 8-bit plaintext: ";
    cin >> plaintext_input;

    for (size_t i = 0; i < plaintext.size(); i++) {
        plaintext[i] = plaintext_input[i] - '0';
    }

    generate_keys(key, subkey1, subkey2);

    s_des_rounds(plaintext, subkey1, subkey2, ciphertext, false);
    cout << "Ciphertext: ";
    for (int bit : ciphertext) {
        cout << bit;
    }
    cout << "\n";

    s_des_rounds(ciphertext, subkey1, subkey2, decrypted, true);
    cout << "Decrypted plaintext: ";
    for (int bit : decrypted) {
        cout << bit;
    }
    cout<<endl;
    cout<<"This is the key for this decryption"<<endl;
    cout << "\n";

    return 0;
}