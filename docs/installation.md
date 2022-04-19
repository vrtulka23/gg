# Installation

## On Mac OS

* Go to App Store, install Xcode and upgrade cmake
  '''
  sudo xcodebuild -license accept
  brew upgrade cmake
  '''
* Clone and install yaml-cpp (https://codedocs.xyz/jbeder/yaml-cpp/index.html)
  '''
  git clone https://github.com/jbeder/yaml-cpp.git
  mkdir yaml-cpp/build
  cd yaml-cpp/build
  cmake -G Xcode ..
  '''