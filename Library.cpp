#include "Library.h"
//add record to database, avoid complete duplicates
//  return true if unique
using namespace std;
bool Library::add_record(const Record r){
    char firstChar = r.get_title()[0];
    int index = firstChar - 'A';
    const auto *node = book_db[index].first_node();
    while(node = node->next){
        if(node->obj == r && node->obj.get_edition() == r.get_edition()){
            return false;
        }
    }
    book_db[index].insert_last(r);
    return true;
}

void Library::print_database() const{
    for(int i = 0; i < 26; i++){
        const auto *node = book_db[i].first_node();
        while(node != book_db[i].after_last_node()){
            cout << node->obj << endl;
            node = node->next;
        }
    }
}

//Deletes a record from the database
void Library::remove_record(const Record r){
    int index = r.get_title()[0] - 'A';
    auto *node = book_db[index].first_node();
    while(node != book_db[index].after_last_node()->next){
        if(node->obj == r){
            book_db[index].remove_after(*node->prev);
        }
        node = node->next;
    }
}

int Library::export_database(const string filename) const{
    ofstream outputFS(filename);
    int numRecords = 0;
    for(int i = 0; i < 26; i++){
        auto* node = book_db[i].first_node();
        while(node != book_db[i].after_last_node()){
            outputFS << node->obj;
            numRecords++;
            node = node->next;
        }
    }
    outputFS.close();
    return numRecords;
}

int Library::import_database(const string filename){
    int numRecords = 0;
    ifstream inputFS(filename);//open file
    string tmp;//tmp record variable
    Record temp;
    while(!inputFS.eof()){
        getline(inputFS,tmp, '\n');
        if(!tmp.empty()){
            temp.set_title(tmp);
            getline(inputFS,tmp, '\n');
            temp.set_author(tmp);
            getline(inputFS,tmp, '\n');
            temp.set_ISBN(tmp);
            getline(inputFS,tmp, '\n');
            temp.set_year(tmp);
            getline(inputFS,tmp, '\n');
            temp.set_edition(tmp);
            char firstChar = temp.get_title()[0];
            int index = firstChar - 'A';
            const auto *node = book_db[index].first_node();
            book_db[index].insert_last(temp);
            numRecords++;
        }
    }
    inputFS.close();
    return numRecords;
}
vector<Record> Library::search(const std::string title) const{
    vector<Record> result;
    int index = title[0] - 'A';
    if(index < 0 || index > 25){
        return result;
    }
    else if(book_db[index].is_empty()){
        return result;
    }
    else{
        auto* node = book_db.at(index).first_node();
        while(node != book_db[index].after_last_node()){
            if(title == node ->obj.get_title())
                result.push_back(node->obj);
            node = node->next;
        }
    }
    return result;
}