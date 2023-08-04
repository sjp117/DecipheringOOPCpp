using Item = int;
class LinkList;

class LinkListElement
{
private:
    void *data = nullptr;
    LinkListElement *next = nullptr;

    // private access methods to be used in scope of friend
    void *GetData() const { return data; }
    LinkListElement *GetNext() const { return next; }
    void SetNext(LinkListElement *e) { next = e; }

public:
    // All member functions of LinkList are friend functions of LinkListElement
    friend class LinkList;
    LinkListElement() = default;
    LinkListElement(Item *i) : data(i), next(nullptr) {}
    ~LinkListElement()
    {
        delete static_cast<Item *>(data);
        next = nullptr;
    }
};

// LinkList should only be extended as a protected/private base class; it does not contain a virtual
// destructor. It can be used as-is, or as implementation for another ADT(?)
class LinkList
{
private:
    LinkListElement *head = nullptr, *tail = nullptr, *current = nullptr; // in-class initialization
public:
    LinkList() = default;
    LinkList(LinkListElement *e) { head = tail = current = e; }
    void InsertAtFront(Item *);
    LinkListElement *RemoveAtFront();
    void DeleteAtFront() { delete RemoveAtFront(); }
    bool IsEmpty() const { return head == nullptr; }
    void Print() const;
    ~LinkList()
    {
        while (!IsEmpty())
            DeleteAtFront();
    }
};

void LinkList::InsertAtFront(Item *theItem)
{
    LinkListElement *newHead = new LinkListElement(theItem);
    newHead->SetNext(head); // same as: newHead->next = head;
    head = newHead;
}

LinkListElement *LinkList::RemoveAtFront()
{
    LinkListElement *remove = head;
    head = head->GetNext();
    current = head;
    return remove;
}