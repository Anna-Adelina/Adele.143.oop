#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <vector>

using namespace std;

const string admin_pass = "12345677";

class Book {
private:
    string title;
    string author;
    int year;

public:
    Book() : title{}, author{}, year{} {}
    Book(const string& new_title, const string& new_author, int new_year)
        : title{ new_title }, author{ new_author }, year{ new_year } {}
    ~Book() {}
    void display() const {
        cout << "Book: " << title << ", Author: " << author << ", Year: " << year << endl;
    }
    void setTitle(const string& new_title) { title = new_title; }
    string getTitle() const { return title; }
    void setAuthor(const string& new_author) { author = new_author; }
    void setYear(int new_year) { year = new_year; }

    void save(ofstream& file) const {
        file << title << endl << author << endl << year << endl;
    }
    bool load(ifstream& file) {
        if (getline(file, title) && getline(file, author) && (file >> year)) {
            file.ignore();
            return true;
        }
        return false;
    }
};

class Reader {
private:
    string name;
    int age;

public:
    Reader() : name{}, age{} {}
    Reader(const string& new_name, int new_age)
        : name{ new_name }, age{ new_age } {}
    ~Reader() {}

    void display() const {
        cout << "Reader: " << name << ", Age: " << age << endl;
    }
    void setName(const string& new_name) { name = new_name; }
    string getName() const { return name; }
    void setAge(int new_age) { age = new_age; }

    void save(ofstream& file) const {
        file << name << endl << age << endl << endl;
    }
    bool load(ifstream& file) {
        if (getline(file, name) && (file >> age)) {
            file.ignore();
            return true;
        }
        return false;
    }
};

class Library {
private:
    string name;
    int book_amount;

public:
    Library() : name{ "KSD" }, book_amount{ 0 } {}
    Library(const string& new_name, int new_book_amount)
        : name{ new_name }, book_amount{ new_book_amount } {}
    ~Library() {}
    void display() const {
        cout << "Library: " << name << ", Amount of books: " << book_amount << endl;
    }
    void updateBookAmount(int new_amount) { book_amount = new_amount; }
    int getBookAmount() const { return book_amount; }

    void save(ofstream& file) const {
        file << name << endl << book_amount << endl;
    }
    bool load(ifstream& file) {
        if (getline(file, name) && (file >> book_amount)) {
            file.ignore();
            return true;
        }
        return false;
    }
};

vector<Book> books;
vector<Reader> readers;
shared_ptr<Library> library = make_shared<Library>();

void saveData() {
    ofstream booksFile("books.txt");
    ofstream readersFile("readers.txt");
    ofstream libraryFile("library.txt");

    for (const auto& book : books) {
        book.save(booksFile);
    }

    for (const auto& reader : readers) {
        reader.save(readersFile);
    }

    library->save(libraryFile);

    cout << "Data saved successfully.\n";
}

void loadData() {
    ifstream booksFile("books.txt");
    ifstream readersFile("readers.txt");
    ifstream libraryFile("library.txt");

    books.clear();
    Book book;
    while (book.load(booksFile)) {
        books.push_back(book);
    }

    readers.clear();
    Reader reader;
    while (reader.load(readersFile)) {
        readers.push_back(reader);
    }

    library->load(libraryFile);
    cout << "Data loaded successfully.\n";
}

class UserActionHistory {
public:
    static void saveAction(const string& action) {
        try {
            ofstream historyFile("user_action_history.txt", ios::app);
            if (!historyFile) {
                throw runtime_error("Failed to open file for action history.");
            }
            historyFile << action << endl;
        }
        catch (const exception& e) {
            cout << "Error saving action history: " << e.what() << endl;
        }
    }
};

void showUserMenu();

void showAdminMenu() {
    string password;
    int choice;

    cout << "\nEnter administrator password: ";
    cin >> password;

    if (password == admin_pass) {
        do {
            cout << "\nAdmin Menu:\n";
            cout << "1. Add Book\n";
            cout << "2. Add Reader\n";
            cout << "3. Update Library Book Amount\n";
            cout << "4. Save Data\n";
            cout << "5. Exit Admin Menu\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                string title, author;
                int year;
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                cout << "Enter book year: ";
                cin >> year;
                cin.ignore();
                books.emplace_back(title, author, year);
                UserActionHistory::saveAction("Added book: " + title);
                cout << "Book added successfully.\n";
                cout << "\nCurrent list of books:\n";
                for (const auto& book : books) {
                    book.display();
                }
            }
            else if (choice == 2) {
                string name;
                int age;
                cout << "Enter reader name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter reader age: ";
                cin >> age;
                readers.emplace_back(name, age);
                UserActionHistory::saveAction("Added reader: " + name);
                cout << "Reader added successfully.\n";
                cout << "\nCurrent list of readers:\n";
                for (const auto& reader : readers) {
                    reader.display();
                }
            }
            else if (choice == 3) {
                int new_amount;
                cout << "Enter new book amount: ";
                cin >> new_amount;
                library->updateBookAmount(new_amount);
                UserActionHistory::saveAction("Updated library book amount: " + to_string(new_amount));
                break;
            }
            else if (choice == 4) {
                saveData();
                break;
            }
            else if (choice == 5) {
                cout << "Exiting Admin Menu.\n";
                return;
            }
            else {
                cout << "Wrong choice, try again.\n";
            }
        } while (true);
    }
    else {
        cout << "Incorrect password. Access denied.\n";
    }

}

void showUserMenu() {
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Show Books\n";
        cout << "2. Show Readers\n";
        cout << "3. Show Library\n";
        cout << "4. Enter Admin Menu\n";
        cout << "5. Exit Program\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (books.empty()) {
                cout << "No books in the library.\n";
            }
            else {
                cout << "\nList of Books:\n";
                for (const auto& book : books) {
                    book.display();
                }
            }
            break;
        case 2:
            if (readers.empty()) {
                cout << "No readers registered.\n";
            }
            else {
                cout << "\nList of Readers:\n";
                for (const auto& reader : readers) {
                    reader.display();
                }
            }
            break;
        case 3:
            library->display();
            break;
        case 4:
            showAdminMenu();
            break;
        case 5:
            cout << "Exiting program.\n";
            exit(0);
            break;
        default:
            cout << "Wrong choice, try again.\n";
        }
    } while (true);
}

int main() {
    loadData();

    int userType;
    do {
        cout << "\nSelect user type:\n1. Administrator\n2. User\n3. Exit Program\nEnter choice: ";
        cin >> userType;

        if (userType == 1) {
            showAdminMenu();
        }
        else if (userType == 2) {
            showUserMenu();
        }
        else if (userType == 3) {
            cout << "Exiting program.\n";
            break;
        }
        else {
            cout << "This option doesn`t exist.\n";
        }
    } while (true);
    return 0;
}
