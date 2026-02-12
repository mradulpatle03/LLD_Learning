#include <iostream>
using namespace std;

class Printer {
public:
    virtual void print(string text) = 0;
    virtual ~Printer() {}
};

class OldPrinter {
public:
    void oldPrint(string text) {
        cout << "Old Printer: " << text << endl;
    }
};


class PrinterAdapter : public Printer {
private:
    OldPrinter* oldPrinter;

public:
    PrinterAdapter(OldPrinter* p) {
        oldPrinter = p;
    }

    void print(string text) override {
        oldPrinter->oldPrint(text);  // adapt call
    }
};


int main() {
    OldPrinter oldPrinter;
    Printer* printer = new PrinterAdapter(&oldPrinter);

    printer->print("Hello Adapter Pattern!");

    delete printer;
    return 0;
}
