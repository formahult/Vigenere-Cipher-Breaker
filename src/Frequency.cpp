/**
@file Frequency.cpp
@version 0.1
@author Leo Sleet

A wrapper defining the absolute or relative frequencies of an
abstract body of text.
*/
#include <PolyCrack.hpp>
#include <Frequency.hpp>
#include <FileManager.hpp>
#include <functional>
#include <algorithm>
#include <cmath>

/**
Constructor

@param F Map between characters and their frequencies
@param T Total characters in text
*/
Frequency::Frequency(map<char, double> F, int T)
  :symFreqs(F), totalSymbols(T){
}
/**
Named constructor

@param cipherText String of text to analyse for symbol frequencies
*/
Frequency Frequency::FrequencyFromString(string cipherText){
  map<char, double> symFreqs;
  cipherText = pureString(cipherText);
  int size = cipherText.size();
  for (char c : cipherText){
    symFreqs[c]++;
  }
  return Frequency(symFreqs, size);
}
/**
Loads a previously saved frequency from a CSV file.

@param file URI of file
*/
Frequency Frequency::FrequencyFromCSV(string file){
  FileManager fm(file);
  map<char, double> sfreqs = fm.parseFrequencies();
  int count = 0;
  for (const auto freq : sfreqs){
    count += freq.second;
  }
  return Frequency(sfreqs, count);
}
/**
Read a file and counts symbol frequencies.

@param file URI of file
*/
Frequency Frequency::FrequencyFromFile(string file){
  FileManager fm(file);
  return Frequency::FrequencyFromString(fm.textOnly());
}

void Frequency::printFrequencies(){
  for (const auto freq : symFreqs){
    cout << freq.first << ": " << freq.second << "\n";
  }
}

double Frequency::getSymbolFrequency(char c)      {return symFreqs[c];}
map<char, double> Frequency::getSymbolFrequency() {return symFreqs;}

/**
Turns an absolute frequency set into it's relative representation

@return A RelFrequency object
*/
RelFrequency Frequency::getRelativeFrequency(){
  map<char, double> symRelFreqs = symFreqs;
  int count = 0;
  for (const auto freq : symRelFreqs){
    count += freq.second;
  }
  for (const auto freq : symRelFreqs){
    symRelFreqs[freq.first] = freq.second / count;
  }
  RelFrequency res(symRelFreqs);
  return res;
}

RelFrequency::RelFrequency(map<char, double> F)
  :symFreqs(F){
}

RelFrequency RelFrequency::FrequencyFromString(string cipherText){
  map<char, double> symFreqs;
  cipherText = cleanPunc(cleanNum(cleanWhite(cipherText)));
  int size = cipherText.size();
  for (char c : cipherText){
    symFreqs[c]++;
  }
  for (const auto freq : symFreqs){
    symFreqs[freq.first] = freq.second / size;
  }
  return RelFrequency(symFreqs);
}

RelFrequency RelFrequency::FrequencyFromCSV(string file){
  FileManager fm(file);
  map<char, double> sfreqs = fm.parseFrequencies();
  return RelFrequency(sfreqs);
}

RelFrequency RelFrequency::FrequencyFromFile(string file){
  FileManager fm(file);
  return RelFrequency::FrequencyFromString(fm.textOnly());
}

double RelFrequency::getSymbolFrequency(char c){
  return symFreqs[c];
}

map<char, double> RelFrequency::getSymbolFrequency(){
  return symFreqs;
}


void RelFrequency::printFrequencies(){
  for (const auto freq : symFreqs){
    cout.precision(17);
    cout << freq.first << ": " << freq.second << "\n";
  }
}

double RelFrequency::compare(RelFrequency reference){
  double average, difference;
  int count;
  cout << "\tReference\tText\t\tDifference" << endl;

  for(const auto freq : symFreqs){
    difference = abs(reference.getSymbolFrequency(freq.first) - freq.second);
    average += difference;
    count++;
    cout << freq.first << "\t";
    cout << reference.getSymbolFrequency(freq.first) << "\t\t";
    cout << freq.second << "\t";
    cout << difference << endl;
  }
  average /= count;
  cout << "\t\tAverage difference:\t" << average << endl;
  return average;
}
