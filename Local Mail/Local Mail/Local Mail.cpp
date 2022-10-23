#include<iostream>
#include<fstream>                   //file handling
#include<stdlib.h>                  //system("cls");
#include<string.h>
#include <stdio.h>                  //remove    //rename

using namespace std;

string username;

void Login()
{
    int isLoggedIn = 0;
    string password, userN, pass;

    system("cls");
    cout << "------------------------------------------------------------------" << endl;
    cout << "                           LOGIN                              " << endl;
    cout << "------------------------------------------------------------------" << endl << endl;
    cout << "USERNAME: ";
    cin >> username;
    cout << "PASWWORD: ";
    cin >> password;

    ifstream data("data.txt");                                                                                         //odczytanie pliku
    while (data >> userN >> pass)                                                                                                                                                                                    //
    {
        if (userN == username && pass == password)
            isLoggedIn = 1;
    }
    data.close();                                                                                                      //zamkniecie pliku

    system("cls");
    if (isLoggedIn == 1)
    {
        cout << "Hello " << username << "! Logged in successfully! \nPress Enter to continue...";
        cin.get();  cin.get();
    }
    else
    {
        cout << "Invalid username or password!\nPress Enter to continue...";
        cin.get();  cin.get();
        Login();
    }

}

void Register()
{
    int isRegistered = 0;

    string regUsername, regPassword, rUserN, rPass;
    cout << "------------------------------------------------------------------" << endl;
    cout << "                          REGISTRATION                             " << endl;
    cout << "------------------------------------------------------------------" << endl << endl;

    cout << "ENTER USERNAME: ";
    cin >> regUsername;
    cout << "ENTER PASSWORD: ";
    cin >> regPassword;

    ifstream data("data.txt");

    while (data >> rUserN >> rPass)
    {
        if (rUserN == regUsername || rPass == regPassword)
        {
            isRegistered = 1;
            system("cls");
        }
    }
    data.close();

    if (isRegistered == 1)
    {
        cout << "This user already exists. Please try again." << endl;
        cin.get();
        cin.get();
        Register();
    }

    else
    {
        ofstream reg("data.txt", ios::app);                                                                      //append, dopisuje, a nie nadpisuje
        reg << regUsername << ' ' << regPassword << endl;
        system("cls");
        cout << regUsername << ", you've been successfully registered!\nPress Enter to continue...";

        string name = regUsername + ".txt";
        ofstream user(name);
        user.close();
        reg.close();

        cin.get();
        cin.get();
    }
}

void Recovery()
{
    int userInput;
    system("cls");
    cout << "------------------------------------------------------------------" << endl;
    cout << "                    DATA RECOVERY                                 " << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << "         1.Forgot password.                                       " << endl;
    cout << "         2.Forgot username.                                       " << endl;
    cout << "------------------------------------------------------------------" << endl << endl;


    cout << "INPUT:  ";
    cin >> userInput;
    switch (userInput)
    {
    case 1:
    {
        int count = 0;
        string searchUsername, sUserN, sPass;
        cout << "\nINPUT USERNAME: ";
        cin >> searchUsername;

        ifstream Search_Username("data.txt");
        while (Search_Username >> sUserN >> sPass)
        {
            if (sUserN == searchUsername)
            {
                count = 1;
                break;
            }
        }
        Search_Username.close();

        if (count == 1)
        {
            cout << "PASSWORD FOUND!";
            cout << "\nPASSWORD: " << sPass;
            cout << endl << "Press ENTER to continue..." << endl;
            cin.get();
            cin.get();
            system("cls");
        }
        else
        {
            cout << "\nUser not found.\nPress ENTER to continue...";
            cin.get();
            cin.get();
        }
        break;
    }
    case 2:
    {
        int counter = 0;
        string searchPassword, sUserN2, sPass2;
        cout << "\nINPUT PASSWORD: ";
        cin >> searchPassword;

        ifstream Search_Password("data.txt");
        while (Search_Password >> sUserN2 >> sPass2)
        {
            if (sPass2 == searchPassword)
            {
                counter = 1;
                break;
            }
        }
        Search_Password.close();
        if (counter == 1)
        {
            cout << "USERNAME FOUND!";
            cout << "\nUSERNAME: " << sUserN2;
            cout << endl << "Press ENTER to continue..." << endl;
            cin.get();
            cin.get();
            system("cls");
        }
        else
        {
            cout << "\nUser not found.\nPress ENTER to continue...";
            cin.get();
            cin.get();
        }

        break;
    }

    default:
        cout << "Invalid input. Please try again..." << endl;
        cin.get();
        cin.get();

        break;
    }
}

void Mini_Menu(void (*f)())                                                                                             //wskaznik do funkcji, bo uzywane w nowa_wiadomosc i skzynka_odbiorcza
{
    int userInput = 0;
    cout << "1.CONTINUE                                                       " << endl;
    cout << "2.BACK TO MENU                                                   " << endl;
    cout << "------------------------------------------------------------------" << endl;

    cout << "INPUT: ";
    cin >> userInput;

    cout << "------------------------------------------------------------------" << endl << endl;

    if (userInput == 1)
        (*f)();
    else cin.get();
}

void New_Message_Header()
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "                        NEW MESSAGE                               " << endl;
    cout << "------------------------------------------------------------------" << endl;
}

void New_Message()
{
    string title, message, recipient;

    cout << "RECIPIENT: ";      cin >> recipient;

    //Excluding characters that cannot be used in a .txt file title
    cout << "Title cannot contain: / : * \" < > | or SPACE" << endl << "TITLE: ";
    getline(cin, title);
    getline(cin, title);

    string messageTitle = recipient + ".txt";
    ofstream user(messageTitle, ios::app);
    user << title << "   od: " << username << endl;
    user.close();

    title = title + ".txt";

    ofstream mess(title);
    if (mess.is_open())
    {
        cout << "\nPress \" $ \" end ENTER to send your message. \n\nYOUR MESSAGE: " << endl;
        getline(cin, message, '$');
        mess << message;
        mess.close();
        cin.get();
    }

    system("cls");
    cout << "SEND!\nPress ENTER to continue..." << endl;
    cin.get();
    cin.get();
}

void Show_Titles()
{
    string name = username + ".txt", input;

    ifstream titles(name);
    if (titles.is_open())
    {
        while (!titles.eof())                                                                                                    //end of file
        {
            getline(titles, input);
            cout << input << endl;
        }
    }
    titles.close();
    cout << "------------------------------------------------------------------" << endl;
}

void Received_Header()
{
    system("cls");
    cout << "------------------------------------------------------------------" << endl;
    cout << "                      RECEIVED MESSAGES                           " << endl;
    cout << "------------------------------------------------------------------" << endl;
    Show_Titles();
}

void Received()
{
    string title, message;

    cout << endl << "Input the name of the message you want to display:         " << endl;
    getline(cin, title);    getline(cin, title);

    system("cls");
    cout << "------------------------------------------------------------------" << endl;
    cout << "                          THE MESSAGE                             " << endl;
    cout << "------------------------------------------------------------------" << endl;

    string name = title + ".txt";

    ifstream message_file(name);
    if (message_file.is_open())
    {
        while (!message_file.eof())
        {
            getline(message_file, message);
            cout << message << endl;
        }
    }
    message_file.close();

    cout << "------------------------------------------------------------------" << endl;
    cout << "\nPress ENTER to continue..." << endl;
    cin.get();  cin.get();
}

void Delete(string title, string sender)
{
    string row, user = username + ".txt";

    ifstream message_titles;
    message_titles.open(user);
    ofstream temp;
    temp.open("temp.txt");

    title = title + "   from: " + sender;
    while (getline(message_titles, row))
    {
        if (row != title)
            temp << row << endl;
    }

    temp.close();
    message_titles.close();
    remove(user.c_str());                                                                             //.c_str zwraca lancuch znakow tylko do odczytu
    rename("temp.txt", user.c_str());

    system("cls");
    cout << "Message deleted!\nPress ENTER to continue..." << endl;
    cin.get(); cin.get();
}

int Delete_File(string title)
{
    string name = title + ".txt";
    int stan = remove(name.c_str());                                         // zwraca lancuch znaków tylko do odczytu

    return stan;
}

void Delete_FIle_Header()
{
    system("cls");
    cout << "------------------------------------------------------------------" << endl;
    cout << "                          DELETE MESSAGE                          " << endl;
    cout << "------------------------------------------------------------------" << endl;
    Show_Titles();
}

void Delete_Message()
{
    string title, sender;
    cout << "Input title of the message you want to delete:  " << endl;
    getline(cin, title);    getline(cin, title);

    cout << "Input name of the user who had sent it: " << endl;
    getline(cin, sender);

    if (Delete_File(title) != 0)
    {
        cout << "Something went wrong! Try again..." << endl;
        cin.get(); cin.get();
        Delete_Message();
    }

    else
        Delete(title, sender);
}

void menu(int userInput)
{
    system("cls");
    cout << "------------------------------------------------------------------" << endl;
    cout << "                               MENU                               " << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << "         1.NEW MESSAGE                                            " << endl;
    cout << "         2.RECEIVED                                               " << endl;
    cout << "         3.DELETE MESSAGES                                        " << endl;
    cout << "         4.EXIT                                                   " << endl;
    cout << "------------------------------------------------------------------" << endl << endl;

    cout << "INPUT: ";
    cin >> userInput;
    system("cls");

    switch (userInput)
    {
    case 1:
        New_Message_Header();
        Mini_Menu(New_Message);
        menu(userInput);
        break;
    case 2:
        Received_Header();
        Mini_Menu(Received);
        menu(userInput);
        break;
    case 3:
        Delete_FIle_Header();
        Mini_Menu(Delete_Message);
        menu(userInput);
        break;
    case 4:
        system("cls");
        cout << "Thank you for using the Local Mail :)\n\n\n";
        break;

    default:
        system("cls");
        cout << "Invalid input. Try again..." << endl;
    }
}

int main()
{
    int userInput;
    cout << "------------------------------------------------------------------" << endl;
    cout << "                           MENU                                   " << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << "          1.LOGIN                                                 " << endl;
    cout << "          2.REGISTER                                              " << endl;
    cout << "          3.USERNAME OR PASSWORD RECOVERY                         " << endl;
    cout << "          4.EXIT                                                  " << endl;
    cout << "------------------------------------------------------------------" << endl << endl;

    cout << "INPUT: ";           cin >> userInput;
    system("cls");

    switch (userInput)
    {
    case 1:
        Login();
        menu(userInput);
        break;
    case 2:
        Register();
        Login();
        menu(userInput);
        break;
    case 3:
        Recovery();
        system("cls");
        main();
        break;
    case 4:
        cout << "Thank you for using the Local Mail :)\n\n\n";
        break;
    default:
        cout << "Invalid input. Try again..." << endl;
    }

    return 0;
}

