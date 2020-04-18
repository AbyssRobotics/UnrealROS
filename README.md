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
