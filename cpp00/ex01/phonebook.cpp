#include <string>
#include <iostream>
#include <iomanip>

class Contact {

public:
    //initialize members
    Contact() : index(0), phone_number("") {}

    //setter and getter methods
    void SetIndex(size_t idx) { index = idx; }
    void SetFirstName(const std::string& fname) { first_name = fname; }
    void SetLastName(const std::string& lname) { last_name = lname; }
    void SetNickName(const std::string& nname) { nick_name = nname; }
    void SetDarkestSecret(const std::string& secret) { darkest_secret = secret; }
    void SetPhoneNumber(const std::string& pnumber) { phone_number = pnumber; }

    int GetIndex() const { return index; }
    const std::string& GetFirstName() const { return first_name; }
    const std::string& GetLastName() const { return last_name; }
    const std::string& GetNickName() const { return nick_name; }
    const std::string& GetDarkestSecret() const { return darkest_secret; }
    const std::string& GetPhoneNumber() const { return phone_number; }

private:
    size_t index;
    std::string first_name;
    std::string last_name;
    std::string nick_name; 
    std::string darkest_secret;
    std::string phone_number;
};

class PhoneBook {
private:
    Contact contacts[8];

public:
    
    void Search() 
    {
        std::string input;
        size_t idx;
        while(idx != 9)
        {
            std::cout << "Index | First Name | Last Name  | Nick Name " << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
            for (size_t i = 0; i < 8; ++i) {
                if (!contacts[i].GetFirstName().empty()) {
                    std::cout << std::setw(10) << contacts[i].GetIndex() << "|"
                            << std::setw(10) << contacts[i].GetFirstName().substr(0, 10) << "|"
                            << std::setw(10) << contacts[i].GetLastName().substr(0, 10) << "|"
                            << std::setw(10) << contacts[i].GetNickName().substr(0, 10) << std::endl;
                }
            }
            std::cout << "Enter index to view details or 9 to quit: ";
            std::cin >> idx;
            std::cin.ignore(); // Clear newline character from input buffer
            if (idx < 8 && !contacts[idx].GetFirstName().empty()) {
                std::cout << "First Name: " << contacts[idx].GetFirstName() << std::endl;
                std::cout << "Last Name: " << contacts[idx].GetLastName() << std::endl;
                std::cout << "Nick Name: " << contacts[idx].GetNickName() << std::endl;
                std::cout << "Darkest Secret: " << contacts[idx].GetDarkestSecret() << std::endl;
                std::cout << "Phone Number: " << contacts[idx].GetPhoneNumber() << std::endl;
            } 
            else if (idx == 9) {
                break;
            }
            else {
                std::cout << "Invalid index." << std::endl;
            }
        }
    }
    void AddContact() 
    {
        std::string input;
        std::string temp;
        Contact new_contact;
        static size_t index = 0;

        std::cout << "Enter First Name: ";
        std::getline(std::cin, temp);
        new_contact.SetFirstName(temp);
        std::cout << "Enter Last Name: ";
        std::getline(std::cin, temp);
        new_contact.SetLastName(temp);
        std::cout << "Enter Nick Name: ";
        std::getline(std::cin, temp);
        new_contact.SetNickName(temp);
        std::cout << "Enter Darkest Secret: ";
        std::getline(std::cin, temp);
        new_contact.SetDarkestSecret(temp);
        std::cout << "Enter Phone Number: ";
        std::getline(std::cin, temp);
        new_contact.SetPhoneNumber(temp);
        new_contact.SetIndex(index);
        // AddContact2(new_contact, index);
        if (index < 8) {
            contacts[index] = new_contact;
        }
        index = (index + 1) % 8; // Wrap around after 8 contacts
    }
    void Exit(){}
};

int main() {
    PhoneBook phonebook;
    std::string input;

    std::cout << "PhoneBook application started." << std::endl;
    std::cout << "Please choose command:" << std::endl;
    std::cout << "ADD, SEARCH, or EXIT" << std::endl;
    
    std::getline(std::cin, input);
    while (input != "EXIT") 
    {
        if (input == "ADD") 
        {
            phonebook.AddContact();
            std::cout << "Please choose command:" << std::endl;
            std::cout << "ADD, SEARCH, or EXIT" << std::endl;      
            std::getline(std::cin, input);      
        }
        else if (input == "SEARCH") 
        {
            phonebook.Search();
            std::cout << "Please choose command:" << std::endl;
            std::cout << "ADD, SEARCH, or EXIT" << std::endl;      
            std::getline(std::cin, input);   
        }
        else 
        {
            std::cout << "Invalid command. Please enter ADD, SEARCH, or EXIT." << std::endl;
            std::getline(std::cin, input);
        }
    }
    return 0;
}