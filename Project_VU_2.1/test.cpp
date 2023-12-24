#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <sstream>
void purchased()
{
  string userId = to_string(2);
  string newData = "HEy mama";
  ifstream fin("purchased.txt");
  ofstream fout("temp.txt");
  bool idFound = false;

  while (!fin.eof())
  {
    string user;
    getline(fin, user);

    if (!user.empty())
    {
      size_t idEnd = user.find(' ');
      if (idEnd != string::npos)
      {
        string id = user.substr(0, idEnd);
        string restOfLine = user.substr(idEnd + 1, user.length());

        if (id == userId)
        {
          // ID exists, append newData to the existing line
          fout << id << " " << restOfLine << " " << newData << endl;
          idFound = true;
        }
        else
        {
          // ID doesn't match, copy the line as it is
          fout << user << endl;
        }
      }
    }
  }

  fin.close();

  // If the user was not found, add a new line
  if (!idFound)
  {
    fout << userId << " " << newData << endl;
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
  string userId = to_string(2);
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
      if (id == userId)
      {
       string restOfLine = singleLine.substr(findSpace + 1, singleLine.length());
      istringstream iss(restOfLine);
        // Iterate through the string word by word
        string word;
        while (iss >> word)
        {
          
         findProduct(word);
        }
      }
    }
  }
}
int main()
{
  // purchased();
  fetchHistory();
  return 0;
}
