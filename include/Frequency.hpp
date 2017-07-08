/**
@file Frequency.hpp
@version 0.1
@author Leo Sleet

Header for Frequency.cpp
 */
#ifndef FREQ_HEAD
#define FREQ_HEAD

class RelFrequency;

class Frequency{
private:
	map<char, double> symFreqs;
	int totalSymbols;
public:
	Frequency(map<char, double>, int); //empty freq object
	static Frequency FrequencyFromCSV(string);
	static Frequency FrequencyFromString(string);
	static Frequency FrequencyFromFile(string);

	map<char, double> getSymbolFrequency();
	double getSymbolFrequency(char);

	RelFrequency getRelativeFrequency();

	void printFrequencies();
	double compare(Frequency);

};

class RelFrequency{
private:
	map<char, double> symFreqs;
public:
	RelFrequency(map<char, double>); //empty freq object
	static RelFrequency FrequencyFromCSV(string);
	static RelFrequency FrequencyFromString(string);
	static RelFrequency FrequencyFromFile(string);

	map<char, double> getSymbolFrequency();
	double getSymbolFrequency(char);

	void printFrequencies();
	double compare(RelFrequency);

};




#endif