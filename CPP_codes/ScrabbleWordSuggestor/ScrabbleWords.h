#include<map>
#include<vector>
#include<string>

class ScrabbleWords {

  map<string, vector<string> > sowpods;
  public: 
    ScrabbleWords(string);
    vector<string> getAnagrams(string);
    bool isValidWord(string);
    string getSortedString(string str);
    void insertInSowpodsMap(string word);
};
