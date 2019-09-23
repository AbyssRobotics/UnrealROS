//==============================================================================
// Unreal ROS Plugin
//
// Description: Defines the std_msgs/Float64MultiArray ROS message and its 
//              interface with JSON.
//==============================================================================
#pragma once

// ROS message base class
#include "RosMessageBase.h"

// Message dependencies
#include "MultiArrayLayout.h"

// UE4 imports
#include "CoreMinimal.h"
#include "Float64MultiArray.generated.h"

//==============================================================================
//                              CLASS DECLARATION
//==============================================================================

UCLASS(BlueprintType)
class UNREALROS_API UFloat64MultiArray : public URosMessageBase
{

	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------
	// Name:        UFloat64MultiArray constructor
	// Description: Default constructor.
	//--------------------------------------------------------------------------
	UFloat64MultiArray() : URosMessageBase("std_msgs/Float64MultiArray")
	{

	};

	//--------------------------------------------------------------------------
	// Name:        UFloat64MultiArray destructor
	// Description: Default destructor.
	//--------------------------------------------------------------------------
	~UFloat64MultiArray() override
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
		for (double item : m_data)
			json["data"].push_back(item);
		return json;

	}

	//--------------------------------------------------------------------------
	// Name:        from_json
	// Description: Populates the message fields from the given JSON object.
	// Arguments:   - json: JSON object to populate message fields from
	//--------------------------------------------------------------------------
	void from_json(json json_message) override
	{

		UMultiArrayLayout* layout = NewObject<UMultiArrayLayout>();
		layout->from_json(json_message["layout"]);
		m_layout = layout;

		m_data.Empty();
		for (double item : json_message["data"])
			m_data.Push(item);

	}

	//--------------------------------------------------------------------------
	// Name:        get_contents
	// Description: Gets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "ROS")
	void get_contents(UMultiArrayLayout*& layout, TArray<float>& data)
	{
		layout = m_layout;
		data.Empty();
		for (size_t i = 0; i < m_data.Num(); i++)
			data.Add(static_cast<float>(m_data[i]));

	}

	//--------------------------------------------------------------------------
	// Name:        set_contents
	// Description: Sets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
	void set_contents(UMultiArrayLayout* layout, TArray<float> data)
	{
		m_layout = layout;
		m_data.Empty();
		for (size_t i = 0; i < data.Num(); i++)
			m_data.Add(static_cast<double>(data[i]));
	}

private:

	// Specification of data layout
	UMultiArrayLayout* m_layout;

	// Array of data
	TArray<double> m_data;

};
