//==============================================================================
// Unreal ROS Plugin
//
// Description: Provides the base rosbridge functionality. Provides blueprint
//              callable functions to connect to a rosbridge server, and publish
//              and subscribe to ROS topics through the rosbridge API.
//==============================================================================

#pragma once

// TCP socket functionality
#include "Networking.h"

// UE4 core functionality
#include "CoreMinimal.h"

// Actor base class
#include "GameFramework/Actor.h"

// JSON parsing
#include "ThirdParty/json.hpp"

// Map class
#include <map>

// ROS message base class
#include "RosMessageBase.h"

#include "rosbridge.generated.h"

//==============================================================================
//                              CLASS DECLARATION
//==============================================================================

UCLASS(ClassGroup = ROS, editinlinenew, meta = (BlueprintSpawnableComponent))
class UNREALROS_API URosbridge : public UActorComponent
{
	
	GENERATED_BODY()

public:	

	//--------------------------------------------------------------------------
	// Name:        ARosbridge constructor
	// Description: Default constructor.
	//--------------------------------------------------------------------------
	URosbridge();

	//--------------------------------------------------------------------------
	// Name:        OnMessageReceived delegate
	// Description: Declare a delegate type that gets called when a message is 
	//              received from a subscription.
	//--------------------------------------------------------------------------
	DECLARE_DYNAMIC_DELEGATE_OneParam(FMessageReceivedCallback, URosMessageBase*, Message);

	//--------------------------------------------------------------------------
	// Name:        connect
	// Description: Connects to a rosbridge server.
	// Arguments:   - address: rosbridge server address
	//              - port: rosbridge server port
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
		void connect(FString address, int port);

	//--------------------------------------------------------------------------
	// Name:        advertise
	// Description: Advertises that a ROS topic will be published.
	// Arguments:   - topic: topic name
	//              - type: message type
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
	void advertise(FString topic, FString type);

	//--------------------------------------------------------------------------
	// Name:        unadvertise
	// Description: Stops advertising that a ROS topic will be published.
	// Arguments:   - topic: topic name
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
	void unadvertise(FString topic);

	//--------------------------------------------------------------------------
	// Name:        publish
	// Description: Publishes to a ROS topic.
	// Arguments:   - topic: topic name
	//              - type: message type
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
	void publish(FString topic, UPARAM(ref) URosMessageBase* message);

	//--------------------------------------------------------------------------
	// Name:        subscribe
	// Description: Subscribes to a ROS topic.
	// Arguments:   - topic: topic name
	//              - message_type: message type
	//              - callback: callback to be called when a message arrives on 
	//                the topic
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
	void subscribe(FString topic, TSubclassOf<URosMessageBase> message_type, 
				   const FMessageReceivedCallback& callback);

	//--------------------------------------------------------------------------
	// Name:        unsubscribe
	// Description: Unsubscribes from a ROS topic.
	// Arguments:   - topic: topic name
	//--------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ROS")
	void unsubscribe(FString topic);

	//------------------------------------------------------------------------------
	// Name:        set_level
	// Description: Sets the status message level on the rosbridge server.
	// Arguments:   - level: status_message_level
	//------------------------------------------------------------------------------
	void set_level(FString level);

protected:

	//--------------------------------------------------------------------------
	// Name:        BeginPlay
	// Description: Called when the game starts or when spawned. Override of 
	//              AActor::BeginPlay.
	//--------------------------------------------------------------------------
	virtual void BeginPlay() override;

	//--------------------------------------------------------------------------
	// Name:        Tick
	// Description: Called every game tick. Override of AActor::Tick.
	// Arguments:   - DeltaTime: time since last tick in seconds
	//--------------------------------------------------------------------------
	void TickComponent(float DeltaTime, enum ELevelTick TickType, 
					   FActorComponentTickFunction *ThisTickFunction) override;

	//--------------------------------------------------------------------------
	// Name:        EndPlay
	// Description: Called when the game ends. Override of AActor::EndPlay.
	// Arguments:   - EndPlayReason: reason for play ending
	//--------------------------------------------------------------------------
	virtual	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//--------------------------------------------------------------------------
	// Name:        handle_received_json
	// Description: Handles a JSON message received over TCP.
	// Arguments:   - json_message: JSON message to be handles
	//--------------------------------------------------------------------------
	void handle_received_json(nlohmann::json json_message);

private:	

	// Socket instance for TCP communication
	FSocket* tcp_socket;

	// Receive buffer for bytes received over TCP
	std::string receive_buffer;

	// Map between a string representing a ROS message type and a UClass that 
	// can be used to create an instance of the message type
	std::map<FString, UClass*> message_type_map;

	// Map between topic name and type name for all subscriptions. Used to get
	// the type of an incoming message since that is not indicated by rosbridge
	std::map<FString, FString> subscription_map;
	std::map<FString, FMessageReceivedCallback> subscription_callback_map;

	// Flag indicating whether the TCP server is connected
	bool socket_connected = false;

private:

	//--------------------------------------------------------------------------
	// Name:        print
	// Description: Prints a message on the editor screen.
	// Arguments:   - color: message color
	//              - message: message string
	//--------------------------------------------------------------------------
	void print(FColor color, FString message);

	//--------------------------------------------------------------------------
	// Name:        json_to_bytes
	// Description: Converts a JSON object to an array of uint8 bytes.
	// Arguments:   - json: JSON object to be converted
	//              - num_bytes: number of bytes in resulting byte array
	// Returns:     Array of bytes representing the JSON object.
	//--------------------------------------------------------------------------
	const uint8* json_to_bytes(json json, int32& num_bytes);

};
