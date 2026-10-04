#!/bin/bash

echo -e "Start installing Void-storage...\n"
sleep 1s

echo -e "Creating storage directory\n"
sleep 0.5s
mkdir -p ~/storage

echo -e "Creating 'usbdevice' file"
touch usbdevice

echo -e "Enter your USB device way (like /dev/sda1)"

lsblk

read WAY
echo $WAY > usbdevice
echo -e "${WAY} was writed"

echo -e "Building sources form /src..."
gcc src/storage.c -o storage

if [ -e "storage" ]; then
	echo -e "Application was builded"
	chmod +x storage
else
	echo -e "Something went wrong!\nIf you have enough knowledge try to fix it yourselves\nElse send me a message on GitHub.com"
fi
