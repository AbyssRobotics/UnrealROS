//==============================================================================
// Unreal ROS Plugin
//
// Description: Defines the std_msgs/UInt16MultiArray ROS message and its 
//              interface with JSON.
//==============================================================================
#pragma once

// ROS message base class
#include "RosMessageBase.h"

// Message dependencies
#include "MultiArrayLayoutMsg.h"

// UE4 imports
#include "CoreMinimal.h"
#include "UInt16MultiArrayMsg.generated.h"

//==============================================================================
//                              CLASS DECLARATION
//==============================================================================

UCLASS(BlueprintType)
class UNREALROS_API UUInt16MultiArrayMsg : public URosMessageBase
{

	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------
	// Name:        UUInt16MultiArrayMsg constructor
	// Description: Default constructor.
	//--------------------------------------------------------------------------
	UUInt16MultiArrayMsg() : URosMessageBase("std_msgs/UInt16MultiArray")
	{
		m_layout = NewObject<UMultiArrayLayoutMsg>();
	};

	//--------------------------------------------------------------------------
	// Name:        UUInt16MultiArrayMsg destructor
	// Description: Default destructor.
	//--------------------------------------------------------------------------
	~UUInt16MultiArrayMsg() override
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
		json["layout"] = m_layout->get_json();
		for (auto item : m_data)
			json["data"].push_back(item);
		return json;
	}

	//--------------------------------------------------------------------------
	// Name:        from_json
	// Description: Populates the message fields from the given JSON object.
	// Arguments:   - json: JSON object to populate message fields from
	//--------------------------------------------------------------------------
	void from_json(json json) override
	{

		UMultiArrayLayoutMsg* layout = NewObject<UMultiArrayLayoutMsg>();
		layout->from_json(json["layout"]);
		m_layout = layout;

		m_data.Empty();
		for (auto item : json["data"])
			m_data.Push(item);

	}

	//--------------------------------------------------------------------------
	// Name:        get_contents
	// Description: Gets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "ROS")
		void get_contents(UMultiArrayLayoutMsg*& layout, TArray<int>& data)
	{
		layout = m_layout;
		data.Empty();
		for (size_t i = 0; i < m_data.Num(); i++)
			data.Add(static_cast<int>(m_data[i]));
	}

	//--------------------------------------------------------------------------
	// Name:        set_contents
	// Description: Sets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
		void set_contents(UMultiArrayLayoutMsg* layout, TArray<int> data)
	{
		m_layout = layout;
		m_data.Empty();
		for (size_t i = 0; i < data.Num(); i++)
			m_data.Add(static_cast<uint16_t>(data[i]));
	}

private:

	// Specification of data layout
	UMultiArrayLayoutMsg* m_layout;

	// Array of data
	TArray<uint16_t> m_data;

};
