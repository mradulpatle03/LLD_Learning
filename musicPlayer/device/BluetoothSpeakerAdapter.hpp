#pragma once

#include<bits/stdc++.h>
#include "../models/Song.hpp"
#include "../device/IAudioOutputDevice.hpp"
#include "../external/BluetoothSpeakerAPI.hpp"
using namespace std;

class BluetoothSpeakerAdapter : public IAudioOutputDevice {
private:
    BluetoothSpeakerAPI* bluetoothSpeakerAPI;
public:
    BluetoothSpeakerAdapter(BluetoothSpeakerAPI* bluetoothSpeakerAPI) {
        this->bluetoothSpeakerAPI = bluetoothSpeakerAPI;
    }

    void playAudio(Song* song) {
        bluetoothSpeakerAPI->playSoundViaBluetooth(song->getTitle());
    }
};

