#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

static const char mnt[] = "ls /mnt";
static const char stor[] = "ls ~/storage/";


bool do_mount(FILE *stream)
{
	char old[128] = "sudo mount ";
	char dev[32];
	char mnt_[7] = " /mnt";

	if (fgets(dev, sizeof dev, stream) !=NULL)
	{
		dev[strcspn(dev, "\n")] = '\0';
	}

	strcat(old, dev);
	strcat(old, mnt_);

	int i = system(old);

	if (i == 0)
	{
		printf("USB Flash was mounted\n");
		return true;
	}
	else 
	{
		printf("Something went wrong!\n");
		return false;
	}
}

bool do_umount()
{
	printf("USB Flash is unmounting. Don't do anything\n");
	int i = system("sudo umount /mnt");
	while (true)
	{
		if (i == 0)
		{
			printf("USB Flash was unmounted\n");
			return true;
		}
		else if (i == 1)
		{
			printf("Something went wrong!\n");
			return false;
		}
	}
}

void out()
{
	printf("Choose action\n\n[1] - Copy from USB\n[2] - Move from USB\n[3] - Copy to USB\n[4] - Move to USB\n[5] - Delete local storage directory\n[6] - Format USB\n[7] - Rename local storage directory\n[0] - Quit programm\n\n");
}

int main()
{
	
	bool ok;

	FILE *fp = fopen("./usbdevice", "r");
	if (fp == NULL)
	{
		perror("fopen");
		exit(1);
	}

	ok = do_mount(fp);
	if (!ok)
	{
		exit(1);
	}

	fclose(fp);
	system("clear");

	while (true)
	{

		out();

		unsigned int act = 0;
	
		scanf("%u", &act);
	
		switch(act)
		{
			case(1): // Copy from USB
			{
				system(mnt);

				char i;
	
				printf("Do you want to COPY ALL to your storage?\n[y]es/[n]o\n\n");
				scanf(" %c", &i);
	
				if (toupper(i) == 'Y')
				{
					printf("Enter directory name (64)\n");

					char name [65];
					
					scanf("%s", name);
					
					char create [100] = "mkdir -p ~/storage/";
					char cp [100] = "sudo cp -r /mnt/* ~/storage/";
					
					strcat(create, name);
					strcat(cp, name);

					system(create);

					printf("Coping...\n");

					system(cp);

					break;
				}
				else if (toupper(i) == 'N')
				{
					break;
				}
				else {printf("Incorrect input\n");break;}	
			}
			case(2): // Move from USB
			{
				system(mnt);
				
				char i;

				printf("Do you want to MOVE ALL to your storage?\n[y]es/[n]o\n\n");
				scanf("%c", &i);
	
				if (toupper(i) == 'Y')
				{
					printf("Enter directory name (64)\n");

					char name [65];
					
					scanf("%s", name);
					
					char create [100] = "mkdir -p ~/storage/";
					char mv [100] = "sudo mv /mnt/* ~/storage/";
					
					strcat(create, name);
					strcat(mv, name);

					system(create);

					printf("Moving...\n");

					system(mv);

					break;
				}
				else if (toupper(i) == 'N')
				{
					break;
				}
				else {printf("Incorrect input\n");break;}	
			}
			case(3): // Copy to USB
			{
				system(stor);
				printf("What directory do you want to copy on USB?\n");

				char name [65];
	
				scanf("%s", name);

				char cp [100] = "sudo cp -r ~/storage/";
				char res [6] = " /mnt";

				strcat(cp, name);
				strcat(cp, res);

				printf("Copying...\n");

				int i = system(cp);
				if (i != 0)
				{
					printf("No such directory\n");
				}

				break;
			}
			case(4): // Move to USB
			{
				system(stor);
				printf("What directory do you want to copy on USB?\n");

				char name [65];
	
				scanf("%s", name);

				char mv [100] = "sudo mv * ~/storage/";
				char res [6] = " /mnt";

				strcat(mv, name);
				strcat(mv, res);

				printf("Moving...\n");

				int i = system(mv);
				if (i != 0)
				{
					printf("No such directory\n");
				}

				break;
			}
			case(5): // Delete current directory
			{
				system(stor);
				printf("What directory do you want to delete?\n");

				char name [65];
	
				scanf("%s", name);

				char mv [100] = "rm -r ~/storage/";

				strcat(mv, name);

				printf("Deleting...\n");

				int i = system(mv);
				if (i != 0)
				{
					printf("No such directory\n");
				}
				
				break;
			}
			case(6): // Format USB
			{
				system(mnt);
				printf("Do you REALY want to format ALL files on your USB?\n[y]es/[n]o\n");

				char i;
				scanf("%c", &i);

				if (toupper(i) == 'Y')
				{
					printf("Formating...");
					system(mnt);
					system("sudo rm -r ./*");

					printf("Your USB device was formated successfuly\n");
				}
				else if (toupper(i) == 'N')
				{
					break;
				}
				else
				{
					printf("Incorrect input\n");
				} 

				break;
			}
			case(7): // Rename directory
			{
				system(stor);
				printf("Select directoy to RENAME\n\n");

				char name[65];
				scanf("%s", name);

				char rn[131] = "mv ";
				char new_name[65];
				char space[2] = " ";

				printf("Enter new directory NAME\n\n");
				scanf("%s", new_name);

				strcat(rn, name);
				strcat(rn, space);
				strcat(rn, new_name);

				int done = system(rn);

				if (done == 0)
				{
					printf("Directory was RENAMED\n");
				}
				else 
				{
					printf("Something went wrong\n");
				}

				break;
			}
			case(0):
			{
				printf("Exiting...\n");
				do_umount();
				exit(0);
				break;
			}
			default:
			{
				printf("Incorrect input\n");
				break;
			}
		}
	}
}
