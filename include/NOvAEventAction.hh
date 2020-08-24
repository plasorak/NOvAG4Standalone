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
// $Id: NOvAEventAction.hh,v 1.1.1.1 2011-12-06 17:49:39 rhatcher Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef NOvAEventAction_h
#define NOvAEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include "G4ThreeVector.hh"

#include "TH1F.h"

class NOvARunAction;
class NOvAEventActionMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NOvAEventAction : public G4UserEventAction {
public:
  NOvAEventAction(NOvARunAction*);
  virtual ~NOvAEventAction();

  void  BeginOfEventAction(const G4Event*);
  void    EndOfEventAction(const G4Event*);
  
  const G4ThreeVector& getRayOrigin() { return rayOrigin; }
  const G4ThreeVector& getRayDircos() { return rayDircos; }
  
  void AddE(G4double de, G4double r);
                     
  void SetPrintModulo(G4int    val)  {printModulo = val;};
    
private:
  NOvARunAction*  runAct;

  G4ThreeVector rayOrigin;
  G4ThreeVector rayDircos;

  TH1F* fOneEvtTransverseProfile;
  G4double  fSumE, fSumRE;

  G4int     printModulo;
                             
  NOvAEventActionMessenger*  eventMessenger;
  std::atomic<int> nonAbortedCount = {0};
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
