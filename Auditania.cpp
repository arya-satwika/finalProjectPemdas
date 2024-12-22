void addPassword(string &vaultName) {
    ofstream vault(vaultName, ios::app);
    if (!vault) {
        cerr << "Error: Cannot open vault file." << endl;
        return;
    }

    string website, username, password;
    cout << "Enter website: ";
    cin >> website;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    vault << "Website: " << website << endl;
    vault << "Username: " << username << endl;
    vault << "Password: " << password << endl;
    cout << "Password added successfully!" << endl;

    vault.close();
}
void updatePassword(string &vaultName) {
    ifstream vault(vaultName);
    ofstream temp("temp.txt");

    if (!vault || !temp) {
        cerr << "Error: Cannot open file." << endl;
        return;
    }

    string findWebsite, line, username, password, newPassword;
    cout << "Enter website to update password: ";
    cin >> findWebsite;

    bool found = false;
    while (getline(vault, line)) {
        if (line == "Website: " + findWebsite) {
            found = true;
            temp << line << endl;
            getline(vault, username);
            getline(vault, password);
            cout << "Enter new password: ";
            cin >> newPassword;
            temp << username << endl;
            temp << "Password: " << newPassword << endl;
        } else {
            temp << line << endl;
        }
    }

    vault.close();
    temp.close();

    if (found) {
        remove(vaultName.c_str());
        rename("temp.txt", vaultName.c_str());
        cout << "Password updated successfully!" << endl;
    } else {
        remove("temp.txt");
        cout << "No entries found for " << findWebsite << endl;
    }
}