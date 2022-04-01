#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>

using namespace std;

time_t now = time(0);
    tm *ltm = localtime(&now);
    // cout << "Year: " << 1900 + ltm->tm_year<<endl;
    // cout << "Month: "<< 1 + ltm->tm_mon<< endl;
    // cout << "Day: "<< ltm->tm_mday << endl;

class Book
{
    public:
        int dueDate;
        int dueMonth;
        int dueYear;
        string Title;
        string Author;
        string ISBN;
        string Publication;

        Book(string TitleString = "", string AuthorString = "", string ISBNString = "", string PublicationString = "")
        {
            this->Title = TitleString;
            this->Author = AuthorString;
            this->ISBN = ISBNString;
            this->Publication = PublicationString;
        }
        Book* Book_Request(string userType)
        {
            Book *book = new Book;
            if(this->dueDate == ltm->tm_mday && this->dueMonth == 1 + ltm->tm_mon && this->dueYear == 1900 + ltm->tm_year)
            {
                dueDate += (userType == "student") ? 30 : 60;
                while(dueDate>30)
                {
                    dueMonth++;
                    if(dueMonth>12)
                        dueMonth = 1, dueYear++;
                    dueDate -= 30;
                }
                *book = *this;
            }
            else
                book = NULL;
            return book;
        }
        void Show_duedate()
        {
            cout << "This book will be available from " << this->dueDate << this->dueMonth << this->dueYear << endl;
            return;
        }
};

class BookDatabase
{
    public:
        vector<Book> books;
        BookDatabase()
        {
            string fname = "BookDatabase.csv";

            vector<vector<string>> content;
            vector<string> row;
            string line, word;
        
            fstream file (fname, ios::in);
            if(file.is_open())
            {
                while(getline(file, line))
                {
                    row.clear();
        
                    stringstream str(line);
        
                    while(getline(str, word, ','))
                        row.push_back(word);
                    content.push_back(row);
                }
            }
            else
                cout<<"Could not open the file\n";
        
            for(int i=0;i<content.size();i++)
            {
                Book newBook = Book(content[i][0],content[i][1],content[i][2],content[i][3]);
                books.push_back(newBook);
                // for(int j=0;j<content[i].size();j++)
                // {
                //     cout<<content[i][j]<<" ";
                // }
                //cout<<"\n";
            }
        }
        void Add()
        {
            string TitleString, AuthorString, ISBNString, PublicationString;
            cout << "Type Title :";
            cin >> TitleString;
            cout << "Type Author :";
            cin >> AuthorString;
            cout << "Type ISBN :";
            cin >> ISBNString;
            cout << "Type Publication :";
            cin >> PublicationString;
            Book bookObject = Book(TitleString, AuthorString, ISBNString, PublicationString);
            books.push_back(bookObject);

            std::ofstream bookFile; //("BookDatabase.csv");
            bookFile.open("BookDatabase.csv", std::ofstream::out | std::ofstream::app);
            bookFile << endl
                     << TitleString << "," << AuthorString << "," << ISBNString << "," << PublicationString;
            bookFile.close();
        }
        void Update()
        {
            string titleString;
            string instructionSet = "-1.Return\n1.Change Title\n2.Change Author\n3.Change ISBN\n4.Change Publication";
            string help = "---Type '0' to show set of instructions---";
            string wrong = "Wrong instruction number!";
            string pls = "Type your choice: ";
            int i, ins;
            cout << "Type book title: ";
            cin >> titleString;
            for (i = 0; i < books.size(); i++)
            {
                if(books[i].Title.compare(titleString)==0)
                    break;
            }
            if(i == books.size())
            {
                cout << "Book titled as \"" << titleString << "\" doesn't exist!" << endl;
                return;
            }
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
                
                case 1:
                {
                    string newTitle;
                    cout << "Type new Title :";
                    cin >> newTitle;
                    cout << "Successfully changed title of book \"" << books[i].Title << "\" to \"" << newTitle << "\"" << endl;
                    books[i].Title = newTitle;
                    break;
                }

                case 2:
                {
                    string newAuthor;
                    cout << "Type new Author :";
                    cin >> newAuthor;
                    cout << "Successfully changed Author of book \"" << books[i].Author << "\" to \"" << newAuthor << "\"" << endl;
                    books[i].Author = newAuthor;
                    break;
                }

                case 3:
                {
                    string newISBN;
                    cout << "Type new ISBN :";
                    cin >> newISBN;
                    cout << "Successfully changed ISBN of book \"" << books[i].ISBN << "\" to \"" << newISBN << "\"" << endl;
                    books[i].ISBN = newISBN;
                    break;
                }

                case 4:
                {
                    string newPublication;
                    cout << "Type new Publication :";
                    cin >> newPublication;
                    cout << "Successfully changed Publication of book \"" << books[i].Publication << "\" to \"" << newPublication<< "\"" << endl;
                    books[i].Publication = newPublication;
                    break;
                }

                default:
                    cout << wrong << endl;
                    break;
                }
            }
        }
        void Delete(string titleString)
        {
            for (int i = 0; i < books.size(); i++)
            {
                if(books[i].Title.compare(titleString)==0)
                {
                    cout << "Successfully deleted \"" << books[i].Title << " \"" << endl;
                    books.erase(books.begin() + i);
                    return;
                }
            }
            cout << "Book titled as \"" << titleString << " \" doesn't exist!" << endl;
            return;
        }
        Book* Search(string titleString)
        {
            for (int i = 0; i < books.size(); i++)
            {
                if(books[i].Title.compare(titleString)==0)
                {
                    cout << "Found book tiled as \"" << books[i].Title << " \"" << endl;
                    return &books[i];
                }
            }
            cout << "Book titled as \"" << titleString << " \" doesn't exist!" << endl;
            Book *bookPointer = NULL;
            return bookPointer;
        }
        void Display()
        {
            if(books.size() == 0)
                cout << "There's no book to display!" << endl;
            else
                cout << "List of " << books.size() << " books:" << endl;
            for (int i = 0; i < books.size(); i++)
            {
                cout << i + 1 << ". " << books[i].Title << endl;
            }
            return;
        }
};

BookDatabase bookDatabase;

class User
{
    public:
        string name;
        string id;
        string password;
        vector<Book> listOfBooks;

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
        virtual string className()
        {
            cout << "ye wala className ni access karna h" << endl;
            return "noooo";
        }
        void RequestBook()
        {
            cout << "Sorry, this book is not available!" << endl;
            cout << "This is the list of available books:" << endl;
            int num;
            for (int i = 0; i < bookDatabase.books.size(); i++)
            {
                if(bookDatabase.books[i].dueDate == ltm->tm_mday && bookDatabase.books[i].dueMonth == 1 + ltm->tm_mon && bookDatabase.books[i].dueYear == 1900 + ltm->tm_year)
                {
                    cout << "i+1." << bookDatabase.books[i].Title << " \"" << endl;
                }
            }
            cout << "Type your choice :";
            cin >> num;
            Book *_book = bookDatabase.books[num - 1].Book_Request(this->className());
            this->listOfBooks.push_back(*_book);
        }
};

class Professor: public User
{
    public:
        int Fine_amount;
    
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
            cout << "Loging in as a Professor" << endl;
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
            cout << "Loging in as a Student" << endl;
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
        void AddBook()
        {
            bookDatabase.Add();
            return;
        }
        void Update()
        {
            bookDatabase.Update();
            return;
        }
        void DeleteBook()
        {
            string titleString;
            cout << "Type Title :";
            cin >> titleString;
            bookDatabase.Delete(titleString);
            return;
        }
        void DeleteUser()
        {
            string userString;
            cout << "Type Username :";
            cin >> userString;
            //userDatabase.Delete(userString);
            return;
        }
        void Instructions()
        {
            cout << "Loging in as a Librarian" << endl;
            int ins;
            string pls = "Please type instruction number :";
            string help = "---Type '0' to show set of instructions---";
            string instructionsSet = "-1.Logout\n1.Add a Book\n2.Add a User\n3.Delete a Book\n4.Delete a User\n5.List all Books\n6.List all Users"; // type -1 to logout
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
                    this->AddBook();
                    break;
                
                case 2:
                    //this->userDatabase.Add(); CHECK ORDER OF INSTANTIATION!!
                    break;

                case 3:
                    this->DeleteBook();
                    break;
                
                case 4:
                    //this->DeleteUser(); CHECK ORDER OF INSTANTIATION!!
                    break;

                case 5:
                    bookDatabase.Display();
                    break;
                
                case 6:
                    //userDatabase->Display(); CHECK ORDER OF INSTANTIATION!!
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
            Add("abhi", "200026", "1234", "librarian");

            string fname = "UserDatabase.csv";

            vector<vector<string>> content;
            vector<string> row;
            string line, word;
        
            fstream file (fname, ios::in);
            if(file.is_open())
            {
                while(getline(file, line))
                {
                    row.clear();
        
                    stringstream str(line);
        
                    while(getline(str, word, ','))
                        row.push_back(word);
                    content.push_back(row);
                }
            }
            else
                cout<<"Could not open the file\n";
        
            for(int i=0;i<content.size();i++)
            {
                Add(content[i][0],content[i][1],content[i][2],content[i][3]);
                // for(int j=0;j<content[i].size();j++)
                // {
                //     cout<<content[i][j]<<" ";
                // }
                //cout<<"\n";
            }
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
            else if(className == "professor")
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
        void Display()
        {
            cout << "List of " << users.size() << " users:" << endl;
            for (int i = 0; i < users.size(); i++)
            {
                cout << i + 1 << ". " << users[i]->name << endl;
            }
            return;
        }
        
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
        for (auto user : userDatabase.users)
        {
            if (userName.compare(user->name) == 0 && userPassword.compare(user->password) == 0)
            {
                cout << "Welcome " << user->name << "!!" << endl
                        << "Thank you for logging in." << endl
                        << endl;
                cout << "";
                return user;
            }
        }
        cout << "Invalid login attempt." << endl
                << "Please check your credentials." << endl
                << endl;
        loginAttempt++;
    }
    cout << "Too many login attempts! The program will now terminate." << endl;
    User* null_ptr = NULL;
    return null_ptr; //make it dynamic, put time limit
}

int main()
{
    //UserDatabase userDatabase;
    User *user;
    while(true)
    {
        user = Login();
        //cout << user->name << endl;
        if(user != NULL)
        {
            user->Instructions();
        }
        else
        {
            cout << "Closing library.cpp..." << endl;
            return 0;
        }    
    }
}