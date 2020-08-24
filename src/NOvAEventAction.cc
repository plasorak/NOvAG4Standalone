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
// $Id: NOvAEventAction.cc,v 1.2 2012-01-23 21:16:50 rhatcher Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "NOvAEventAction.hh"

#include "NOvARunAction.hh"
#include "NOvAEventActionMessenger.hh"

#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"

#include "Randomize.hh"
#include <iomanip>
#include <exception>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NOvAEventAction::NOvAEventAction(NOvARunAction* run)
  : runAct(run)
  , fOneEvtTransverseProfile(0)
  , fSumE(0)
  , fSumRE(0)
  , printModulo(1)
  , eventMessenger(0)
{
  eventMessenger = new NOvAEventActionMessenger(this);

  if ( ! fOneEvtTransverseProfile )
    fOneEvtTransverseProfile = 
      (TH1F*) run->getShowerTransverseProfile()->Clone();
  fOneEvtTransverseProfile->SetNameTitle("OneEvtTransverseProfile",
                                         "OneEvtTransverseProfile");
  fOneEvtTransverseProfile->Sumw2(); // full fill-time statistics

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NOvAEventAction::~NOvAEventAction()
{
  delete eventMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NOvAEventAction::BeginOfEventAction(const G4Event* evt)
{  
  
  // initialisation per event
  fOneEvtTransverseProfile->Reset();
  fSumE = fSumRE = 0.;

  G4PrimaryVertex* vtx0 = evt->GetPrimaryVertex();
  rayOrigin = vtx0->GetPosition();
  rayDircos = vtx0->GetPrimary()->GetMomentum().unit();

  if ( false ) {
    G4cout << "BeginOfEventAction: origin " << rayOrigin 
           << " ray " << rayDircos << G4endl;
    evt->Print();
    evt->GetPrimaryVertex()->Print();
    evt->GetPrimaryVertex()->GetPrimary()->Print();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void NOvAEventAction::AddE(G4double de, G4double r)
{
  fSumE += de; fSumRE += r*de; 
  fOneEvtTransverseProfile->Fill(r,de);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NOvAEventAction::EndOfEventAction(const G4Event* evt)
{
  if (evt->IsAborted()) {
    throw std::runtime_error("Event was aborted!");
  }
  
  if (nonAbortedCount%1000 == 0) {
    std::cout << nonAbortedCount << " were non aborted\n";
  }
  nonAbortedCount++;

  double width = -1; 
  if ( fSumE > 0 ) width = fSumRE/fSumE;
  
  //accumulates statistic
  //
  runAct->fillPerEvent(fOneEvtTransverseProfile,width);
}  

