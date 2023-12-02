#include <iostream> 
#include <SFML/Graphics.hpp>

using namespace std;

enum COLOR { ROJO, NEGRO };

class Node {
public:
    int val;
    COLOR color;
    Node* left, * right, * parent;

    // Coordenadas para dibujar el nodo
    float x;
    float y;

    Node(int val) : val(val), color(ROJO) {
        parent = left = right = nullptr;
    }

    bool isOnLeft() { return this == parent->left; }

    Node* sibling() {
        if (parent == nullptr)
            return nullptr;

        return isOnLeft() ? parent->right : parent->left;
    }

    Node* uncle() {
        if (parent == nullptr || parent->parent == nullptr)
            return nullptr;

        return parent->isOnLeft() ? parent->parent->right : parent->parent->left;
    }

    void moveDown(Node* newParent) {
        if (parent != nullptr) {
            if (isOnLeft()) {
                parent->left = newParent;
            }
            else {
                parent->right = newParent;
            }
        }
        newParent->parent = parent;
        parent = newParent;
    }

    bool hasROJOChild() {
        return (left != nullptr && left->color == ROJO) ||
            (right != nullptr && right->color == ROJO);
    }
};

class RBTree {
    Node* root;

    void leftRotate(Node* x) {
        Node* nParent = x->right;
        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        x->right = nParent->left;
        if (nParent->left != nullptr)
            nParent->left->parent = x;

        nParent->left = x;
    }

    void rightRotate(Node* x) {
        Node* nParent = x->left;
        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        x->left = nParent->right;
        if (nParent->right != nullptr)
            nParent->right->parent = x;

        nParent->right = x;
    }

    void swapColors(Node* x1, Node* x2) {
        COLOR temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }

    void swapValues(Node* u, Node* v) {
        int temp = u->val;
        u->val = v->val;
        v->val = temp;
    }

    void fixROJOROJO(Node* x) {
        if (x == root) {
            x->color = NEGRO;
            return;
        }

        Node* parent = x->parent, * grandparent = parent->parent, * uncle = x->uncle();

        if (parent->color != NEGRO) {
            if (uncle != nullptr && uncle->color == ROJO) {
                parent->color = NEGRO;
                uncle->color = NEGRO;
                grandparent->color = ROJO;
                fixROJOROJO(grandparent);
            }
            else {
                if (parent->isOnLeft()) {
                    if (x->isOnLeft()) {
                        swapColors(parent, grandparent);
                    }
                    else {
                        leftRotate(parent);
                        swapColors(x, grandparent);
                    }
                    rightRotate(grandparent);
                }
                else {
                    if (x->isOnLeft()) {
                        rightRotate(parent);
                        swapColors(x, grandparent);
                    }
                    else {
                        swapColors(parent, grandparent);
                    }
                    leftRotate(grandparent);
                }
            }
        }
    }

    Node* search(int n) {
        Node* temp = root;
        while (temp != nullptr) {
            if (n < temp->val) {
                if (temp->left == nullptr)
                    break;
                else
                    temp = temp->left;
            }
            else if (n == temp->val) {
                break;
            }
            else {
                if (temp->right == nullptr)
                    break;
                else
                    temp = temp->right;
            }
        }

        return temp;
    }

    void inorder(Node* x) {
        if (x == nullptr)
            return;
        inorder(x->left);
        std::cout << x->val << " (" << (x->color == ROJO ? "ROJO" : "NEGRO") << ") ";
        inorder(x->right);
    }

    Node* maxValueNode(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        Node* current = node;

        // Encuentra la hoja más a la derecha
        while (current->right != nullptr) {
            current = current->right;
        }

        return current;
    }

    void fixDoubleNEGRO(Node* x, Node* parent) {
        while (x != root && (x == nullptr || x->color == NEGRO)) {
            if (x == root) {
                break;
            }

            Node* sibling = (x == parent->left) ? parent->right : parent->left;

            if (sibling == nullptr) {
                x = parent;
            }
            else {
                if (sibling->color == ROJO) {
                    sibling->color = NEGRO;
                    parent->color = ROJO;
                    if (x == parent->left) {
                        leftRotate(parent);
                        sibling = parent->right;
                    }
                    else {
                        rightRotate(parent);
                        sibling = parent->left;
                    }
                }

                if ((sibling->left == nullptr || sibling->left->color == NEGRO) &&
                    (sibling->right == nullptr || sibling->right->color == NEGRO)) {
                    sibling->color = ROJO;
                    if (parent->color == NEGRO) {
                        x = parent;
                    }
                    else {
                        parent->color = NEGRO;
                        break;
                    }
                }
                else {
                    if (x == parent->left && (sibling->right == nullptr || sibling->right->color == NEGRO)) {
                        sibling->left->color = NEGRO;
                        sibling->color = ROJO;
                        rightRotate(sibling);
                        sibling = parent->right;
                    }
                    else if (x == parent->right && (sibling->left == nullptr || sibling->left->color == NEGRO)) {
                        sibling->right->color = NEGRO;
                        sibling->color = ROJO;
                        leftRotate(sibling);
                        sibling = parent->left;
                    }

                    sibling->color = parent->color;
                    parent->color = NEGRO;
                    if (x == parent->left) {
                        sibling->right->color = NEGRO;
                        leftRotate(parent);
                    }
                    else {
                        sibling->left->color = NEGRO;
                        rightRotate(parent);
                    }
                    break;
                }
            }
        }

        if (x != nullptr) {
            x->color = NEGRO;
        }
    }

    void deleteNode(Node* v) {
        if (v == nullptr) {
            return;
        }

        Node* nodeToDelete = v;
        if (v->left != nullptr && v->right != nullptr) {
            // Si tiene dos hijos, encontrar el sucesor inmediato (mayor valor en el subárbol izquierdo)
            nodeToDelete = maxValueNode(v->left);
        }

        Node* child = (nodeToDelete->left != nullptr) ? nodeToDelete->left : nodeToDelete->right;

        if (child != nullptr) {
            child->parent = nodeToDelete->parent;
        }

        if (nodeToDelete->parent == nullptr) {
            root = child;
        }
        else {
            if (nodeToDelete == nodeToDelete->parent->left) {
                nodeToDelete->parent->left = child;
            }
            else {
                nodeToDelete->parent->right = child;
            }
        }

        // Save the color of the node to be deleted
        COLOR originalColor = nodeToDelete->color;

        if (nodeToDelete != v) {
            v->val = nodeToDelete->val;
        }

        if (originalColor == NEGRO) {
            fixDoubleNEGRO(child, nodeToDelete->parent);
        }

        if (nodeToDelete->parent == nullptr && child != nullptr) {
            // If we replaced the root with a non-null child, make it NEGRO
            child->color = NEGRO;
        }

        delete nodeToDelete;
    }

public:
    RBTree() : root(nullptr) {}

    Node* getRoot() { return root; }

    void insert(int n) {
        Node* newNode = new Node(n);
        if (root == nullptr) {
            newNode->color = NEGRO;
            root = newNode;
        }
        else {
            Node* temp = search(n);

            if (temp->val == n) {
                delete newNode;
                return;
            }

            newNode->parent = temp;

            if (n < temp->val)
                temp->left = newNode;
            else
                temp->right = newNode;

            fixROJOROJO(newNode);
        }
    }

    void remove(int n) {
        if (root == nullptr) {
            std::cout << "Tree is empty" << std::endl;
            return;
        }

        Node* v = search(n);
        if (v->val != n) {
            std::cout << "No se encontró el nodo con valor " << n << std::endl;
            return;
        }

        deleteNode(v);
    }

    void printInOrder() {
        if (root == nullptr)
            std::cout << "Tree is empty" << std::endl;
        else
            inorder(root);
        std::cout << std::endl;
    }

    void assignCoordinates(Node* root, float x, float y, float horizontalSpacing) {
        if (root != nullptr) {
            root->x = x;
            root->y = y;

            assignCoordinates(root->left, x - horizontalSpacing, y + 50, horizontalSpacing / 2);
            assignCoordinates(root->right, x + horizontalSpacing, y + 50, horizontalSpacing / 2);
        }
    }

    void drawTree(sf::RenderWindow& window, Node* root) {
        if (root != nullptr) {
            
            if (root->left != nullptr) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(root->x, root->y), sf::Color::White),
                    sf::Vertex(sf::Vector2f(root->left->x, root->left->y), sf::Color::White)
                };
                window.draw(line, 4, sf::Lines);
            }

            if (root->right != nullptr) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(root->x, root->y), sf::Color::White),
                    sf::Vertex(sf::Vector2f(root->right->x, root->right->y), sf::Color::White)
                };
                window.draw(line, 4, sf::Lines);
            }

            sf::CircleShape circle(20);
            circle.setFillColor(root->color == ROJO ? sf::Color::Red : sf::Color::Black);
            circle.setOutlineThickness(1);
            circle.setOutlineColor(sf::Color::White);
            circle.setPosition(root->x - 20, root->y - 20);

            window.draw(circle);

            sf::Font font;
            font.loadFromFile("arial.ttf");

            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(root->val));
            text.setCharacterSize(12);
            text.setFillColor(sf::Color::White);
            text.setPosition(root->x - 5, root->y - 12);

            window.draw(text);

            drawTree(window, root->left);
            drawTree(window, root->right);
        }
    }

    void visualizeTree() {
        assignCoordinates(root, 400, 50, 200);

        sf::RenderWindow window(sf::VideoMode(800, 600), "RB Tree Visualization");

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();

            drawTree(window, root);

            window.display();
        }
    }
};

int main() {
    RBTree tree;

    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);
    tree.insert(8);
    tree.insert(11);
    tree.insert(26);
    tree.insert(2);
    tree.insert(6);
    tree.insert(13);
    tree.printInOrder();

    cout << "Deleting 18, 11, 3, 10, 22" << endl;
    tree.remove(18);
    tree.printInOrder();
    tree.remove(11);
    tree.printInOrder();
    tree.remove(3);
    tree.printInOrder();
    tree.remove(10);
    tree.printInOrder();
    tree.remove(22);
    tree.printInOrder();

    tree.visualizeTree();

    return 0;
}