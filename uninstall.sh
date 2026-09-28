#!/bin/sh

echo -e "WARNING! Your local directory '~/storage' will be DELETED! Do you want to continue?
[n]o/[y]es"
read -n 1 ANS
echo
if [ ${ANS} == "y" ]; then
		if [ -e "../storage" ]; then
			sudo rm -rf ~/storage/
			echo -e "'~/storage/' directory was deleted"
		fi

		if [ -e "storage" ]; then
			rm -f storage
			echo -e "'storage' program was deleted"
		fi

		if [ -e "usbdevice" ]; then
			rm -f usbdevice
			echo -e "'usbdevice' file was deleted"
		fi


		echo -e "Deinstallation was finished"

elif [ ${ANS} == "n" ]; then
		echo -e "Deleting was canceled"
else
		echo -e "Something went wrong!"
fi
