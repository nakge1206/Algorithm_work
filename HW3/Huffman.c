#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned int size;
    unsigned int capacity;
    struct MinHeapNode** array;
};

struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

struct MinHeap* createMinHeap(unsigned int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, unsigned int idx) {
    unsigned int smallest = idx;
    unsigned int left = 2 * idx + 1;
    unsigned int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    unsigned int i = minHeap->size++;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap) {
    int n = (int)minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, (unsigned int)i);
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap((unsigned int)size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], (unsigned int)freq[i]);
    minHeap->size = (unsigned int)size;
    buildMinHeap(minHeap);
    return minHeap;
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void printCodes(struct MinHeapNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!root->left && !root->right) {
        printf("\'%c\' = ", root->data, root->freq);
        for (int i = 0; i < top; i++)
            printf("%d", arr[i]);
        printf("\n");
    }
}

void HuffmanCodes(char data[], int freq[], int size) {
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);
}

void decodeHuffman(struct MinHeapNode* root, const char* encodedStr) {
    struct MinHeapNode* current = root;
    printf("압축해체 결과 : ");
    for (int i = 0; encodedStr[i] != '\0'; i++) {
        if (encodedStr[i] == '0')
            current = current->left;
        else
            current = current->right;

        if (!current->left && !current->right) {
            printf("%c", current->data);
            current = root;
        }
    }
    printf("\n");
}

int main() {
    FILE *file = fopen("Huffman_input.txt", "r");
    if (!file) {
        printf("파일 열기 실패\n");
        return 1;
    }
    
    int freq[256] = {0};
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        freq[ch]++;
    }
    fclose(file);

    char data[256];
    int frequencies[256];
    int size = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            data[size] = (char)i;
            frequencies[size] = freq[i];
            size++;
        }
    }

    struct MinHeapNode* root = buildHuffmanTree(data, frequencies, size);
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);


    const char* encodedStr = "10110010001110101010100"; // 예제 압축된 문자열
    decodeHuffman(root, encodedStr);

    return 0;
}

