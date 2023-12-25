#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath> 

using namespace std;

bool isNumeric(const string& str) {
    for (int i = 0; i < str.size(); i++) {
        char ch = str[i];
        if (!isdigit(ch)) {
            return false; // If a non-numeric character is found, return false immediately
        }
    }
    return true; // If the loop completes without finding non-numeric characters, return true
}

class PhoneRecord {
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    // Constructor
    PhoneRecord(const string& n, const string& org, const vector<string>& numbers)
        : name(n), organisation(org), phoneNumbers(numbers) {}

    // Getter methods
    string getName() const {
        return name;
    }

    string getOrganisation() const {
        return organisation;
    }

    vector<string> getPhoneNumbers() const {
        return phoneNumbers;
    }
};

class HashTableRecord {
private:
    int key;
    PhoneRecord* element; // Pointer to PhoneRecord
    HashTableRecord* next;

public:
    // Constructor
    HashTableRecord(int k, PhoneRecord* rec)
        : key(k), element(rec), next(nullptr) {}

    // Getter methods
    int getKey() const {
        return key;
    }

    PhoneRecord* getRecord() const {
        return element;
    }

    HashTableRecord* getNext() const {
        return next;
    }

    void setNext(HashTableRecord* nxt) {
        next = nxt;
    }
};

class PhoneBook {
private:
    static const int HASH_TABLE_SIZE = 263;
    HashTableRecord* hashTable[HASH_TABLE_SIZE];

public:
    // Constructor
    PhoneBook() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
    }

    // Add your own implementation for hashing
   long long computeHash(const string& str) {
        // Implement a hash function for strings
        long long p = 1000000007;
        long long x = 263;
        long long m=263;
        long long hashvalue = 0;
        long long x_pow_i = 1;
        int i;
        for(i=0;i<str.size();i++){
            long long s = str[i];
            hashvalue = (hashvalue + (s * ((x_pow_i) % p)));
            x_pow_i = (x_pow_i * x) % p;
         hashvalue = hashvalue%m; }
        // cout<<hashvalue<<" ";
        return hashvalue;

}


    // Add your own implementation for adding a contact
    void addContact(const PhoneRecord* record)
    {
        int key;
           string name = record->getName() , attribute, org= record->getOrganisation();
           stringstream ss(name);
          /* while (ss, attribute, ' ')
           {
               key= computeHash(attribute);
               
               HashTableRecord* htrobj=new HashTableRecord(key, record);


           } */
           
           while (ss>>attribute)
                 {
                       key=  (computeHash(attribute));
                       PhoneRecord * demo = const_cast <PhoneRecord *> (record);
                       HashTableRecord* htrobj=new HashTableRecord(key, demo);
                       if (hashTable[key]==nullptr) 
                       {
                           htrobj-> setNext(nullptr);
                           hashTable[key]=htrobj;
                           
                       }
                       else
                       {
                            HashTableRecord* temp= hashTable[key];
                            while (temp->getNext()!=nullptr)
                            {
                                temp=temp->getNext();

                            }
                            temp->setNext(htrobj);
                            htrobj->setNext(nullptr);
                       }



                 }


    };

    // Add your own implementation for deleting a contact
    bool deleteContact(const string* searchName) {
        // Implement deleting a contact from the phone book
        const std::string& s = *searchName;
        vector<PhoneRecord*> searches = fetchContacts(searchName);
        if(searches.empty()){
            return false;
        }
        for(int j=0;j<searches.size();j++){
        PhoneRecord* deleting = searches[j];
        // vector<HashTableRecord*> deleted;
        for(int i=0;i<HASH_TABLE_SIZE;i++){
            HashTableRecord* current = hashTable[i];
            HashTableRecord* prev = nullptr;
            while(current!=nullptr){
            if(current->getRecord()->getName() == deleting->getName()){
                // deleted.push_back(current);
                if(prev!=nullptr){
                    prev->setNext(current->getNext());
                }
                else {
                    hashTable[i]=current->getNext();
                }
                delete current;
            }
            else{
                prev = current;
            }
            current=current->getNext();
        }
    } }
    return true;
    }
  
  
  
    // Add your own implementation for fetching contacts
    vector<PhoneRecord*> fetchContacts(const string* query) {
    vector<PhoneRecord*> probj; // Vector to store the retrieved PhoneRecord objects
    stringstream ss(*query);
    string word;

    // Create a map to count how many times each PhoneRecord is pointed to
    unordered_map<PhoneRecord*, int> recordCount;

    while (ss >> word) {
        int key = static_cast<int>(computeHash(word));
        HashTableRecord* temp = hashTable[key];

        while (temp != nullptr) {
            PhoneRecord* record = temp->getRecord();
            recordCount[record]++;
            temp = temp->getNext();
        }
    }

    // Create a multimap to sort PhoneRecord objects by the number of occurrences
    multimap<int, PhoneRecord*, greater<int>> sortedRecords; // Using greater<int> for reverse order

    for (const auto& entry : recordCount) {
        sortedRecords.insert({entry.second, entry.first});
    }

    // Iterate over the multimap to retrieve PhoneRecord objects
    for (const auto& entry : sortedRecords) {
        probj.push_back(entry.second);
    }

    return probj;
}



    // Add your own implementation for counting records pointing to a contact
    int countRecordsPointingTo(const PhoneRecord* record) const;

    // Add your own implementation for reading records from a file
    void readRecordsFromFile(const string& filename)
    {
        
        ifstream fileinput(filename);

        if (!fileinput.is_open())
        {
             cerr<<"failed to open the file"<<endl;
             return;
        }
        else{
             
             string name,line,attribute,  organisation;
             vector<string> phonenumber;
             
             //stringstream ss;

             while(getline(fileinput,line))
             {
                stringstream ss(line);
                getline (ss, name,',');

               
                

                while (getline(ss,attribute,','))
                {
                    if (isNumeric(attribute))
                    {
                       phonenumber.push_back(attribute);

                    }
                    else 
                    organisation= attribute;
                }
                 
                 PhoneRecord* newprob=new PhoneRecord(name,organisation, phonenumber );
                 
                 addContact(newprob);
                 phonenumber.clear();

                 
             }
             






        }

    };

    // Destructor
   // ~PhoneBook();
};