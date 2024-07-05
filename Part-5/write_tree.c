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

void writeTreeToFile(Node* root, FILE* file) {
    if (root == NULL) return;
    fprintf(file, "[%s", root->name);
    for (int i = 0; i < 15; i++) {
        if (root->children[i] != NULL) {
            fprintf(file, "[");
            writeTreeToFile(root->children[i], file);
            fprintf(file, "]");
        }
    }
    fprintf(file, "]");
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

int main() {
    Node* a = makeNode("prog", -1);
    Node* b = makeNode("child1", -1);
    Node* c = makeNode("child2", -1);
    Node* gc1 = makeNode("gc1", -1);
    Node* gc2 = makeNode("gc2", -1);

    a = connectChild(a, b, 0);
    a = connectChild(a, c, 1);
    c = connectChild(c, gc1, 0);
    c = connectChild(c, gc2, 1);

    FILE* file = fopen("syntaxtree.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    writeTreeToFile(a, file);
    fclose(file);

    return 0;
}
