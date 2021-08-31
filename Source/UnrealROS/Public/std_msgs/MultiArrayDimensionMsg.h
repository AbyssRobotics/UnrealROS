//==============================================================================
// Unreal ROS Plugin
//
// Description: Defines the std_msgs/MultiArrayDimension ROS message and its 
//              interface with JSON.
//==============================================================================
#pragma once

// ROS message base class
#include "RosMessageBase.h"

// UE4 imports
#include "CoreMinimal.h"
#include "MultiArrayDimensionMsg.generated.h"

//==============================================================================
//                              CLASS DECLARATION
//==============================================================================

UCLASS(BlueprintType)
class UNREALROS_API UMultiArrayDimensionMsg : public URosMessageBase
{

	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------
	// Name:        UMultiArrayDimensionMsg constructor
	// Description: Default constructor.
	//--------------------------------------------------------------------------
	UMultiArrayDimensionMsg() : URosMessageBase("std_msgs/MultiArrayDimension")
	{

	};

	//--------------------------------------------------------------------------
	// Name:        UMultiArrayDimensionMsg destructor
	// Description: Default destructor.
	//--------------------------------------------------------------------------
	~UMultiArrayDimensionMsg() override
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
		json["label"] = std::string(TCHAR_TO_UTF8(*m_label));
		json["size"] = m_size;
		json["stride"] = m_stride;
		return json;
	}

	//--------------------------------------------------------------------------
	// Name:        from_json
	// Description: Populates the message fields from the given JSON object.
	// Arguments:   - json: JSON object to populate message fields from
	//--------------------------------------------------------------------------
	void from_json(json json) override
	{
		std::string label_string = json["label"];
		m_label = FString(label_string.c_str());
		m_size = json["size"];
		m_stride = json["stride"];
	}

	//--------------------------------------------------------------------------
	// Name:        get_contents
	// Description: Gets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "ROS")
		void get_contents(FString& label, int& size, int& stride)
	{
		label = m_label;
		size = static_cast<int>(m_size);
		stride = static_cast<int>(m_stride);
	}

	//--------------------------------------------------------------------------
	// Name:        set_contents
	// Description: Sets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
		void set_contents(FString label, int size, int stride)
	{
		m_label = label;
		m_size = static_cast<uint32>(size);
		m_stride = static_cast<uint32>(stride);
	}

private:

	// Label of given dimension
	FString m_label = "";

	// Size of given dimension(in type units)
	uint32 m_size = 0;

	// Stride of given dimension
	uint32 m_stride = 0;

};
