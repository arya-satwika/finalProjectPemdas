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
void loginMenu(const string vaultName);
void mainMenu();
void findLogin(const string &vaultName);
void newVault(string &vaultName, sudo &master);
int loginInstance(const string &vaultname, string findWebsite);
int outputLogin(const string* storedUser, string* storedPass, int size);
void hapusPassword(const string &vaultName);
void hapusVault(const string &vaultName);

bool existingUser(sudo &master){
    ifstream file("users.txt");
    string line;
    while (getline(file,line))
    {
        if (line.find("Username: "+master.masterUser) != string::npos)
        {
            file.close();
            return true;
        }
        
    }
    file.close();
    return false;
    
}

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
    cout << "2. Kembali ke menu Login" << endl;
    cout << "3. Log Out" << endl;
    cout << "Masukkan Pilihan: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        addPassword(vaultName);
        break;
    case 2:
        loginMenu(vaultName);
        break;
    case 3:
        mainMenu();
        break;
    }
}

void newVault(string &vaultName, sudo &master){
    bool repeat;
    do
    {
        string username, password;
        cout << "Enter Master Username: ";
        cin >> master.masterUser;

        cout << "Enter Master Password: ";
        cin >> master.masterPass;
        if (existingUser(master))
        {
            cout << "User sudah terdaftar" << endl;
            repeat = true;
        }
        else{
        ofstream file("users.txt", ios::app);
        file << "Username: " << master.masterUser << endl
             << "Password: " << master.masterPass << endl;
        file.close();
        }

    } while (repeat == true);
    
    ofstream vault(master.masterUser+".txt");
    vault.close();
    loginMenu(master.masterUser+".txt");
}

int loginInstance(const string &vaultname , string findWebsite){ 
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
int outputLogin(const string* storedUser, string* storedPass, int size){
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
    cout << "\n\n\n";
    cout<< "1. Cari Password lagi?" << endl;
    cout << "2. Kembali ke menu Login" << endl;
    cout << "3. Log Out" << endl;
    cout << "Masukkan Pilihan: ";
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
    default:
        cout << "Invalid choice" << endl;
        break;
    }
}

void hapusVault(const string &vaultName){
    string line;
    string accPass, inputPass;
    bool validUser = false;
    string tempUser = vaultName;
    string account = tempUser.erase(tempUser.size() - 4, tempUser.size());
    ifstream users("users.txt");
    ifstream temp("temp.txt");
    ofstream tempWrite("temp.txt");
    while (getline(users, line))
    {
        if (line.find("Username: "+account) != string::npos)
        {
            getline(users, accPass);
            accPass.erase(0, 10);
            validUser = true;
        }
        else if (line.find("Username: "+account) == string::npos)
        {
            tempWrite << line << endl;
        }
    }
    tempWrite.close();
    temp.close();
    users.close();
    if (validUser)
    {
        cout << "Masukkan master Password untuk Konfirmasi: ";
        cin >> inputPass;
        cout << accPass;
        if (inputPass == accPass)
        {
            remove(vaultName.c_str());
            remove("users.txt");
            rename("temp.txt", "users.txt");
            cout << "Vault berhasil dihapus!" << endl;
        }
        else 
        {
            cout << "Password Salah!" << endl;
        }
    }
    else
    {
            remove("temp.txt");
            cout << "User tidak ditemukan" << endl;
    }
}

void hapusPassword(const string &vaultName) {
    string website, line, username;
    cout << "Masukkan nama website yang ingin dihapus: ";
    cin >> website;
    cout << "Masukkan Username: ";
    cin >> username;
    ifstream vault(vaultName);
    ofstream temp("temp.txt");
    bool ditemukan = false;

    while (getline(vault, line)) {
        if (line == "Website: "+website) {
            getline(vault, line); // Username
            if (line == "Username: "+username)
            {
                getline(vault, line); // Password
                ditemukan = true;
            }
        } else {
            temp << line << endl;
        }
    }
    vault.close();
    temp.close();
    if (ditemukan) {
        remove(vaultName.c_str());  
        rename("temp.txt", vaultName.c_str());  
        cout << "Password berhasil dihapus!" << endl;
    } else {
        remove("temp.txt");  
        cout << "User tidak ditemukan!" << endl;
    }
}

void loginMenu(string vaultName) {
    int pilihan;
        cout << "\nMenu:\n";
        cout << "1. Tambah Password\n";
        cout << "2. Cari Password\n";
        cout << "3. Hapus Vault\n";
        cout << "4. Hapus Password\n";
        cout << "5. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                addPassword(vaultName);
                break;
            case 2:
                findLogin(vaultName);
                break;
            case 3:
                hapusVault(vaultName);
                break;
            case 4:
                hapusPassword(vaultName);
                break;
            case 5:
                mainMenu();
                return;
            default:
                cout << "Pilihan tidak valid" << endl;
                break;
        }
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
    bool valUser;
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
                    repeat = false;
                    return username + ".txt";
                }
                else
                {
                    cout << "\n\nPASSWORD SALAH\n" ;
                    repeat = true;
                    break;
                }
            }
            else{
                valUser = false;
            }
        }
        if (valUser == false)
        {
            cout << "Username tidak ditemukan" << endl;
            repeat = true;
        }
        
    } while (repeat == true);
    return " "; 
}

int main()
{
    mainMenu();
    return 0;
}
