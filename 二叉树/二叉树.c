#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

typedef struct Tree {
	char value;
	struct Tree *left;
	struct Tree* right;
}Tree;

//创建结点
Tree *creatNode(char value) {
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	tree->value = value;
	tree->left = NULL;
	tree->right = NULL;
	return tree;
}

//一.三种遍历二叉树的方式
//	1.先序遍历二叉树
void preOrder(Tree* root) {
	//先进行判空
	if (root == NULL) {
		return;
	}
	//二叉树不为空，开始先序遍历：根、左、右
	printf("%c  ", root->value);
	preOrder(root->left);
	preOrder(root->right);
	return;
}

//	2.中序遍历二叉树
void midOrder(Tree* root) {
	//先进行判空
	if (root == NULL) {
		return;
	}
	//不为空,中序遍历：左、根、右
	midOrder(root->left);
	printf("%c  ", root->value);
	midOrder(root->right);
	return;
}

//	3.后序遍历二叉树
void subOrder(Tree* root) {
	//先进行判空
	if (root == NULL) {
		return;
	}
	//非空，进行后序遍历：左、右、根
	subOrder(root->left);
	subOrder(root->right);
	printf("%c  ", root->value);
	return;
}

int count;//用来计算二叉树中的节点个数
//二.求二叉树的结点个数
//	1.随便哪种遍历方式进行计数即可，以先序为例
int numNode(Tree* root) {
	//如果为空，返回0
	if (root == NULL) {
		return 0;
	}
	//非空，遍历计数
	count++;
	numNode(root->left);
	numNode(root->right);
	return count;
}

//	2.分而治之：左+右+根
int numNode2(Tree* root) {
	//新进行判空
	if (root == NULL) {
		return 0;
	}
	return numNode2(root->left) + numNode2(root->right) + 1;
}

//三.求二叉树的深度
int depthTree(Tree* root) {
	//先进行判空
	if (root == NULL) {
		return 0;
	}
	//非空，开始进行计数,MAX（左子树的深度，右子树的深度）+根
	int left = depthTree(root->left);
	int right = depthTree(root->right);
	return (left > right ? left : right) + 1;
}

//四.求二叉树的第k层的结点个数
int kLevelSize(Tree* root,int k) {
	//先进行判空
	if (root == NULL) {
		return 0;
	}
	if (k == 1) {
		return 1;
	}
	//开始进行计数，左子树的k-1层的节点数+右子树的k-1层的节点数
	return kLevelSize(root->left, k - 1) + kLevelSize(root->right, k - 1);
}

//五.查找结点，并返回其地址
Tree* find(Tree* root, char val) {
	//先判空
	if (root == NULL) {
		return NULL;
	}
	//再判断根节点是否是目标节点
	if (root->value == val) {
		return root;
	}
	//根节点不是，查找左子树，左子树没有，再查找右子树
	//开始查找左子树
	Tree* result = find(root->left,val);
	if (result != NULL) {
		//说明找到了
		return result;
	}
	//左子树中没找到，在右子树中查找
	result = find(root->right, val);
	if (result != NULL) {
		//说明找到了，返回其地址
		return result;
	}
	//整棵树都查找完了，没找到，返回NULL
	return NULL;
}

//六.判断两颗二叉树是否互为镜像
bool isMirror(Tree* p, Tree* q) {
	//先进性判空
	//两颗都是空树，就是互为镜像
	if (p == NULL && q == NULL) {
		return true;
	}
	//只有其中一棵为空，不是互为镜像
	if (p == NULL || q == NULL) {
		return false;
	}
	//普通树的判断，p二叉树左子树的值==q二叉树右子树的值
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
	//构建二叉树
	a->left = b; a->right = c;
	b->left = d; b->right = e;
	e->right = h;
	c->left = f; c->right = g;
	//一.遍历二叉树
	//	1.先序遍历
	printf("先序遍历：");
	preOrder(a);
	//	2.中序遍历
	printf("\n中序遍历：");
	midOrder(a);
	//	3.后序遍历
	printf("\n后序遍历：");
	subOrder(a);
	//二.二叉树的结点个数：
	count = 0;
	numNode(a);
	printf("\n遍历得到二叉树的结点个数为：%d", count);
	printf("\n分而治之的思想得到的结点个数为：%d", numNode2(a));
	//三.求二叉树的深度	
	printf("\n该二叉树的深度为：%d", depthTree(a));
	//四.求二叉树的第k层的结点个数
	printf("\n第3层的结点数目是：%d", kLevelSize(a, 3));
	//五.查找
	Tree* node = find(a, 'E');
	printf("\n查找结点E，它的地址是：%p,它的值是：%c", node,node->value);
	//六.判断两棵二叉树是否互为镜像
	//	1.创建两棵二叉树
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
	//开始进行判断是否互为镜像
	bool k = isMirror(aa, aaa);
	printf("\n两棵树互为镜像：%d", k);
	printf("\n");
}


int main() {
	test();
	system("pause");
	return 0;
}