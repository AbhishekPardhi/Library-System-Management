#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class Book
{
    private:
        string Title;
        string Author;
        string ISBN;
        string Publication;

    public:
        Book(string TitleString, string AuthorString, string ISBNString, string PublicationString)
        {
            Title = TitleString;
            Author = AuthorString;
            ISBN = ISBNString;
            Publication = PublicationString;
        }
        int Book_Request();
        int Show_duedate();
};

class User
{
    private:
        string name;
        string id;
        string password;

    public:
        User(string nameString = "Abhishek", string idString = "200026", string passwordString = "1234")
        {
            name = nameString;
            id = idString;
            password = passwordString;
        }
        friend class UserDatabase;
        virtual void Instructions();
};

class UserDatabase
{
    private:
        vector<User> users;
    
    public:
        UserDatabase();
        int Add();
        int Update();
        int Delete();
        int Search();
        void Display();
        User* Login()
        {
            string userName;
            string userPassword;
            int loginAttempt = 0;
            cout << "This is a Library Management System in C++" << endl;
            while (loginAttempt < 5)
            {
                cout << "Please enter your user name: ";
                cin >> userName;
                cout << "Please enter your user password: ";
                cin >> userPassword;
                User *userPointer = (User *)calloc(1, sizeof(User));
                for (User user : users)
                {
                    if (userName.compare(user.name) == 0 && userPassword.compare(user.password) == 0)
                    {
                        cout << "Welcome " << user.name << "!!" << endl
                             << "Thank you for logging in." << endl
                             << endl;
                        cout << "";
                        userPointer = &user;
                        return userPointer;
                    }
                }
                cout << "Invalid login attempt." << endl
                     << "Please check your credentials." << endl
                     << endl;
                loginAttempt++;
            }
            cout << "Too many login attempts! The program will now terminate.";
            return 0;
        }
};

class Professor: public User
{
    private:
        int Fine_amount;
        vector<Book> listOfBooks;
    
    public:
        Professor(int fine, vector<Book> list)
        {
            Fine_amount = fine;
            listOfBooks = list;
        }
        int Calculate_fine();
        int Clear_fine_amount();
        void Instructions()
        {
            int ins;
            string pls = "Please type instruction number :";
            string help = "---Type '0' to show set of instructions---";
            string instructionsSet = ""; //type -1 to logout
            string wrong = "Wrong instruction number!";
            while(true)
            {
                cout << help << endl
                     << pls;
                cin >> ins;
                switch (ins)
                {
                case -1:
                    return;
                    break;
                
                case 0:
                    cout << instructionsSet << endl;
                    break;
                
                case 1:
                    Calculate_fine();
                    break;
                
                case 2:
                    Clear_fine_amount();
                    break;
                
                default:
                    cout << wrong << endl;
                    break;
                }
            }
        }
};

class Student: public User
{
    private:
        int Fine_amount;
        vector<Book> listOfBooks;
    
    public:
        Student(int fine, vector<Book> list)
        {
            Fine_amount = fine;
            listOfBooks = list;
        }
        int Calculate_fine();
        int Clear_fine_amount();
        void Instructions()
        {
            int ins;
            string pls = "Please type instruction number :";
            string help = "---Type '0' to show set of instructions---";
            string instructionsSet = ""; //type -1 to logout
            string wrong = "Wrong instruction number!";
            while(true)
            {
                cout << help << endl
                     << pls;
                cin >> ins;
                switch (ins)
                {
                case -1:
                    return;
                    break;
                
                case 0:
                    cout << instructionsSet << endl;
                    break;
                
                case 1:
                    Calculate_fine();
                    break;
                
                case 2:
                    Clear_fine_amount();
                    break;
                
                default:
                    cout << wrong << endl;
                    break;
                }
            }
        }
};

class Librarian: public User
{
    public:
        Librarian();
        void Add(const User &);
        // void Add(const Book &);
        // void Update();
        // void Delete();
        void listAllUsers(UserDatabase* userDatabase)
        {
            userDatabase->Display();
        }
        void Instructions()
        {
            int ins;
            string pls = "Please type instruction number :";
            string help = "---Type '0' to show set of instructions---";
            string instructionsSet = ""; //type -1 to logout
            string wrong = "Wrong instruction number!";
            while(true)
            {
                cout << help << endl
                     << pls;
                cin >> ins;
                switch (ins)
                {
                case -1:
                    return;
                    break;
                
                case 0:
                    cout << instructionsSet << endl;
                    break;
                
                case 1:
                    //Add();
                    break;
                
                case 2:
                    //listAllUsers();
                    break;
                
                default:
                    cout << wrong << endl;
                    break;
                }
            }
        }
};

class BookDatabase
{
    private:
        vector<Book> books;
    
    public:
        int Add();
        int Update();
        int Delete();
        int Search();
        void Display();
};

int main ()
{
    time_t now = time(0);
    UserDatabase userDatabase;
    while(true)
    {
        User* user = userDatabase.Login();
        if(user != NULL)
        {
            string type = typeid(user).name();
            if(type=="Professor")
                dynamic_cast<Professor *>(user)->Instructions();
            else if(type=="Student")
                dynamic_cast<Student *>(user)->Instructions();
            else
                dynamic_cast<Librarian *>(user)->Instructions();
        }
        else
            return 0;
        delete user;
    }
}