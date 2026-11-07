#include<iostream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<string>

using namespace std;

void login();
void menu();
void viewPackages();
void makeSale();
void addPackage();
void deletePackage();
void savePackages();
void loadPackages();
void viewCompanyDetails();
void logout();
void viewHistory();
void saveHistory();
void loadHistory();

int choice;
string username, pwd;
bool status = false;

string packages[50];
int pamount[50];
int packageCount = 3;

struct Sale {
    string packageName;
    int quantity;
    int price;
    int subtotal;
};

vector<Sale> salesHistory;

int main() {
	loadPackages(); 
    loadHistory();
    
    login(); 
    if (status == true)
        menu();
    else {
        cout << "\nIncorrect Username or Password...\n";
        login();
    }
    return 0;
}

void login() {
    cout << "===== LOGIN =====\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> pwd;

    if (username == "nimnada" && pwd == "nimnada123") {
        status = true;
        cout << "\nLogin Successful!\n\n";
    } else {
        status = false;
    }
}

void menu() {
    do {
        cout << "\n========== LAUNDRY MANAGEMENT SYSTEM ==========\n";
        cout << "1. View Available Packages\n";
        cout << "2. Make Sale\n";
        cout << "3. Add New Package\n";
        cout << "4. Delete a Package\n";
        cout << "5. View Sales History\n";
        cout << "6. View Company Details\n";
        cout << "7. Logout\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewPackages();
            break;
        case 2:
            makeSale();
            break;
        case 3:
            addPackage();
            break;
        case 4:
            deletePackage();
            break;
        case 5:
            viewHistory(); 
            break;
        case 6:
        	viewCompanyDetails();  
        	break;
        case 7:
        	logout(); 
        	break;
        case 8:
            cout << "Exiting the program. Thank you!\n";
            savePackages();
            saveHistory();
            break;
        default:
            cout << "Invalid choice. Try again!\n";
        }
    } while (choice != 8);
}

void viewPackages() {
    cout << "\nAvailable Packages:\n";
    cout << "-----------------------------------------\n";
    cout << left << setw(5) << "No" << setw(25) << "Service" << setw(10) << "Price (Rs)" << endl;
    cout << "-----------------------------------------\n";

    for (int i = 0; i < packageCount; i++) {
        cout << setw(5) << i + 1 << setw(25) << packages[i] << setw(10) << pamount[i] << endl;
    }
    cout << "-----------------------------------------\n";
}

void makeSale() {
    int pnumber[10], quantity[10], subtotal[10];
    int total = 0, count = 0;
    char another;

    viewPackages(); 
      
    do {
        cout << "\nEnter Package No: ";
        cin >> pnumber[count];
        if (pnumber[count] < 1 || pnumber[count] > packageCount) {
            cout << "Invalid package number!\n";
            continue;
        }

        cout << "Enter Quantity: ";
        cin >> quantity[count];

        subtotal[count] = pamount[pnumber[count] - 1] * quantity[count];
        total += subtotal[count];
        count++;

        cout << "Do you want to add another sale? (y/n): ";
        cin >> another;
    } while (another == 'y' || another == 'Y');
     
    cout << "\n=============== BILL ===============\n";
    cout << left << setw(25) << "Service" << setw(10) << "Price" 
         << setw(10) << "Qty" << setw(10) << "Total\n";
    cout << "-----------------------------------------\n";
    for (int i = 0; i < count; i++) {
        cout << setw(25) << packages[pnumber[i] - 1]
             << setw(10) << pamount[pnumber[i] - 1]
             << setw(10) << quantity[i]
             << setw(10) << subtotal[i] << endl;
    }
    cout << "-----------------------------------------\n";
    cout << "      Total: Rs. " << total << "\n";
    cout << "=========================================\n";

    for (int i = 0; i < count; i++) {
        Sale newSale;
        newSale.packageName = packages[pnumber[i] - 1];
        newSale.quantity = quantity[i];
        newSale.price = pamount[pnumber[i] - 1];
        newSale.subtotal = subtotal[i];
        salesHistory.push_back(newSale);
    }
}

void addPackage() {
    cin.ignore();
    cout << "Enter new package name: ";
    getline(cin, packages[packageCount]);
    cout << "Enter package price (Rs): ";
    cin >> pamount[packageCount];
    packageCount++;

    cout << "Package added successfully!\n";
    savePackages(); 
}

void deletePackage() {
    viewPackages();
    int delNo;
    cout << "Enter package number to delete: ";
    cin >> delNo;

    if (delNo < 1 || delNo > packageCount) {
        cout << "Invalid package number!\n"; 
        return;
    }

    for (int i = delNo - 1; i < packageCount - 1; i++) {
        packages[i] = packages[i + 1];
        pamount[i] = pamount[i + 1];
    }
    packageCount--;
    cout << "Package deleted successfully!\n";
    savePackages();
}

void viewHistory() {
    if (salesHistory.empty()) {
        cout << "\nNo sales history available.\n";
        return;
    }

    cout << "\n========= Sales History =========\n";
    cout << left << setw(25) << "Service" << setw(10) << "Price" 
         << setw(10) << "Qty" << setw(10) << "Total\n";
    cout << "-----------------------------------------\n";

    for (int i = 0; i < salesHistory.size(); i++) {
        cout << setw(25) << salesHistory[i].packageName
             << setw(10) << salesHistory[i].price
             << setw(10) << salesHistory[i].quantity
             << setw(10) << salesHistory[i].subtotal << endl;
    }

    cout << "=========================================\n";
}

void savePackages() {
    ofstream file("packages.txt");
    if (!file) {
        cout << "Error saving packages!\n";
        return;
    }
    file << packageCount << endl;
    for (int i = 0; i < packageCount; i++) {
        file << packages[i] << "," << pamount[i] << endl;
    }
    file.close();
}

void loadPackages() {
    ifstream file("packages.txt");
    if (!file) {
        packages[0] = "Wash and Fold";
        packages[1] = "Dry Cleaning";
        packages[2] = "Ironing";
        pamount[0] = 50;
        pamount[1] = 500;
        pamount[2] = 30;
        return;
    }

    file >> packageCount;
    file.ignore();
    for (int i = 0; i < packageCount; i++) {
        getline(file, packages[i], ',');
        file >> pamount[i];
        file.ignore();
    }
    file.close();
}

void saveHistory() {
    ofstream file("sales_history.txt", ios::app);
    if (!file) {
        cout << "Error saving sales history!\n";
        return;
    }

    for (int i = 0; i < salesHistory.size(); i++) {
        file << salesHistory[i].packageName << "," 
             << salesHistory[i].quantity << "," 
             << salesHistory[i].price << "," 
             << salesHistory[i].subtotal << endl;
    }
    file.close();
}

void viewCompanyDetails() {
    cout << "\n========== COMPANY DETAILS ==========\n";
    cout << "Company Name : Eco-Clean Laundry Services\n";
    cout << "Address       : NO1, mirissa , Matara\n";
    cout << "Contact       : +94764634069\n";
    cout << "Email         : ecoclean@gmail.com\n";
    cout << "--------------------------------------\n";
    
    menu();
}

void logout() {
	cout<< "\n=============  Log Out success  ==============\n";
	main();
}

void loadHistory() {
    ifstream file("sales_history.txt");
    if (!file) {
        return;
    }

    string packageName;
    int quantity, price, subtotal;
    while (getline(file, packageName, ',')) {
        file >> quantity >> price >> subtotal;
        file.ignore();

        Sale sale;
        sale.packageName = packageName;
        sale.quantity = quantity;
        sale.price = price;
        sale.subtotal = subtotal;
        salesHistory.push_back(sale);
    }
    file.close();
}

