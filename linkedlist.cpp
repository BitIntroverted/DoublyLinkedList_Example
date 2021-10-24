/*
 * 	Name: Lukas Friedrich
 * 	Coding 05
 * 	Linkedin List class
 */

 #include "linkedlist.h"

    LinkedList::LinkedList() {
        head = NULL;
    }

    LinkedList::~LinkedList(){
        clearList();
    }

    bool LinkedList::addNode(int id, string* info){
        bool addedFlag = false;
        if (id > 0 && *info != "") {
            Node* current, * temp;
            current = head;
                while (current && id > current->data.id && current->next) {
                    current = current->next;
                }
                if (!current || id != current->data.id){
                temp = new Node;
                temp->data.id = id; temp->data.data = *info;
                addedFlag = true;
                    if (!current || (current && id < head->data.id)) {
                        addHead(current, temp);
                    }
                    else if (!current->next) {
                        addTail(current, temp);
                    }
                    else{ addMiddle(current, temp); }
                }
            }
        return addedFlag;
    }

    bool LinkedList::deleteNode(int id){
        bool isDeleted = false;
        Node* current = head;
        while (current && current->next && id != current->data.id) {
            current = current->next;
        }
        if (current && id == current->data.id){
            if (!current->prev && current->next) { //replace head
                current->next->prev = NULL;
                head = current->next;
            }
            else if (!current->next && current->prev) { //replace tail
                current->prev->next = NULL;
            }
            else if (current->next && current->prev){ //replace middle
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            else if (!current->prev && !current->next) { //solo node case
                head = current->next; 
            }
            delete current;
            isDeleted = true;
        }
        return isDeleted;
    }
    bool LinkedList::getNode(int id, Data* tempData){
        bool exists = false;
        Node* current = head;
        while (current && current->data.id != id)
        {
            current = current->next;
        }
        if (current && current->data.id == id) {
            tempData->id = current->data.id;
            tempData->data = current->data.data;
            exists = true;
        }
        return exists;
    }
    void LinkedList::printList(bool backward){
        Node* current = head;
        if(backward == false) {
            while (current) {
                std::cout << current->data.id << ": " << current->data.data << std::endl;
                current = current->next;
            }
        }
        else {
            while (current && current->next) {
                current = current->next;
            }
            while (current) {
                std::cout << current->data.id << ": " << current->data.data << std::endl;
                current = current->prev;
            }
        }
    }

    int LinkedList::getCount(){
        Node* current = head;
        int counter = 0;
        if (current) { counter = 1; }
        while (current && current->next) {
            counter++;
            current = current->next;
        }
        return counter;
    }

    bool LinkedList::clearList(){
        Node* temp;
        Node* current = head;
        bool cleared = false;
        while (current)
        {
            temp = current->next;
            delete current;
            current = temp;
        }
        head = NULL; cleared = true;
        return cleared;
    }

    bool LinkedList::exists(int id){
        bool exists = false;
        Node* current = head;
        while (current && current->data.id != id)
        {
            current = current->next;
        }
        if (current && current->data.id == id) {
            exists = true;
        }
        return exists;
    }

    void LinkedList::addHead(Node* current, Node* temp)
    {
        if (current) {
            head->prev = temp;
        }
        temp->next = head;
        temp->prev = NULL;
        head = temp;
    }
    void LinkedList::addTail(Node* current, Node* temp)
    {
        temp->next = NULL;
        temp->prev = current;
        current->next = temp;
    }
    void LinkedList::addMiddle(Node* current, Node* temp)
    {
        temp->next = current;
        temp->prev = current->prev;
        current->prev->next = temp;
        current->prev = temp;
    }