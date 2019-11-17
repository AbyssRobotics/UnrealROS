//==============================================================================
// Unreal ROS Plugin
//
// Description: Defines the sensor_msgs/Joy ROS message and its 
//              interface with JSON.
//==============================================================================
#pragma once

// ROS message base class
#include "RosMessageBase.h"

// Message dependencies
#include "std_msgs/HeaderMsg.h"

// UE4 imports
#include "CoreMinimal.h"
#include "JoyMsg.generated.h"

//==============================================================================
//                              CLASS DECLARATION
//==============================================================================

UCLASS(BlueprintType)
class UNREALROS_API UJoyMsg : public URosMessageBase
{

	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------
	// Name:        UJoyMsg constructor
	// Description: Default constructor.
	//--------------------------------------------------------------------------
	UJoyMsg() : URosMessageBase("sensor_msgs/Joy")
	{

	};

	//--------------------------------------------------------------------------
	// Name:        UJoyMsg destructor
	// Description: Default destructor.
	//--------------------------------------------------------------------------
	~UJoyMsg() override
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
		json["header"] = m_header->get_json();
		for (float item : m_axes)
			json["axes"].push_back(item);
		for (uint32_t item : m_buttons)
			json["buttons"].push_back(item);
		return json;

	}

	//--------------------------------------------------------------------------
	// Name:        from_json
	// Description: Populates the message fields from the given JSON object.
	// Arguments:   - json: JSON object to populate message fields from
	//--------------------------------------------------------------------------
	void from_json(json json_message) override
	{

		UHeaderMsg* header = NewObject<UHeaderMsg>();
		header->from_json(json_message["header"]);
		m_header = header;

		m_axes.Empty();
		for (float item : json_message["axes"])
			m_axes.Push(item);

		m_buttons.Empty();
		for (uint32_t item : json_message["buttons"])
			m_buttons.Push(item);

	}

	//--------------------------------------------------------------------------
	// Name:        get_contents
	// Description: Gets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "ROS")
		void get_contents(UHeaderMsg*& header, TArray<float>& axes, TArray<int>& buttons)
	{
		header = m_header;
		axes = m_axes;
		buttons.Empty();
		for (size_t i = 0; i < m_buttons.Num(); i++)
			buttons.Add(static_cast<int>(m_buttons[i]));

	}

	//--------------------------------------------------------------------------
	// Name:        set_contents
	// Description: Sets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
		void set_contents(UHeaderMsg* header, TArray<float> axes, TArray<int> buttons)
	{
		m_header = header;
		m_axes = axes;
		m_buttons.Empty();
		for (size_t i = 0; i < buttons.Num(); i++)
			m_buttons.Add(static_cast<int32_t>(buttons[i]));
	}

private:

	UHeaderMsg* m_header;
	TArray<float> m_axes;
	TArray<int32_t> m_buttons;

};
