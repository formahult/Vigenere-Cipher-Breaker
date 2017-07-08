/**
@file main.cpp
@version 0.1
@author Leo Sleet
Compile: g++ -std=gnu++11 -Wall -Werror -pendantic
*/
#include <PolyCrack.hpp>
#include <Frequency.hpp>
#include <Vigenere.hpp>
#include <FileManager.hpp>
#include <KeyAnalyser.hpp>

//TextParser
void testReadLines(){
  list<string> correct = {
    "a,0.08167",
    "b,0.01492",
    "c,0.02782",
    "d,0.04253",
    "e,0.12702",
    "f,0.02228",
    "g,0.02015",
    "h,0.06094",
    "i,0.06966",
    "j,0.00153",
    "k,0.00772",
    "l,0.04025",
    "m,0.02406",
    "n,0.06749",
    "o,0.07507",
    "p,0.01929",
    "q,0.00095",
    "r,0.05987",
    "s,0.06327",
    "t,0.09056",
    "u,0.02758",
    "v,0.00978",
    "w,0.02361",
    "x,0.00150",
    "y,0.01974",
    "z,0.00074"};
  FileManager fm("english.csv");
  if(fm.parseLines() != correct)
    cout << "readLines() failed" << endl;
  return;
}

void testCleanPunc(){
  string input = "!T@h#i$s^i%%s&a*s?t.r,i;n'g~";
  string correct = "Thisisastring";
  if(cleanPunc(input) != correct)
    cout << "testCleanPunc() failed " << cleanPunc(input) << endl;
  return;
}

void testCleanNum(){
  string input = "1T2h3i4sis5a6s7t8ri9n0g";
  string correct = "Thisisastring";
  if(cleanNum(input) != correct)
    cout << "testCleanNum() failed " << cleanNum(input) << endl;
  return;
}

void testMakeLower(){
  string input = "THISISastring";
  string correct = "thisisastring";
  if (makeLower(input) != correct){
    cout << "testMakeLower() failed " << makeLower(input) << endl;}
  return;
}

void testCleanWhite(){
  string input = "this i\vs\ta\n     s\ft\rring";
  string correct ="thisisastring";
  if (cleanWhite(input) != correct){
    cout << "testCleanWhite() failed" << endl;
  }
  return;
}

void testCleanQuotes(){
  string input = "\"this\'isa\"\"\'`string";
  string correct ="thisisastring";
  if (cleanQuotes(input) != correct){
    cout << "testCleanQuotes() failed" << endl;
  }
  return;
}

//Vigenere class
void testEncryption(){
  Vigenere cipher("VIGENERECIPHER");
  string input = "Beware the Jabberwock, my son! The jaws that bite, the claws that catch!";
  string correct = "WMCEEIKLGRPIFVMEUGXQPWQVIOIAVEYXUEKFKBTALVXTGAFXYEVKPAGY";
  if (cipher.encrypt(input) != correct){
    cout << "testEncryption() failed " << cipher.encrypt(input) << endl;
  }
}

void testDecryption(){
  Vigenere cipher("VIGENERECIPHER");
  string input = "WMCEEIKLGRPIFVMEUGXQPWQVIOIAVEYXUEKFKBTALVXTGAFXYEVKPAGY";
  string correct = "bewarethejabberwockmysonthejawsthatbitetheclawsthatcatch";
  if (cipher.decrypt(input) != correct){
    cout << "testDecryption() failed " << cipher.decrypt(input) << endl;
  }
}

void testEncryptFile(){
  Vigenere cipher("VIGENERECIPHER");
  string input = "brosk.txt";
  string correct = "WMCEEIKLGRPIFVMEUGXQPWQVIOIAVEYXUEKFKBTALVXTGAFXYEVKPAGY";
  cipher.encryptFile(input);
}

void testDecryptFile(){
  Vigenere cipher("VIGENERECIPHER");
  string input = "crypt.vig";
  string correct = "WMCEEIKLGRPIFVMEUGXQPWQVIOIAVEYXUEKFKBTALVXTGAFXYEVKPAGY";
  cipher.decryptFile(input);
}

//Frequency class

// void testFreqMap(){
//   map<char, double> input = {
//     {'s', 2},
//     {'p', 1},
//     {'a', 3},
//     {'m', 2},
//     {'e', 1},
//     {'g', 2},
//     {'n', 1},
//     {'d', 1},
//     {'h', 1}
//   };
//   Frequency freq(input, input.size());
//   cout << freq.getSymbolFrequency('p') << endl;
//   cout << freq.getSymbolFrequency('q') << endl;
//   return;
// }

void testPrintFrequencies(){
  map<char, double> input = {
    {'s', 2},
    {'p', 1},
    {'a', 3},
    {'m', 2},
    {'e', 1},
    {'g', 2},
    {'n', 1},
    {'d', 1},
    {'h', 1}
  };
  Frequency freq(input, input.size());
  freq.printFrequencies();
  return;
}

void testFrequencyFromString(){
  map<char, double> correcta = {
    {'s', 2},
    {'p', 1},
    {'a', 3},
    {'m', 2},
    {'e', 1},
    {'g', 2},
    {'n', 1},
    {'d', 1},
    {'h', 1}
  };

  map<char, double> correctb = {
    {'s', 0.14285714285714285},
    {'p', 0.071428571428571425},
    {'a', 0.21428571428571427},
    {'m', 0.14285714285714285},
    {'e', 0.071428571428571425},
    {'g', 0.14285714285714285},
    {'n', 0.071428571428571425},
    {'d', 0.071428571428571425},
    {'h', 0.071428571428571425}
  };
  Frequency freq = Frequency::FrequencyFromString("spameggsandham");
  RelFrequency rfreq = RelFrequency::FrequencyFromString("spameggsandham");
  if(freq.getSymbolFrequency() != correcta)
    cout << "getSymbolFrequency failed" << endl;
  if(rfreq.getSymbolFrequency() != correctb){
    cout << "getRelativeFrequency failed" << endl;
    rfreq.printFrequencies();
  }
  return;
}

void testFrequencyFromCSV(){
  map<char, double> correct = {
    {'a',8.167},
    {'b',1.492},
    {'c',2.782},
    {'d',4.253},
    {'e',12.702}
  };
  RelFrequency rfreq = RelFrequency::FrequencyFromCSV("t.csv");
  if(rfreq.getSymbolFrequency() != correct)
    cout << "testFrequencyFromCSV() failed" << endl;
  return;
}

void testFrequencyFromFile(){
  Frequency freq = Frequency::FrequencyFromFile("t.txt");
  Frequency correct = Frequency::FrequencyFromString("bewarethejabberwockmysonthejawsthatbitetheclawsthatcatch");
  if(freq.getSymbolFrequency() != correct.getSymbolFrequency()){
    cout << "testFrequencyFromFile failed" << endl;
    freq.printFrequencies();
    cout << "should be" << endl;
    correct.printFrequencies();
  }
  RelFrequency freq2 = RelFrequency::FrequencyFromFile("t.txt");
  RelFrequency correct2 = RelFrequency::FrequencyFromString("bewarethejabberwockmysonthejawsthatbitetheclawsthatcatch");
  if(freq2.getSymbolFrequency() != correct2.getSymbolFrequency()){
    cout << "testFrequencyFromFile failed" << endl;
    freq2.printFrequencies();
    cout << "should be" << endl;
    correct2.printFrequencies();
  }
  return;
}

//KeyAnalyser
void testGuessKeyLength(){
  Friedmann F("QPWKALVRXCQZIKGRBPFAEOMFLJMSDZVDHXCXJYEBIM    TRQWNMEAIZRVKCVKVLXNEICFZPZCZZHKMLVZVZIZRRQWDKECHOSNYXXLSPMYKVQXJTDCIOMEEXDQVSRXLRLKZHOV");
  int res = F.guessKeyLength(1, 9);
  cout << "best guess key: " << res << endl;

}

void testQuickGuessKeyLength(){
  Friedmann F = Friedmann::FriedmannFromFile("t.vig");
  int res = F.quickGuessKeyLength();
  cout << "quick guess key: " << res << endl;

}


int main(int argc, char const *argv[]) {
  //FileManager
  testReadLines();
  testCleanPunc();
  testCleanNum();
  testMakeLower();
  testCleanWhite();
  //vigenere class
  testEncryption();
  testDecryption();
  testEncryptFile();
  testDecryptFile();
  // //frequnecy class
  // //testFreqMap();
  // testPrintFrequencies();
  testFrequencyFromCSV();
  testFrequencyFromString();
  testFrequencyFromFile();
  //Friedmann class
  testGuessKeyLength();
  testQuickGuessKeyLength();

  return 0;
}
 //128/

/*
0.0285/0.031846

*/
