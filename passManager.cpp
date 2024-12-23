#include <iostream>
#include <fstream>


using namespace std;

struct sudo
{
    string masterUser;
    string masterPass;
};
string loginVault();
void addPassword(string &vaultName);
void loginMenu(string vaultName);
void mainMenu();
void findLogin(string &vaultName);



void addPassword(string &vaultName) {
    int choice;
    ofstream vault(vaultName, ios::app);

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
    cout << "1. Nambah Password?" << endl;
    cout << "2. Log Out" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
        addPassword(vaultName);
        break;
    case 2:
        mainMenu();
        break;
    }
}

void newVault(string &vaultName, sudo &master){

    string username, password;
    cout << "Enter Master Username: ";
    cin >> master.masterUser;

    cout << "Enter Master Password: ";
    cin >> master.masterPass;
    ofstream file("users.txt", ios::app);
    file << "Username: " << master.masterUser << endl
        << "Password: " << master.masterPass << endl;
    file.close();
    ifstream vault(master.masterUser+".txt");
    vault.close();
}
void updatePassword(string &vaultName) {
    ifstream vault(vaultName);
    ofstream temp("temp.txt");

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
        cout << "No entries found for " << findWebsite << endl;
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
    cout<< "1. Cari Password lagi?" << endl;
    cout << "2. Kembali ke menu Login" << endl;
    cout << "3. Log Out" << endl;
    int choice2;
    cin >> choice2;
    switch (choice2)
    {
    case 1:
        findLogin(vaultName);
        break;
    case 2:
        loginMenu(vaultName);
        break;
    case 3:
        mainMenu();
        break;
    }
}
void loginMenu(string vaultName){
    int pilihan;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Tambah Password\n";
        cout << "2. Cari Password\n";
        cout << "3. Hapus Password\n";
        cout << "4. Update Password\n";
        cout << "5. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;

        if (pilihan == 1) {
            addPassword(vaultName);
        } else if (pilihan == 2) {
            findLogin(vaultName);
        } else if (pilihan == 3) {
            //hapusPassword(vaultName);
        } else if (pilihan == 4) {
            updatePassword(vaultName);
            break;
        } else if (pilihan == 5) {
            mainMenu();
            break;
        }
        else {
            cout << "Pilihan tidak valid" << endl;
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
        newVault(vaultName, master);
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

int main()
{
    mainMenu();
    
    
    string vaultName;
    return 0;
}
