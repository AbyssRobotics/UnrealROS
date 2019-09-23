//==============================================================================
// Unreal ROS Plugin
//
// Description: Defines a base ROS message and its interface with JSON.
//==============================================================================
#pragma once

// JSON parsing
#include "ThirdParty/json.hpp"
using namespace nlohmann;

// UE4 imports
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RosMessageBase.generated.h"

//==============================================================================
//                              CLASS DECLARATION
//==============================================================================

UCLASS(BlueprintType)
class UNREALROS_API URosMessageBase : public UObject
{

	GENERATED_BODY()

public:

	// String representation of the message type
	UPROPERTY(BlueprintReadOnly, Category = "ROS")
	FString type = "avl_unreal/RosMessageBase";

public:

	//--------------------------------------------------------------------------
	// Name:        URosMessageBase constructor
	// Description: Default constructor.
	//--------------------------------------------------------------------------
	URosMessageBase( )
	{
		
	}

	//--------------------------------------------------------------------------
	// Name:        URosMessageBase constructor
	// Description: Constructs the class with a type name.
	//--------------------------------------------------------------------------
	URosMessageBase(FString type_name) : type(type_name)
	{
	
	}

	//--------------------------------------------------------------------------
	// Name:        URosMessageBase destructor
	// Description: Default destructor.
	//--------------------------------------------------------------------------
	virtual ~URosMessageBase()
	{

	}

	//--------------------------------------------------------------------------
	// Name:        get_json
	// Description: Gets the JSON object corresponding to the message.
	// Returns:     JSON object corresponding to the message.
	//--------------------------------------------------------------------------
	virtual json get_json()
	{
		json json;
		return json;
	}

	//--------------------------------------------------------------------------
	// Name:        get_json_string
	// Description: Gets a string representation of the JSON object 
	//              corresponding to the message.
	// Returns:     String representation of the JSON object corresponding to
	//              the message.
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "ROS")
	FString get_json_string()
	{
		return FString(this->get_json().dump().c_str());
	}

	//--------------------------------------------------------------------------
	// Name:        from_json
	// Description: Populates the message fields from the given JSON object.
	// Arguments:   -json: JSON object to populate message fields from
	//--------------------------------------------------------------------------
	virtual void from_json(json json)
	{

	}

	template<typename To, typename From>
	FORCEINLINE TArray<To> CastArray(TArray<From> InArray)
	{
		TArray<To> OutArray;
		OutArray.Reserve(InArray.Num());

		for (auto& Elem : InArray)
		{
			To ThisCastedObject = Cast<To>(Elem);
			if (ThisCastedObject)
			{
				OutArray.Emplace(ThisCastedObject);
			}
		}
		return OutArray;
	}

};
