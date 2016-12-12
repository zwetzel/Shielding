#ifndef B4SteppingAction_H
#define B4SteppingAction_H 1

#include "globals.hh"
#include "G4UserSteppingAction.hh"

class B4SteppingAction : public G4UserSteppingAction
{
public:
	G4int NumPart = 0;
	G4int NumNeutron = 0;
	G4int NumGamma = 0;
	G4double TotKinE = 0;
  B4SteppingAction();
  virtual ~B4SteppingAction();

  virtual void UserSteppingAction(const G4Step*);
};

#endif

