#include<bits/stdc++.h>
using namespace std;

class IEmployee {
private:
    IEmployee* nextEmployee;
public:
    virtual void handleLeaveRequest(int days) = 0;
    void setNextEmployee(IEmployee* employee) {
        nextEmployee = employee;
    }
    IEmployee* getNextEmployee() {
        return nextEmployee;
    }   
};


class TeamLead : public IEmployee {
public:
    void handleLeaveRequest(int days) {
        if (days <= 2) {
            cout << "Team Lead approved leave for " << days << " days." << endl;
        } else if (getNextEmployee() != nullptr) {
            getNextEmployee()->handleLeaveRequest(days);
        } else {
            cout << "Leave request for " << days << " days cannot be approved." << endl;
        }
    }
};

class Manager : public IEmployee {
public:
    void handleLeaveRequest(int days) {
        if (days <= 5) {
            cout << "Manager approved leave for " << days << " days." << endl;
        } else if (getNextEmployee() != nullptr) {
            getNextEmployee()->handleLeaveRequest(days);
        } else {
            cout << "Leave request for " << days << " days cannot be approved." << endl;
        }
    }
};

class Director : public IEmployee {
public: 
    void handleLeaveRequest(int days) {
        if (days <= 10) {
            cout << "Director approved leave for " << days << " days." << endl;
        } else {
            cout << "Leave request for " << days << " days cannot be approved." << endl;
        }
    }
};

int main(){
    TeamLead* teamLead = new TeamLead();
    Manager* manager = new Manager();
    Director* director = new Director();

    teamLead->setNextEmployee(manager);
    manager->setNextEmployee(director);

    teamLead->handleLeaveRequest(3);
    teamLead->handleLeaveRequest(6);
    teamLead->handleLeaveRequest(11);

    return 0;
}