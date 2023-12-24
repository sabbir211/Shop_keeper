#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

bool isLoggedIn = false;
int loginAttempt = 0;
int userId;
int userRole;
void buyOrShow();
void addOrShow();
void displayProduct();
void findProduct(string targetId);
void purchaseHistory(int productId);
void addProduct();
void afterLogin();
int homeMenu();
void registration();
void login();
void faildLogin();
void addProduct();
int getId(string fileName);
void fetchHistory();
bool userOnDb(int id, string email, string password, string role);
int main()
{

  cout << "Welcome to Shop Keeper !\n";
  if (homeMenu() == 0)
  {
    return 0;
  }

  return 0;
}

int homeMenu()
{
  if (isLoggedIn)
  {
    afterLogin();
  }
  else
  {
    cout << "Press 1 to login" << endl;
    cout << "Press 2 to Register" << endl;
    cout << "Press 3 to exit" << endl;
    int choice;
    cin >> choice;

    if (choice == 2)
    {
      registration();
    }
    else if (choice == 1)
    {
      login();
    }
    else if (choice == 3)
    {
      return 0;
    }
    else
    {
      cout << "Invalid choice" << endl;
      return 0;
    }
  }

  return 0;
}

void registration()
{
  cout << "<-- Please Register -->" << endl;
  string mail, password, role;
  int roleSelected = 1;
  cout << "Enter email address:";
  cin >> mail;
  cout << "Enter password:";
  cin >> password;
  cout << "Are you a Customer?(press 1)" << endl
       << "Are you Shop Owner?(press 2)" << endl;
  cin >> roleSelected;
  if (roleSelected == 1)
  {
    role = "customer";
  }
  else if (roleSelected == 2)
  {
    role = "owner";
  }
  else
  {
    cout << "Please select a valid option" << endl;
  }
  int id = getId("user.txt") + 1;
  userOnDb(id, mail, password, role);
  userId = id;
  if (role == "customer")
  {
    userRole = 1;
  }
  else if (role == "owner")
  {
    userRole = 2;
  }
  cout << "Registration is successful" << endl;
  afterLogin();
}
void login()
{
  if (loginAttempt >= 3)
  {
    cout << "You have exceeded the maximum number of login attempts. Please try again later." << endl;
    homeMenu();
    loginAttempt = 0;
  }
  else
  {
    if (isLoggedIn == false)
    {
      cout << "<-- Please Login -->" << endl;
      loginAttempt++;
      string mail, password;
      string user;
      cout << "Enter email address:";
      cin >> mail;
      cout << "Enter password:";
      cin >> password;
      ifstream fout;
      fout.open("user.txt");
      if (fout.is_open())
      {
        bool userFound = false;
        while (getline(fout,user))
        {
          if (user.find(mail) != string::npos && user.find(password) != string::npos)
          {
            userFound = true;
            isLoggedIn = true;
            cout << user << endl;
            string id;
            int i = 0;
            while (user[i] != ' ')
            {
              id = id + user[i];
              i++;
            }
          
            userId = stoi(id);

            // Extracting the role using substring between last space and end of string
            size_t lastSpacePos = user.rfind(' ');
            string role = user.substr(lastSpacePos + 1);

            // Trim leading/trailing spaces from role
            role.erase(0, role.find_first_not_of(' '));
            role.erase(role.find_last_not_of(' ') + 1);
 
            if (role == "customer")
            {
              userRole = 1;
              
            }
            else if (role == "owner")
            {
              userRole = 2;
            }
          }
        }
        if (userFound)
        {
          cout << "Login successful !!" << endl;
          homeMenu();
        }
        else
        {
          cout << "Wrong Credentials" << endl;
          faildLogin();
        }
        fout.close();
      }
      else
      {
        cout << "Something went wrong.Please try registering" << endl;
        homeMenu();
      }
    }
  }
}

void faildLogin()
{
  int choice;

  cout << "Try Again (Press 1) " << endl;
  cout << "Register (Press 2)" << endl;
  cout << "Close Program (Press 3)" << endl;
  cin >> choice;
  if (choice == 1)
  {
    login();
  }
  else if (choice == 2)
  {
    registration();
  }
  else if (choice==3) 
  {
    exit(0);
  }
  
}
bool userOnDb(int id, string email, string password, string role)
{

  ofstream userDb;
  userDb.open("user.txt", ios::app);
  if (userDb.is_open())
  {
    userDb << id << " " << email << " " << password << " " << role << endl;
    userDb.close();
    return true;
  }
  else
  {
    userDb.close();
    cout << "Error";
    return false;
  }
}

void addProduct()
{
  int idCount = getId("products.txt");
  cout << " <-- ADD PRODUCT --> " << endl;
  string name;
  int price;

  cout << " Product Name:";
  cin >> name;
  cout << " Product Price:";
  cin >> price;
  ofstream productFile("products.txt", ios::app);
  productFile << idCount + 1 << " " << name << " " << price << endl;
  productFile.close();
  cout << " Product Added Successfully " << endl;
  addOrShow();
}

void buyProduct()
{
  cout << " <-- BUY PRODUCT --> " << endl;
    displayProduct();
    int productId;
    cout << "Product Id:";
    cin >> productId;
    cout <<"Product purchase successful !!!" << endl<<endl;
    purchaseHistory(productId);
  buyOrShow();
}

int getId(string fileName)
{
  string existing;
  int idCount = 0;
  ifstream item;
  item.open(fileName);
  if (item.is_open())
  {
    while (getline(item, existing))
    {
      idCount++;
    }

    item.close();
  }
  else
  {
    cout << "Something went wrong" << endl;
  }
  return idCount;
}

void afterLogin()
{
  if (userRole == 1)
  {
   buyOrShow();
  }
  else if (userRole == 2)
  {
    addOrShow();
  }
}
void purchaseHistory(int productId){
  
  string buyer=to_string(userId);
  int newData=productId;
  ifstream fin("purchased.txt");
    ofstream fout("temp.txt");
    bool idFound = false;

    while (!fin.eof()) {
        string user;
        getline(fin, user);

        if (!user.empty()) {
            size_t idEnd = user.find(' ');
            if (idEnd != string::npos) {
                string id = user.substr(0, idEnd);
                string restOfLine = user.substr(idEnd + 1);

                if (id == buyer) {
                    // ID exists, append newData to the existing line
                    fout << id << " " << restOfLine << " " << newData << endl;
                    idFound = true;
                } else {
                    // ID doesn't match, copy the line as it is
                    fout << user << endl;
                }
            }
        }
    }

    fin.close();

    // If the user was not found, add a new line
    if (!idFound) {
        fout << userId << " "<< newData << endl;
    }

    fout.close();

    // Rename temp.txt to user.txt
    remove("purchased.txt");
    rename("temp.txt", "purchased.txt");
}
    
void findProduct(string targetId)
{

  ifstream inputFile("products.txt");

  if (!inputFile.is_open())
  {
    cerr << "Error opening the file." << endl;
    return;
  }

  string line;
  while (getline(inputFile, line))
  {
    size_t idEnd = line.find(' ');
    // Read the ID
    string id = line.substr(0, idEnd);
    // Check if the IDs match
    if (id == targetId)
    {
    string restOfLine = line.substr(idEnd + 1, line.length());
      // Create istringstream for each line
      istringstream iss(restOfLine);

      // Iterate through the string word by word
      string word;
      while (iss >> word)
      {
        cout  << word<<"\t";
      break; // Stop searching after finding the matching product name
      }
    }
  }

  inputFile.close();
}
void fetchHistory()
{
  cout<<"<-- Products you brought so far -->"<<endl;
  ifstream history;
  history.open("purchased.txt");
  if (history.is_open())
  {
    string singleLine;
    while (!history.eof())
    {

      getline(history, singleLine);
      size_t findSpace = singleLine.find(' ');
      string id = singleLine.substr(0, findSpace);
      if (id == to_string(userId))
      {
       string restOfLine = singleLine.substr(findSpace + 1, singleLine.length());
      istringstream iss(restOfLine);
        // Iterate through the string word by word
        string word;
        while (iss >> word)
        {
          
         findProduct(word);
        }
        cout<<endl;
      }
    }
  }
  buyOrShow();
}

void buyOrShow(){
cout<<"Press 1 to buy"<<endl;
cout<<"Press 2 to Show purchased list"<<endl;
cout<<"Press 3 to log out"<<endl;
int choice;
cin>>choice;
switch (choice)
{
case 1:
  buyProduct();
  break;
case 2:
fetchHistory();
break;
case 3:
exit(0);

default:
cout<<"Wrong press."<<endl;
buyOrShow();
  break;
}
}


void displayProduct(){
   string product;
  ifstream allProduct;
  allProduct.open("products.txt");
  if (allProduct.is_open())
  {
    cout<<"id"<<" name"<<" price"<<endl;
    while (getline(allProduct, product))
    {
      cout << product << endl;
    }
  }
  if (userRole==2)
  {
    addOrShow();
  }
  
}

void addOrShow(){
  cout<<"Press 1 to Add Product"<<endl;
cout<<"Press 2 to Show list"<<endl;
cout<<"Press 3 to log out"<<endl;
int choice;
cin>>choice;
switch (choice)
{
case 1:
  addProduct();
  break;
case 2:
displayProduct();
break;
case 3:
exit(0);

default:
cout<<"Wrong press."<<endl;
buyOrShow();
  break;
}
}