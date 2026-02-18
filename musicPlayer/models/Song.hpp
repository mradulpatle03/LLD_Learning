#pragma once

#include<bits/stdc++.h>
using namespace std;

class Song{
    private:
        string title;
        string artist;
        string filePath;
    public:
        Song(string title, string artist, string filePath){
            this->title = title;
            this->artist = artist;
            this->filePath = filePath;
        }
        string getTitle(){
            return title;
        }
        string getArtist(){
            return artist;
        }
        string getFilePath(){
            return filePath;
        }

};