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
// $Id: NOvARunAction.cc,v 1.2 2012-01-23 21:12:01 rhatcher Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "NOvARunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

#include "TFile.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NOvARunAction::NOvARunAction()
  : fShowerTransverseProfile(0)
  , fShowerWidthHist(0)
{
  if ( ! fShowerTransverseProfile )
    fShowerTransverseProfile = 
      new TH1F("ShowerTransverseProfile","ShowerTransverseProfile",300,0,300.);
  fShowerTransverseProfile->Sumw2(); // full fill-time statistics

  if ( ! fShowerWidthHist )
    fShowerWidthHist = 
      new TH1F("ShowerWidthHist","ShowerWidthHist",1200,0.,150.);
  fShowerWidthHist->Sumw2(); // full fill-time statistics
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NOvARunAction::~NOvARunAction()
{
  delete fShowerTransverseProfile;
  delete fShowerWidthHist;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NOvARunAction::BeginOfRunAction(const G4Run* aRun)
{ 
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(true);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NOvARunAction::fillPerEvent(TH1F* oneevtTransverseProfile, G4double width )
{
  //accumulate statistic
  //
  fShowerTransverseProfile->Add(oneevtTransverseProfile);
  fShowerWidthHist->Fill(width,1.0);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NOvARunAction::EndOfRunAction(const G4Run* aRun)
{
  G4int NbOfEvents = aRun->GetNumberOfEvent();
  if (NbOfEvents == 0) return;
  
  //compute statistics: mean and rms
  //

  TFile rfile(fHistFileName,"UPDATE");
  fShowerTransverseProfile->Write();
  fShowerWidthHist->Write();
  
  //print
  //
  G4cout
     << "\n--------------------End of Run------------------------------\n"
     << " TransverseProfile mean " << fShowerTransverseProfile->GetMean() << "\n"
     << " WidthHist mean " << fShowerWidthHist->GetMean()
     << G4endl;
     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
