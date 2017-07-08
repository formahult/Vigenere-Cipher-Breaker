/**
@file KeyAnalyser.hpp
@version 0.1
@author Leo Sleet

Header for KeyAnalyser.cpp
*/
#ifndef KEY_HEAD
#define KEY_HEAD

#include <set>
#include <thread>

class Friedmann{
private:
	string cipherText;
public:
	Friedmann(string);
	static Friedmann FriedmannFromFile(string);
	map<int, double> getKeyICs(int=1, int=25);
	int guessKeyLength(int=1, int=25);
	int quickGuessKeyLength();
	double getIC(string);
	void printKeyICs(int=1, int=25);
};
class Kasiski{
private:
	string cipherText;
public:
	Kasiski(string);
	set<int> testDigraphs();
	set<int> testTrigraphs();
	set<int> testCrib();
	int guessKeyUsingCrib(string);
	set<int> factors(int);

};
class Kerckhoff{
private:
public:
	Kerckhoff();
	~Kerckhoff();

};
class KeyEliminator{
private:
	list<string> cipherText;
public:
	KeyEliminator(string);
	~KeyEliminator();

};


class KeyBrute
{
private:
	string fileName;
	int threads;


public:
	KeyBrute(string, int);
	~KeyBrute();


	/* data */
};


#endif