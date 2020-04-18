//==============================================================================
// Unreal ROS Plugin
//
// Description: Defines the std_msgs/Empty ROS message and its 
//              interface with JSON.
//==============================================================================

#pragma once

#include "CoreMinimal.h"
#include "RosMessageBase.h"
#include "EmptyMsg.generated.h"

//==============================================================================
//                              CLASS DECLARATION
//==============================================================================

UCLASS(BlueprintType)
class UNREALROS_API UEmptyMsg : public URosMessageBase
{

	GENERATED_BODY()

public:

	//--------------------------------------------------------------------------
	// Name:        UEmptyMsg constructor
	// Description: Default constructor.
	//--------------------------------------------------------------------------
	UEmptyMsg() : URosMessageBase("std_msgs/Empty")
	{

	};

	//--------------------------------------------------------------------------
	// Name:        UEmptyMsg destructor
	// Description: Default destructor.
	//--------------------------------------------------------------------------
	~UEmptyMsg() override
	{

	}

private:



};
