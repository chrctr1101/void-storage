#!/bin/sh

echo -e "Start installing Void-storage...\n"
sleep 1s

echo -e "Creating storage directory\n"
sleep 0.5s
mkdir -p ~/storage

echo -e "Enter your USB device way (like /dev/sda1)"
read WAY
echo $WAY > usbdevice
echo -e "${WAY} was writed"

echo -e "Compillating sources form /src..."
gcc src/storage.c -o storage

if [ -f "storage" ]; then
	echo -e "Application was compilled"
	chmod +x storage
else
	echo -e "Something went wrong!\nIf you have enough knowledge try to fix it yourselves\nElse send me a message on GitHub.com"
fi
