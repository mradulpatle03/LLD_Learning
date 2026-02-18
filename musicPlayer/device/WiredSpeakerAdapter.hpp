#pragma once

#include<bits/stdc++.h>
#include "../models/Song.hpp"
#include "../device/IAudioOutputDevice.hpp"
#include "../external/WiredSpeakerAPI.hpp"
using namespace std;

class WiredSpeakerAdapter : public IAudioOutputDevice {
    WiredSpeakerAPI* wiredSpeakerAPI;
public:
    WiredSpeakerAdapter(WiredSpeakerAPI* wiredSpeakerAPI) {
        this->wiredSpeakerAPI = wiredSpeakerAPI;
    }
    void playAudio(Song* song) {
        wiredSpeakerAPI->playSong(song->getTitle());
    }
};