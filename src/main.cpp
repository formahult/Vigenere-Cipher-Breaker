/**
@file main.cpp
@version 0.1
@author Leo Sleet

Main body of polycrack.

Accepts arguments and returns appropriate outputs.

Compiling using make and running
./polycrack --help provides usage instructions.
*/
#include "PolyCrack.hpp"
#include "optionparser.hpp"
#include <Vigenere.hpp>
#include <KeyAnalyser.hpp>
#include <Frequency.hpp>

// for lean mean option parser
enum OptionIndex {
  UNKNOWN,
  HELP,
  MODE,
  FILEIN,
  FILEOUT,
  KEYLEN,
  DICT,
  CRIB,
};
enum OptionType {
  KANAL,
  FANAL,
  ENCRYPT,
  DECRYPT,
  KELIM,
  FQANAL,
};

//argument checking functions
struct Arg : public option::Arg{

  static void printError(const char* msg1, const option::Option& opt, const char* msg2){
    fprintf(stderr, "ERROR: %s", msg1);
    fwrite(opt.name, opt.namelen, 1, stderr);
    fprintf(stderr, "%s", msg2);
  }

  static option::ArgStatus Unknown(const option::Option& option, bool msg){
     if (msg) printError("Unknown option '", option, "'\n");
     return option::ARG_ILLEGAL;
  }

  static option::ArgStatus Numeric(const option::Option& option, bool msg){
    char* endptr = 0;
    if (option.arg != 0 && strtol(option.arg, &endptr, 10)){};
    if (endptr != option.arg && *endptr == 0)
      return option::ARG_OK;
    if (msg) printError("Option '", option, "' requires a numeric argument\n");
    return option::ARG_ILLEGAL;
  }

  static option::ArgStatus NonEmpty(const option::Option& option, bool msg)
   {
     if (option.arg != 0 && option.arg[0] != 0)
       return option::ARG_OK;

     if (msg) printError("Option '", option, "' requires a non-empty argument\n");
     return option::ARG_ILLEGAL;
   }

  static option::ArgStatus FileName(const option::Option& option, bool msg){
    return option::ARG_OK;
  }
};

const option::Descriptor usage[] = {
  {UNKNOWN,   0,   "",    "",            option::Arg::None,          "Usage: PolyCrack [mode] [options] \n\nOptions:"},
  {HELP,      0,   "h",   "help",         option::Arg::None,          " --help \tPrint usage and exit."},

  {MODE,ENCRYPT,  "e",  "encrypt",      Arg::NonEmpty,  " -e --encrypt [key] \tEncrypt file using specified key."},
  {MODE,DECRYPT,  "d",  "decrypt",      Arg::NonEmpty,  " -d --decrypt [key] \tDecrypt file using specified key."},
  {MODE,  FANAL,  "f",  "freidmann",    option::Arg::None,          " -f --friedmann [lower limit] [upper limit]\n \tPerform friedmann analysis to guess key length.\n\t-f quick, -ff accurate."},
  {MODE,  KANAL,  "k",  "kasiski",      option::Arg::None,          " -k --kasiski \tPerform kasiski examination to guess key length."},
  {MODE,  KELIM,  "E",  "key-elimination", option::Arg::None,       " -E --key-elimination [] \tSubtracts the ciphertext from itself offset by key length."},
  {MODE,  FQANAL, "F",  "frequency-analysis", Arg::NonEmpty,    " -F --frequency-analysis [Ref Freqs] \tCompares infile frequencies to [Ref Freqs]\n \tRef Freqs is a csv of the letter frequencies for a language."},

  {FILEIN,    0,  "i",  "input-file",   Arg::NonEmpty, " -i --input-file [filename] \tRequired for some oprations."},
  {FILEOUT,   0,  "o",  "output-file",  Arg::NonEmpty, " -o --output-file [filename] \tRequired for some oprations."},
  {KEYLEN,    0,  "s",  "key-size",     Arg::Numeric, " -s --key-size \tSpecifiy the size of the key to use when performing frequency analysis or brutforing"},
  {DICT,      0,  "w",  "word-list",    Arg::NonEmpty, " -w --word-list [file] \tSpecify a word list to use when bruteforcing."},
  {CRIB,      0,  "c",  "crib",         Arg::NonEmpty,  " -c --crib \tProvide a crib to improve analysis and to verify a brute force attack."},

  {0,0,0,0,0,0} //sentinel
};

int main(int argc, char const *argv[]) {
  argc-=(argc>0); argv+=(argc>0);

  string infile, outfile, wordlist;
  //int keylen=0;


  option::Stats stats(usage, argc, argv);
  option::Option* options = new option::Option[stats.options_max];
  option::Option* buffer = new option::Option[stats.buffer_max];
  option::Parser parse(usage, argc, argv, options, buffer);

  if(parse.error())
    return 1;

  if (options[HELP] || argc==0){
    option::printUsage(cout, usage);
    return 0;
  }

  //take some options
  if (options[FILEIN])
    infile=options[FILEIN].arg;
  if (options[FILEOUT])
    outfile=options[FILEOUT].arg;
  // if (options[KEYLEN])
  //   keylen = atoi(options[KEYLEN].arg);
  if (options[DICT])
    wordlist=options[DICT].arg;

  switch(options[MODE].first()->type()){
    case ENCRYPT:{
      Vigenere vig(options[MODE].first()->arg);
      vig.encryptFile(infile, outfile);
      return 0;
    }
    case DECRYPT:{
      Vigenere vig(options[MODE].first()->arg);
      vig.decryptFile(infile, outfile);
      return 0;
    }
    case FANAL:{
      int flevel = options[MODE].count();
      if(flevel < 2){
        Friedmann F = Friedmann::FriedmannFromFile(infile);
        int res = F.quickGuessKeyLength();
        cout << "Key length estimate: " << res << endl;
        return 0;
      }else if(flevel < 3){
        cout << infile << endl;
        Friedmann F = Friedmann::FriedmannFromFile(infile);
        int res = F.guessKeyLength(atoi(options[MODE].next()->arg), atoi(options[MODE].next()->arg));
        cout << "Key length estimate: " << res << endl;
        return 0;
      }else{
        cerr << "only -f and -ff are valid levels" << endl;
        return 1;
      }
    }
    case FQANAL:{
      RelFrequency reference = RelFrequency::FrequencyFromCSV(options[MODE].first()->arg);
      RelFrequency text = RelFrequency::FrequencyFromFile(infile);
      text.compare(reference);
      return 0;
    }
    case KANAL:{
      cout << "kasiski analysis is not yet imlemented\n";
      return 0;
    }
    case KELIM:{
      cout << "Key elimination is not yet implemented\n";
      return 0;
    }
    default:{
      option::printUsage(cout, usage);
      return 0;
    }
  }

}
