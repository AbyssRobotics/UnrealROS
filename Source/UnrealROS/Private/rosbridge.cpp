//==============================================================================
// Unreal ROS Plugin
//
// Description: Provides the base rosbridge functionality. Provides blueprint
//              callable functions to connect to a rosbridge server, and publish
//              and subscribe to ROS topics through the rosbridge API.
//==============================================================================

#include "rosbridge.h"

// AddOnScreenDebugMessage function
#include "Engine.h"

// Stringstream for JSON parsing
#include <sstream>

//==============================================================================
//                              CLASS DEFINITION
//==============================================================================

//------------------------------------------------------------------------------
// Name:        URosbridge constructor
// Description: Default constructor.
//------------------------------------------------------------------------------
URosbridge::URosbridge()
{

	// Enable ticks
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

}

//--------------------------------------------------------------------------
// Name:        connect
// Description: Connects to a rosbridge server.
// Arguments:   - address: rosbridge server address
//              - port: rosbridge server port
//--------------------------------------------------------------------------
void URosbridge::connect(FString address, int port)
{

	// Configure the IPv4 address that the socket will connect to
	TSharedRef<FInternetAddr> internet_address = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool address_valid;
	internet_address->SetIp(*address, address_valid);
	internet_address->SetPort(port);

	// Ensure that the address is valid
	if (!address_valid)
	{
		print(FColor::Red, FString::Printf(TEXT("connect: invalid address")));
		return;
	}

	// Attempt to connect the socket to the address
	if (tcp_socket->Connect(*internet_address))
	{
		socket_connected = true;
		print(FColor::Green, TEXT("socket connected"));
	}
	else
	{
		socket_connected = false;
		print(FColor::Red, TEXT("socket connection failed"));
	}
		

}

//------------------------------------------------------------------------------
// Name:        advertise
// Description: Advertises that a ROS topic will be published.
// Arguments:   - topic: topic name
//              - type: message type
//------------------------------------------------------------------------------
void URosbridge::advertise(FString topic, FString type)
{

	// Ensure the TCP socket is connected
	if (!socket_connected)
	{
		print(FColor::Red, FString::Printf(TEXT("advertise: rosbridge is not connected")));
		return;
	}

	// Ensure that the type is valid
	if (message_type_map.find(type) == message_type_map.end())
	{
		print(FColor::Red, FString::Printf(TEXT("advertise: unknown message type (%s)"), *type));
		return;
	}

	// Assemble the JSON object
	json json_message;
	json_message["op"] = "advertise";
	json_message["topic"] = std::string(TCHAR_TO_UTF8(*topic));
	json_message["type"] = std::string(TCHAR_TO_UTF8(*type));

	// Convert the JSON object to an array of bytes
	std::string json_string = json_message.dump();
	int32 num_bytes = json_string.length();
	const uint8* json_bytes = reinterpret_cast<const uint8*>(json_string.c_str());

	// Send the message
	int32 num_bytes_sent;
	if (!(tcp_socket->Send(json_bytes, num_bytes, num_bytes_sent)))
		print(FColor::Red, TEXT("advertise failed"));

}

//------------------------------------------------------------------------------
// Name:        unadvertise
// Description: Stops advertising that a ROS topic will be published.
// Arguments:   - topic: topic name
//------------------------------------------------------------------------------
void URosbridge::unadvertise(FString topic)
{

	// Ensure the TCP socket is connected
	if (!socket_connected)
	{
		print(FColor::Red, FString::Printf(TEXT("unadvertise: rosbridge is not connected")));
		return;
	}

	// Assemble the JSON object
	json json_message;
	json_message["op"] = "unadvertise";
	json_message["topic"] = std::string(TCHAR_TO_UTF8(*topic));

	// Convert the JSON object to an array of bytes
	std::string json_string = json_message.dump();
	int32 num_bytes = json_string.length();
	const uint8* json_bytes = reinterpret_cast<const uint8*>(json_string.c_str());

	// Send the message
	int32 num_bytes_sent;
	if (!(tcp_socket->Send(json_bytes, num_bytes, num_bytes_sent)))
		print(FColor::Red, TEXT("unadvertise failed"));

}

//------------------------------------------------------------------------------
// Name:        publish
// Description: Publishes to a ROS topic.
// Arguments:   - topic: topic name
//              - type: message type
//------------------------------------------------------------------------------
void URosbridge::publish(FString topic, UPARAM(ref) URosMessageBase* message)
{

	// Ensure the TCP socket is connected
	if (!socket_connected)
	{
		print(FColor::Red, FString::Printf(TEXT("publish: rosbridge is not connected")));
		return;
	}

	// Assemble the JSON object
	json json_message;
	json_message["op"] = "publish";
	json_message["topic"] = std::string(TCHAR_TO_UTF8(*topic));
	json_message["msg"] = message->get_json();

	// Convert the JSON object to an array of bytes
	std::string json_string = json_message.dump();
	int32 num_bytes = json_string.length();
	const uint8* json_bytes = reinterpret_cast<const uint8*>(json_string.c_str());

	// Send the message
	int32 num_bytes_sent;
	if (!(tcp_socket->Send(json_bytes, num_bytes, num_bytes_sent)))
		print(FColor::Red, TEXT("publish failed"));

}

//------------------------------------------------------------------------------
// Name:        subscribe
// Description: Subscribes to a ROS topic.
// Arguments:   - topic: topic name
//              - message_type: message type
//              - callback: callback to be called when a message arrives on
//                the topic
//------------------------------------------------------------------------------
void URosbridge::subscribe(FString topic, TSubclassOf<URosMessageBase> message_type,
						   const FMessageReceivedCallback& callback)
{

	// Ensure the message type is selected
	if (message_type == NULL)
	{
		print(FColor::Red, FString::Printf(TEXT("subscribe: message type must be selected")));
		return;
	}

	// Ensure the TCP socket is connected
	if (!socket_connected)
	{
		print(FColor::Red, FString::Printf(TEXT("subscribe: rosbridge is not connected")));
		return;
	}

	// Create an instance of the class in order to get the type string
	URosMessageBase* message_instance = NewObject<URosMessageBase>(this, message_type);
	FString type_string = message_instance->type;

	// Add the subscription to the mapping between the topic name and the topic's
	// message received callback
	subscription_callback_map[topic] = callback;

	// Assemble the rosbridge JSON object to subscribe
	json json_message;
	json_message["op"] = "subscribe";
	json_message["topic"] = std::string(TCHAR_TO_UTF8(*topic));
	json_message["type"] = std::string(TCHAR_TO_UTF8(*type_string));

	// Convert the JSON object to an array of bytes to be sent over TCP
	std::string json_string = json_message.dump();
	int32 num_bytes = json_string.length();
	const uint8* json_bytes = reinterpret_cast<const uint8*>(json_string.c_str());

	// Send the subscribe message bytes with the TCP socket
	int32 num_bytes_sent;
	if (tcp_socket->Send(json_bytes, num_bytes, num_bytes_sent))
	{
		subscription_map[topic] = type_string;
		print(FColor::Green, TEXT("subscribe succeeded"));
	}
	else
	{
		print(FColor::Red, TEXT("subscribe failed"));
	}

}

//------------------------------------------------------------------------------
// Name:        unsubscribe
// Description: Unsubscribes from a ROS topic.
// Arguments:   - topic: topic name
//------------------------------------------------------------------------------
void URosbridge::unsubscribe(FString topic)
{

	// Ensure the TCP socket is connected
	if (!socket_connected)
	{
		print(FColor::Red, FString::Printf(TEXT("unsubscribe: rosbridge is not connected")));
		return;
	}

	// Assemble the JSON object
	json json_message;
	json_message["op"] = "unsubscribe";
	json_message["topic"] = std::string(TCHAR_TO_UTF8(*topic));

	// Convert the JSON object to an array of bytes
	std::string json_string = json_message.dump();
	int32 num_bytes = json_string.length();
	const uint8* json_bytes = reinterpret_cast<const uint8*>(json_string.c_str());

	// Send the message
	int32 num_bytes_sent;
	if (tcp_socket->Send(json_bytes, num_bytes, num_bytes_sent))
		print(FColor::Green, TEXT("unsubscribe succeeded"));
	else
		print(FColor::Red, TEXT("unsubscribe failed"));

}

//------------------------------------------------------------------------------
// Name:        set_level
// Description: Sets the status message level on the rosbridge server.
// Arguments:   - level: status_message_level
//------------------------------------------------------------------------------
void URosbridge::set_level(FString level)
{

	// Ensure the TCP socket is connected
	if (!socket_connected)
	{
		print(FColor::Red, FString::Printf(TEXT("set_level: rosbridge is not connected")));
		return;
	}

	// Assemble the JSON object for a topic subscribe message
	json json_message;
	json_message["op"] = "set_level";
	json_message["level"] = std::string(TCHAR_TO_UTF8(*level));

	// Convert the JSON object to an array of bytes
	std::string json_string = json_message.dump();
	int32 num_bytes = json_string.length();
	const uint8* json_bytes = reinterpret_cast<const uint8*>(json_string.c_str());

	// Send the subscribe message
	int32 num_bytes_sent;
	if (tcp_socket->Send(json_bytes, num_bytes, num_bytes_sent))
		print(FColor::Green, TEXT("set_level succeeded"));
	else
		print(FColor::Red, TEXT("set_level failed"));

}

//------------------------------------------------------------------------------
// Name:        BeginPlay
// Description: Called when the game starts or when spawned. Override of
//              AActor::BeginPlay.
//------------------------------------------------------------------------------
void URosbridge::BeginPlay()
{

	Super::BeginPlay();

	// Create a socket
	tcp_socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket("tcp_socket", TEXT("default"), false);

	// Find all subclasses of the ROS message base class
	TArray< TAssetSubclassOf<UObject> > subclass_list;
	for (TObjectIterator<UClass> it; it; ++it)
		if (it->IsChildOf(URosMessageBase::StaticClass()) && !it->HasAnyClassFlags(CLASS_Abstract))
			subclass_list.Add(*it);

	// Populate the map between message type string and UClass using the list
	// of objects inheriting the ROS message base class
	for (TAssetSubclassOf<UObject> type : subclass_list)
	{

		// Get the UClass of the subclass and create an instance of it.
		UClass* message_class = type.Get();
		URosMessageBase* message_instance = NewObject<URosMessageBase>(this, message_class);

		// Use the message instance to get the type string and add it to the
		// type string to UClass map
		FString message_type = message_instance->type;
		message_type_map[message_type] = message_class;

		print(FColor::Turquoise, message_type);

	}

}

//------------------------------------------------------------------------------
// Name:        Tick
// Description: Called every game tick. Override of AActor::Tick.
// Arguments:   - DeltaTime: time since last tick in seconds
//------------------------------------------------------------------------------
void URosbridge::TickComponent(float DeltaTime, enum ELevelTick TickType, 
							   FActorComponentTickFunction *ThisTickFunction)
{

	// Check whether there is data ready to be read in the receive buffer
	uint32 num_pending_bytes;
	if (tcp_socket->HasPendingData(num_pending_bytes))
	{

		// Initialize the received data buffer to hold the number of pending bytes
		TArray<uint8> received_data;
		received_data.Init(0, FMath::Min(num_pending_bytes, 65507u));

		// Receive the data from the socket
		int32 num_bytes_read;
		tcp_socket->Recv(received_data.GetData(), received_data.Num(), num_bytes_read);

		// Convert the received data buffer into a std::string and add it to the 
		// receive buffer for processing
		received_data.Add(0);
		FString received_fstring = FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(received_data.GetData())));
		std::string received_string(TCHAR_TO_UTF8(*received_fstring));

		//std::string received_string((char*)received_data.GetData());
		receive_buffer += received_string;

		// Assume the received buffer can contain more than one JSON object with 
		// random characters between them. We must loop through the receive
		// buffer and extract every JSON object by locating the opening bracket
		// and closing bracket. Since there may be brackets in between, we must 
		// keep track of the number of opened brackets and find when the last one
		// has been closed to find the end of the JSON object
		size_t json_start_pos = std::string::npos;
		size_t json_stop_pos = std::string::npos;
		std::string json_string;

		// Locate the first opening bracket in the receive buffer, 
		// indicating the start of the JSON object. Repeat for every
		// JSON object in the receive buffer
		json_start_pos = receive_buffer.find_first_of('{');
		while (json_start_pos != std::string::npos)
		{

			// Find the last closing bracket that closes the first
			// opening bracket by keeping a count of how many brackets
			// are left open
			json_stop_pos = std::string::npos;
			size_t num_open_brackets = 1;
			for (size_t i = json_start_pos + 1; i < receive_buffer.length(); i++)
			{
				if (receive_buffer[i] == '{')
					num_open_brackets++;
				if (receive_buffer[i] == '}')
					num_open_brackets--;
				if (num_open_brackets == 0)
				{
					json_stop_pos = i;
					break;
				}
			}

			// If there is an unbalanced number of brackets, move on
			// and do not parse the JSON object since it is incomplete
			if (json_stop_pos == std::string::npos)
				return;

			// Extract the JSON object string between the open and close brackets
			// and parse it into a JSON object to be handled
			json_string = receive_buffer.substr(json_start_pos, json_stop_pos - json_start_pos + 1);

			try
			{
				nlohmann::json json_message = nlohmann::json::parse(json_string);
				handle_received_json(json_message);
			}
			catch (const std::exception & ex)
			{
				FString reason(ex.what());
				FString buffer_string(json_string.c_str());
				print(FColor::Yellow, FString::Printf(TEXT("failed to parse received JSON string %d %d (%s)"), json_start_pos, json_stop_pos, *buffer_string));
			}

			// Remove the parts that have been parsed from the receive buffer and 
			// find the start of the next JSON object in the received string if there
			// is one
			receive_buffer.erase(0, json_stop_pos + 1);
			json_start_pos = receive_buffer.find_first_of('{');

		}

	}

}

//------------------------------------------------------------------------------
// Name:        EndPlay
// Description: Called when the game ends. Override of AActor::EndPlay.
// Arguments:   - EndPlayReason: reason for play ending
//------------------------------------------------------------------------------
void URosbridge::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	tcp_socket->Close();
}

//------------------------------------------------------------------------------
// Name:        handle_received_json
// Description: Handles a JSON message received over TCP.
// Arguments:   - json_message: JSON message to be handles
//------------------------------------------------------------------------------
void URosbridge::handle_received_json(nlohmann::json json_message)
{

	try
	{

		// Parse the JSON message based on the operation tag
		std::string operation = json_message["op"];

		// Status messages contain messages about successes and failures of
		// commands sent to the server
		if (operation == "status")
		{
			print(FColor::Green, TEXT("operation: status"));
		}

		// Publish messages contain a ROS message sent by the server when this
		// client is subscribed to a topic
		else if (operation == "publish")
		{

			// Extract the topic name from the message
			std::string topic_string = json_message["topic"];
			FString topic = FString(topic_string.c_str());

			// Use the topic name to find the corresponding message type in
			// the subscriptions
			FString message_type = subscription_map[topic];

			// Get the UClass associated with the message type
			UClass* message_class = message_type_map[message_type];

			// Construct an instance of the message class and load its data
			// from the JSON message.
			URosMessageBase* ros_message = NewObject<URosMessageBase>(this, message_class);
			ros_message->from_json(json_message["msg"]);

			// Broadcast the message received event
			subscription_callback_map[topic].Execute(ros_message);

		}

		// Service response messages contain a ROS service response sent by the
		// server when this client calls a service
		else if (operation == "service_response")
		{
			print(FColor::Green, TEXT("operation: service_response"));
		}

		// All other operations can be ignored since they are either invalid or
		// are not sent to the client by the server
		else
		{
			print(FColor::Yellow, FString::Printf(TEXT("ignoring operation (%s)"), *FString(operation.c_str())));
		}

	}
	catch (const std::exception& ex)
	{
		FString reason(ex.what());
		std::string json_string = json_message.dump();
		FString json_fstring = FString(json_string.c_str());
		print(FColor::Yellow, FString::Printf(TEXT("handle_received_json: failed to parse JSON message (%s)(%s)"), *reason, *json_fstring));
	}

}

//------------------------------------------------------------------------------
// Name:        handle_received_json
// Description: Handles a JSON message received over TCP.
// Arguments:   - json_message: JSON message to be handles
//------------------------------------------------------------------------------
void URosbridge::print(FColor color, FString message)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, color, *message);
}

//------------------------------------------------------------------------------
// Name:        json_to_bytes
// Description: Converts a JSON object to an array of uint8 bytes.
// Arguments:   - json: JSON object to be converted
//              - num_bytes: number of bytes in resulting byte array
// Returns:     Array of bytes representing the JSON object.
//------------------------------------------------------------------------------
const uint8* URosbridge::json_to_bytes(json json, int32& num_bytes)
{

	std::string json_string = json.dump();
	num_bytes = json_string.length();
	const uint8* byte_array = reinterpret_cast<const uint8*>(json_string.c_str());
	return byte_array;

}
