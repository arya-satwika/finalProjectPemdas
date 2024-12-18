#include <iostream>
#include <fstream>


using namespace std;

struct login
{
    string username;
    string website;
    string password;
};


void newVault(string &vaultName){
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



int main()
{
    string vaultName;
    return 0;
}
