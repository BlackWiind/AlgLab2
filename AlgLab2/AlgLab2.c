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
void search(Tree* t, int x);                                                 //Поиск по ключу
Tree* isdp(int l, int r, int* A);                                            //Идеально сбалансираванное дерево
void sdp(Tree** t, int d);                                                   //Случайное дерево поиска
bool istree(Tree* t);                                                        //Проверяет является ли дерево двоичным деревом поиска

Tree* root1 = NULL; *root2 = NULL;

int* A;
int n;

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	printf("Введите количество вершин в дереве:\n");
	scanf("%d", &n);
	system("cls");

	A = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		A[i] = rand() % 1000;
	}
	for (int i = 0; i < n; i++) {
		sdp(&root2, A[i]);
	}
	printf("Случайное дерево поиска:\n");
	ltr(root2);
	printf("\n");
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

void search(Tree* t, int x) {
	if (t != NULL) {
		if (t->data < x) {
			search(t->right, x);
		}
		else if (t->data > x) {
			search(t->left, x);
		}
		else {
			printf("Вершина найдена.");
		}
	}
	else {
		printf("Вершина не найдена");
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

void sdp(Tree** t, int d) {
	if ((*t) == NULL) {
		(*t) = (Tree*)malloc(sizeof(Tree));
		(*t)->data = d;
		(*t)->left = (*t)->right = NULL;
	}
	else if ((*t)->data < d) {
		sdp(&((*t)->right), d);
	}
	else if ((*t)->data > d) {
		sdp(&((*t)->left), d);
	}
}

bool istree(Tree* t) {
	if (t != NULL && ((t->left != NULL && (t->data <= t->left->data || istree(t->left))) || (t->right != NULL && (t->data >= t->right->data || !istree(t->right))))) {
		return false;
	}
	return true;
}

int cmp(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}