#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>

struct tnode                                                                 //дерево
{
	int data;
	struct tnode* left;
	struct tnode* right;
};

typedef struct tnode Tree;

int cmp(const void* a, const void* b);                                       //Для упорядочивания массива
int tsize(Tree* t);                                                          //Размер дерева
int theight(Tree* t);                                                        //Высота дерева
int tmiddleh(Tree* t, int l);                                                //Средняя высота дерева
int csumm(Tree* t);                                                          //Контрольная сумма
void ltr(Tree* t);                                                           //Обход слева направо
Tree* isdp(int l, int r, int* A);                                            //Идеально сбалансираванное дерево

Tree* root1 = NULL; *root2 = NULL;

int* A;
int n;

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	printf("Введите количество вершин в дереве:\n");
	scanf_s("%d", &n);
	system("cls");

	A = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		A[i] = rand() % 1000;
	}	
	root1 = isdp(0, n - 1, A);
	printf("Идеально сбалансированное дерево поиска:\n");
	ltr(root1);
	printf("\n");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("+++++++++++|Размер|Высота|Средняя высота|контр. сумма|++++++++++++++++++++++++++++++++\n");
	printf("+ИСДП %10d %7d %10.2f %15d\n", tsize(root1), theight(root1), (double)tmiddleh(root1, 1) / tsize(root1), csumm(root1));
	printf("++СДП %10d %7d %10.2f %15d\n", tsize(root2), theight(root2), (double)tmiddleh(root2, 1) / tsize(root2), csumm(root2));
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	getch();
	return EXIT_SUCCESS;
}

int tsize(Tree* t) {
	if (t == NULL) {
		return 0;
	}
	else {
		return 1 + tsize(t->left) + tsize(t->right);
	}
}

int theight(Tree* t) {
	if (t == NULL) {
		return 0;
	}
	else {
		return 1 + max(theight(t->left), theight(t->right));
	}
}

int tmiddleh(Tree* t, int l) {
	if (t == NULL) {
		return 0;
	}
	else {
		return l + tmiddleh(t->left, l + 1) + tmiddleh(t->right, l + 1);
	}
}

int csumm(Tree* t) {
	if (t == NULL) {
		return 0;
	}
	else {
		return t->data + csumm(t->left) + csumm(t->right);
	}
}

void ltr(Tree* t) {
	if (t != NULL) {
		ltr(t->left);
		printf("%d%s", t->data, " ");
		ltr(t->right);
	}
}

Tree* isdp(int l, int r, int* A) {
	qsort(A, n, sizeof(int), cmp);
	int k;
	Tree* t;
	if (l > r) return NULL;
	else {
		k = (l + r) / 2;
		t = (Tree*)malloc(sizeof(Tree));
		if (t == NULL) { printf("Error!"); exit(1); }
		/*/struct tnode* t;
		struct tnode t;*/
		t->data = A[k];
		t->left = isdp(l, k - 1, A);
		t->right = isdp(k + 1, r, A);
		return t;
	}
}

int cmp(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}