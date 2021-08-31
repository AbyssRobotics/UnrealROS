//==============================================================================
// Unreal ROS Plugin
//
// Description: Defines the std_msgs/ColorRGBA ROS message and its 
//              interface with JSON.
//==============================================================================

#pragma once

#include "CoreMinimal.h"
#include "RosMessageBase.h"
#include "ColorRGBAMsg.generated.h"

//==============================================================================
//                              CLASS DECLARATION
//==============================================================================

UCLASS(BlueprintType)
class UNREALROS_API UColorRGBAMsg : public URosMessageBase
{

	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------
	// Name:        UColorRGBAMsg constructor
	// Description: Default constructor.
	//--------------------------------------------------------------------------
	UColorRGBAMsg() : URosMessageBase("std_msgs/ColorRGBA")
	{

	};

	//--------------------------------------------------------------------------
	// Name:        UColorRGBAMsg destructor
	// Description: Default destructor.
	//--------------------------------------------------------------------------
	~UColorRGBAMsg() override
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
		json["r"] = m_r;
		json["g"] = m_g;
		json["b"] = m_b;
		json["a"] = m_a;
		return json;
	}

	//--------------------------------------------------------------------------
	// Name:        from_json
	// Description: Populates the message fields from the given JSON object.
	// Arguments:   - json: JSON object to populate message fields from
	//--------------------------------------------------------------------------
	void from_json(json json) override
	{
		m_r = json["r"];
		m_g = json["g"];
		m_b = json["b"];
		m_a = json["a"];
	}

	//--------------------------------------------------------------------------
	// Name:        get_contents
	// Description: Gets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "ROS")
	void get_contents(float& r, float& g, float& b, float& a)
	{
		r = m_r;
		g = m_g;
		b = m_b;
		a = m_a;
	}

	//--------------------------------------------------------------------------
	// Name:        set_contents
	// Description: Sets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
	void set_contents(float r, float g, float b, float a)
	{
		m_r = r;
		m_g = g;
		m_b = b;
		m_a = a;
	}

private:

	float m_r;
	float m_g;
	float m_b;
	float m_a;


};
