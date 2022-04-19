# Installation

## On Mac OS

* Install yaml-cpp (https://codedocs.xyz/jbeder/yaml-cpp/index.html)
  '''
  brew install yaml-cpp
  '''
* Set correct include paths in the Makefile
  '''
  INC := -I /opt/homebrew/include
  LIB := -L /opt/homebrew/lib -lyaml-cpp
  '''