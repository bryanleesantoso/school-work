#include <iostream>
#include <iomanip>
using namespace std;

const int N = 10;

struct Date {
    int day;
    int month;
    int year;
};

struct Book {
    int id;
    double price;
    Date date;
};

struct Library {
    Book books[N];
    int num;
};

void listOptions() {
    cout << "~~~~~~~~~Welcome!~~~~~~~~~~" << endl;
    cout << "0: Exit" << endl;
    cout << "1: Add" << endl;
    cout << "2: Show" << endl;
    cout << "3: Delete" << endl;
    cout << "4: Sort" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

void add(Library& lib) {
    if (lib.num >= N) {
        cout << "Library is full." << endl;
        return;
    }

    cout << "Input Book ID: " << endl;
    cin >> lib.books[lib.num].id;
    cout << "Input Price: " << endl;
    cin >> lib.books[lib.num].price;
    cout << "Input Date (dd mm yyyy): " << endl; 
    cin >> lib.books[lib.num].date.day >> lib.books[lib.num].date.month >> lib.books[lib.num].date.year;

    lib.num++;
}

void show(Library& lib) {
    for (int i = 0; i < lib.num; i++) {
        cout << setfill('0') << setw(3) << lib.books[i].id << "     ";
        cout << fixed << setprecision(2) << lib.books[i].price << "   ";
        cout << lib.books[i].date.day << "-" << lib.books[i].date.month << "-" << lib.books[i].date.year << endl;
    }
}

void del(Library& lib) {
    if (lib.num == 0) {
        cout << "Library is empty. No books to delete." << endl;
        return;
    }
    
    int bookId;
    cout << "Enter the ID to be deleted ";
    cout << endl;
    cin >> bookId;

    int index = -1;
    for (int i = 0; i < lib.num; i++) {
        if (lib.books[i].id == bookId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "The ID cannot be found"<< endl;
    } else {
        for (int i = index; i < lib.num - 1; i++) {
            lib.books[i] = lib.books[i + 1];
        }
        lib.num--;
    }
}

void sort_id(Library& lib) {
    for (int i = 0; i < lib.num - 1; i++) {
        for (int j = i + 1; j < lib.num; j++) {
            if (lib.books[i].id > lib.books[j].id) {
                Book temp = lib.books[i];
                lib.books[i] = lib.books[j];
                lib.books[j] = temp;
            }
        }
    }
}


void sort_date(Library& lib) {
    for (int i = 0; i < lib.num - 1; i++) {
        for (int j = i + 1; j < lib.num; j++) {
            if (lib.books[i].date.year > lib.books[j].date.year ||
                (lib.books[i].date.year == lib.books[j].date.year &&
                 lib.books[i].date.month > lib.books[j].date.month) ||
                (lib.books[i].date.year == lib.books[j].date.year &&
                 lib.books[i].date.month == lib.books[j].date.month &&
                 lib.books[i].date.day > lib.books[j].date.day) ||
                (lib.books[i].date.year == lib.books[j].date.year &&
                 lib.books[i].date.month == lib.books[j].date.month &&
                 lib.books[i].date.day == lib.books[j].date.day &&
                 lib.books[i].id > lib.books[j].id)) {
                Book temp = lib.books[i];
                lib.books[i] = lib.books[j];
                lib.books[j] = temp;
            }
        }
    }
}

void sort(Library& lib) {
    int n;
    cout << "1: Sort by ID" << endl;
    cout << "2: Sort by Date" << endl;
    cin >> n;
    switch (n) {
        case 1:
            sort_id(lib);
            break;
        case 2:
            sort_date(lib);
            break;
    }

}

void init(Library *p) {
    p->books[p->num].id = 3;
    p->books[p->num].price = 10.5;
    p->books[p->num].date.day = 15;
    p->books[p->num].date.month = 1;
    p->books[p->num].date.year = 1990;
    ++(p->num);

    p->books[p->num].id = 2;
    p->books[p->num].price = 20.55;
    p->books[p->num].date.day = 15;
    p->books[p->num].date.month = 2;
    p->books[p->num].date.year = 2024;
    ++(p->num);

    p->books[p->num].id = 4;
    p->books[p->num].price = 10.5;
    p->books[p->num].date.day = 20;
    p->books[p->num].date.month = 2;
    p->books[p->num].date.year = 2021;
    ++(p->num);

    p->books[p->num].id = 1;
    p->books[p->num].price = 30.1;
    p->books[p->num].date.day = 20;
    p->books[p->num].date.month = 2;
    p->books[p->num].date.year = 2021;
    ++(p->num);
}


int main() {
    Library lib;
    lib.num = 0;

    init(&lib);
    
    int opt;

    do {
        listOptions();
        cin >> opt;

        switch (opt) {
            case 0:
                cout << "Bye!" << endl;
                break;
            case 1:
                add(lib);
                break;
            case 2:
                show(lib);
                break;
            case 3:
                del(lib);
                break;
            case 4:
                sort(lib);
                break;
        }

        cout << endl;
    } while (opt != 0);

    return 0;
}
