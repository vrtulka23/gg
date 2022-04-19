#include <string>  
#include <iostream>  
#include <sstream>  
#include <fstream>
#include <filesystem>
#include <vector>
#include "GGSettings.H"
#include "functions.H"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "yaml-cpp/yaml.h"
#include <stdlib.h>     /* exit, EXIT_FAILURE */

using namespace std;
namespace fs = std::filesystem;

GGSettings::GGSettings() {
  struct passwd *pw = getpwuid(getuid());
  dirHome = fs::path(pw->pw_dir);
  dirGG = dirHome/fs::path(".gg");
  fileSettings = dirGG/fs::path("settings.yaml");
  try {
    if (fs::exists(dirGG)) {
      isInitialized = true;
      if (!fs::exists(fileSettings)) {
	throw "GG settings file (~/.gg/settings.yaml) does not exits! Remove the old GG directory and setup a new one.";
      }
    }
  } catch (const char* msg) {
     cerr << msg << endl;
     exit(EXIT_FAILURE);
  }
}

string GGSettings::selectOption(std::string question, std::vector<string> options) {
  int max = options.size();
  std::vector<string> index;
  for (int i=0; i<max; i++) {
    cout << i << " = " << options[i] << endl;
    index.push_back(std::to_string(i));
  }
  int choice = prompt(question, index);
  return options[choice];
}

void GGSettings::initialize() {

  cout << endl;
  cout << tc("blue","STEP 0") << endl;
  
  std::vector<string> options;
  options.push_back("<new>");
  std::string pathProfiles = "./profiles";
  for (const auto & entry : fs::directory_iterator(pathProfiles)) {
    options.push_back(entry.path().filename());
  }
  cout << "Following profiles are available:" << endl;
  string choice = this->selectOption("Select profile:", options);
  if (choice=="<new>") {
    cout << tc("green","Input a new profile name:") << endl;
    cin >> profileName;
  } else {
    profileName = choice;
  }
  fs::path dirProfile = pathProfiles/fs::path(profileName);
  
  cout << endl;
  cout << tc("blue","STEP 1") << endl;
  
  if (isInitialized) {
    cout << "GG directory already exists" << endl;
    int choice = prompt("Do you want to overwrite it? (y/n)", {"n","y"});
    if (choice==1) {
      cout << "Old directory was removed and new will be created: " << dirGG << endl;
      fs::remove_all(dirGG);
    } else {
      cout << "Old directory will be used: " << dirGG << endl;
    }
  } else {
    cout << "New directory will be created: " << dirGG << endl;
  }

  cout << endl;
  cout << tc("blue","STEP 2") << endl;

  fs::path pathListBash[] = {
    dirHome / fs::path(".bash_aliases"),
    dirHome / fs::path(".bash_profile"),
    dirHome / fs::path(".bashrc"),
    dirHome / fs::path(".zshrc")
  };
  std::vector<string> pathFoundBash;
  for (int i=0; i<size(pathListBash); i++) {
    if (fs::exists(pathListBash[i])) {
      pathFoundBash.push_back(pathListBash[i]);
    }
  }
  if (pathFoundBash.size()>0) {
    cout << "Following shell files were found:" << endl;
    string choice = this->selectOption("Select shell script:", pathFoundBash);
    fileShell = choice;
  }

  cout << endl;
  cout << tc("blue","STEP 3") << endl;

  fs::path pathListEmacs[] = {
    dirHome / fs::path(".emacs"),
    dirHome / fs::path(".emacs.d/init.el")
  };
  std::vector<string> pathFoundEmacs;
  for (int i=0; i<size(pathListEmacs); i++) {
    if (fs::exists(pathListEmacs[i])) {
      pathFoundEmacs.push_back(pathListEmacs[i]);
    }
  }
  if (pathFoundEmacs.size()>0) {
    cout << "Following emacs files were found:" << endl;
    string choice = this->selectOption("Select emacs file", pathFoundEmacs);
    fileEmacs = choice;
  }

  cout << endl;
  cout << tc("blue","STEP 4") << endl;  

  cout << "Following settings were selected:" << endl;
  cout << "Profile:      " << profileName << endl;
  cout << "GG directory: " << dirGG << endl;
  cout << "Shell file:   " << fileShell << endl;
  cout << "Emacs file:   " << fileEmacs << endl;
  int correct = prompt("Continue? (y/n)", {"n","y"});
  if (correct==1) {

    cout << "GG directory created: " << dirGG << endl;
    fs::create_directory(dirGG);

    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "profileName";
    out << YAML::Value << profileName;
    out << YAML::Key << "dirGG";
    out << YAML::Value << dirGG;
    out << YAML::Key << "fileShell";
    out << YAML::Value << fileShell;
    out << YAML::Key << "fileEmacs";
    out << YAML::Value << fileEmacs;
    ofstream fout(fileSettings);
    fout << out.c_str();
    cout << "Settings saved to: " << fileSettings << endl;
    
    if (fs::exists(dirProfile)) {
      const auto copyOptions = fs::copy_options::update_existing | fs::copy_options::recursive;
      cout << "Copying profile settings to:" << endl;
      fs::path dirFromEmacs = dirProfile/fs::path("emacs");
      fs::path dirToEmacs = dirGG/fs::path("emacs");
      fs::copy(dirFromEmacs, dirToEmacs, copyOptions);
      cout << dirFromEmacs << " -> " << dirToEmacs << endl;
      fs::path dirFromShell = dirProfile/fs::path("shell");
      fs::path dirToShell = dirGG/fs::path("shell");
      fs::copy(dirFromShell, dirToShell, copyOptions);
      cout << dirFromShell << " -> " << dirToShell << endl;
    } else {
      
    }
  } else {
    cout << "Terminanig installation..." << endl;
  }
}
