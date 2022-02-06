#include <string>  
#include <iostream>  
#include <sstream>  
#include <filesystem>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

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

class GG {
  public: 
  fs::path dirHome;
  fs::path dirGG;
  fs::path fileShell;
  fs::path fileEmacs;

  GG() {
    cout << tc("red","Welcome to the GG setup!") << endl;
    dirHome = getenv("HOME");
    dirGG = dirHome / fs::path(".gg");

    this->initDir();
    this->determineShell();
    this->determineEmacs();
  }

  void initDir();
  void determineShell();
  void determineEmacs();
};

void GG::initDir() {
  int choice;
  cout << endl;
  cout << tc("blue","STEP 1") << endl;
  if (fs::exists(dirGG)) {
    cout << "GG directory already exists" << endl;
    int choice = prompt("Do you want to overwrite it? (y/n)", {"n","y"});
    if (choice==1) {
      cout << "New directory was created" << endl;
      fs::remove_all(dirGG);
      fs::create_directory(dirGG);
    } else {
      cout << "Old directory is used" << endl;
    }
  } else {
    cout << "New directory was created" << endl;
    fs::create_directory(dirGG);
  }
}

void GG::determineShell() {
  fs::path pathList[] = {
    dirHome / fs::path(".bash_aliases"),
    dirHome / fs::path(".bash_profile"),
    dirHome / fs::path(".bashrc"),
    dirHome / fs::path(".zshrc")
  };
  std::vector<fs::path> pathFound;
  cout << endl;
  cout << tc("blue","STEP 2") << endl;
  cout << "Following shell files were found:" << endl;
  for (int i=0; i<size(pathList); i++) {
    if (fs::exists(pathList[i])) {
      pathFound.push_back(pathList[i]);
      cout << pathFound.size() << ") " << pathList[i] << endl;
    }
  }
  if (pathFound.size()>0) {
    int max = pathFound.size();
    std::vector<string> options;
    for (int i=0; i<max; i++)
      options.push_back(std::to_string(i+1));
    int choice = prompt("Which one to use? (1-"+std::to_string(max)+")", options);
    fileShell = pathFound[choice];
  }
}

void GG::determineEmacs() {
  fs::path pathList[] = {
    dirHome / fs::path(".emacs"),
    dirHome / fs::path(".emacs.d/init.el")
  };
  std::vector<fs::path> pathFound;
  cout << endl;
  cout << tc("blue","STEP 3") << endl;
  cout << "Following emacs files were found:" << endl;
  for (int i=0; i<size(pathList); i++) {
    if (fs::exists(pathList[i])) {
      pathFound.push_back(pathList[i]);
      cout << pathFound.size() << ") " << pathList[i] << endl;
    }
  }
  if (pathFound.size()>0) {
    int max = pathFound.size();
    std::vector<string> options;
    for (int i=0; i<max; i++)
      options.push_back(std::to_string(i+1));
    int choice = prompt("Which one to use? (1-"+std::to_string(max)+")", options);
    fileEmacs = pathFound[choice];
  }
}

int main(int argc, char *argv[])
{

  GG gg;
  
  /*
  string ggDir = "~/.sestos";
  
  cout << "Please input name of this machine:\n";
  string machineName;
  cin >> machineName;
  cout << machineName << "\n";

  fs::path pathToShow("/Users/perseus/Projects/gg");
  cout << pathToShow << endl;
  cout << "exists() = " << fs::exists(pathToShow) << "\n"
     << "root_name() = " << pathToShow.root_name() << "\n"
     << "root_path() = " << pathToShow.root_path() << "\n"
     << "relative_path() = " << pathToShow.relative_path() << "\n"
     << "parent_path() = " << pathToShow.parent_path() << "\n"
     << "filename() = " << pathToShow.filename() << "\n"
     << "stem() = " << pathToShow.stem() << "\n"
     << "extension() = " << pathToShow.extension() << "\n";

  //char const* home = getenv("HOME");
  fs::path home(getenv("HOME"));
  cout << home << endl;
  cout << "exists() = " << fs::exists(home) << "\n";
  
  fs::path pathToShow1(".bashrc");
  cout << home / pathToShow1 << endl;
  cout << "exists() = " << fs::exists(home/pathToShow1) << "\n";

  fs::path pathToShow2(".zshrc");
  cout << home / pathToShow2 << endl;
  cout << "exists() = " << fs::exists(home/pathToShow2) << "\n";
  */
  
}
