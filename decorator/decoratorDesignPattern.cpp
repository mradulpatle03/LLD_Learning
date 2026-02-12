#include<bits/stdc++.h>
using namespace std;

class TextElement{
    public:
    virtual string render() = 0;
    virtual ~TextElement(){};
};

class Text : public TextElement{
    public:
    string render() override {
        return "Hello, World!";
    }
};

class TextDecorator :public TextElement{
    public:
    TextElement* textElement;
    TextDecorator(TextElement* textElement){
        this->textElement = textElement;
    }
};

class BoldDecorator :public TextDecorator{
    public:
    // calling the constructor of base class
    BoldDecorator(TextElement* textElement):TextDecorator(textElement){};
    string render() override {
        return "<b>" + textElement->render() + "</b>";
    }
};

class ItalicDecorator :public TextDecorator{
    public:
    // calling the constructor of base class
    ItalicDecorator(TextElement* textElement):TextDecorator(textElement){};
    string render() override {
        return "<i>" + textElement->render() + "</i>";
    }
};

int main(){

    TextElement* text = new Text();
    cout << "Original Text: " << text->render() << endl;

    text = new BoldDecorator(text);
    cout << "make Bold: " << text->render() << endl;

    text = new ItalicDecorator(text);
    cout << "make Italic: " << text->render() << endl;

    return 0;   
}