
/*#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"
using namespace std;

// Iterates though all people in the AddressBook and prints info about them.
void ListPeople(const tutorial::AddressBook& address_book) {
  for (int i = 0; i < address_book.people_size(); i++) {
    const tutorial::Person& person = address_book.people(i);

    cout << "Person ID: " << person.id() << endl;
    cout << "  Name: " << person.name() << endl;
    if (person.has_email()) {
      cout << "  E-mail address: " << person.email() << endl;
    }

    for (int j = 0; j < person.phones_size(); j++) {
      const tutorial::Person::PhoneNumber& phone_number = person.phones(j);

      switch (phone_number.type()) {
        case tutorial::Person::MOBILE:
          cout << "  Mobile phone #: ";
          break;
        case tutorial::Person::HOME:
          cout << "  Home phone #: ";
          break;
        case tutorial::Person::WORK:
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

  tutorial::AddressBook address_book;

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
#include <assert.h>
#include "foo.pb.h"
using namespace std;
using namespace google::protobuf;


// Main function:  Reads the entire address book from a file,
//   adds one person based on user input, then writes it back out to the same
//   file.
#include <sstream>
int main(int argc, char* argv[]) {

    string data;  // Will store a serialized version of the message.
    int i = 0;
    i++;

    {
      // Create a message and serialize it.
      Foo foo;
      foo.set_text("Hello World!");
      foo.add_numbers(1);
      foo.add_numbers(5);
      foo.add_numbers(42);

      foo.SerializeToString(&data);
      std::string file_str = "./dress.xml";
      fstream output(file_str, ios::out | ios::trunc | ios::binary);
      if (!foo.SerializeToOstream(&output)) {
        cerr << "Failed to write address book." << endl;
        return -1;
      }

    }

    {
      // Parse the serialized message and check that it contains the
      // correct data.
      Foo foo;
//      foo.ParseFromString(data);
      std::string file_str = "./dress.xml";
      fstream input(file_str, ios::in | ios::binary);
      if (!input) {
        cout << file_str << ": File not found.  Creating a new file." << endl;
      } else if (!foo.ParseFromIstream(&input)) {
        cerr << "Failed to parse address book." << endl;
        return -1;
      }

      assert(foo.text() == "Hello World!");
      assert(foo.numbers_size() == 3);
      assert(foo.numbers(0) == 1);
      assert(foo.numbers(1) == 5);
      assert(foo.numbers(2) == 42);
    }

    {
      // Same as the last block, but do it dynamically via the Message
      // reflection interface.
      Message* foo = new Foo;
      const Descriptor* descriptor = foo->GetDescriptor();

      // Get the descriptors for the fields we're interested in and verify
      // their types.
      const FieldDescriptor* text_field = descriptor->FindFieldByName("text");
      assert(text_field != NULL);
      assert(text_field->type() == FieldDescriptor::TYPE_STRING);
      assert(text_field->label() == FieldDescriptor::LABEL_OPTIONAL);
      const FieldDescriptor* numbers_field = descriptor->
                                             FindFieldByName("numbers");
      assert(numbers_field != NULL);
      assert(numbers_field->type() == FieldDescriptor::TYPE_INT32);
      assert(numbers_field->label() == FieldDescriptor::LABEL_REPEATED);

      // Parse the message.
      foo->ParseFromString(data);

      // Use the reflection interface to examine the contents.
      const Reflection* reflection = foo->GetReflection();
      assert(reflection->GetString(*foo, text_field) == "Hello World!");
      assert(reflection->FieldSize(*foo, numbers_field) == 3);
      assert(reflection->GetRepeatedInt32(*foo, numbers_field, 0) == 1);
      assert(reflection->GetRepeatedInt32(*foo, numbers_field, 1) == 5);
      assert(reflection->GetRepeatedInt32(*foo, numbers_field, 2) == 42);

      delete foo;
    }
  return 0;
}
