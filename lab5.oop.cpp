#include <iostream>
#include <string>

using namespace std;

class Book {
protected:
    string title;
    string author;
    int year;

public:
    Book()
        : title{ "Dumb Witness" }, author{ "Agatha Christie" }, year{ 1937 } {
    }
    virtual ~Book() {}

    virtual void display() const {
        cout << "Book: " << title << ", Author: " << author << ", Year: " << year << " - It`s a printed book" << endl;
    }
};
class EBook : public Book {
private:
    string format;
public:
    EBook(const string& new_format)
        : Book(), format{ new_format } {}

    virtual ~EBook() {}

    void display() const override {
        cout << "Book: " << title << ", Author: " << author << ", Format: " << format <<  endl;
    }
};
class Reader {
private:
    string name;
    int age;
    bool isMember;
public:
    Reader() : name{ "Natalia" }, age{ 19 }, isMember{ false } {
    }
    Reader(string new_name, int new_age, bool isMember)
        : name{ new_name }, age{ new_age }, isMember{ false } {
    }
    virtual void display() const {
        cout << "Reader: " << name << ", Age: " << age << endl;
    }
    virtual string getStatus() const {
        return isMember ? "Member of the club" : "Not a member of the club";
    }
};
class Library {
public:
    virtual ~Library() {}

    virtual void display() const = 0;             
    virtual void displayPublishingType() const = 0;
};
class UkLibrary : public Library {
private:
    string name;
    int book_amount;
public:
    UkLibrary(string new_name, int new_book_amount)
        : name{ new_name }, book_amount{ new_book_amount } {}

    virtual ~UkLibrary() {}

    void display() const override {
        cout << "Library: " << name << ", Amount of books: " << book_amount << endl;
    } 
    void displayPublishingType() const override final {
        cout << "Publishing type: Ukrainian library." << endl;
    }
};
class IntLibrary : public Library {
private:
    string name;
    int book_amount;
public:
    IntLibrary(string new_name, int new_book_amount)
        : name{ new_name }, book_amount{ new_book_amount } {}

    virtual ~IntLibrary() {}

    void display() const override {
        cout << "Library: " << name << ", Amount of books: " << book_amount << endl;
    }
    void displayPublishingType() const override final {
        cout << "Publishing type: International library." << endl;
    }
};

int main() {
    Book b;
    Reader h;
    Reader h1("Oksana", 20, true);

    b.display();
    Book* ptr = new EBook("Electronic");
    ptr->display();

    cout << endl;
    h.display();
    cout << h.getStatus() << endl;
    h1.display();
    cout << h1.getStatus() << endl;
    Reader* ptr1 = new Reader("Olga", 22, true);
    ptr1->display();
    cout << ptr1->getStatus() << endl;

    cout << endl;
    UkLibrary intUk("Vivat", 62);
    Library& ref1 = intUk;
    ref1.display();
    ref1.displayPublishingType();

    IntLibrary intLib("Cambridge International Publishing", 154);
    Library& ref2 = intLib;
    ref2.display();                
    ref2.displayPublishingType();


    delete ptr;
    delete ptr1;
    return 0;
}