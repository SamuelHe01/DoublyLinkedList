#ifndef LIBRARY_H
#define LIBRARY_H

#include "Record.h"
#include "TemplatedDLList.h"
#include <cctype>
#include <vector>
#include <fstream>

class Library {
    private:
        std::vector<TemplatedDLList<Record>> book_db = std::vector<TemplatedDLList<Record>>(26);
    public:
        //Searches for a title in the database and returns vector of matching records
        std::vector<Record> search(const std::string title) const;

        //Imports records from a file.  Does not import duplicates.
        // Return the number of records added to the database
        int import_database(const std::string filename);

        //Exports the current database to a file
        //Return the number of records exported
        int export_database(const std::string filename) const;

        void print_database() const;

        //add record to database, avoid complete duplicates
        //  return true if unique
        bool add_record(const Record r);

        //Deletes a record from the database
        void remove_record(const Record r);

        // The following functions are tentative, pending a redo of Part 2
        // Please do not implmenet them until we provide more details.

        //Prompts user for yes or no and returns choice Y or N
        char prompt_yes_no();

        //Given a vector of menu options returns index of choice
        int prompt_menu(std::vector<std::string>);

        //Prompts user for a new record
        Record prompt_record();

        //Prompt for a valid title
        std::string prompt_title();

        // Prompt for a valid string
        std::string prompt_string(std::string prompt);
};

#endif