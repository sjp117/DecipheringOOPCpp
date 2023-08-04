#include <iostream>

// forward declaration with template preamble
template <class Type>
class LinkList;

template <class Type> // template preamble for class definition
class LinkListElement
{
private:
    Type *data = nullptr;
    LinkListElement *next = nullptr;
    // private access methods to be used in scope of friend
    Type *GetData() const { return data; }
    LinkListElement *GetNext() const { return next; }
    void SetNext(LinkListElement *e) { next = e; }

public:
    friend class LinkList<Type>;
    LinkListElement() = default;
    LinkListElement(Type *i) : data(i), next(nullptr) {}
    ~LinkListElement()
    {
        delete data;
        next = nullptr;
    }
};

// LinkList should only be extended as a protected/private base class; it does not contain a virtual
// destructor. It can be used as-is, or as implementation for another ADT(?)

template <class Type>
class LinkList
{
private:
    LinkListElement<Type> *head = nullptr, *tail = nullptr, *current = nullptr;

public:
    LinkList() = default;
    LinkList(LinkListElement<Type> *e) { head = tail = current = e; }
    void InsertAtFront(Type *);
    LinkListElement<Type> *RemoveAtFront();
    void DeleteAtFront() { delete RemoveAtFront(); }
    bool IsEmpty() const { return head == nullptr; }
    void OrderedInsert(Type *);
    void Print() const;
    ~LinkList()
    {
        while (!IsEmpty())
            DeleteAtFront();
    }
};

template <class Type>
void LinkList<Type>::InsertAtFront(Type *theItem)
{
    LinkListElement<Type> *newHead = nullptr;
    newHead = new LinkListElement<Type>(theItem);
    newHead->SetNext(head);
    head = newHead;
}

template <class Type>
LinkListElement<Type> *LinkList<Type>::RemoveAtFront()
{
    LinkListElement<Type> *remove = head;
    head = head->GetNext();
    current = head;
    return remove;
}

template <class Type>
void LinkList<Type>::OrderedInsert(Type *theItem)
{
    current = head;
    if (*theItem < *(head->GetData()))
        InsertAtFront(theItem);
    else
        return;
}

template <class Type>
void LinkList<Type>::Print() const
{
    if (!head)
        std::cout << "<EMPTY>" << std::endl;
    LinkListElement<Type> *traverse = head;
    while (traverse)
    {
        Type output = *(traverse->GetData());
        std::cout << output << ' ';
        traverse = traverse->GetNext();
    }
    std::cout << std::endl;
}

int main()
{
    LinkList<int> list1;
    list1.InsertAtFront(new int(3000));
    list1.InsertAtFront(new int(600));
    list1.InsertAtFront(new int(475));

    std::cout << "List1: ";
    list1.Print();

    // delete elements from list, one by one
    while (!list1.IsEmpty())
    {
        list1.DeleteAtFront();
        std::cout << "List 1 after removing an item: ";
        list1.Print();
    }

    LinkList<float> list2;
    list2.InsertAtFront(new float(30.50));
    list2.InsertAtFront(new float(60.89));
    list2.InsertAtFront(new float(45.93));
    std::cout << "List 2: ";
    list2.Print();

    return 0;
}