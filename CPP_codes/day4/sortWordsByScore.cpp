#include<iostream>
#include<map>
#include<string>
#include <fstream>
#include <sstream>
using namespace std;
#define SPACE_DELIMITER " "

const int ALPHABET_SCORE[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20, 21,22,23,24,25,26};

bool openFile(string filename, ifstream& file)
{
    file.open(filename.c_str());
    bool fileExists = file.is_open();
    if ( !fileExists ) {
        cout << "unable to open file" ;
    }
    return fileExists;
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

void writeMapToFile(map<int, string> wordValue) {
	int count = 0;
  map<int, string>::iterator it = wordValue.begin();
  ofstream outFile ("wordValue.txt");
  if (outFile.is_open()){
    for (it=wordValue.begin(); it!=wordValue.end(); ++it) {
    		count ++;
    		outFile << it->second << '\n';
    }
    outFile.close();
    cout<< count <<" words written to file";
  }
  else{
    cout << "Unable to open file";
  } 	
}

void pushFileContentToMap(ifstream &file, map<int, string> &valueWord)
{
    string word;
    while(getline(file,word))
    {
        insertInMap(computeScore(word), valueWord);
    }
    writeMapToFile(valueWord);
}

int main(int argc, char *argv[])
{
	map<int, string> valueWord;
    if (argc < 2)
    {
        cout << "enter the file name";
        return 0;
    }

    ifstream file;

    if (openFile(argv[1], file))
    {
    	cout<<"file opened";
        pushFileContentToMap(file, valueWord);
    }
    else
    {
        cout << "file not opened";
    }
}

