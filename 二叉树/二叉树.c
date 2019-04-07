#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

typedef struct Tree {
	char value;
	struct Tree *left;
	struct Tree* right;
}Tree;

//�������
Tree *creatNode(char value) {
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	tree->value = value;
	tree->left = NULL;
	tree->right = NULL;
	return tree;
}

//һ.���ֱ����������ķ�ʽ
//	1.�������������
void preOrder(Tree* root) {
	//�Ƚ����п�
	if (root == NULL) {
		return;
	}
	//��������Ϊ�գ���ʼ�����������������
	printf("%c  ", root->value);
	preOrder(root->left);
	preOrder(root->right);
	return;
}

//	2.�������������
void midOrder(Tree* root) {
	//�Ƚ����п�
	if (root == NULL) {
		return;
	}
	//��Ϊ��,����������󡢸�����
	midOrder(root->left);
	printf("%c  ", root->value);
	midOrder(root->right);
	return;
}

//	3.�������������
void subOrder(Tree* root) {
	//�Ƚ����п�
	if (root == NULL) {
		return;
	}
	//�ǿգ����к�����������ҡ���
	subOrder(root->left);
	subOrder(root->right);
	printf("%c  ", root->value);
	return;
}

int count;//��������������еĽڵ����
//��.��������Ľ�����
//	1.������ֱ�����ʽ���м������ɣ�������Ϊ��
int numNode(Tree* root) {
	//���Ϊ�գ�����0
	if (root == NULL) {
		return 0;
	}
	//�ǿգ���������
	count++;
	numNode(root->left);
	numNode(root->right);
	return count;
}

//	2.�ֶ���֮����+��+��
int numNode2(Tree* root) {
	//�½����п�
	if (root == NULL) {
		return 0;
	}
	return numNode2(root->left) + numNode2(root->right) + 1;
}

//��.������������
int depthTree(Tree* root) {
	//�Ƚ����п�
	if (root == NULL) {
		return 0;
	}
	//�ǿգ���ʼ���м���,MAX������������ȣ�����������ȣ�+��
	int left = depthTree(root->left);
	int right = depthTree(root->right);
	return (left > right ? left : right) + 1;
}

//��.��������ĵ�k��Ľ�����
int kLevelSize(Tree* root,int k) {
	//�Ƚ����п�
	if (root == NULL) {
		return 0;
	}
	if (k == 1) {
		return 1;
	}
	//��ʼ���м�������������k-1��Ľڵ���+��������k-1��Ľڵ���
	return kLevelSize(root->left, k - 1) + kLevelSize(root->right, k - 1);
}

//��.���ҽ�㣬���������ַ
Tree* find(Tree* root, char val) {
	//���п�
	if (root == NULL) {
		return NULL;
	}
	//���жϸ��ڵ��Ƿ���Ŀ��ڵ�
	if (root->value == val) {
		return root;
	}
	//���ڵ㲻�ǣ�������������������û�У��ٲ���������
	//��ʼ����������
	Tree* result = find(root->left,val);
	if (result != NULL) {
		//˵���ҵ���
		return result;
	}
	//��������û�ҵ������������в���
	result = find(root->right, val);
	if (result != NULL) {
		//˵���ҵ��ˣ��������ַ
		return result;
	}
	//���������������ˣ�û�ҵ�������NULL
	return NULL;
}

//��.�ж����Ŷ������Ƿ�Ϊ����
bool isMirror(Tree* p, Tree* q) {
	//�Ƚ����п�
	//���Ŷ��ǿ��������ǻ�Ϊ����
	if (p == NULL && q == NULL) {
		return true;
	}
	//ֻ������һ��Ϊ�գ����ǻ�Ϊ����
	if (p == NULL || q == NULL) {
		return false;
	}
	//��ͨ�����жϣ�p��������������ֵ==q��������������ֵ
	return p->value == q->value&&
		isMirror(p->left, q->right) &&
		isMirror(p->right, q->left);
}


void test() {
	Tree *a = creatNode('A');
	Tree *b = creatNode('B');
	Tree *c = creatNode('C');
	Tree *d = creatNode('D');
	Tree *e = creatNode('E');
	Tree *f = creatNode('F');
	Tree *g = creatNode('G');
	Tree *h = creatNode('H');
	//����������
	a->left = b; a->right = c;
	b->left = d; b->right = e;
	e->right = h;
	c->left = f; c->right = g;
	//һ.����������
	//	1.�������
	printf("���������");
	preOrder(a);
	//	2.�������
	printf("\n���������");
	midOrder(a);
	//	3.�������
	printf("\n���������");
	subOrder(a);
	//��.�������Ľ�������
	count = 0;
	numNode(a);
	printf("\n�����õ��������Ľ�����Ϊ��%d", count);
	printf("\n�ֶ���֮��˼��õ��Ľ�����Ϊ��%d", numNode2(a));
	//��.������������	
	printf("\n�ö����������Ϊ��%d", depthTree(a));
	//��.��������ĵ�k��Ľ�����
	printf("\n��3��Ľ����Ŀ�ǣ�%d", kLevelSize(a, 3));
	//��.����
	Tree* node = find(a, 'E');
	printf("\n���ҽ��E�����ĵ�ַ�ǣ�%p,����ֵ�ǣ�%c", node,node->value);
	//��.�ж����ö������Ƿ�Ϊ����
	//	1.�������ö�����
	Tree *aa = creatNode('A');
	Tree *bb = creatNode('B');
	Tree *cc = creatNode('C');
	Tree *dd = creatNode('D');
	Tree *ee = creatNode('E');
	Tree *ff = creatNode('F');
	aa->left = bb; aa->right = cc;
	bb->left = dd;
	cc->left = ee; cc->right = ff;

	Tree *aaa = creatNode('A');
	Tree *bbb = creatNode('B');
	Tree *ccc = creatNode('C');
	Tree *ddd = creatNode('D');
	Tree *eee = creatNode('E');
	Tree *fff = creatNode('F');
	aaa->left = ccc; aaa->right = bbb;
	ccc->left = fff; ccc->right = eee;
	bbb->right = ddd;
	//��ʼ�����ж��Ƿ�Ϊ����
	bool k = isMirror(aa, aaa);
	printf("\n��������Ϊ����%d", k);
	printf("\n");
}


int main() {
	test();
	system("pause");
	return 0;
}