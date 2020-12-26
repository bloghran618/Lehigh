#include <iostream>
#include <fstream>

using namespace std;

int WriteToText() {
ofstream myfile ("example.txt");
  if (myfile.is_open())
  {
    myfile << "This is a line.\n";
    myfile << "This is another line.\n";
    myfile.close();
  }
  else cout << "Unable to open file";
  return 0;
}

int ReadFromText() {
string line;
  ifstream myfile ("example.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      cout << line << '\n';
    }
    myfile.close();
  }

  else cout << "Unable to open file";

  return 0;
}

int Binary() {
streampos begin,end;
  ifstream myfile ("example.txt", ios::binary);
  begin = myfile.tellg();
  myfile.seekg (0, ios::end);
  end = myfile.tellg();
  myfile.close();
  cout << "size is: " << (end-begin) << " bytes.\n";
  return 0;
  }

int main()
{
    cout<<"Please Enter Your Selection"<<endl;
    cout<<"1: WriteToFile()"<<endl;
    cout<<"2: ReadFromFile()"<<endl;
    cout<<"3: Binary() //Read Size of File"<<endl;
    cout<<"4: Exit"<<endl;
    cout<<"\nSelection: ";
    int selection;
    cin>>selection;
    switch(selection) {
    case 1:
        WriteToText();
        break;
    case 2:
        ReadFromText() ;
        break;
    case 3:
        Binary();
        break;
    }
}
