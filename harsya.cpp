void addPassword(const string &vaultFile);
void findPassword(const string &vaultFile);
void deleteVault(const string &vaultFile);
void updatePassword(const string &vaultFile);

// Function to display the menu and handle user choices
void menu(const string &vaultFile) {
    int choice;

    do {
        cout << "\nVault Menu\n";
        cout << "1. Add Password\n";
        cout << "2. Find Password\n";
        cout << "3. Delete Vault\n";
        cout << "4. Update Password\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addPassword(vaultFile);
                break;
            case 2:
                findPassword(vaultFile);
                break;
            case 3:
                deleteVault(vaultFile);
                break;
            case 4:
                updatePassword(vaultFile);
                break;
            case 5:
                cout << "Exiting the vault. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}
struct MasterCredentials {
    string masterUsername;
    string masterPassword;
};

// Function to create master credentials
void createMasterCredentials(MasterCredentials &master) {
    cout << "Enter Master Username: ";
    cin >> master.masterUsername;

    cout << "Enter Master Password: ";
    cin >> master.masterPassword;
ini kode sintax flowchart 1 dari bagian harsya