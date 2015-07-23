#include <iostream>
#include <string>

using namespace std;

const int ALPHABET_SCORE[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20, 21,22,23,24,25,26};

int computeScore(string str) {
    int score = 0;
    //for ( char& ch : str ) {
    for ( int i = 0; i < str.length(); i++ ) {
        char ch = str[i];
        if ( 'a' <= ch && ch <= 'z' ) {
            score += ALPHABET_SCORE[ ch - 'a' ];
        }
    }
    return score;
}

bool checkFileExistence(const string& fileName)
{
    ifstream f(fileName.c_str());
    return f.is_open();
}

void openFile(string filename, ifstream& file)
{
    const bool file_exists = checkFileExistence(filename);
    if (!file_exists) {
        cout<<"\n unable to open file";
    }
    file.open(filename.c_str());
}

void insertIntoMap(int score, string word)
{

}

void pushFileContentToMap(ifstream &file)
{
    string word;
    while(getline(file,word))
    {
        //compute score here for each word and put the word into the map
    }
}

int main() {
    std::pair<int,string> result = computeScore("abc");
    cout << result.first << result.second << endl;

    return 0;
}
