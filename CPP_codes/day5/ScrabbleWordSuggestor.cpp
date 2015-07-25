#include "ScrabbleWordSuggestor.h"

using namespace std;



int ScrabbleWordSuggestor::getCharScore(char ch) {
        return ALPHABET_SCORE[ ch - 'a' ];
    }

    void ScrabbleWordSuggestor::generatePowerSetOfRack( string rack, set<string>& power_set ) {
        int set_size = rack.length();
        unsigned int pow_set_size = pow(2, set_size);
        int counter, j;
        string subset;

        for(counter = 1; counter < pow_set_size; counter++) {
            subset = "";

			int letterSelectCounter = counter;

            for(j = 0; j < set_size; j++) {
                bool selectable = letterSelectCounter % 2 == 1;
                if(selectable) {
                    subset += rack[j];
            	}
                letterSelectCounter /= 2;
            }
            power_set.insert(subset);
        }
    }

    void ScrabbleWordSuggestor::generateBlankReplacedPowerSet( set<string>& power_set, set< pair<string,int> >& power_set_score )
    {
        for ( string power_set_element : power_set )
        {
            replaceBlankTile( power_set_element, power_set_score );
        }
    }

    void ScrabbleWordSuggestor::replaceBlankTile( string rack, set< std::pair<string,int> >& set_of_racks )
    {
        replaceBlankTile( rack, 0, set_of_racks );
    }

    void ScrabbleWordSuggestor::replaceBlankTile( string rack, int scoreDeductionValue, set< std::pair<string,int> >& set_of_racks )
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

    string ScrabbleWordSuggestor::getSortedString(string word)
    {
        std::string sortedWord = word;
        std::sort(sortedWord.begin(), sortedWord.end());
        return sortedWord;
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

    void ScrabbleWordSuggestor::generateSowpodsMap(ifstream &file)
    {
        string word;
        while(getline(file, word))
        {
            insertInSowpodsMap(getSortedString(word), word);
        }
    }

    vector<string> ScrabbleWordSuggestor::getAnagramListFromSowpodsMap(string key)
    {
        vector<string> anagramList;
        if( sowpods.find(key) != sowpods.end() )
        {
            anagramList = sowpods.find( key )->second;
        }
        return anagramList;
    }

    int ScrabbleWordSuggestor::computeScore(string str, int scoreCompensation)
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

    void ScrabbleWordSuggestor::insertInScoredList(int score, string word)
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

    void ScrabbleWordSuggestor::generateScoredList()
    {
        set<string> powerSet;

        POWERSET_RACKS.clear();
        scored_list.clear();

        generatePowerSetOfRack(this->RACK_STRING, powerSet);
        generateBlankReplacedPowerSet(powerSet, POWERSET_RACKS);

        for ( pair<string,int> p : POWERSET_RACKS )
        {
            int score = computeScore( p.first, NO_SCORE_COMPENSATION );
            for ( string anagram : getAnagramListFromSowpodsMap( p.first ) ) {
                int scoreCompensation = p.second;
                if (this->rackRegExp.length() > 0) {
                    if (isMatchesRegularExpression(anagram)) {
                        insertInScoredList( score - scoreCompensation, anagram);
                    }
                } else {
                    insertInScoredList( score - scoreCompensation, anagram);
                }
            }
        }
    }

    void ScrabbleWordSuggestor::addConstraintToRack(string constraint) {
    	for(int index = 0; index < constraint.length(); index++) {
    		char letter = constraint.at(index);
    		if(letter != '*') {
    			this->RACK_STRING.push_back(letter);
            }
        }
    }

    void ScrabbleWordSuggestor::removeConstraintFromRack(string constraint) {
        for(int index = 0; index < constraint.length(); index++) {
            char letter = constraint.at(index);
            if(letter != '*') {
            	string::size_type index = this->RACK_STRING.find(letter);
            	if(index != string::npos)
    				this->RACK_STRING.erase(index, 1);
            }
        }
        rackRegExp = "";
    }

	string ScrabbleWordSuggestor::generateRegExp(string constraint) {
        string startExp = "";
        string endExp = "";
        string midExp = "";

        int i = 0;
        try {
            while (constraint[i] == '*') {
                startExp += ".{0,1}";
                i++;
            }
            int startInd = i;
            i = constraint.length() - 1;
            while (constraint[i] == '*') {
                endExp += ".{0,1}";
                i--;
            }
            int endInd = i;
            for (int k = startInd; k <= endInd; k++ ) {
                if (constraint[k] == '*') {
                    midExp += ".";
                } else {
                    midExp += constraint[k];
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

	bool ScrabbleWordSuggestor::isMatchesRegularExpression(string word)
	{
	    try {

	        return std::regex_match(word, std::regex(rackRegExp));
	    }
	    catch (const std::regex_error& e) {
            std::cout << "regex_error caught: " << e.what() << '\n';
            if (e.code() == std::regex_constants::error_brack) {
                std::cout << "The code was error_back\n";
            }
        }
	}



    ScrabbleWordSuggestor::ScrabbleWordSuggestor(string FILENAME)
    {
        ifstream sowpodsFile;

        sowpodsFile.open(FILENAME.c_str());
        generateSowpodsMap(sowpodsFile);
        this->rackRegExp = "";
    }

    string ScrabbleWordSuggestor::suggestWords(string rack, string constraint) {      // removed default argument ""
        string suggestWords="";
        this->RACK_STRING = rack;
        if (constraint != "") {
            addConstraint(constraint);
        }
        generateScoredList();
        int outputCount = 0;

        for ( map<int, vector<string> >::reverse_iterator r = scored_list.rbegin(); r != scored_list.rend() && outputCount < NUMBER_OF_OUTPUT; ++r, outputCount++ )
        {

            cout << r->first << " " ;
            for ( string s : r->second )
            {
                suggestWords+=s+" ";
            }
        }

        return suggestWords;
    }

    void ScrabbleWordSuggestor::addConstraint(string constraint)
    {
        addConstraintToRack(constraint);
        rackRegExp = generateRegExp(constraint);
	}

/*
int main(int argc, char* argv[]) {
   ifstream sowpodsFile;
   string FILENAME = "sowpods.txt";

   try
   {
       sowpodsFile.open(FILENAME.c_str());
       ScrabbleWordSuggestor scrabble(sowpodsFile);
       scrabble.suggestWords("babul", "*all");
   }
    catch (std::ifstream::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    return 0;
}
*/
