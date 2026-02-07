#include <bits/stdc++.h>
using namespace std;

class DocumentElement
{
public:
    virtual string render() = 0;
};

class TextElement : public DocumentElement
{
private:
    string text;

public:
    TextElement(string text)
    {
        this->text = text;
    }

    string render() override
    {
        return text;
    }
};

class ImageElement : public DocumentElement
{
private:
    string imagePath;

public:
    ImageElement(string imagePath)
    {
        this->imagePath = imagePath;
    }

    string render() override
    {
        return "<img src=" + imagePath + ">";
    }
};

class Document
{
private:
    vector<DocumentElement *> elements;

public:
    void addElement(DocumentElement *element)
    {
        elements.push_back(element);
    }

    string render()
    {
        string result;
        for (auto element : elements)
        {
            result += element->render() + "\n";
        }
        return result;
    }
};

class Persistence
{
public:
    virtual void save(string s) = 0;
};

class SaveToFile : public Persistence
{
public:
    void save(string s) override
    {
        cout << "Saving to file: " << s << endl;
    }
};

class SaveToDB : public Persistence
{
public:
    void save(string s) override
    {
        cout << "Saving to DB: " << s << endl;
    }
};

class Editor
{
private:
    Document *document;
    Persistence *persistence;
    string currentState;

public:
    Editor(Document *document, Persistence *persistence)
    {
        this->document = document;
        this->persistence = persistence;
    }

    void addText(string text)
    {
        document->addElement(new TextElement(text));
    }

    void addImage(string imagePath)
    {
        document->addElement(new ImageElement(imagePath));
    }

    string renderDocument()
    {
        if (currentState.empty())
        {
            currentState = document->render();
        }
        return currentState;
    }

    void save()
    {
        persistence->save(renderDocument());
    }
};


int main(){
    Document* doc = new Document();
    Persistence* filePersistence = new SaveToFile();

    Editor* editor = new Editor(doc, filePersistence);

    editor->addText("Hello, World!");
    editor->addImage("image.png");
    cout << editor->renderDocument() << endl;
    editor->save();

    return 0;
}