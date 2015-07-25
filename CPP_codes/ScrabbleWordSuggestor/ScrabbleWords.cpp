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

vector<string> ScrabbleWords::getAnagrams(string word) {
	string sortedWord = getSortedString(word);
	vector<string> anagrams;
	if(sowpods.find(sortedWord) != sowpods.end()) {
		vector<string> anagrams = sowpods[sortedWord];
	}
	return anagrams;
}

int main() {
	ScrabbleWords scr("sowpods.txt");
	vector<string> a = scr.getAnagrams("friends");
	for(string s : a) {
		cout << s << endl;
	}
}
