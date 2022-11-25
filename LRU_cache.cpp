using namespace std;
#include <unordered_map>

struct node {
    int key, value;
    node* prev;
    node* next;
    node() :key(0), value(0), prev(nullptr), next(nullptr) {}
    node(int k, int v) :key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    unordered_map <int, node*> map;
    node* head, *tail;
    int max_size;

    void remove(node* n)
    {
        n->next->prev = n->prev;
        n->prev->next = n->next;
    }

    void add_ahead(node* n) {
        n->next = head->next;
        n->prev = head;
        head->next->prev = n;
        head->next = n;
    }

public:
    //Initialize the LRU cache with positive size capacity.
    LRUCache(int capacity) {
        max_size = capacity;
        head = new node();
        tail = new node();
        head->next = tail;
        tail->prev = head;
    }

    //Return the value of the key if the key exists, otherwise return -1.
    int get(int key) {
        if (map.find(key) == map.end()) {
            return -1;
        }
        remove(map[key]);
        add_ahead(map[key]);
        return map[key]->value;
    }

    //Update the value of the key if the key exists. 
    //Otherwise, add the key-value pair to the cache. 
    //If the number of keys exceeds the capacity from this operation, evict the least recently used key.
    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            map[key]->value = value;
            remove(map[key]);
            add_ahead(map[key]);
        }
        else {
            if (map.size() == max_size) {
                map.erase(tail->prev->key);
                remove(tail->prev);
            }
            node* n = new node(key, value);
            map[key] = n;
            add_ahead(n);
        }
    }
};