#include <iostream>
#include <fstream>


using namespace std;

struct sudo
{
    string masterUser;
    string masterPass;
};



void newVault(string &vaultName, sudo* master){

    string username, password;
    cout << "Enter Master Username: ";
    cin >> master.masterUser;

    cout << "Enter Master Password: ";
    cin >> master.masterPass;
}
    //arya
    ifstream vault(username+".txt");
    vault.close();
}

void findPassword(string &vaultName){
    string website, username, password, findWebsite, line;
    cout << "Enter website: ";
    cin >> findWebsite;
    ofstream temp("temp.txt");
    ifstream vault(vaultName);
    while(getline(vault, line)){
        if (line.find(findWebsite) != string::npos)
        {
         for (int i = 0; i < 2; i+=2)
            {
            getline(vault, line);  
            temp << line << endl;
            }
        }   
    }
}

void newPassword(){}
void mainMenu(){
    int choice;
    sudo master;
    string vaultName;
    cout << "1. New Vault" << endl;
    cout << "2. Login" << endl;
    cout << "3. Quit" << endl;
    cout << "Masukkan Pilihan: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        newVault(VaultName, master);
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
int main()
{
    mainMenu();
    
    
    string vaultName;
    return 0;
}
