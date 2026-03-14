#include <bits/stdc++.h>
using namespace std;

// Observer Pattern

class NotificationObserver
{
public:
    virtual void update(string message) = 0;
};

class UserNotificationObserver : public NotificationObserver
{
private:
    string userId;

public:
    UserNotificationObserver(string id) : userId(id) {}
    void update(string message)
    {
        cout << "Notification for user " << userId << " received: " << message << endl;
    }
};

class NotificationService
{
private:
    map<string, NotificationObserver *> observers;
    static NotificationService *instance;
    NotificationService() {}

public:
    static NotificationService *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new NotificationService();
        }
        return instance;
    }
    void subscribe(string userId, NotificationObserver *observer)
    {
        observers[userId] = observer;
    }
    void unsubscribe(string userId)
    {
        observers.erase(userId);
    }
    void notify(string userId, string message)
    {
        if (observers.find(userId) != observers.end())
        {
            observers[userId]->update(message);
        }
    }
    void notifyAll(string message)
    {
        for (auto &observer : observers)
        {
            observer.second->update(message);
        }
    }
};
NotificationService *NotificationService::instance = nullptr;

// ENUMs

enum Gender
{
    MALE,
    FEMALE,
    OTHER
};

class Location
{
private:
    double latitude;
    double longitude;

public:
    Location()
    {
        latitude = 0.0;
        longitude = 0.0;
    }
    Location(double lat, double lon) : latitude(lat), longitude(lon) {}
    // Getters
    double getLatitude() { return latitude; }
    double getLongitude() { return longitude; }

    // Setters
    void setLatitude(double lat) { latitude = lat; }
    void setLongitude(double lon) { longitude = lon; }

    // Method to calculate distance between two locations
    double distanceTo(Location other)
    {

        double lat1 = latitude * M_PI / 180.0;
        double lon1 = longitude * M_PI / 180.0;
        double lat2 = other.latitude * M_PI / 180.0;
        double lon2 = other.longitude * M_PI / 180.0;

        double dlat = lat2 - lat1;
        double dlon = lon2 - lon1;

        double a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        double R = 6371; // Radius of the Earth in kilometers
        return R * c;    // Distance in kilometers
    }
};

class Interest
{
private:
    string name;
    string category;

public:
    Interest(string n, string c) : name(n), category(c) {}
    Interest() : name(""), category("") {}
    // Getters
    string getName() { return name; }
    string getCategory() { return category; }

    // Setters
    void setName(string n) { name = n; }
    void setCategory(string c) { category = c; }
};

class Preference
{
private:
    int minAge;
    int maxAge;
    vector<Gender> InterestedGenders;
    double maxDistance; // in kilometers
    vector<string> intersts;

public:
    Preference() : minAge(18), maxAge(100), maxDistance(100) {}
    Preference(int minA, int maxA, double maxD) : minAge(minA), maxAge(maxA), maxDistance(maxD) {}

    // Getters
    int getMinAge() { return minAge; }
    int getMaxAge() { return maxAge; }
    double getMaxDistance() { return maxDistance; }
    vector<Gender> getInterestedGenders() { return InterestedGenders; }
    vector<string> getInterests() { return intersts; }

    // Setters
    void setMinAge(int minA) { minAge = minA; }
    void setMaxAge(int maxA) { maxAge = maxA; }

    void setMaxDistance(double maxD) { maxDistance = maxD; }
    void addInterestedGender(Gender g) { InterestedGenders.push_back(g); }
    void addInterest(string interest) { intersts.push_back(interest); }
    void removeInterestedGender(Gender g)
    {
        InterestedGenders.erase(remove(InterestedGenders.begin(), InterestedGenders.end(), g), InterestedGenders.end());
    }
    void removeInterest(string interest)
    {
        intersts.erase(remove(intersts.begin(), intersts.end(), interest), intersts.end());
    }

    bool isInterestedInGender(Gender g)
    {
        return find(InterestedGenders.begin(), InterestedGenders.end(), g) != InterestedGenders.end();
    }
    bool isInterestedInInterest(string interest)
    {
        return find(intersts.begin(), intersts.end(), interest) != intersts.end();
    }

    bool isWithinAgeRange(int age)
    {
        return age >= minAge && age <= maxAge;
    }

    bool isWithinDistance(double distance)
    {
        return distance <= maxDistance;
    }
};

class Message
{
private:
    string senderId;
    string receiverId;
    string content;
    time_t timestamp;

public:
    Message(string sender, string receiver, string content) : senderId(sender), receiverId(receiver), content(content)
    {
        timestamp = time(0);
    }
    // Getters
    string getSenderId() { return senderId; }
    string getReceiverId() { return receiverId; }
    string getContent() { return content; }
    time_t getTimestamp() { return timestamp; }

    string getFormattedTimestamp()
    {
        char buffer[80];
        struct tm *timeinfo = localtime(&timestamp);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        return string(buffer);
    }

    // Setters
    void setSenderId(string sender) { senderId = sender; }
    void setReceiverId(string receiver) { receiverId = receiver; }
    void setContent(string content) { this->content = content; }
    void setTimestamp(time_t timestamp) { this->timestamp = timestamp; }
};

class ChatRoom
{
private:
    string id;
    vector<string> participantIds;
    vector<Message *> messages;

public:
    ChatRoom(string roomId, string userId1, string userId2) : id(roomId)
    {
        participantIds.push_back(userId1);
        participantIds.push_back(userId2);
    }

    ~ChatRoom()
    {
        for (Message *msg : messages)
        {
            delete msg;
        }
    }

    string getId() { return id; }
    vector<string> getParticipantIds() { return participantIds; }
    vector<Message *> getMessages() { return messages; }

    void addMessage(string senderId, string receiverId, string content)
    {
        Message *newMessage = new Message(senderId, receiverId, content);
        messages.push_back(newMessage);
    }

    bool isParticipant(string userId)
    {
        return find(participantIds.begin(), participantIds.end(), userId) != participantIds.end();
    }

    void removeParticipant(string userId)
    {
        participantIds.erase(remove(participantIds.begin(), participantIds.end(), userId), participantIds.end());
    }

    void displayChat()
    {
        cout << "Chat Room ID: " << id << endl;
        for (Message *msg : messages)
        {
            cout << "[" << msg->getFormattedTimestamp() << "] " << msg->getSenderId() << " to " << msg->getReceiverId() << ": " << msg->getContent() << endl;
        }
        cout << "-----------------------------" << endl;
    }
};

class UserProfile
{
private:
    string name;
    int age;
    Gender gender;
    Location location;
    vector<Interest *> interests;
    vector<string> photos;
    string bio;

public:
    UserProfile()
    {
        name = "";
        age = 0;
        gender = Gender::OTHER;
        bio = "";
    }

    ~UserProfile()
    {
        for (Interest *interest : interests)
        {
            delete interest;
        }
    }

    // setters
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setGender(Gender g) { gender = g; }
    void setLocation(Location loc) { location = loc; }
    void addInterest(string name, string category) { interests.push_back(new Interest(name, category)); }
    void addPhoto(string photoUrl) { photos.push_back(photoUrl); }
    void removePhoto(string photoUrl)
    {
        photos.erase(remove(photos.begin(), photos.end(), photoUrl), photos.end());
    }
    void removeInterest(string name)
    {
        interests.erase(remove_if(interests.begin(), interests.end(), [&](Interest *i)
                                  { return i->getName() == name; }),
                        interests.end());
    }
    void setBio(string b) { bio = b; }

    // getters
    string getName() { return name; }
    int getAge() { return age; }
    Gender getGender() { return gender; }
    Location getLocation() { return location; }
    vector<Interest *> getInterests() { return interests; }
    vector<string> getPhotos() { return photos; }
    string getBio() { return bio; }

    void display()
    {
        cout << "User Profile:" << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << (gender == Gender::MALE ? "Male" : (gender == Gender::FEMALE ? "Female" : "Other")) << endl;
        cout << "Location: (" << location.getLatitude() << ", " << location.getLongitude() << ")" << endl;
        cout << "Bio: " << bio << endl;
        cout << "Interests: ";
        for (Interest *interest : interests)
        {
            cout << interest->getName() << " (" << interest->getCategory() << "), ";
        }
        cout << endl;
        cout << "Photos: ";
        for (string photo : photos)
        {
            cout << photo << ", ";
        }
        cout << endl;
    }
};

enum SwipeAction
{
    LEFT,
    RIGHT
};

class User
{
private:
    string id;
    UserProfile *profile;
    Preference *preference;
    map<string, SwipeAction> swipeHistory;
    NotificationObserver *notificationObserver;

public:
    User(string userId)
    {
        id = userId;
        profile = new UserProfile();
        preference = new Preference();
        notificationObserver = new UserNotificationObserver(userId);
        NotificationService::getInstance()->subscribe(userId, notificationObserver);
    }

    ~User()
    {
        delete profile;
        delete preference;
        NotificationService::getInstance()->unsubscribe(id);
        delete notificationObserver;
    }

    string getId() { return id; }
    UserProfile *getProfile() { return profile; }
    Preference *getPreference() { return preference; }
    void swipe(string otherUserId, SwipeAction action)
    {
        swipeHistory[otherUserId] = action;
    }

    bool hasSwipedRight(string otherUserId)
    {
        return swipeHistory.find(otherUserId) != swipeHistory.end() && swipeHistory[otherUserId] == SwipeAction::RIGHT;
    }

    bool hasSwipedLeft(string otherUserId)
    {
        return swipeHistory.find(otherUserId) != swipeHistory.end() && swipeHistory[otherUserId] == SwipeAction::LEFT;
    }
    bool hasSwiped(string otherUserId)
    {
        return swipeHistory.find(otherUserId) != swipeHistory.end();
    }

    void display()
    {
        profile->display();
    }
};

// strategy pattern for location service
class LocationStrategy
{
public:
    virtual ~LocationStrategy() {}
    virtual vector<User *> getNearbyUsers(Location *location, double maxDistance, vector<User *> allUsers) = 0;
};

class BasicLocationStrategy : public LocationStrategy
{
public:
    vector<User *> getNearbyUsers(Location *location, double maxDistance, vector<User *> allUsers)
    {
        vector<User *> nearbyUsers;
        for (User *user : allUsers)
        {
            if (location->distanceTo(user->getProfile()->getLocation()) <= maxDistance)
            {
                nearbyUsers.push_back(user);
            }
        }
        return nearbyUsers;
    }
};

class LocationService
{
private:
    LocationStrategy *strategy;

    static LocationService *instance;
    LocationService()
    {
        strategy = new BasicLocationStrategy();
    }

public:
    static LocationService *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new LocationService();
        }
        return instance;
    }
    ~LocationService()
    {
        delete strategy;
    }
    void setStrategy(LocationStrategy *newStrategy)
    {
        if (strategy)
            delete strategy;
        strategy = newStrategy;
    }
    vector<User *> getNearbyUsers(Location *location, double maxDistance, vector<User *> allUsers)
    {
        return strategy->getNearbyUsers(location, maxDistance, allUsers);
    }
};

LocationService *LocationService::instance = nullptr;

enum MatcherType
{
    BASIC,
    INTEREST_BASED,
    LOCATION_BASED
};

class Matcher
{
public:
    virtual ~Matcher() {}
    virtual double calculateMatchScore(User *user1, User *user2) = 0;
};

class BasicMatcher : public Matcher
{
public:
    double calculateMatchScore(User *user1, User *user2)
    {
        bool user1LikesUser2Gender = user1->getPreference()->isInterestedInGender(user2->getProfile()->getGender());
        bool user2LikesUser1Gender = user2->getPreference()->isInterestedInGender(user1->getProfile()->getGender());
        if (!user1LikesUser2Gender || !user2LikesUser1Gender)
        {
            return 0.0; // Basic
        }

        bool user1WithinUser2AgeRange = user2->getPreference()->isWithinAgeRange(user1->getProfile()->getAge());

        bool user2WithinUser1AgeRange = user1->getPreference()->isWithinAgeRange(user2->getProfile()->getAge());

        if (!user1WithinUser2AgeRange || !user2WithinUser1AgeRange)
        {
            return 0.0; // Basic
        }
        bool user1WithinUser2Distance = user2->getPreference()->isWithinDistance(user1->getProfile()->getLocation().distanceTo(user2->getProfile()->getLocation()));

        bool user2WithinUser1Distance = user1->getPreference()->isWithinDistance(user2->getProfile()->getLocation().distanceTo(user1->getProfile()->getLocation()));

        if (!user1WithinUser2Distance || !user2WithinUser1Distance)
        {
            return 0.0; // Basic
        }
        return 0.5;
    }
};

class InterestBasedMatcher : public Matcher
{
public:
    double calculateMatchScore(User *user1, User *user2)
    {
        BasicMatcher basicMatcher;
        double score = basicMatcher.calculateMatchScore(user1, user2);
        if (score == 0.0)
            return 0.0; // If basic criteria not met, return 0

        vector<string> user1Interests;
        for (Interest *interest : user1->getProfile()->getInterests())
        {
            user1Interests.push_back(interest->getName());
        }
        vector<string> user2Interests;
        for (Interest *interest : user2->getProfile()->getInterests())
        {
            user2Interests.push_back(interest->getName());
        }
        int commonInterests = 0;
        for (string interest : user1Interests)
        {
            if (find(user2Interests.begin(), user2Interests.end(), interest) != user2Interests.end())
            {
                commonInterests++;
            }
        }

        double maxInterests = max(user1->getProfile()->getInterests().size(), user2->getProfile()->getInterests().size());

        double interestScore = maxInterests > 0 ? 0.5 * (commonInterests / maxInterests) : 0.0;

        return score + interestScore;
    }
};

class LocationBasedMatcher : public Matcher
{
public:
    double calculateMatchScore(User *user1, User *user2)
    {
        InterestBasedMatcher interestBasedMatcher;
        double score = interestBasedMatcher.calculateMatchScore(user1, user2);
        if (score == 0.0)
            return 0.0; // If basic criteria not met, return 0

        double distance = user1->getProfile()->getLocation().distanceTo(user2->getProfile()->getLocation());
        double maxDistance = max(user1->getPreference()->getMaxDistance(), user2->getPreference()->getMaxDistance());
        double distanceScore = maxDistance > 0 ? 0.2 * (1.0 - (distance / maxDistance)) : 0.0;
        return score + distanceScore;
    }
};

class MatcherFactory
{
public:
    static Matcher *createMatcher(MatcherType type)
    {
        switch (type)
        {
        case MatcherType::BASIC:
            return new BasicMatcher();
        case MatcherType::INTEREST_BASED:
            return new InterestBasedMatcher();
        case MatcherType::LOCATION_BASED:
            return new LocationBasedMatcher();
        default:
            return nullptr;
        }
    }
};

class DatingApp
{
private:
    vector<User *> users;
    vector<ChatRoom *> chatRooms;
    Matcher *matcher;

    static DatingApp *instance;
    DatingApp()
    {
        matcher = MatcherFactory::createMatcher(MatcherType::LOCATION_BASED);
    }

public:
    static DatingApp *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new DatingApp();
        }
        return instance;
    }
    ~DatingApp()
    {
        for (User *user : users)
        {
            delete user;
        }
        for (ChatRoom *room : chatRooms)
        {
            delete room;
        }
        delete matcher;
    }
    void setMatcher(MatcherType type)
    {
        delete matcher;
        matcher = MatcherFactory::createMatcher(type);
    }

    User *createUser(string userId)
    {
        User *newUser = new User(userId);
        users.push_back(newUser);
        return newUser;
    }

    User *getUserById(string userId)
    {
        for (User *user : users)
        {
            if (user->getId() == userId)
            {
                return user;
            }
        }
        return nullptr;
    }

    vector<User *> findNearByUsers(string userId, double maxDistance = 5.0)
    {
        User *user = getUserById(userId);
        if (user == nullptr)
            return {};
        Location userLocation = user->getProfile()->getLocation();
        vector<User *> nearByUsers = LocationService::getInstance()->getNearbyUsers(&userLocation, maxDistance, users);

        nearByUsers.erase(remove(nearByUsers.begin(), nearByUsers.end(), user), nearByUsers.end());

        vector<User *> filteredUsers;
        for (User *nearByUser : nearByUsers)
        {
            if (user->hasSwiped(nearByUser->getId()) || nearByUser->hasSwiped(user->getId()))
            {
                continue; // Skip users that have already been swiped on
            }
            if (matcher->calculateMatchScore(user, nearByUser) > 0.0)
            {
                filteredUsers.push_back(nearByUser);
            }
        }
        return filteredUsers;
    }

    bool swipe(string userId, string otherUserId, SwipeAction action)
    {
        User *user = getUserById(userId);
        User *otherUser = getUserById(otherUserId);
        if (user == nullptr || otherUser == nullptr)
            return false;
        user->swipe(otherUserId, action);

        if (action == SwipeAction::RIGHT && otherUser->hasSwipedRight(userId))
        {
            string roomId = userId + "_" + otherUserId;
            ChatRoom *newChatRoom = new ChatRoom(roomId, userId, otherUserId);
            chatRooms.push_back(newChatRoom);

            NotificationService::getInstance()->notify(otherUserId, "You have a new match with user " + userId);

            NotificationService::getInstance()->notify(userId, "You have a new match with user " + otherUserId);

            return true;
        }
        return false;
    }

    ChatRoom *getChatRoom(string user1ID, string user2ID)
    {
        for(ChatRoom *room : chatRooms)
        {
            if (room->isParticipant(user1ID) && room->isParticipant(user2ID))
            {
                return room;
            }
        }
        return nullptr;
    }

    void sendMessage(string senderId, string receiverId, string content)
    {
        ChatRoom *chatRoom = getChatRoom(senderId, receiverId);
        if (chatRoom != nullptr)
        {
            chatRoom->addMessage(senderId, receiverId, content);
        }else {
            cout << "No chat room found between " << senderId << " and " << receiverId << endl;
            return;
        }

        NotificationService::getInstance()->notify(receiverId, "You have a new message from user " + senderId);
    }

    void displayUserProfile(string userId)
    {
        User *user = getUserById(userId);
        if (user != nullptr)
        {
            user->display();
        }else {
            cout << "User with ID " << userId << " not found." << endl;
            return;
        }
    }

    void displayChat(string user1ID, string user2ID)
    {
        ChatRoom *chatRoom = getChatRoom(user1ID, user2ID);
        if (chatRoom != nullptr)
        {
            chatRoom->displayChat();
        }else {
            cout << "No chat room found between " << user1ID << " and " << user2ID << endl;
            return;
        }
    }
};

DatingApp *DatingApp::instance = nullptr;

int main()
{
    DatingApp* app = DatingApp::getInstance();

    User* user1 = app->createUser("user1");
    User* user2 = app->createUser("user2");

    UserProfile* profile1 = user1->getProfile();
    profile1->setName("John Doe");
    profile1->setAge(25);
    profile1->setGender(Gender::MALE);
    Location location;
    location.setLatitude(37.7749);
    location.setLongitude(-122.4194);
    profile1->setLocation(location);
    profile1->setBio("I'm a software engineer and love coding.");
    profile1->addPhoto("photo1.jpg");
    profile1->addPhoto("rohan_photo1.jpg");
    profile1->addInterest("Coding", "Programming");
    profile1->addInterest("Travel", "Lifestyle");
    profile1->addInterest("Music", "Entertainment");

    Preference* pref1 = user1->getPreference();
    pref1->setMinAge(20);
    pref1->setMaxAge(30);
    pref1->addInterestedGender(Gender::MALE);
    pref1->setMaxDistance(50.0);
    pref1->addInterestedGender(Gender::FEMALE);
    pref1->addInterest("Travel");
    pref1->addInterest("Music");
    

    UserProfile* profile2 = user2->getProfile();
    profile2->setName("Jane Doe");
    profile2->setAge(30);
    profile2->setGender(Gender::FEMALE);
    Location location2;
    location2.setLatitude(38.7749);
    location2.setLongitude(-122.6194);
    profile2->setLocation(location2);
    profile2->setBio("I'm a designer and love creating beautiful interfaces.");
    profile2->addPhoto("photo2.jpg");
    profile2->addPhoto("rohan_photo2.jpg");
    profile2->addInterest("Design", "Art");
    profile2->addInterest("Travel", "Lifestyle");
    profile2->addInterest("Music", "Entertainment");

    Preference* pref2 = user2->getPreference();
    pref2->setMinAge(20);
    pref2->setMaxAge(30);
    pref2->addInterestedGender(Gender::FEMALE);
    pref2->setMaxDistance(50.0);
    pref2->addInterestedGender(Gender::MALE);
    pref2->addInterest("Travel");
    pref2->addInterest("Coding");

    // display user profiles
    app->displayUserProfile("user1");
    app->displayUserProfile("user2");

    // find near by users for user1
    cout<<"Nearby users for user1: "<<endl;
    vector<User*> nearByUsers = app->findNearByUsers("user1");
    for (User* user : nearByUsers)
    {
        cout << user->getProfile()->getName() << endl;
    }

    // user1 swipes right on user2
    app->swipe("user1", "user2", SwipeAction::RIGHT);

    // user2 swipes right on user1
    app->swipe("user2", "user1", SwipeAction::RIGHT);

    // send message from user1 to user2
    app->sendMessage("user1", "user2", "Hello, how are you?");

    // send message from user2 to user1
    app->sendMessage("user2", "user1", "Hi, I'm good. How about you?");

    // display chat between user1 and user2
    app->displayChat("user1", "user2");

    return 0;
}