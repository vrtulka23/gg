#include <iostream>

using namespace std;

string tc(string color, string text)
{
  if (color=="red") {
    return "\x1B[31m"+text+"\033[0m";
  } else if (color=="green") {
    return "\x1B[32m"+text+"\033[0m";
  } else if (color=="blue") {
    return "\x1B[34m"+text+"\033[0m";
  }
  return text;
}

int prompt(string question, std::vector<string> options)
{
  string choice;
  int found = 0;
  int index;
  do
    {
      cout << tc("green",question) << endl;
      cin >> choice;
      auto itr = std::find(options.begin(), options.end(), choice);
      index = std::distance(options.begin(), itr);
      if ( index < options.size() )
	found = 1;
    }
  while( !cin.fail() && found==0 );
  return index;
}
