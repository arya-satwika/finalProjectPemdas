#include <iostream>
#include <fstream>

using namespace std;

struct sudo{
    string User;
    string Pass;
};

void mainMenu();
void loginMenu(string vaultName);
void inputPassword(string &vaultName);
void findLogin(string &vaultName);
void loginMenu(string vaultName);

void newVault(sudo &master, string &vaultName){

    
    cout << "Enter username: ";
    cin >> master.User;
    cout << "Enter password: ";
    cin >> master.Pass;
    ofstream file("users.txt", ios::app);
    file << "Username: " << master.User << endl << "Password: " << master.Pass << endl;
    vaultName = master.User + ".txt";
    ofstream vault(vaultName);
    vault.close();
    inputPassword(vaultName);

}
void inputPassword(string &vaultName){
    char lanjut;
    do
    {
        string username, password, website;
        cout << "Enter website: ";
        cin >> website;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        ofstream vault(vaultName, ios::app);
        vault << website << endl << username << endl << password << endl;
        vault.close();
        cout << "Do you want to add another password? (y/n): ";
        cin >> lanjut;
    } while (tolower(lanjut) == 'y');
    if (tolower(lanjut) == 'n')
    {
        mainMenu();
    }
    
}
void findLogin(string &vaultName){
    string website, username, password, findWebsite, masterUser;
    cout << "Enter website: ";
    cin >> findWebsite;
    ofstream temp("temp.txt");
    ifstream vault(vaultName);
    while(getline(vault, masterUser)){
        if (masterUser.find(findWebsite) != string::npos)
        {
         for (int i = 0; i < 2; i++)
            {
            getline(vault, masterUser);  
            temp << masterUser << endl;
            cout << masterUser << endl;
            }
        }   
    }
}
void outputPassword(string &vaultName){
    string masterUser;
    ifstream vault(vaultName);
    while(getline(vault, masterUser)){
        cout << masterUser << endl;
    }
}
string loginVault()
{
    string username, password, masterUser, masterPass;
    bool repeat;
    bool valUser, valPass;
    // valUser = false;
    do
    {
        cout << "masukkan username: ";
        cin >> username;
        cout << "masukkkan password: ";
        cin >> password;
        ifstream users("users.txt");
        while (getline(users, masterUser))
        {
            if (masterUser.find(username) != string::npos)
            {
                // valUser = true;
                cout << "user " << masterUser << endl;
                getline(users, masterPass);
                cout << "password " << masterPass << endl;
                if (masterPass.find(password) != string::npos)
                {
                    valPass = true;
                    return username + ".txt";
                }
                else
                {
                    valPass = false;
                    cout << "\n\nPASSWORD SALAH\n" ;
                    repeat = true;
                    break;
                }
            }
            else // else if (masterUser.find(username) == string::npos)
            {
                cout << "Username tidak ditemukan" << endl;
                repeat = true;
            }
        }
    } while (repeat == true);
    return " "; // return empty string
}
void mainMenu(){
    int choice;
    sudo master;
    string vaultName;
    cout << "1. New Vault" << endl;
    cout << "2. Login" << endl;
    cout << "3. Quit" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        newVault(master, vaultName);
        break;
    case 2:
        loginMenu(loginVault());
        break;
    case 3:
        cout << "Goodbye!";
        break;
    default:
        mainMenu();
        cout << "Invalid choice";
        break;
    }
}
void loginMenu(string vaultName){
    int choice;
    cout << "1. Find Password" << endl;
    cout << "2. New Password" << endl;
    cout << "3. Quit" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        findLogin(vaultName);
        break;
    case 2:
        inputPassword(vaultName);
        break;
    case 3:
        cout << "Goodbye!";
        break;
    default:
        cout << "Invalid choice";
        loginMenu(vaultName);
        break;
    }
}
int main()
{
    mainMenu();
    return 0;
}
