/**
 * \file Controller.h
 *
 * \author Jenn Proos
 *
 * 
 */

#pragma once
#include "ElevatorController.h"
#include "Floor.h"

/**
 * 
 */
class CController :
	public CElevatorController
{
public:
	CController();
	virtual ~CController();

	virtual void OnOpenPressed() override;
	virtual void OnClosePressed() override;

	/// The state machine states
	enum States { Idle, DoorOpening, DoorOpen, DoorClosing, Moving, Stop };

	virtual void Service() override;
	void Initialize();

	virtual void OnPanelFloorPressed(int floor) override;
	virtual void OnCallUpPressed(int floor) override;
	virtual void OnCallDownPressed(int floor) override;

	int WhatFloorToGoTo();
	int WhatFloorUp();
	int WhatFloorDown();

private:
	int mFloor = 1;		 ///< The current floor
	States mState = Idle;		///< The current state
	double mStateTime = 0;		///< The time in a current state

	void SetState(States state);

	CFloor mFloors[NumFloors];	///< An object for each floor
	bool mGoingUp = true;		///< Is the elevator going up?
};

