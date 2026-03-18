#include <bits/stdc++.h>
using namespace std;

class Observer
{
public:
    virtual void update(string message) = 0;
};

class User : public Observer
{
public:
    static int nextId;
    string id;
    string name;
    string email;
    map<string, double> balance;

    User(string name, string email)
    {
        this->name = name;
        this->email = email;
        nextId++;
        this->id = "user_" + to_string(nextId);
    }

    void update(string message)
    {
        cout << "Notification for user " << id << " received: " << message << endl;
    }

    void updateBalance(string userId, double amount)
    {
        balance[userId] += amount;
        if (abs(balance[userId]) < 0.01)
        {
            balance.erase(userId);
        }
        string message = "You have received Rs " + to_string(amount) + " from user " + userId;
        update(message);
    }

    double getTotalOwed()
    {
        double total = 0;
        for (auto it : balance)
        {
            if (it.second < 0)
            {
                total += abs(it.second);
            }
        }
        return total;
    }

    double getTotalOwing()
    {
        double total = 0;
        for (auto it : balance)
        {
            if (it.second > 0)
            {
                total += it.second;
            }
        }
        return total;
    }
};

int User::nextId = 0;

class Split
{
public:
    string userId;
    double amount;
    Split(string userId, double amount)
    {
        this->userId = userId;
        this->amount = amount;
    }
};

class Expense
{
public:
    static int nextId;
    string expenseId;
    string description;
    double amount;
    string payedBy;
    vector<Split> splits;
    string groupId;

    Expense(string description, double amount, string payedBy, vector<Split> splits, string groupId = "")
    {
        nextId++;
        this->expenseId = "expense_" + to_string(nextId);
        this->description = description;
        this->amount = amount;
        this->payedBy = payedBy;
        this->splits = splits;
        this->groupId = groupId;
    }
};

int Expense::nextId = 0;

enum SplitType
{
    EQUAL,
    PERCENTAGE,
    EXACT,
};

class SplitStrategy
{
public:
    virtual vector<Split> splitExpense(double total, vector<string> userIds, vector<double> amounts = {}) = 0;
};

class EqualSplit : public SplitStrategy
{
public:
    vector<Split> splitExpense(double total, vector<string> userIds, vector<double> amounts = {})
    {
        vector<Split> splits;
        double amount = total / userIds.size();
        for (string userId : userIds)
        {
            splits.push_back(Split(userId, amount));
        }
        return splits;
    }
};

class ExactSplit : public SplitStrategy
{
public:
    vector<Split> splitExpense(double total, vector<string> userIds, vector<double> amounts = {})
    {
        vector<Split> splits;
        for (int i = 0; i < userIds.size(); i++)
        {
            splits.push_back(Split(userIds[i], amounts[i]));
        }
        return splits;
    }
};

class PercentageSplit : public SplitStrategy
{
public:
    vector<Split> splitExpense(double total, vector<string> userIds, vector<double> amounts = {})
    {
        vector<Split> splits;
        for (int i = 0; i < userIds.size(); i++)
        {
            splits.push_back(Split(userIds[i], (amounts[i] / 100) * total));
        }
        return splits;
    }
};

class SplitFactory
{
public:
    static SplitStrategy *getSplitStrategy(SplitType splitType)
    {
        switch (splitType)
        {
        case EQUAL:
            return new EqualSplit();
        case PERCENTAGE:
            return new PercentageSplit();
        case EXACT:
            return new ExactSplit();
        default:
            return nullptr;
        }
    }
};

class DebtSimplifier
{
public:
    static map<string, map<string, double>> simplifyDebts(map<string, map<string, double>> groupBalances)
    {
        map<string, map<string, double>> simplifiedBalances;

        // calculate net for each user
        map<string, double> netBalances;

        for (auto it : groupBalances)
        {
            netBalances[it.first] = 0;
        }

        for (auto userBalance : groupBalances)
        {
            string userId = userBalance.first;
            for (auto it : userBalance.second)
            {
                string debtorId = it.first;
                double amount = it.second;

                // avoid counting twice for same user
                if (amount > 0)
                {
                    netBalances[userId] += amount;
                    netBalances[debtorId] -= amount;
                }
            }
        }

        vector<pair<string, double>> creditors;
        vector<pair<string, double>> debtors;

        // separate creditors and debtors
        for (auto it : netBalances)
        {
            string userId = it.first;
            double amount = it.second;

            if (amount > 0.01)
            {
                creditors.push_back(make_pair(userId, amount));
            }
            else if (amount < -0.01)
            {
                debtors.push_back(make_pair(userId, abs(amount)));
            }
        }

        // sort creditors and debtors
        sort(creditors.begin(), creditors.end(), [](pair<string, double> a, pair<string, double> b)
             { return a.second > b.second; });

        sort(debtors.begin(), debtors.end(), [](pair<string, double> a, pair<string, double> b)
             { return a.second > b.second; });

        for (auto balance : groupBalances)
        {
            simplifiedBalances[balance.first] = map<string, double>();
        }

        int i = 0;
        int j = 0;
        while (i < creditors.size() && j < debtors.size())
        {
            string creditor = creditors[i].first;
            string debtor = debtors[j].first;
            double amount = min(creditors[i].second, debtors[j].second);
            simplifiedBalances[creditor][debtor] = amount;
            simplifiedBalances[debtor][creditor] = -amount;

            creditors[i].second -= amount;
            debtors[j].second -= amount;

            if (creditors[i].second < 0.01)
            {
                i++;
            }
            if (debtors[j].second < 0.01)
            {
                j++;
            }
        }
        return simplifiedBalances;
    }
};

class Group
{
private:
    User *getUserById(string userId)
    {
        User *user = nullptr;

        for (User *member : members)
        {
            if (member->id == userId)
            {
                user = member;
                break;
            }
        }
        return user;
    }

public:
    static int nextGroupId;
    string groupId;
    string name;
    vector<User *> members;
    map<string, Expense *> groupExpenses;
    map<string, map<string, double>> groupBalances;

    Group(string name)
    {
        this->name = name;
        this->groupId = "group _" + to_string(nextGroupId++);
    }
    ~Group()
    {
        for (auto it : groupExpenses)
        {
            delete it.second;
        }
    }

    void addMember(User *user)
    {
        members.push_back(user);

        groupBalances[user->id] = map<string, double>();
        cout << "User " << user->id << " added to group " << groupId << endl;
    }

    bool removeMember(string userId)
    {
        if (!canUserLeaveGroup(userId))
        {
            cout << "User " << userId << " cannot leave group " << groupId << endl;
            return false;
        }

        for (User *member : members)
        {
            if (member->id == userId)
            {
                members.erase(remove(members.begin(), members.end(), member), members.end());
                cout << "User " << userId << " left group " << groupId << endl;
                break;
            }
        }

        groupBalances.erase(userId);

        for (auto memberBalance : groupBalances)
        {
            memberBalance.second.erase(userId);
        }

        return true;
    }

    void notifyMembers(string message)
    {
        for (User *member : members)
        {
            member->update(message);
        }
    }

    bool isMember(string userId)
    {
        return groupBalances.find(userId) != groupBalances.end();
    }

    void updateGroupBalance(string fromUserId, string toUserId, double amount)
    {
        groupBalances[fromUserId][toUserId] += amount;
        groupBalances[toUserId][fromUserId] -= amount;

        if (abs(groupBalances[fromUserId][toUserId]) < 0.01)
        {
            groupBalances[fromUserId].erase(toUserId);
        }
        if (abs(groupBalances[toUserId][fromUserId]) < 0.01)
        {
            groupBalances[toUserId].erase(fromUserId);
        }
    }

    bool canUserLeaveGroup(string userId)
    {
        if (!isMember(userId))
        {
            throw runtime_error("User " + userId + " is not a member of group " + groupId);
        }

        map<string, double> userBalanceSheet = groupBalances[userId];
        for (auto balance : userBalanceSheet)
        {
            if (abs(balance.second) > 0.01)
            {
                return false;
            }
        }
        return true;
    }

    map<string, double> getGroupBalance(string userId)
    {
        if (!isMember(userId))
        {
            throw runtime_error("User " + userId + " is not a member of group " + groupId);
        }
        return groupBalances[userId];
    }

    bool addExpense(string description, double amount, string paidByUserId, vector<string> involvedUsers, SplitType splitType, vector<double> splitValues = {})
    {

        if (!isMember(paidByUserId))
        {
            throw runtime_error("user is not part of group");
        }

        for (string user : involvedUsers)
        {
            if (!isMember(user))
            {
                throw runtime_error("user is not part of group");
            }
        }

        vector<Split> splits = SplitFactory::getSplitStrategy(splitType)->splitExpense(amount, involvedUsers, splitValues);

        Expense *expense = new Expense(description, amount, paidByUserId, splits, groupId);
        groupExpenses[expense->expenseId] = expense;

        for (Split split : splits)
        {
            if (split.userId == paidByUserId)
            {
                continue;
            }
            updateGroupBalance(paidByUserId, split.userId, split.amount);
        }

        // ------------- send notification to all members --------------

        string paidByUserIdName = getUserById(paidByUserId)->name;
        string message = "Expense " + description + " of " + to_string(amount) + " has been added by " + paidByUserIdName;
        notifyMembers(message);

        if (!splitValues.empty())
        {
            for (int i = 0; i < splitValues.size(); i++)
            {
                cout << involvedUsers[i] << " owes " << splitValues[i] << " to " << paidByUserIdName << endl;
            }
        }
        else
        {
            for (string user : involvedUsers)
            {
                cout << getUserById(user)->name << ", ";
                cout << endl
                     << "Will be paid Equal amount" << endl;
            }
        }
        return true;
    }

    bool settlePayment(string fromUserId, string toUserId, double amount)
    {
        if (!isMember(fromUserId) || !isMember(toUserId))
        {
            throw runtime_error("User is not a member of group " + groupId);
            return false;
        }

        updateGroupBalance(fromUserId, toUserId, amount);

        string fromUserName = getUserById(fromUserId)->name;
        string toUserName = getUserById(toUserId)->name;
        string message = "Payment of " + to_string(amount) + " from " + fromUserName + " to " + toUserName + " has been settled";
        notifyMembers(message);
        return true;
    }

    void showGroupBalance()
    {
        cout << "Group Balance" << endl;

        for (const auto &pair : groupBalances)
        {
            string memberId = pair.first;
            string memberName = getUserById(memberId)->name;

            cout << memberName << "'s balances in group:" << endl;

            auto userBalances = pair.second;
            if (userBalances.empty())
            {
                cout << "  No outstanding balances" << endl;
            }
            else
            {
                for (const auto &userBalance : userBalances)
                {
                    string otherMemberUserId = userBalance.first;
                    string otherName = getUserById(otherMemberUserId)->name;

                    double balance = userBalance.second;
                    if (balance > 0)
                    {
                        cout << "  " << otherName << " owes: Rs " << fixed << setprecision(2) << balance << endl;
                    }
                    else
                    {
                        cout << "  Owes " << otherName << ": Rs " << fixed << setprecision(2) << abs(balance) << endl;
                    }
                }
            }
        }
    }
    void simplifyGroupDebts()
    {
        map<string, map<string, double>> simplifiedBalances = DebtSimplifier::simplifyDebts(groupBalances);
        groupBalances = simplifiedBalances;

        cout << "Group debts have been simplified." << endl;
    }
};

int Group::nextGroupId = 0;

class Splitwise
{
private:
    map<string, User *> users;
    map<string, Group *> groups;
    map<string, Expense *> expenses;

    static Splitwise *instance;
    Splitwise() {}

public:
    static Splitwise *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Splitwise();
        }
        return instance;
    }

    User *createUser(string name, string email)
    {
        User *user = new User(name, email);
        users[user->id] = user;
        cout << "user created" << endl;
        return user;
    }

    User *getUser(string userId)
    {
        auto it = users.find(userId);
        if (it != users.end())
        {
            return it->second;
        }
        return nullptr;
    }

    Group *createGroup(string name)
    {
        Group *group = new Group(name);
        groups[group->groupId] = group;
        cout << "group created" << endl;
        return group;
    }

    Group *getGroup(string groupId)
    {
        auto it = groups.find(groupId);
        if (it != groups.end())
        {
            return it->second;
        }
        return nullptr;
    }

    void addUserToGroup(string userId, string groupId)
    {
        Group *group = getGroup(groupId);
        if (group != nullptr)
        {
            User *user = getUser(userId);
            if (user != nullptr)
            {
                group->addMember(user);
            }
        }
    }

    bool removeUserFromGroup(string userId, string groupId)
    {
        Group *group = getGroup(groupId);
        if (!group)
        {
            cout << "group not found" << endl;
            return false;
        }
        User *user = getUser(userId);
        if (!user)
        {
            cout << "user not found" << endl;
            return false;
        }
        bool userRemoved = group->removeMember(userId);
        if (!userRemoved)
        {
            cout << "user not removed from group" << endl;
            return false;
        }
        return userRemoved;
    }

    void addExpenseToGroup(string groupId, string description, double amount, string paidByUserId, vector<string> involvedUsers, SplitType splitType, vector<double> splitValues={})
    {
        Group *group = getGroup(groupId);
        if (!group)
        {
            cout << "group not found" << endl;
            return;
        }
        group->addExpense(description, amount, paidByUserId, involvedUsers, splitType, splitValues);
    }

    void settlePaymentInGroup(string groupId, string fromUserId, string toUserId, double amount)
    {
        Group *group = getGroup(groupId);
        if (!group)
        {
            cout << "group not found" << endl;
            return;
        }
        group->settlePayment(fromUserId, toUserId, amount);
    }

    void settleIndividualPayment(string fromUserId, string toUserId, double amount)
    {
        User *fromUser = getUser(fromUserId);
        User *toUser = getUser(toUserId);
        if (!fromUser || !toUser)
        {
            cout << "user not found" << endl;
            return;
        }
        fromUser->updateBalance(toUserId, amount);
        toUser->updateBalance(fromUserId, -amount);

        cout << "payment settled" << endl;
    }

    void addIndividualExpense(string description, double amount, string paidByUserId, string toUserId, SplitType splitType, vector<double> splitValues = {})
    {
        SplitStrategy *splitStrategy = SplitFactory::getSplitStrategy(splitType);

        vector<Split> splits = splitStrategy->splitExpense(amount, {paidByUserId, toUserId}, splitValues);

        Expense *expense = new Expense(description, amount, paidByUserId, splits);
        expenses[expense->expenseId] = expense;

        User *fromUser = getUser(paidByUserId);
        User *toUser = getUser(toUserId);
        if (!fromUser || !toUser)
        {
            cout << "user not found" << endl;
            return;
        }
        fromUser->updateBalance(toUserId, amount);
        toUser->updateBalance(paidByUserId, -amount);

        cout << "expense added" << endl;
    }

    void showUserBalance(string userId)
    {
        User *user = getUser(userId);
        if (!user)
        {
            cout << "user not found" << endl;
            return;
        }

        cout << endl
             << "Balance for " << user->name << endl;
        cout << "Total you owe: Rs " << fixed << setprecision(2) << user->getTotalOwed() << endl;
        cout << "Total others owe you: Rs " << fixed << setprecision(2) << user->getTotalOwing() << endl;

        cout << "Detailed balances:" << endl;
        for (auto &balance : user->balance)
        {
            User *otherUser = getUser(balance.first);
            if (otherUser)
            {
                if (balance.second > 0)
                {
                    cout << "  " << otherUser->name << " owes you: Rs" << balance.second << endl;
                }
                else
                {
                    cout << "  You owe " << otherUser->name << ": Rs" << abs(balance.second) << endl;
                }
            }
        }
    }

    void showGroupBalance(string groupId)
    {
        Group *group = getGroup(groupId);
        if (!group)
        {
            cout << "group not found" << endl;
            return;
        }
        group->showGroupBalance();
    }

    void simplifyGroupDebts(string groupId)
    {
        Group *group = getGroup(groupId);
        if (!group)
        {
            cout << "group not found" << endl;
            return;
        }
        group->simplifyGroupDebts();
    }
};

Splitwise *Splitwise::instance = nullptr;

int main()
{
    Splitwise *splitwise = Splitwise::getInstance();

    User* user1 = splitwise->createUser("A", "a@a.com");
    User* user2 = splitwise->createUser("B", "b@b.com");
    User* user3 = splitwise->createUser("C", "c@c.com");
    User* user4 = splitwise->createUser("D", "d@d.com");

    Group* group1 = splitwise->createGroup("Group 1");
    
    splitwise->addUserToGroup(user1->id, group1->groupId);
    splitwise->addUserToGroup(user2->id, group1->groupId);
    splitwise->addUserToGroup(user3->id, group1->groupId);
    splitwise->addUserToGroup(user4->id, group1->groupId);

    vector<string> userIds = {user1->id, user2->id, user3->id, user4->id};
    
    splitwise->addExpenseToGroup(group1->groupId, "Expense 1", 100, user1->id, userIds, SplitType::EQUAL); 

    splitwise->showGroupBalance(group1->groupId);

    splitwise->simplifyGroupDebts(group1->groupId);

    splitwise->showGroupBalance(group1->groupId);

    return 0;
}