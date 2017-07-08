/**
@file FileManager.hpp
@version 0.1
@author Leo Sleet

Header for FileManager.cpp
*/
#ifndef FILE_HEAD
#define FILE_HEAD

class FileManager{
private:
	fstream fs;
public:
	FileManager(string);
	~FileManager();
	bool is_open();
	list<string> parseLines();
	int saveLines(list<string>);
	map<char, double> parseFrequencies();
	string textOnly();
};
#endif