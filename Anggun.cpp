void tambahPassword(const string &vaultName) {
    string website, username, password;
    cout << "Masukkan nama website: ";
    cin >> website;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    ofstream vault(vaultName);
    if (vault.is_open()) {
        vault << website << endl;
        vault << username << endl;
        vault << password << endl;
        cout << "Password berhasil ditambahkan!" << endl;
    } else {
        cout << "Gagal membuka file vault!" << endl;
    }
}

void cariPassword(const string &vaultName) {
    string website, line;
    cout << "Masukkan nama website yang ingin dicari: ";
    cin >> website;

    ifstream vault(vaultName);
    bool ditemukan = false;
    
    while (getline(vault, line)) {
        if (line == website) {
            cout << "Website ditemukan!" << endl;
            getline(vault, line); // Baca username
            cout << "Username: " << line << endl;
            getline(vault, line); // Baca password
            cout << "Password: " << line << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Website tidak ditemukan!" << endl;
    }
}

void hapusPassword(const string &vaultName) {
    string website, line;
    cout << "Masukkan nama website yang ingin dihapus: ";
    cin >> website;

    ifstream vault(vaultName);
    ofstream temp("temp.txt");
    bool ditemukan = false;

    while (getline(vault, line)) {
        if (line == website) {
            getline(vault, line); // Username
            getline(vault, line); // Password
            ditemukan = true;
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
        cout << "Website tidak ditemukan!" << endl;
    }
}

int main() {
    string vaultName = "vault.txt";
    int pilihan;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Tambah Password\n";
        cout << "2. Cari Password\n";
        cout << "3. Hapus Password\n";
        cout << "4. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;

        if (pilihan == 1) {
            tambahPassword(vaultName);
        } else if (pilihan == 2) {
            cariPassword(vaultName);
        } else if (pilihan == 3) {
            hapusPassword(vaultName);
        } else if (pilihan == 4) {
            break;
        } else {
            cout << "Pilihan tidak valid, coba lagi.\n";
        }
    }
