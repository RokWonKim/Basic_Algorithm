#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	struct Node* right;		//���� �ڽ�
	struct Node* left;		//���� �ڽ�
	struct Node* parent;	//�θ�
	int value;				//��
	int color;				//1�̸� ��, 0�̸� ����
}Node;


typedef struct Root {
	Node* nil;			//��� nill���� �ϳ�!
	Node* r;			//�������� root(r->r)
}Root;

Root* r;

void Make_nil(Root* r);
void L_rotation(Root* r, Node* x);
void R_rotation(Root* r, Node* y);
void insertnode(Root* r, int value);
void Restruct(Root* r, Node* x);

int main(void) {
	r = (Root*)malloc(sizeof(Root));
	Make_nil(r);
	insertnode(r, 4);
	insertnode(r, 6);
	insertnode(r, 7);
	insertnode(r, 8);
	insertnode(r, 2);
	insertnode(r, 10);

	printf("%10d[%d]\n", r->r->value, r->r->color);
	printf("%5d[%d]", r->r->left->value, r->r->left->color);
	printf("%10d[%d]\n", r->r->right->value, r->r->right->color);
	printf("%d[%d]", r->r->left->left->value, r->r->left->left->color);
	printf("%10d[%d]", r->r->right->left->value, r->r->right->left->color);
	printf("%5d[%d]", r->r->right->right->value, r->r->right->right->color);
	


	return 0;
}

void Make_nil(Root* r) {
	r->nil = (Node*)malloc(sizeof(Node));	//nill���� NULL����
	(r->nil)->color = 1;					//nill���� �׻� ��
	r->r = r->nil;							//ó�� ��Ʈ�� ����� Ʈ���� ��������Ƿ� NULL
}

//x�� �������� ������ �۾�
void L_rotation(Root* r, Node* x) {
	
	Node* temp = x->right;
	//���� �ڽ��� ���� �ڽĵ��� x�� ���� �ڽĵ�� ����
	//������ �۾� �ǽ�
	x->right = temp->left;

	//���� �ڽ��� ���� �ڽĵ��� �θ� x�� ����
	if (temp->left != r->nil) {
		temp->left->parent = x;
	}
	//���� �ڽ��� �θ� x�� �θ�� ����
	temp->parent = x->parent;

	// �θ� ���� ��, x�� ��Ʈ �� �� ���� �׷���� root�� �� temp�� root�� ����
	if (x->parent == r->nil)	r->r = temp;
	// ���� �θ��� ���� �ڽ��̾����� �θ��� ���ʿ� temp�� ����Ű����
	else if (x == x->parent->left)	x->parent->left = temp;
	// ���� �θ��� ������ �ڽ��̾����� �θ��� �����ʿ� temp�� ����Ű����
	else x->parent->right = temp;

	//���������� temp�� x�� ���θ� ����Ű���� �θ�� �ڽİ����
	temp->left = x;
	x->parent = temp;
}

//x�� ���������� ������ �۾�
void R_rotation(Root* r, Node* x) {

	Node* temp = x->left;
	x->left = temp->right;

	//Null�̶�� �θ� ���������� �ʾƵ� �ǹǷ� Null�� �ƴ� ��쿡 �θ� ����
	if (temp->right != r->nil)	temp->right->parent = x;

	//temp�� x�� �θ� �� ���̹Ƿ� ���� x�� �θ� temp�� �θ�� ����
	temp->parent = x->parent;

	//�θ� Null�̴� ��, �θ� ���� root�� ���
	if (x->parent == r->nil)	r->r = temp;
	//���� �θ��� �����ΰ� �����ΰ��� ���� �θ� ����Ű�� ������ �ٲ� �ڽ�(temp)�� �־���
	else if (x == x->parent->left) x->parent->left = temp;
	else x->parent->right = temp;

	//���������� ������ ���踦 �ٲ��� �θ�-�ڽĿ��� �ڽ��� �θ� �ǰ� �θ� �� �ڽ��� �ǰ� �ٲ�
	temp->right = x;
	x->parent = temp;

}

void insertnode(Root* r, int value) {
	Node* n = (Node*)malloc(sizeof(Node));	//��� ����
	Node* temp = r->r;				// �������� root�������� ����
	Node* parent = r->nil;			// ����� �θ�

	n->left = r->nil;				//ó������ �Ŵϱ� 
	n->right = r->nil;				//�ڽĵ��� ��� null
	n->color = 0;					//���� ���� ����� ����
	n->value = value;				//�� �־��ֱ�

	while (temp != r->nil) {		//�� �ڸ� ã��
		parent = temp;				//���->parent�� ���� �־�����ϴϱ� �����س���
		
		if (value > temp->value) temp = temp->right;	//����Ž��Ʈ�� ����ó��
		else temp = temp->left;
	}

	n->parent = parent;		// ���->parent�� ������ ���� parent�־���

	if (parent == r->nil) r->r = n;		//root�� null���϶�
	else if (value > parent->value) parent->right = n;	//�θ𰪰� ���� �θ��� �������� �������� Ȯ��
	else parent->left = n;	

	Restruct(r, n);
}

//���� �� ����� Ʈ�� ���� ���߱�
void Restruct(Root* r, Node* x) {

	//���� ��� 
	Node* uncle = NULL;
	
	//x�� �θ��� ���� red�̸� ��� ���ư���... x�� �ڵ�ȿ��� ��� �ٲ����
	while ((x->parent)->color == 0) {

		//�θ� ���θ��� ���� �ڽ��� ���
		if (x->parent == (x->parent->parent->left)) {

			//������ ������ �ڽ��̰��� �θ� �����ڽ��̴ϱ�
			uncle = x->parent->parent->right;

			//��, �θ� ���̵� RED�ΰ�� - CASE 1�� �ش�
			//�θ� ���� ������ �ٲٰ� �Ҿƹ��� ����� �ٲ� 
			// -> �Ҿƹ����� �θ� ������ ���� �����Ƿ� Ȯ���� �����
			// -> ��, �Ҿƹ����� x�� while�� �� �� �� ���ƾ� ��
			// -> ���⼭ �Ҿƹ����� �ٲٱ� �� �̹� ���忳�� ���� ����
			// -> �ֳ��ϸ� �θ�� ������ �̹� �����̹Ƿ�
			if (uncle->color == 0) {
				x->parent->color = 1;
				uncle->color = 1;
				x->parent->parent->color = 0;
				x = x->parent->parent;
			}
			//�θ� �����̰� x�� �θ� ������ �ڽ� �϶� - CASE 2-1�� �ش�
			//x�� �θ��� ���� �ڽ����� �ٲ��ְ� �ѹ� �� �۾���
			else {
				if (x == x->parent->right) {
					x = x->parent;
					L_rotation(r, x);	//�������� ȸ��(ȸ���ϸ� CASE 2-2�� ��)
										//�θ��� ���� �ڽ��϶��� �ٲ�(x�� �ٲ���� ����)
				}

				//CASE 2-2 ���� ���� �ٲپ��ְ� ȸ�� ���ֱ�
				x->parent->color = 1;
				x->parent->parent->color = 0;

				R_rotation(r, x->parent->parent);	
			}
		}
		//�θ� ���θ��� ������ �ڽ��� ���(��, if�� �ݴ��Ȳ��)
		else {
			//�θ� ���θ��� �������̴� ������ ����
			uncle = x->parent->parent->left;

			//å�� CASE 1�� ������ ��ġ�� �ٸ� ��Ȳ
			//�׷��� �ڵ�� ����(���� �ٲ��ָ� ��)
			if ( uncle->color == 0 ) {
				x->parent->color = 1;
				uncle->color = 1;

				x->parent->parent->color = 0;

				x = x->parent->parent;
			}
			else {
				//���⸸ �ٲ���� ���̹Ƿ� right_rotate �� left_rotate����
				if (x == x->parent->left) {
					x = x->parent;
					R_rotation(r, x);
				}
				x->parent->color = 1;
				x->parent->parent->color = 0;

				L_rotation(r, x->parent->parent);
			}
		}
	}

	//���� �͵��� �� �����ϰ� ���� ��Ʈ�� RED�� �ٲ���� ���� ����
	//�׷��Ƿ� BLACK���� �ٲپ� �־�� ��
	r->r->color = 1;
}