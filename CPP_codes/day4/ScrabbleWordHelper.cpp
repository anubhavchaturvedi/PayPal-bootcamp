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

class scrabbleWordHelper {
private:
    std::map<string,vector<string> > sowpods;
    set <string> rackSubset;
public:
    string rack;

    ScrabbleWordHelper(string rack)	{
        this->rack = rack;
    }

    void findRackSubset(void) {
        int set_size = rack.length();
        unsigned int pow_set_size = pow(2, set_size);
        int counter, j;
        string subset;

        for(counter = 0; counter < pow_set_size; counter++) {
            subset = "";
            for(j = 0; j < set_size; j++) {
                if(counter & (1<<j))
                    subset += rack[j];
            }
            rackSubset.insert(subset);
        }

        for(set<string>::iterator it=rackSubset.begin(); it!=rackSubset.end(); ++it) {
            cout << *it << endl;
        }
    }

    void replaceBlankTile( string rack, vector<string>& listOfRacks ) {
        int rackBlankTileIndex = rack.find(EMPTY_TILE);
        if ( rackBlankTileIndex >= 0 ) {
            for ( char ch = 'a'; ch <='z'; ch++ ) {
                replaceBlankTile( rack.replace(rackBlankTileIndex, ch), listOfRacks);
            }
        } else {
            listOfRacks.push_back(rack);
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
            cout << "\nKey Exists : " << entry.first << " adding " << entry.second << " to vector.";
        }

        else {
            vector<string> newVector;
            newVector.push_back(entry.second);
            sowpods.insert ( std::pair<string, vector<string> >(entry.first, newVector) );
            cout << "\nNew Key : " << entry.first;
        }
    }

    void generateSowpodsMap(ifstream &file) {
        string word;
        while(getline(file, word)) {
            insertInMap(getSortedString(word));
        }
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
    scrabbleWordHelper scrabble;

    if (argc < 2) {
        cout << "enter the file name";
        return 0;
    }

    ifstream file;

    if (openFile(argv[1], file)) {
        cout<<"file opened";
        scrabble.generateSowpodsMap(file);
    }

    else {
        cout << "file not opened";
    }

    return 0;
}
