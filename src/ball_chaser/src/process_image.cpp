#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;
//Define a variable that controls the direction of rotation of the cart when the target is not found
static int count=0;
// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ROS_INFO_STREAM("Driving the robot");
    ball_chaser::DriveToTarget drive_cmd;
    drive_cmd.request.linear_x = lin_x;
    drive_cmd.request.angular_z = ang_z;
    
    if (!client.call(drive_cmd)){
        ROS_ERROR("Failed to call service");
    }
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;
    int white_moment = 0;
    int white_pixels = 0;
    float white_center=0.00;
    float x, z;
    for(int i=0; i<img.height; ++i){
        for (int j=0; j<img.step; ++j){
            if (img.data[i * img.step + j] == white_pixel){
                ++white_pixels;
                white_moment += j - img.step/2;
            }
        }
    }
    
    // Filter out interference points,found turn until you find white_ball.
    if (white_pixels <5)
   { 
        count++;
        if(count<20)
        {
            x = 0.0;
            z = 0.5;
         }
         else if(count<40)
         {
            x=0.0;
            z=-0.5;
          }
          else
          {
             x=-0.2;
             z=0.0;
             count=0;
           }
    }  
    else {
        count=0;
        x = 0.1;
        white_center=white_moment/white_pixels;
        z=  -0.5*white_center/500;
    }
    drive_robot(x,z);
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
