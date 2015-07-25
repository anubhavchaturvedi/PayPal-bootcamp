#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <regex>

#define private public

using namespace std;

int computeScore(string,int);

const string EMPTY_TILE = "*";
const int NO_SCORE_COMPENSATION = 0;
const int MAX_RACK_LENGTH = 7;
const int NUMBER_OF_OUTPUT = 5;

const int ALPHABET_SCORE[] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

class ScrabbleWordSuggestor
{

    private:

    map< string, vector<string> > sowpods;
    map< int, vector<string> > scored_list;
    set < pair<string,int> > POWERSET_RACKS;
    string RACK_STRING;
    string rackRegExp;

    private:
    int getCharScore(char ch);
    void generatePowerSetOfRack( string rack, set<string>& power_set );
    void generateBlankReplacedPowerSet( set<string>& power_set, set< pair<string,int> >& power_set_score );
    void replaceBlankTile( string rack, set< std::pair<string,int> >& set_of_racks );
    void replaceBlankTile( string rack, int scoreDeductionValue, set< std::pair<string,int> >& set_of_racks );
    string getSortedString(string word);
    void insertInSowpodsMap(string key, string value);
    void generateSowpodsMap(ifstream &file);
    vector<string> getAnagramListFromSowpodsMap(string key);
    int computeScore(string str, int scoreCompensation);
    void insertInScoredList(int score, string word);
    void generateScoredList();
    void addConstraintToRack(string constraint);
    void removeConstraintFromRack(string constraint);
    string generateRegExp(string constraint);
    bool isMatchesRegularExpression(string word);


    public:
    ScrabbleWordSuggestor(string FILENAME);
    string suggestWords(string rack, string constraint = "");
    void addConstraint(string constraint);
};

