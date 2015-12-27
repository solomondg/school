package org.usfirst.frc.team1510.robot;

import java.util.*;
import edu.wpi.first.wpilibj.buttons.Button;
import org.usfirst.frc.team1510.robot.subsystems.*;
import org.usfirst.frc.team1510.robot.commands.*;
import edu.wpi.first.wpilibj.Joystick;
import java.lang.Math;
import java.awt.geom.Point2D;

// @author Solomon

public final class GamePadControl extends Joystick {
    


    public GamePadControl(int port) {
        super(port, 6, 10); // USB port of the gamepad/joystick/whatever
    }
    

    /* 
     * 3 types of value returns:
     * direction (in degrees) and magnitude, or raw values.
     */
    public Vector2D[] getSticks() {
    /* Use this function if you want to get the stick states.
     * Returns an array of Vector2D of the two stick states.
     */
        Vector2D[] stickMap = new Vector2D[];
        stickMap.add(getLstick());
        stickMap.add(getRstick());
        return stickMap;
    }

    private Vector2D getLstick() { // Returns value of left stick
        return new Vector2D(getRawAxis(0), getRawAxis(1));
    }
    
    private Vector2D getRstick() { // Returns value of right stick
        return new Vector2D(getRawAxis(2), getRawAxis(3));
    }

    public bool[] getButtons() {  // returns array of all buttons 
        bool[] buttonMap = new bool[];
        int n;
        for (n=0;n<getButtonCount();n++) {
            buttonMap.add(getRawButton(n + 1);
        }
        return buttonMap;
    }

}
