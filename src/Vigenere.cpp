/**
@file Vigenere.cpp
@version 0.1
@author Leo Sleet
@compile: g++ -std=gnu++11 -Wall -Werror -pendantic

@section Description

Performs polyalphabetic en/decryption
*/
#include <PolyCrack.hpp>
#include <Vigenere.hpp>
#include <FileManager.hpp>

/**
Constructor to create an en/decrypting object

@param key string to use as a key
*/
Vigenere::Vigenere(string key){
    this->key = makeLower(pureString(key));
    kp=0; //key pointer
  }
/**
Currently strips any non a-z|A-Z and forces to a single case

@param text encrypts a plaintext string
@return encrypted text
*/
string Vigenere::encrypt(string text){
    string out;
    text = makeLower(pureString(text));
    char c;
    for(unsigned int i = 0; i < text.length(); i++){
      c = text[i];
      out += ((c + key[kp]) % 'a' % 26) + 'A';
      kp = (kp + 1) % key.length();
    }
    kp = 0;
    return out;
}
/**

Currently cannot recover any non a-z|A-Z and forces to a single case

@param text decrypts a cipher string
@return decrypted text
*/
string Vigenere::decrypt(string text){
    string out;
    text = makeLower(pureString(text));
    char c;
    for(unsigned int i = 0; i < text.length(); i++){
      c = text[i];
      out += (((c - key[kp])+26) % 26) + 'a';
      kp = (kp + 1) % key.length();
    }
    kp = 0;
    return makeLower(out);
}
/**
performs encryption on a single text file. All non a-z|A-Z
is stripped.

key is reset so later calls are not affected by earlier calls.

@param file Name of file to encrypt
@param out optional name of output file
*/
void Vigenere::encryptFile(string file, string out){
  int oldKp = kp;
  kp=0;
  FileManager ifs(file);
  FileManager ofs(out);
  list<string> lines = ifs.parseLines();
  list<string> cryptLines;
  for (string line : lines){
    cryptLines.push_back(encrypt(line));
  }
  ofs.saveLines(cryptLines);
  kp=oldKp;
  return;
}
/**
performs decryption on a single text file. All non a-z|A-Z
is stripped.

key is reset so later calls are not affected by earlier calls.

@param file Name of file to decrypt
@param out optional name of output file
*/
void Vigenere::decryptFile(string file, string out){
  int oldKp = kp;
  kp=0;
  FileManager ifs(file);
  FileManager ofs(out);
  list<string> lines = ifs.parseLines();
  list<string> plainLines;
  for (string line : lines){
    plainLines.push_back(decrypt(line));
  }
  ofs.saveLines(plainLines);
  kp=oldKp;
  return;
}
