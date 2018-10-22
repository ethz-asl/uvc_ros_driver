/****************************************************************************
 *
 *   Copyright (c) 2015-2016 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/
/*
 * uvc_ros_driver_node.cpp
 *
 *  Created on: Mar 11, 2016
 *      Author: nicolas, christoph, simone
 *
 */

#include "uvc_ros_driver.h"

#include <functional>

//void dynamicReconfigureCallback(uvc_ros_driver::UvcDriverConfig& config, uint32_t level)
//{
  //ROS_INFO("Reconfigure Request: %s %f",
            //config.CAMERA_AUTOEXP? "True" : "False",
            //config.CAMERA_EXP);
//}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "uvc_camera");
	ros::NodeHandle nh("~");  // private nodehandle

	uvc::uvcROSDriver uvc_ros_driver(nh);

	// get params from launch file
	bool set_calibration, depth_map, primary_camera_mode;
	int number_of_cameras;
	std::string calibration_file_path;
	// TODO: check if parameter exist
	nh.getParam("numberOfCameras", number_of_cameras);
	nh.getParam("setCalibration", set_calibration);
	nh.getParam("depthMap", depth_map);
	nh.getParam("cameraConfigFile", calibration_file_path);
	nh.getParam("primaryCamMode", primary_camera_mode);

	//force cam number to be even
	if (number_of_cameras % 2 != 0){
      ++number_of_cameras;
    }

	// set parameters
	uvc_ros_driver.setNumberOfCameras(number_of_cameras);
	uvc_ros_driver.setPrimaryCamMode(primary_camera_mode);

	// initialize device
	uvc_ros_driver.initDevice();
	uvc_ros_driver.setCalibrationParam(0);
	uvc_ros_driver.setUseOfDepthMap(0);
	uvc_ros_driver.setCalibrationMode(false);

	// start device
	uvc_ros_driver.startDevice();
	// endless loop
	ros::spin();
	return 0;
}
