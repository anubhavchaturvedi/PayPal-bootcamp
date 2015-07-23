#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

const string EMPTY_TILE = "*";

const int ALPHABET_SCORE[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20, 21,22,23,24,25,26};

class ScrabbleWordHelper {

public:
    map< string, vector<string> > sowpods;
    map< int, vector<string> > scored_list;
    set < pair<string,int> > POWERSET_RACKS;
public:
    string RACK_STRING;

    ScrabbleWordHelper(string rack, ifstream& sowpodsFile) {
        this->RACK_STRING = rack;
        set<string> powerSet;
        generatePowerSetOfRack(rack, powerSet);
        generateBlankReplacedPowerSet(powerSet, POWERSET_RACKS);
        generateSowpodsMap(sowpodsFile);
    }

    int getCharScore(char ch) {
        return ALPHABET_SCORE[ ch - 'a' ];
    }

    void generatePowerSetOfRack( string rack, set<string>& power_set ) {
        int set_size = rack.length();
        unsigned int pow_set_size = pow(2, set_size);
        int counter, j;
        string subset;

        for(counter = 1; counter < pow_set_size; counter++) {
            subset = "";
            for(j = 0; j < set_size; j++) {
                if(counter & (1<<j))
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
            set_of_racks.insert( pair<string,int> (rack, scoreDeductionValue) );
        }
    }

    std::pair<string, string> getSortedString(string word) {
        std::string sortedWord = word;
        std::sort(sortedWord.begin(), sortedWord.end());
        return std::pair<string, string> (sortedWord, word);
    }

    void insertInMap(std::pair<string, string> entry) {
        map<string, vector<string> >::iterator it = sowpods.begin();

        if( sowpods.count(entry.first) ) {
            it = sowpods.find( entry.first );
            (it->second).push_back(entry.second);
        }

        else {
            vector<string> newVector;
            newVector.push_back(entry.second);
            sowpods.insert ( std::pair<string, vector<string> >(entry.first, newVector) );
        }
    }

    void generateSowpodsMap(ifstream &file) {
        string word;
        while(getline(file, word)) {
            insertInMap(getSortedString(word));
        }
    }

    vector<string> findInSowpodsMap(string key) {
        vector<string> x;
        //if(sowpods.find(key))
        //return sowpods.find( key ) ==  ? return sowpods.find( key ) -> second : x;
    }
};

bool openFile(string filename, ifstream& file) {
    file.open(filename.c_str());
    bool fileExists = file.is_open();
    if ( !fileExists ) {
        cout << "unable to open file" ;
    }
    return fileExists;
}

int main(int argc, char* argv[]) {
    ifstream file;
    string FILENAME = "sowpods.txt";
    if ( openFile(FILENAME,file)) {
        ScrabbleWordHelper scrabble("ab*", file);
        for ( pair<string,int> r : scrabble.POWERSET_RACKS ) {
            cout << "( " << r.first << " , " << r.second << " )" << endl;
        }

        cout << "finish";
    }
    return 0;
}
