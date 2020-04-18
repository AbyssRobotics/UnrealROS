//==============================================================================
// Unreal ROS Plugin
//
// Description: Defines the std_msgs/MultiArrayLayout ROS message and its 
//              interface with JSON.
//==============================================================================
#pragma once

// ROS message base class
#include "RosMessageBase.h"

// Message dependencies
#include "MultiArrayDimensionMsg.h"

// UE4 imports
#include "CoreMinimal.h"
#include "MultiArrayLayoutMsg.generated.h"

//==============================================================================
//                              CLASS DECLARATION
//==============================================================================

UCLASS(BlueprintType)
class UNREALROS_API UMultiArrayLayoutMsg : public URosMessageBase
{

	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------
	// Name:        UMultiArrayLayoutMsg constructor
	// Description: Default constructor.
	//--------------------------------------------------------------------------
	UMultiArrayLayoutMsg() : URosMessageBase("std_msgs/MultiArrayLayout")
	{
		m_dim.Add(NewObject<UMultiArrayDimensionMsg>());
	};

	//--------------------------------------------------------------------------
	// Name:        UMultiArrayLayoutMsg destructor
	// Description: Default destructor.
	//--------------------------------------------------------------------------
	~UMultiArrayLayoutMsg() override
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

		auto dim_array = json::array();
		for (int i = 0; i < m_dim.Num(); ++i)
			dim_array.push_back(m_dim[i]->get_json());

		json["dim"] = dim_array;
		json["data_offset"] = m_data_offset;

		return json;

	}

	//--------------------------------------------------------------------------
	// Name:        from_json
	// Description: Populates the message fields from the given JSON object.
	// Arguments:   - json: JSON object to populate message fields from
	//--------------------------------------------------------------------------
	void from_json(json json_message) override
	{

		json dim_array = json_message["dim"];
		TArray<UMultiArrayDimensionMsg*> dim;
		for (const auto& item : dim_array)
		{
			UMultiArrayDimensionMsg* new_dim = NewObject<UMultiArrayDimensionMsg>();
			new_dim->from_json(item);
			dim.Push(new_dim);
		}

		m_dim = dim;
		m_data_offset = json_message["data_offset"];

	}

	//--------------------------------------------------------------------------
	// Name:        get_contents
	// Description: Gets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "ROS")
	void get_contents(TArray<UMultiArrayDimensionMsg*>& dim, int& data_offset)
	{
		dim = m_dim;
		data_offset = static_cast<int>(m_data_offset);
	}

	//--------------------------------------------------------------------------
	// Name:        set_contents
	// Description: Sets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
	void set_contents(TArray<UMultiArrayDimensionMsg*> dim, int data_offset)
	{
		m_dim = dim;
		m_data_offset = static_cast<uint32>(data_offset);
	}

private:

	// Array of dimension properties
	TArray<UMultiArrayDimensionMsg*> m_dim;

	// Padding elements at front of data
	uint32 m_data_offset = 0;

};
