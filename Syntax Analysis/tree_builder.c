#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[30];
    int type;
    struct Node* children[15];
} Node;

Node* makeNode(char name[], int type) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->name, name);
    // int type = findTypeFromTable(name);
    node->type = type;
    for (int i = 0; i < 15; i++) {
        node->children[i] = NULL;
    }
    return node;
}

Node* connectChild(Node* parent, Node* child, int index) {
    parent->children[index] = child;
    return parent;
}

void printTree(Node* root, int level) {
    if (root == NULL) return;
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("%s\n", root->name);
    for (int i = 0; i < 15; i++) {
        printTree(root->children[i], level + 1);
    }
}

// int main() {
//     Node* a = makeNode("a", 3);
//     Node* b = makeNode("1", 1);
//     Node* c = makeNode("2.5", 2), *d = makeNode("3", 1);

//     a = connectChild(a, b, 0);
//     b = connectChild(b, c, 1);
//     b = connectChild(b, d, 2);

//     printTree(a, 0);
// }