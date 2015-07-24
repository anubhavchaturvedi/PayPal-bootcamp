#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

const string EMPTY_TILE = "*";
const int NO_SCORE_COMPENSATION = 0;
const int MAX_RACK_LENGTH = 7;

const int ALPHABET_SCORE[] = {1,3,3,2, 1,4,2,4, 1,8,5,1,3, 1,1,3,10, 1,1,1,1, 4,4,8,4, 10};

class ScrabbleWordSuggestor {

private:
    map< string, vector<string> > sowpods;
    map< int, vector<string> > scored_list;
    set < pair<string,int> > POWERSET_RACKS;
    string RACK_STRING;

private:
    int getCharScore(char ch) {
        return ALPHABET_SCORE[ ch - 'a' ];
    }

    void generatePowerSetOfRack( string rack, set<string>& power_set ) {
        int set_size = rack.length();
        unsigned int pow_set_size = pow(2, set_size);
        int counter, j;
        string subset;
        int multiplicationFactor;

        for(counter = 1; counter < pow_set_size; counter++) {
            subset = "";


            for(j = 0; j < set_size; j++) {
                multiplicationFactor = pow (2, j);
                if(counter & (1 * multiplicationFactor))
                    subset += rack[j];
            }
            power_set.insert(subset);
        }
    }

    void generateBlankReplacedPowerSet( set<string>& power_set, set< pair<string,int> >& power_set_score ) {
        for ( string power_set_element : power_set ) {
            replaceBlankTile( power_set_element, power_set_score );
        }
    }

    void replaceBlankTile( string rack, set< std::pair<string,int> >& set_of_racks ) {
        replaceBlankTile( rack, 0, set_of_racks );
    }

    void replaceBlankTile( string rack, int scoreDeductionValue, set< std::pair<string,int> >& set_of_racks ) {
        int rackBlankTileIndex = rack.find(EMPTY_TILE);
        if ( rackBlankTileIndex >= 0 ) {
            for ( char ch = 'a'; ch <='z'; ch++ ) {
                rack[rackBlankTileIndex] = ch;
                int newScoreDectionValue = scoreDeductionValue + getCharScore(ch);
                replaceBlankTile( rack, newScoreDectionValue, set_of_racks);
            }
        } else {
            set_of_racks.insert( pair<string,int> ( getSortedString(rack), scoreDeductionValue) );
        }
    }

    string getSortedString(string word) {
        std::string sortedWord = word;
        std::sort(sortedWord.begin(), sortedWord.end());
        return sortedWord;
    }

    void insertInMap(string key, string value) {
        map<string, vector<string> >::iterator it = sowpods.begin();

        if( sowpods.count(key) ) {
            it = sowpods.find( key );
            (it->second).push_back(value);
        }

        else {
            vector<string> newVector;
            newVector.push_back(value);
            sowpods.insert ( std::pair<string, vector<string> >( key, newVector) );
        }
    }

    void generateSowpodsMap(ifstream &file) {
        string word;
        while(getline(file, word)) {
            if ( word.length() <= MAX_RACK_LENGTH ) {
                insertInMap(getSortedString(word), word);
            }
        }
    }

    vector<string> findInSowpodsMap(string key) {
        vector<string> x;
        if( sowpods.find(key) != sowpods.end() ) {
            return sowpods.find( key )->second;
        }
        vector<string> a;
        return a;
    }

    int computeScore(string str, int scoreCompensation) {
        int score = 0;
        for ( int i = 0; i < str.length(); i++ ) {
            char ch = str[i];
            if ( 'a' <= ch && ch <= 'z' ) {
                score += ALPHABET_SCORE[ ch - 'a' ];
            }
        }
        return score - scoreCompensation;;
    }

    void insertInScoredList(int score, string word) {
        map<int, vector<string> >::iterator it = scored_list.begin();
        if ( scored_list.find(score) != scored_list.end() ) {
            it = scored_list.find( score );
            (it->second).push_back(word);
        } else {
            vector<string> newVector;
            newVector.push_back(word);
            scored_list.insert ( std::pair<int, vector<string> >(score, newVector) );
        }
    }

    void generateScoredList(string rack) {
        this->RACK_STRING = rack;
        set<string> powerSet;

        POWERSET_RACKS.clear();
        scored_list.clear();

        generatePowerSetOfRack(rack, powerSet);
        generateBlankReplacedPowerSet(powerSet, POWERSET_RACKS);

        for ( pair<string,int> p : POWERSET_RACKS ) {
            int score = computeScore( p.first, NO_SCORE_COMPENSATION );
            for ( string anagram : findInSowpodsMap( p.first ) ) {
                int scoreCompensation = p.second;
                insertInScoredList( score - scoreCompensation, anagram);
            }
        }
    }

    string setRegularExpression(string constraint)
    {
    	string regularExpression="";
    	for(int i=0;i<constraint.length();i++)
    	{
    	if(constraint[i]=='*')
    		regularExpression+="[a-z]{0,1}";
    	else
    		regularExpression+=constraint[i];
    		
		}
    	return regularExpression;
	}

	bool matchesRegularExpression(string word,string regularExpression)
	{
		return regex_match (word, regex(regularExpression));
	}

public:
    ScrabbleWordSuggestor(ifstream& sowpodsFile) {
        generateSowpodsMap(sowpodsFile);
    }

    void suggestWords(string rack){
        generateScoredList(rack);
        for ( map<int, vector<string> >::reverse_iterator r = scored_list.rbegin(); r != scored_list.rend(); ++r ) {

            cout << r->first << "\t\t" ;
            for ( string s : r->second ) {
                cout << s << " " ;
            }
            cout << endl;
        }
    }
};

int main(int argc, char* argv[]) {
   ifstream sowpodsFile;
   string FILENAME = "sowpods.txt";

   try
   {
       sowpodsFile.open(FILENAME.c_str());
       ScrabbleWordSuggestor scrabble(sowpodsFile);
       scrabble.suggestWords("apple*d");
       cout << "======================================================================================================================" << endl;
       cout << "======================================================================================================================" << endl;
       scrabble.suggestWords("abcdef");
   }
    catch (std::ifstream::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
 	}
   return 0;
}
