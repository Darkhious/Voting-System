
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <map>

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
        cout << "\nIs " << value << " correct? (Y/N): ";
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

string getName() {
    string lastName, firstName, middleName, fullName;

    cout << "========================================\n";
    cout << "           PERSONAL INFORMATION!        \n";
    cout << "========================================\n"<<endl;

    cout << "Enter last name: ";
    getline(cin, lastName);
    cout << "Enter first name: ";
    getline(cin, firstName);
    cout << "Enter middle name: ";
    getline(cin, middleName);

    fullName = lastName + ", " + firstName + " " + middleName;
    fullName = toCapital(fullName);

    return fullName;
}

int getAge() {
    string userInput;
    bool correctData;

    do {
        cout << "Enter age: ";
        getline(cin, userInput);

    } while (!isDigit(userInput));

    if (stoi(userInput) >= 18) {
        return stoi(userInput);
    }

    return 0;
}

string getSex() {
    string sex;
    bool correctData = false;

    cout << "========================================\n";
    cout << "           PERSONAL INFORMATION!        \n";
    cout << "========================================\n"<<endl;
    do {
        cout << "Enter sex (M/F): ";
        getline(cin, sex);

        sex = toCapital(sex);

        if (sex == "MALE") {
            sex = "M";
        } else if (sex == "FEMALE") {
            sex = "F";
        }

        if (sex == "M" || sex == "F") {
            correctData = true;
        }
    } while (!correctData);

    return sex;
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

    cout << "=====================\n";
    cout << "       LOG-IN        \n";
    cout << "=====================\n"<<endl;
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

void saveFile(vector<string> voters) {
    ofstream list_of_voters("list_of_voters.save");

    for (string voter : voters) {
        list_of_voters << voter << "\n"; // Inserts each voters' name into a file
    }

    list_of_voters.close();
}

void saveFile(map<string, string> candidates, string position) {
    ofstream list_of_voters("list_of_" + position + ".save");

    for (auto candidate : candidates) {
        list_of_voters << candidate.first << "\n" << candidate.second << "\n"; // Inserts each voters' name into a file
    }

    list_of_voters.close();
}

void assignPrecinct(vector<string> voters) {
    const int MAX_VOTERS = 5;

    string userInput;
    int precinctCTR, ctr;

    precinctCTR = 2; // Starts at 2 because the display will automatically display 1
    ctr = 1;

    clearScreen();
    cout << "=================================\n";
    cout << "      MASTERLIST OF PRECINTS     \n";
    cout << "          PRECINT #1             \n";
    cout << "=================================\n"<<endl;
    for (string voter : voters) {
        cout << ctr << ".) " << voter << endl;

        if ((ctr % MAX_VOTERS) == 0) {
            cout << "\nPRECINT #" << precinctCTR << endl;

            ctr = 0; // Resets the counter
            precinctCTR++;
        }

        ctr++;
    }

    cout << "Enter anything to continue: ";
    getline(cin, userInput);
}

string search(vector<string> voters) {
    string keyword, indices;
    int ctr, numOfResults;

    clearScreen();
    cout << "SEARCH FOR A NAME\n\n";
    cout << "===========================\n";
    cout << "    SEARCG FOR A NAME!     \n";
    cout << "===========================\n"<<endl;

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

void search(map<string, string> candidates) {
    vector<string> partyList = {};

    int ctr;

    // ADDS THE PARTY-LIST TO THE VECTOR
    for (auto candidate : candidates) {
        if (find(partyList.begin(), partyList.end(), candidate.second) != partyList.end()) {
            continue;
        } else {
            partyList.push_back(candidate.second);
        }
    }

    for (int i = 0; i < partyList.size(); i++) {
        cout << partyList[i] << endl;

        ctr = 1;
        for (auto candidate : candidates) {
            if (candidate.second == partyList[i]) {
                cout << ctr << ".) " << candidate.first << endl;
            }

            ctr++;
        }
    }
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
            cout << "=====Enter the number of the name you want to remove (0 to Cancel): =====";

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

int voteNow(vector<string> candName, map<string, string> candidates, string position) {
    string userInput, candidate;
    bool correctData;

    do {
        clearScreen();
        cout << position << "\n\n";

        search(candidates);

        cout << "Enter the number of the candidate to vote: ";
        getline(cin, userInput);

        if (isDigit(userInput)) {
            candidate = candName.at(stoi(userInput) - 1);
        }

        correctData = confirmValue(candidate);
    } while (!isDigit(userInput) && !correctData);

    int i = 0;
    // LINEAR SEARCH
    for (auto element : candName) {
        if (element == candidate) {
            return i;
        }

        i++;
    }

    return 0;
}

void produceResult(vector<string> candidates, vector<int> votes, string filename, string position) {
    const int TYPES_OF_CANDIDATES = 3;

    ofstream result(filename, fstream::app);

    result << "\n\n" << position << "\n\n";
    for (int i = 0; i < candidates.size(); i++) {
        result << candidates.at(i) << " : " << votes.at(i) << " VOTES\n";
    }

    result.close();
}

void bubbleSort(vector<string>& candidates, vector<int>& votes) {
    int sizeOfVector = candidates.size();
    bool swapped;

    for (int i = 0; i < sizeOfVector - 1; i++) {
        swapped = false;
        for (int j = 0; j < sizeOfVector - i - 1; j++) {
            if (votes[j] < votes[j + 1]) {
                swap(votes[j], votes[j + 1]);
                swap(candidates[j], candidates[j + 1]);

                swapped = true;
            }
        }

        // If no two elements were swapped, then break
        if (!swapped)
            break;
    }
}

void startVoting(map<string, string> presidents, map<string, string> vPresidents, map<string, string> senators) {
    vector<string> presName = {};
    vector<int> presVote = {};
    vector<string> vpresName = {};
    vector<int> vpresVote = {};
    vector<string> senatorName = {};
    vector<int> senatorVote = {};
    vector<int> voteContainer = {};

    string userInput, president, vicePresident, filename;
    int i, j;
    bool correctData, found, exit;

    exit = false;

    for (auto president : presidents) {
        presName.push_back(president.first);
        presVote.push_back(0);
    }

    for (auto president : vPresidents) {
        vpresName.push_back(president.first);
        vpresVote.push_back(0);
    }

    for (auto president : senators) {
        senatorName.push_back(president.first);
        senatorVote.push_back(0);
    }


    while (!exit) {
        clearScreen();
        cout << "=====================================\n";
        cout << "             PILI-PINAS              \n";
        cout << "         National Voting System      \n";
        cout << "=====================================\n"<<endl;

        cout << "PRESS ENTER TO START VOTING: ";
        getline(cin, userInput);

        if (userInput == "0") {
            exit = logIn();

            if (exit) {
                break;
            }
        }

        clearScreen();
        i = voteNow(presName, presidents, "PRESIDENT");
        presVote[i] += 1;

        clearScreen();
        i = voteNow(vpresName, vPresidents, "VICE PRESIDENT");
        vpresVote[i] += 1;

        if (senatorName.size() <= 0) {
            i = 0;

            cout << "\nERROR: There are no senator candidates\n";
        } else if (senatorName.size() >= 10) {
            i = 5;
        } else if (senatorName.size() >= 8) {
            i = 4;
        } else if (senatorName.size() >= 6) {
            i = 3;
        } else if (senatorName.size() >= 4) {
            i = 2;
        } else {
            i = 1;
        }

        voteContainer.clear(); // Makes sure the thing is clean before starting

        clearScreen();
        for (int j = 0; j < i; j++) {
            cout << "SENATOR\n\n";

            search(senators);

            cout << "Enter the number of the candidate to vote (Press '0' to exit): ";
            getline(cin, userInput);

            found = false;
            if (isDigit(userInput)) {
                for (int vote : voteContainer) {
                    if (stoi(userInput) == vote) {
                        found = true;

                        break;
                    }
                }

                if (!found) {
                    for (int element : voteContainer) {
                        cout << element << "\n";
                    }

                    clearScreen();
                    voteContainer.push_back(stoi(userInput));
                } else {
                    j--;

                    clearScreen();
                    cout << "\nERROR: Please select another candidate\n";
                }
            }
        }

        for (auto vote : voteContainer) {
            senatorVote[vote] += 1;
        }
    }

    // SORTS THE VOTES
    bubbleSort(presName, presVote);
    bubbleSort(vpresName, vpresVote);
    bubbleSort(senatorName, senatorVote);


    filename = "vote_result.txt";
    ofstream result(filename);
    result.close();

    produceResult(presName, presVote, filename, "PRESIDENT");
    produceResult(vpresName, vpresVote, filename, "VICE PRESIDENT");
    produceResult(senatorName, senatorVote, filename, "SENATORS");
}

void updateName(vector<string>& voters) {
    string userInput;
    int ctr, index;

    clearScreen();
    cout << "============================\n";
    cout << "    UPDATE VOTER'S NAME     \n";
    cout << "============================\n"<<endl;

    ctr = 1;
    for (string voter : voters) {
        cout << ctr << ".) " << voter << endl;
        ctr++;
    }

    do {
        do {
            cout << "Enter the number of the name you want to update: ";
            getline(cin, userInput);
        } while (!isDigit(userInput));

        index = stoi(userInput) - 1;
    } while (!confirmValue(voters.at(stoi(userInput) - 1)));

    do {
        cout << "Enter new name: ";
        getline(cin, userInput);

        userInput = toCapital(userInput);
    } while (!confirmValue(userInput));

    voters.at(index) = userInput;
}

int removeCandidate(map<string, string>& presidents, map<string, string>& vPres, map<string, string>& senators) {
    string userInput, choice;
    int ctr;

    do {
        clearScreen();
        cout << "======================\n";
        cout << "    REMOVE A NAME     \n";
        cout << "======================\n"<<endl;

        cout << "1.) Presidents\n2.) Vice Presidents\n3.) Senators\n4.) Exit\n\n";
        cout << "Enter the number of the type you want to remove (1/2/3): ";
        getline(cin, choice);
    } while (!isDigit(choice));

    clearScreen();
    ctr = 1;
    switch (stoi(choice)) {
        case 1:
            cout << "PRESIDENTS\n";
            for (auto president : presidents) {
                cout << ctr << ".) " << president.first << endl;
                ctr++;
            }

            break;
        case 2:
            cout << "\n\nVICE PRESIDENTS\n";
            for (auto vPres : vPres) {
                cout << ctr << ".) " << vPres.first << endl;
                ctr++;
            }

            break;

        case 3:
            cout << "\n\nSENATORS\n";
            for (auto senator : senators) {
                cout << ctr << ".) " << senator.first << endl;
                ctr++;
            }

            break;
        case 4:

            break;
        default:
            cout << "\nERROR: Invalid option\n";
    }

    if (stoi(choice) != 4) {
        cout << "Enter the name you want to remove: ";
        getline (cin, userInput);

        userInput = toCapital(userInput);
    }

    switch (stoi(choice)) {
        case 1:
            presidents.erase(userInput);

            break;
        case 2:
            vPres.erase(userInput);

            break;
        case 3:
            senators.erase(userInput);

            break;
    }

    if (stoi(choice) != 4) {
        return 1;
    }

    return 4;
}

// DATABASE
void database(int action, string name, string address, string sex, int age) {
    static vector <string> voters = {};

    string userInput, indices;
    int index;
    bool addedNew = false;

    switch (action) {
        case 0: // Sorts and Saves the list of voters into a file
            sort(voters.begin(), voters.end());

            saveFile(voters);

            break;
        case 1: // Loads/Adds voters name to the vector
            voters.push_back(name);

            addedNew = true;

            break;
        case 2: // Removes voters
            indices = search(voters);
            index = removeVoter(indices);

            if (index >= 0) {
                voters.erase(voters.begin() + index);

                database(0, "", "", "", 0); // Sends a command for itself to sort and save the updated voters
            }

            break;
        case 3: // Assigns voters to a precinct
            assignPrecinct(voters);

            break;
        case 4: // Updates voter's name
            updateName(voters);

            break;
        default:
            cout << "\nERROR: Invalid database action!\n";
    }

    if (addedNew) {
        ofstream file(name + ".txt");

        file << "NAME: " << name << "\nADDRESS: " << address << "\nSEX: " << sex << "\nAGE: " << age;
        file.close();

        addedNew = false;
    }
}

void database(int action, string name, string position, string partylist) {
    static map<string, string> presidents = {};
    static map<string, string> vPresidents = {};
    static map<string, string> senators = {};

    int mode;

    switch (action) {
        case 0: // Sorts and Saves the list of candidates into a file
            saveFile(presidents, "presidents");
            saveFile(vPresidents, "vpresidents");
            saveFile(senators, "senators");

            break;
        case 1: // Loads/Adds candidates name to the map
            if (position == "PRESIDENT") {
                presidents.insert({name, partylist});
            } else if (position == "VICE PRESIDENT") {
                vPresidents.insert({name, partylist});
            } else if (position == "SENATOR") {
                senators.insert({name, partylist});
            } else {
                cout << "\nERROR: A problem occured while adding a candidate\n";
            }

            break;
        case 2: // Removes candidates
            mode = removeCandidate(presidents, vPresidents, senators);
            if (mode != 4) {
                database(0, "", "", "");
            }

            break;
        case 3: // Start Voting
            startVoting(presidents, vPresidents, senators);

            break;
        default:
            cout << "\nERROR: Invalid database action!\n";
    }
}

void uploadName(string filename, string position) {
    string line, name, partyList;
    int i;
    bool switcher;

    ifstream file(filename);
    if (file.is_open()) {

        i = 0;
        switcher = true;
        while (getline(file, line)) {
            if (switcher) {
                name = line;

                switcher = false;
            } else {
                partyList = line;

                switcher = true;
            }
            i++;

            if (i == 2) {
                database(1, name, position, partyList);

                i = 0;
            }
        }

        file.close();
    }
}

void loadFile() {
    string name, line, partyList;
    bool switcher;

    ifstream list_of_voters("list_of_voters.save");
    if (list_of_voters.is_open()) {
        while (getline(list_of_voters, name)) {
            name = toCapital(name);

            database(1, name, "", "", 0);
        }

        list_of_voters.close();

        database(0, "", "", "", 0); // Sends a command for the database to save the list of voters. This will overwrite the old file
    }

    uploadName("list_of_presidents.save", "PRESIDENT");
    uploadName("list_of_vpresidents.save", "VICE PRESIDENT");
    uploadName("list_of_senators.save", "SENATOR");

    database(0, "", "", "");
}

void addToDatabase(int action) {
    string fullName, address, sex, position, data, userInput, partylist;
    int age;
    bool correctData = false;

    position = "";
    data = "";

    do {
        clearScreen();
        cout << "==================================================\n";
        cout << "    Please fill out the required information:     \n";
        cout << "==================================================\n"<<endl;

        fullName = getName();

        if (action == 1) { // For voters
            cout << "Enter address: ";
            getline(cin, address);

            age = getAge();

            if (age <= 0) {
                cout << "\nERROR: Minor detected!\n";

                break;
            }

            sex = getSex();
            data = "\nNAME: " + fullName + "\nADDRESS: " + address + "\nAGE: " + to_string(age) + "\nSEX: " + sex + "\n\n";
        } else if (action == 2) { // For candidates
            do {
                cout << "\nPOSITION:\n1.) PRESIDENT\n2.) VICE PRESIDENT\n3.) SENATOR\n\n";
                cout << "Enter position (1/2/3): ";
                getline(cin, position);

                if (position == "1") {
                    position = "PRESIDENT";
                } else if (position == "2") {
                    position = "VICE PRESIDENT";
                } else if (position == "3") {
                    position = "SENATOR";
                } else {
                    position = "";

                    cout << "\nERROR: Invalid position!\n";
                }
            } while (position == "");

            cout << "Enter PARTY-LIST name: ";
            getline(cin, partylist);

            if (position != "") {
                data = "\nNAME: " + fullName + "\nPOSITION: " + position + "\nPARTY-LIST: " + partylist + "\n\n";
            }
        }
        correctData = confirmValue(data);
    } while (!correctData);

    if (correctData) {
        if (action == 1) {
            database(1, fullName, address, sex, age); // Sends the name to the database
            database(0, "", "", "", 0); // Auto-saves the list of names to immediately create a load file incase of crash
        } else if (action == 2) {
            database(1, fullName, position, partylist); // Same as here
            database(0, "", "", "");
        }

    }
}

void toEdit(int mode) {
    int action;
    string userInput;

    do {
        cout << "SELECT WHAT TO ADD:\n";
        cout << "===========================\n";
        cout << "    SELECT WHAT TO ADD     \n";
        cout << "================= =========\n"<<endl;
        cout << "1.) Voter \n2.) Candidate\n\n";

        cout << "Enter the number from the options (1/2): ";
        getline(cin, userInput);
    } while (!isDigit(userInput));

    switch (stoi(userInput)) {
        case 1:
            action = 1;

            break;
        case 2:
            action = 2;

            break;
        default:
            cout << "\nERROR: Invalid option!\n";
    }

    if (mode == 1) {
        addToDatabase(action);
    } else if (mode == 2) {
        if (action == 1) {
            database(2, "", "", "", 0);
        } else {
            database(2, "", "", "");
        }
    } else {
        cout << "\nERROR: There was problem in selecting a mode\n";
    }
    
}



bool mainMenu() {
    string userInput;

    cout << "===============================\n";
    cout << "           MAIN MENU!          \n";
    cout << "===============================\n"<<endl;
    cout << "1.) Add a Voter/Candidate \n2.) Remove a Voter/Candidate \n3.) Update Voter's Name \n4.) Display Precincts \n5.) Start Voting \n6.) Exit\n\n";

    cout << "Select from the Menu (1/2/3/4/5/6): ";
    getline(cin, userInput);

    clearScreen();
    if (isDigit(userInput)) {
        switch (stoi(userInput)) {
            case 1:
                toEdit(1);

                break;
            case 2:
                toEdit(2);

                break;
            case 3:
                database(4, "", "", "", 0);

                break;
            case 4:
                database(3, "", "", "", 0);

                break;
            case 5:
                database(3, "", "", "");

                break;
            case 6:
                return false;

                break;
            default:
                cout << "\nERROR: Invalid selection from the main menu!\n";
        }
    }

    return true;
}

int main() {
    bool loggedIn;

    // SETS UP THE SYSTEM...
    clearScreen();
    loadFile();
    loggedIn = logIn();

    while (loggedIn) {
        clearScreen();

        loggedIn = mainMenu();
    }

    return EXIT_SUCCESS;
}