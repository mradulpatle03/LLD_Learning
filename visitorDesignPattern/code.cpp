#include<bits/stdc++.h>
using namespace std;

class TextElement;
class ImageElement;
class VideoElement;

class Visitor{
    public:
    virtual void visit(TextElement* element) = 0;
    virtual void visit(ImageElement* element) = 0;
    virtual void visit(VideoElement* element) = 0;
};

class DocumentElement{
    public:
    virtual void accept(Visitor* visitor) = 0;
};

class TextElement: public DocumentElement{
    public:
    string text;
    TextElement(string text){
        this->text = text;
    }
    void accept(Visitor* visitor){
        visitor->visit(this);
    }
};

class ImageElement: public DocumentElement{
    public:
    string imagePath;
    ImageElement(string imagePath){
        this->imagePath = imagePath;
    }
    void accept(Visitor* visitor){
        visitor->visit(this);
    }
};

class VideoElement: public DocumentElement{
    public:
    string videoPath;
    VideoElement(string videoPath){
        this->videoPath = videoPath;
    }
    void accept(Visitor* visitor){
        visitor->visit(this);
    }
};

class SizeCalculator: public Visitor{
    public:
        void visit(TextElement* element){
            cout<<"Calculating size of text element: "<<element->text<<endl;
        }
        void visit(ImageElement* element){
            cout<<"Calculating size of image element: "<<element->imagePath<<endl;
        }
        void visit(VideoElement* element){
            cout<<"Calculating size of video element: "<<element->videoPath<<endl;
        }
};

class Compressor: public Visitor{
    public:
        void visit(TextElement* element){
            cout<<"Compressing text element: "<<element->text<<endl;
        }
        void visit(ImageElement* element){
            cout<<"Compressing image element: "<<element->imagePath<<endl;
        }
        void visit(VideoElement* element){
            cout<<"Compressing video element: "<<element->videoPath<<endl;
        }
};

class ScanVirus: public Visitor{
    public:
        void visit(TextElement* element){
            cout<<"Scanning text element: "<<element->text<<endl;
        }
        void visit(ImageElement* element){
            cout<<"Scanning image element: "<<element->imagePath<<endl;
        }
        void visit(VideoElement* element){
            cout<<"Scanning video element: "<<element->videoPath<<endl;
        }
};

int main(){

    DocumentElement* textElement = new TextElement("Hello, World!");
    DocumentElement* imageElement = new ImageElement("image.jpg");
    DocumentElement* videoElement = new VideoElement("video.mp4");

    Visitor* sizeCalculator = new SizeCalculator();
    Visitor* compressor = new Compressor();
    Visitor* scanVirus = new ScanVirus();

    textElement->accept(sizeCalculator);
    textElement->accept(compressor);
    textElement->accept(scanVirus);

    imageElement->accept(sizeCalculator);
    imageElement->accept(compressor);
    imageElement->accept(scanVirus);

    videoElement->accept(sizeCalculator);
    videoElement->accept(compressor);
    videoElement->accept(scanVirus);

    return 0;
}