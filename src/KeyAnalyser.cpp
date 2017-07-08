/**
@file KeyAnalyser.cpp
@version 0.1
@author Leo Sleet

Includes multiple classes for determining the key length of a given
cipher text. Once the key size is known, the cipher text
can be broken down into monoalphabetic ciphers
which can either be bruteforced or frequency attacked.

*/
#include <PolyCrack.hpp>
#include <Frequency.hpp>
#include <FileManager.hpp>
#include <KeyAnalyser.hpp>
#include <set>
#include <map>
#include <cmath>


//Replace Defines with a more general description of a chosen language
#define KP 0.067 //MONOCASE ENGLISH ONLY!!!!!
#define KR 0.0385 //1/26 for ENGLISH ONLY!!!!
#define C 26 //Number of letters in english alphabet
#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

/**
Constructor

@param S Cipher text as a single string.
*/
Friedmann::Friedmann(string S){
	this->cipherText = makeUpper(pureString(S));
}

/**
Named constructor

@param filename URI of a file containing the cipher text
*/
Friedmann Friedmann::FriedmannFromFile(string filename){
	FileManager fm(filename);
	return Friedmann(fm.textOnly());
}

/**
Tries multiple key lengths and chooses the key length which maximises
the index of co-incidence (IC).

@param rLo lower possible key size bound default=1
@param rHi upper possible key size bound default=25
@return return the key length which maximises index of co-incidence
*/
int Friedmann::guessKeyLength(int rLo, int rHi){
	double maxIC=0.0;
	map<int, double> keyICs = getKeyICs(rLo, rHi);
	int probKey=rLo;
	//loop over possible key lengths
	for (int posKey=rLo; posKey<rHi; posKey++){
		//return key length with highest average IC
		if(maxIC < keyICs[posKey]) {
			maxIC = keyICs[posKey];
			probKey = posKey;
		}
	}
	//problem multiples of the actual key length may have higher ICs
	// than the actual key length. e.g keylen=5 may result in 10 having higher IC
	// resolve this problem by facotring the proposed key.
	return probKey;
}
/**
A method of guessing the key length that requires only one pass.
Less effective, but much faster.

@return returns the estimated key length
*/
int Friedmann::quickGuessKeyLength(){
	double ic = getIC(cipherText);
	double kp = KP; //kappa p for ref lang
	double kr = KR; //kappa r for ref lang
	return round((kp - kr)/abs(ic - kr));

}

/**
Calculates the average IC for different key lengths.

@param rLo lower possible key size bound default=1
@param rHi upper possible key size bound default=25
@return Map<int, double> of the calculated key lengths and ICs
*/
map<int, double> Friedmann::getKeyICs(int rLo, int rHi){
	map<int, double> keyICs;
	string col;
	double aveIC=0.0;
	for (int posKey=rLo; posKey<rHi; posKey++){
	//create a matrix with 'key length colums'
		for(int i=0; i<posKey; i++){
		//different starting locations for each 'row'
			//start at i and grab each char at posKey intervals until end
			col="";
			for(int j=i; j<(int)cipherText.size(); j+=posKey){
				col += cipherText[j];
			}
			aveIC += getIC(col);
		}
		//average ICs for each matrix
		aveIC /= posKey;
		keyICs[posKey]= aveIC;
	}
	return keyICs;
}

/*
Calculates IC for a single string of cipher text.

@param col String of cipher text to calculate IC for
@return The index of coincidence for a given string
*/
double Friedmann::getIC(string col){
	double res=0.0;
	double long summand=0.0;
	Frequency colFreq = Frequency::FrequencyFromString(col);
	long N = col.size();
	N = N*(N-1);
	int f;

	for (char c : ALPHABET){
		f = colFreq.getSymbolFrequency(c);
		summand += f*(f-1);
	}
	res = summand/N;
	return res;
}
/**
Calcuates and outputs the ICs for given key ICs

@param rLo lower possible key size bound default=1
@param rHi upper possible key size bound default=25
*/
void Friedmann::printKeyICs(int rLo, int rHi){
	map<int, double> keyICs = getKeyICs(rLo, rHi);
	for (int posKey=rLo; posKey<rHi; posKey++){
		cout << posKey << ":" << keyICs[posKey] << endl;
	}
}

KeyBrute::KeyBrute(string S, int T){
	this->threads = T;
	this->fileName = S;
}

/*
Try and find a known crib in the entirety of the text.
*/
// string KeyBrute::TryForCrib(string key, string testText, string crib){
// 	return 0;
// }


/*
For speed and efficiency only decrypts a section the
same length as the key being tested.
*/
// string KeyBrute::TryKey(string key, string testText, string dictName){
// 	FileManager dictFP(dictName);
// 	list<string> dictLines = dictFP.parseLines();
// 	testText.resize(key.length());
// 	Vigenere cipher(key);
// 	cipher.decrypt(testText);


// }

/**
Constructor Not immplemented

@param file Name of file to analyse
@return possible key length as an int
*/
Kasiski::Kasiski(string S)
:cipherText(S){
}

// set<int> Kasiski::testDigraphs(){
// 	map<string, KasTable> digraphs;
// 	set<int> posKeyLens;
// 	int len = cipherText.size();
// 	for (int i=0; i<len; i++){
// 		subs = cipherText.substr(i, i++);
// 		if(digraphs.count(subs)){
// 			KasTable modify = digraphs[subs];
// 			modify.dist = i - modify.posn;
// 			digraphs[subs] = modify;
// 		} else {
// 			KasTable entry;
// 			entry.posn = i;
// 			digraphs[subs] = entry;
// 		}

// 	}
// 	for (KasTable kas : digraphs){
// 		posKeyLens.insert(factors(kas.dist));
// 	}
// }

/**
Will return the factors of a given integer.
Not implemented

@param n integer to break into factors
@return an int set containing factors of n
*/
set<int> Kasiski::factors(int n){
	set<int> fs;
	int limit = sqrt(n);
	for (int i=2; i<limit; i++){
		if(n%i==0)
			fs.insert(i);
	}
	return fs;
}