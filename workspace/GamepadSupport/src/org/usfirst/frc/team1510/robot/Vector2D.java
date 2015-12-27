/**
 * 
 */
package org.usfirst.frc.team1510.robot;

/**
 * @author Stephen
 * 
 */
public class Vector2D {

	public final double x;
	public final double y;
	public final double angle;
	public final double magnitude;
	
	/**
	 * Constructor for objects of class Vector2D
	 * @param x
	 * @param y
	 */
	public Vector2D(double x, double y) {
		this.x = x;
		this.y = y;
		this.angle = Math.atan2(this.y,this.x);
		this.magnitude = Math.sqrt(this.x*this.x + this.y*this.y);
	}
	
	/**
	 * Constructor for objects of class Vector2D
	 * @param angle
	 * @param magnitude
	 * @param filler Necessary to differentiate between this and the rectangular coordinates. Any value will work.
	 */
	
	public Vector2D(double angle, double magnitude, boolean filler) {
		this.x = magnitude * Math.cos(angle);
		this.y = magnitude * Math.sin(angle);
		this.angle = angle;
		this.magnitude = magnitude;
	}
}
