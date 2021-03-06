/*========================================================================================================
 * OperatorInterface.h
 *========================================================================================================
 *
 * File Description:
 *
 * This defines all functions and variable names
 *========================================================================================================*/

#ifndef SRC_TELEOP_CONTROLLERS_TELEOPCONTROL_H_
#define SRC_TELEOP_CONTROLLERS_TELEOPCONTROL_H_

#include <controllers/IDragonGamePad.h>
#include <controllers/DragonXbox.h>
#include <frc/driverstation.h>

using namespace frc;

class TeleopControl
{
    public:

        enum FUNCTION_IDENTIFIER
        {
            TANK_DRIVE_LEFT_CONTROL,
            TANK_DRIVE_RIGHT_CONTROL,
            ARCADE_DRIVE_THROTTLE,
            ARCADE_DRIVE_STEER,
			ROBOT_X_MAGNITUDE,
			ROBOT_Y_MAGNITUDE,
			ROBOT_ROTATION_MAGNITUDE,
			RETRACT_WINCH,
			ROTATE_SIDE_CLIMB_BAR_CW,
			ROTATE_SIDE_CLIMB_BAR_CCW,
			EXTEND_CLIMB_LATCH,
			RETRACT_CLIMB_LATCH,
			RELEASE_SIDE_HANGER,
            GRAB_CUBE,
            SPIN_CUBE,
			MANUAL_ELEVATOR_CONTROL,
			RAISE_4BAR,
			LOWER_4BAR,
			SWITCH_DRIVE_MODE,
			GRABBER_AT_FLOOR_POS,
			GRABBER_AT_SWITCH_POS,
			GRABBER_AT_SCALE_POS,
			INTAKE_CUBE,
			UNRETRACT_WINCH,
			TOGGLE_SAFTEY_SWITCH,
			MANUAL_MOVE_4BAR_MOTOR,
			HUMAN_PLAYER_SIGNAL,
            MAX_FUNCTIONS
        };


        //----------------------------------------------------------------------------------
        // Method:      GetInstance
        // Description: If there isn't an instance of this class, it will create one.  The
        //              single class instance will be returned.
        // Returns:     OperatorInterface*  instance of this class
        //----------------------------------------------------------------------------------
        static TeleopControl* GetInstance();


        //------------------------------------------------------------------
        // Method:      SetScaleFactor
        // Description: Allow the range of values to be set smaller than
        //              -1.0 to 1.0.  By providing a scale factor between 0.0
        //              and 1.0, the range can be made smaller.  If a value
        //              outside the range is provided, then the value will
        //              be set to the closest bounding value (e.g. 1.5 will
        //              become 1.0)
        // Returns:     void
        //------------------------------------------------------------------
        void SetAxisScaleFactor
        (
            TeleopControl::FUNCTION_IDENTIFIER  axis,          // <I> - axis number to update
            float                               scaleFactor    // <I> - scale factor used to limit the range
        );

        //------------------------------------------------------------------
        // Method:      SetAxisProfile
        // Description: Sets the axis profile for the specifed axis
        // Returns:     void
        //------------------------------------------------------------------
        void SetAxisProfile
        (
            TeleopControl::FUNCTION_IDENTIFIER      axis,       // <I> - axis number to update
			IDragonGamePad::AXIS_PROFILE	        profile     // <I> - profile to use
        );

        //------------------------------------------------------------------
        // Method:      GetAxisValue
        // Description: Reads the joystick axis, removes any deadband (small
        //              value) and then scales as requested.
        // Returns:     float   -  scaled axis value
        //------------------------------------------------------------------
        float GetAxisValue
        (
            TeleopControl::FUNCTION_IDENTIFIER     axis // <I> - axis number to update
        ) const;

        //------------------------------------------------------------------
        // Method:      GetRawButton
        // Description: Reads the button value.  Also allows POV, bumpers,
        //              and triggers to be treated as buttons.
        // Returns:     bool   -  scaled axis value
        //------------------------------------------------------------------
        bool IsButtonPressed
        (
            TeleopControl::FUNCTION_IDENTIFIER button   // <I> - button number to query
        ) const;


    private:
        //----------------------------------------------------------------------------------
        // Method:      OperatorInterface <<constructor>>
        // Description: This will construct and initialize the object
        //----------------------------------------------------------------------------------
        TeleopControl();

        //----------------------------------------------------------------------------------
        // Method:      ~OperatorInterface <<destructor>>
        // Description: This will clean up the object
        //----------------------------------------------------------------------------------
        virtual ~TeleopControl() = default;

        //----------------------------------------------------------------------------------
        // Attributes
        //----------------------------------------------------------------------------------
        static TeleopControl*                       m_instance; // Singleton instance of this class
        const int                                   m_maxFunctions = 35;

        IDragonGamePad::AXIS_IDENTIFIER				m_axisIDs[35];
        IDragonGamePad::BUTTON_IDENTIFIER			m_buttonIDs[35];
        int							                m_controllerIndex[35];
        IDragonGamePad*		    	                m_controllers[DriverStation::kJoystickPorts];

        mutable int                                 m_count;
};

#endif /* SRC_TELEOP_CONTROLLERS_TELEOPCONTROL_H_ */
