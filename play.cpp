#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(int argc, char const *argv[])
{
    string vaultName = "aku.txt";
    string account = vaultName;
    account.erase(account.size() - 4, account.size());
    cout << account;
    return 0;
}

