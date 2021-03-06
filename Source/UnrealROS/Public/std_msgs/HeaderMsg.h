//==============================================================================
// Unreal ROS Plugin
//
// Description: Defines the std_msgs/Header ROS message and its 
//              interface with JSON.
//==============================================================================

#pragma once

#include "CoreMinimal.h"
#include "RosMessageBase.h"
#include "HeaderMsg.generated.h"

//==============================================================================
//                              CLASS DECLARATION
//==============================================================================

UCLASS(BlueprintType)
class UNREALROS_API UHeaderMsg : public URosMessageBase
{

	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------
	// Name:        UHeaderMsg constructor
	// Description: Default constructor.
	//--------------------------------------------------------------------------
	UHeaderMsg() : URosMessageBase("std_msgs/Header")
	{

	};

	//--------------------------------------------------------------------------
	// Name:        UHeaderMsg destructor
	// Description: Default destructor.
	//--------------------------------------------------------------------------
	~UHeaderMsg() override
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
		json["seq"] = m_seq;
		json["stamp"]["secs"] = m_secs;
		json["stamp"]["nsecs"] = m_nsecs;
		json["frame_id"] = m_frame_id;
		return json;
	}

	//--------------------------------------------------------------------------
	// Name:        from_json
	// Description: Populates the message fields from the given JSON object.
	// Arguments:   - json: JSON object to populate message fields from
	//--------------------------------------------------------------------------
	void from_json(json json) override
	{
		m_seq = json["seq"];
		m_secs = json["stamp"]["secs"];
		m_nsecs = json["stamp"]["nsecs"];
		m_frame_id = json["frame_id"].get<std::string>();
	}

	//--------------------------------------------------------------------------
	// Name:        get_contents
	// Description: Gets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "ROS")
	void get_contents(int& seq, int& sec, int& nsec, FString& frame_id)
	{
		seq = static_cast<int>(m_seq);
		sec = static_cast<int>(m_secs);
		nsec = static_cast<int>(m_nsecs);
		frame_id = FString(m_frame_id.c_str());
	}

	//--------------------------------------------------------------------------
	// Name:        set_contents
	// Description: Sets the contents of the ROS message.
	// Arguments:   - data: message data
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
	void set_contents(int seq, int secs, int nsecs, FString frame_id)
	{
		m_seq = static_cast<uint32>(seq);
		m_secs = static_cast<int32>(secs);
		m_nsecs = static_cast<int32>(nsecs);
		m_frame_id = std::string(TCHAR_TO_UTF8(*frame_id));
	}

private:

	uint32 m_seq;
	int32 m_secs;
	int32 m_nsecs;
	std::string m_frame_id;

};
