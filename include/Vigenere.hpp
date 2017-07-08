/**
@file Vigenere.hpp
@version 0.1
@author Leo Sleet

Header for Vigenere.cpp
*/
#ifndef VIG_HEAD
#define VIG_HEAD

class Vigenere{
private:
  string key;
  int kp; //persistant pointer to a character of the key.
public:
  Vigenere(string);
  string decrypt(string);
  string encrypt(string);
  void encryptFile(string, string ="crypt.vig");
  void decryptFile(string, string ="plain.txt");
};

#endif