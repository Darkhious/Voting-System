#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

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

void saveFile(vector<string> voters) {
    ofstream list_of_voters("list_of_voters.txt");

    for (int i = 0; i < voters.size(); i++) {
        list_of_voters << voters[i] << endl; // Inserts each name inside the voters vector into the list_of_voters file
    }
}

void database(int action, string name) {
    vector<string> voters = {};

    switch (action) {
        case 0: // Sorts and Saves the list of voters into a file
            sort(voters.begin(), voters.end());

            saveFile(voters);

        case 1: // Loads/Adds voters name to the vector
            voters.push_back(name);
            
            break;
        default:
            cout << "\nERROR: Invalid database action!\n";
    }
}

void loadFile() {
    string name;

    ifstream list_of_voters("list_of_voters.txt");
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

    cout << "Please fill out the required information:\n";
    
    cout << "Enter last name: ";
    getline(cin, lastName);
    cout << "Enter first name: ";
    getline(cin, firstName);
    cout << "Enter middle name: ";
    getline(cin, middleName);

    fullName = lastName + ", " + firstName + " " + middleName;
}

int main() {
    

    return 0;
}
