#include <iostream>
#include <string>

using namespace std;

const int ALPHABET_SCORE[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20, 21,22,23,24,25,26};

std::pair<int,string> computeScore(string str) {
    int score = 0;
    //for ( char& ch : str ) {
    for ( int i = 0; i < str.length(); i++ ) {
        char ch = str[i];
        if ( 'a' <= ch && ch <= 'z' ) {
            score += ALPHABET_SCORE[ ch - 'a' ];
        }
    }
    return std::pair<int,string> ( score, str );
}

int main() {
    std::pair<int,string> result = computeScore("abc");
    cout << result.first << result.second << endl;

    return 0;
}
