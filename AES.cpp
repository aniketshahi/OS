#include <iostream>
#include <vector>

using namespace std;

// The AES key schedule.
vector<unsigned char> key_schedule(const vector<unsigned char>& key) {
  vector<unsigned char> expanded_key(16 * 14);

  for (int i = 0; i < 16; i++) {
    expanded_key[i] = key[i];
  }

  for (int r = 1; r < 14; r++) {
    for (int i = 0; i < 4; i++) {
      expanded_key[16 * r + i] = expanded_key[16 * (r - 1) + i] ^ sub_bytes(expanded_key[16 * (r - 1) + i + 4]);
    }

    for (int i = 0; i < 4; i++) {
      expanded_key[16 * r + i + 4] = expanded_key[16 * r + i] ^ shift_rows(expanded_key[16 * r + i]);
    }

    expanded_key[16 * r + 12] = expanded_key[16 * r + 12] ^ rcon[r - 1];
  }

  return expanded_key;
}

// The AES encryption function.
vector<unsigned char> encrypt(const vector<unsigned char>& plaintext, const vector<unsigned char>& key) {
  vector<unsigned char> expanded_key = key_schedule(key);

  for (int round = 0; round < 10; round++) {
    plaintext = add_round_key(plaintext, expanded_key, round);
    plaintext = sub_bytes(plaintext);
    plaintext = shift_rows(plaintext);
    plaintext = mix_columns(plaintext);
  }

  plaintext = add_round_key(plaintext, expanded_key, 10);

  return plaintext;
}

// The AES decryption function.
vector<unsigned char> decrypt(const vector<unsigned char>& ciphertext, const vector<unsigned char>& key) {
  vector<unsigned char> expanded_key = key_schedule(key);

  for (int round = 10; round > 0; round--) {
    ciphertext = add_round_key(ciphertext, expanded_key, round);
    ciphertext = inv_shift_rows(ciphertext);
    ciphertext = inv_sub_bytes(ciphertext);
    ciphertext = add_round_key(ciphertext, expanded_key, round - 1);
  }

  ciphertext = inv_shift_rows(ciphertext);
  ciphertext = inv_sub_bytes(ciphertext);
  ciphertext = add_round_key(ciphertext, expanded_key, 0);

  return ciphertext;
}

int main() {
  // Get the key from the user.
  string key;
  cout << "Enter the key: ";
  getline(cin, key);

  // Convert the key to a vector of unsigned char.
  vector<unsigned char> key_vector(key.begin(), key.end());

  // Get the plaintext from the user.
  string plaintext;
  cout << "Enter the plaintext: ";
  getline(cin, plaintext);

  // Convert the plaintext to a vector of unsigned char.
  vector<unsigned char> plaintext_vector(plaintext.begin(), plaintext.end());

  // Encrypt the plaintext.
  vector<unsigned char> ciphertext = encrypt(plaintext_vector, key_vector);

  // Print the ciphertext.
  for (unsigned char c : ciphertext) {
    cout << c;
  }

  cout << endl;

  // Decrypt the ciphertext.
  vector<unsigned char> decrypted_plaintext = decrypt(ciphertext, key_vector);

  // Print the decrypted plaintext.
  for (unsigned char c : decrypted_plaintext) {
    cout << c;
  }

  cout << endl;

  return 0;
}
