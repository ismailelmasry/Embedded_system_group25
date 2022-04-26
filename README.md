# Embedded_system_group25
This is a github repository for the DBL Embedded systems group 25.

Project Description: 

The main project assignment, is to simply build an embedded system - a robot in this case -
together with your group members. There is a basic assignment which you can follow, but you
are encouraged to use your own creativity and come up with alternative ideas and challenges.
The robot you build will become part of a larger factory floor on which the robots of other
groups also operate. This means you have to adapt your design to fit the floor, but it also gives
opportunities for additional challenges.

The center-piece of the assignment is a conveyor belt system, called the factory floor, provided
by the practicum coordinator. On this factory floor, there are black and white disks being moved
around. The goal of the basic assignment is to build a sorting robot that is able to pick those disks
from the belt and sort them for color, putting the white disks in one bucket and putting the black
disks in another. Ideally, the robot should be designed in such a way that it takes the behavior
of other robots on the belt into account, and maintains a ‘fair’ distribution of disks among the
robots without knowing how many robots are in operation at any given time. For this, the robots
will have to communicate with one another somehow (that is a topic we’ll discuss later).
Typically, a simple sorting robot will have a pushing mechanism for removing disks from the
belt, a light sensor for determining the presence of a disk and another light sensor for determining
its color (black/white). Finally, there will be a mechanism for putting a disk in one bucket or
another. These actuators and sensors will be connected by a piece of software that implements a
collecting and sorting strategy.
Examples of how to use light sensors to detect the presence of disks can be found online, but
some experimentation will be necessary to figure out how to use light sensors to determine the
color (black or white) of a disk. As a hint, use the fact that a white disk reflects considerably more
light than a black one.
This scenario sketches the ‘happy flow’ of the robot; all behavior that is necessary for it to
achieve its function. However, during this DBL you will notice that physical machines seldom
follow the intended scenario exactly, and you are expected to consider the possibility of faults
and failures of the electronics and mechanics (as well as purposeful obstructions by a demonic
supervisor during demos). A simple sorting robot will also have functionality in its software,
like time-outs and other measurements, to ascertain that the physical robot is still functioning
according to expectations. Furthermore, if the robot seems to be malfunctioning, the software
should report this to the other robots on the factory floor, and take appropriate action itself. You
cannot possibly catch all possible faults and failures, but a good design includes a study of which
faults and failures might occur, which effects this will have on the operation of the robot, and
includes remedies for the ones deemed most important.
