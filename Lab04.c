#include <stdio.h>
#include <stdlib.h>

typedef struct NODE_s *NODE;
typedef struct NODE_s{
	NODE left;
	NODE right;
	int key;
	void *data;
} NODE_t[1];

typedef struct{
	NODE root;
} BST_t[1], *BST;

typedef struct LINKED_QUEUE_NODE_s *LINKED_QUEUE_NODE;
typedef struct LINKED_QUEUE_NODE_s{
	LINKED_QUEUE_NODE next;
	void *data;
} LINKED_QUEUE_NODE_t[1];

typedef struct LINKED_QUEUE_s{
  	LINKED_QUEUE_NODE head;
  	LINKED_QUEUE_NODE tail;
} LINKED_QUEUE_t[1], *LINKED_QUEUE;

LINKED_QUEUE_NODE linked_queue_node_init() {
	LINKED_QUEUE_NODE new = malloc(sizeof(LINKED_QUEUE_NODE_t));
	new->data = NULL;
	new->next = NULL;
	return new;
}

void *linked_queue_dequeue(LINKED_QUEUE queue) {
	LINKED_QUEUE_NODE res, node;
	node = (LINKED_QUEUE_NODE) queue->head;
	if (node != NULL) {
		queue->head = node->next;
		res = node->data;
	} else {
		printf("Queue is Empty");
	}
	return res;
}

void linked_queue_enqueue(LINKED_QUEUE queue, void *data) {
	LINKED_QUEUE_NODE node = linked_queue_node_init();
	node->data = data;
	if (queue->head == NULL) {
		queue->head = node;
		queue->tail = node;
	} else {
		LINKED_QUEUE_NODE temp = (LINKED_QUEUE_NODE) queue->tail;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = node;
		queue->tail = node;
	}
}

void print(NODE n, int h){
	int i;
	if(n != NULL){
		print(n->right,h+1);
		for(i = 0; i < h; i++) {
			printf("     ");
		}
		printf("%d\n", n->key);
		print(n->left, h+1);
	}
}
NODE bst_init_node(int key, void *data){
	NODE n = (NODE)malloc(sizeof(NODE_t));
	n->left = NULL;
	n->right = NULL;
	n->key = key;
	n->data = data;
	return n;
}

NODE insert_rec(NODE curr, int key, void *data){
	if(curr == NULL){
		curr = bst_init_node(key, data);
	}
	else{
		if(key < curr->key){
			curr->left = insert_rec(curr->left, key, data);
		}
		else if(key > curr->key){
			curr->right = insert_rec(curr->right, key, data);
		}
		else {
			printf("ERROR: Duplicate key: %d. Ignoring...\n\n", key);
		}
	}
	return curr;
}

void insert(BST tree, int key, void *data){
	if(tree != NULL){
		if(tree->root != NULL){
			tree->root = insert_rec(tree->root, key, data);
		}
		else{
			tree->root = bst_init_node(key, data);
		}
	}
	else{
		printf("Invalid tree.\n");
	}
}


BST bst_init(){
	BST t1 = (BST)malloc(sizeof(BST_t));
	t1->root = NULL;
	return t1;
}

void bst_free(BST t){
	//Tentative
	free(t);
}

//BREAK POINT
void traversal(LINKED_QUEUE queue , BST tree){
    NODE node = tree->root;

    linked_queue_enqueue(queue, node);

    while (queue->head != NULL &&  queue->tail != NULL)
    {
        node = linked_queue_dequeue(queue);

        printf("In traversal: %d \n", node->key);

        if(node->left != NULL)
        {
            linked_queue_enqueue(queue, node->left);
        }
        if(node->right != NULL)
        {
            linked_queue_enqueue(queue, node->right);
        }

        free(node);
    }
    tree->root = NULL;
}

int main(int argc, char const *argv[])
{
    BST t1 = bst_init();

	insert(t1, 52, NULL);
	insert(t1, 13, NULL);
	insert(t1, 18, NULL);
	insert(t1, 32, NULL);
	insert(t1, 78, NULL);
	insert(t1, 45, NULL);
	insert(t1, 67, NULL);
	insert(t1, 28, NULL);
	insert(t1, 72, NULL);
	insert(t1, 32, NULL);
	insert(t1, 99, NULL);
	insert(t1, 3, NULL);

	print(t1->root,0);

    LINKED_QUEUE queue = (LINKED_QUEUE)malloc(sizeof(LINKED_QUEUE_t));
    queue->head = NULL;
    queue->tail = NULL;

    traversal(queue, t1);

	bst_free(t1);

    print(t1->root, 0);

    return 0;
}
