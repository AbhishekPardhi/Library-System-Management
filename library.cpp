#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

time_t now = time(0);
tm *ltm = localtime(&now);
// cout << "Year: " << 1900 + ltm->tm_year<<endl;
// cout << "Month: "<< 1 + ltm->tm_mon<< endl;
// cout << "Day: "<< ltm->tm_mday << endl;

int diffTime(int day, int month, int year)
{
    struct tm a = {0, 0, 0, day, month, year};
    struct tm b = {0, 0, 0, ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year};
    time_t x = mktime(&a);
    time_t y = mktime(&b);
    if ( x != (time_t)(-1) && y != (time_t)(-1) )
    {
        double difference = difftime(y, x) / (60 * 60 * 24);
        return (int)difference;
    }
    else
        return 0;
}

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
            this->dueDate = ltm->tm_mday;
            this->dueMonth = 1 + ltm->tm_mon;
            this->dueYear = 1900 + ltm->tm_year;
        }
        Book* Book_Request(int timeLimit)
        {
            Book *book = new Book;
            if(this->dueDate == ltm->tm_mday && this->dueMonth == 1 + ltm->tm_mon && this->dueYear == 1900 + ltm->tm_year)
            {
                time_t now = time( NULL);
                struct tm now_tm = *localtime( &now);
                struct tm then_tm = now_tm;
                then_tm.tm_sec += timeLimit * 24 * 3600;
                mktime( &then_tm);
                dueDate = then_tm.tm_mday;
                dueMonth = then_tm.tm_mon;
                dueYear = then_tm.tm_year;
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
            }
        }
        void Add()
        {
            string TitleString, AuthorString, ISBNString, PublicationString;
            cout << "Please type info of the Book to be added:" << endl;
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
                cout << "\nThere's no book to display!" << endl;
            else
            {
                cout << "\nList of " << " books:\n" << endl;
                // for (int i = 0; i < books.size(); i++)
                // {
                //     cout << i + 1 << ". " << books[i].Title << endl;
                // }
                cout
                    << left
                    << setw(4)
                    << "Sr."
                    << left
                    << setw(12)
                    << "Title"
                    << left
                    << setw(12)
                    << "Author"
                    << left
                    << setw(15)
                    << "ISBN"
                    << left
                    << setw(12)
                    << "Publication"
                    << endl;
                std::string str("");
                str.insert(0, 52, '-');
                cout << str << endl;
                for (int i = 0; i < this->books.size(); i++)
                {
                    cout
                        << left
                        << setw(4)
                        << i+1
                        << left
                        << setw(12)
                        << books[i].Title
                        << left
                        << setw(12)
                        << books[i].Author
                        << left
                        << setw(15)
                        << books[i].ISBN
                        << left
                        << setw(12)
                        << books[i].Publication
                        << endl;
                }
            }
            return;
        }
};

class UserDatabase;
BookDatabase bookDatabase;

class User
{
    public:
        string name;
        string id;
        string password;
        vector<Book*> listOfBooks;

        friend class UserDatabase;
        friend class Professor;
        friend class Student;
        friend class Librarian;
        virtual void Instructions(UserDatabase*userDatabase)
        {
            cout << "User instructions..." << endl;
        }
        void Calculate_fine(int fineRate)
        {
            int Fine_amount = 0;
            for (int i = 0; i < this->listOfBooks.size(); i++)
            {
                int timeDifference = diffTime(this->listOfBooks[i]->dueDate, this->listOfBooks[i]->dueMonth, this->listOfBooks[i]->dueYear);
                Fine_amount += (timeDifference>0) ? (fineRate*timeDifference) : 0;
            }
            cout << "\nThe total fine of the User \"" << this->name << "\" is: Rs." << Fine_amount << endl <<  endl;
            return;
        }
        void Clear_fine_amount()
        {
            for (int i = 0; i < this->listOfBooks.size(); i++)
            {
                this->listOfBooks[i]->dueDate = ltm->tm_mday;
                this->listOfBooks[i]->dueMonth = 1 + ltm->tm_mon;
                this->listOfBooks[i]->dueYear = 1900 + ltm->tm_year;
            }
            this->listOfBooks.clear();
            cout << "\nSuccessfully Returned all issued books\n" << endl;
            return;
        }
        virtual string className()
        {
            cout << "shouldn't be accessible" << endl;
            return "noooo";
        }
        void RequestBook(int timeLimit)
        {
            int num;
            while(true)
            {
                if(bookDatabase.books.size()==0)
                {
                    cout << "\nThere isn't any book available!\n" << endl;
                    break;
                }
                cout << "\nThis is the list of available books:\n" << endl;
                cout
                    << left
                    << setw(4)
                    << "Sr."
                    << left
                    << setw(20)
                    << "Title"
                    << left
                    << setw(20)
                    << "Author"
                    << left
                    << setw(20)
                    << "ISBN"
                    << left
                    << setw(20)
                    << "Publication"
                    << left
                    << setw(12)
                    << "Due Date"
                    << endl;
                std::string str("");
                str.insert(0, 96, '-');
                cout << str << endl;
                for (int i = 0; i < bookDatabase.books.size(); i++)
                {
                    if(bookDatabase.books[i].dueDate == ltm->tm_mday && bookDatabase.books[i].dueMonth == 1 + ltm->tm_mon && bookDatabase.books[i].dueYear == 1900 + ltm->tm_year)
                    {
                        cout
                            << left
                            << setw(4)
                            << i+1
                            << left
                            << setw(20)
                            << bookDatabase.books[i].Title
                            << left
                            << setw(20)
                            << bookDatabase.books[i].Author
                            << left
                            << setw(20)
                            << bookDatabase.books[i].ISBN
                            << left
                            << setw(20)
                            << bookDatabase.books[i].Publication
                            << left
                            << setw(2)
                            << bookDatabase.books[i].dueDate
                            << left
                            << setw(1)
                            << "/"
                            << left
                            << setw(2)
                            << bookDatabase.books[i].dueMonth
                            << left
                            << setw(1)
                            << "/"
                            << left
                            << setw(4)
                            << bookDatabase.books[i].dueYear
                            << endl;
                    }
                }
                if(this->className()=="student" && this->listOfBooks.size()==5)
                {
                    cout << "\nCan't issue more than 5 books at a time!\n" << endl;
                    break;
                }
                cout << "\nType -1 to Return\nType your choice :";
                cin >> num;
                if(num==-1)
                    break;
                Book *_book = bookDatabase.books[num - 1].Book_Request(timeLimit);
                if(_book!=NULL)
                {
                    this->listOfBooks.push_back(_book);
                    cout << "\nSuccesfully issued book: \"" << _book->Title << "\"\n" << endl;
                }
                else
                    cout << "\nPlease choose only those books which are available!\n" << endl;
            }
            return;
        }
        void Display()
        {
            if(listOfBooks.size() == 0)
                cout << "\nYou haven't issued any book!\n" << endl;
            else
            {
                // for (int i = 0; i < this->listOfBooks.size();i++)
                // {
                //     cout << "i+1." << this->listOfBooks[i]->Title << endl;
                // }
                cout
                    << left
                    << setw(4)
                    << "Sr."
                    << left
                    << setw(20)
                    << "Title"
                    << left
                    << setw(20)
                    << "Author"
                    << left
                    << setw(20)
                    << "ISBN"
                    << left
                    << setw(20)
                    << "Publication"
                    << left
                    << setw(12)
                    << "Due Date"
                    << endl;
                std::string str("");
                str.insert(0, 96, '-');
                cout << str << endl;
                for (int i = 0; i < this->listOfBooks.size(); i++)
                {
                    cout
                        << left
                        << setw(4)
                        << i+1
                        << left
                        << setw(20)
                        << this->listOfBooks[i]->Title
                        << left
                        << setw(20)
                        << this->listOfBooks[i]->Author
                        << left
                        << setw(20)
                        << this->listOfBooks[i]->ISBN
                        << left
                        << setw(20)
                        << this->listOfBooks[i]->Publication
                        << left
                        << setw(2)
                        << this->listOfBooks[i]->dueDate
                        << left
                        << setw(1)
                        << "/"
                        << left
                        << setw(2)
                        << this->listOfBooks[i]->dueMonth
                        << left
                        << setw(1)
                        << "/"
                        << left
                        << setw(4)
                        << this->listOfBooks[i]->dueYear
                        << endl;
                }
            }
            return;
        }
};

class Professor: public User
{
    public:
        int fineRate = 5;
        int timeLimit = 60;
        Professor(string nameString = "ab", string idString = "200026", string passwordString = "1234")
        {
            name = nameString;
            id = idString;
            password = passwordString;
        }
        void Instructions(UserDatabase* userDatabase)
        {
            cout << "Loging in as a Professor" << endl;
            int ins;
            string pls = "Please type instruction number :";
            string help = "\n---Type '0' to show set of instructions---";
            string instructionsSet = "\n-1.Logout\n1.Display all books\n2.Display all your issued books\n3.Check availability/Issue book\n4.Calculate Fine\n5.Clear Fine Amount\n";
            string wrong = "\nWrong instruction number!";
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
                    bookDatabase.Display();
                    break;

                case 2:
                    this->Display();
                    break;

                case 3:
                    this->RequestBook(this->timeLimit);
                    break;

                case 4:
                    this->Calculate_fine(this->fineRate);
                    break;
                
                case 5:
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
        int fineRate = 2;
        int timeLimit = 30;
        Student(string nameString = "Abhishek", string idString = "200026", string passwordString = "1234")
        {
            User::name = nameString;
            User::id = idString;
            User::password = passwordString;
        }
        void Instructions(UserDatabase* userDatabase)
        {
            cout << "Loging in as a Student" << endl;
            int ins;
            string pls = "Please type instruction number :";
            string help = "\n---Type '0' to show set of instructions---";
            string instructionsSet = "\n-1.Logout\n1.Display all books\n2.Display all your issued books\n3.Check availability/Issue book\n4.Calculate Fine\n5.Clear Fine Amount\n.";
            string wrong = "\nWrong instruction number!";
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
                    bookDatabase.Display();
                    break;

                case 2:
                    this->Display();
                    break;

                case 3:
                    this->RequestBook(this->timeLimit);
                    break;

                case 4:
                    this->Calculate_fine(this->fineRate);
                    break;
                
                case 5:
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
        void AddUser(UserDatabase *userDatabase);
        void UpdateBook()
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
        void DeleteUser(UserDatabase *userDatabase);
        void SearchBook()
        {
            string titleString;
            cout << "Type the Title of the Book you want to search :";
            cin >> titleString;
            bookDatabase.Search(titleString);
        }
        void SearchUser(UserDatabase *userDatabase);
        void Instructions(UserDatabase *userDatabase);
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
        void Update()
        {
            string idString;
            string instructionSet = "-1.Return\n1.Change Name\n2.Change ID\n3.Change Password";
            string help = "---Type '0' to show set of instructions---";
            string wrong = "Wrong instruction number!";
            string pls = "Type your choice: ";
            int i, ins;
            cout << "Type User ID: ";
            cin >> idString;
            for (i = 0; i < users.size(); i++)
            {
                if(users[i]->name.compare(idString)==0)
                    break;
            }
            if(i == users.size())
            {
                cout << "User having ID as \"" << idString << "\" doesn't exist!" << endl;
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
                    string newName;
                    cout << "Type new User Name :";
                    cin >> newName;
                    cout << "Successfully changed Name of User from \"" << users[i]->name << "\" to \"" << newName<< "\"" << endl;
                    users[i]->name = newName;
                    break;
                }

                case 2:
                {
                    string newID;
                    cout << "Type new ID :";
                    cin >> newID;
                    cout << "Successfully changed ID of User from \"" << users[i]->id << "\" to \"" << newID << "\"" << endl;
                    users[i]->id = newID;
                    break;
                }

                case 3:
                {
                    string newPassword;
                    cout << "Type new Password :";
                    cin >> newPassword;
                    cout << "Successfully changed Password of User from \"" << users[i]->password << "\" to \"" << newPassword << "\"" << endl;
                    users[i]->password = newPassword;
                    break;
                }

                default:
                    cout << wrong << endl;
                    break;
                }
            }
        }
        void Delete(string userString)
        {
            for (int i = 0; i < users.size(); i++)
            {
                if(userString==users[i]->id)
                {
                    users.erase(users.begin() + i);
                    cout << "Succesfully deleted \"" << users[i]->name << "\" from users list" << endl;
                    return;
                }
            }
            cout << "User with ID \"" << userString << "\" doesn't exist!" << endl;
        }
        User* Search(string nameString)
        {
            for (int i = 0; i < users.size(); i++)
            {
                if(users[i]->name.compare(nameString)==0)
                {
                    cout << "Found book tiled as \"" << users[i]->name << " \"" << endl;
                    return users[i];
                }
            }
            cout << "Book titled as \"" << nameString << " \" doesn't exist!" << endl;
            User *userPointer = NULL;
            return userPointer;
        }
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

void Librarian::Instructions(UserDatabase* userDatabase)
{
    cout << "Loging in as a Librarian" << endl;
    int ins;
    string pls = "Please type instruction number :";
    string help = "\n---Type '0' to show set of instructions---";
    string instructionsSet = "\n-1.Logout\n1.Add a Book\n2.Add a User\n3.Delete a Book\n4.Delete a User\n5.List all Books\n6.List all Users"; // type -1 to logout
    string wrong = "\nWrong instruction number!";
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
            this->AddUser(userDatabase);
            break;

        case 3:
            this->DeleteBook();
            break;
        
        case 4:
            this->DeleteUser(userDatabase);
            break;

        case 5:
            bookDatabase.Display();
            break;
        
        case 6:
            userDatabase->Display();
            break;

        case 7:
            userDatabase->Display();
            break;

        case 8:
            userDatabase->Display();
            break;

        default:
            cout << wrong << endl;
            break;
        }
    }
    return;
}
void Librarian::DeleteUser(UserDatabase* userDatabase)
{
    string userString;
    cout << "Type ID of user :";
    cin >> userString;
    userDatabase->Delete(userString);
    return;
}
void Librarian::SearchUser(UserDatabase* userDatabase)
{
    string idString;
    cout << "Type the ID of the user you want to search :";
    cin >> idString;
    userDatabase->Search(idString);
}

string className()
{
    return "librarian";
}


User* Login(UserDatabase* userDatabase)
{
    string userName;
    string userPassword;
    int loginAttempt = 0;
    cout << "=>This is a Library Management System in C++\n" << endl;
    while (loginAttempt < 5)
    {
        cout << "Please enter your user name: ";
        cin >> userName;
        cout << "Please enter your user password: ";
        cin >> userPassword;
        for (auto user : userDatabase->users)
        {
            if (userName.compare(user->name) == 0 && userPassword.compare(user->password) == 0)
            {
                cout << "\nWelcome " << user->name << "!!" << endl
                        << "Thank you for logging in" << endl
                        << endl;
                cout << "";
                return user;
            }
        }
        cout << "\nInvalid login attempt" << endl
                << "Please check your credentials" << endl
                << endl;
        loginAttempt++;
    }
    cout << "Too many login attempts! The program will now terminate." << endl;
    User* null_ptr = NULL;
    return null_ptr; //make it dynamic, put time limit
};
void Librarian::AddUser(UserDatabase* userDatabase)
        {
            string nameString, idString, passwordString, className;
            cout << "Please type info of the User to be added:" << endl;
            cout << "Type Name :";
            cin >> nameString;
            cout << "Type ID :";
            cin >> idString;
            cout << "Type Password :";
            cin >> passwordString;
            cout << "Type User Type :";
            cin >> className;
            userDatabase->Add(nameString, idString, passwordString, className);

            std::ofstream userFile;
            userFile.open("UserDatabase.csv", std::ofstream::out | std::ofstream::app);
            userFile << endl
                     << nameString << "," << idString << "," << passwordString << "," << className;
            userFile.close();
        }

int main()
{
    UserDatabase userDatabase;
    User *user;
    while(true)
    {
        user = Login(&userDatabase);
        if(user != NULL)
        {
            user->Instructions(&userDatabase);
            cout << "\nHave a nice day!\nLoging out..\n\n";
        }
        else
        {
            cout << "Closing library.cpp...\n" << endl;
            return 0;
        }    
    }
}