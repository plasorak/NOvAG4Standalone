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
// $Id: PrimaryGeneratorAction.hh,v 1.1.1.1 2011-12-06 17:49:39 rhatcher Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

#include "G4ThreeVector.hh"

class G4ParticleGun;
class G4Event;
class G4VUserDetectorConstruction;
class PrimaryGeneratorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  PrimaryGeneratorAction(G4VUserDetectorConstruction*);
  virtual ~PrimaryGeneratorAction();

  void GeneratePrimaries(G4Event*);


  void SetRndmFlag(G4String val)       { rndmFlag = val; }
  void SetPDGCode(G4int pdg)           { PDGCode = pdg; }
  void SetEnergy(G4double e)           { energy  = e; }
  void SetOrigin(G4ThreeVector o)      { origin = o; }
  void SetOriginSmear(G4ThreeVector s) { osmear = s; }
  void SetDirection(G4ThreeVector dir) { direction = dir; }
  void SetDirTheta(G4double dt)        { dirtheta = dt; }

private:
  G4ParticleGun*               particleGun;  //pointer a to G4 class
  G4VUserDetectorConstruction* Detector;     //pointer to the geometry
    
  PrimaryGeneratorMessenger* gunMessenger;   //messenger of this class
  G4String                   rndmFlag;	     //flag for a rndm impact point
  G4int                      PDGCode;        //pdg code for particle gun
  G4double                   energy;         //gun energy
  G4ThreeVector              origin;         //gun origin
  G4ThreeVector              osmear;         //half-ranges of smear on orgin 
  G4ThreeVector              direction;      //gun central direction
  G4double                   dirtheta;       //smear in theta on direction
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


