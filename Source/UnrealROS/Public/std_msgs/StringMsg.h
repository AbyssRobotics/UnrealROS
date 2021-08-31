//==============================================================================
// Unreal ROS Plugin
//
// Description: Defines the std_msgs/String ROS message and its interface with
//              JSON.
//==============================================================================

#pragma once

// ROS message base class
#include "RosMessageBase.h"

// UE4 imports
#include "CoreMinimal.h"
#include "StringMsg.generated.h"

//==============================================================================
//                              CLASS DECLARATION
//==============================================================================

UCLASS(BlueprintType)
class UNREALROS_API UStringMsg : public URosMessageBase
{

	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------
	// Name:        UStringMsg constructor
	// Description: Default constructor.
	//--------------------------------------------------------------------------
	UStringMsg() : URosMessageBase("std_msgs/String")
	{

	};

	//--------------------------------------------------------------------------
	// Name:        UStringMsg destructor
	// Description: Default destructor.
	//--------------------------------------------------------------------------
	~UStringMsg() override
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
		json["data"] = std::string(TCHAR_TO_UTF8(*m_data));
		return json;
	}

	//--------------------------------------------------------------------------
	// Name:        from_json
	// Description: Populates the message fields from the given JSON object.
	// Arguments:   - json: JSON object to populate message fields from
	//--------------------------------------------------------------------------
	void from_json(json json) override
	{
		std::string data_string = json["label"];
		m_data = FString(data_string.c_str());
	}

	//--------------------------------------------------------------------------
	// Name:        get_contents
	// Description: Gets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "ROS")
	void get_contents(FString& data)
	{
		data = m_data;
	}

	//--------------------------------------------------------------------------
	// Name:        set_contents
	// Description: Sets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
	void set_contents(FString data)
	{
		m_data = data;
	}

private:

	FString m_data;

};