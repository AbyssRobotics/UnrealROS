//==============================================================================
// Unreal ROS Plugin
//
// Description: Defines the std_msgs/Float32 ROS message and its interface with
//              JSON.
//==============================================================================
#pragma once

// ROS message base class
#include "RosMessageBase.h"

// UE4 imports
#include "CoreMinimal.h"
#include "Float32Msg.generated.h"

//==============================================================================
//                              CLASS DECLARATION
//==============================================================================

UCLASS(BlueprintType)
class UNREALROS_API UFloat32Msg : public URosMessageBase
{

	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------
	// Name:        UFloat32Msg constructor
	// Description: Default constructor.
	//--------------------------------------------------------------------------
	UFloat32Msg() : URosMessageBase("std_msgs/Float32")
	{

	}

	//--------------------------------------------------------------------------
	// Name:        UFloat32Msg destructor
	// Description: Default destructor.
	//--------------------------------------------------------------------------
	~UFloat32Msg() override
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
		json["data"] = m_data;
		return json;
	}

	//--------------------------------------------------------------------------
	// Name:        from_json
	// Description: Populates the message fields from the given JSON object.
	// Arguments:   - json: JSON object to populate message fields from
	//--------------------------------------------------------------------------
	void from_json(json json) override
	{
		m_data = json["data"];
	}

	//--------------------------------------------------------------------------
	// Name:        get_contents
	// Description: Gets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "ROS")
		void get_contents(float& data)
	{
		data = m_data;
	}

	//--------------------------------------------------------------------------
	// Name:        set_contents
	// Description: Sets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
		void set_contents(float data)
	{
		m_data = data;
	}

private:

	float m_data;

};
