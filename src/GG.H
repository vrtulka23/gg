#include <string>  
#include <iostream>  
#include <filesystem>
#include <vector>
#include "GGSettings.H"

using namespace std;
namespace fs = std::filesystem;

class GG {
public:
  GG();
  void initialize();
private:
  GGSettings settings;
};
