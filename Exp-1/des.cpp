#include <iostream>
#include <bitset>
#include <string>

using namespace std;

int IP[] = {2, 6, 3, 1, 4, 8, 5, 7};
int FP[] = {4, 1, 3, 5, 7, 2, 8, 6};
int E[] = {4, 1, 2, 3, 2, 3, 4, 1};
int P[] = {2, 4, 3, 1};

int S_BOX[2][4][4] = {
    {
        {1, 0, 3, 2},
        {3, 2, 1, 0},
        {0, 2, 1, 3},
        {3, 1, 3, 2}
    },
    {
        {0, 1, 2, 3},
        {2, 0, 1, 3},
        {3, 0, 1, 0},
        {2, 1, 0, 3}
    }
};

string permute(string bits, int* table, int size) {
    string result = "";
    for (int i = 0; i < size; i++) {
        result += bits[table[i] - 1];
    }
    return result;
}

string initial_permutation(string bits) {
    return permute(bits, IP, 8);
}

string final_permutation(string bits) {
    return permute(bits, FP, 8);
}

string sbox_lookup(string input_bits, int sbox_index) {
    int row = (input_bits[0] - '0') * 2 + (input_bits[3] - '0');
    int col = (input_bits[1] - '0') * 2 + (input_bits[2] - '0');
    int sbox_value = S_BOX[sbox_index][row][col];
    return bitset<2>(sbox_value).to_string();
}

string xor_bits(string bits1, string bits2) {
    string result = "";
    for (size_t i = 0; i < bits1.size(); i++) {
        result += (bits1[i] == bits2[i]) ? '0' : '1';
    }
    return result;
}

string feistel_function(string right, string key) {
    string expanded = permute(right, E, 8);
    string xored = xor_bits(expanded, key);
    string sbox_output = "";
    sbox_output += sbox_lookup(xored.substr(0, 4), 0);
    sbox_output += sbox_lookup(xored.substr(4, 4), 1);
    return permute(sbox_output, P, 4);
}

string des_encrypt(string plain_text, string key1, string key2) {
    string permuted = initial_permutation(plain_text);
    string left = permuted.substr(0, 4);
    string right = permuted.substr(4, 4);

    for (string key : {key1, key2}) {
        string temp_right = right;
        right = xor_bits(left, feistel_function(right, key));
        left = temp_right;
    }

    string pre_output = left + right;
    return final_permutation(pre_output);
}

string des_decrypt(string cipher_text, string key1, string key2) {
    string permuted = initial_permutation(cipher_text);
    string left = permuted.substr(0, 4);
    string right = permuted.substr(4, 4);

    for (string key : {key2, key1}) {
        string temp_left = left;
        left = xor_bits(right, feistel_function(left, key));
        right = temp_left;
    }

    string pre_output = left + right;
    return final_permutation(pre_output);
}

int main() {
    string key1 = "10101010";
    string key2 = "01010101";
    string text;
    int option;

    cout << "Enter 1 for Encryption, 0 for Decryption: ";
    cin >> option;
    cout << "Enter 8-bit text: ";
    cin >> text;

    if (option == 1) {
        string encrypted = des_encrypt(text, key1, key2);
        cout << "Encrypted Text: " << encrypted << endl;
    } else if (option == 0) {
        string decrypted = des_decrypt(text, key1, key2);
        cout << "Decrypted Text: " << decrypted << endl;
    } else {
        cout << "Invalid option!" << endl;
    }

    return 0;
}
