#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "windows.h"

#define log std::cout

int main() {
	
	std::ifstream fileIn;

    fileIn.open("./values.txt", std::ios::in);

    if(!fileIn.is_open()) {
        log << "Error while opening the file\n";

		// run the script to make the file with the default value
		system("createDefFile.bat");
        return 0;
    }

    // reading from the file
    std::string line;
    std::vector<std::string> prevValues(3); // [0] : minimum     [1] : maximum
    int i = 0;

    while (fileIn) {
        // Read a Line from File
        getline(fileIn, prevValues[i++]);
    }

	fileIn.close();

	const int minimumChargeLimit = stoi(prevValues[0]);
	const int maximumChargeLimit = stoi(prevValues[1]);

    while(1) {
		// https://learn.microsoft.com/en-us/windows/win32/api/winbase/ns-winbase-system_power_status?redirectedfrom=MSDN
        SYSTEM_POWER_STATUS status;
        GetSystemPowerStatus( &status);

        BYTE isCharging = status.ACLineStatus;
        int batteryPercentage = (int)status.BatteryLifePercent;

        // if(isCharging == 1)
        //     cout << "status.ACLineStatus:"<< " online" << "\n";
        // else if( isCharging==0 )
        //     cout << "status.ACLineStatus:"<< " offline" << "\n";


        // cout << "status.BatteryLifePercent:" << batteryPercentage << "\n";

        int snoozeTime = 120000; // 2min

        // if battery percentage is greater then 90 and charger is still pugedin
        if(batteryPercentage > maximumChargeLimit && isCharging) {
            
            // give the warning of UNPLUG THE CHARGER in the form of pop-up window

			// if pressed OK then snooze for 5 minutes
			// if pressed CANCEL then terminate the program
            LPCWSTR message = L"UN-PLUG THE CHARGER\n\nOK: To Snooze\nCancel: To completely ignore";
        	
			// step 1: construct the string having integer value
			std::string str = "Battery > " + std::to_string(maximumChargeLimit);
			// step2: convert teh string into LPCWSTR type
			std::wstring temp = std::wstring(str.begin(), str.end());
			LPCWSTR title = temp.c_str();

			// https://www.youtube.com/watch?v=C9msBx8DOVc
			// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
			AllocConsole();
        	int responce = MessageBoxW(NULL, message, title, 
				MB_OKCANCEL | MB_ICONWARNING | MB_DEFBUTTON1 | MB_SYSTEMMODAL);

			if(responce == IDCANCEL) {
            	std::cout << "cancel!\n";
            	break;
        	} 

			// snooze for 5 mins
			snoozeTime = 300000;	

        } else if (batteryPercentage < minimumChargeLimit && !isCharging) {
            //  give the warning of PLUG-IN THE CHARGER in the form of pop-up window

			// if pressed OK then snooze for 2 minutes
			// if pressed CANCEL then terminate the program

			LPCWSTR message = L"PLUG-IN THE CHARGER\n\nOK: To Snooze\nCancel: To completely ignore";
        	// LPCWSTR title = L"Battery < 50%";
			
			// step 1: construct the string having integer value
			std::string str = "Battery < " + std::to_string(minimumChargeLimit);
			// step2: convert teh string into LPCWSTR type
			std::wstring temp = std::wstring(str.begin(), str.end());
			LPCWSTR title = temp.c_str();

			// to convert the std::string to the LPCWSTR
			// https://www.geeksforgeeks.org/convert-stdstring-to-lpcwstr-in-c/
			// to change the `title` of the window dynamically.

			AllocConsole();
        	int responce = MessageBoxW(NULL, message, title, 
				MB_OKCANCEL | MB_ICONWARNING | MB_DEFBUTTON1 | MB_SYSTEMMODAL);

			if(responce == IDCANCEL) {
            	std::cout << "cancel!\n";
            	break;
        	} 

			// snooze for 2 mins
			snoozeTime = 120000;
        } 

        Sleep(snoozeTime);
    }

    return 0;
}
