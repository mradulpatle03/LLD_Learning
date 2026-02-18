#pragma once

#include<bits/stdc++.h>
#include "../device/IAudioOutputDevice.hpp"
#include "../device/HeadphonesAdapter.hpp"
#include "../device/WiredSpeakerAdapter.hpp"
#include "../device/BluetoothSpeakerAdapter.hpp"
#include "../enums/DeviceType.hpp"
using namespace std;

class DeviceFactory {
public:
    static IAudioOutputDevice* createDevice(DeviceType deviceType) {
        if (deviceType == DeviceType::HEADPHONES) {
            return new HeadphonesAdapter(new HeadphonesAPI());
        } else if (deviceType == DeviceType::WIRED) {
            return new WiredSpeakerAdapter(new WiredSpeakerAPI());
        } else if (deviceType == DeviceType::BLUETOOTH) {
            return new BluetoothSpeakerAdapter(new BluetoothSpeakerAPI());
        }
        return nullptr;
    }
};