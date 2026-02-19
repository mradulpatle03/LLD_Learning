#pragma once 

#include<bits/stdc++.h>
#include "../device/IAudioOutputDevice.hpp"
#include "../enums/DeviceType.hpp"
#include "../factories/DeviceFactory.hpp"
using namespace std;

class DeviceManager {
    private:
        static DeviceManager* instance;
        IAudioOutputDevice* currentDevice;
        DeviceManager(){
            currentDevice = nullptr;
        }
    public:
        static DeviceManager* getInstance() {
            if (instance == nullptr) {
                instance = new DeviceManager(); 
            }
            return instance;
        }
        void connect(DeviceType deviceType) {
            if (currentDevice != nullptr) {
                delete currentDevice;
            }
            currentDevice = DeviceFactory::createDevice(deviceType);

            if(deviceType == DeviceType::HEADPHONES) {
                cout << "Connected to headphones" << endl;
            } else if (deviceType == DeviceType::WIRED) {
                cout << "Connected to wired speaker" << endl;
            } else if (deviceType == DeviceType::BLUETOOTH) {
                cout << "Connected to bluetooth speaker" << endl;
            }
        }
        IAudioOutputDevice* getOutputDevice() {
            return currentDevice;
        }
        bool hasOutputDevice() {
            return currentDevice != nullptr;
        };
};
DeviceManager* DeviceManager::instance = nullptr;