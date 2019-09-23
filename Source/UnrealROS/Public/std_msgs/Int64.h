//==============================================================================
// Unreal ROS Plugin
//
// Description: Defines the std_msgs/Int64 ROS message and its 
//              interface with JSON.
//==============================================================================

#pragma once

#include "CoreMinimal.h"
#include "RosMessageBase.h"
#include "Int64.generated.h"

//==============================================================================
//                              CLASS DECLARATION
//==============================================================================

UCLASS(BlueprintType)
class UNREALROS_API UInt64 : public URosMessageBase
{

	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------
	// Name:        UInt64 constructor
	// Description: Default constructor.
	//--------------------------------------------------------------------------
	UInt64() : URosMessageBase("std_msgs/Int64")
	{

	};

	//--------------------------------------------------------------------------
	// Name:        UInt64 destructor
	// Description: Default destructor.
	//--------------------------------------------------------------------------
	~UInt64() override
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
		return json;
	}

	//--------------------------------------------------------------------------
	// Name:        from_json
	// Description: Populates the message fields from the given JSON object.
	// Arguments:   - json: JSON object to populate message fields from
	//--------------------------------------------------------------------------
	void from_json(json json) override
	{

	}

	//--------------------------------------------------------------------------
	// Name:        get_contents
	// Description: Gets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "ROS")
		void get_contents(int& data)
	{

	}

	//--------------------------------------------------------------------------
	// Name:        set_contents
	// Description: Sets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
		void set_contents(int data)
	{

	}

private:



};
