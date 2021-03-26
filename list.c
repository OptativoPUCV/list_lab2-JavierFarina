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
  /* 
  aca debo hacer un casting a int o void?, si no hago el casting no retorna nada
  */
}

void * nextList(List * list) {
  if (list->current && list->current->next != NULL) {
		list->current = list->current->next;
	} else return NULL;
	return (void*)list->current->data;
}

void * lastList(List * list) {
  if ( list->tail && list->tail->data ) {
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
  Node* n = createNode(data);
  n->next = list->head;
  if ( list->head ) list->head->prev = n; //nueva cabecera
  //pq es necesaria esa linea de codigo?
  if ( list->tail == NULL) list->tail = n; //si la lista es de 1 elemento se agrega al final
  list->head = n; //actualiza el primer dato
  list->head->prev = NULL; //  no hay nada antes de la cabecera
}

void pushBack(List * list, const void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) {
  Node* n = createNode(data);
  if ( list->current->next && list->current->prev ) {
   n->next = list->current->next; //si la siguiente posicion exite no estamos en el final, por lo que la siguiente posicion del nodo a colocar apuntara a la siguiente(ACTUAL) del current
    n->prev = list->current; // si la posicion anterior al current existe no estamos en la primera posicion pro lo que la psocion anterior del nodo a colocar apuntara al current
  } //esta si o si al medio
  

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
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}