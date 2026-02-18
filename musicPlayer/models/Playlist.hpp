#pragma once

#include<bits/stdc++.h>
#include "Song.hpp"
using namespace std;

class Playlist{
    private:
        string name;
        vector<Song*> PlaylistSongs;
    public:
        Playlist(string name){
            this->name = name;
        }
        void addSongToPlaylist(Song* song){
            PlaylistSongs.push_back(song);
        }
        const vector<Song*> getSongs(){
            return PlaylistSongs;
        }
        string getPlaylistName(){
            return name;
        }
        int getSize(){
            return PlaylistSongs.size();
        }
};
