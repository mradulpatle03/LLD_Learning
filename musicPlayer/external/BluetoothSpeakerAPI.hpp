#pragma once

#include<bits/stdc++.h>
using namespace std;

class BluetoothSpeakerAPI{
    public:
        void playSoundViaBluetooth(const string& songName) {
            cout << "Playing " << songName << " via Bluetooth." << endl;
        }
};