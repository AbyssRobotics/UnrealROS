# UnrealROS
UnrealROS ia an Unreal Engine plugin that provides a ROS message publish/subscribe interface over TCP by interfacing with ROS's [rosbridge](http://wiki.ros.org/rosbridge_suite) package. The plugin provides rosbridge functionality by providing a rosbridge ActorComponent that can be attached to an actor. The component provides the following blueprint functions:
- **connect**: Connects to the remote rosbridge instance.
- **advertise**: Advertises a topic to be published by the plugin.
- **unadvertise**: Unadvertises a topic that will no longer be published b ythe plugin.
- **publish**: Publishes a message to a topic that has already been advertised.
- **subscribe**: Subscribes to a topic that has been advertised.
- **unsubscribe**: Unsubscribes from a topic.
