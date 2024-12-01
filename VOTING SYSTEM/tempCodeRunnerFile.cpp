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