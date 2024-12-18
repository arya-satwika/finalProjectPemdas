
#include <iostream>
#include <fstream>


using namespace std;

struct login
{
    string username;
    string website;
    string password;
};

struct masterCred{
    string masterUser;
    string masterPass;
};
void newVault(string &vaultName){

    string username, password;
    cout << "Enter username: ";
    masterCred user1;
    cin >> user1.masterUser;
    cout << "Enter password: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;
    ofstream vault(username + ".txt");
    vault.close();
    vaultName = username + ".txt"; 

}
void inputPassword(string &vaultName){
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

string loginVault(){
    string username, password, line;
    cout << "masukkan username: ";
    cin >> username;
    cout << "masukkkan password: ";
    cin >> password;
    bool valUser;
    ifstream users("users.txt");
    while(getline(users, line)){
        if (line.find(username) != string::npos)
        {
         for (int i = 0; i < 2; i++)
         {
            getline(users, line);  
            if (i == 0)
            {
                if (line == username)
                {
                    valUser = 1;
                }
                else{
                valUser=0;

                }
            }
            else if (i == 1)
            {
                if (line == password)
                {
                    bool valUser = 1;
                }
                else{
                valUser=0;}
            }
            
            
        }
            if (!valUser)
            {
                cout << "username dan password tidak sesuai";
                return "tidak ada user";
            }
        return username + ".txt";
        }
    }
}

int main()
{
    string vaultName;
    return 0;
}
