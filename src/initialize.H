#include <string>  
#include <iostream>  
#include <filesystem>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

class Initialize {
public:
  std::string profileName;
  fs::path dirHome;
  fs::path dirGG;
  fs::path fileShell;
  fs::path fileEmacs;

  Initialize();
  void selectProfile();
  void initDir();
  void determineShell();
  void determineEmacs();
  
private:
  string selectOption(std::string question, std::vector<string> options);
};
