/**
@file TextUtils.cpp
@version 0.1
@author Leo Sleet

Helper functions
*/
#include "PolyCrack.hpp"
#include <algorithm>
#include <cctype>


bool invalidChar (char c)
{
  return !(c>= 0 && c <128);
}

string makeASCII(string str){
  str.erase(remove_if(str.begin(), str.end(), invalidChar ), str.end());
  return str;
}

string cleanPunc(string str){
  string result;
  remove_copy_if(str.begin(), str.end(),
                back_inserter(result),
                ptr_fun<int, int>(&ispunct));
  return result;
}

string cleanNum(string str){
  string result;
  remove_copy_if(str.begin(), str.end(),
                back_inserter(result),
                ptr_fun<int, int>(&isdigit));
  return result;
}

string cleanWhite(string str){
  string result;
  remove_copy_if(str.begin(), str.end(),
                back_inserter(result),
                ptr_fun<int, int>(&isspace));
  return result;
}

string makeLower(string str){
  int (*tl)(int) = tolower; // Select that particular overload
  transform(str.begin(), str.end(), str.begin(), tl);
  return str;
}

string makeUpper(string str){
  int (*tu)(int) = toupper; // Select that particular overload
  transform(str.begin(), str.end(), str.begin(), tu);
  return str;
}

string cleanQuotes(string str){
  str.erase(remove( str.begin(), str.end(), '\"' ), str.end());
  str.erase(remove( str.begin(), str.end(), '\'' ), str.end());
  str.erase(remove( str.begin(), str.end(), '`' ), str.end());
  return str;
}

string pureString(string str){
  return cleanQuotes(cleanWhite(cleanNum(cleanPunc(makeASCII(str)))));
}