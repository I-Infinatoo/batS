#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#define log std::cout

void printHelp() {
    std::cout << "\n'changeLimit' changes the upper and lower limit of the 'batS'";
    std::cout << "\nchangeLimit receives two arguments as follows:\t";
    std::cout << "changeLimit <lower limit> <upperlimit>\n\n";

    std::cout << "\n\t( 1 < lower limit < upper limit < 99 )\n\n";

    std::cout << "-r\t\tTo reset the limits to their default values\n";
    std::cout << "-h | --help\t for help\n";

    std::cout << "\nAfter changing the limits or resetting the values 'System Restart'";
    std::cout << " is required' to successfully change the limits.";
}

int main (int argc, char *argv[]) {

    /**
     * @brief 
     * file name : values.txt
     * 
     * arg[0] : program name
     * arg[1] : minimum val
     * arg[2] : maximum val
    */

    /**
     * @brief 
     * if argc == 0
     * then, run the script to generate the new file ```values.txt``` with the default values  
    */

    // log << argv[0] << " => " << argv[1] << " : " << argv[2] << "\n";
    if(argc == 1) {
        printHelp();
        return 0;
    }
    if(argc == 2) { 
        std::string argv1 = argv[1];
        if(argv1 == "-h" || argv1 == "--help") { printHelp(); }
        if(argv1 == "-r") { system("createDefFile.bat"); }
        return 0;
    }
    
    // input validation
    if(argv[1] < to_string(1) && argv[2] > to_string(99) && stoi(argv[1]) > stoi(argv[2])) {
        std::cout << "\nEnter valid limits!\nUse -h or --help for more info";
        return 0;
    }

    ifstream fileIn;
    fileIn.open("values.txt", std::ios::in);
    
    if(!fileIn.is_open()) {
        log << "Error while opening the file!\n";
        return 0;
    }

    // reading from the file
    string line;
    vector<string> prevValues(3); // [0] : minimum     [1] : maximum
    int i = 0;

    while (fileIn) {
        // Read a Line from File
        getline(fileIn, prevValues[i++]);
    }
    std::cout << "\nPrevious Values:\nMinimum Charge Value: " << prevValues[0];
    std::cout << "\nMaximum Charge Value: " << prevValues[1] << "\n";
    // closing the file
    fileIn.close();


    ofstream fileOut;
    fileOut.open("values.txt", std::ios::out);

    if(!fileOut.is_open()) {
        log << "Error while opening the file\n";
        
        /*
            run the script for the default values
        */
        system("createDefFile.bat");
        return 0;
    }

    // writing in the file
    fileOut << argv[1] << "\n" << argv[2];
    // closing the file
    fileOut.close();

    std::cout << "\nUpdated Values:\nMinimum Charge Value: " << argv[1];
    std::cout << "\nMaximum Charge Value: " << argv[2] << "\n";

    std::cout << "\nSystem Restart is required to experience the effect!\n";
    
    return 0;
}