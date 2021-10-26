#ifndef Record_H
#define Record_H

#include <iostream>
#include <string>

using namespace std;
class Record {
private:
    //member variables
    std::string title;
    std::string author;
    std::string ISBN;
    std::string year;
    std::string edition;
public:
    //accessor/mutator functions
    string get_title(void) const{return title;}
    string get_author(void) const{return author;}
    string get_ISBN(void) const{return ISBN;}
    string get_year(void) const{return year;}
    string get_edition(void) const{return edition;}

    void set_title(string in) {title = in;}
    void set_author(string in) {author = in;}
    void set_ISBN(string in) {ISBN = in;}
    void set_year(string in) {year = in;}
    void set_edition(string in) {edition = in;}
    friend std::istream& operator>>(std::istream& is, Record& rec);
    // ... for all 5 fields
};

// Stream operators

std::ostream& operator<<(std::ostream& os, const Record& rec);

// Comparison operators
bool operator==(const Record& r1, const Record& r2);
bool operator<(const Record& lhs, const Record& rhs);
#endif