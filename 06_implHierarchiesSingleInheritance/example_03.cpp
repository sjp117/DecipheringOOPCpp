// Using a private base class to implement one class in terms of another

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

class Stack : private LinkList
{
private: // no new data member
public:
    // Constructor, destructor prototypes are redundant. They are only for demonstration
    Stack() = default;
    ~Stack() = default;
    // public interface for Stack
    void Push(Item *i) { InsertAtFront(i); }
    Item *Pop();
    // These operators need to be redefined because LinkList is a private base class of Stack
    int IsEmpty() const { return LinkList::IsEmpty(); }
    void Print() { LinkList::Print(); }
};

Item *Stack::Pop()
{
    LinkListElement *top;
    top = RemoveAtFront();
    // copy top's data
    Item *item = new Item(*(static_cast<Item *>(top->GetData())));
    delete top;
    return item;
}

int main()
{
    Stack stack1; // create a Stack
    // Add some items to the stack, using public interface
    stack1.Push(new Item(3000));
    stack1.Push(new Item(600));
    stack1.Push(new Item(475));
    std::cout << "Stack 1: ";
    stack1.Print();

    // Pop elements from stack, one by one
    while (!(stack1.IsEmpty()))
    {
        stack1.Pop();
        std::cout << "Stack 1 after popping an item: ";
        stack1.Print();
    }
    return 0;
}