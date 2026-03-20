#include <bits/stdc++.h>
using namespace std;

enum PieceType
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum Color
{
    WHITE,
    BLACK
};

enum GameStatus
{
    WAITING,
    IN_PROGRESS,
    COMPLETED,
    ABORTED
};

class Position
{
private:
    int x;
    int y;

public:
    Position() : x(0), y(0) {}
    Position(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    bool isValid()
    {
        return x >= 0 && x <= 7 && y >= 0 && y <= 7;
    }
    bool operator==(const Position &other) const
    {
        return x == other.x && y == other.y;
    }
    bool operator<(const Position &other) const
    {
        return x < other.x || (x == other.x && y < other.y);
    }
    string toString()
    {
        return "(" + to_string(x) + "," + to_string(y) + ")";
    }
    // this will show in form of chess notation like a1, b2 etc
    string toChessNotation()
    {
        string letters = "abcdefgh";
        return letters[x] + to_string(8 - y);
    }
};

class Piece;

class Move
{
private:
    Position from;
    Position to;
    Piece *piece;
    Piece *capturedPiece;

public:
    Move() : from(Position()), to(Position()), piece(nullptr), capturedPiece(nullptr) {}
    Move(Position from, Position to, Piece *piece, Piece *capturedPiece)
    {
        this->from = from;
        this->to = to;
        this->piece = piece;
        this->capturedPiece = capturedPiece;
    }

    // getters
    Position getFrom()
    {
        return from;
    }
    Position getTo()
    {
        return to;
    }
    Piece *getPiece()
    {
        return piece;
    }
    Piece *getCapturedPiece()
    {
        return capturedPiece;
    }
};

class Board;

class Piece
{
private:
    PieceType type;
    Color color;
    bool hasMoved;

public:
    Piece(PieceType type, Color color)
    {
        this->type = type;
        this->color = color;
        this->hasMoved = false;
    }

    // getters
    PieceType getType()
    {
        return type;
    }
    Color getColor()
    {
        return color;
    }
    bool getHasMoved()
    {
        return hasMoved;
    }
    void setMoved()
    {
        hasMoved = true;
    }

    virtual vector<Position> getValidMoves(Position currPosition, Board *board) = 0;
    virtual string getSymbol() = 0;

    string toString()
    {
        string color = this->color == WHITE ? "W" : "B";
        return color + " " + this->getSymbol();
    }
};

class King : public Piece
{
public:
    King(Color color) : Piece(KING, color) {}

    vector<Position> getValidMoves(Position currPosition, Board *board);
    string getSymbol()
    {
        return "K";
    }
};
class Queen : public Piece
{
public:
    Queen(Color color) : Piece(QUEEN, color) {}

    vector<Position> getValidMoves(Position currPosition, Board *board);
    string getSymbol()
    {
        return "Q";
    }
};

class Knight : public Piece
{
public:
    Knight(Color color) : Piece(KNIGHT, color) {}

    vector<Position> getValidMoves(Position currPosition, Board *board);
    string getSymbol()
    {
        return "N";
    }
};

class Rook : public Piece
{
public:
    Rook(Color color) : Piece(ROOK, color) {}

    vector<Position> getValidMoves(Position currPosition, Board *board);
    string getSymbol()
    {
        return "R";
    }
};

class Bishop : public Piece
{
public:
    Bishop(Color color) : Piece(BISHOP, color) {}

    vector<Position> getValidMoves(Position currPosition, Board *board);
    string getSymbol()
    {
        return "B";
    }
};

class Pawn : public Piece
{
public:
    Pawn(Color color) : Piece(PAWN, color) {}

    vector<Position> getValidMoves(Position currPosition, Board *board);
    string getSymbol()
    {
        return "P";
    }
};

class PieceFactory
{
public:
    static Piece *createPiece(PieceType type, Color color)
    {
        switch (type)
        {
        case PAWN:
            return new Pawn(color);
        case KNIGHT:
            return new Knight(color);
        case BISHOP:
            return new Bishop(color);
        case ROOK:
            return new Rook(color);
        case QUEEN:
            return new Queen(color);
        case KING:
            return new King(color);
        default:
            return nullptr;
        }
    }
};

class Board
{
private:
    Piece *board[8][8];
    map<Position, Piece *> piecePositions;

public:
    Board()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                board[i][j] = nullptr;
            }
        }
    }

    ~Board()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j] != nullptr)
                {
                    delete board[i][j];
                }
            }
        }
    }

    void InitializeBoard()
    {
        placePiece(Position(7, 0), PieceFactory::createPiece(ROOK, WHITE));
        placePiece(Position(7, 1), PieceFactory::createPiece(KNIGHT, WHITE));
        placePiece(Position(7, 2), PieceFactory::createPiece(BISHOP, WHITE));
        placePiece(Position(7, 3), PieceFactory::createPiece(QUEEN, WHITE));
        placePiece(Position(7, 4), PieceFactory::createPiece(KING, WHITE));
        placePiece(Position(7, 5), PieceFactory::createPiece(BISHOP, WHITE));
        placePiece(Position(7, 6), PieceFactory::createPiece(KNIGHT, WHITE));
        placePiece(Position(7, 7), PieceFactory::createPiece(ROOK, WHITE));

        for (int i = 0; i < 8; i++)
        {
            placePiece(Position(6, i), PieceFactory::createPiece(PAWN, WHITE));
        }

        placePiece(Position(0, 0), PieceFactory::createPiece(ROOK, BLACK));
        placePiece(Position(0, 1), PieceFactory::createPiece(KNIGHT, BLACK));
        placePiece(Position(0, 2), PieceFactory::createPiece(BISHOP, BLACK));
        placePiece(Position(0, 3), PieceFactory::createPiece(QUEEN, BLACK));
        placePiece(Position(0, 4), PieceFactory::createPiece(KING, BLACK));
        placePiece(Position(0, 5), PieceFactory::createPiece(BISHOP, BLACK));
        placePiece(Position(0, 6), PieceFactory::createPiece(KNIGHT, BLACK));
        placePiece(Position(0, 7), PieceFactory::createPiece(ROOK, BLACK));

        for (int i = 0; i < 8; i++)
        {
            placePiece(Position(1, i), PieceFactory::createPiece(PAWN, BLACK));
        }
    }

    void placePiece(Position position, Piece *piece)
    {
        board[position.getX()][position.getY()] = piece;
        piecePositions[position] = piece;
    }

    void removePiece(Position position)
    {
        board[position.getX()][position.getY()] = nullptr;
        piecePositions.erase(position);
    }

    Piece *getPiece(Position position)
    {
        return board[position.getX()][position.getY()];
    }

    bool isPositionOccupied(Position position)
    {
        return board[position.getX()][position.getY()] != nullptr;
    }

    bool isOccupiedByColor(Position position, Color color)
    {
        return board[position.getX()][position.getY()] != nullptr && board[position.getX()][position.getY()]->getColor() == color;
    }

    void movePiece(Position from, Position to)
    {
        Piece *piece = getPiece(from);
        if (piece == nullptr)
        {
            return;
        }
        Piece *capturedPiece = getPiece(to);
        if (capturedPiece != nullptr)
        {
            removePiece(to);
            delete capturedPiece;
        }
        removePiece(from);
        placePiece(to, piece);

        piece->setMoved();
    }

    Position findking(Color color)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j] != nullptr && board[i][j]->getType() == KING && board[i][j]->getColor() == color)
                {
                    return Position(i, j);
                }
            }
        }
        return Position(-1, -1);
    }

    vector<Position> getAllPieces(Color color)
    {
        vector<Position> positions;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j] != nullptr && board[i][j]->getColor() == color)
                {
                    positions.push_back(Position(i, j));
                }
            }
        }
        return positions;
    }

    void displayBoard()
    {
        // print chess board with pieces, color, and borders
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j] != nullptr)
                {
                    cout << board[i][j]->toString() << " ";
                }
                else
                {
                    cout << "  ";
                }
            }
            cout << endl;
        }
    }
};

vector<Position> King::getValidMoves(Position currPosition, Board *board)
{
    vector<Position> validMoves;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            int x = currPosition.getX() + i;
            int y = currPosition.getY() + j;
            if (x >= 0 && x < 8 && y >= 0 && y < 8 && board->isPositionOccupied(Position(x, y)) == false)
            {
                validMoves.push_back(Position(x, y));
            }
        }
    }
    return validMoves;
}

vector<Position> Queen::getValidMoves(Position currPosition, Board *board)
{
    vector<Position> moves;
    int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (int d = 0; d < 8; d++)
    {
        for (int i = 1; i < 8; i++)
        {
            Position newPos(currPosition.getX() + directions[d][0] * i, currPosition.getY() + directions[d][1] * i);
            if (!newPos.isValid())
                break;

            if (board->isOccupiedByColor(newPos, this->getColor()))
                break;

            moves.push_back(newPos);
            if (board->isPositionOccupied(newPos))
                break;
        }
    }
    return moves;
}

vector<Position> Bishop::getValidMoves(Position currPosition, Board *board)
{
    vector<Position> moves;
    int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    for (int d = 0; d < 4; d++)
    {
        for (int i = 1; i < 8; i++)
        {
            Position newPos(currPosition.getX() + directions[d][0] * i, currPosition.getY() + directions[d][1] * i);
            if (!newPos.isValid())
                break;

            if (board->isOccupiedByColor(newPos, this->getColor()))
                break;

            moves.push_back(newPos);
            if (board->isPositionOccupied(newPos))
                break;
        }
    }
    return moves;
}

vector<Position> Rook::getValidMoves(Position currPosition, Board *board)
{
    vector<Position> moves;
    int directions[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

    for (int d = 0; d < 4; d++)
    {
        for (int i = 1; i < 8; i++)
        {
            Position newPos(currPosition.getX() + directions[d][0] * i, currPosition.getY() + directions[d][1] * i);
            if (!newPos.isValid())
                break;

            if (board->isOccupiedByColor(newPos, this->getColor()))
                break;

            moves.push_back(newPos);
            if (board->isPositionOccupied(newPos))
                break;
        }
    }
    return moves;
}

vector<Position> Knight::getValidMoves(Position currPosition, Board *board)
{
    vector<Position> moves;
    int directions[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    for (int d = 0; d < 8; d++)
    {
        Position newPos(currPosition.getX() + directions[d][0], currPosition.getY() + directions[d][1]);
        if (!newPos.isValid())
            continue;

        if (board->isOccupiedByColor(newPos, this->getColor()))
            continue;

        moves.push_back(newPos);
    }
    return moves;
}

vector<Position> Pawn::getValidMoves(Position currPosition, Board *board)
{
    vector<Position> moves;
    int direction = (this->getColor() == WHITE) ? -1 : 1;

    // Forward move
    Position oneStep(currPosition.getX() + direction, currPosition.getY());
    if (oneStep.isValid() && !board->isPositionOccupied(oneStep))
    {
        moves.push_back(oneStep);

        // Double move from starting position
        if (!getHasMoved())
        {
            Position twoStep(currPosition.getX() + 2 * direction, currPosition.getY());
            if (twoStep.isValid() && !board->isPositionOccupied(twoStep))
            {
                moves.push_back(twoStep);
            }
        }
    }

    // Diagonal captures
    Position leftCapture(currPosition.getX() + direction, currPosition.getY() - 1);
    Position rightCapture(currPosition.getX() + direction, currPosition.getY() + 1);

    if (leftCapture.isValid() && board->isPositionOccupied(leftCapture) &&
        !board->isOccupiedByColor(leftCapture, this->getColor()))
    {
        moves.push_back(leftCapture);
    }

    if (rightCapture.isValid() && board->isPositionOccupied(rightCapture) &&
        !board->isOccupiedByColor(rightCapture, this->getColor()))
    {
        moves.push_back(rightCapture);
    }

    return moves;
}

class ChessRules
{
public:
    virtual ~ChessRules() {}
    virtual bool isValidMove(Move move, Board *board) = 0;
    virtual bool isInCheck(Color color, Board *board) = 0;
    virtual bool isCheckmate(Color color, Board *board) = 0;
    virtual bool isStalemate(Color color, Board *board) = 0;
    virtual bool wouldMoveCauseCheck(Move move, Board *board, Color kingColor) = 0;
};

class StandardChessRules : public ChessRules
{
public:
    bool isValidMove(Move move, Board *board) override
    {
        Piece *piece = move.getPiece();
        vector<Position> possibleMoves = piece->getValidMoves(move.getFrom(), board);

        // Check if the target position is in possible moves
        bool validDestination = false;
        for (const Position &pos : possibleMoves)
        {
            if (pos == move.getTo())
            {
                validDestination = true;
                break;
            }
        }

        if (!validDestination)
        {
            return false;
        }

        // Check if move would put own king in check
        return !wouldMoveCauseCheck(move, board, piece->getColor());
    }

    bool wouldMoveCauseCheck(Move move, Board *board, Color kingColor) override
    {
        // Create a temporary copy to simulate the move safely
        Piece *movingPiece = board->getPiece(move.getFrom());
        Piece *capturedPiece = board->getPiece(move.getTo());

        if (movingPiece == nullptr)
            return true; // Invalid move

        // Temporarily execute the move
        board->removePiece(move.getFrom());
        if (capturedPiece != nullptr)
        {
            board->removePiece(move.getTo());
        }
        board->placePiece(move.getTo(), movingPiece);

        // Check if king is in check after the move
        bool inCheck = isInCheck(kingColor, board);

        // Undo the move
        board->removePiece(move.getTo());
        board->placePiece(move.getFrom(), movingPiece);
        if (capturedPiece != nullptr)
        {
            board->placePiece(move.getTo(), capturedPiece);
        }

        return inCheck;
    }

    bool isInCheck(Color color, Board *board) override
    {
        Position kingPos = board->findking(color);
        if (kingPos.getX() == -1)
            return false; // King not found

        Color opponentColor = (color == WHITE) ? BLACK : WHITE;
        vector<Position> opponentPieces = board->getAllPieces(opponentColor);

        for (const Position &pos : opponentPieces)
        {
            Piece *piece = board->getPiece(pos);
            vector<Position> moves = piece->getValidMoves(pos, board);
            for (const Position &targetPos : moves)
            {
                if (targetPos == kingPos)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool isCheckmate(Color color, Board *board) override
    {
        if (!isInCheck(color, board))
            return false;

        vector<Position> pieces = board->getAllPieces(color);
        for (const Position &pos : pieces)
        {
            Piece *piece = board->getPiece(pos);
            vector<Position> moves = piece->getValidMoves(pos, board);

            for (const Position &targetPos : moves)
            {
                Move move(pos, targetPos, piece, board->getPiece(targetPos));
                if (isValidMove(move, board))
                {
                    return false; // Found a valid move, not checkmate
                }
            }
        }
        return true;
    }

    bool isStalemate(Color color, Board *board) override
    {
        if (isInCheck(color, board))
            return false;

        vector<Position> pieces = board->getAllPieces(color);
        for (const Position &pos : pieces)
        {
            Piece *piece = board->getPiece(pos);
            vector<Position> moves = piece->getValidMoves(pos, board);

            for (const Position &targetPos : moves)
            {
                Move move(pos, targetPos, piece, board->getPiece(targetPos));
                if (isValidMove(move, board))
                {
                    return false; // Found a valid move, not stalemate
                }
            }
        }
        return true;
    }
};

class Message
{
private:
    string message;
    string sender;
    time_t timestamp;

public:
    Message(string message, string sender)
    {
        this->message = message;
        this->sender = sender;
        this->timestamp = time(0);
    }

    string getMessage()
    {
        return message;
    }

    string getSender()
    {
        return sender;
    }

    time_t getTimestamp()
    {
        return timestamp;
    }
    string toString()
    {
        return "Message: " + message + " from " + sender + " at " + ctime(&timestamp);
    }
};

class User;

class chatMediator
{
public:
    virtual ~chatMediator() {}
    virtual void sendMessage(Message *message, User *user) = 0;
    virtual void addUser(User *user) = 0;
    virtual void removeUser(User *user) = 0;
};

class Colleage
{
private:
    chatMediator *mediator;

public:
    Colleage() : mediator(nullptr) {}
    virtual ~Colleage() {}
    virtual void sendMessage(Message *message) = 0;
    virtual void receiveMessage(Message *message) = 0;
    virtual void setMediator(chatMediator *mediator)
    {
        this->mediator = mediator;
    }

    // getter
    chatMediator *getMediator()
    {
        return mediator;
    }
};

class User : public Colleage
{
private:
    string id;
    string name;
    int score;

public:
    User(string userId, string userName) : Colleage()
    {
        this->id = userId;
        this->name = userName;
        this->score = 1000;
    }

    string getId()
    {
        return id;
    }

    string getName()
    {
        return name;
    }

    int getScore()
    {
        return score;
    }

    void increaseScore(int score)
    {
        this->score += score;
    }

    void decreaseScore(int score)
    {
        this->score -= score;
    }

    string toString()
    {
        return "User: " + id + " Name: " + name + " Score: " + to_string(score);
    }

    void sendMessage(Message *message)
    {
        this->getMediator()->sendMessage(message, this);
    }

    void receiveMessage(Message *message)
    {
        cout << message->toString() << endl;
    }
};

class Match : public chatMediator
{
private:
    string matchId;
    User *whitePlayer;
    User *blackPlayer;
    Board *board;
    ChessRules *rules;
    Color currentTurn;
    GameStatus status;
    vector<Move> moveHistory;
    vector<Message *> chatHistory;

public:
    Match(string mId, User *white, User *black)
    {
        matchId = mId;
        whitePlayer = white;
        blackPlayer = black;
        board = new Board();
        rules = new StandardChessRules();
        currentTurn = WHITE;
        status = IN_PROGRESS;

        // Set mediator for both users
        whitePlayer->setMediator(this);
        blackPlayer->setMediator(this);

        cout << "Match started between " << whitePlayer->getName() << " (White) and "
             << blackPlayer->getName() << " (Black)" << endl;
    }

    ~Match()
    {
        delete board;
        delete rules;
    }

    bool makeMove(Position from, Position to, User *player)
    {
        if (status != IN_PROGRESS)
        {
            cout << "Game is not in progress!" << endl;
            return false;
        }

        Color playerColor = getPlayerColor(player);
        if (playerColor != currentTurn)
        {
            cout << "It's not your turn!" << endl;
            return false;
        }

        Piece *piece = board->getPiece(from);
        if (piece == nullptr || piece->getColor() != playerColor)
        {
            cout << "Invalid piece selection!" << endl;
            return false;
        }

        Move move(from, to, piece, board->getPiece(to));

        if (!rules->isValidMove(move, board))
        {
            cout << "Invalid move!" << endl;
            return false;
        }

        // Execute move
        board->movePiece(from, to);
        moveHistory.push_back(move);

        cout << player->getName() << " moved " << piece->getSymbol()
             << " from " << from.toChessNotation() << " to " << to.toChessNotation() << endl;

        board->displayBoard();

        // Check game end conditions
        Color opponentColor = (currentTurn == WHITE) ? BLACK : WHITE;
        if (rules->isCheckmate(opponentColor, board))
        {
            endGame(player, "checkmate");
            return true;
        }
        else if (rules->isStalemate(opponentColor, board))
        {
            endGame(player, "stalemate");
            return true;
        }
        else
        {
            currentTurn = opponentColor;
            if (rules->isInCheck(opponentColor, board))
            {
                cout << getPlayerByColor(opponentColor)->getName() << " is in check!" << endl;
            }
        }

        return true;
    }

    void quitGame(User *player)
    {
        User *opponent = (player == whitePlayer) ? blackPlayer : whitePlayer;
        endGame(opponent, "quit");
        player->decreaseScore(50); // Penalty for quitting
        cout << player->getName() << " quit the game. Score decreased by 50." << endl;
    }

    void endGame(User *winner, string reason)
    {
        status = COMPLETED;

        if (winner != nullptr)
        {
            User *loser = (winner == whitePlayer) ? blackPlayer : whitePlayer;
            winner->increaseScore(30);
            loser->decreaseScore(20);
            cout << "Game ended - " << winner->getName() << " wins by " << reason << "!" << endl;
            cout << "Score update: " << winner->getName() << " +30, " << loser->getName() << " -20" << endl;
        }
        else
        {
            cout << "Game ended in " << reason << "! No score change." << endl;
        }
    }

    Color getPlayerColor(User *player)
    {
        return (player == whitePlayer) ? WHITE : BLACK;
    }

    User *getPlayerByColor(Color color)
    {
        return (color == WHITE) ? whitePlayer : blackPlayer;
    }

    // Mediator Pattern implementation
    void sendMessage(Message *message, User *user) override
    {
        chatHistory.push_back(message);

        User *recipient = (user == whitePlayer) ? blackPlayer : whitePlayer;
        recipient->sendMessage(message);
        cout << "Chat in match " << matchId << " - " << message->getMessage() << endl;
    }

    void addUser(User *user) override
    {
        // Not applicable for chess match (always 2 users)
    }

    void removeUser(User *user) override
    {
        quitGame(user);
    }

    string getMatchId() const
    {
        return matchId;
    }
    GameStatus getStatus() const
    {
        return status;
    }
    User *getWhitePlayer() const
    {
        return whitePlayer;
    }
    User *getBlackPlayer() const
    {
        return blackPlayer;
    }
    Board *getBoard() const
    {
        return board;
    }
};

class MatchingStrategy {
public:
    virtual ~MatchingStrategy() {}
    virtual User* findMatch(User* user, vector<User*>& waitingUsers) = 0;
};

// Score-based matching strategy
class ScoreBasedMatching : public MatchingStrategy {
private:
    int scoreTolerance;

public:
    ScoreBasedMatching(int tolerance) {
        scoreTolerance = tolerance;
    }
    
    User* findMatch(User* user, vector<User*>& waitingUsers) override {
        User* bestMatch = nullptr;
        int bestScoreDiff = INT_MAX;
        
        for (User* waitingUser : waitingUsers) {
            if (waitingUser->getId() != user->getId()) {
                int scoreDiff = abs(waitingUser->getScore() - user->getScore());
                if (scoreDiff <= scoreTolerance && scoreDiff < bestScoreDiff) {
                    bestMatch = waitingUser;
                    bestScoreDiff = scoreDiff;
                }
            }
        }
        return bestMatch;
    }
};

// Game Manager - Singleton Pattern
class GameManager {
private:
    static GameManager* instance;
    map<string, Match*> activeMatches; // matchId --> Match
    vector<User*> waitingUsers;
    MatchingStrategy* matchingStrategy;
    int matchCounter;
    
    GameManager() {
        matchingStrategy = new ScoreBasedMatching(100); // 100 points tolerance
        matchCounter = 0;
    }

public:
    static GameManager* getInstance() {
        if (instance == nullptr) {
            instance = new GameManager();
        }
        return instance;
    }
    
    ~GameManager() {
        delete matchingStrategy;
        for (auto& pair : activeMatches) {
            delete pair.second;
        }
    }
    
    void requestMatch(User* user) {
        cout << user->getName() << " is looking for a match..." << endl;
        
        User* opponent = matchingStrategy->findMatch(user, waitingUsers);
        
        if (opponent != nullptr) {
            // Remove opponent from waiting list
            waitingUsers.erase(remove(waitingUsers.begin(), waitingUsers.end(), opponent), waitingUsers.end());
            
            string matchId = "MATCH_" + to_string(++matchCounter);
            Match* match = new Match(matchId, user, opponent);
            activeMatches[matchId] = match;
            
            cout << "Match found! " << user->getName() << " vs " << opponent->getName() << endl;
            match->getBoard()->displayBoard();
        } 
        else {
            waitingUsers.push_back(user);
            cout << user->getName() << " added to waiting list." << endl;
        }
    }
    
    void makeMove(string matchId, Position from, Position to, User* player) {
        if (activeMatches.find(matchId) != activeMatches.end()) {
            Match* match = activeMatches[matchId];
            match->makeMove(from, to, player);
            
            if (match->getStatus() == COMPLETED) {
                delete match;
                activeMatches.erase(matchId);
                cout << "Match " << matchId << " completed and removed from active matches." << endl;
            }
        }
    }
    
    void quitMatch(string matchId, User* player) {
        if (activeMatches.find(matchId) != activeMatches.end()) {
            Match* match = activeMatches[matchId];
            match->quitGame(player);
            delete match;
            activeMatches.erase(matchId);
        }
    }
    
    void sendChatMessage(string matchId, string message, User* user) {
        if (activeMatches.find(matchId) != activeMatches.end()) {
            Match* match = activeMatches[matchId];
            Message* msg = new Message(user->getId(), message);
            match->sendMessage(msg, user);
        }
    }
    
    Match* getMatch(string matchId) {
        if (activeMatches.find(matchId) != activeMatches.end()) {
            return activeMatches[matchId];
        }
        return nullptr;
    }
    
    void displayActiveMatches() {
        cout << "\n=== Active Matches ===" << endl;
        for (auto& pair : activeMatches) {
            Match* match = pair.second;
            cout << "Match " << match->getMatchId() << ": " 
                 << match->getWhitePlayer()->getName() << " vs " 
                 << match->getBlackPlayer()->getName() << endl;
        }
        cout << "Total active matches: " << activeMatches.size() << endl;
        cout << "Users waiting: " << waitingUsers.size() << endl;
    }
};

// Initialize static member
GameManager* GameManager::instance = nullptr;


int main()
{
    GameManager* gameManager = GameManager::getInstance();
    User* Mradul = new User("user1","Mradul");
    gameManager->requestMatch(Mradul);
    User* Kohli = new User("user2","Kohli");
    gameManager->requestMatch(Kohli);
    User* Rohit = new User("user3","Rohit");
    gameManager->requestMatch(Rohit);
    User* KlRahul = new User("user4","Kl Rahul");
    gameManager->requestMatch(KlRahul);
    User* Dhoni = new User("user5","Dhoni");
    gameManager->requestMatch(Dhoni);
    
    gameManager->displayActiveMatches();
    
    return 0;
}