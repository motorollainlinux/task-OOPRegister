#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Person {
    private: 
    int ID;
    std::string login, password, data;
    std::string Search(std::string searchstr) {
        int someID;
        std::string someloigin, somepassword, somedata;
        FILE *DataBase;
        DataBase = fopen("Data_Base.txt", "r");
        for (;!feof(DataBase);) {
            fscanf(DataBase, "%d %s %s %s", someID, someloigin, somepassword, somedata);
            if (searchstr == someloigin) {
                fclose(DataBase);
                return somepassword;
            }
        }
        fclose(DataBase);
        return "";
    }
    public: 
    Person(std::string login, std::string password, int ID, std::string data) {
        this -> login = login;
        this -> password = password;
        this -> ID = ID;
        this -> data = data;
    }
    void SingIn(std::string newlogin, std::string newPassword, int newID, std::string newdata) {
        FILE *DataBase;
        DataBase = fopen("Data_Base.txt", "a");
        fprintf(DataBase, "%d %s %s %s\n", newID, newlogin, newPassword, newdata);
        fclose(DataBase);
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
    Person* newperson = new Person(ID, login, password, data);
    newperson -> SingIn(ID, login, password, data);
}
void UserChoise() {
    srand(time(NULL));
    bool IsEnd = false;
    int UserEnter, ID;
    std::string login, password, data;
    do {
        std::cout << "what you wanna?| 0 - create account; 1 - enter to account; -1 - exit programm |\n";
        std::cin >> UserEnter;
        if (UserEnter == 0) {
            std::cout << "Enter how login you wanna: ";
            std::cin >> login;
            std::cout << "Enter how password you wanna: ";
            std::cin >> password;
            std::cout << "Your position in the company: ";
            std::cin >> data;
            ID = 170 + Rand() % 250;
            CreateAccount(ID, login, password, data);
        } else if (UserChoise == 1) {
            Person* newperson = new Person(0 , "", "123", "");
            newperson -> LogIn();
        } else if (UserChoise == -1) {
            IsEnd = true;
        } else {
            std::cout << "Is invalid enter. try again.\n";
        }
    } while(!IsEnd);
}

int main() {
    UserChoise();
}
