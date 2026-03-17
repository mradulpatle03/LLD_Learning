#include<bits/stdc++.h>
using namespace std;

template<typename T>
class Iterator{
    public:
        virtual bool hasNext() = 0;
        virtual T next() = 0;
};

template<typename T>
class Iterable{
    public:
        virtual Iterator<T>* getIterator() = 0;
};

class LinkedListIterator;

class LinkedList: public Iterable<int>{
    public:
        int data;
        LinkedList* next;

        LinkedList(int data){
            this->data = data;
            this->next = nullptr;
        }

        Iterator<int>* getIterator() override;
};

class LinkedListIterator: public Iterator<int>{
    private:
        LinkedList* current;
    public:
        LinkedListIterator(LinkedList* current){
            this->current = current;
        }
        bool hasNext(){
            return current != nullptr;
        }
        int next(){
            int data = current->data;
            current = current->next;
            return data;
        }
};

Iterator<int>* LinkedList::getIterator(){
    return new LinkedListIterator(this);
}

class Song{
    public:
        string title;
        string artist;
        string path;
        Song(string title, string artist, string path){
            this->title = title;
            this->artist = artist;
            this->path = path;
        }
};

class PlayListIterator;

class PlayList: public Iterable<Song*>{
    public: 
        string name;
        vector<Song*> songs;
        PlayList(string name){
            this->name = name;
        }
        void addSong(Song* song){
            songs.push_back(song);
        }
        Iterator<Song*>* getIterator() override;
};

class PlayListIterator: public Iterator<Song*>{
    private:
        vector<Song*> songs;
        int index;
    public:
        PlayListIterator(PlayList* playList){
            this->songs = playList->songs;
            this->index = 0;
        }
        bool hasNext(){
            return index < songs.size();
        }
        Song* next(){
            return songs[index++];
        }
};

Iterator<Song*>* PlayList::getIterator(){
    return new PlayListIterator(this);
}

int main(){

    LinkedList* linkedList = new LinkedList(1);
    linkedList->next = new LinkedList(2);
    linkedList->next->next = new LinkedList(3);

    Iterator<int>* iterator = linkedList->getIterator();

    while(iterator->hasNext()){
        cout << iterator->next() << endl;
    }

    Song* song1 = new Song("song1", "artist1", "path1");
    Song* song2 = new Song("song2", "artist2", "path2");
    Song* song3 = new Song("song3", "artist3", "path3");

    PlayList* playList = new PlayList("playlist1");
    playList->addSong(song1);
    playList->addSong(song2);
    playList->addSong(song3);

    Iterator<Song*>* iterator2 = playList->getIterator();
    while(iterator2->hasNext()){
        Song* song = iterator2->next();
        cout << song->title << " by " << song->artist << endl;
    }
    
    return 0;
}