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
        map<string, vector<string> >::iterator it = sowpods.begin();

        if( sowpods.count(key) )
        {
            it = sowpods.find( key );
            (it->second).push_back(value);
        }

        else
        {
            vector<string> newVector;
            newVector.push_back(value);
            sowpods.insert ( std::pair<string, vector<string> >( key, newVector) );
        }
    }
    
    
    string getSortedString(string str){
        std::sort(word.begin(), word.end());
    }

vector<string> ScrabbleWords::getAnagrams(string word) {
	string sortedWord = getSortedString(word);
	vector<string> anagrams;
	if(sowpods.find(sortedWord) != sowpods.end()) {
		vector<string> anagrams = sowpods[sortedWord];
	}
	return anagrams;
}

string getSortedString(string str){
    std::sort(word.begin(), word.end());
    }
