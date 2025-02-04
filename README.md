# Unreal Engine 5 Agricultural Robot Simulation

This repo host the Unreal Engine 5 part for the simulation, there is a seperate [ROS repo](https://github.com/NCSU-BAE-ARLab/AgriRoboSim_ROS) that work along side this simulation. 

[poster](https://drive.google.com/file/d/1NSpDXXA8XAvhLl7YAn9lH2GgQGdDXhRv/view?usp=drivesdk)



`AgriRoboSim` contains the current project in development using UE5.3.

`Test2` contains UE5.1 version (outdated). `Test2 5.2` contains UE5.2 version (outdated).

*Important*: The Megascans assets (materials and plants) are not part of this repo, so you need to download those later from UE5 or the scenes will have missing high-quality plants and textures.

## Usage (.exe), Recommended

The packaged application cannot be uploaded under Github release because it is greater than 2GB.

The simplest way to use is by downloading the packaged "game" (2.8 GB after unzip) through Mediafire linked below, only windows build for now: [https://www.mediafire.com/file/fq5qipsuocxgbdz/AgriculturalRobotSimulation_UE5Build.7z/file](https://www.mediafire.com/file/fq5qipsuocxgbdz/AgriculturalRobotSimulation_UE5Build.7z/file)

Or OneDrive link because Mediafire can be slow: [https://1drv.ms/u/s!AuM5Q-daepZAitkkKQ_B1UWMQq_jvw?e=QrW16N](https://1drv.ms/u/s!AuM5Q-daepZAitkkKQ_B1UWMQq_jvw?e=QrW16N)

To control it using ROS, I recommend installing Windows Subsystem for Linux (WSL) Ubuntu 20.04. Then follow instructions of this repo for ROS packages [https://github.com/NCSU-BAE-ARLab/AgriRoboSim_ROS](https://github.com/NCSU-BAE-ARLab/AgriRoboSim_ROS).

## Usage (UE5 editor)
This is tested on a windows 11 desktop, the UE5 simulation runs in Windows, the ROS part runs in WSL with rosbridge for communications (see separate repo for usage).

Note: The repository do not contain plant assets or materials because they are from Quixel and take a lot of storage.

1. Clone repo in file manager and navigate to `Plugin` folder inside `Test2` or `Test2 5.2`
2. Clone [ROSIntegration repo](https://github.com/code-iai/ROSIntegration) in `Plugin` folder under the cloned repo
3. Launch UE5.3 in the Launcher
4. `Browse` and select the `AgriRoboSim.uproject` to open the project
5. Accept the prompt to rebuild now (wait for several minutes)
6. The project should open, the default level is `2-robot_plant_vis`, it should contain two ur10 arms and a room with missing textures.
7. Before fixing plants and textures, you might want to change settings for ROS communications by editing the `ROS_UR10e` blueprint under `ur10e` folder. For specifics see [ROSIntegration](https://github.com/code-iai/ROSIntegration), but I left it to use WebSockets over localhost.
8.  To fill the textures, go to Quixel Megascans to download some materials and plants by `Window -> Quixel Bridge` at the top of the editor.
9.  To segment the plant, navigate to Content/Assets/Plants and add entry in `PlantCollection_DT` and you can switch the plant by the `Change Plant` function during play.
10. The simulation can be run alone, but to control the arm and capture images, I recommend using the [ROS part of the repo](https://github.com/XingjianL/AgriRoboSim_ROS).

# Images
Point cloud reconstructed from the simulation using RGBD images and segmentation masks using 24 setpoints.
![](./readme_images/RGBD_PointCloud_Sample.png)
