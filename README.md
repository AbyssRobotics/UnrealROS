# UnrealROS
UnrealROS ia an Unreal Engine plugin that provides a ROS message publish/subscribe interface over TCP by interfacing with ROS's [rosbridge](http://wiki.ros.org/rosbridge_suite) package. The plugin provides rosbridge functionality by providing a rosbridge ActorComponent that can be attached to an actor. The component provides the following blueprint functions:
- **Connect**: Connects to the remote rosbridge instance.
- **Advertise**: Advertises a topic to be published by the plugin.
- **Unadvertise**: Unadvertises a topic that will no longer be published b ythe plugin.
- **Publish**: Publishes a message to a topic that has already been advertised.
- **Subscribe**: Subscribes to a topic that has been advertised.
- **Unsubscribe**: Unsubscribes from a topic.

# Installation
To install this plugin into an Unreal Engine project follow these steps:

1. Navigate to an Unreal Engine project folder that contains the `<ProjectName>.uproject` folder.
2. Create a `Plugins` folder if it does not already exist.
3. Clone this repository into the `Plugins` folder.

Launch the project. You should be prompted to re-compile the project which should complete successfully. The plugin is now ready to use in the Unreal Engine editor.

# Usage
To use the rosbridge actor component, create or edit an Actor blueprint. In the Actor's editing window, press `Add Component` and select the `Rosbridge` component as shown in the below image.

<h1 align="center">
  <img src="https://raw.githubusercontent.com/AbyssRobotics/UnrealROS/master/Resources/add_component.png">
</h1>

The component must first be connected to a remote rosbridge session. See [rosbridge](http://wiki.ros.org/rosbridge_suite) documentation on how to launch rosbridge. The image below shows the rosbridge component being connected to rosbridge running on a computer with IP address `192.168.1.10` on port `9090`.

<h1 align="center">
  <img src="https://raw.githubusercontent.com/AbyssRobotics/UnrealROS/master/Resources/connect.png">
</h1>

After being connected, the rosbridge component can be used for publish/scubscribe functionality. 

## Publish
To publish a message, the following steps must be followed:

1. If the topic has not been advertised yet, advertise the topic.
2. Construct an instance of a message class.
3. Set the contents of the message.
4. Publish the message.

These steps are shown in the image below.

<h1 align="center">
  <img src="https://raw.githubusercontent.com/AbyssRobotics/UnrealROS/master/Resources/publish.png">
</h1>
  
This will publish the message over rosbirgde into the ROS system. 

## Subscribe
To subscribe to a message, use the following process:

1. Subscribe to the topic and specify a callback event.
2. In the callback event, cast the base message to the expected message type.
3. Get the contents of the message from the casted message.
4. Use the message contents in any way desired.

The following image illustrates the subscription process:

<h1 align="center">
  <img src="https://raw.githubusercontent.com/AbyssRobotics/UnrealROS/master/Resources/subscribe.png">
</h1>
  
Whenever a message is published to the topic that is being subscribed to, the callback event will be triggered and the message will be passed to the `Message` pin. This message is a RosMessageBase type and must be cast to the expected message type in order to get the message contents correctly.
