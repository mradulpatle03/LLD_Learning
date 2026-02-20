#include<bits/stdc++.h>
using namespace std;

class FileFolderSystem{
    public:
        virtual ~FileFolderSystem(){};
        virtual void ls(int indent=0) = 0;
        virtual void openAll(int indent = 0) = 0;      
        virtual int getSize() = 0;                  
        virtual FileFolderSystem* cd(const string& name) = 0; 
        virtual string getName() = 0;
        virtual bool isFolder() = 0;
};

class File : public FileFolderSystem{
    private:
        string name;
        int size;
    public:
        File(const string& name, int size) : name(name), size(size) {}
        void ls(int indent = 0) override {
            cout << string(indent, ' ') << name << " (File, Size: " << size << "KB)" << endl;
        }
        void openAll(int indent = 0) override {
            cout << string(indent, ' ') << "Opening file: " << name << endl;
        }
        int getSize() override {
            return size;
        }
        FileFolderSystem* cd(const string& name) override {
            return nullptr; 
        }
        string getName() override {
            return name;
        }
        bool isFolder() override {
            return false;
        }
};

class Folder : public FileFolderSystem{
    private:
        string name;
        vector<FileFolderSystem*> children;
    public:
        Folder(const string& name) : name(name) {}
        ~Folder() {
            for (auto child : children) {
                delete child;
            }
        }
        void add(FileFolderSystem* child) {
            children.push_back(child);
        }
        void ls(int indent = 0) override {
            cout << string(indent, ' ') << name << " (Folder)" << endl;
            for (auto child : children) {
                child->ls(indent + 2);
            }
        }
        void openAll(int indent = 0) override {
            cout << string(indent, ' ') << "Opening folder: " << name << endl;
            for (auto child : children) {
                child->openAll(indent + 2);
            }
        }
        int getSize() override {
            int totalSize = 0;
            for (auto child : children) {
                totalSize += child->getSize();
            }
            return totalSize;
        }
        FileFolderSystem* cd(const string& name) override {
            for (auto child : children) {
                if (child->getName() == name && child->isFolder()) {
                    return child;
                }
            }
            return nullptr; 
        }
        string getName() override {
            return name;
        }
        bool isFolder() override {
            return true;
        }
};

int main(){
    Folder* root = new Folder("root");
    root->add(new File("file1.txt", 10));
    root->add(new File("file2.txt", 20));

    Folder* subFolder = new Folder("subfolder");
    subFolder->add(new File("file3.txt", 30));
    root->add(subFolder);

    root->ls();
    root->openAll();

    cout << "Total size of root folder: " << root->getSize() << "KB" << endl;

    FileFolderSystem* subFolder2 = root->cd("subfolder");
    if (subFolder2) {
        subFolder2->ls();
        subFolder2->openAll();
    } else {
        cout << "Subfolder not found!" << endl;
    }

    delete root;

    return 0;
}