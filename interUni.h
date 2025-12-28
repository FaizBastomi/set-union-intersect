#ifndef INTERUNI_H_INCLUDED
#define INTERUNI_H_INCLUDED

typedef struct node *adrNode;
struct node{
    int info;
    adrNode prev, next;
};
struct List{
    adrNode first, last;
};

void createList(List &L);
adrNode createNewNode(int info);
void insertNewNode(List &L, adrNode p);
List unionIteratif(List H1, List H2, List &resUnion);
void unionRecursive(adrNode p1, List &resUnion);
List intersectionIteratif(List H1, List H2, List &resIntersection);
void intersectionRecursive(adrNode p1, List H2, List &resInter);
void deleteAllNodes(List &L);
void printList(List L);

#endif // INTERUNI_H_INCLUDED
