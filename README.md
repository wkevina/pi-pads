pi-pads
=======

# Hardware and software to hook up your old Super Nintendo gamepads to a Raspberry Pi

## Goals:


pi-pads is a project to develop a hardware interface to connect SNES gamepads (joysticks or controllers) to a Raspberry Pi, as well as driver software to allow them to be used in emulators and games.

That being the primary goal of the project, a secondary but still important goal is to do a hardware project right.  There are a lot of open-source hardware projects out there, but few make it easy to find what you're looking for if you want to get into the technical aspects of them.  For example, I'm a machinist, and so I wanted to see the technical drawings of the Arduino Duemilanove.  Well, I couldn't find it, only a version for the Uno.  I trust they are similar, but I still I had to do a lot of digging to find something that wasn't quite what I wanted.

I don't want pi-pads to suffer from that problem.  If you come across this project and want to know something and can't find it, please let me know.  If it's something that hasn't been created or is organized poorly, let's streamline that.  When the software comes along, I want you to know how to get it, how to install it, and *what* to install it on.  Everything should have context so that you can make use of it.

## Hardware:


This system is intended to work with the Raspberry Pi single board computer from [The Raspberry Pi Foundation](http://www.raspberrypi.org/).

It will consist of a hardware module which connects to the Raspberry Pi's GPIO header, and will have connectors for two Super Nintendo gamepads.  Alternate versions could use a different connector for other controllers, requiring only a firmware change to support them.

The module will use an Atmega328 processor, popularly known as the core of the [Arduino platform](http://arduino.cc).

The module will communicate with the Raspberry Pi using the SPI communication bus.  An alternate interface may be developed if it turns out that this project is often used in conjunction with hardware that needs to use both channels of the SPI bus.  pi-pads should be easy to integrate into your custom project.  As a project we'll try to play nice with the hardware you want to use.

## Software:

The software for pi-pads will be a driver for the Raspian Linux distribution that runs on the Raspberry Pi.  The device will show up on the filesystem as `/dev/input/js0` and `/dev/input/js1`, if using both controllers.  

It is intended that the driver will be implemented in userspace as much as possible.  What this means is that bugs in the pi-pads driver will be unlikely to upset the stability of the whole system.  You may be running a server on your Raspberry Pi, and wouldn't want the gamepad thing you're messing with to bring the whole thing down.

## Right now:


Everything is at a pre-pre-alpha status; basically, planning.  In addition to investigating the technical details of the hardware and software, I'm looking for tools that will allow me to document the process.  The most important piece I need to find is a way to create schematics and put them under version control.  I am working from a Mac, which has no good tools for schematic capture that I'm aware of other than Eagle, and I would like to use a tool that would be easy for the community to open.  Once that is found, hardware revisions will begin showing up.

# What you can do:


Offer suggestions for documentation tools, pointers to similar projects or other well-run hardware projects, and offer emotional support or expertise on Linux driver development.
