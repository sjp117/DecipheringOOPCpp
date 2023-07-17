// Creating a base class to illustrate implementation inheritance

#include <iostream>

using Item = int;

class LinkListElement // a 'node' or element of a LinkList
{
private:
    void *data = nullptr; // in-class initialization
    LinkListElement *next = nullptr;

public:
    LinkListElement() = default;
    LinkListElement(Item *i) : data(i), next(nullptr) {}
    ~LinkListElement()
    {
        delete static_cast<Item *>(data);
        next = nullptr;
    }
    void *GetData() const { return data; }
    LinkListElement *GetNext() const { return next; }
    void SetNext(LinkListElement *e) { next = e; }
};

class LinkList // an encapsulated LinkList
{
private:
    LinkListElement *head = nullptr; // in-class init
    LinkListElement *tail = nullptr;
    LinkListElement *current = nullptr;

public:
    LinkList() = default; // required t keep default interface
    LinkList(LinkListElement *);
    ~LinkList();
    void InsertAtFront(Item *);
    LinkListElement *RemoveAtFront();
    void DeleteAtFront();
    int IsEmpty() const { return head == nullptr; }
    void Print() const;
};

// default constructor - not necessary to write it with in-class initialization above

LinkList::LinkList(LinkListElement *element)
{
    head = tail = current = element;
}

void LinkList::InsertAtFront(Item *theItem)
{
    LinkListElement *newHead = new LinkListElement(theItem);
    newHead->SetNext(head); // newHead->next = head
    head = newHead;
}

LinkListElement *LinkList::RemoveAtFront()
{
    LinkListElement *remove = head;
    head = head->GetNext(); // head = head->next;
    current = head;         // reset current for use elsewhere
    return remove;
}

void LinkList::DeleteAtFront()
{
    LinkListElement *deallocate;
    deallocate = RemoveAtFront();
    delete deallocate; // destructor will both delete data and set next to nullptr
}

void LinkList::Print() const
{
    if (!head)
        std::cout << "<EMPTY>";
    LinkListElement *traverse = head;
    while (traverse)
    {
        Item output = *(static_cast<Item *>(traverse->GetData()));
        std::cout << output << " ";
        traverse = traverse->GetNext();
    }
    std::cout << std::endl;
}

LinkList::~LinkList()
{
    while (!IsEmpty())
        DeleteAtFront();
}

int main()
{
    // create a few items to be data for LinkListElements
    Item *item1 = new Item;
    *item1 = 100;
    Item *item2 = new Item(200);

    // create an element for the Linked List
    LinkListElement *element1 = new LinkListElement(item1);
    // create a linked list and initialize with one element
    LinkList list1(element1);

    // Add some new items into the list and print
    list1.InsertAtFront(item2);
    list1.InsertAtFront(new Item(50)); // add a nameless item
    std::cout << "List 1: ";
    list1.Print(); // print out contents of list

    // delete elements from list, one by one
    while (!(list1.IsEmpty()))
    {
        list1.DeleteAtFront();
        std::cout << "List 1 after removing an item: ";
        list1.Print();
    }

    // create a second linked list, add some items, print
    LinkList list2;
    list2.InsertAtFront(new Item(3000));
    list2.InsertAtFront(new Item(600));
    list2.InsertAtFront(new Item(475));
    std::cout << "List 2: ";
    list2.Print();

    // delete elements form list, one by one
    while (!(list2.IsEmpty()))
    {
        list2.DeleteAtFront();
        std::cout << "List 2 after removing an item: ";
        list2.Print();
    }
    return 0;
}