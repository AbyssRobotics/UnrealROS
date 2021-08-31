//==============================================================================
// Unreal ROS Plugin
//
// Description: Defines the avl_msgs/VehicleStateMsg ROS message and its
//              interface with JSON.
//==============================================================================
#pragma once

// ROS message base class
#include "RosMessageBase.h"

// UE4 imports
#include "CoreMinimal.h"
#include "VehicleStateMsg.generated.h"

//==============================================================================
//                              CLASS DECLARATION
//==============================================================================

UCLASS(BlueprintType)
class UNREALROS_API UVehicleStateMsg : public URosMessageBase
{

	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------
	// Name:        UVehicleStateMsg constructor
	// Description: Default constructor.
	//--------------------------------------------------------------------------
	UVehicleStateMsg() : URosMessageBase("avl_simulation/VehicleStateMsg")
	{

	}

	//--------------------------------------------------------------------------
	// Name:        UVehicleStateMsg destructor
	// Description: Default destructor.
	//--------------------------------------------------------------------------
	~UVehicleStateMsg() override
	{

	}

	//--------------------------------------------------------------------------
	// Name:        get_json
	// Description: Gets the JSON object corresponding to the message.
	// Returns:     JSON object corresponding to the message.
	//--------------------------------------------------------------------------
	json get_json() override
	{
		json json;

		m_rpm = json["rpm"] = m_rpm;

		json["roll"]  = m_attitude.X;
		json["pitch"] = m_attitude.Y;
	    json["yaw"]   = m_attitude.Z;

		json["v_eb_b_x"] = m_velocity.X;
		json["v_eb_b_y"] = m_velocity.Y;
		json["v_eb_b_z"] = m_velocity.Z;

		json["lat"] = m_pos_lla.X;
		json["lon"] = m_pos_lla.Y;
		json["alt"] = m_pos_lla.Z;

		json["lat0"] = m_ned_origin.X;
		json["lon0"] = m_ned_origin.Y;
		json["alt0"] = m_ned_origin.Z;

		json["r_b_n"] = m_pos_ned.X;
		json["r_b_e"] = m_pos_ned.Y;
		json["r_b_d"] = m_pos_ned.Z;

		json["w_ib_b_x"] = m_angular_velocity.X;
		json["w_ib_b_y"] = m_angular_velocity.Y;
		json["w_ib_b_z"] = m_angular_velocity.Z;

		json["f_ib_b_x"] = m_linear_acceleration.X;
		json["f_ib_b_y"] = m_linear_acceleration.Y;
		json["f_ib_b_z"] = m_linear_acceleration.Z;

		return json;
	}

	//--------------------------------------------------------------------------
	// Name:        from_json
	// Description: Populates the message fields from the given JSON object.
	// Arguments:   - json: JSON object to populate message fields from
	//--------------------------------------------------------------------------
	void from_json(json json) override
	{

		m_rpm = json["rpm"];

		m_attitude.X = json["roll"];
		m_attitude.Y = json["pitch"];
		m_attitude.Z = json["yaw"];

		m_velocity.X = json["v_eb_b_x"];
		m_velocity.Y = json["v_eb_b_y"];
		m_velocity.Z = json["v_eb_b_z"];

		m_pos_lla.X = json["lat"];
		m_pos_lla.Y = json["lon"];
		m_pos_lla.Z = json["alt"];

		m_ned_origin.X = json["lat0"];
		m_ned_origin.Y = json["lon0"];
		m_ned_origin.Z = json["alt0"];

		m_pos_ned.X = json["r_b_n"];
		m_pos_ned.Y = json["r_b_e"];
		m_pos_ned.Z = json["r_b_d"];

		m_angular_velocity.X = json["w_ib_b_x"];
		m_angular_velocity.Y = json["w_ib_b_y"];
		m_angular_velocity.Z = json["w_ib_b_z"];

		m_linear_acceleration.X = json["f_ib_b_x"];
		m_linear_acceleration.Y = json["f_ib_b_y"];
		m_linear_acceleration.Z = json["f_ib_b_z"];

	}

	//--------------------------------------------------------------------------
	// Name:        get_contents
	// Description: Gets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "ROS")
		void get_contents(float& rpm, FVector& attitude, FVector& velocity,
			FVector& pos_lla, FVector& ned_origin, FVector& pos_ned,
			FVector& angular_velocity, FVector& linear_acceleration)
	{
	  rpm = m_rpm;
	  attitude = m_attitude;
	  velocity = m_velocity;
	  pos_lla = m_pos_lla;
	  ned_origin = m_ned_origin;
	  pos_ned = m_pos_ned;
	  angular_velocity = m_angular_velocity;
	  linear_acceleration = m_linear_acceleration;
	}

	//--------------------------------------------------------------------------
	// Name:        set_contents
	// Description: Sets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
		void set_contents(float rpm, FVector attitude, FVector velocity,
			FVector pos_lla, FVector ned_origin, FVector pos_ned,
			FVector angular_velocity, FVector linear_acceleration)
	{
		m_rpm = rpm;
		m_attitude = attitude;
	  m_velocity = velocity;
	  m_pos_lla = pos_lla;
	  m_ned_origin = ned_origin;
	  m_pos_ned = pos_ned;
	  m_angular_velocity = angular_velocity;
	  m_linear_acceleration = linear_acceleration;
	}

private:

  // Propeller RPM
  float m_rpm;

  // Euler angles to rotate from the NED frame to the body frame. These are the
  // vehicle's roll, pitch, and heading. Units are radians.
  FVector m_attitude;

  // Vehicle body frame velocity relative to the earth frame, expressed in the
	// body frame. This is the vehicle's ground-relative speed. Units are m/s.
  FVector m_velocity;

  // Vehicle body frame position expressed in geodetic coordinates. Units are
  // radians for lat/lon and meters for alt.
  FVector m_pos_lla;

  // Vehicle body frame position expressed in a local cartesian frame with
	// origin at lat0, lon0, and alt0. Units are radians for lat0/lon0 and meters
	// for the rest.
  FVector m_ned_origin;
  FVector m_pos_ned;

  // Vehicle body frame rotation rate relative to the inertial frame, expressed
	// in the body frame. These are the values that a gyroscope would read if
	// mounted to the vehicle body frame. Units are rad/s.
  FVector m_angular_velocity;

  // Vehicle body frame acceleration relative to the inertial frame, expressed
	// in the body frame. These are the values that an accelerometer would read if
  // mounted to the vehicle body frame. Units are m/s^2.
  FVector m_linear_acceleration;

};
