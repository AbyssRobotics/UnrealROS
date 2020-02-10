//==============================================================================
// Unreal ROS Plugin
//
// Description: Defines the geometry_msgs/Vector3 ROS message and its interface
//              with JSON.
//==============================================================================
#pragma once

// ROS message base class
#include "RosMessageBase.h"

// UE4 imports
#include "CoreMinimal.h"
#include "Vector3Msg.generated.h"

//==============================================================================
//                              CLASS DECLARATION
//==============================================================================

UCLASS(BlueprintType)
class UNREALROS_API UVector3Msg : public URosMessageBase
{

	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------
	// Name:        UVector3Msg constructor
	// Description: Default constructor.
	//--------------------------------------------------------------------------
	UVector3Msg() : URosMessageBase("geometry_msgs/Vector3")
	{

	}

	//--------------------------------------------------------------------------
	// Name:        UVector3Msg destructor
	// Description: Default destructor.
	//--------------------------------------------------------------------------
	~UVector3Msg() override
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
		json["x"] = m_x;
		json["y"] = m_y;
		json["z"] = m_z;
		return json;
	}

	//--------------------------------------------------------------------------
	// Name:        from_json
	// Description: Populates the message fields from the given JSON object.
	// Arguments:   - json: JSON object to populate message fields from
	//--------------------------------------------------------------------------
	void from_json(json json) override
	{
		m_x = json["x"];
		m_y = json["y"];
		m_z = json["z"];
	}

	//--------------------------------------------------------------------------
	// Name:        get_contents
	// Description: Gets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "ROS")
		void get_contents(float& x, float& y, float& z)
	{
		x = static_cast<float>(m_x);
		y = static_cast<float>(m_y);
		z = static_cast<float>(m_z);
	}

	//--------------------------------------------------------------------------
	// Name:        set_contents
	// Description: Sets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
		void set_contents(float x, float y, float z)
	{
		m_x = static_cast<double>(x);
		m_y = static_cast<double>(y);
		m_z = static_cast<double>(z);
	}

private:

	double m_x;
	double m_y;
	double m_z;

};
