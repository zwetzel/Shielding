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
// $Id: B4dEventAction.cc 75604 2013-11-04 13:17:26Z gcosmo $
//
/// \file B4dEventAction.cc
/// \brief Implementation of the B4dEventAction class

#include "B4dEventAction.hh"
#include "B4Analysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "G4Step.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4dEventAction::B4dEventAction()
 : G4UserEventAction(),
   fAbsoEdepHCID(-1),
   fGapEdepHCID(-1),
   fAbsoTrackLengthHCID(-1),
   fGapTrackLengthHCID(-1)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4dEventAction::~B4dEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4THitsMap<G4double>* 
B4dEventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  G4THitsMap<G4double>* hitsCollection 
    = static_cast<G4THitsMap<G4double>*>(
        event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("B4dEventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }         

  return hitsCollection;
}    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double B4dEventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
  G4double sumValue = 0;
  std::map<G4int, G4double*>::iterator it;
  for ( it = hitsMap->GetMap()->begin(); it != hitsMap->GetMap()->end(); it++) {
    sumValue += *(it->second);
  }
  return sumValue;  
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4dEventAction::PrintEventStatistics(
                            G4double absoEdep, G4double absoTrackLength,
                            G4double gapEdep, G4double gapTrackLength) const
{
  // Print event statistics
  //
  G4cout
     << "   Absorber: total energy: " 
     << std::setw(7) << G4BestUnit(absoEdep, "Energy")
     << "       total track length: " 
     << std::setw(7) << G4BestUnit(absoTrackLength, "Length")
     << G4endl
     << "        Gap: total energy: " 
     << std::setw(7) << G4BestUnit(gapEdep, "Energy")
     << "       total track length: " 
     << std::setw(7) << G4BestUnit(gapTrackLength, "Length")
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4dEventAction::BeginOfEventAction(const G4Event* /*event*/)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4dEventAction::EndOfEventAction(const G4Event* event)
{/*  
   // Get hist collections IDs
  if ( fAbsoEdepHCID == -1 ) {
    fAbsoEdepHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("Scoring Sheet/Passage Current");

    fAbsoTrackLengthHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("Polyeth/TrackLength");
    fGapTrackLengthHCID 
    = G4SDManager::GetSDMpointer()->GetCollectionID("Sci1/TrackLength");
  }
  
  // Get sum values from hits collections
  //
  G4double absoEdep = GetSum(GetHitsCollection(fAbsoEdepHCID, event));
  
  
  G4double absoTrackLength 
    = GetSum(GetHitsCollection(fAbsoTrackLengthHCID, event));
  G4double gapTrackLength 
    = GetSum(GetHitsCollection(fGapTrackLengthHCID, event));
  
  // get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  //  
  analysisManager->FillH1(1, absoEdep );
 
  //analysisManager->FillH1(3, absoTrackLength);
  //analysisManager->FillH1(4, gapTrackLength);
  
  // fill ntuple
  //
  analysisManager->FillNtupleDColumn(0, absoEdep);
 
  //analysisManager->FillNtupleDColumn(2, absoTrackLength);
  //analysisManager->FillNtupleDColumn(3, gapTrackLength);
  analysisManager->AddNtupleRow();  
  
  //print per event (modulo n)
  //*/
  G4int eventID = event->GetEventID();
  G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
 // if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
 //   G4cout << "---> End of event: " << eventID << G4endl;     
    // PrintEventStatistics(absoEdep, absoTrackLength, gapEdep, gapTrackLength);
 // }
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......