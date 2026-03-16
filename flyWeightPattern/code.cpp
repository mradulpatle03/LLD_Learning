#include<bits/stdc++.h>
using namespace std;    

class AsteroidFlyWeight{
    private:
        int length;
        int width;
        int weight;
        string color;
        string texture;
    public:
        virtual ~AsteroidFlyWeight(){}
        AsteroidFlyWeight(int length, int width, int weight, string color, string texture){
            this->length = length;
            this->width = width;
            this->weight = weight;
            this->color = color;
            this->texture = texture;
        }

        void render(int posX, int posY, int velX, int velY){
            cout<<"Rendering asteroid with length "<<length<<" width "<<width<<" weight "<<weight<<" color "<<color<<" texture "<<texture<<endl;
            cout<<"Asteroid rendered at position ("<<posX<<","<<posY<<") with velocity ("<<velX<<","<<velY<<")"<<endl;
        }
};

class AsteroidFlyWeightContext{
    private:
        AsteroidFlyWeight* flyWeight;
        int posX, posY;
        int velX, velY;
    public:
        AsteroidFlyWeightContext(AsteroidFlyWeight* flyWeight, int posX, int posY, int velX, int velY){
            this->flyWeight = flyWeight;
            this->posX = posX;
            this->posY = posY;
            this->velX = velX;
            this->velY = velY;
        }

        void render(){
            flyWeight->render(posX,posY,velX,velY);
        }
};

class AsteroidFlyWeightFactory{
    private:
        static unordered_map<string,AsteroidFlyWeight*> flyWeights;
    public:
        static AsteroidFlyWeight* getFlyWeight(int length, int width, int weight, string color, string texture){
            string key = to_string(length) + "-" + to_string(width) + "-" + to_string(weight) + "-" + color + "-" + texture;
            if(flyWeights.find(key) == flyWeights.end()){
                AsteroidFlyWeight* flyWeight = new AsteroidFlyWeight(length,width,weight,color,texture);
                flyWeights[key] = flyWeight;
            }
            return flyWeights[key];
        }
};

unordered_map<string,AsteroidFlyWeight*> AsteroidFlyWeightFactory ::flyWeights;

int main(){

    AsteroidFlyWeight* flyWeight = AsteroidFlyWeightFactory::getFlyWeight(100, 200, 300, "Red", "Smooth");
    AsteroidFlyWeightContext* context = new AsteroidFlyWeightContext(flyWeight, 10, 20, 30, 40);
    context->render();

    AsteroidFlyWeight* flyWeight2 = AsteroidFlyWeightFactory::getFlyWeight(100, 200, 300, "Red", "Smooth");
    AsteroidFlyWeightContext* context2 = new AsteroidFlyWeightContext(flyWeight2, 10, 20, 30, 40);
    context2->render();

    flyWeight==flyWeight2 ? cout<<"Same FlyWeight"<<endl : cout<<"Different FlyWeight"<<endl;

    return 0;
}