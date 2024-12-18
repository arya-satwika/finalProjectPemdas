#include <iostream>
#include <fstream>


using namespace std;

struct login
{
    string username;
    string website;
    string password;
};
struct sudo
{
    string masterUser;
    string masterPass;
};



void newVault(string &vaultName, sudo* master){
    string username, password;
    //harsya

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

void outputSudo(){
    //cout << "Master Username: " << master.masterUser << endl;
    //cout << "Master Password: " << master.masterPass << endl;
}

int main()
{
    sudo master;
    cout << "Welcome to PassManager!" << endl;
    cout << "Enter Master Username: ";
    cin >> master.masterUser;
    cout << "Enter Master Password: ";
    cin >> master.masterPass;
    
    
    string vaultName;
    return 0;
}
