 #include <iostream>
 #include <bits/stdc++.h>

 using namespace std;

 struct Node {
    int key, val;
    Node* prev, *next;
    Node(int key, int val) : key(key), val(val), prev(nullptr), next(nullptr) {}
 };

 class LRUcache {
public:
    LRUcache(int capcity) : n(capcity) {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    ~LRUcache() {
        while(head->next != tail) {
            pop_front();
        }

        delete head;
        delete tail;
    }

    int get(int key) {
        if(map.find(key) != map.end()) {
            Node* node = map[key];
            int val =  node->val;
            pop_front(node);
            push_back(node);
            return val;
        }
        return -1;
    }

    void put(int key, int val) {
        if(map.find(key) != map.end()) {
            Node* node = map[key];
            pop_front(node);
            node->val = val;
            push_back(node);
        }else {
            if(map.size() == n) {
                Node* oldstNode = head->next;
                map.erase(oldstNode->key);
                pop_front(oldstNode);
            }
            Node* node = new Node(key, val);
            map[key] = node;
            push_back(node);
        }
    }

    void pop_front(Node* node = nullptr) {
        if(!node) node = head->next;

        Node* preNode = node->prev;
        Node* nextNode = node->next;

        preNode->next = nextNode;
        nextNode->prev = preNode;

        delete node;
    }

    void push_back(Node* node) {
        Node* lastNode = tail->prev;
        node->prev = lastNode;
        lastNode->next = node;
        node->next = tail;
        tail->prev = node;
    }

private:
    unordered_map<int, Node*> map;
    Node *head, *tail;
    int n;
 };

 int main() {
    LRUcache cache(2);

    cache.put(1,1);
    cache.put(2,2);
    cout << "Get 1: " << cache.get(1) << endl; // 返回 1
    cache.put(3, 3); // 淘汰键 2
    cout << "Get 2: " << cache.get(2) << endl; // 返回 -1 (未找到)

    return 0;
 }