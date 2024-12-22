#include <iostream>
#include <fstream>

using namespace std;

struct sudo{
    string User;
    string Pass;
};
struct storedLogin
{
    string username;
    string password;
};


void mainMenu();
void loginMenu(string vaultName);
void inputPassword(string &vaultName);
void findLogin(string &vaultName);
void loginMenu(string vaultName);
int loginInstance(string &vaultname , string findWebsite);
bool existingUser(sudo &master);

bool existingUser(sudo &master){
    ifstream file("users.txt");
    string line;
    while (getline(file,line))
    {
        if (line.find("Username: "+master.User) != string::npos)
        {
            file.close();
            return true;
        }
        
    }
    file.close();
    return false;
    
}

void newVault(sudo &master, string &vaultName){

    
    cout << "Enter username: ";
    cin >> master.User;
    cout << "Enter password: ";
    cin >> master.Pass;
    if (existingUser(master))
    {
        cout << "User sudah terdaftar" << endl;
        newVault(master, vaultName);
    }
    else
    {
        ofstream file("users.txt", ios::app);
        file << "Username: " << master.User << endl
             << "Password: " << master.Pass << endl;
        vaultName = master.User + ".txt";
        ofstream vault(vaultName);
        vault.close();
        inputPassword(vaultName);
    }
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
        vault << "Website: " << website << endl << "Username: " << username << endl << "Password: " << password << endl;
        vault.close();
        cout << "Apakah mau nambah password lagi? (y/n): ";
        cin >> lanjut;
    } while (tolower(lanjut) == 'y');
    if (tolower(lanjut) == 'n')
    {
        mainMenu();
    }
    
}
int loginInstance(string &vaultname , string findWebsite){ 
    string temp;
    int count=0;
    ifstream vault(vaultname);
    while (getline(vault, temp))
    {
        if (temp.find("Website: "+findWebsite) != string::npos)
        {
            count++;
        }
        
    }
    return count;
}
int outputLogin(string* storedUser, string* storedPass, int size){
    int choice;
    cout <<"pilih akun yang mana?" << endl;
    for (int j = 0; j < size; j++)
    {
    cout << j+1 << ". Username: " << storedUser[j] << endl;
    }
    cout << "masukkan angka: ";
    cin >> choice;
    return choice;
}
void findLogin(string &vaultName){
    string website, findWebsite ;
    string temp;
    int index=0;
    int index2=0;
    cout << "Enter website: ";
    cin >> findWebsite;
    for (char ch : findWebsite)
    {
        findWebsite[index2] = tolower(ch);
        index2++;
    }
    int size = loginInstance(vaultName, findWebsite);
    string storedUser[size];
    string storedPass[size];
    ifstream vault(vaultName);
    while (getline(vault, temp)) {
        if (temp == "Website: "+findWebsite) {
            for (int i = 0; i < 2; i++)
            {
            getline(vault, temp);
                if (i==0)
                {
                    temp.erase(0,10);
                    storedUser[index]=temp;
                } 
                else if (i==1)
                {
                    temp.erase(0,10);
                    storedPass[index]=temp;
                    index++;
                } 
            }
        }
    }
    vault.close();
    int choice = outputLogin(storedUser, storedPass, size);
    cout << "Username: " << storedUser[choice-1] << endl;
    cout << "Password: " << storedPass[choice-1] << endl;
}
void masukkinPass(string findWebsite, string* storedUser, string &vaultName, int choice){
    ifstream vaultRead(vaultName);
    string temp;
    string newPassword;
    while (getline(vaultRead, temp)) {
        if (temp == "Website: "+findWebsite) {
            getline(vaultRead, temp);
            if (temp == "Username: "+storedUser[choice-1])
            {
                cout << "Enter new password: ";
                cin >> newPassword;
                getline(vaultRead, temp);
                ofstream vaultWrite(vaultName);
                vaultWrite << "Password: " << newPassword << endl;
                vaultWrite.close();
            }
          
          
        }
    }
    vaultRead.close();
}
void updatePass(string &vaultName){
    string website, findWebsite ;
    string temp;
    int index=0;
    int index2=0;
    cout << "Enter website: ";
    cin >> findWebsite;
    for (char ch : findWebsite)
    {
        findWebsite[index2] = tolower(ch);
        index2++;
    }
    int size = loginInstance(vaultName, findWebsite);
    string storedUser[size];
    string storedPass[size];
    ifstream vaultRead(vaultName);
    while (getline(vaultRead, temp)) {
        if (temp == "Website: "+findWebsite) {
            for (int i = 0; i < 2; i++)
            {
            getline(vaultRead, temp);
                if (i==0)
                {
                    temp.erase(0,10);
                    storedUser[index]=temp;
                } 
                else if (i==1)
                {
                    temp.erase(0,10);
                    storedPass[index]=temp;
                    index++;
                } 
            }
        }
    }
    int choice = outputLogin(storedUser, storedPass, size);
    masukkinPass(findWebsite, storedUser, vaultName, choice);
}
string loginVault()
{
    string username, password, masterUser, masterPass;
    bool repeat;
    bool valUser, valPass;
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
                getline(users, masterPass);
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
            else 
            {
                cout << "Username tidak ditemukan" << endl;
                repeat = true;
            }
        }
    } while (repeat == true);
    return " "; 
}
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
    cout << "4. Update Password" << endl;
    cout << "Masukkan Pilihan: ";
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
    case 4:
        updatePass(vaultName);
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
