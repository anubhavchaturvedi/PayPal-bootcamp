#include "ScrabbleWords.h"

ScrabbleWords::ScrabbleWords(string filename) {
  ifstream sowpodsFile;
  sowpodsFile.open(filename.c_str());
}

string getSortedString(string str){
    std::sort(word.begin(), word.end());
    }
