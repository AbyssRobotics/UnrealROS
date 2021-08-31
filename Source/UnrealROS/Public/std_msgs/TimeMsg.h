//==============================================================================
// Unreal ROS Plugin
//
// Description: Defines the std_msgs/Time ROS message and its 
//              interface with JSON.
//==============================================================================

#pragma once

#include "CoreMinimal.h"
#include "RosMessageBase.h"
#include "TimeMsg.generated.h"

//==============================================================================
//                              CLASS DECLARATION
//==============================================================================

UCLASS(BlueprintType)
class UNREALROS_API UTimeMsg : public URosMessageBase
{

	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------
	// Name:        UTimeMsg constructor
	// Description: Default constructor.
	//--------------------------------------------------------------------------
	UTimeMsg() : URosMessageBase("std_msgs/Time")
	{

	};

	//--------------------------------------------------------------------------
	// Name:        UTimeMsg destructor
	// Description: Default destructor.
	//--------------------------------------------------------------------------
	~UTimeMsg() override
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
		json["data"]["secs"] = m_secs;
		json["data"]["nsecs"] = m_nsecs;
		return json;
	}

	//--------------------------------------------------------------------------
	// Name:        from_json
	// Description: Populates the message fields from the given JSON object.
	// Arguments:   - json: JSON object to populate message fields from
	//--------------------------------------------------------------------------
	void from_json(json json) override
	{
		m_secs = json["data"]["secs"];
		m_nsecs = json["data"]["nsecs"];
	}

	//--------------------------------------------------------------------------
	// Name:        get_contents
	// Description: Gets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "ROS")
		void get_contents(int& secs, int& nsecs)
	{
		secs = static_cast<int>(m_secs);
		nsecs = static_cast<int>(m_nsecs);
	}

	//--------------------------------------------------------------------------
	// Name:        set_contents
	// Description: Sets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
		void set_contents(int secs, int nsecs)
	{
		m_secs = static_cast<int32_t>(secs);
		m_nsecs = static_cast<int32_t>(nsecs);
	}

private:

	int32_t m_secs;
	int32_t m_nsecs;

};
