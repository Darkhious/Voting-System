#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

void clearScreen() {
    system("cls");
}

string toCapital(string value) {
    for (int i = 0; i < value.length(); i++) {
        value[i] = toupper(value[i]); // Capitalize a word/sentence by converting each character to their uppercase equivalent
    }

    return value;
}

bool confirmValue(string value) {
    string reply;

    while (true) {
        cout << "\n Is " << value << " correct? (Y/N): ";
        getline(cin, reply);

        reply = toCapital(reply);

        if (reply[0] == 'Y') {
            return true;

            break; // Is there to ensure that the loop ends
        } else if (reply[0] == 'N') {
            return false;

            break; // Is there to ensure that the loop ends
        } else {
            cout << "\nERROR: A problem occured with confirming your input\n";
        }
    }
}

bool isDigit(string value) {
    for (int i = 0; i < value.length(); i++) {
        if (isdigit(value[i])) {
            continue;
        } else {
            return false;
        }
    }

    return true;
}

void saveFile(vector<string> voters) {
    ofstream list_of_voters("list_of_voters.save");

    for (string voter : voters) {
        list_of_voters << voter << "\n"; // Inserts each voters' name into a file
    }

    list_of_voters.close();
}

void assignPrecinct(vector<string> voters) {
    const int MAX_VOTERS = 30;

    int precinctCTR, ctr;

    precinctCTR = 2; // Starts at 2 because the display will automatically display 1
    ctr = 1;

    cout << "MASTERLIST OF PRECINCTS\n\n";
    cout << "PRECINT #1\n";
    for (string voter : voters) {
        cout << ctr << ".) " << voter << endl;

        if ((ctr % MAX_VOTERS) == 0) {
            cout << "\nPRECINT #" << precinctCTR << endl;

            ctr = 0; // Resets the counter
            precinctCTR++;
        }

        ctr++;
    }
}

string search(vector<string> voters) {
    string keyword, indices;
    int ctr, numOfResults;

    cout << "SEARCH FOR A NAME\n\n";

    cout << "Enter a keyword (Name/Letter | 0 to EXIT): ";
    getline(cin, keyword);

    if (keyword != "0") {
        indices = "";
        keyword = toCapital(keyword);
        ctr = 1;
        numOfResults = 0;

        for (string voter : voters) {
            if (voter.find(keyword) != string::npos) { // Locates the first occurence of the keyword in the name
                cout << ctr << ".) " << voter << endl;

                indices += to_string((ctr - 1)) + " ";

                numOfResults++;
            }

            ctr++;
        }

        cout << "\n" << numOfResults << " MATCH RESULTS FOUND!\n";

        return indices;
    }

    return " ";
}

int removeVoter(string indices) {
    vector <string> matchResults = {};

    string userInput, index;
    bool isNumber;

    isNumber = false;
    if (indices != " ") {
        index = "";
        for (int i = 0; i < indices.length(); i++) { // Compiles the results from a string, and transfers it to a vector for reference
            if (indices[i] != ' ') {
                index += indices[i];
            } else {
                matchResults.push_back(index);

                index = "";
            }
        }

        do {
            cout << "Enter the number of the name you want to remove (0 to Cancel): ";
            getline(cin, userInput);

            isNumber = isDigit(userInput);
        } while (!isNumber);

        if (isNumber) {
            index = to_string(stoi(userInput) - 1);

            auto result = find(matchResults.begin(), matchResults.end(), index); // Searches for a valid index

            if (result != matchResults.end()) {
                return stoi(index);
            } else {
                return -1; // Returns a negative value signifying false
            }
        }
    }

    return -1;
}

// DATABASE
void database(int action, string name) {
    static vector <string> voters = {};

    string userInput, indices;
    int index;

    switch (action) {
        case 0: // Sorts and Saves the list of voters into a file
            sort(voters.begin(), voters.end());

            saveFile(voters);

            break;
        case 1: // Loads/Adds voters name to the vector
            voters.push_back(name);
            
            break;
        case 2: // Removes voters
            indices = search(voters);
            index = removeVoter(indices);
            
            if (index >= 0) {
                voters.erase(voters.begin() + index);

                database(0, ""); // Sends a command for itself to sort and save the updated voters
            }

            break;
        case 3: // Assigns voters to a precinct
            assignPrecinct(voters);

            break;
        default:
            cout << "\nERROR: Invalid database action!\n";
    }
}

void loadFile() {
    string name;

    ifstream list_of_voters("list_of_voters.save");
    if (list_of_voters.is_open()) {
        while (getline(list_of_voters, name)) {
            name = toCapital(name);

            database(1, name);
        }

        list_of_voters.close();

        database(0, ""); // Sends a command for the database to save the list of voters. This will overwrite the old file
    }
}

void addVoter() {
    string lastName, firstName, middleName, fullName;
    bool correctData;

    do {
        cout << "Please fill out the required information:\n";
        
        cout << "Enter last name: ";
        getline(cin, lastName);
        cout << "Enter first name: ";
        getline(cin, firstName);
        cout << "Enter middle name: ";
        getline(cin, middleName);

        fullName = lastName + ", " + firstName + " " + middleName;
        fullName = toCapital(fullName);

        correctData = confirmValue(fullName);
    } while (!correctData);

    if (correctData) {
        database(1, fullName); // Sends the name to the database
        database(0, ""); // Auto-saves the list of names to immediately create a load file incase of crash
    }
}

/*

FORMULA:
hashCode = x₁*P⁰ + x₂*Pⁱ + x₃*P² ... xₙ*Pⁿ⁻ⁱ

*/
int toHash(string key) {
    const int PRIME_CONST = 31;
    
    int hashCode = 0;

    for (int i = 0; i < key.length(); i++) {
        hashCode += key[i] * pow(PRIME_CONST, i);
    }

    return hashCode;
}

bool logIn() {
    string username, password, key;

    while (true) {
        cout << "Enter username: ";
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);

        password = to_string(toHash(password));

        ifstream adminFile(username + ".save");
        if (!adminFile.is_open()) {
            cout << "\nERROR: Username or password is wrong!\n";
        } else {
            getline(adminFile, key);
            
            if (password == key) {
                return true;
            } else {
                cout << "\nERROR: Username or password is wrong!\n";
            }

            adminFile.close();
        }
    }
}

void mainMenu() {
    string userInput;

    cout << "MAIN MENU\n\n";
    cout << "1.) Add a Voter \n2.) Remove a Voter \n3.) Update Voter's Name \n4.) Display Precincts \n5.) Start Voting \n6.) Exit\n\n";

    cout << "Select from the Menu (1/2/3/4/5/6): ";
    getline(cin, userInput);

    if (isDigit(userInput)) {
        switch (stoi(userInput)) {
            case 1:
                addVoter();

                break;
            case 2:
                database(2, "");

                break;
            case 3:


                break;
            case 4:
                database(3, "");

                break;
            case 5:

                break;
            case 6:

                break;
            default:
                cout << "\nERROR: Invalid selection from the main menu!\n";
        }
    }
}

int main() {
    bool loggedIn;

    // SETS UP THE SYSTEM...
    clearScreen();
    loadFile();
    loggedIn = logIn();

    while (loggedIn) {
        clearScreen();

        mainMenu();
    }

    return EXIT_SUCCESS;
}
