#include "ScrabbleWords.h"

ScrabbleWords::ScrabbleWords(string filename) {
  ifstream sowpodsFile;
  sowpodsFile.open(filename.c_str());
  string word;
  while(getline(file, word)) {
  	insertInSowpodsMap(getSortedString(word), word);
  }
}

void ScrabbleWordSuggestor::insertInSowpodsMap(string key, string value)
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
