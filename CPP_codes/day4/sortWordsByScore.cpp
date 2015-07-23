#include<iostream>
#include<map>
#include<string>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
#define SPACE_DELIMITER " "

const int ALPHABET_SCORE[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20, 21,22,23,24,25,26};


void displayMap(std::map<int, string> wordValue) {
	std::map<int, string>::iterator it = wordValue.begin();
	std::cout << "\nMap contains:\n";
	for (it=wordValue.begin(); it!=wordValue.end(); ++it) {
  			std::cout << it->first << " => " << it->second << '\n';
	}
}

void writeMapToFile(map<int, string> wordValue) {
	int count = 0;
  map<int, string>::iterator it = wordValue.end();
  ofstream outFile ("wordValue.txt");
  if (outFile.is_open()){
    for (it=wordValue.end(); it!=wordValue.begin(); --it) {
    	if((it->second).find_first_of(SPACE_DELIMITER) < (it->second).length()) {
    		count ++;
    		outFile << it->second << '\n';
		}
    }
    outFile.close();
    cout<< count <<" words written to file";
  }
  else{
    cout << "Unable to open file";
  } 	
}

void insertInMap(std::pair<int, string> currentPair, map<int, string> &valueWord) {
  
  map<int, string>::iterator it = valueWord.begin();
	
  if( valueWord.count(currentPair.first) ) {
    it = valueWord.find( currentPair.first );
    it -> second = it->second + SPACE_DELIMITER + currentPair.second;
  }
  else {
    valueWord.insert ( std::pair<int, string>(currentPair.first, currentPair.second));
  }
}

std::pair<int,string> computeScore(string str) {
    int score = 0;
    for ( int i = 0; i < str.length(); i++ ) {
        char ch = str[i];
        if ( 'a' <= ch && ch <= 'z' ) {
            score += ALPHABET_SCORE[ ch - 'a' ];
        }
    }
    return std::pair<int,string> ( score, str );
}

int main() {
	map<int, string> valueWord;
	insertInMap(computeScore("hello"), valueWord);
	insertInMap(computeScore("jello"), valueWord);
	insertInMap(computeScore("garvit"), valueWord);
	insertInMap(computeScore("jain"), valueWord);
	insertInMap(computeScore("hello"), valueWord);
	displayMap(valueWord);
	//writeMapToFile(valueWord);
	return 0;
}
