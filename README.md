# NOvA standalone GEANT4 simulation

A simple implementation of GEANT4 with NOvA geometry, maybe that helps us understanding why G4 sometimes aborts the event.

## Installation
Make sure you have G4 installed and source and all the libraries `G4*DATA` in your path (on OSX, if you have homebrew, you can simply do `brew install geant4` and follow along what it tells you to do), then:
```
mkdir build
cd build
cmake ../
make
```
You should now have the executable `build/standalone_NOvA`.

## Running
```
./standalone_NOvA run1.mac
```
Somehow that gives a seg fault at the end, not sure what the reason is.

This will just generate an electron neutrino of energy, position and direction defined in `src/NOvAPrimaryGeneratorAction.cc` (or in the `run1.mac`? no clue what is overiding what here).
If you want to change that position, edit this file, and recompile with `make`.


