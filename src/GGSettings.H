#include <string>  
#include <iostream>  
#include <sstream>  
#include <filesystem>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

class GGSettings {
public:
  std::string profileName;
  fs::path dirHome;            // Home directory of the current user
  fs::path dirGG;              // Directory of the GG, usually $HOME/.gg
  fs::path fileSettings;       // GG settings file
  fs::path fileShell;          // Path of the shell settings (e.g. .bashrc)
  fs::path fileEmacs;          // Path of the Emacs settings (e.g. .emacs.d/init.el)
  bool isInitialized = false;  // Was GG previously initialized?
  
  GGSettings();              // Settings class
  void initialize();         // Initialization 
  
private:
  string selectOption(std::string question, std::vector<string> options);
};
