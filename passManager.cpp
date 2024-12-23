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


void deleteVault(const string &vaultFile, const string &masterUsername, const string &masterPassword) {
    cout << "Untuk menghapus vault, Anda harus memasukkan Master Username dan Password.\n";

    // Meminta Master Username dan Password
    string inputUsername, inputPassword;
    cout << "Masukkan Master Username: ";
    cin >> inputUsername;
    cout << "Masukkan Master Password: ";
    cin >> inputPassword;

    // Verifikasi Master Username dan Password
    if (inputUsername == masterUsername && inputPassword == masterPassword) {
        cout << "Apakah Anda yakin ingin menghapus file vault? (y/n): ";
        char confirm;
        cin >> confirm;

        if (tolower(confirm) == 'y') {
            if (remove(vaultFile.c_str()) == 0) {
                cout << "File vault berhasil dihapus.\n";
            } else {
                cerr << "Error: Gagal menghapus file vault. File mungkin tidak ada.\n";
            }
        } else {
            cout << "Penghapusan file vault dibatalkan.\n";
        }
    } else {
        cout << "Verifikasi gagal! Master Username atau Password salah.\n";
    }
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
    ofstream vault(master.masterUser+".txt");
    vault.close();
    loginMenu(master.masterUser+".txt");
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
void loginMenu(string vaultName){
    int pilihan;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Tambah Password\n";
        cout << "2. Cari Password\n";
        cout << "3. Hapus Password\n";
        cout << "4. Update Password\n";
        cout << "5. Hapus Vault\n";
        cout << "6. Keluar\n";
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
            //hapusVault(vaultName);
            break;
        }
        else if (pilihan == 6)
        {
            mainMenu();
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
    
    
    string vaultName;
    return 0;
}
