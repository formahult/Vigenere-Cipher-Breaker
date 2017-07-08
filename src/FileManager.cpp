/**
@file FileManager.hpp
@version 0.1
@author Leo Sleet

File I/O utilities
*/

#include <PolyCrack.hpp>
#include <FileManager.hpp>
#include <list>
#include <map>

#define DELIMITER "," //For CSVs

/**
Constructor to safely open a file.

@param fileName URI to file
*/
FileManager::FileManager(string fileName){
  fs.open(fileName, fstream::in | fstream::out | fstream::app);
  if(!fs.is_open())
  {
    cerr << "Failed to open file \'" << fileName << "\'" << endl;
    exit(EXIT_FAILURE);
  }
}
/**
Destructor ensures that the file is safely closed.
*/
FileManager::~FileManager(){
    fs.close();
}
/**
@return The file's lines as a list of strings.
*/
list<string> FileManager::parseLines(){
  list<string> lines;
  string line;
  while(getline(fs, line)){
    lines.push_back(line);
  }
  return lines;
}
/**
@return The file's lines as a single cleaned string
*/
string FileManager::textOnly(){
  list<string> lines = FileManager::parseLines();
  string str;
  for (string line : lines){
    str = str + makeLower(pureString(line));
  }
  return str;
}
/**
@return a map of chars and the recorded frequencies.
*/
map<char, double> FileManager::parseFrequencies(){
  map<char, double> freqs;
  list<string> lines = parseLines();
  string token;
  size_t pos = 0;
  double value = 0.0;

  for(string line : lines){
    pos = line.find(DELIMITER);
    token = line.substr(0, pos);
    value = stod(line.substr(pos+1));
    freqs[*token.c_str()] = value;
  }
  return freqs;
}
/**
Writes out a list of strings each on a new line.

@param lines List of string to write.
@return count of lines saved.
*/
int FileManager::saveLines(list<string> lines){
  int count=0;
  for (string line : lines){
    fs << line << endl;
    count++;
  }
  return count;
}