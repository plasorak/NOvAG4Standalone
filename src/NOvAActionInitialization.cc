//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file NOvAActionInitialization.cc
/// \brief Implementation of the NOvAActionInitialization class

#include "NOvAActionInitialization.hh"
#include "NOvAPrimaryGeneratorAction.hh"
#include "NOvARunAction.hh"
#include "NOvAEventAction.hh"
#include "NOvASteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NOvAActionInitialization::NOvAActionInitialization(NOvADetectorConstruction* det):
  G4VUserActionInitialization(),
  fDet(det) {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NOvAActionInitialization::~NOvAActionInitialization() { }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NOvAActionInitialization::Build() const {
  SetUserAction(new NOvAPrimaryGeneratorAction);
  
  NOvARunAction* runAction = new NOvARunAction;
  SetUserAction(runAction);
  runAction->SetHistFileName("hist_file.root");
  std::cout << "\033[32myay\033[0m\n";
  NOvAEventAction* eventAction = new NOvAEventAction(runAction);
  SetUserAction(eventAction);

  NOvASteppingAction* steppingAction = new NOvASteppingAction(fDet, eventAction);
  SetUserAction(steppingAction);
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
