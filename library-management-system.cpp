
#include <iostream>  // For input and output operations
#include <cctype>    // For character handling functions like toupper and isalnum
#include <string>    // For string manipulation
#include <iomanip>   // For formatted output (e.g., setw)
#include <conio.h>   // For _getch() to wait for key press

using namespace std;

// Function to convert a string to uppercase for case-insensitive comparison
string toUpperCase(string str) {
    string result = str;
    for (size_t i = 0; i < result.length(); i++) {
        result[i] = toupper(result[i]);
    }
    return result;
}

// Function to check if a string is alphanumeric
bool isAlphanumeric(const string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (!isalnum(str[i])) {
            return false;
        }
    }
    return true;
}

// Function to check if a string is a valid menu option
bool isValidMenuOption(const string& input, int& output, int min, int max) {
    // Check if all characters are digits
    if (input.empty() || input.find(' ') != string::npos) {
        return false;
    }
    
    // Check if the string contains only digits
    for (char c : input) {
        if (!isdigit(c)) return false;
    }

    // Convert string to integer
    try {
        output = stoi(input);
        return output >= min && output <= max;
    } catch (...) {
        return false; // Handles out-of-range errors
    }
}

// Function to wait for a key press before continuing
void waitForKeyPress() {
    cout << "Press any key to continue...";
    _getch(); // Waits for any key press
}

// Base class for Book (Abstraction)
class Book {
private:
    string id;
    string isbn;
    string title;
    string author;
    string edition;
    string publication;
    string category;
    
public:
    // Constructor
    Book() {}
    
    // Constructor with parameters
    Book(const string& bookId, const string& bookIsbn, const string& bookTitle, 
         const string& bookAuthor, const string& bookEdition, 
         const string& bookPublication, const string& bookCategory) {
        id = bookId;
        isbn = bookIsbn;
        title = bookTitle;
        author = bookAuthor;
        edition = bookEdition;
        publication = bookPublication;
        category = bookCategory;
    }
    
    // Getter methods (Encapsulation)
    string getId() const {
        return id;
    }
    
    string getIsbn() const {
        return isbn;
    }
    
    string getTitle() const {
        return title;
    }
    
    string getAuthor() const {
        return author;
    }
    
    string getEdition() const {
        return edition;
    }
    
    string getPublication() const {
        return publication;
    }
    
    string getCategory() const {
        return category;
    }
    
    // Setter methods (Encapsulation)
    // Set ID with alphanumeric validation
    bool setId(const string& bookId) {
        if (!isAlphanumeric(bookId)) {
            return false;
        }
        id = bookId;
        return true;
    }
    
    void setIsbn(const string& bookIsbn) {
        isbn = bookIsbn;
    }
    
    void setTitle(const string& bookTitle) {
        title = bookTitle;
    }
    
    void setAuthor(const string& bookAuthor) {
        author = bookAuthor;
    }
    
    void setEdition(const string& bookEdition) {
        edition = bookEdition;
    }
    
    void setPublication(const string& bookPublication) {
        publication = bookPublication;
    }
    
    void setCategory(const string& bookCategory) {
        category = bookCategory;
    }
    
    // Display book details
    void displayDetails() const {
        cout << "ID: " << id << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Edition: " << edition << endl;
        cout << "Publication: " << publication << endl;
        cout << "Category: " << category << endl;
    }
};

// Library Management System class
class LibrarySystem {
private:
    Book books[10];
    int bookCount;
    
    // Helper function to check if an ID already exists
    bool isIdUnique(const string& id) const {
        string upperId = toUpperCase(id);
        
        for (int i = 0; i < bookCount; i++) {
            string currentId = toUpperCase(books[i].getId());
            
            if (currentId == upperId) {
                return false;
            }
        }
        return true;
    }
    
    // Helper function to find a book by ID
    int findBookById(const string& id) const {
        string upperId = toUpperCase(id);
        
        for (int i = 0; i < bookCount; i++) {
            string currentId = toUpperCase(books[i].getId());
            
            if (currentId == upperId) {
                return i;
            }
        }
        return -1;
    }
    
    // Helper function to find books by category
    bool categoryExists(const string& category) const {
        string upperCategory = toUpperCase(category); // Convert input to uppercase
        for (int i = 0; i < bookCount; i++) {
            if (books[i].getCategory() == category) {
                return true;
            }
        }
        return false;
    }
    
    // Helper function to get validated input
    string getInput(const string& prompt, bool allowEmpty = false) {
        string output;
        bool validInput = false;
        
        while (!validInput) {
            cout << prompt;
            getline(cin, output);
            
            if (allowEmpty || !output.empty()) {
                validInput = true;
            } else {
                cout << "Input cannot be empty. Please try again." << endl;
            }
        }
        return output;
    }
    
    // Helper function to get book ID with validation
    string getBookId() {
        string id;
        bool validInput = false;
        
        while (!validInput) {
            id = getInput("Enter Book ID (alphanumeric): ");
            
            if (!isAlphanumeric(id)) {
                cout << "Invalid ID format! ID must contain only alphanumeric characters." << endl;
            } else if (!isIdUnique(id)) {
                cout << "Duplicate ID! Please enter a unique ID." << endl;
            } else {
                validInput = true;
            }
        }
        return id;
    }
    
    // Helper function to get category (Fiction or Non-fiction)
    string getCategory() {
        string category;
        bool validInput = false;
        
        while (!validInput) {
            category = getInput("Enter Category (Fiction or Non-fiction): ");
            category = toUpperCase(category); // Convert input to uppercase

            if (category == "FICTION" || category == "NON-FICTION") {
                validInput = true;
            } else {
                cout << "Invalid category. Please enter either fiction or 'non-fiction." << endl;
            }
        }
        return category;
    }
    
public:
    // Constructor
    LibrarySystem() : bookCount(0) {}
    
    // Function to add a book
    void addBook() {
        if (bookCount >= 10) {
            cout << "Library is full. Cannot add more books." << endl;
            return;
        }
        
        Book newBook;
        
        // Get category first
        string category = getCategory();
        newBook.setCategory(category);
        
        // Get the rest of the book details
        string id = getBookId();
        newBook.setId(id);
        
        string isbn = getInput("Enter ISBN: ");
        newBook.setIsbn(isbn);
        
        string title = getInput("Enter Title: ");
        newBook.setTitle(title);
        
        string author = getInput("Enter Author: ");
        newBook.setAuthor(author);
        
        string edition = getInput("Enter Edition: ");
        newBook.setEdition(edition);
        
        string publication = getInput("Enter Publication: ");
        newBook.setPublication(publication);
        
        // Add book to array
        books[bookCount++] = newBook;
        cout << "Book added successfully!" << endl;
        waitForKeyPress();
    }
    
    // Function to edit a book
    void editBook() {
        string id = getInput("Enter Book ID to edit: ");
        
        int index = findBookById(id);
        
        if (index == -1) {
            cout << "Book not found!" << endl;
            waitForKeyPress();
            return;
        }
        
        cout << "Book found. Please enter new details (except ID):" << endl;
        
        string isbn = getInput("Enter ISBN: ");
        books[index].setIsbn(isbn);
        
        string title = getInput("Enter Title: ");
        books[index].setTitle(title);
        
        string author = getInput("Enter Author: ");
        books[index].setAuthor(author);
        
        string edition = getInput("Enter Edition: ");
        books[index].setEdition(edition);
        
        string publication = getInput("Enter Publication: ");
        books[index].setPublication(publication);
        
        string category = getCategory();
        books[index].setCategory(category);
        
        cout << "Book edited successfully!" << endl;
        waitForKeyPress();
    }
    
    // Function to search for a book
    void searchBook() {
        string id = getInput("Enter Book ID to search: ");
        
        int index = findBookById(id);
        
        if (index == -1) {
            cout << "Book not found!" << endl;
            waitForKeyPress();
            return;
        }
        
        cout << "Book found:" << endl;
        books[index].displayDetails();
        waitForKeyPress();
    }
    
    // Function to delete a book
    void deleteBook() {
        string id = getInput("Enter Book ID to delete: ");
        
        int index = findBookById(id);
        
        if (index == -1) {
            cout << "Book not found!" << endl;
            waitForKeyPress();
            return;
        }
        
        cout << "Book found. Details:" << endl;
        books[index].displayDetails();
        
        string response = getInput("Do you want to delete this book? (y/n): ");
        
        if (response[0] == 'y' || response[0] == 'Y') {
            // Shift all books after this index to fill the gap
            for (int i = index; i < bookCount - 1; i++) {
                books[i] = books[i + 1];
            }
            bookCount--;
            cout << "Book Deleted successfully!" << endl;
        } else {
            cout << "Deletion cancelled." << endl;
        }
        
        waitForKeyPress();
    }
    
    // Function to view books by category
    void viewBooksByCategory() {
        string category = getInput("Enter Category to view (Fiction or Non-fiction): ");
        category = toUpperCase(category); // Convert input to uppercase for case-insensitive comparison
        
        if (!categoryExists(category)) {
            cout << "Category not found!" << endl;
            waitForKeyPress();
            return;
        }
        
        // Display header
        cout << "\n----- Books in Category: " << category << " -----" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(10) << "ID"
            << setw(20) << "ISBN"
            << setw(30) << "Title"
            << setw(20) << "Author"
            << setw(10) << "Edition"
            << setw(20) << "Publication" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------" << endl;

        // Display each book's details
        for (int i = 0; i < bookCount; i++) {
            if (toUpperCase(books[i].getCategory()) == category) { // Case-insensitive comparison
                cout << left << setw(10) << books[i].getId()
                    << setw(20) << books[i].getIsbn()
                    << setw(30) << books[i].getTitle()
                    << setw(20) << books[i].getAuthor()
                    << setw(10) << books[i].getEdition()
                    << setw(20) << books[i].getPublication() << endl;
            }
        }
        
        waitForKeyPress();
    }
    
    // Function to view all books
    void viewAllBooks() {
        if (bookCount == 0) {
            cout << "No books to display." << endl;
            waitForKeyPress();
            return;
        }
        
        // Display header
        cout << "\n----- All Books in Library -----" << endl;
        cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(10) << "ID"
            << setw(20) << "ISBN"
            << setw(30) << "Title"
            << setw(20) << "Author"
            << setw(10) << "Edition"
            << setw(20) << "Publication"
            << setw(15) << "Category" << endl;
        cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
        // Display each book's details
        for (int i = 0; i < bookCount; i++) {
            cout << left << setw(10) << books[i].getId()
                << setw(20) << books[i].getIsbn()
                << setw(30) << books[i].getTitle()
                << setw(20) << books[i].getAuthor()
                << setw(10) << books[i].getEdition()
                << setw(20) << books[i].getPublication()
                << setw(15) << books[i].getCategory() << endl;
        }    

        waitForKeyPress();
    }
};

// Main function to run the library management system
int main() {
    LibrarySystem librarySystem;
    string choice;
    
    do {
        // Display main menu
        cout << "\n================================\n";
        cout << "    LIBRARY MANAGEMENT SYSTEM    \n";
        cout << "================================\n";
        cout << "[1] Add Book\n";
        cout << "[2] Edit Book\n";
        cout << "[3] Search Book\n";
        cout << "[4] Delete Book\n";
        cout << "[5] View Books by Category\n";
        cout << "[6] View All Books\n";
        cout << "[7] Exit\n";
        cout << "================================\n";
        cout << "Enter your choice: ";
        getline(cin, choice);
        
        // Validate menu option
        int option;
        if (isValidMenuOption(choice, option, 1, 7)) {
            switch (option) {
                case 1:
                    librarySystem.addBook();
                    break;
                case 2:
                    librarySystem.editBook();
                    break;
                case 3:
                    librarySystem.searchBook();
                    break;
                case 4:
                    librarySystem.deleteBook();
                    break;
                case 5:
                    librarySystem.viewBooksByCategory();
                    break;
                case 6:
                    librarySystem.viewAllBooks();
                    break;
                case 7:
                    cout << "Exiting program. Goodbye!" << endl;
                    break;
            }
        } else {
            cout << "Invalid choice. Please enter a number between 1 and 7." << endl;
        }
    } while (choice != "7");

    return 0;
}