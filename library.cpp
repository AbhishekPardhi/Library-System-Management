//-------------This code is written by Abhishek Pardhi IIT KANPUR CSE'24--------------

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

#define MAX_LEN 60  // Maximum len of any field of book/user can't be more than 18

void Clear()
{
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

time_t now = time(0);
tm *ltm = localtime(&now);

int diffTime(int day, int month, int year)
{
    struct tm a = {0, 0, 0, day, month -1, year - 1900};
    struct tm b = {0, 0, 0, ltm->tm_mday, ltm->tm_mon, ltm->tm_year};
    time_t x = mktime(&a);
    time_t y = mktime(&b);
    if ( x != (time_t)(-1) && y != (time_t)(-1) )
    {
        double difference = difftime(y, x) / (60 * 60 * 24);
        return (int)difference;
    }
    else
    {
        cout << mktime(&a);
        cout << " ";
        return 0;
    }
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
        string issuedToUser;

        Book(string TitleString = "", string AuthorString = "", string ISBNString = "", string PublicationString = "")
        {
            this->Title = TitleString;
            this->Author = AuthorString;
            this->ISBN = ISBNString;
            this->Publication = PublicationString;
            this->dueDate = ltm->tm_mday;
            this->dueMonth = 1 + ltm->tm_mon;
            this->dueYear = 1900 + ltm->tm_year;
            this->issuedToUser = "-None-";
        }
        Book* Book_Request(int timeLimit, string idString)
        {
            Book *book;
            if(diffTime(this->dueDate,this->dueMonth,this->dueYear)>=0)
            {
                time_t now = time( NULL);
                struct tm now_tm = *localtime( &now);
                struct tm then_tm = now_tm;
                then_tm.tm_sec += timeLimit * 24 * 3600;
                mktime( &then_tm);
                this->dueDate = then_tm.tm_mday;
                this->dueMonth = 1 + then_tm.tm_mon;
                this->dueYear = 1900 + then_tm.tm_year;
                this->issuedToUser = idString;
                book = this;
            }
            else
                book = NULL;
            return book;
        }
        void Show_duedate()
        {
            if(diffTime(this->dueDate,this->dueMonth,this->dueYear)>=0)
                cout << "\nThis book is available for issue" << endl;
            else
                cout << "\nThis book will be available from " << this->dueDate << "/" << this->dueMonth << "/" << this->dueYear << endl;
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
                newBook.dueDate = stoi(content[i][4]);
                newBook.dueMonth = stoi(content[i][5]);
                newBook.dueYear = stoi(content[i][6]);
                books.push_back(newBook);
            }
        }
        void Add()
        {
            Clear();
            string TitleString, AuthorString, ISBNString, PublicationString;
            cout << "\nPlease type info of the Book to be added:\n" << endl;
            cout << "Type Title :";
            getline(cin >> ws, TitleString);
            cout << "Type Author :";
            getline(cin >> ws, AuthorString);
            cout << "Type ISBN :";
            getline(cin >> ws, ISBNString);
            cout << "Type Publication :";
            getline(cin >> ws, PublicationString);
            Book bookObject = Book(TitleString, AuthorString, ISBNString, PublicationString);
            books.push_back(bookObject);
            system("CLS");
            cout << "\nSuccesfully Added Book \"" << TitleString << "\"" << endl;

            std::ofstream bookFile;
            bookFile.open("BookDatabase.csv", std::ofstream::out | std::ofstream::app);
            bookFile << endl
                     << TitleString << "," << AuthorString << "," << ISBNString << "," << PublicationString << "," << ltm->tm_mday << "," << 1 + ltm->tm_mon << "," << 1900 + ltm->tm_year;
            bookFile.close();
        }
        void Update()
        {
            Clear();
            string titleString;
            string instructionSet = "\n-1.Return\n1.Change Title\n2.Change Author\n3.Change ISBN\n4.Change Publication";
            string help = "\n---Type '0' to show set of instructions to Update Book Info---";
            string wrong = "Wrong instruction number!";
            string pls = "Type your choice: ";
            int i, ins;
            cout << "Type book title: ";
            getline(cin >> ws, titleString);
            for (i = 0; i < books.size(); i++)
            {
                if(books[i].Title.compare(titleString)==0)
                    break;
            }
            if(i == books.size())
            {
                cout << "\nBook titled as \"" << titleString << "\" doesn't exist!" << endl;
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
                    
                    case 0:
                    {
                        Clear();
                        cout << instructionSet << endl;
                    }    
                        break;

                    case 1:
                    {
                        string newTitle;
                        cout << "Type new Title :";
                        getline(cin >> ws, newTitle);
                        system("CLS");
                        cout << "\nSuccessfully changed title of book \"" << books[i].Title << "\" to \"" << newTitle << "\"" << endl;
                        books[i].Title = newTitle;
                        break;
                    }

                    case 2:
                    {
                        string newAuthor;
                        cout << "Type new Author :";
                        getline(cin >> ws, newAuthor);
                        system("CLS");
                        cout << "\nSuccessfully changed Author of book \"" << books[i].Author << "\" to \"" << newAuthor << "\"" << endl;
                        books[i].Author = newAuthor;
                        break;
                    }

                    case 3:
                    {
                        string newISBN;
                        cout << "Type new ISBN :";
                        getline(cin >> ws, newISBN);
                        system("CLS");
                        cout << "\nSuccessfully changed ISBN of book \"" << books[i].ISBN << "\" to \"" << newISBN << "\"" << endl;
                        books[i].ISBN = newISBN;
                        break;
                    }

                    case 4:
                    {
                        string newPublication;
                        cout << "Type new Publication :";
                        getline(cin >> ws, newPublication);
                        system("CLS");
                        cout << "\nSuccessfully changed Publication of book \"" << books[i].Publication << "\" to \"" << newPublication<< "\"" << endl;
                        books[i].Publication = newPublication;
                        break;
                    }

                    default:
                        cout << wrong << endl;
                        break;
                }
                fstream fin, fout;
                fin.open("BookDatabase.csv", ios::in);
                fout.open("BookDatabaseNew.csv", ios::out);
                string line;
                int iterator = 0;
                while(getline(fin, line))
                {
                    stringstream str(line);
                    if(iterator!=i)
                        fout << line;
                    else
                        fout << books[i].Title << "," << books[i].Author << "," << books[i].ISBN << "," << books[i].Publication << ","  << books[i].dueDate << "," << books[i].dueMonth << "," << books[i].dueYear;
                    if(iterator!=books.size()-1)
                            fout << endl;
                    iterator++;
                }
                fin.close();
                fout.close();
                remove("BookDatabase.csv");
                rename("BookDatabaseNew.csv", "BookDatabase.csv");
            }
        }
        void Delete(string titleString)
        {
            Clear();
            for (int i = 0; i < books.size(); i++)
            {
                if(books[i].Title.compare(titleString)==0)
                {
                    string confirm;
                    cout << "Are you sure you want to Delete Book \"" << titleString << "\" ?" << endl;
                    cout << "Type y/n: ";
                    cin >> confirm;
                    if(confirm=="y")
                    {
                        system("CLS");
                        cout << "\nSuccessfully Deleted Book \"" << titleString << " \" from books list" << endl;
                        books.erase(books.begin() + i);

                        fstream fin, fout;
                        fin.open("BookDatabase.csv", ios::in);
                        fout.open("BookDatabaseNew.csv", ios::out);
                        string line;
                        int iterator = 0;
                        while(getline(fin, line))
                        {
                            stringstream str(line);
                            if(iterator!=i)
                                fout << line;
                            if(iterator!=books.size()-1 && iterator!=i)
                                fout << endl;
                            iterator++;
                        }
                        fin.close();
                        fout.close();
                        remove("BookDatabase.csv");
                        rename("BookDatabaseNew.csv", "BookDatabase.csv");
                    }
                    else
                        cout << "\nAborted Deletion of Book \"" << titleString << "\"" << endl;
                    return;
                }
            }
            cout << "\nBook titled as \"" << titleString << " \" doesn't exist!" << endl;
            return;
        }
        Book* Search(string titleString)
        {
            for (int i = 0; i < books.size(); i++)
            {
                if(books[i].Title.compare(titleString)==0)
                    return &books[i];
            }
            cout << "Book titled as \"" << titleString << " \" doesn't exist!" << endl;
            Book *bookPointer = NULL;
            return bookPointer;
        }
        void Display(int check)
        {
            Clear();
            if(books.size() == 0)
                cout << "\nThere's no book to display!" << endl;
            else
            {
                cout << "\nList of books:\n" << endl;
                cout
                    << left
                    << setw(5)
                    << "Sr."
                    << left
                    << setw(MAX_LEN)
                    << "Title"
                    << left
                    << setw(MAX_LEN)
                    << "Author"
                    << left
                    << setw(MAX_LEN - 30)
                    << "ISBN"
                    << left
                    << setw(MAX_LEN)
                    << "Publication";
                    if(check)
                    {
                        cout
                        << left
                        << setw(12)
                        << "Due Date"
                        << endl;
                    }
                    else
                        cout << endl;
                std::string str("");
                str.insert(0, 4 * MAX_LEN - 11, '-');
                cout << str << endl;
                for (int i = 0; i < this->books.size(); i++)
                {
                    cout
                        << endl
                        << left
                        << setw(5)
                        << i + 1
                        << left
                        << setw(MAX_LEN)
                        << books[i].Title
                        << left
                        << setw(MAX_LEN)
                        << books[i].Author
                        << left
                        << setw(MAX_LEN - 30)
                        << books[i].ISBN
                        << left
                        << setw(MAX_LEN)
                        << books[i].Publication;
                        if (check)
                        {
                            cout
                            << left
                            << setw(2)
                            << books[i].dueDate
                            << left
                            << setw(1)
                            << "/"
                            << left
                            << setw(2)
                            << books[i].dueMonth
                            << left
                            << setw(1)
                            << "/"
                            << left
                            << setw(4)
                            << books[i].dueYear
                            << endl;
                        }
                        else
                            cout << endl;
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
            Clear();
            int Fine_amount = 0;
            for (int i = 0; i < this->listOfBooks.size(); i++)
            {
                int timeDifference = diffTime(this->listOfBooks[i]->dueDate, this->listOfBooks[i]->dueMonth, this->listOfBooks[i]->dueYear);
                Fine_amount += (timeDifference>0) ? (fineRate*timeDifference) : 0;
            }
            cout << "\nThe total fine of the User \"" << this->name << "\" is: Rs." << Fine_amount << endl <<  endl;
            return;
        }
        void Clear_fine_amount(UserDatabase *userDatabase);
        virtual string className()
        {
            cout << "shouldn't be accessible" << endl;
            return "noooo";
        }
        void RequestBook(int timeLimit, UserDatabase *userDatabase);
        void DisplayDueDate()
        {
            Clear();
            string bookTitle;
            cout << "\nPlease type the Book Title: ";
            getline(cin >> ws, bookTitle);
            Book* bookPointer = bookDatabase.Search(bookTitle);
            if(bookPointer!=NULL)
                bookPointer->Show_duedate();
        }
        void Display()
        {
            Clear();
            if(listOfBooks.size() == 0)
                cout << "\n\"" << this->name << "\" hasn't issued any book!" << endl;
            else
            {
                cout
                    << left
                    << setw(5)
                    << "Sr."
                    << left
                    << setw(MAX_LEN)
                    << "Title"
                    << left
                    << setw(MAX_LEN)
                    << "Author"
                    << left
                    << setw(MAX_LEN-30)
                    << "ISBN"
                    << left
                    << setw(MAX_LEN)
                    << "Publication"
                    << left
                    << setw(12)
                    << "Due Date"
                    << endl;
                std::string str("");
                str.insert(0, 4 * MAX_LEN - 11, '-');
                cout << str << endl;
                for (int i = 0; i < this->listOfBooks.size(); i++)
                {
                    cout
                        << endl
                        << left
                        << setw(5)
                        << i+1
                        << left
                        << setw(MAX_LEN)
                        << this->listOfBooks[i]->Title
                        << left
                        << setw(MAX_LEN)
                        << this->listOfBooks[i]->Author
                        << left
                        << setw(MAX_LEN-30)
                        << this->listOfBooks[i]->ISBN
                        << left
                        << setw(MAX_LEN)
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
            string instructionsSet = "\n-1.Logout\n1.Display all books\n2.Display all your issued books\n3.Check availability/Issue book\n4.Check availability of a Book\n5.Calculate Fine\n6.Clear Fine Amount";
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
                {
                    system("CLS");
                    cout << instructionsSet << endl;
                }    
                    break;
                
                case 1:
                    bookDatabase.Display(0);
                    break;

                case 2:
                    this->Display();
                    break;

                case 3:
                    this->RequestBook(this->timeLimit, userDatabase);
                    break;

                case 4:
                    this->DisplayDueDate();
                    break;
                
                case 5:
                    this->Calculate_fine(this->fineRate);
                    break;

                case 6:
                    this->Clear_fine_amount(userDatabase);
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
            string instructionsSet = "\n-1.Logout\n1.Display all books\n2.Display all your issued books\n3.Check availability/Issue book\n4.Check availability of a Book\n5.Calculate Fine\n6.Clear Fine Amount";
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
                {
                    system("CLS");
                    cout << instructionsSet << endl;
                }
                    break;
                
                case 1:
                    bookDatabase.Display(0);
                    break;

                case 2:
                    this->Display();
                    break;

                case 3:
                    this->RequestBook(this->timeLimit, userDatabase);
                    break;

                case 4:
                    this->DisplayDueDate();
                    break;
                
                case 5:
                    this->Calculate_fine(this->fineRate);
                    break;

                case 6:
                    this->Clear_fine_amount(userDatabase);
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
            Clear();
            bookDatabase.Update();
            return;
        }
        void DeleteBook()
        {
            Clear();
            string titleString;
            cout << "\nType Title :";
            getline(cin >> ws, titleString);
            bookDatabase.Delete(titleString);
            return;
        }
        void DeleteUser(UserDatabase *userDatabase);
        void SearchBook()
        {
            Clear();
            string titleString;
            cout << "Type the Title of the Book you want to search :";
            getline(cin >> ws, titleString);
            bookDatabase.Search(titleString);
        }
        void SearchUser(UserDatabase *userDatabase);
        void Instructions(UserDatabase *userDatabase);
        void ListOfBooks_User(UserDatabase *userDatabase);
        void BookIssuedToUser()
        {
            Clear();
            string bookTitle;
            cout << "\nPlease type the Book Title: ";
            getline(cin >> ws, bookTitle);
            for (int i = 0; i < bookDatabase.books.size(); i++)
            {
                if(bookTitle==bookDatabase.books[i].Title)
                {
                    if(bookDatabase.books[i].issuedToUser!="-None-")
                        cout << "\n\"" << bookTitle << "\" is issued to \"" << bookDatabase.books[i].issuedToUser << "\"" << endl;
                    else
                        cout << "\n\"" << bookTitle << "\" isn't issued yet" << endl;
                    return;
                }
            }
            cout << "\nCouldn't find a Book with title \"" << bookTitle << "\"" << endl;
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
                User *userPointer = Add(content[i][0], content[i][1], content[i][2], content[i][3]);
                for (int j = 4; j < content[i].size();j++)
                {
                    Book *bookPointer = bookDatabase.Search(content[i][j]);
                    bookPointer->issuedToUser = content[i][1];
                    userPointer->listOfBooks.push_back(bookPointer);
                }
            }
        }
        User* Add(string nameString, string idString, string passwordString, string className)
        {
            if(className == "student")
            {
                User *userPointer = new Student;
                Student studentObject = Student(nameString, idString, passwordString);
                *userPointer = studentObject;
                this->users.push_back(userPointer);
                system("CLS");
                cout << "\nSuccesfully Added User \"" << nameString << "\"" << endl;
                return userPointer;
            }
            else if(className == "professor")
            {
                User *userPointer = new Professor;
                Professor professorObject = Professor(nameString, idString, passwordString);
                *userPointer = professorObject;
                this->users.push_back(userPointer);
                system("CLS");
                cout << "\nSuccesfully Added User \"" << nameString << "\"" << endl;
                return userPointer;
            }
            else if(className == "librarian")
            {
                User *userPointer = new Librarian;
                Librarian librarianObject = Librarian(nameString, idString, passwordString);
                *userPointer = librarianObject;
                this->users.push_back(userPointer);
                system("CLS");
                cout << "\nSuccesfully Added User \"" << nameString << "\"" << endl;
                return userPointer;
            }
            else
                cout << "\nUser Type \"" << className << "\" doesn't exist!" << endl;
            User *userPointer = NULL;
            return userPointer;
        }
        void Update()
        {
            Clear();
            string idString;
            string instructionSet = "\n-1.Return\n1.Change Name\n2.Change ID\n3.Change Password";
            string help = "\n---Type '0' to show set of instructions to Update User Info---";
            string wrong = "Wrong instruction number!";
            string pls = "Type your choice: ";
            int i, ins;
            cout << "\nType User ID: ";
            getline(cin >> ws, idString);
            for (i = 0; i < users.size(); i++)
            {
                if(users[i]->id.compare(idString)==0)
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

                case 0:
                {
                    system("CLS");
                    cout << instructionSet << endl;
                }    
                    break;
                
                case 1:
                {
                    string newName;
                    cout << "Type new User Name :";
                    getline(cin >> ws, newName);
                    system("CLS");
                    cout << "\nSuccessfully changed Name of User from \"" << users[i]->name << "\" to \"" << newName<< "\"" << endl;
                    users[i]->name = newName;
                    break;
                }

                case 2:
                {
                    string newID;
                    cout << "Type new ID :";
                    getline(cin >> ws, newID);
                    system("CLS");
                    cout << "\nSuccessfully changed ID of User from \"" << users[i]->id << "\" to \"" << newID << "\"" << endl;
                    users[i]->id = newID;
                    break;
                }

                case 3:
                {
                    string newPassword;
                    cout << "Type new Password :";
                    getline(cin >> ws, newPassword);
                    system("CLS");
                    cout << "\nSuccessfully changed Password of User from \"" << users[i]->password << "\" to \"" << newPassword << "\"" << endl;
                    users[i]->password = newPassword;
                    break;
                }

                default:
                    cout << wrong << endl;
                    break;
                }
                fstream fin, fout;
                fin.open("UserDatabase.csv", ios::in);
                fout.open("UserDatabaseNew.csv", ios::out);
                string line;
                int iterator = 0;
                while(getline(fin, line))
                {
                    stringstream str(line);
                    if(iterator!=i)
                        fout << line;
                    else
                    {
                        fout << users[i]->name << "," << users[i]->id << "," << users[i]->password << "," << users[i]->className();
                        for (int j = 0; j < users[i]->listOfBooks.size(); j++)
                        {
                            fout << "," << users[i]->listOfBooks[j]->Title;
                        }
                    }
                    if(iterator!=users.size())
                        fout << endl;
                    iterator++;
                }
                fin.close();
                fout.close();
                remove("UserDatabase.csv");
                rename("UserDatabaseNew.csv", "UserDatabase.csv");
            }
        }
        void Delete(string userString)
        {
            for (int i = 0; i < users.size(); i++)
            {
                if(userString==users[i]->id)
                {
                    string confirm;
                    cout << "Are you sure you want to Delete User \"" << users[i]->name << "\" ?" << endl;
                    cout << "Type y/n: ";
                    cin >> confirm;
                    if(confirm=="y")
                    {
                        system("CLS");
                        cout << "\nSuccessfully Deleted User \"" << users[i]->name << " \" from users list" << endl;
                        users.erase(users.begin() + i);

                        fstream fin, fout;
                        fin.open("UserDatabase.csv", ios::in);
                        fout.open("UserDatabaseNew.csv", ios::out);
                        string line;
                        int iterator = 0;
                        while(getline(fin, line))
                        {
                            stringstream str(line);
                            if(iterator!=i)
                                fout << line;
                            if(iterator!=users.size()-1  && iterator!=i)
                                fout << endl;
                            iterator++;
                        }
                        fin.close();
                        fout.close();
                        remove("UserDatabase.csv");
                        rename("UserDatabaseNew.csv", "UserDatabase.csv");
                    }
                    else
                        cout << "\nAborted Deletion of Book \"" << users[i]->name << "\"" << endl;
                    return;
                }
            }
            cout << "\nUser with ID \"" << userString << "\" doesn't exist!" << endl;
        }
        User* Search(string nameString)
        {
            for (int i = 0; i < users.size(); i++)
            {
                if(users[i]->name.compare(nameString)==0)
                {
                    cout << "Found User named as \"" << users[i]->name << " \"" << endl;
                    return users[i];
                }
            }
            cout << "User named as \"" << nameString << " \" doesn't exist!" << endl;
            User *userPointer = NULL;
            return userPointer;
        }
        void Display()
        {
            system("CLS");
            if(this->users.size() == 0)
            {
                cout << "\nThere's no User to display!" << endl;
                return;
            }
            cout << "\nList of Users:\n" << endl;
            cout
                << left
                << setw(5)
                << "Sr."
                << left
                << setw(MAX_LEN)
                << "User Name"
                << left
                << setw(MAX_LEN)
                << "ID"
                << left
                << setw(MAX_LEN)
                << "Type of User"
                << endl;
            std::string str("");
            str.insert(0, 3 * MAX_LEN - 6, '-');
            cout << str << endl;
            for (int i = 0; i < this->users.size(); i++)
            {
                cout
                    << endl
                    << left
                    << setw(5)
                    << i + 1
                    << left
                    << setw(MAX_LEN)
                    << this->users[i]->name
                    << left
                    << setw(MAX_LEN)
                    << this->users[i]->id
                    << left
                    << setw(MAX_LEN)
                    << this->users[i]->className()
                    << endl;
            }
            return;
        }
};
void User::Clear_fine_amount(UserDatabase* userDatabase)
{
    Clear();
    for (int i = 0; i < this->listOfBooks.size(); i++)
    {
        this->listOfBooks[i]->dueDate = ltm->tm_mday;
        this->listOfBooks[i]->dueMonth = 1 + ltm->tm_mon;
        this->listOfBooks[i]->dueYear = 1900 + ltm->tm_year;
        this->listOfBooks[i]->issuedToUser = "-None-";
    }
    fstream fin, fout;
    fin.open("BookDatabase.csv", ios::in);
    fout.open("BookDatabaseNew.csv", ios::out);
    for (int i = 0; i < bookDatabase.books.size(); i++)
    {
        fout << bookDatabase.books[i].Title << "," << bookDatabase.books[i].Author << "," << bookDatabase.books[i].ISBN << "," << bookDatabase.books[i].Publication << "," << bookDatabase.books[i].dueDate << "," << bookDatabase.books[i].dueMonth << "," << bookDatabase.books[i].dueYear;
        if(i!=bookDatabase.books.size()-1)
            fout << endl;
    }
    fin.close();
    fout.close();
    remove("BookDatabase.csv");
    rename("BookDatabaseNew.csv", "BookDatabase.csv");

    string line;
    int iterator = 0;
    fin.open("UserDatabase.csv", ios::in);
    fout.open("UserDatabaseNew.csv", ios::out);
    while(getline(fin, line))
    {
        stringstream str(line);
        if(userDatabase->users[iterator]->name!=this->name)
            fout << line;
        else
            fout << this->name << "," << this->id << "," << this->password << "," << this->className();
        if(iterator!=userDatabase->users.size()-1)
            fout << endl;
        iterator++;
    }
    fin.close();
    fout.close();
    remove("UserDatabase.csv");
    rename("UserDatabaseNew.csv", "UserDatabase.csv");

    this->listOfBooks.clear();
    system("CLS");
    cout << "\nSuccessfully Returned all issued books" << endl;
    return;
}
void User::RequestBook(int timeLimit, UserDatabase* userDatabase)
{
    Clear();
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
            << setw(5)
            << "Sr."
            << left
            << setw(MAX_LEN)
            << "Title"
            << left
            << setw(MAX_LEN)
            << "Author"
            << left
            << setw(MAX_LEN-30)
            << "ISBN"
            << left
            << setw(MAX_LEN)
            << "Publication"
            << endl;
        std::string str("");
        str.insert(0, 4 * MAX_LEN - 11, '-');
        cout << str << endl;
        for (int i = 0; i < bookDatabase.books.size(); i++)
        {
            if(diffTime(bookDatabase.books[i].dueDate,bookDatabase.books[i].dueMonth,bookDatabase.books[i].dueYear)>=0)
            {
                cout
                    << endl
                    << left
                    << setw(5)
                    << i+1
                    << left
                    << setw(MAX_LEN)
                    << bookDatabase.books[i].Title
                    << left
                    << setw(MAX_LEN)
                    << bookDatabase.books[i].Author
                    << left
                    << setw(MAX_LEN-30)
                    << bookDatabase.books[i].ISBN
                    << left
                    << setw(MAX_LEN)
                    << bookDatabase.books[i].Publication
                    << endl;
            }
        }
        if(this->className()=="student" && this->listOfBooks.size()==5)
        {
            cout << "\nCan't issue more than 5 books at a time!\n" << endl;
            break;
        }
        cout << "\nType -1 to Return\nType your choice(Sr. of Book) :";
        cin >> num;
        if(num==-1)
            break;
        Book *_book = bookDatabase.books[num - 1].Book_Request(timeLimit, this->id);
        if(_book!=NULL)
        {
            this->listOfBooks.push_back(_book);
            system("CLS");
            cout << "\nSuccesfully issued book: \"" << _book->Title << "\"" << endl;
            fstream fin, fout;
            fin.open("BookDatabase.csv", ios::in);
            fout.open("BookDatabaseNew.csv", ios::out);
            string line;
            int iterator = 0;
            while(getline(fin, line))
            {
                stringstream str(line);
                if(iterator!=num-1)
                    fout << line;
                else
                    fout << bookDatabase.books[num-1].Title << "," << bookDatabase.books[num-1].Author << "," << bookDatabase.books[num-1].ISBN << "," << bookDatabase.books[num-1].Publication << ","  << bookDatabase.books[num-1].dueDate << "," << bookDatabase.books[num-1].dueMonth << "," << bookDatabase.books[num-1].dueYear;
                if(iterator!=bookDatabase.books.size()-1)
                    fout << endl;
                iterator++;
            }
            fin.close();
            fout.close();
            remove("BookDatabase.csv");
            rename("BookDatabaseNew.csv", "BookDatabase.csv");
            
            fin.open("UserDatabase.csv", ios::in);
            fout.open("UserDatabaseNew.csv", ios::out);
            iterator = 0;
            while(getline(fin, line))
            {
                stringstream str(line);
                if(userDatabase->users[iterator]->name!=this->name)
                    fout << line;
                else
                    fout << line << "," << _book->Title;
                if(iterator!=userDatabase->users.size()-1)
                    fout << endl;
                iterator++;
            }
            fin.close();
            fout.close();
            remove("UserDatabase.csv");
            rename("UserDatabaseNew.csv", "UserDatabase.csv");
        }
        else
        {
            system("CLS");
            cout << "\nPlease choose only those books which are available!" << endl;
        }
    }
    return;
}

void Librarian::Instructions(UserDatabase* userDatabase)
{
    cout << "Loging in as a Librarian" << endl;
    int ins;
    string pls = "Please type instruction number :";
    string help = "\n---Type '0' to show set of instructions---";
    string instructionsSet = "\n-1.Logout\n1.Add a Book\n2.Add a User\n3.List all Books\n4.List all Users\n5.Update a Book\n6.Update a User\n7.Delete a Book\n8.Delete a User\n9.Check which book is issued to which user\n10.Check list of Books issued to a User";
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
        {
            system("CLS");
            cout << instructionsSet << endl;
        }    
            break;
        
        case 1:
            this->AddBook();
            break;
        
        case 2:
            this->AddUser(userDatabase);
            break;

        case 3:
            bookDatabase.Display(1);
            break;
        
        case 4:
            userDatabase->Display();
            break;

        case 5:
            bookDatabase.Update();
            break;
        
        case 6:
            userDatabase->Update();
            break;

        case 7:
            this->DeleteBook();
            break;

        case 8:
            this->DeleteUser(userDatabase);
            break;

        case 9:
            this->BookIssuedToUser();
            break;

        case 10:
            ListOfBooks_User(userDatabase);
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
    Clear();
    string userString;
    cout << "\nType ID of user :";
    getline(cin >> ws, userString);
    userDatabase->Delete(userString);
    return;
}
void Librarian::SearchUser(UserDatabase* userDatabase)
{
    Clear();
    string idString;
    cout << "Type the ID of the user you want to search :";
    getline(cin >> ws, idString);
    userDatabase->Search(idString);
}
void Librarian::AddUser(UserDatabase* userDatabase)
{
    Clear();
    string nameString, idString, passwordString, className;
    cout << "\nPlease type info of the User to be added:\n" << endl;
    cout << "Type Name :";
    getline(cin >> ws, nameString);
    cout << "Type ID :";
    getline(cin >> ws, idString);
    cout << "Type Password :";
    getline(cin >> ws, passwordString);
    cout << "Type User Type :";
    getline(cin >> ws, className);
    User* userPointer = userDatabase->Add(nameString, idString, passwordString, className);
    if(userPointer!=NULL)
    {
        std::ofstream fin;
        fin.open("UserDatabase.csv", std::ofstream::out | std::ofstream::app);
        fin << endl
            << userPointer->name << "," << userPointer->id << "," << userPointer->password << ","
            << userPointer->className();
        fin.close();
    }
}
void Librarian::ListOfBooks_User(UserDatabase *userDatabase)
{
    Clear();
    string userString;
    cout << "\nType ID of user :";
    getline(cin >> ws, userString);
    for (int i = 0; i < userDatabase->users.size();i++)
    {
        if(userString==userDatabase->users[i]->id)
        {
            if(userDatabase->users[i]->listOfBooks.size()!=0) cout << "\n\"" << userDatabase->users[i]->name << "\" has issued " << userDatabase->users[i]->listOfBooks.size() << " books:" << endl;
            userDatabase->users[i]->Display();
            return;
        }
    }
    cout << "\nCouldn't find any User with ID \"" << userString << "\"\n" << endl;
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
        getline(cin >> ws, userName);
        cout << "Please enter your user password: ";
        getline(cin >> ws, userPassword);
        for (auto user : userDatabase->users)
        {
            if (userName.compare(user->name) == 0 && userPassword.compare(user->password) == 0)
            {
                Clear();
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
    return null_ptr;
};

int main()
{
    UserDatabase userDatabase;
    User *user;
    while(true)
    {
        Clear();
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