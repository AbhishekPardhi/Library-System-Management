#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class Book
{
    public:
        string Title;
        string Author;
        string ISBN;
        string Publication;

        Book(string TitleString, string AuthorString, string ISBNString, string PublicationString)
        {
            Title = TitleString;
            Author = AuthorString;
            ISBN = ISBNString;
            Publication = PublicationString;
        }
        // int Book_Request();
        // int Show_duedate();
};

class BookDatabase
{
    public:
        static vector<Book> books;
    
        // int Add();
        // int Update();
        // int Delete();
        // int Search();
        // void Display();
};

class User
{
    public:
        string name;
        string id;
        string password;

        friend class UserDatabase;
        friend class Professor;
        friend class Student;
        friend class Librarian;
        virtual void Instructions()
        {
            cout << "User instructions..." << endl;
        }
        virtual void Calculate_fine()
        {
            cout << "ye wala calculate ni access karna h" << endl;
        }
        virtual void Clear_fine_amount()
        {
            cout << "ye wala clear ni access karna h" << endl;
        }
        // virtual string className();
};

class Professor: public User
{
    public:
        int Fine_amount;
        vector<Book> listOfBooks;
    
        Professor(string nameString = "ab", string idString = "200026", string passwordString = "1234")
        {
            name = nameString;
            id = idString;
            password = passwordString;
        }
        void Calculate_fine()
        {
            cout << "calculating fine" << endl;
        }
        void Clear_fine_amount()
        {
            cout << "clearing fine amount" << endl;
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
                    this->Calculate_fine();
                    break;
                
                case 2:
                    this->Clear_fine_amount();
                    break;
                
                default:
                    cout << wrong << endl;
                    break;
                }
            }
        }
        string className()
        {
            return "professor";
        }
};

class Student: public User
{
    public:
        int Fine_amount;
        vector<Book> listOfBooks;
    
        Student(string nameString = "Abhishek", string idString = "200026", string passwordString = "1234")
        {
            User::name = nameString;
            User::id = idString;
            User::password = passwordString;
        }
        void Calculate_fine()
        {
            cout << "calculating fine" << endl;
        }
        void Clear_fine_amount()
        {
            cout << "clearing fine amount" << endl;
        }
        void Instructions()
        {
            int ins;
            string pls = "Please type instruction number :";
            string help = "---Type '0' to show set of instructions---";
            string instructionsSet = "1.Calculate Fine\n2.Clear Fine Amount\n."; //type -1 to logout
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
                    this->Calculate_fine();
                    break;
                
                case 2:
                    this->Clear_fine_amount();
                    break;
                
                default:
                    cout << wrong << endl;
                    break;
                }
            }
        }
        string className()
        {
            return "student";
        }
};

class Librarian: public User
{
    public:
        Librarian(string nameString = "Abhishek", string idString = "200026", string passwordString = "1234")
        {
            name = nameString;
            id = idString;
            password = passwordString;
        }
        // void Add(const User &);
        // void Add(const Book &);
        // void Update();
        // void Delete();
        // void listAllUsers(UserDatabase* userDatabase)
        // {
        //     userDatabase->Display();
        // }
        void Calculate_fine()
        {
            cout << "calculating fine" << endl;
        }
        void Clear_fine_amount()
        {
            cout << "clearing fine amount" << endl;
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
                    //this->Add();
                    break;
                
                case 2:
                    //this->listAllUsers();
                    break;
                
                default:
                    cout << wrong << endl;
                    break;
                }
            }
            return;
        }
        string className()
        {
            return "librarian";
        }
};

class UserDatabase
{
    public:
        vector<User*> users;
    
        UserDatabase()
        {
            Add("Abhishek", "200026", "1234", "student");
        }
        void Add(string nameString, string idString, string passwordString, string className)
        {
            if(className == "student")
            {
                User *userPointer = new Student;
                Student studentObject = Student(nameString, idString, passwordString);
                *userPointer = studentObject;
                users.push_back(userPointer);
            }
            else if(className == "professors")
            {
                User *userPointer = new Professor;
                Professor professorObject = Professor(nameString, idString, passwordString);
                *userPointer = professorObject;
                users.push_back(userPointer);
            }
            else if(className == "librarian")
            {
                User *userPointer = new Librarian;
                Librarian librarianObject = Librarian(nameString, idString, passwordString);
                *userPointer = librarianObject;
                users.push_back(userPointer);
            }
            else
                cout << "class name: \"" << className << "\" doesn't exist!" << endl;
        }
        // void Update();
        // void Delete();
        // void Search();
        // void Display();
        
};

UserDatabase userDatabase;


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
        //User *userPointer = (User *)calloc(1, sizeof(User));
        //User *userPointer;
        for (auto user : userDatabase.users)
        {
            if (userName.compare(user->name) == 0 && userPassword.compare(user->password) == 0)
            {
                cout << "Welcome " << user->name << "!!" << endl
                        << "Thank you for logging in." << endl
                        << endl;
                cout << "";
                //userPointer = user;
                //return userPointer;
                return user;
            }
        }
        cout << "Invalid login attempt." << endl
                << "Please check your credentials." << endl
                << endl;
        loginAttempt++;
        //delete userPointer;
    }
    cout << "Too many login attempts! The program will now terminate." << endl;
    User* null_ptr = NULL;
    return null_ptr; //make it dynamic, put time limit
}

int main()
{
    time_t now = time(0);
    //UserDatabase userDatabase;
    User *user;
    while(true)
    {
        user = Login();
        //cout << user->name << endl;
        if(user != NULL)
        {
            user->Instructions();
            //user->check();
        }
        else
        {
            cout << "Closing library.cpp..." << endl;
            return 0;
        }    
        //delete user;
    }
}