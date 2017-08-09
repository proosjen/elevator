/**
 * \file Floor.h
 *
 * \author Jenn Proos
 *
 * 
 */

#pragma once

class CController;


/**
 * 
 */
class CFloor
{
public:
	CFloor();
	virtual ~CFloor();

	/** \brief Get up status
	* \return mUp*/
	bool IsUp() { return mUp; }
	void SetUp(bool up);

	/** \brief Get down status
	* \return mDown*/
	bool IsDown() { return mDown; }
	void SetDown(bool down);

	/** \brief Get panel status
	* \return mPanel*/
	bool IsPanel() { return mPanel; }
	void SetPanel(bool panel);

	/** \brief Get the floor number
	* \return Floor number*/
	int GetFloor() { return mFloor; }

	/** \brief Set floor number
	* \param floor Floor number to set*/
	void SetFloor(int floor) { mFloor = floor; }

	/** \brief Set the controller
	* \param controller Controller to set*/
	void SetController(CController *controller);

private:
	bool mUp = false;		///< Floor up
	bool mDown = false;		///< Floor down
	bool mPanel = false;	///< Floor panel
	int mFloor = 1;		///< Floor number

	CController *mController;   ///< Controller for this object
};

