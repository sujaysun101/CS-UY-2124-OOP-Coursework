//Sujay Sundar
//rec09
//Inheritance tutorial

#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned int pages) : numberOfPages(pages) {}
    virtual void displayNumPages() const = 0;
protected:
    unsigned int numberOfPages;
};

class Novel : public PrintedMaterial {
public:
    Novel(unsigned int pages) : PrintedMaterial(pages) {}
    void displayNumPages() const override {cout << numberOfPages << endl;}
};

class Textbook : public PrintedMaterial {
public:
    Textbook(unsigned int pages, unsigned int indexPages) : PrintedMaterial(pages), numOfIndexPages(indexPages) {}
    void displayNumPages() const override {
        cout << "Pages: " << numberOfPages << endl;
        cout << "Index pages: " << numberOfPages << endl;
    }
    void displayNumberOfPages(const PrintedMaterial& printed_material) {
        printed_material.displayNumPages();
    }
private:
    unsigned int numOfIndexPages;
};

int main()
{
    vector<PrintedMaterial*> printed_materials;
    printed_materials.push_back(new Novel(300));
    printed_materials.push_back(new Textbook(500, 50));

    for (size_t i = 0; i < printed_materials.size(); ++i) {
        printed_materials[i]->displayNumPages();
    }
    for (size_t i = 0; i < printed_materials.size(); ++i) {
        delete printed_materials[i];
    }
    return 0;
}
