#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    const void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List * list =(List*) malloc(sizeof(List));
  list->head = NULL;
  return list;
}

void * firstList(List * list) {
  list->current = list->head;
  return (void*)list->head->data;
}

void * nextList(List * list) {
  if (list->current && list->current->next != NULL) {
		list->current = list->current->next;
	} else return NULL;
	return (void*)list->current->data;
}

void * lastList(List * list) {
  if ( list->tail ) {
    list->current = list->tail;
    return (void*)list->tail->data;
  }
  else return NULL;
}

void * prevList(List * list) {
  if ( list->current && list->current->prev ) {
  list->current = list->current->prev;
  return (void*) list->current->data;
  }
  else return NULL;
}

void pushFront(List * list, const void * data) {
  Node* nuevoNodo = createNode(data);
 if ( list->head ) {
   nuevoNodo->next = list->head;
   list->head->prev = nuevoNodo;
   list->head = nuevoNodo;
 }
 else {
  list->head = nuevoNodo;
  list->tail = list->head;
 }
}

void pushBack(List * list, const void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) {
  Node* n = createNode(data);
  if ( list->head == NULL ) {
    list->head = n;
    list->tail = list->head;
  }
  if ( list->current->next == NULL ) {
    list->current->next = n;
    n->prev = list->current;
    list->current = n;
    list->tail = list->current;
  }
  if ( list->current->next ) {
    n->next = list->current->next;
    list->current->next->prev = n;
    list->current->next = n;
    n->prev = list->current;
    list->current = n;
  }
  
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
if ( list->head == NULL || list->current->next == NULL)
  return NULL;
const void* dato = list->current->data;
if ( list->current == list->head ) {
  list->current->next->prev = NULL;
  list->head = list->head->next;
  free(list->current);
  list->current = list->head;
  
}
else {
  Node* aux = list->current->prev;
  aux->next = list->current->next;
  list->current->next->prev = aux;
  free(list->current);
  list->current = list->head;
}
return (void*)dato;

}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}