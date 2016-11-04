//Programmer: Ethan Chiang
//Programmer ID: 1538719

#ifndef AssociativeArray_H
#define AssociativeArray_H

#include <queue>
using namespace std;

template <typename K, typename V>
class AssociativeArray // linked list version
{
  struct Node
  {
    K key;
    V value;
    Node* next;
  };

  Node* firstNode;
  Node* lastNode;
  Node* dummy;
  int siz;

  public:
  AssociativeArray() {firstNode = 0; lastNode = 0; siz = 0;} // default con
  AssociativeArray(const AssociativeArray&); // copy con
  AssociativeArray<K, V>& operator=(const AssociativeArray<K, V>&); // assignment operator
  ~AssociativeArray(); // destructor

  int size() {return siz;}
  V operator[ ] (const K&) const; // getter
  V& operator[ ] (const K&); // setter
  bool containsKey(const K&) const; // getter
  void deleteKey(const K&); // setter
  queue<K> Keys() const;
  void clear();
};

template <typename K, typename V>
AssociativeArray<K, V>::AssociativeArray(const AssociativeArray& original)
{
  firstNode = 0;
  siz = original.siz;

  for(Node* p = original.firstNode; p; p = p->next)
  {
    Node* temp = new Node;
    temp->value = p->value;
    temp->key = p->key;
    temp->next = 0;
    if(lastNode) lastNode->next = temp;
    else firstNode = temp;
    lastNode = temp;
  }
}

template <typename K, typename V>
AssociativeArray<K, V>::~AssociativeArray()
{
	while(firstNode)
  {
    Node* p = firstNode;
    firstNode = firstNode->next;
    delete p;
  }

  firstNode = 0;
  lastNode = 0;
  siz = 0;
}

template <typename K, typename V>
AssociativeArray<K, V> &AssociativeArray<K, V>::operator=(const AssociativeArray<K, V>& original)
{
  if (this != &original) // of it's not a self copy...
  {
    // do what the destructor does
    while(firstNode)
    {
      Node* p = firstNode;
      firstNode = firstNode->next;
      delete p;
    }

    // build new queue
    for(Node* p = original.firstNode; p; p = p->next)
    {
      Node* temp = new Node;
      temp->value = p->value;
      temp->key = p->key;
      temp->next = 0;
      if(lastNode) lastNode->next = temp;
      else firstNode = temp;
      lastNode = temp;
    }
    siz = original.siz;
  }
  return *this; // return a self reference
}

template <typename K, typename V>
V AssociativeArray<K, V>::operator[ ] (const K& key) const // getter
{
  for (Node* p = firstNode; p; p = p->next)
   if (p->key == key)
     return p->value;

  return dummy->value; // if no match
}

template <typename K, typename V>
V& AssociativeArray<K, V>::operator[ ] (const K& key) // setter
{
  for (Node* p = firstNode; p; p = p->next) // find match first
   if (p->key == key)
     return p->value;

  // create new if not found
  siz++;    
  Node* temp = new Node;
  temp->key = key;
  temp->value = V();
  temp->next = firstNode;
  firstNode = temp;
  return firstNode->value;
}

template <typename K, typename V>
bool AssociativeArray<K, V>::containsKey(const K& key) const
{
	for (Node* p = firstNode; p; p = p->next) 
   if (p->key == key)
     return true;

  return false;
}

template <typename K, typename V>
void AssociativeArray<K, V>::deleteKey(const K& key)
{
	for (Node* p = firstNode; p; p = p->next) 
   if (p->next->key == key)
   {
     Node* temp = p->next;
     p->next = temp->next; // un-link node
   }
}

template <typename K, typename V>
queue<K> AssociativeArray<K, V>::Keys() const
{
  queue<K> keys;
  Node* p;
  for(p = firstNode; p; p = p->next)
    keys.push(p->key);
  return keys;
}

template <typename K, typename V>
void AssociativeArray<K, V>::clear()
{
  while(firstNode)
  {
    Node* p = firstNode;
    firstNode = firstNode->next;
    delete p;
  }

  firstNode = 0;
  lastNode = 0;
  siz = 0;
}

#endif 