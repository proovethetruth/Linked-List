
#include <stdio.h>
#include <malloc.h>

typedef struct node_t {
	int value;
	struct node_t* next;							// узел следующий
	struct node_t* prev;							// узел предыдущий
} node_t;

typedef struct {
	node_t* head;							// адрес нулевого элемента
	size_t size;							// кол-во элементов
} list_t;

void init(list_t* l){						// O(1)
	l->head = NULL;
	l->size = 0;
}

void destroy(list_t* l) {					// O(n)
	node_t* cur = l->head;
	node_t* prev = NULL;
	while (cur != NULL) {
		prev = cur;
		cur = cur->next;
		free(prev);
	}
}

void push_back(list_t* l, int val) {		// O(n)
	node_t* n, * cur;
	n = (node_t*)malloc(sizeof(node_t));
	n->value = val;
	n->next = NULL;
	if (l->head == NULL) {
		n->prev = NULL;
		l->head = n;
	}
	else {
		cur = l->head;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = n;
		n->prev = cur;
	}
	l->size++;
	printf(" %d\n", val);
}

void print(list_t* l) {
	node_t* cur = l->head;
	while (cur != NULL) {

		printf("%d | ", cur->value);
		cur = cur->next;
	}
	printf("\n");
}

void set(list_t* l, int i, int val) {		// O(n)
	node_t* cur = l->head;
	int count = 0;
	if (i < 0 || i >= l->size) {
		printf("\n\a ERROR in SET function: Incorrect index (%d)\n", i);
		return;
	}
	while (count != i) {
		cur = cur->next;
		count++;
	}
	cur->value = val;
}

void insert(list_t *l, node_t* cur, int val) {
	node_t* n = (node_t*)malloc(sizeof(node_t));
	n->value = val;
	n->next = cur->next;
	n->prev = cur;
	cur->next->prev = n;
	l->size++;
}

void erase(list_t* l, node_t* cur) {		// O(n)
	if (cur == l->head) {
		l->head = cur->next;
		if (cur->next != NULL)
			cur->next->prev = NULL;
		free(cur);
	}
	else {
		cur->prev->next = cur->next;
		if (cur->next != NULL)
			cur->next->prev = cur->prev;
		free(cur);
	}
	l->size--;
}

int main() {
	list_t l;
	node_t* cur;
	init(&l);
	for (int i = 0; i < 100; i++)
		push_back(&l, i);
	printf("%p", l.head);
	for (cur = l.head; cur->value != NULL; cur = cur->next)
	{
		if (cur->value % 2 == 0) {
			insert(&l, &cur, 0);
			cur = cur->next;
		}
	}
	print(&l);
	destroy(&l);
	return 0;
}