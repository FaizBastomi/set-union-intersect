#include "interUni.h"
#include <iostream>

void createList(List &L)
{
    L.first = nullptr;
    L.last = nullptr;
}

adrNode createNewNode(int info)
{
    adrNode p = new node;
    p->info = info;
    p->prev = nullptr;
    p->next = nullptr;
    return p;
}

void insertNewNode(List &L, adrNode p)
{
    if (L.first == nullptr)
    {
        L.first = p;
        L.last = p;
    }
    else
    {
        L.last->next = p;
        p->prev = L.last;
        L.last = p;
    }
}

List unionIteratif(List H1, List H2, List &resUnion)
{
    adrNode p1 = H1.first;
    while(p1 != nullptr)
    {
        bool found = false;
        adrNode pSeen = resUnion.first;
        while(pSeen != nullptr)
        {
            if (p1->info == pSeen->info)
            {
                found = true;
            }
            pSeen = pSeen->next;
        }
        if (!found)
        {
            adrNode newNode = createNewNode(p1->info);
            insertNewNode(resUnion, newNode);
        }
        p1 = p1->next;
    }

    adrNode p2 = H2.first;
    while(p2 != nullptr)
    {
        bool found = false;
        adrNode pSeen = resUnion.first;
        while(pSeen != nullptr)
        {
            if (p2->info == pSeen->info)
            {
                found = true;
            }
            pSeen = pSeen->next;
        }
        if (!found)
        {
            adrNode newNode = createNewNode(p2->info);
            insertNewNode(resUnion, newNode);
        }
        p2 = p2->next;
    }
    return resUnion;
}

void unionRecursive(adrNode p, List &resUnion)
{
    if (p == nullptr)
    {
        return;
    }

    bool found = false;
    adrNode pSeen = resUnion.first;
    while(pSeen != nullptr)
    {
        if (p->info == pSeen->info)
        {
            found = true;
        }
        pSeen = pSeen->next;
    }
    if (!found)
    {
        adrNode newNode = createNewNode(p->info);
        insertNewNode(resUnion, newNode);
    }
    unionRecursive(p->next, resUnion);
}

List intersectionIteratif(List H1, List H2, List &resIntersection)
{
    adrNode p1 = H1.first;
    while(p1 != nullptr)
    {
        adrNode p2 = H2.first;
        while(p2 != nullptr)
        {
            if (p1->info == p2->info)
            {
                bool found = false;
                adrNode pSeen = resIntersection.first;
                while(pSeen != nullptr)
                {
                    if (p1->info == pSeen->info)
                    {
                        found = true;
                    }
                    pSeen = pSeen->next;
                }
                if (!found)
                {
                    adrNode newNode = createNewNode(p1->info);
                    insertNewNode(resIntersection, newNode);
                }
            }
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    return resIntersection;
}

void intersectionRecursive(adrNode p1, List H2, List &resInter)
{
    if (p1 == nullptr)
    {
        return;
    }

    adrNode p2 = H2.first;
    while(p2 != nullptr)
    {
        if (p1->info == p2->info)
        {
            bool found = false;
            adrNode pSeen = resInter.first;
            while(pSeen != nullptr)
            {
                if (p1->info == pSeen->info)
                {
                    found = true;
                }
                pSeen = pSeen->next;
            }
            if (!found)
            {
                adrNode newNode = createNewNode(p1->info);
                insertNewNode(resInter, newNode);
            }
        }
        p2 = p2->next;
    }
    intersectionRecursive(p1->next, H2, resInter);
}

void deleteAllNodes(List &L)
{
    adrNode p = L.first;
    while (p != nullptr)
    {
        adrNode temp = p;
        p = p->next;
        delete temp;
    }
    L.first = nullptr;
    L.last = nullptr;
}

void printList(List L)
{
    adrNode p = L.first;
    while (p != nullptr)
    {
        std::cout << p->info << " ";
        p = p->next;
    }
    std::cout << std::endl;
}