#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CBinNode
{
    CBinNode(int _v)
    {
        value = _v; nodes[0] = nodes[1] = 0;
    }
    int value;
    CBinNode* nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBinTree
{
public:
    CBinTree();
    bool Insert(int x);
    bool Remove(int x);
    void Print();
    void hijos();
    void hermanos();

private:
    bool Find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void InOrder(CBinNode* n);
    CBinNode* m_root;
    bool m_b;
    void mostrar_hijos(CBinNode* nodo);
    void mostrar_hermanos(CBinNode* nodo, CBinNode* padre);
};

CBinTree::CBinTree()
{
    m_root = 0;
    m_b = 0;
}

bool CBinTree::Find(int x, CBinNode**& p)
{
    for (p = &m_root;
        *p && (*p)->value != x;
        p = &((*p)->nodes[(*p)->value < x]));
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x)
{
    CBinNode** p;
    if (Find(x, p)) return 0;
    *p = new CBinNode(x);
    return 0;
}
bool CBinTree::Remove(int x)
{
    CBinNode** p;
    if (!Find(x, p)) return 0;
    if ((*p)->nodes[0] && (*p)->nodes[1])
    {
        CBinNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CBinNode* t = *p;
    *p = (*p)->nodes[(*p)->nodes[0] == 0];
    delete t;
    return 1;
}

CBinNode** CBinTree::Rep(CBinNode** q)
{
    m_b = !m_b;
    q = &((*q)->nodes[!m_b]);
    while ((*q)->nodes[m_b])
        q = &((*q)->nodes[m_b]);
    return q;
}

void CBinTree::InOrder(CBinNode* n)
{
    if (!n) return;
    InOrder(n->nodes[0]);
    cout << n->value << " ";
    InOrder(n->nodes[1]);
}

void CBinTree::Print()
{
    InOrder(m_root);
    cout << endl;
}

void CBinTree::hijos()
{
    if (m_root == nullptr) {
        cout << "El árbol está vacío." << endl;
        return;
    }

    mostrar_hijos(m_root);
}

void CBinTree::mostrar_hijos(CBinNode* nodo)
{
    if (nodo == nullptr)
        return;


    if (nodo->nodes[0] != nullptr || nodo->nodes[1] != nullptr) {
        cout << nodo->value << " -> (";

        if (nodo->nodes[0] != nullptr) {
            cout << nodo->nodes[0]->value;
        }

        cout << ",";

        if (nodo->nodes[1] != nullptr) {
            cout << nodo->nodes[1]->value;
        }

        cout << ")" << endl;
    }

    mostrar_hijos(nodo->nodes[0]);
    mostrar_hijos(nodo->nodes[1]);
}

void CBinTree::hermanos()
{
    if (m_root == nullptr) {
        cout << "El árbol está vacío." << endl;
        return;
    }

    mostrar_hermanos(m_root, nullptr);
}

void CBinTree::mostrar_hermanos(CBinNode* nodo, CBinNode* padre)
{
    if (nodo == nullptr)
        return;

    if (padre != nullptr && (padre->nodes[0] != nullptr || padre->nodes[1] != nullptr)) {
        cout << "(";

        if (padre->nodes[0] != nullptr && padre->nodes[1] != nullptr) {
            cout << padre->nodes[0]->value << "," << padre->nodes[1]->value;
        }
        else if (padre->nodes[0] != nullptr) {
            cout << padre->nodes[0]->value;
        }
        else if (padre->nodes[1] != nullptr) {
            cout << padre->nodes[1]->value;
        }

        cout << ")" << endl;
    }

    mostrar_hermanos(nodo->nodes[0], nodo);
    mostrar_hermanos(nodo->nodes[1], nodo);
}


int main()
{
    CBinTree t;

    t.Insert(8); t.Insert(3); t.Insert(10);
    t.Insert(1); t.Insert(5); t.Insert(9);
    t.Insert(11); t.Insert(12);
    t.Print();

    cout << "hijos:" << endl;
    t.hijos();
    cout << "hermanos:" << endl;
    t.hermanos();
}
