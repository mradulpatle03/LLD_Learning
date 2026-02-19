#pragma once

#include<bits/stdc++.h>
#include "../models/Playlist.hpp"
using namespace std;

class PlaylistManager{
    private:
        static PlaylistManager* instance;
        map<string, Playlist*> playlists;
        PlaylistManager(){}
    public:
        static PlaylistManager* getInstance(){
            if(instance == nullptr){
                instance = new PlaylistManager();
            }
            return instance;
        }
        void createPlaylist(const string& name){
            if(playlists.find(name) == playlists.end()){
                playlists[name] = new Playlist(name);
            }else{
                cout << "Playlist with name " << name << " already exists." << endl;
            }
        }
        void addSongToPlaylist(const string& playlistName, Song* song){
            if(playlists.find(playlistName) != playlists.end()){
                playlists[playlistName]->addSongToPlaylist(song);
            }else{
                cout << "Playlist with name " << playlistName << " does not exist." << endl;
            }
        }
        Playlist* getPlaylist(const string& name){
            if(playlists.find(name) != playlists.end()){
                return playlists[name];
            }else{
                cout << "Playlist with name " << name << " does not exist." << endl;
                return nullptr;
            }
        }
};

PlaylistManager* PlaylistManager::instance = nullptr;