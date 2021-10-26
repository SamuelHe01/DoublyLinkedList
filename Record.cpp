//implementation of record class

#include "Record.h"
#include <string>
using namespace std;
std::istream& operator>>(std::istream& is, Record& rec){
    string tmp;
	getline(is,tmp, '\n'); rec.set_title(tmp);
	getline(is,tmp, '\n'); rec.set_author(tmp);
	getline(is,tmp, '\n'); rec.set_ISBN(tmp);
	getline(is,tmp, '\n'); rec.set_year(tmp);
	getline(is,tmp, '\n'); rec.set_edition(tmp);
    return is;
}
std::ostream& operator<<(std::ostream& os, const Record& rec){
    os <<   rec.get_title() << endl <<
            rec.get_author() << endl << 
            rec.get_ISBN() << endl <<
            rec.get_year() << endl << 
            rec.get_edition() << endl;
    return os;
}
bool operator==(const Record& r1, const Record& r2){
    return  (r1.get_title() == r2.get_title()) && 
            (r1.get_author() == r2.get_author()) && 
            (r1.get_ISBN() == r2.get_ISBN());
}
bool operator<(const Record& lhs, const Record& rhs){
    return false;
}