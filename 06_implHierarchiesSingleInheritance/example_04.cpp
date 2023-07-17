// Using a protected base class to implement one class in terms of another

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

    // additional member fuctions added
    void InsertBeforeItem(Item *, Item *);
    LinkListElement *RemoveSpecificItem(Item *);
    void DeleteSpecificItem(Item *);
    void InsertAtEnd(Item *);
    LinkListElement *RemoveAtEnd();
    void DeleteAtEnd();

    int IsEmpty() const { return head == nullptr; }
    void Print() const;
};

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

void LinkList::InsertBeforeItem(Item *newItem, Item *existing)
{
    LinkListElement *temp = nullptr, *toAdd = nullptr;
    // assumes item to insert before exists
    current = head;
    if (*(static_cast<Item *>(current->GetData())) == *existing)
        InsertAtFront(newItem);
    else
    {
        while (*(static_cast<Item *>(current->GetData())) != *existing)
        {
            temp = current;
            current = current->GetNext();
        }

        toAdd = new LinkListElement(newItem); // wrap an item in a LinkListElement
        temp->SetNext(toAdd);
        toAdd->SetNext(current);
    }
}

LinkListElement *LinkList::RemoveSpecificItem(Item *item)
{
    // add implementation
}

void LinkList::DeleteSpecificItem(Item *item)
{
    // add implementation
}

void LinkList::InsertAtEnd(Item *item)
{
    if (!head)
    {
        head = new LinkListElement(item); // constructor also nulls out next
        tail = head;
    }
    else
    {
        tail->SetNext(new LinkListElement(item));
        tail = tail->GetNext();
    }
}

LinkListElement *LinkList::RemoveAtEnd()
{
    // add implementation
}

void LinkList::DeleteAtEnd()
{
    // add implementation
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

class Queue : protected LinkList
{
private: // no new data members
public:
    Queue() = default;
    virtual ~Queue() = default; // virtual explained in ch. 7
    // public interface
    void Enqueue(Item *i) { InsertAtEnd(i); }
    Item *Dequeue();
    // redefine methods from LinkList protected base class
    int IsEmpty() const { return LinkList::IsEmpty(); }
    void Print() { LinkList::Print(); }
};

Item *Queue::Dequeue()
{
    LinkListElement *front;
    front = RemoveAtFront();
    // make copy of front's data
    Item *item = new Item(*(static_cast<Item *>(front->GetData())));
    delete front;
    return item;
}

class PriorityQueue : public Queue
{
private: // NA
public:
    void PriorityEnqueue(Item *i1, Item *i2) { InsertBeforeItem(i1, i2); }
};

int main()
{
    Queue q1;
    q1.Enqueue(new Item(50));
    q1.Enqueue(new Item(67));
    q1.Enqueue(new Item(80));
    q1.Print();
    while (!(q1.IsEmpty()))
    {
        q1.Dequeue();
        q1.Print();
    }

    PriorityQueue q2;           // PriorityQueue instance
    Item *item = new Item(167); // save a handle to item
    q2.Enqueue(new Item(67));   // first item added
    q2.Enqueue(item);           // seconds item added
    q2.Enqueue(new Item(180));  // third item
    // add new item before an existing item
    q2.PriorityEnqueue(new Item(100), item); // 4th item
    q2.Print();
    while (!(q2.IsEmpty()))
    {
        q2.Dequeue();
        q2.Print();
    }
    return 0;
}