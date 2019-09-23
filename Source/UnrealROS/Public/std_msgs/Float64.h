//==============================================================================
// Unreal ROS Plugin
//
// Description: Defines the std_msgs/Float64 ROS message and its interface with
//              JSON.
//==============================================================================
#pragma once

// ROS message base class
#include "RosMessageBase.h"

// UE4 imports
#include "CoreMinimal.h"
#include "Float64.generated.h"

//==============================================================================
//                              CLASS DECLARATION
//==============================================================================

UCLASS(BlueprintType)
class UNREALROS_API UFloat64 : public URosMessageBase
{

	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------
	// Name:        UFloat64 constructor
	// Description: Default constructor.
	//--------------------------------------------------------------------------
	UFloat64() : URosMessageBase("std_msgs/Float64")
	{

	}

	//--------------------------------------------------------------------------
	// Name:        UFloat64 destructor
	// Description: Default destructor.
	//--------------------------------------------------------------------------
	~UFloat64() override
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
		data = static_cast<float>(m_data);
	}

	//--------------------------------------------------------------------------
	// Name:        set_contents
	// Description: Sets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
	void set_contents(float data)
	{
		m_data = static_cast<double>(data);
	}

private:

	double m_data;

};
