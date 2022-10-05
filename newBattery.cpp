#include <iostream>
#include "windows.h"

void stringToLPCWSTR(std::string &str, LPCWSTR &title) {

	// Initializing a string object
	// string str = "GeeksforGeeks";

	// Initializing an object of wstring
	std::wstring temp = std::wstring(str.begin(), str.end());

	// Applying c_str() method on temp
	// LPCWSTR wideString = temp.c_str();
	title = temp.c_str();

	// Print strings
	// cout << "str is : " << str << endl;
	// wcout << "wideString is : "
	// 	<< wideString << endl;
}

int main() {

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
		const int maximumChargeLimit = 88;
		const int minimumChargeLimit = 50;

        // if battery percentage is greater then 90 and charger is still pugedin
        if(batteryPercentage > maximumChargeLimit && isCharging) {
            
            // give the warning of UNPLUG THE CHARGER in the form of pop-up window

			// if pressed OK then snooze for 5 minutes
			// if pressed CANCEL then terminate the program
            LPCWSTR message = L"UN-PLUG THE CHARGER\n\nOK: To Snooze\nCancel: To completely ignore";
        	LPCWSTR title;

			std::string str = "Battery > " + std::to_string(maximumChargeLimit);
			stringToLPCWSTR(str, title);

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
			LPCWSTR title;

			std::string str = "Battery < " + std::to_string(minimumChargeLimit);
			stringToLPCWSTR(str, title);

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