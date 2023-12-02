#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    // Coordenadas para dibujar el nodo
    float x;
    float y;
};

int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node* insert(Node* node, int key) {
    if (node == NULL)
        return(newNode(key));
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node* findMax(Node* node) {
    while (node->right != NULL) {
        node = node->right;
    }
    return node;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Nodo con un solo hijo o sin hijos
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Nodo con dos hijos, encontrar el máximo en el subárbol izquierdo
        Node* temp = findMax(root->left);
        root->key = temp->key;
        root->left = deleteNode(root->left, temp->key);
    }

    // Actualizar la altura del nodo actual
    root->height = 1 + max(height(root->left), height(root->right));

    // Realizar las rotaciones para mantener el equilibrio
    int balance = getBalance(root);

    // Casos de rotación
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
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
        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(root->x - 20, root->y - 20);

        window.draw(circle);

        sf::Font font;
        font.loadFromFile("arial.ttf"); // Reemplaza con la ruta a tu fuente

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(root->key));
        text.setCharacterSize(18);
        text.setFillColor(sf::Color::White);
        text.setPosition(root->x - 5, root->y - 12);

        window.draw(text);

        if (root->left != nullptr) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(root->x, root->y), sf::Color::Green),
                sf::Vertex(sf::Vector2f(root->left->x, root->left->y), sf::Color::Green)
            };
            window.draw(line, 2, sf::Lines);
        }

        if (root->right != nullptr) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(root->x, root->y), sf::Color::Green),
                sf::Vertex(sf::Vector2f(root->right->x, root->right->y), sf::Color::Green)
            };
            window.draw(line, 2, sf::Lines);
        }

        drawTree(window, root->left);
        drawTree(window, root->right);
    }
}



int main() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    inOrder(root);
    cout << endl;

    root = deleteNode(root, 40);
    inOrder(root);

    assignCoordinates(root, 400, 50, 200);

    sf::RenderWindow window(sf::VideoMode(800, 600), "AVL Tree Visualization");

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

    return 0;
}
