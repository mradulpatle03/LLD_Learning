#pragma once

#include<bits/stdc++.h>
#include "../models/Song.hpp"
#include "../device/IAudioOutputDevice.hpp"
#include "../external/HeadphonesAPI.hpp"
using namespace std;

class HeadphonesAdapter : public IAudioOutputDevice {
    private:
        HeadphonesAPI* headphonesAPI;
    public:
        HeadphonesAdapter(HeadphonesAPI* headphonesAPI) {
            this->headphonesAPI = headphonesAPI;
        }
        void playAudio(Song* song) override {
            headphonesAPI->playSongViaJack(song->getTitle());
        }
};