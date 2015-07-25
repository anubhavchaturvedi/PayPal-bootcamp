#include "ScrabbleWords.h"

ScrabbleWords::ScrabbleWords(string filename) {
  ifstream sowpodsFile;
  sowpodsFile.open(filename.c_str());
  string word;
  while(getline(sowpodsFile, word)) {
  	insertInSowpodsMap(getSortedString(word), word);
  }
}

void ScrabbleWords::insertInSowpodsMap(string key, string value)
    {
    	sowpods[key].push_back(value);
    }
    
    
    string ScrabbleWords::getSortedString(string word){
    	string sortedWord = word;
        std::sort(sortedWord.begin(), sortedWord.end());
        return sortedWord;
    }

vector<string> ScrabbleWords::getAnagrams(string word) {
	string sortedWord = getSortedString(word);
	vector<string> anagrams;
	if(sowpods.find(sortedWord) != sowpods.end()) {
		anagrams = sowpods[sortedWord];
	}
	return anagrams;
}
