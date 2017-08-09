/**
 * \file Floor.cpp
 *
 * \author Jenn Proos
 */

#include "stdafx.h"
#include "Floor.h"
#include "Controller.h"


/**
 * Constructor
 */
CFloor::CFloor()
{
}


/**
 * Destructor
 */
CFloor::~CFloor()
{
}

/** Set the value of Up for a floor.
* \param up The new value for mUp
*/
void CFloor::SetUp(bool up)
{
	mUp = up;
	mController->SetCallLight(mFloor, CElevatorController::Up, mUp);
}

/** Set the value of Up for a floor.
* \param up The new value for mUp
*/
void CFloor::SetDown(bool down)
{
	mDown = down;
	mController->SetCallLight(mFloor, CElevatorController::Down, mDown);
}

/** Set the value of Panel for a floor.
* \param panel The new value for mPanel
*/
void CFloor::SetPanel(bool panel)
{
	mPanel = panel;
	mController->SetPanelFloorLight(mFloor, mPanel);
}

void CFloor::SetController(CController * controller)
{
	mController = controller; 
}
