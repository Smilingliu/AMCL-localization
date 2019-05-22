# AMCL-localization
Locate robot with AMCL package.
This program needs to run in the ros workspace. There are four packages in it：
The ball_chaser package implements the robot tracking white ball function; 
The my_localization package implements the robot positioning, including the design of the ros simulation environment, the robot design, the rviz configuration，and so on; 
The pgm_map_creator package maps the gazebo environment to a two-dimensional map;
The teleop_twist_keyboard package control The movement of the robot.
(The last two packages are downloaded)

Enter the following command on the terminal：
roslaunch my_localization world.launch
roslaunch my_localization amcl.launch

Choose one of the following three commands：
rosrun teleop_twist_keyboard teleop_twist_keyboard.py cmd_vel:=/cmd_vel 
roslaunch ball_chaser ball_chaser.launch
rostopic pub /move_base_simple/goal  geometry_msgs/PoseStamped \ '{header: {frame_id: "map"},pose: {position:{x: 1.0,y: 0,z: 0},orientation: {x: 0,y: 0,z: 0,w: 1}}}'



