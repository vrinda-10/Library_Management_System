#include <iostream>
#include <vector>
using namespace std;

struct Book {
    string title;
    string author;
    string isbn;
    bool isAvailable = true;
    int dueDays = 0;
};

vector<Book> library;

// Add some books initially
void loadBooks() {
    library.push_back({"C++ Programming", "Bjarne Stroustrup", "1111"});
    library.push_back({"Clean Code", "Robert C. Martin", "2222"});
    library.push_back({"Data Structures", "Mark Allen", "3333"});
}

// Display all books
void showBooks() {
    cout << "\nBook List:\n";
    for (int i = 0; i < library.size(); i++) {
        cout << i + 1 << ". " << library[i].title << " | "
             << library[i].author << " | ISBN: " << library[i].isbn
             << " | " << (library[i].isAvailable ? "Available" : "Checked Out") << "\n";
    }
}

// Search for a book
void searchBook() {
    cin.ignore();
    string key;
    cout << "Enter title, author, or ISBN to search: ";
    getline(cin, key);

    bool found = false;
    for (Book b : library) {
        if (b.title.find(key) != string::npos ||
            b.author.find(key) != string::npos ||
            b.isbn.find(key) != string::npos) {
            cout << "Found: " << b.title << " | " << b.author << " | ISBN: " << b.isbn;
            cout << " | " << (b.isAvailable ? "Available" : "Checked Out") << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No book found.\n";
    }
}

// Checkout book
void checkoutBook() {
    showBooks();
    int choice;
    cout << "Enter book number to checkout: ";
    cin >> choice;

    if (choice < 1 || choice > library.size()) {
        cout << "Invalid selection.\n";
        return;
    }

    Book &b = library[choice - 1];

    if (!b.isAvailable) {
        cout << "Book is already checked out.\n";
        return;
    }

    cout << "Enter number of days to return the book: ";
    cin >> b.dueDays;
    b.isAvailable = false;
    cout << "Book checked out successfully.\n";
}

// Return book
void returnBook() {
    showBooks();
    int choice;
    cout << "Enter book number to return: ";
    cin >> choice;

    if (choice < 1 || choice > library.size()) {
        cout << "Invalid selection.\n";
        return;
    }

    Book &b = library[choice - 1];

    if (b.isAvailable) {
        cout << "Book is not checked out.\n";
        return;
    }

    int actualDays;
    cout << "Enter actual number of days you kept the book: ";
    cin >> actualDays;

    if (actualDays > b.dueDays) {
        int fine = (actualDays - b.dueDays) * 5;
        cout << "You returned the book late. Fine: Rs. " << fine << "\n";
    } else {
        cout << "Book returned on time. No fine.\n";
    }

    b.isAvailable = true;
    b.dueDays = 0;
    cout << "Book returned successfully.\n";
}

// Menu
void showMenu() {
    cout << "\nLibrary Management System\n";
    cout << "1. View All Books\n";
    cout << "2. Search Book\n";
    cout << "3. Checkout Book\n";
    cout << "4. Return Book\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    loadBooks();
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                showBooks();
                break;
            case 2:
                searchBook();
                break;
            case 3:
                checkoutBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                cout << "Thank you for using the library system.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
