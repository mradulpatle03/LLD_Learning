#include <bits/stdc++.h>
using namespace std;

class INotification
{
public:
    virtual string getContent() = 0;
};

class SimpleNotifictaion : public INotification
{
public:
    string text;
    SimpleNotifictaion(string text) : text(text) {}
    string getContent()
    {
        return text;
    }
};

class INotificationDecorator : public INotification
{
public:
    INotification *notification;
    INotificationDecorator(INotification *notification)
    {
        this->notification = notification;
    }
};

class TimeDecorator : public INotificationDecorator
{
public:
    TimeDecorator(INotification *notification) : INotificationDecorator(notification) {}
    string getContent()
    {
        time_t now = time(0);
        char *dt = ctime(&now);
        return notification->getContent() + " Time: " + string(dt);
    }
};

class SignatureDecorator : public INotificationDecorator
{
public:
    SignatureDecorator(INotification *notification) : INotificationDecorator(notification) {}
    string getContent()
    {
        return notification->getContent() + " Regards, Team";
    }
};
class IObserver
{
public:
    virtual void update() = 0;
};

class IObservervable
{
public:
    vector<IObserver*> observers;
    virtual void addObserver(IObserver* observer) = 0;
    virtual void removeObserver(IObserver* observer) = 0;
    virtual void notifyObservers() = 0;
};

class NotificationObserverable : public IObservervable
{
public:
    INotification *notification;
    void addObserver(IObserver *observer) override
    {
        observers.push_back(observer);
    }
    void removeObserver(IObserver *observer) override
    {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }
    void notifyObservers() override
    {
        for (auto observer : observers)
        {
            observer->update();
        }
    }

    INotification *getNotification()
    {
        return notification;
    }

    void setNotification(INotification *notification)
    {
        this->notification = notification;
        notifyObservers();
    }
};

class NotificationService
{
    // we should make it singleton but for simplicity we are not doing it here
public:
    vector<INotification *> notifications;
    NotificationObserverable *observerable;
    NotificationService(NotificationObserverable *observerable)
    {
        this->observerable = observerable;
    }
    void sendNotification(INotification *notification)
    {
        notifications.push_back(notification);
        observerable->setNotification(notification);
    }
};



class LoggerObserver : public IObserver
{
public:
    void update() override
    {
        cout << "Log -> Notification sent!" << endl;
    }
};

class INotificationStrategy
{
public:
    virtual void send(string message) = 0;
};

class NotificationEngine : public IObserver
{
public:
    NotificationObserverable* observerable;
    vector<INotificationStrategy *> strategies;
    
    NotificationEngine(NotificationObserverable* observerable) : observerable(observerable) {}

    void addStrategy(INotificationStrategy* strategy)
    {
        strategies.push_back(strategy);
    }

    void update() override
    {
        for (auto strategy : strategies)
        {
            strategy->send(observerable->getNotification()->getContent());
        }
    }
};

class EmailNotificationStrategy : public INotificationStrategy
{
public:
    string email;
    EmailNotificationStrategy(string email) : email(email) {}
    void send(string message) override
    {
        cout << "Sending Email to: " << email << " with message: " << message << endl;
    }
};

class SMSNotificationStrategy : public INotificationStrategy
{
public:
    string number;
    SMSNotificationStrategy(string number) : number(number) {}
    void send(string message) override
    {
        cout << "Sending SMS to: " << number << " with message: " << message << endl;
    }
};

class PopupNotificationStrategy : public INotificationStrategy
{
public:
    void send(string message) override
    {
        cout << "Showing Popup: " << message << endl;
    }
};

int main()
{
    INotification* notification = new SimpleNotifictaion("Hello, this is a notification!");

    INotification* decoratedNotification = new TimeDecorator(notification);
    decoratedNotification = new SignatureDecorator(decoratedNotification);

    NotificationObserverable* observerable = new NotificationObserverable();
    LoggerObserver* logger = new LoggerObserver();
    NotificationEngine* engine = new NotificationEngine(observerable);

    engine->strategies.push_back(new EmailNotificationStrategy("mradul@pm.me"));
    engine->strategies.push_back(new SMSNotificationStrategy("+1234567890"));
    engine->strategies.push_back(new PopupNotificationStrategy());

    observerable->addObserver(logger);
    observerable->addObserver(engine);

    observerable->setNotification(decoratedNotification);

    return 0;
}