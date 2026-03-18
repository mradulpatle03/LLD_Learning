#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

class IGameObserver {
public:
    virtual void onNotify(string message) = 0;
    virtual ~IGameObserver() {}
};

class ConsoleLogger : public IGameObserver {
public:
    void onNotify(string message) override {
        cout << "[NOTIFICATION] " << message << endl;
    }
};

class GameDice {
private:
    int sideCount;
    
public:
    GameDice(int sides) {
        sideCount = sides;
        srand(time(0));
    }
    
    int rollDice() {
        return (rand() % sideCount) + 1;
    }
};

class BoardElement {
protected:
    int headPos;
    int tailPos;
    
public:
    BoardElement(int start, int end) : headPos(start), tailPos(end) {}
    
    int getHead() { return headPos; }
    int getTail() { return tailPos; }
    
    virtual void printDetails() = 0;
    virtual string getTypeName() = 0;
    virtual ~BoardElement() {}
};

class ObstacleSnake : public BoardElement {
public:
    ObstacleSnake(int start, int end) : BoardElement(start, end) {
        if(end >= start) {
            cout << "Invalid snake! End must be less than start." << endl;
        }
    }
    
    void printDetails() override {
        cout << "Snake: " << headPos << " -> " << tailPos << endl;
    }

    string getTypeName() override {
        return "SNAKE";
    }
};

class AssetLadder : public BoardElement {
public:
    AssetLadder(int start, int end) : BoardElement(start, end) {
        if(end <= start) {
            cout << "Invalid ladder! End must be greater than start." << endl;
        }
    }
    
    void printDetails() override {
        cout << "Ladder: " << headPos << " -> " << tailPos << endl;
    }

    string getTypeName() override {
        return "LADDER";
    }
};

class IBoardLayoutStrategy;

class GameBoard {
private:
    int totalCells;
    vector<BoardElement*> elementList;
    map<int, BoardElement*> jumpMap;
    
public:
    GameBoard(int dimension) {
        totalCells = dimension * dimension;
    }
    
    bool isCellAvailable(int index) {
        return jumpMap.find(index) == jumpMap.end();
    }
    
    void registerElement(BoardElement* element) {
        if(isCellAvailable(element->getHead())) {
            elementList.push_back(element);
            jumpMap[element->getHead()] = element;
        }
    }
    
    void initialize(IBoardLayoutStrategy* strategy);
    
    BoardElement* findElementAt(int index) {
        if(jumpMap.find(index) != jumpMap.end()) {
            return jumpMap[index];
        }
        return nullptr;
    }
    
    int getSize() { return totalCells; }
    
    void render() {
        cout << "\n=== Board Configuration ===" << endl;
        cout << "Board Size: " << totalCells << " cells" << endl;

        int sCount = 0;
        int lCount = 0;
        for(auto item : elementList) {
            if(item->getTypeName() == "SNAKE") sCount++;
            else lCount++;
        }
        
        cout << "\nSnakes: " << sCount << endl;
        for(auto item : elementList) {
            if(item->getTypeName() == "SNAKE") item->printDetails();
        }
        
        cout << "\nLadders: " << lCount << endl;
        for(auto item : elementList) {
            if(item->getTypeName() == "LADDER") item->printDetails();
        }
        cout << "=========================" << endl;
    }
    
    ~GameBoard() {
        for(auto item : elementList) {
            delete item;
        }
    }
};

class IBoardLayoutStrategy {
public:
    virtual void applyLayout(GameBoard* board) = 0;
    virtual ~IBoardLayoutStrategy() {}
};

class ProceduralLayout : public IBoardLayoutStrategy {
public:
    enum Intensity { EASY_MODE, MEDIUM_MODE, HARD_MODE };
    
private:
    Intensity mode;
    
    void generateWithWeight(GameBoard* board, double snakeWeight) {
        int limit = board->getSize();
        int targetCount = limit / 10;
        
        for(int i = 0; i < targetCount; i++) {
            double roll = (double)rand() / RAND_MAX;
            
            if(roll < snakeWeight) {
                int retries = 0;
                while(retries < 50) {
                    int start = rand() % (limit - 10) + 10;
                    int end = rand() % (start - 1) + 1;
                    if(board->isCellAvailable(start)) {
                        board->registerElement(new ObstacleSnake(start, end));
                        break;
                    }
                    retries++;
                }
            } else {
                int retries = 0;
                while(retries < 50) {
                    int start = rand() % (limit - 10) + 1;
                    int end = rand() % (limit - start) + start + 1;
                    if(board->isCellAvailable(start) && end < limit) {
                        board->registerElement(new AssetLadder(start, end));
                        break;
                    }
                    retries++;
                }
            }
        }
    }
    
public:
    ProceduralLayout(Intensity i) : mode(i) {}
    
    void applyLayout(GameBoard* board) override {
        if (mode == EASY_MODE) generateWithWeight(board, 0.3);
        else if (mode == MEDIUM_MODE) generateWithWeight(board, 0.5);
        else if (mode == HARD_MODE) generateWithWeight(board, 0.7);
    }
};

class ManualLayout : public IBoardLayoutStrategy {
private:
    int sQty, lQty;
    bool isRandomized;
    vector<pair<int, int>> sCoords, lCoords;
    
public:
    ManualLayout(int s, int l, bool randPos) : sQty(s), lQty(l), isRandomized(randPos) {}
    
    void defineSnake(int s, int e) { sCoords.push_back({s, e}); }
    void defineLadder(int s, int e) { lCoords.push_back({s, e}); }
    
    void applyLayout(GameBoard* board) override {
        int limit = board->getSize();
        if(isRandomized) {
            int sDone = 0;
            while(sDone < sQty) {
                int start = rand() % (limit - 10) + 10;
                int end = rand() % (start - 1) + 1;
                if(board->isCellAvailable(start)) {
                    board->registerElement(new ObstacleSnake(start, end));
                    sDone++;
                }
            }
            int lDone = 0;
            while(lDone < lQty) {
                int start = rand() % (limit - 10) + 1;
                int end = rand() % (limit - start) + start + 1;
                if(board->isCellAvailable(start) && end < limit) {
                    board->registerElement(new AssetLadder(start, end));
                    lDone++;
                }
            }
        } else {
            for(auto& p : sCoords) if(board->isCellAvailable(p.first)) board->registerElement(new ObstacleSnake(p.first, p.second));
            for(auto& p : lCoords) if(board->isCellAvailable(p.first)) board->registerElement(new AssetLadder(p.first, p.second));
        }
    }
};

class ClassicLayout : public IBoardLayoutStrategy {
public:
    void applyLayout(GameBoard* board) override {
        if(board->getSize() != 100) return;
        board->registerElement(new ObstacleSnake(99, 54));
        board->registerElement(new ObstacleSnake(62, 19));
        board->registerElement(new AssetLadder(2, 38));
        board->registerElement(new AssetLadder(21, 42));
    }
};

void GameBoard::initialize(IBoardLayoutStrategy* strategy) {
    strategy->applyLayout(this);
}

class Participant {
private:
    int id;
    string displayName;
    int currentIdx;
    int points;
    
public:
    Participant(int pId, string n) : id(pId), displayName(n), currentIdx(0), points(0) {}
    
    string getName() { return displayName; }
    int getIdx() { return currentIdx; }
    void updateIdx(int val) { currentIdx = val; }
    void addPoint() { points++; }
};

class IGameRules {
public:
    virtual bool canMove(int pos, int roll, int max) = 0;
    virtual int getDestination(int pos, int roll, GameBoard* board) = 0;
    virtual bool hasWon(int pos, int max) = 0;
    virtual ~IGameRules() {}
};

class DefaultRules : public IGameRules {
public:
    bool canMove(int pos, int roll, int max) override { return (pos + roll) <= max; }
    int getDestination(int pos, int roll, GameBoard* board) override {
        int next = pos + roll;
        BoardElement* obj = board->findElementAt(next);
        return obj ? obj->getTail() : next;
    }
    bool hasWon(int pos, int max) override { return pos == max; }
};

class MatchEngine {
private:
    GameBoard* mapRef;
    GameDice* diceRef;
    deque<Participant*> roster;
    IGameRules* logic;
    vector<IGameObserver*> listeners;
    bool isFinished;
    
public:
    MatchEngine(GameBoard* m, GameDice* d) : mapRef(m), diceRef(d), isFinished(false) {
        logic = new DefaultRules();
    }
    
    void enroll(Participant* p) { roster.push_back(p); }
    void attach(IGameObserver* o) { listeners.push_back(o); }

    void broadcast(string m) {
        for(auto l : listeners) l->onNotify(m);
    }
    
    void run() {
        if(roster.size() < 2) return;
        broadcast("Session Started");
        mapRef->render();
        
        while(!isFinished) {
            Participant* active = roster.front();
            cout << "\n" << active->getName() << "'s turn. [Enter]";
            cin.ignore(); cin.get();
            
            int val = diceRef->rollDice();
            cout << "Value: " << val << endl;
            
            int now = active->getIdx();
            if(logic->canMove(now, val, mapRef->getSize())) {
                int mid = now + val;
                int fin = logic->getDestination(now, val, mapRef);
                active->updateIdx(fin);
                
                BoardElement* encounter = mapRef->findElementAt(mid);
                if(encounter) {
                    broadcast(active->getName() + " hit " + encounter->getTypeName());
                }
                
                broadcast(active->getName() + " at " + to_string(fin));
                
                if(logic->hasWon(fin, mapRef->getSize())) {
                    cout << active->getName() << " Wins!" << endl;
                    active->addPoint();
                    isFinished = true;
                } else {
                    roster.pop_front();
                    roster.push_back(active);
                }
            } else {
                roster.pop_front();
                roster.push_back(active);
            }
        }
    }
    
    ~MatchEngine() { delete logic; }
};

class GameFactory {
public:
    static MatchEngine* buildStandard() {
        GameBoard* b = new GameBoard(10);
        ClassicLayout strategy;
        b->initialize(&strategy);
        return new MatchEngine(b, new GameDice(6));
    }
};

int main() {
    MatchEngine* session = GameFactory::buildStandard();
    ConsoleLogger* logger = new ConsoleLogger();
    session->attach(logger);
    
    session->enroll(new Participant(1, "Alpha"));
    session->enroll(new Participant(2, "Bravo"));
    
    session->run();
    
    delete session;
    delete logger;
    return 0;
}