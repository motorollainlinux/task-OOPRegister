#include <iostream>
#include <fstream>
#include <stdlib.h>

class Person {
    private: 
    int ID;
    std::string login, password, data;
    std::string Search(std::string searchstr) {
        int someID;
        std::string someloigin, somepassword, somedata, str;
        std::ifstream Data_Base;
        Data_Base.open("Data_Base.txt");
         while(Data_Base >> someloigin >> somepassword >> someID >> somedata){
            if (searchstr == someloigin) {
                Data_Base.close();
                return somepassword;
            }
        }
        Data_Base.close();
        return "";
    }
    public: 
    Person(std::string login, std::string password, int ID, std::string data) {
        this->login = login;
        this->password = password;
        this->ID = ID;
        this->data = data;
    }
    void SingIn(std::string newlogin, std::string newPassword, int newID, std::string newdata) {
        std::ofstream Data_Base;
        Data_Base.open("Data_Base.txt", std::ios::app);
        Data_Base << newlogin << " " << newPassword << " " << newID << " " << newdata << "\n";
        Data_Base.close();
    }
    void LogIn() {
        bool IsValidEnter = false;
        int counterrors = 0;
        std::string UserEnter, thispassword;
        do {
            std::cout << "Enter your login: ";
            std::cin >> UserEnter;
            if (Search(UserEnter) == "")
            std::cout << "Invalid login. Try register account first.\n";
            else {
                thispassword = Search(UserEnter);
                IsValidEnter = true;
            }
        } while(!IsValidEnter);
        IsValidEnter = false;
        do { 
            if (counterrors == 3) {
                std::cout << "Your account is bloked.\n";
                return;
            }
            std::cout << "Enter your password: ";
            std::cin >> UserEnter;
            if (UserEnter != thispassword) {
                counterrors++;
                std::cout << "Wrong password! Count of attempts after bloked account: " << 3 - counterrors << ".\n";
            } else IsValidEnter = true;
        } while(!IsValidEnter);
        std::cout << "You are enter in account.\n";
        std::cin.get();
    }
};
void CreateAccount(int ID, std::string login, std::string password, std::string data) {
    Person* newperson = new Person(login, password, ID, data);
    newperson->SingIn(login, password, ID, data);
}
void UserChoise() {
    srand(time(NULL));
    bool IsEnd = false, IsValidEnter = false;
    int UserEnter, ID;
    std::string login, password, data;
    do {
        std::cout << "what you wanna?| 0 - create account; 1 - enter to account; -1 - exit programm |\n";
        std::cin >> UserEnter;
        if (UserEnter == 0) {
            std::cout << "Enter how login you wanna: ";
            std::cin >> login;
            do {
            std::cout << "Enter how password you wanna: ";
            std::cin >> password;
            if (password.size() >= 5 && password.size() <= 7) {
                IsValidEnter = true;
            } else std::cout << "uncorrect password!\n";
            } while(!IsValidEnter);
            std::cout << "Your position in the company: ";
            std::cin >> data;
            ID = 170 + rand() % 250;
            CreateAccount(ID, login, password, data);
        } else if (UserEnter == 1) {
            Person* newperson = new Person("", "123", 0, "");
            newperson->LogIn();
        } else if (UserEnter == -1) {
            IsEnd = true;
        } else {
            std::cout << "Is invalid enter. try again.\n";
        }
    } while(!IsEnd);
}

int main() {
    UserChoise();
}
