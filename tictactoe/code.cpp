#include<bits/stdc++.h>
using namespace std;

enum GameType{
    STANDARD
};

class Symbol{
    private:
        char mark;
    public:
        Symbol(char symbol){
            this->mark = symbol;
        }

        char getMark(){
            return this->mark;
        }
};

class Board{
    private:
        vector<vector<Symbol*>> grid;
        int size;
        Symbol* emptySymbol;
    public:
        Board(int size){
            this->size = size;
            emptySymbol = new Symbol('_');
            this->grid.resize(size, vector<Symbol*>(size, emptySymbol));
        }

        bool isCellEmpty(int row, int col){
            if(row < 0 || row >= this->size || col < 0 || col >= this->size){
                return false;
            }
            return this->grid[row][col] == emptySymbol;
        }
        bool placeMark(int row, int col, Symbol* symbol){
            if(isCellEmpty(row, col)){
                if(row < 0 || row >= this->size || col < 0 || col >= this->size){
                    return false;
                }
                this->grid[row][col] = symbol;
                return true;
            }
            return false;
        }
        Symbol* getSymbol(int row, int col){
            if(row < 0 || row >= this->size || col < 0 || col >= this->size){
                return nullptr;
            }
            return this->grid[row][col];
        }
        int getSize(){
            return this->size;
        }
        Symbol* getEmptySymbol(){
            return this->emptySymbol;
        }

        void display(){
            for(int i=0; i<this->size; i++){
                for(int j=0; j<this->size; j++){
                    cout<<this->grid[i][j]->getMark()<<" ";
                }
                cout<<endl;
            }
        }
};

class Rules{
    public:
        virtual bool isValidMove(Board* board, int row, int col)=0;
        virtual bool checkWin(Board* board, Symbol* symbol)=0;
        virtual bool checkDraw(Board* board)=0;
        virtual ~Rules(){}
};

class StandardRules: public Rules{
    public:
        bool isValidMove(Board* board, int row, int col){
            return board->isCellEmpty(row, col);
        }
        bool checkWin(Board* board, Symbol* symbol) {
        int size = board->getSize();

        for(int i = 0; i < size; i++) {
            bool win = true;
            for(int j = 0; j < size; j++) {
                if(board->getSymbol(i, j) != symbol) {
                    win = false;
                    break;
                }
            }
            if(win) return true;
        }

        for(int j = 0; j < size; j++) {
            bool win = true;
            for(int i = 0; i < size; i++) {
                if(board->getSymbol(i, j) != symbol) {
                    win = false;
                    break;
                }
            }
            if(win) return true;
        }
        
        bool win = true;
        for(int i = 0; i < size; i++) {
            if(board->getSymbol(i, i) != symbol) {
                win = false;
                break;
            }
        }
        if(win) return true;
        
        win = true;
        for(int i = 0; i < size; i++) {
            if(board->getSymbol(i, size-1-i) != symbol) {
                win = false;
                break;
            }
        }
        return win;
    }

    bool checkDraw(Board* board) {
        int size = board->getSize();
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                if(board->getSymbol(i, j) == board->getEmptySymbol()) {
                    return false;
                }
            }
        }
        return true;
    }
};

class Player{
    private:
        int id;
        string name;
        Symbol* symbol;
        int score;

    public:
        Player(int id, string name, Symbol* symbol){
            this->id = id;
            this->name = name;
            this->symbol = symbol;
            this->score = 0;
        }

        int getId(){
            return this->id;
        }
        string getName(){
            return this->name;
        }
        Symbol* getSymbol(){
            return this->symbol;
        }
        int getScore(){
            return this->score;
        }
        void incrementScore(){
            this->score++;
        }   
};

class Iobserver{
    public:
        virtual void update(string message) = 0;
        virtual ~Iobserver(){}
};

class console: public Iobserver{
    public:
        void update(string message){
            cout<<"Update:"<<message<<endl;
        }
};

class TicTacToeGame{
    private:
        Board* board;
        deque<Player*> players;
        Rules* rules;
        vector<Iobserver*> observers;
        bool gameOver;

    public:
        TicTacToeGame(int size){
            this->board = new Board(size);
            this->rules = new StandardRules();
            this->gameOver = false;
        }
        void addPlayer(Player* player){
            this->players.push_back(player);
        }
        void addObserver(Iobserver* observer){
            this->observers.push_back(observer);
        }

        void notify(string message){
            for(Iobserver* observer : this->observers){
                observer->update(message);
            }
        }

        void play(){
            if(players.size() < 2){
                cout<<"Not enough players"<<endl;
                return;
            }
            notify("Game started");
            while(!gameOver){
                board->display();
                
                Player* player = players.front();
                players.pop_front();
                players.push_back(player);

                int row, col;
                cout<<"Player "<<player->getName()<<" turn"<<endl;
                cout<<"Enter row: ";
                cin>>row;
                cout<<"Enter col: ";
                cin>>col;
                if(rules->isValidMove(board, row, col)){
                    board->placeMark(row, col, player->getSymbol());
                    notify("Player "+player->getName()+" placed mark at "+to_string(row)+", "+to_string(col));

                    if(rules->checkWin(board, player->getSymbol())){
                        notify("Player "+player->getName()+" wins");
                        player->incrementScore();
                        gameOver = true;
                    }
                    else if(rules->checkDraw(board)){
                        notify("Draw");
                        gameOver = true;
                    }
                    else{
                        notify("Next turn");
                    }
                }
                
            }
        }
        ~TicTacToeGame(){
            delete this->board;
            delete this->rules;
        }
};

class GameFactory{
    public:
        static TicTacToeGame* createGame(GameType type,int size){
            if(type == GameType::STANDARD){
                return new TicTacToeGame(size);
            }
            return nullptr;
        }
};

int main(){

    TicTacToeGame* game = GameFactory::createGame(GameType::STANDARD, 3);
    game->addObserver(new console());
    game->addPlayer(new Player(1, "Player 1", new Symbol('X')));
    game->addPlayer(new Player(2, "Player 2", new Symbol('O')));
    game->play();
    return 0;
}