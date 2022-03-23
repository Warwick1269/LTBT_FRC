# EveryBot
EveryBot program for FRC in CPP

## Getting started

### Setting up driverstation/programming laptop

- Programming Tools
	1. Install wpilibsuite. From this site -> https://github.com/wpilibsuite/allwpilib/releases, scroll down to the bottom and install wpilib from the operating system you need. E.g, Windows64 if you use windows, and it's 64 bit. More in depth instructions can be found here https://docs.wpilib.org/en/stable/docs/zero-to-robot/step-2/wpilib-setup.html

	2. Once you have installed all the tools needed (this also includes VSCode the prefered text editor) you can download the code for the everybot. You can either clone it using git, or you can download it from github. If you plan on cloning, you will need to install git from https://git-scm.com/downloads

	3. After this is complete you can open the EveryBot directory inside of VSCode (Note that this is different to VS). From here you can edit the program to how you need. All robot code should be placed within `src/main/cpp/` for cpp files and `src/main/include/` for header files.

- FRC Utilities. Driverstation, radio config & rio imager
	1. To install all of these tools, NI (National Instruments) has an installer to easily download all of these utilities. https://www.ni.com/en-au/support/downloads/drivers/download.frc-game-tools.html#369633. These tools are only for Windows, and cannot be used on other platforms such as macOS and Linux. You can download the Radio Configuration utility from https://firstfrc.blob.core.windows.net/frc2020/Radio/FRC_Radio_Configuration_20_0_0.zip

	2. FRC uses the teamnumber to identify robots on field using the field management system. As such, we need to configure our Radio & Rio to that team number. E.g `4788` which is Curtin Universities team number. To configure your radio, you can use these steps https://docs.wpilib.org/en/stable/docs/zero-to-robot/step-3/radio-programming.html. The radio confiurator is usually updated every year, but has not changed since for 2021, this has caused a known bug with newer versions of Java 8. To solve this we need to install the older version of Java which we can do by installing the 2020 version of wpilib suite https://github.com/wpilibsuite/allwpilib/releases/tag/v2020.3.2, and only selecting java to download. The radio configurator will automatically use that version intead of others. You can see detailed instructions of this bug and how to fix it here https://docs.wpilib.org/en/latest/docs/yearly-overview/known-issues.html.

	3. Imaging the Roborio. Just like the Radio, the RoboRio also needs to be imaged with the latest software to be compatible, it also needs to be imaged with the correct team number. The Imaging software should have been downloaded with the rest of the tools from step 1. Open the software named `roboRio Imageing Tool` and plug you computer directy into the USB type B port on the rio. After scanning for the rio, you should be able to enter a team number and then select reformat. (Make sure you are using the latest firmware, 2021 V3 should be slected). This will take a few minutes to compete.


### Programming

- Team number
	1. The team number needs to be specified in order to send the code to the robot over wifi or cable. You can change this by heading to `build.gradle` and changing the line which says `team = XXXX` to `team = YOUR_NUMBER`

	2. Programming the robot itself is a little more complicated, but there are instructions which you can follow from here https://docs.wpilib.org/en/stable/docs/software/vscode-overview/creating-robot-program.html a few of the first steps have already been completed, this is because we have already setup our project.

	3. The controllers that the everybot use by default are the f310's. Which need to use raw input in order to use them. You can see steps here for them https://mililanirobotics.gitbooks.io/frc-electrical-bible/content/CPP/the_joystick.html

	![Raw Input Numbers for F310](images/gamepadlabel.jpg)

	4. CLI, BUILD/DEPLOY. The tutorials for building and deploying the robot code use the WPI extention. But you can do this from command line interface as well if need be. The steps for building the program is quite simple, you can either use the wpi extension by clicking on the logo in vscode, and then slecting build robot code. Or you can open up a terminal/CMD and navigate to the directory that your program is located in. And while in that directory you can run `gradlew build` or `./gradlew build` depending on your OS/Terminal.

	Deploying code is as simple, but requires a lot of the previous steps to be complete, this includes the Radio being configured with the right team number, the rio imaged/formated with the correct team number, and the code also set using the right team number. After all of those steps are complete, you can connect to your robot either through a USB cable to the USB type B port, or the better version, over wifi by connecting to the radio. After this you can either select the wpi logo in vscode and select deploy robot code. Or you can go into the terminal/cmd and navigate to the dirtectory and deploy using these commands `gradlew deploy` or `./gradlew deploy`. This will locate your Rio using the ip address `10.TE.AM.2`, where TEAM is your team number that you specified in code. And then it will deploy all code to your Robot which you can then connect to using the driverstation.

### Driverstation

- Using driverstation
	1. The driverstation has some decent documentation and does not need much to be covered. You can find the documentation here https://docs.wpilib.org/en/stable/docs/software/driverstation/driver-station.html

	2. However, a quick setup is as follows. First open the software. Then connect to your robot over wifi (you can also connect via a USB type B cable). Then in the settings tab of the driverstation you can change the team number. (The driverstation will not connect to the robot unless you input the correct team number). In the USB tab you can see the controllers connected to the computer you are using. You can also drag your controllers in different orders. The orders starting from zero upwards, are ports. If your code specifies that a controller is on port zero. And uses that, then you will need to have a controller on port zero in driverstation. (Sometimes these will get randomly placed, it's a good idea to check to see what controllers are where and to fix them up before driving). 

	3. After the above, you can select either teleop, auto, practice or test and the select enable. To quickly disable you can hit enter on the keyboard. You can also hit space bar, which will e-stop the robot and will require you to reset the roborio by hand, or re deploy code.

	(Note that if you only have code in the teleop function inside of Robot.cpp, then only the Teleop tab will work, as each tab corrolates to the specified function inside of Robot.cpp).

