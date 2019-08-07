
/*#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"
using namespace std;

// Iterates though all people in the AddressBook and prints info about them.
void ListPeople(const AddressBook& address_book) {
  for (int i = 0; i < address_book.people_size(); i++) {
    const Person& person = address_book.people(i);

    cout << "Person ID: " << person.id() << endl;
    cout << "  Name: " << person.name() << endl;
    if (person.has_email()) {
      cout << "  E-mail address: " << person.email() << endl;
    }

    for (int j = 0; j < person.phones_size(); j++) {
      const Person::PhoneNumber& phone_number = person.phones(j);

      switch (phone_number.type()) {
        case Person::MOBILE:
          cout << "  Mobile phone #: ";
          break;
        case Person::HOME:
          cout << "  Home phone #: ";
          break;
        case Person::WORK:
          cout << "  Work phone #: ";
          break;
      }
      cout << phone_number.number() << endl;
    }
  }
}

// Main function:  Reads the entire address book from a file and prints all
//   the information inside.
int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

//  if (argc != 2) {
//    cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
//    return -1;
//  }

  AddressBook address_book;

  {
      std::string file_str = "./dress.xml";
    // Read the existing address book.
//    fstream input(file_str, ios::in | ios::binary);
      fstream input(file_str, ios::in );
    if (!address_book.ParseFromIstream(&input)) {
      cerr << "Failed to parse address book." << endl;
      return -1;
    }
  }

  ListPeople(address_book);

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}*/
#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"
using namespace std;
using namespace google::protobuf;
// This function fills in a Person message based on user input.
void PromptForAddress(Person* person) {
  cout << "Enter person ID number: ";
  int id;
  cin >> id;
  person->set_id(id);
  cin.ignore(256, '\n');

  cout << "Enter name: ";
  getline(cin, *person->mutable_name());

  cout << "Enter email address (blank for none): ";
  string email;
  getline(cin, email);
  if (!email.empty()) {
    person->set_email(email);
  }

  while (true) {
    cout << "Enter a phone number (or leave blank to finish): ";
    string number;
    getline(cin, number);
    if (number.empty()) {
      break;
    }

    /*Person::PhoneNumber* phone_number = person->add_phones();
    phone_number->set_number(number);

    cout << "Is this a mobile, home, or work phone? ";
    string type;
    getline(cin, type);
    if (type == "mobile") {
      phone_number->set_type(Person::MOBILE);
    } else if (type == "home") {
      phone_number->set_type(Person::HOME);
    } else if (type == "work") {
      phone_number->set_type(Person::WORK);
    } else {
      cout << "Unknown phone type.  Using default." << endl;
    }*/
  }
}

// Main function:  Reads the entire address book from a file,
//   adds one person based on user input, then writes it back out to the same
//   file.
#include <sstream>
int main(int argc, char* argv[]) {

    AddressBook bk;


    std::string data;

    Person* n_ps = bk.add_people();
    n_ps->set_name( "hmm2" );
    n_ps->set_email( "newaddssss2");
    n_ps->set_id( 1 );
    Person* n_ps2 = bk.add_people();
    n_ps2->set_name( "hmm3" );
    n_ps2->set_email( "newaddssss3");
    n_ps2->set_id( 2 );

    bk.SerializeToString( &data );
    std::string file_str = "./dress3.xml";
    fstream output(file_str, ios::out /*| ios::trunc | ios::binary*/);
    output<<data;
    output.close();/*
    if (!bk.SerializeToOstream(&output)) {
      cerr << "Failed to write address book." << endl;
      return -1;
    }
    for( int i = 0; i < bk.people_size() ; i++ ){
        const Person& ps = bk.people( i );
        cout<<"person id : "<<ps.id()<<endl;
        cout<<"name: "<<ps.name()<<endl;
        cout<<"email:"<<ps.email()<<endl;
    }*/
    /*std::string file_str = "./dress2.xml";
    AddressBook bk;

    fstream input(file_str, ios::in );
    if (!input) {
      cout << file_str << ": File not found.  Creating a new file." << endl;
    } else if (!bk.ParseFromIstream(&input)) {
      cerr << "Failed to parse address book." << endl;
      return -1;
    }else{
        for( int i = 0; i < bk.people_size() ; i++ ){
            const Person& ps = bk.people( i );
            cout<<"person id : "<<ps.id()<<endl;
            cout<<"name: "<<ps.name()<<endl;
            cout<<"email:"<<ps.email()<<endl;
        }
    }*/

//    for (int i = 0; i < address_book.people_size(); i++) {
//      const Person& person = address_book.people(i);

//      cout << "Person ID: " << person.id() << endl;
//      cout << "  Name: " << person.name() << endl;
//      if (person.has_email()) {
//        cout << "  E-mail address: " << person.email() << endl;
//      }
    /*Person ps;
    ps.set_id( 1 );
    ps.set_name( "hmm" );
    ps.set_email( "addsssss");
    std::string data;
    if( ps.IsInitialized() ){
        ps.SerializeToString(&data);
        std::string file_str = "./dress.xml";
        fstream output(file_str, ios::out | ios::trunc | ios::binary);
        if (!ps.SerializeToOstream(&output)) {
          cerr << "Failed to write address book." << endl;
          return -1;
        }


         Person ps3;
         ps3.ParseFromString( data );
         output.close();
    }
    {
        Person ps2;
        std::string file_str = "dress.xml";
        fstream input(file_str, ios::in | ios::binary);
        if (!input) {
          cout << file_str << ": File not found.  Creating a new file." << endl;
        } else if (!ps2.ParseFromIstream(&input)) {
          cerr << "Failed to parse address book." << endl;
          return -1;
        }else{
            cout <<" ParseFromIstream right"
                <<"[name]:"<<ps2.name()
               <<"[email]:"<<ps2.email()
              <<"[id]:"<<ps2.id();
        }
    }*/

    cout << "exe end";
}
