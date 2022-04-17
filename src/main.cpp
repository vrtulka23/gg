#include <string>  
#include <iostream>  
#include <sstream>  
#include <filesystem>
#include <vector>
#include "GG.H"

using namespace std;
namespace fs = std::filesystem;

class InputParser{
    public:
        InputParser (int &argc, char **argv){
            for (int i=1; i < argc; ++i)
                this->tokens.push_back(std::string(argv[i]));
        }
        const std::string& getCmdOption(const std::string &option) const{
            std::vector<std::string>::const_iterator itr;
            itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
            if (itr != this->tokens.end() && ++itr != this->tokens.end()){
                return *itr;
            }
            static const std::string empty_string("");
            return empty_string;
        }
        bool cmdOptionExists(const std::string &option) const{
            return std::find(this->tokens.begin(), this->tokens.end(), option)
                   != this->tokens.end();
        }
    private:
        std::vector <std::string> tokens;
};

int main(int argc, char **argv)
{
  
  GG gg;

  InputParser input(argc, argv);
  if(input.cmdOptionExists("-i")||input.cmdOptionExists("--init")) {
    gg.initialize();
  }
  //const std::string &filename = input.getCmdOption("-f");
  //if (!filename.empty()){
    // Do interesting things ...
  //}
  return 0;
  
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
