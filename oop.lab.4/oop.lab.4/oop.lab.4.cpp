#include <iostream>
#include <string>

using namespace std;

class Book {
protected:
    string title;
    string author;
    int year;

public:
    Book(string new_title, string new_author, int new_year)
        : title{ new_title }, author{ new_author }, year{ new_year } {
    }
    ~Book() {
        cout << "Destructor of Book " << endl;
    }
    void display() const {
        cout << "Name: " << title << ", Author: " << author << ", Year: " << year << endl;
    }
};
class Genre : public Book {
public:
    Genre(string new_title, string new_author, int new_year)
        : Book(new_title, new_author, new_year) {}
    ~Genre() {
        cout << "Destructor of Genre " << endl;
    }
};
class DetectiveGenre : public Genre {
public:
    DetectiveGenre(string new_title = "Dumb Witness", string new_author = "Agatha Christie", int new_year = 1937)
        : Genre(new_title, new_author, new_year) {}

    DetectiveGenre(const DetectiveGenre& other) : Genre(other) {
        cout << "DetectiveGenre Copy Constructor" << endl;
    }
    DetectiveGenre(DetectiveGenre&& other) noexcept : Genre(move(other)) {
        cout << "DetectiveGenre Move Constructor" << endl;
    }
    DetectiveGenre& operator=(const DetectiveGenre& other) {
        if (this == &other) return *this;
        title = other.title;  
        author = other.author;
        year = other.year;
        cout << "DetectiveGenre Copy Assignment" << endl;
        return *this;
    }

    ~DetectiveGenre() {
        cout << "Destructor of Detective Book " << endl;
    }
    void display() const {
        Book::display();  
    }
};
class ScienceGenre : public Genre {
public:
    ScienceGenre(string new_title, string new_author, int new_year)
        : Genre(new_title, new_author, new_year) {
    }
    ~ScienceGenre() {
        cout << "Destructor of Science Book " << endl;
    }
    void display() const {
        Book::display();
    }
};
class Reader {
private:
    string name;
    int age;

public:
    Reader() : name{ "Natalia" }, age{ 19 } {
    }
    Reader(string new_name, int new_age)
        : name{ new_name }, age{ new_age } {
    }
    Reader(string new_name) : Reader(new_name, 19) {
    }
    ~Reader() {
    }

    void display() const {
        cout << "Reader: " << name << ", Age: " << age << endl;
    }
};
class Library {
private:
    string name;
    int book_amount;

public:
    Library(string new_name, int new_book_amount)
        : name{ new_name }, book_amount{ new_book_amount } {
    }
    ~Library() {
        cout << "Destructor of Library" << endl;
    }
    void display() const {
        cout << "Library: " << name << ", Amount of books: " << book_amount << ", " ;
    }
};
class UkranianLibrary : public Library {
private:
    string popular_genre;
public:
    UkranianLibrary(string new_name = "KSD", int new_book_amount = 66, string new_popular_genre = "Fantasy, Detective, Military literature" ) :
        Library(new_name, new_book_amount), popular_genre{ new_popular_genre }{
    }
    ~UkranianLibrary() {
        cout << "Destructor of UkranianLibrary " << endl;
    }
    void display() const {
        Library::display();
        cout << "Popular genre in Ukraine: " << popular_genre << endl;
    }

};
class ForeignLibrary : public Library {
private:
    string location;
public:
    ForeignLibrary(string new_name = "Carusel Readers", int new_book_amount = 157, string new_location = " the Old Town of Bucharest, Romania") :
        Library(new_name, new_book_amount), location{ new_location } {
    }
    ~ForeignLibrary() {
        cout << "Destructor of ForeignLibrary " << endl;
    }
    void display() const {
        Library::display();
        cout << "Location: " << location << endl;
    }

};

int main() {
    DetectiveGenre b1;
    ScienceGenre b2("The Midnight Library", "Matt Haig", 2021);
    Reader h;
    Reader h1("Oksana", 20);
    Reader h2("Anna");
    UkranianLibrary l1;
    ForeignLibrary l2;

    DetectiveGenre b3 = b1; 
    DetectiveGenre b4 = move(b1);  
    b3 = b1;
     
    b1.display();
    b2.display();
    b3.display();
    b4.display();
    h.display();
    h1.display();
    h2.display();
    l1.display();
    l2.display();

    return 0;
}