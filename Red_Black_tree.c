#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	struct Node* right;		//우측 자식
	struct Node* left;		//좌측 자식
	struct Node* parent;	//부모
	int value;				//값
	int color;				//1이면 블랙, 0이면 레드
}Node;


typedef struct Root {
	Node* nil;			//모든 nill노드는 하나!
	Node* r;			//실질적인 root(r->r)
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
	r->nil = (Node*)malloc(sizeof(Node));	//nill노드는 NULL값임
	(r->nil)->color = 1;					//nill노드는 항상 블랙
	r->r = r->nil;							//처음 루트를 만들면 트리는 비어있으므로 NULL
}

//x를 왼쪽으로 돌리는 작업
void L_rotation(Root* r, Node* x) {
	
	Node* temp = x->right;
	//우측 자식의 왼쪽 자식들을 x가 우측 자식들로 받음
	//돌리기 작업 실시
	x->right = temp->left;

	//우측 자식의 좌측 자식들의 부모를 x로 설정
	if (temp->left != r->nil) {
		temp->left->parent = x;
	}
	//우측 자식의 부모를 x의 부모로 설정
	temp->parent = x->parent;

	// 부모가 없다 즉, x가 루트 일 수 있음 그럴경우 root가 될 temp를 root로 설정
	if (x->parent == r->nil)	r->r = temp;
	// 원래 부모의 왼쪽 자식이었으면 부모의 왼쪽에 temp를 가리키도록
	else if (x == x->parent->left)	x->parent->left = temp;
	// 원래 부모의 오른쪽 자식이었으면 부모의 오른쪽에 temp를 가리키도록
	else x->parent->right = temp;

	//마지막으로 temp와 x가 서로를 가리키도록 부모와 자식관계로
	temp->left = x;
	x->parent = temp;
}

//x를 오른쪽으로 돌리는 작업
void R_rotation(Root* r, Node* x) {

	Node* temp = x->left;
	x->left = temp->right;

	//Null이라면 부모를 설정해주지 않아도 되므로 Null이 아닐 경우에 부모를 설정
	if (temp->right != r->nil)	temp->right->parent = x;

	//temp가 x의 부모가 될 것이므로 원래 x의 부모를 temp의 부모로 만듬
	temp->parent = x->parent;

	//부모가 Null이다 즉, 부모가 없는 root일 경우
	if (x->parent == r->nil)	r->r = temp;
	//원래 부모의 우측인가 좌측인가를 보고 부모가 가리키는 곳으로 바뀐 자식(temp)을 넣어줌
	else if (x == x->parent->left) x->parent->left = temp;
	else x->parent->right = temp;

	//마지막으로 서로의 관계를 바꿔줌 부모-자식에서 자식이 부모가 되고 부모가 그 자식이 되게 바꿈
	temp->right = x;
	x->parent = temp;

}

void insertnode(Root* r, int value) {
	Node* n = (Node*)malloc(sizeof(Node));	//노드 생성
	Node* temp = r->r;				// 실질적인 root에서부터 시작
	Node* parent = r->nil;			// 노드의 부모

	n->left = r->nil;				//처음들어가는 거니까 
	n->right = r->nil;				//자식들은 모두 null
	n->color = 0;					//삽입 노드는 레드로 시작
	n->value = value;				//값 넣어주기

	while (temp != r->nil) {		//들어갈 자리 찾기
		parent = temp;				//노드->parent에 값을 넣어줘야하니까 저장해놓음
		
		if (value > temp->value) temp = temp->right;	//이진탐색트리 삽입처럼
		else temp = temp->left;
	}

	n->parent = parent;		// 노드->parent에 위에서 구한 parent넣어줌

	if (parent == r->nil) r->r = n;		//root가 null값일때
	else if (value > parent->value) parent->right = n;	//부모값과 비교해 부모의 우측인지 좌측인지 확인
	else parent->left = n;	

	Restruct(r, n);
}

//삽입 후 레드블랙 트리 조건 맞추기
void Restruct(Root* r, Node* x) {

	//삼촌 노드 
	Node* uncle = NULL;
	
	//x의 부모의 색이 red이면 계속 돌아간다... x는 코드안에서 계속 바뀔거임
	while ((x->parent)->color == 0) {

		//부모가 조부모의 왼쪽 자식일 경우
		if (x->parent == (x->parent->parent->left)) {

			//삼촌은 오른쪽 자식이겠지 부모가 왼쪽자식이니까
			uncle = x->parent->parent->right;

			//즉, 부모도 삼촌도 RED인경우 - CASE 1에 해당
			//부모 삼촌 블랙으로 바꾸고 할아버지 레드로 바꿈 
			// -> 할아버지의 부모가 레드일 수도 있으므로 확인해 줘야함
			// -> 즉, 할아버지를 x로 while문 한 번 더 돌아야 함
			// -> 여기서 할아버지가 바꾸기 전 이미 레드엿을 경우는 없음
			// -> 왜냐하면 부모랑 삼촌이 이미 레드이므로
			if (uncle->color == 0) {
				x->parent->color = 1;
				uncle->color = 1;
				x->parent->parent->color = 0;
				x = x->parent->parent;
			}
			//부모가 레드이고 x가 부모 오른쪽 자식 일때 - CASE 2-1에 해당
			//x가 부모의 왼쪽 자식으로 바꿔주고 한번 더 작업함
			else {
				if (x == x->parent->right) {
					x = x->parent;
					L_rotation(r, x);	//왼쪽으로 회전(회전하면 CASE 2-2가 됨)
										//부모의 왼쪽 자식일때로 바뀜(x도 바뀌었기 때문)
				}

				//CASE 2-2 먼저 색을 바꾸어주고 회전 해주기
				x->parent->color = 1;
				x->parent->parent->color = 0;

				R_rotation(r, x->parent->parent);	
			}
		}
		//부모가 조부모의 오른쪽 자식일 경우(즉, if와 반대상황임)
		else {
			//부모가 조부모의 오른쪽이니 삼촌은 왼쪽
			uncle = x->parent->parent->left;

			//책의 CASE 1과 같지만 위치가 다른 상황
			//그러나 코드는 같다(색깔만 바꿔주면 됌)
			if ( uncle->color == 0 ) {
				x->parent->color = 1;
				uncle->color = 1;

				x->parent->parent->color = 0;

				x = x->parent->parent;
			}
			else {
				//방향만 바뀌었을 뿐이므로 right_rotate 후 left_rotate실행
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

	//위의 것들을 다 실행하고 나서 루트가 RED로 바뀌었을 수도 있음
	//그러므로 BLACK으로 바꾸어 주어야 함
	r->r->color = 1;
}