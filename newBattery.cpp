#include <iostream>
#include "windows.h"

using namespace std;

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

        // if battery percentage is greater then 90 and charger is still pugedin
        if(batteryPercentage > 90 && isCharging) {
            
            // give the warning of UNPLUG THE CHARGER in the form of pop-up window

			// if pressed OK then snooze for 5 minutes
			// if pressed CANCEL then terminate the program
            LPCWSTR message = L"UN-PLUG THE CHARGER\n\nOK: To Snooze\nCancel: To completely ignore";
        	LPCWSTR title = L"Battery > 90%";

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

        } else if (batteryPercentage < 50 && !isCharging) {
            //  give the warning of PLUG-IN THE CHARGER in the form of pop-up window

			// if pressed OK then snooze for 2 minutes
			// if pressed CANCEL then terminate the program

			LPCWSTR message = L"PLUG-IN THE CHARGER\n\nOK: To Snooze\nCancel: To completely ignore";
        	LPCWSTR title = L"Battery < 30%";

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