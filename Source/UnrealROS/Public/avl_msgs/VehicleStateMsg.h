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

		json["roll"]  = m_roll;
		json["pitch"] = m_pitch;
	    json["yaw"]   = m_yaw;

		json["v_eb_b_x"] = m_v_eb_b_x;
		json["v_eb_b_y"] = m_v_eb_b_y;
		json["v_eb_b_z"] = m_v_eb_b_z;

		json["lat"] = m_lat;
		json["lon"] = m_lon;
		json["alt"] = m_alt;

		json["lat0"] = m_lat0;
		json["lon0"] = m_lon0;
		json["alt0"] = m_alt0;

		json["r_b_n"] = m_r_b_n;
		json["r_b_e"] = m_r_b_e;
		json["r_b_d"] = m_r_b_d;

		json["w_ib_b_x"] = m_w_ib_b_x;
		json["w_ib_b_y"] = m_w_ib_b_y;
		json["w_ib_b_z"] = m_w_ib_b_z;

		json["f_ib_b_x"] = m_f_ib_b_x;
		json["f_ib_b_y"] = m_f_ib_b_y;
		json["f_ib_b_z"] = m_f_ib_b_z;

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

		m_roll = json["roll"];
		m_pitch = json["pitch"];
		m_yaw = json["yaw"];

		m_v_eb_b_x = json["v_eb_b_x"];
		m_v_eb_b_y = json["v_eb_b_y"];
		m_v_eb_b_z = json["v_eb_b_z"];

		m_lat = json["lat"];
		m_lon = json["lon"];
		m_alt = json["alt"];

		m_lat0 = json["lat0"];
		m_lon0 = json["lon0"];
		m_alt0 = json["alt0"];

		m_r_b_n = json["r_b_n"];
		m_r_b_e = json["r_b_e"];
		m_r_b_d = json["r_b_d"];

		m_w_ib_b_x = json["w_ib_b_x"];
		m_w_ib_b_y = json["w_ib_b_y"];
		m_w_ib_b_z = json["w_ib_b_z"];

		m_f_ib_b_x = json["f_ib_b_x"];
		m_f_ib_b_y = json["f_ib_b_y"];
		m_f_ib_b_z = json["f_ib_b_z"];

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

		attitude.X = m_roll;
		attitude.Y = m_pitch;
		attitude.Z = m_yaw;

		velocity.X = m_v_eb_b_x;
		velocity.Y = m_v_eb_b_y;
		velocity.Z = m_v_eb_b_z;

		pos_lla.X = m_lat;
		pos_lla.Y = m_lon;
		pos_lla.Z = m_alt;

		ned_origin.X = m_lat0;
		ned_origin.Y = m_lon0;
		ned_origin.Z = m_alt0;
		pos_ned.X = m_r_b_n;
		pos_ned.Y = m_r_b_e;
		pos_ned.Z = m_r_b_d;

		angular_velocity.X = m_w_ib_b_x;
		angular_velocity.Y = m_w_ib_b_y;
		angular_velocity.Z = m_w_ib_b_z;

		linear_acceleration.X = m_f_ib_b_x;
		linear_acceleration.Y = m_f_ib_b_y;
		linear_acceleration.Z = m_f_ib_b_z;

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

		m_roll = attitude.X;
		m_pitch = attitude.Y;
		m_yaw = attitude.Z;

		m_v_eb_b_x = velocity.X;
		m_v_eb_b_y = velocity.Y;
		m_v_eb_b_z = velocity.Z;

		m_lat = pos_lla.X;
		m_lon = pos_lla.Y;
		m_alt = pos_lla.Z;

		m_lat0 = ned_origin.X;
		m_lon0 = ned_origin.Y;
		m_alt0 = ned_origin.Z;
		m_r_b_n = pos_ned.X;
		m_r_b_e = pos_ned.Y;
		m_r_b_d = pos_ned.Z;

		m_w_ib_b_x = angular_velocity.X;
		m_w_ib_b_y = angular_velocity.Y;
		m_w_ib_b_z = angular_velocity.Z;

		m_f_ib_b_x = linear_acceleration.X;
		m_f_ib_b_y = linear_acceleration.Y;
		m_f_ib_b_z = linear_acceleration.Z;

	}

public:

	// Propeller RPM
	double m_rpm;

	// Euler angles to rotate from the NED frame to the body frame.These are the
	// vehicle's roll, pitch, and heading. Units are radians.
	double m_roll;
	double m_pitch;
	double m_yaw;

	// Vehicle body frame velocity relative to the earth frame, expressed in the body
	// frame.This is the vehicle's ground-relative speed. Units are m/s.
	double m_v_eb_b_x;
	double m_v_eb_b_y;
	double m_v_eb_b_z;

	// Vehicle body frame position expressed in geodetic coordinates.Units are
	// radians for lat / lon and meters for alt.
	double m_lat;
	double m_lon;
	double m_alt;

	// Vehicle body frame position expressed in a local cartesian frame with origin
	// at lat0, lon0, and alt0.Units are radians for lat0 / lon0 and meters for the
	// rest.
	double m_lat0;
	double m_lon0;
	double m_alt0;
	double m_r_b_n;
	double m_r_b_e;
	double m_r_b_d;

	// Vehicle body frame rotation rate relative to the inertial frame, expressed in
	// the body frame.These are the values that a gyroscope would read if mounted to
	// the vehicle body frame.Units are rad / s.
	double m_w_ib_b_x;
	double m_w_ib_b_y;
	double m_w_ib_b_z;

	// Vehicle body frame acceleration relative to the inertial frame, expressed in
	// the body frame.These are the values that an accelerometer would read if
	// mounted to the vehicle body frame.Units are m / s ^ 2.
	double m_f_ib_b_x;
	double m_f_ib_b_y;
	double m_f_ib_b_z;

};
