#include<map>
#include<vector>

class ScrabbleWords {

  map<string, vector<string> > sowpods;
  public: 
    ScrabbleWords(string);
    vector<string> getAnagrams();
    bool isValidWord(string);
};