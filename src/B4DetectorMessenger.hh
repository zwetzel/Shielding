nclude "DetectorMessenger.hh"

#include "B4dDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"




//Command to create ability to change detector material

fTestemDir = new G4UIdirectory("/messenger/");
  fTestemDir->SetGuidance(" detector control.");

    fDetDir = new G4UIdirectory("/messenger/det/");
      fDetDir->SetGuidance("detector construction commands");

        fMaterCmd = new G4UIcmdWithAString("/messenger/det/setMat",this);
          fMaterCmd->SetGuidance("Select material of the box.");
            fMaterCmd->SetParameterName("choice",false);
              fMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);




              //Assign new material to detector


              void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
              {
                if( command == fMaterCmd )
                   { fDetector->SetMaterial(newValue);}

