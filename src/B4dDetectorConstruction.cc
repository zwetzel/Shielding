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
// $Id: B4dDetectorConstruction.cc 87359 2014-12-01 16:04:27Z gcosmo $
//
/// \file B4dDetectorConstruction.cc
/// \brief Implementation of the B4dDetectorConstruction class

#include "B4dDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AutoDelete.hh"
#include "G4SubtractionSolid.hh"

#include "G4SDManager.hh"
#include "G4SDChargedFilter.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSTrackLength.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4dDetectorConstruction::B4dDetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(true)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4dDetectorConstruction::~B4dDetectorConstruction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4dDetectorConstruction::Construct()
{
 
  
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


  G4NistManager* nistManager = G4NistManager::Instance();

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4dDetectorConstruction::DefineVolumes()
{
  // Geometry parameters
  /*G4int nofLayers = 10;
  G4double absoThickness = 10.*mm;
  G4double gapThickness =  5.*mm;
  G4double calorSizeXY  = 10.*cm;

  G4double layerThickness = absoThickness + gapThickness;
  G4double calorThickness = nofLayers * layerThickness;
  G4double worldSizeXY = 1.2 * calorSizeXY;
  G4double worldSizeZ  = 1.2 * calorThickness; 
  */
  // Envelope, World, Poly, Sci1, Sci2 and Gd parameters
  G4double env_sizeXY = 2*m, env_sizeZ = 2*m;
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4double box_x = 30*cm;
  G4double box_y = 30*cm;
  G4double box_z = 30*cm;
  G4double outer_sheet_x = 2*m;
  G4double outer_sheet_y = 2*m;
  G4double outer_sheet_z = 1*cm;
  G4double inner_sheet_x = 30*cm;
  G4double inner_sheet_y = 30*cm;
  G4double inner_sheet_z = 1*cm;
 // G4double brick_x = 22.86*cm;
 // G4double brick_y = 45.72*cm;
 // G4double brick_z = 15.24*cm;
 // G4double brick_thickness = 0.238*cm;

  G4Box* solidWorld  
    = new G4Box("World",           // its name
    world_sizeXY/2, world_sizeXY/2, world_sizeZ/2); // its size*/

    G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        /*WorldMaterial*/
			 nistManager->FindOrBuildMaterial("G4_AIR"),           //its material
                        "World");            //its name
                                   
    //G4VPhysicalVolume* worldPV
    G4VPhysicalVolume* physWorld =
    new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 logicWorld,          // its logical volume                         
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  


//Envelope

     G4Box* solidEnv =    
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size
      

     
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,            //its solid
			nistManager->FindOrBuildMaterial("G4_AIR"),
			// EnvMaterial,             //its material
                        "Envelope");         //its name
               
                                   
  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 logicEnv,          // its logical volume                         
                 "Envelope",    // its name
                 logicWorld,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

//Define High Density Polyehtylene

G4Material* Water = nistManager->FindOrBuildMaterial("G4_WATER");

G4Material* HDPE = new G4Material("HDPE", 1.1*g/cm3, 1);
HDPE -> AddMaterial(nistManager->FindOrBuildMaterial("G4_POLYETHYLENE"),1.0);

G4Material* BoratedPoly05 = new G4Material("BoratedPoly05", 1.06*g/cm3,2);
BoratedPoly05 -> AddMaterial(nistManager->FindOrBuildMaterial("G4_B"), 0.05);
BoratedPoly05 -> AddMaterial(nistManager->FindOrBuildMaterial("G4_POLYETHYLENE"), 0.95);

G4Material* BoratedPoly30 = new G4Material("BoratedPoly05", 1.19*g/cm3,2);
BoratedPoly30 -> AddMaterial(nistManager->FindOrBuildMaterial("G4_B"), 0.30);
BoratedPoly30 -> AddMaterial(nistManager->FindOrBuildMaterial("G4_POLYETHYLENE"), 0.70);


  
//Water Block
 

   G4ThreeVector pos1 = G4ThreeVector();
   G4Box *water_brick= new G4Box("Water Brick",box_x*0.5, 0.5*box_y,0.5*box_z);

   G4LogicalVolume* logicWB =                         
    new G4LogicalVolume(water_brick,         //its solid
			BoratedPoly30, //nistManager->FindOrBuildMaterial("G4_GRAPHITE"),
			// PolyMaterial,          //its material
                        "Water Brick");           //its name
   new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicWB,             //its logical volume
                    "Water Brick",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    fCheckOverlaps);          //overlaps checking





     //Inner Scoring Sheet

     G4ThreeVector pos4 = G4ThreeVector(0, 0*cm, 0.25*m);
     G4Box *ScoringSheet= new G4Box("Inner Scoring Sheet", 0.5*inner_sheet_x, 0.5*inner_sheet_y,0.5*inner_sheet_z);
     
G4LogicalVolume* logicSheet =                         
    new G4LogicalVolume(ScoringSheet,         //its solid
			nistManager->FindOrBuildMaterial("G4_AIR"),
			//    Sci2Material,          //its material
                        "Inner Scoring Sheet");           //its name

      new G4PVPlacement(0,                       //no rotation
                    pos4,                    //at position
                    logicSheet,             //its logical volume
                    "Inner Scoring Sheet",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    fCheckOverlaps);          //overlaps checking

  //Outer Scoring Sheet

  G4Box *Sheet = new G4Box("Sheet", outer_sheet_x*0.5,outer_sheet_y*0.5,outer_sheet_z*0.5);

 G4SubtractionSolid *Outer_Sheet = new G4SubtractionSolid("Outer Sheet", Sheet, ScoringSheet);
 G4LogicalVolume * logic_Outer_Sheet =
	new G4LogicalVolume(Outer_Sheet, nistManager->FindOrBuildMaterial("G4_AIR"), "Outer Scoring Sheet");

 new G4PVPlacement(0,                       //no rotation
                    pos4,                    //at position
                    logic_Outer_Sheet,             //its logical volume
                    "Outer Scoring Sheet",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    fCheckOverlaps);          //overlaps checking



/*
	//Neutron capture sheet
	
	G4ThreeVector pos2 = G4ThreeVector(0,0, 0.2*m);
	G4Box *Shield = new G4Box("Shield", 0.5*sheet_x, 0.5*sheet_y, 0.005*m);

G4LogicalVolume *logicShield = 
	new G4LogicalVolume(Shield,
				nistManager->FindOrBuildMaterial("G4_Cd"),
				"Shield");
	new G4PVPlacement(0,pos2,logicShield,"Shield", logicEnv, false,0,fCheckOverlaps);
*/
  //
  //                                   
  // Visualization attributes
  //
    
  G4VisAttributes *WBVis= new G4VisAttributes(G4Color(0,0,1));//blue
  G4VisAttributes *SSVis= new G4VisAttributes(G4Color(1,1,1));//white
  
  
  logicWB->SetVisAttributes(WBVis);
  logicSheet->SetVisAttributes(SSVis);

  //
  // Always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void B4dDetectorConstruction::ConstructSDandField()
{}/*
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  // 
  //Sensitive Detectors
  //
  //Scoring Sheet SD
  //
   G4MultiFunctionalDetector* ScoringSheet 
    = new G4MultiFunctionalDetector("Scoring Sheet");

  G4VPrimitiveScorer* passageCurrent;
  passageCurrent = new G4PSPassageCurrent("Passage Current");
  ScoringSheet->RegisterPrimitive(passageCurrent);
 
  SetSensitiveDetector("Scoring Sheet",ScoringSheet);
  
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
