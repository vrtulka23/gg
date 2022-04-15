#include <string>  
#include <iostream>  
#include <sstream>  
#include <filesystem>
#include <vector>
#include "initialize.H"
#include "functions.H"

using namespace std;
namespace fs = std::filesystem;

Initialize::Initialize() {
  cout << tc("red","Welcome to the GG setup!") << endl;
  dirHome = getenv("HOME");
  dirGG = dirHome / fs::path(".gg");
  
  this->selectProfile();
  this->initDir();
  this->determineShell();
  this->determineEmacs();
  
  cout << endl;
  cout << "Profile:     " << profileName << endl;
  cout << "Home folder: " << dirHome << endl;
  cout << "GG folder:   " << dirGG << endl;
  cout << "Shell file:  " << fileShell << endl;
  cout << "Emacs file:  " << fileEmacs << endl;
}

string Initialize::selectOption(std::string question, std::vector<string> options) {
  int max = options.size();
  std::vector<string> index;
  for (int i=0; i<max; i++) {
    cout << i << " = " << options[i] << endl;
    index.push_back(std::to_string(i));
  }
  int choice = prompt(question, index);
  return options[choice];
}

void Initialize::selectProfile() {
  cout << endl;
  cout << tc("blue","STEP 0") << endl;
  std::vector<string> options;
  options.push_back("<new>");
  std::string path = "./profiles";
  for (const auto & entry : fs::directory_iterator(path)) {
    options.push_back(entry.path().filename());
  }
  cout << "Following profiles are available:" << endl;
  string choice = this->selectOption("Select profile:", options);
  if (choice=="<new>") {
    cout << tc("green","Input a new profile name:") << endl;
    cin >> profileName;
    fs::create_directory(path/fs::path(profileName));
  } else {
    profileName = choice;
  }
}

void Initialize::initDir() {
  cout << endl;
  cout << tc("blue","STEP 1") << endl;
  if (fs::exists(dirGG)) {
    cout << "GG directory already exists" << endl;
    int choice = prompt("Do you want to overwrite it? (y/n)", {"n","y"});
    if (choice==1) {
      cout << "New directory was created: " << dirGG << endl;
      fs::remove_all(dirGG);
      fs::create_directory(dirGG);
    } else {
      cout << "Old directory is used: " << dirGG << endl;
    }
  } else {
    cout << "New directory was created: " << dirGG << endl;
    fs::create_directory(dirGG);
  }
}

void Initialize::determineShell() {
  fs::path pathList[] = {
    dirHome / fs::path(".bash_aliases"),
    dirHome / fs::path(".bash_profile"),
    dirHome / fs::path(".bashrc"),
    dirHome / fs::path(".zshrc")
  };
  std::vector<string> pathFound;
  for (int i=0; i<size(pathList); i++) {
    if (fs::exists(pathList[i])) {
      pathFound.push_back(pathList[i]);
    }
  }

  cout << endl;
  cout << tc("blue","STEP 2") << endl;
  if (pathFound.size()>0) {
    cout << "Following shell files were found:" << endl;
    string choice = this->selectOption("Select shell script:", pathFound);
    fileShell = choice;
  }
}

void Initialize::determineEmacs() {
  fs::path pathList[] = {
    dirHome / fs::path(".emacs"),
    dirHome / fs::path(".emacs.d/init.el")
  };
  std::vector<string> pathFound;
  for (int i=0; i<size(pathList); i++) {
    if (fs::exists(pathList[i])) {
      pathFound.push_back(pathList[i]);
    }
  }

  cout << endl;
  cout << tc("blue","STEP 3") << endl;
  if (pathFound.size()>0) {
    cout << "Following emacs files were found:" << endl;
    string choice = this->selectOption("Select emacs file", pathFound);
    fileEmacs = choice;
  }
}
