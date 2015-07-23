#include <iostream>
#include <set>
#include <math.h>

using namespace std;

class ScrabbleWordHelper
{
private:
    set <string> rackSubStringSet;
public:
    string rack;

    void findRackSubstring();
    ScrabbleWordHelper(string rack);

};

ScrabbleWordHelper::ScrabbleWordHelper(string rack)
{
    this->rack = rack;
}

void  ScrabbleWordHelper::findRackSubstring(void)
{

    int set_size = rack.length();
    unsigned int pow_set_size = pow(2, set_size);
    int counter, j;
    string subset;


    for(counter = 0; counter < pow_set_size; counter++)
    {
      subset = "";
      for(j = 0; j < set_size; j++)
       {
          if(counter & (1<<j))
            subset += rack[j];
       }
        rackSubStringSet.insert(subset);
    }

    for(set<string>::iterator it=rackSubStringSet.begin(); it!=rackSubStringSet.end(); ++it)
    {
        cout << *it << endl;
    }
}

int main(int argc, char *argv[])
{
   ScrabbleWordHelper scrabbleWordHelper("abcdef");
   scrabbleWordHelper.findRackSubstring();



}
