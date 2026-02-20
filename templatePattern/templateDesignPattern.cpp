#include<bits/stdc++.h>
using namespace std;

class ModelTrainer{
    public:
        void trainModel(const string& datasetPath){
            loadData(datasetPath);
            preprocessData();
            buildModel();
            evaluateModel();
        }
    protected:
        virtual void loadData(const string& datasetPath) = 0;
        virtual void preprocessData() = 0;
        virtual void buildModel() = 0;
        virtual void evaluateModel() = 0;
};

class RandomForestTrainer : public ModelTrainer{
    protected:
        void loadData(const string& datasetPath) override {
            cout << "Loading data from: " << datasetPath << endl;
        }
        void preprocessData() override {
            cout << "Preprocessing data for Random Forest" << endl;
        }
        void buildModel() override {
            cout << "Building Random Forest model" << endl;
        }
        void evaluateModel() override {
            cout << "Evaluating Random Forest model" << endl;
        }
};

class DecisionTreeTrainer : public ModelTrainer{
    protected:
        void loadData(const string& datasetPath) override {
            cout << "Loading data from: " << datasetPath << endl;
        }
        void preprocessData() override {
            cout << "Preprocessing data for Decision Tree" << endl;
        }
        void buildModel() override {
            cout << "Building Decision Tree model" << endl;
        }
        void evaluateModel() override {
            cout << "Evaluating Decision Tree model" << endl;
        }
};

int main(){
    ModelTrainer* trainer1 = new RandomForestTrainer();
    trainer1->trainModel("random_forest_dataset.csv");
    delete trainer1;
    
    ModelTrainer* trainer2 = new DecisionTreeTrainer();
    trainer2->trainModel("decision_tree_dataset.csv");
    delete trainer2;
    return 0;
}