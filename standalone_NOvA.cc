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
/// \file standalone_NOvA.cc
/// \brief Main program of the NOvA example

#include "NOvADetectorConstruction.hh"
#include "NOvAActionInitialization.hh"
#include "NOvAPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QBBC.hh"
#include "AltG4PhysListFactory.hh"   // alternative version in "alt" namespace
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "PrimaryGeneratorAction.hh"

#include "NOvARunAction.hh"
#include "NOvAEventAction.hh"
#include "NOvASteppingAction.hh"

#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv) {
  G4String gdmlname = "fardet-12x12-28block-xtru-vacuum-stagger-pivoter.gdml";
  G4String hfname   = "g4sa.root";
  G4String plname   = "QGSP_BERT";

  G4RunManager* runManager = new G4RunManager;

  // G4VUserDetectorConstruction* detector = nullptr;
  // detector = new NOvADetectorConstruction();
  // runManager->SetUserInitialization(detector);

  NOvADetectorConstruction* detector = new NOvADetectorConstruction;
  runManager->SetUserInitialization(detector);
  
  alt::G4PhysListFactory* factory = new alt::G4PhysListFactory();
  G4VModularPhysicsList* physics = factory->GetReferencePhysList("QGSP_BERT");
  if (physics) {
    runManager->SetUserInitialization(physics);
  } else {
    factory->PrintAvailableLists();
    abort();
  }

  // //
  // NOvARunAction* run_action = new NOvARunAction;  
  // runManager->SetUserAction(run_action);
  // run_action->SetHistFileName(hfname);
  // //
  // NOvAEventAction* event_action = new NOvAEventAction(run_action);
  // runManager->SetUserAction(event_action);
  // //
  // NOvASteppingAction* stepping_action = new NOvASteppingAction(detector, event_action);
  // runManager->SetUserAction(stepping_action);
  
  runManager->SetUserAction(new NOvAPrimaryGeneratorAction);
  //runManager->SetUserAction(new PrimaryGeneratorAction(detector));
  
  NOvARunAction* runAction = new NOvARunAction;
  runManager->SetUserAction(runAction);
  runAction->SetHistFileName("hist_file.root");

  NOvAEventAction* eventAction = new NOvAEventAction(runAction);
  runManager->SetUserAction(eventAction);

  NOvASteppingAction* steppingAction = new NOvASteppingAction(detector, eventAction);
  runManager->SetUserAction(steppingAction);

  //runManager->SetUserInitialization(new NOvAActionInitialization(detector));
  
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  G4String command = "/control/execute ";
  G4String fileName = argv[1];
  UImanager->ApplyCommand(command+fileName);
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
