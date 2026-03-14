#include<bits/stdc++.h>
using namespace std;

// Observer Pattern

class NotificationObserver{
    public:
    virtual void update(string message) = 0;
};

class UserNotificationObserver: public NotificationObserver{
    private:
        string userId;
    public:
        UserNotificationObserver(string id): userId(id) {}
        void update(string message){
            cout << "Notification for user " << userId << " received: " << message << endl;
        }
};

class NotificationService{
    private:
        map<string, NotificationObserver*> observers;
        static NotificationService* instance;
        NotificationService(){}
    public:
        static NotificationService* getInstance(){
            if(instance == nullptr){
                instance = new NotificationService();
            }
            return instance;
        }
        void subscribe(string userId, NotificationObserver* observer){
            observers[userId] = observer;
        }
        void unsubscribe(string userId){
            observers.erase(userId);
        }
        void notify(string userId, string message){
            if(observers.find(userId) != observers.end()){
                observers[userId]->update(message);
            }
        }
        void notifyAll(string message){
            for(auto& observer : observers){
                observer.second->update(message);
            }
        }
};
NotificationService* NotificationService::instance = nullptr;

// ENUMs

enum Gender{
    MALE,
    FEMALE,
    OTHER
};

class Location{
    private:
        double latitude;
        double longitude;
    public:
        Location() {
            latitude = 0.0;
            longitude = 0.0;
        }
        Location(double lat, double lon): latitude(lat), longitude(lon) {}
        // Getters
        double getLatitude() { return latitude; }
        double getLongitude() { return longitude; }

        // Setters
        void setLatitude(double lat) { latitude = lat; }
        void setLongitude(double lon) { longitude = lon; }

        // Method to calculate distance between two locations 
        double distanceTo(Location other) {
            
            double lat1 = latitude * M_PI / 180.0;
            double lon1 = longitude * M_PI / 180.0;
            double lat2 = other.latitude * M_PI / 180.0;
            double lon2 = other.longitude * M_PI / 180.0;

            double dlat = lat2 - lat1;
            double dlon = lon2 - lon1;

            double a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
            double c = 2 * atan2(sqrt(a), sqrt(1 - a));
            double R = 6371; // Radius of the Earth in kilometers
            return R * c; // Distance in kilometers
        }
};

class Interest{
    private:
        string name;
        string category;
    public:
        Interest(string n, string c): name(n), category(c) {}
        Interest(): name(""), category("") {}
        // Getters
        string getName() { return name; }
        string getCategory() { return category; }

        // Setters
        void setName(string n) { name = n; }
        void setCategory(string c) { category = c; }
};

class Preference{
    private:
        int minAge;
        int maxAge;
        vector<Gender> InterestedGenders;
        double maxDistance; // in kilometers
        vector<string> intersts;

    public:
        Preference(): minAge(18), maxAge(100), maxDistance(100) {}
        Preference(int minA, int maxA, double maxD): minAge(minA), maxAge(maxA), maxDistance(maxD) {}

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
        void removeInterestedGender(Gender g) {
            InterestedGenders.erase(remove(InterestedGenders.begin(), InterestedGenders.end(), g), InterestedGenders.end());
        }
        void removeInterest(string interest) {
            intersts.erase(remove(intersts.begin(), intersts.end(), interest), intersts.end());
        }
        
        bool isInterestedInGender(Gender g) {
            return find(InterestedGenders.begin(), InterestedGenders.end(), g) != InterestedGenders.end();
        }
        bool isInterestedInInterest(string interest) {
            return find(intersts.begin(), intersts.end(), interest) != intersts.end();
        }

        bool isWithinAgeRange(int age) {
            return age >= minAge && age <= maxAge;
        }

        bool isWithinDistance(double distance) {
            return distance <= maxDistance;
        }

};

class Message{
    private:
        string senderId;
        string receiverId;
        string content;
        time_t timestamp;

    public:
        Message(string sender, string receiver, string content): senderId(sender), receiverId(receiver), content(content) {
            timestamp = time(0);
        }
        // Getters
        string getSenderId() { return senderId; }
        string getReceiverId() { return receiverId; }
        string getContent() { return content; }
        time_t getTimestamp() { return timestamp; }

        string getFormattedTimestamp() {
            char buffer[80];
            struct tm * timeinfo = localtime(&timestamp);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
            return string(buffer);
        }

        // Setters
        void setSenderId(string sender) { senderId = sender; }
        void setReceiverId(string receiver) { receiverId = receiver; }
        void setContent(string content) { this->content = content; }
        void setTimestamp(time_t timestamp) { this->timestamp = timestamp; }

};

class ChatRoom{
    private:
        string id;
        vector<string> participantIds;
        vector<Message*> messages;
    public:
        ChatRoom(string roomId, string userId1, string userId2): id(roomId) {
            participantIds.push_back(userId1);
            participantIds.push_back(userId2);
        }

        ~ChatRoom() {
            for(Message* msg : messages) {
                delete msg;
            }
        }

        string getId() { return id; }
        vector<string> getParticipantIds() { return participantIds; }
        vector<Message*> getMessages() { return messages; }

        void addMessage(string senderId, string receiverId, string content) {
            Message* newMessage = new Message(senderId, receiverId, content);
            messages.push_back(newMessage);
        }

        bool isParticipant(string userId) {
            return find(participantIds.begin(), participantIds.end(), userId) != participantIds.end();
        }

        void removeParticipant(string userId) {
            participantIds.erase(remove(participantIds.begin(), participantIds.end(), userId), participantIds.end());
        }

        void displayChat(){
            cout << "Chat Room ID: " << id << endl;
            for(Message* msg : messages) {
                cout << "[" << msg->getFormattedTimestamp() << "] " << msg->getSenderId() << " to " << msg->getReceiverId() << ": " << msg->getContent() << endl;
            }
            cout<<"-----------------------------" << endl;
        }
};

int main(){
    return 0;
}