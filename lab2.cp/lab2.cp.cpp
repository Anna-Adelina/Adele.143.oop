#include <iostream>
#include <string>

using namespace std;

class Book {
private:
    string title;
    string author;
    int year;
    static int bookCount;

public:
    Book() 
        : title{ "Dumb Witness" }, author{ "Agatha Christie" }, year{ 1937 } {
        bookCount++;
    }
    Book(const string& new_title)
        : Book(new_title, 1937) {
    }
    Book(const string& new_title, int new_year)
        : title{ new_title }, author{ "Agatha Christie" }, year{ new_year } {
        bookCount++;
    }
    Book(const Book& other) : title(other.title), author(other.author), year(other.year) {
        cout << "Copy constructor of Book was called\n";
    }
    Book(Book&& other) noexcept
        : title(move(other.title)), author(move(other.author)), year(other.year) {
        cout << "Move constructor of Book was called\n";
        other.year = 0;
    }
    ~Book() {
        cout << "Destroying book: " << title << endl;
        bookCount--;
    }
    Book& setThis(const string title) {
        this->title = title;
        return *this;
    }
    Book& operator++() {
        ++year; 
        return *this;
    }
    Book operator+(const Book& other) {
        string new_title = title + " & " + other.title;  
        return Book(new_title); 
    }
    static int getbCount() { 
        return bookCount;
    }
    void display() const {
        cout << "Book: " << title << ", Author: " << author << ", Year: " << year << endl;
    }
    friend std::ostream& operator<<(std::ostream& os, const Book& b) {
        os << "Book: " << b.title << " by " << b.author << " (" << b.year << ")";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Book& b) {
        std::cout << "Enter title: ";
        is >> std::ws; 
        std::getline(is, b.title);

        std::cout << "Enter author: ";
        std::getline(is, b.author);

        std::cout << "Enter year: ";
        is >> b.year;

        return is;
    }
};
int Book::bookCount = 0;
class Reader {
private:
    string name;
    int age;
    static int readerCount;
public:
    Reader() : name{ "Natalia" }, age{ 19 } {
        readerCount++;
    }
    Reader(string new_name, int new_age)
        : name{ new_name }, age{ new_age } {
        readerCount++;
    }
    Reader(string new_name) : Reader(new_name, 19) {
        
    }
    Reader(const Reader& other) : name(other.name), age(other.age) {
        cout << "Copy constructor of Reader was called\n";
    }
    Reader(Reader&& other) noexcept : name(move(other.name)), age((other.age)) {
        cout << "Move constructor of Reader was called\n";
        other.age = 0;
    }
    ~Reader() {
        cout << "Destroying reader: " << name << endl;
        readerCount--;
    }
    static int getReaderCount() {
        return readerCount;
    }
    void display() const {
        cout << "Reader: " << name << ", Age: " << age << endl;
    }
};
int Reader::readerCount = 0;
class Library {
private:
    string name;
    int book_amount;
    static int libraryCount;
public:
    Library() : name{ "KSD" }, book_amount{ 66 } {
        libraryCount++;
    }
    Library(string new_name, int new_book_amount)
        : name{ new_name }, book_amount{ new_book_amount } {
        libraryCount++;
    }
    Library(string new_name) : Library(new_name, 66) {
        libraryCount++;
    }
    Library(const Library& other) : name(other.name), book_amount(other.book_amount) {
        cout << "Copy constructor of Library was called\n";
    }
    Library(Library&& other) noexcept : name(move(other.name)), book_amount(other.book_amount) {
        cout << "Move constructor of Library was called\n";
        other.book_amount = 0;
    }
    ~Library() {
        cout << "Destroying library: " << name << endl;
        libraryCount--;
    }
    static int getLibraryCount() {
        return libraryCount;
    }
    void display() const {
        cout << "Library: " << name << ", Amount of books: " << book_amount << endl;
    }
};
int Library::libraryCount = 0;
int main() {
    Book b;
    Book b1("Death on the Nile");
    Book b2("They Do It With Mirrors", 1952);
    Reader h;
    Reader h1("Oksana", 20);
    Reader h2("Anna");
    Library s;
    Library s1("Vivat", 62);

    cout << "Number of books: " << Book::getbCount() << endl;
    cout << "Number of readers: " << Reader::getReaderCount() << endl;
    cout << "Number of libraries: " << Library::getLibraryCount() << endl;

    ++b1;  
    b1.display();  

    Book b3 = b1 + b2;  
    b3.display();  

    cout << endl << "Insertion example";
    std::cout << b3 << "\n";

    Book b4;
    cout << endl << "Extraction example\n";
    std::cin >> b4; 
    std::cout << b4 << "\n";

    cout << "\nChanging the name of book with this:\n";
    b.setThis("New Title").display();

    cout << "\nCopying objects:\n";
    Book b_copy = b1;
    Reader h_copy = h1;
    Library s_copy = s1;

    cout << "\nObjects:\n";
    b.display();
    b1.display();
    b2.display();
    h.display();
    h1.display();
    h2.display();
    s.display();
    s1.display();

    cout << "\nDisplaying copied objects:\n";
    b_copy.display();
    h_copy.display();
    s_copy.display();
    
    cout << "\nMoving objects:\n";
    Book b_move = move(b1);  
    Reader h_move = move(h1);  
    Library s_move = move(s1);

    cout << "\nDisplaying moved objects:\n";
    b_move.display();
    h_move.display();
    s_move.display();


    cout << "\n";
    return 0;
}