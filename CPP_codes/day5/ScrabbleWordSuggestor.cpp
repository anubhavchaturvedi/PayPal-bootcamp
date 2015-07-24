#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <regex>

using namespace std;

const string EMPTY_TILE = "*";
const int NO_SCORE_COMPENSATION = 0;
const int NUMBER_OF_OUTPUT = 5;


const int ALPHABET_SCORE[] = {1,3,3,2, 1,4,2,4, 1,8,5,1,3, 1,1,3,10, 1,1,1,1, 4,4,8,4, 10};

class ScrabbleWordSuggestor
{

    private:

    map< string, vector<string> > sowpods;
    map< int, vector<string> > scored_list;
    set < pair<string,int> > POWERSET_RACKS;
    string RACK_STRING;
    string rackRegExp;
    string posConstraint;

    int getCharScore(char ch) {
        return ALPHABET_SCORE[ ch - 'a' ];
    }

    void generatePowerSetOfRack( string rack, set<string>& power_set )
    {
        int set_size = rack.length();
        unsigned int pow_set_size = pow(2, set_size);
        int counter, j;
        string subset;
        int multiplicationFactor;

        for(counter = 1; counter < pow_set_size; counter++)
        {
            subset = "";


            for(j = 0; j < set_size; j++)
            {
                multiplicationFactor = pow (2, j);
                if(counter & (1 * multiplicationFactor))
                    subset += rack[j];
            }
            power_set.insert(subset);
        }
    }

    void generateBlankReplacedPowerSet( set<string>& power_set, set< pair<string,int> >& power_set_score )
    {
        for ( string power_set_element : power_set )
        {
            replaceBlankTile( power_set_element, power_set_score );
        }
    }

    void replaceBlankTile( string rack, set< std::pair<string,int> >& set_of_racks )
    {
        replaceBlankTile( rack, 0, set_of_racks );
    }

    void replaceBlankTile( string rack, int scoreDeductionValue, set< std::pair<string,int> >& set_of_racks )
    {
        int rackBlankTileIndex = rack.find(EMPTY_TILE);
        if ( rackBlankTileIndex >= 0 )
        {
            for ( char ch = 'a'; ch <='z'; ch++ )
            {
                rack[rackBlankTileIndex] = ch;
                int newScoreDectionValue = scoreDeductionValue + getCharScore(ch);
                replaceBlankTile( rack, newScoreDectionValue, set_of_racks);
            }
        }
        else
        {
            set_of_racks.insert( pair<string,int> ( getSortedString(rack), scoreDeductionValue) );
        }
    }

    string getSortedString(string word)
    {
        std::string sortedWord = word;
        std::sort(sortedWord.begin(), sortedWord.end());
        return sortedWord;
    }

    void insertInSowpodsMap(string key, string value)
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

    void generateSowpodsMap(ifstream &file)
    {
        string word;
        while(getline(file, word))
        {
            insertInSowpodsMap(getSortedString(word), word);
        }
    }

    vector<string> getAnagramListFromSowpodsMap(string key)
    {
        vector<string> anagramList;
        if( sowpods.find(key) != sowpods.end() )
        {
            anagramList = sowpods.find( key )->second;
        }
        return anagramList;
    }

    int computeScore(string str, int scoreCompensation)
    {
        int score = 0;
        for ( int i = 0; i < str.length(); i++ )
        {
            char ch = str[i];
            if ( 'a' <= ch && ch <= 'z' )
            {
                score += ALPHABET_SCORE[ ch - 'a' ];
            }
        }
        return score - scoreCompensation;;
    }

    void insertInScoredList(int score, string word)
    {
        map<int, vector<string> >::iterator it = scored_list.begin();
        if ( scored_list.find(score) != scored_list.end() )
        {
            it = scored_list.find( score );
            (it->second).push_back(word);
        }
        else
        {
            vector<string> newVector;
            newVector.push_back(word);
            scored_list.insert ( std::pair<int, vector<string> >(score, newVector) );
        }
    }

    void generateScoredList(string rack)
    {
        this->RACK_STRING = rack;
        set<string> powerSet;

        POWERSET_RACKS.clear();
        scored_list.clear();

        generatePowerSetOfRack(rack, powerSet);
        generateBlankReplacedPowerSet(powerSet, POWERSET_RACKS);

        for ( pair<string,int> p : POWERSET_RACKS )
        {
            int score = computeScore( p.first, NO_SCORE_COMPENSATION );
            for ( string anagram : getAnagramListFromSowpodsMap( p.first ) ) {
                if (this->rackRegExp.length() > 0) {
                    std::cout<< "I AM IN GENERATE" << endl;
                    if (isMatchesRegularExpression(anagram)) {

                            int scoreCompensation = p.second;
                            insertInScoredList( score - scoreCompensation, anagram);
                    }
                }
            }
        }
        removeConstraintFromRack();
    }

    void addConstraintToRack() {
    	for(int index = 0; index < posConstraint.length(); index++) {
    		char letter = posConstraint.at(index);
    		if(letter != '*') {
    			this->RACK_STRING.push_back(letter);
            }
        }
    }

    void removeConstraintFromRack() {
        for(int index = 0; index < posConstraint.length(); index++) {
            char letter = posConstraint.at(index);
            if(letter != '*') {
    			this->RACK_STRING.erase(this->RACK_STRING.find(letter), 1);
            }
        }
        posConstraint = "";
        rackRegExp = "";
    }

	string generateRegExp() {
        string startExp = "";
        string endExp = "";
        string midExp = "";

        int i = 0;
        try {
            while (posConstraint[i] == '*') {
                startExp += "[a-z]{0,1}";
                i++;
            }
            int startInd = i;
            i = posConstraint.length() - 1;
            while (posConstraint[i] == '*') {
                endExp += "[a-z]{0,1}";
                i--;
            }
            int endInd = i;
            for (int k = startInd; k <= endInd; k++ ) {
                if (posConstraint[k] == '*') {
                    midExp += "[a-z]";
                } else {
                    midExp += posConstraint[k];
                }
            }
        }
        catch (const std::regex_error& e) {
            std::cout << "regex_error caught: " << e.what() << '\n';
            if (e.code() == std::regex_constants::error_brack) {
                std::cout << "The code was error_back\n";
            }
        }

        return (startExp + midExp + endExp);
	}

	bool isMatchesRegularExpression(string word)
	{
	    std::cout<< "THE RACK REG EXP IS " << rackRegExp << endl << "AND THE WORD COMAPRED WITH IS " << word << endl;
	    string t = "";
	    try {
	        t = std::regex_match (word, std::regex(".."));
	    }
	    catch (const std::regex_error& e) {
            std::cout << "regex_error caught: " << e.what() << '\n';
            if (e.code() == std::regex_constants::error_brack) {
                std::cout << "The code was error_back\n";
            }
        }
        return false;
	}


public:
    ScrabbleWordSuggestor(ifstream& sowpodsFile)
    {
        generateSowpodsMap(sowpodsFile);
        this->rackRegExp = "";
    }

    void suggestWords(string rack)
    {
        generateScoredList(rack);
        int outputCount = 0;

        for ( map<int, vector<string> >::reverse_iterator r = scored_list.rbegin(); r != scored_list.rend() && outputCount < NUMBER_OF_OUTPUT; ++r, outputCount++ )
        {

            cout << r->first << "\t\t" ;
            for ( string s : r->second )
            {
                cout << s << " " ;
            }
            cout << endl;
        }
    }

    void addConstraint(string constraint)
    {
        posConstraint = constraint;
        addConstraintToRack();
        rackRegExp = generateRegExp();
	}
};

int main(int argc, char* argv[]) {
   ifstream sowpodsFile;
   string FILENAME = "sowpods.txt";

   try
   {
       sowpodsFile.open(FILENAME.c_str());
       ScrabbleWordSuggestor scrabble(sowpodsFile);
       //scrabble.suggestWords("apple*d");
       //cout << "======================================================================================================================" << endl;
       //cout << "======================================================================================================================" << endl;
       scrabble.suggestWords("or");
       scrabble.addConstraint("*u*");
       scrabble.suggestWords("or");
   }
    catch (std::ifstream::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    return 0;
}
