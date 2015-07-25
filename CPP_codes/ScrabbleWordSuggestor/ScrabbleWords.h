#include<map>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>

using namespace std;

class ScrabbleWords {

  map<string, vector<string> > sowpods;
  public: 
    ScrabbleWords(string);
    vector<string> getAnagrams(string);
    bool isValidWord(string);
  private:
    string getSortedString(string);
    void insertInSowpodsMap(string, string);
};
