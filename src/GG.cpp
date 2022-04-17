#include <string>  
#include <iostream>  
#include <sstream>  
#include <filesystem>
#include <vector>
#include "GG.H"

using namespace std;
namespace fs = std::filesystem;

GG::GG() {
}

void GG::initialize() {
  settings.initialize();
}

