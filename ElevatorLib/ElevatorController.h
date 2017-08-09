/**
* \file ElevatorController.h
* Elevator controller abstract base class.
*
* This class is the base class for an elevator controller class.
* That class provides the elevator control.
*
*  \author Charles B. Owen
*/

#pragma once

#include <string>

class CElevatorWnd;

/** Elevator controller base class.
* Elevator controllers are derived from this base class.
*/
class CElevatorController
{
public:
    /** Elevator controller constructor
    * Use the default constructor to create an elevator controller.
    */
    CElevatorController();

    /** Destructor */
    virtual ~CElevatorController();
    /** Copy constructor disabled */
    CElevatorController(const CElevatorController &) = delete;
    /** Assignment operator disabled */
    void operator=(const CElevatorController &) = delete;

    /** Enum that is used to specify a direction
    *
    * Use this enum in functions that require a direction of up or down.
    */
    enum Direction { Up = 0, Down = 1 };

    /** The number of implemented floors
    */
    static const int NumFloors = 3;

    /** Distance from floor to floor in meters.
    */
    static const double FloorSpacing;

    /** Tolerance for a safe door opening.
    *
    * If the car is within 8cm of
    * a floor, the door opening is considered safe. Farther away and
    * we have a safety issue.
    */
    static const double FloorTolerance;

    /*
    * Motor and brakes
    */

    /** Set the motor speed.
    *
    * The elevator uses a DC motor. This function sets the motor
    * speed. The values range from -1 to 1. A value of -1
    * means maximum velocity down. A value of 1 means maximum velocity up.
    * Values outside this range must be bounded to the range [-1, 1].
    * \param speed The speed setting in the range -1 to 1.
    * \code
    SetMotorSpeed(0.4);
    \endcode
    */
    void SetMotorSpeed(double speed);

    /** Set the status of the elevator brake.
    *
    * This function controls the elevator brake. It called with true, the brake is
    * set on. If called with false, the brake is set off. The brake will immediately
    * stop the movement of the car.
    * \param b The brake status to be set. true enables the brake.
    * \code
    SetBrake(true);
    \endcode
    */
    void SetBrake(bool b);

    /** Get the absolute position of the elevator in meters.
    *
    * This function returns the position of the elevator in the shaft in
    * meters relative to the first floor. A value
    * of zero means the elevator is at the first floor door. The constant FloorSpacing
    * indicates the spacing between floors. If this function returns a value of
    * FloorSpacing, the elevator is at the second floor. This is a continuous
    * value and can be negative if the elevator is below the first floor door.
    * \return The current position in meters relative to the first floor door.
    * \code
    if(GetPosition() > FloorSpacing)
    {
    cout << "The elevator is above the second floor" << endl;
    }
    \endcode
    */
    double GetPosition(void) const;

    /** Get the velocity of the elevator in meters per second.
    *
    * This function returns the current velocity of the elevator car
    * in meters per second. A positive value indicates the elevator is
    * going up. A negative value indicates the elevator is going down.
    * Do not exceed the maximum design velocity of 1 meter per second in
    * either direction.
    * \return The elevator car velocity in meters per second
    * \code
    if(fabs(GetVelocity()) < 0.33)
    {
    cout << "Elevator is moving slowly" << endl;
    }
    \endcode
    */
    double GetVelocity(void) const;

    /** Change the current number of passengers on the elevator.
    *
    * This function will cause the number of passengers on the elevator to change
    * to a new random number. This happens automatically when the door opens on any
    * floor, but can also be used to test elevator control code by selecting random
    * loadings.
    */
    void ChangeLoading(void);

    /** Set the passenger load for the elevator car.
    *
    * This function sets the passengers in the elevator car. The passengers are
    * represented by a bitwise or of 1 for Noel, 2 for Neil, and 4 for Sparty. To
    * turn on all passengers, use a value of 1 | 2 | 4 = 7.
    * \param r Binary or of passenger values.
    * This code example enables all passengers.
    * \code
    SetLoading(7);
    \endcode
    *
    */
    void SetLoading(int r);



    /** Service the elevator.
    *
    * This function is called once every millisecond during elevator
    * operation. It provides a place to put code the controls the
    * elevator. Override in a local function.
    */
    virtual void Service() {};

    /*
    * Doors
    */

    /** Set the elevator door motor speed.
    *
    * The speed can be set to -1 for closing, 1 for opening and 0 for off.
    * Smaller values can be used and will make the door close or open slower.
    * The motor is automatically turned off when the door finishes opening or
    * closing.
    *
    * It is the control system's responsibility to only open doors
    * when the elevator is at the floor and not to move the elevator
    * while the doors are open.
    * \param floor The floor number. 1, 2, or 3.
    * \param speed A speed value
    */
    void SetDoorMotor(int floor, double speed);

    /** Determines if the elevator door is open.
    *
    * This function returns true if the elevator door is completely open.
    * When a door is moving from open to closed or vice versa, this function
    * and IsDoorClosed will both return false. Use this function to determine
    * when the opening process has completed.
    * \param floor The floor number. 1, 2, or 3.
    * \returns true if the door is open all the way.
    */
    bool IsDoorOpen(int floor) const;

    /** Determines if the elevator door is closed.
    *
    * This function returns true if the elevator door is completely closed.
    * When a door is moving from open to closed or vice versa, this function
    * and IsDoorOpen will both return false. Use this function to determine
    * when the closing process has completed.
    * \param floor The floor number. 1, 2, or 3.
    * \returns true if the door is closed all of the way.
    */
    bool IsDoorClosed(int floor) const;

    /*
    * Lights
    */

    /** Set the status of the close door light on the panel in the elevator car.
    *
    * This function sets the lighted status of the close door button inside the
    * elevator car. If set to true, the light is turned on.
    * \param s Set to true to run the light on
    * \code
    SetCloseDoorLight(true);
    \endcode
    */
    void SetCloseDoorLight(bool s);

    /** Get the status of the close door light on the panel in the elevator car.
    *
    * This functions checks to see if the close door light on the panel in the elevator
    * car is on.
    * \return true if the light is on.
    * \code
    if(GetCloseDoorLight())
    {
    do something here...
    }
    \endcode
    *
    */
    bool GetCloseDoorLight(void) const;

    /** Set the status of the open door light on the panel in the elevator car.
    *
    * This function sets the lighted status of the open door button inside the
    * elevator car. If set to true, the light is turned on.
    * \param s Set to true to run the light on
    * \code
    SetOpenDoorLight(true);
    \endcode
    */
    void SetOpenDoorLight(bool s);

    /** Get the status of the open door light on the panel in the elevator car.
    *
    * This functions checks to see if the open door light on the panel in the elevator
    * car is on.
    * \return true if the light is on.
    * \code
    if(GetOpenDoorLight())
    {
    do something here...
    }
    \endcode
    *
    */
    bool GetOpenDoorLight(void) const;

    /** Set the status of the floor select light on the panel in the elevator car.
    *
    * This function sets the lighted status of the floor select button inside the
    * elevator car. If set to true, the light is turned on.
    * \param floor The floor number. 1, 2, or 3.
    * \param s Set to true to run the light on
    * \code
    SetPanelFloorLight(1, true);
    \endcode
    */
    void SetPanelFloorLight(int floor, bool s);

    /** Get the status of the floor select light on the panel in the elevator car.
    *
    * This functions checks to see if the floor select button on the panel in the elevator
    * car is currently lit.
    * \param floor The floor number. 1, 2, or 3.
    * \return true if the light is on.
    * \code
    if(GetPanelFloorLight(1))
    {
    do something here...
    }
    \endcode
    *
    */
    bool GetPanelFloorLight(int floor) const;

    /** Set the status of a call button light for a floor.
    *
    * This function sets the lighted status of a call button on a floor.
    * Each floor has an up and down call button. This sets the lighting of
    * that button on or off.
    * \param floor The floor number. 1, 2, or 3.
    * \param d A direction, Up or Down
    * \param s Set to true to turn the light on
    * \code
    SetCallLight(2, Up, true);
    \endcode
    */
    void SetCallLight(int floor, Direction d, bool s);

    /** Get the status of a call button light for a floor.
    *
    * This functions checks to see if an elevator call button for a
    * floor is currently lit. Each floor has an up and down call button.
    * This function determines the status of the lighting of those buttons.
    *
    * The default button behavior sets this light on when the button
    * is pressed (except for down on the bottom floor and top on the
    * upper floor, where the button press is ignored). Use SetCallLight
    * to turn the light back off.
    * \param floor The floor number. 1, 2, or 3.
    * \param d A direction to indication which light, Up or Down
    * \return true if the light is on.
    * \code
    if(GetCallLight(1, Down))
    {
    do something here...
    }
    \endcode
    *
    */
    bool GetCallLight(int floor, Direction d) const;

    /** Set the status of a door indicator for a floor.
    *
    * This function sets the lighted status of a door indicator on a floor.
    * Each floor has an up and down arrow above the elevator door. This light
    * is normally used to indicate when the elevator has arrived and which
    * direction it is going. This function turns those indicators on and off.
    * \param floor The floor number. 1, 2, or 3.
    * \param d A direction to indication which light, Up or Down
    * \param s Set to true to turn the light on
    * \code
    SetCallLight(2, Up, true);
    \endcode
    */
    void SetDoorIndicator(int floor, Direction d, bool s);

    /** Get the status of a door indicator light for a floor.
    *
    * This functions checks to see if a door indicator for a
    * floor is currently lit. Each floor has an up and down arrow above the elevator door. This light
    * is normally used to indicate when the elevator has arrived and which
    * direction it is going. This function checks to see if those indicators are on or off.
    * \param floor The floor number. 1, 2, or 3.
    * \param d A direction to indication which light, Up or Down
    * \return true if the light is on.
    * \code
    if(GetDoorIndicator((3, false))
    {
    do something here...
    }
    \endcode
    *
    */
    bool GetDoorIndicator(int floor, Direction d) const;

    /** Fire mode indication
    *
    * If the fire mode is set on the first floor, this function returns true.
    * \returns true if Fire Mode is set
    */
    bool IsFireMode();

    /** Initialization function.
    *
    * This function is called when the elevator system is initialized. This is
    * later than when it is constructed, since the controller is not installed on
    * an elevator when it is constructed. This function is called when the elevator
    * controller is installed and ready to control an elevator.
    */
    virtual void Initialize() {}

    /** Indication that the Open button in the elevator has been pressed.
    *
    * This function is called when the open button in the elevator is pressed.
    */
    virtual void OnOpenPressed() {}

    /** Indication that the Close button in the elevator has been pressed.
    *
    * This function is called when the close button in the elevator is pressed.
    */
    virtual void OnClosePressed() {}

    /** Indication that a floor button has been pressed in the elevator.
    *
    * This function is called when a floor button is pressed inside the elevator car.
    * \param floor The floor number. 1, 2, or 3.
    */
    virtual void OnPanelFloorPressed(int floor) {}

    /** Indication that the up call button has been pressed on a floor.
    *
    * This function is called when an up button is pressed on a floor.
    * \param floor The floor number. 1, 2, or 3.
    */
    virtual void OnCallUpPressed(int floor) {}

    /** Indication that the down call button has been pressed on a floor.
    *
    * This function is called when an down button is pressed on a floor.
    * \param floor The floor number. 1, 2, or 3.
    */
    virtual void OnCallDownPressed(int floor) {}

    /** Spoken status function
    *
    * This function is used to provide a spoken status of the
    * elevator system for accessibility purposes.
    * \param msg The message to speak
    */
    virtual void Speak(const std::string &msg) {}

    /** Get the elevator this controller is for
     * \returns Pointer to CElevatorWnd object */
    CElevatorWnd *GetElevator() { return mElevator; }

    /** \cond */
    void SetElevator(CElevatorWnd *elevator);

private:
    // The elevator we are controlling
    CElevatorWnd *mElevator = nullptr;

    /** \endcond */
};

