/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {       //key 값과 다음 노드를 가리키는 link를 가진 구조체
	int key;
	struct Node* link;
} listNode;

typedef struct Head {       //첫번째 노드를 가리키는 first를 가진 구조체
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);      //head노드에 동적 메모리 할당하여 생성 후 리턴
int freeList(headNode* h);              //동적 할당 해제

int insertFirst(headNode* h, int key);  //노드의 첫번째에 새로운 노드 삽입
int insertNode(headNode* h, int key);   //입력받은 key값보다 크거나 같은 노드 앞에 새로운 노드 삽입(첫번째 노드부터 검색)
int insertLast(headNode* h, int key);   //노드의 마지막에 새로운 노드 삽입

int deleteFirst(headNode* h);           //첫번째 노드 삭제
int deleteNode(headNode* h, int key);   //입력받은 key값이 있는 노드 삭제(첫번째 노드부터 검색)
int deleteLast(headNode* h);            //마지막 노드 삭제
int invertList(headNode* h);            //리스트의 링크를 역순으로 재 배치 ex)[[0]=1] [[1]=2] [[2]=3] ---> [[2]=3] [[1]=2] [[0]=1]

void printList(headNode* h);            //리스트 출력

int main()
{
	char command;       //선택한 메뉴를 저장할 변수
	int key;            //key값을 저장할 임시 변수
	headNode* headnode=NULL;    //헤드노드 초기화
    printf("[----- [염중화] [2019062038] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");   //메뉴 출력
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);     //메뉴 입력

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);    //headnode생성
			break;
		case 'p': case 'P':
			printList(headnode);                //리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);                  //삽입할 key 값 입력
			insertNode(headnode, key);          //입력받은 key값보다 크거나 같은 노드 앞에 새로운 노드 삽입(첫번째 노드부터 검색)
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);                  //삭제할 key 값 입력
			deleteNode(headnode, key);          //입력받은 key값이 있는 노드 삭제(첫번째 노드부터 검색)
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);                  //삽입할 key 값 입력
			insertLast(headnode, key);          //노드의 마지막에 새로운 노드 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode);               //마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);                  //삽입할 key 값 입력
			insertFirst(headnode, key);         //노드의 첫번째에 새로운 노드 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode);              //첫번째 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);               //리스트의 링크를 역순으로 재 배치
			break;
		case 'q': case 'Q':
			freeList(headnode);                 //동적 할당 해제
			break;
		default:                                //메뉴외에 다른값을 입력받으면 에러문구 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');   //q 또는 Q 입력시 반복문 종료

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;         //head노드의 first 초기화
	return temp;    //head노드 리턴
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;     //head 노드가 가리키는 첫번째 노드를 p에 저장

	listNode* prev = NULL;      //할당된 메모리를 해제할 노드를 임시로 저장할 prev 노드 생성
	while(p != NULL) {          //== head 노드가 가리키는 첫번째 노드가 없을 때까지 반복
		prev = p;               //첫번째 노드를 prev에 저장
		p = p->link;            //첫번째 노드가 가리키는 다음 노드의 주소를 p에 저장
		free(prev);             //메모리 해제
	}
	free(h);                    //head 노드가 할당받은 메모리 해제
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));   //노드 생성
	node->key = key;            //main함수에서 입력 받은 키 값을 생성된 노드의 key에 저장
	node->link = NULL;          //다음 노드를 가리키는 link에 NULL 저장

	if (h->first == NULL)       //첫번째 노드가 없다면
	{
		h->first = node;        //head노드의 first가 생성된 노드를 가리키도록 함(첫번째 노드로 만듦)
		return 0;               //함수 종료
	}

    /*n과 trail사이에 생성된 노드를 삽입*/
	listNode* n = h->first;     //n은 삽입할 노드의 다음 노드
	listNode* trail = h->first; //trail은 노드 삽입전 n의 이전 순서에 있는 노드

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {  //key값을 비교할 노드가 존재하면 반복
		if(n->key >= key) {         //n의 key값이 생성한 노드의 key값보다 크거나 같다면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {     //n이 첫번째 노드이면
				h->first = node;    //head노드의 first가 생성된 노드를 가리키도록 함(첫번째 노드로 만듦)
				node->link = n;     //생성된 노드의 link는 이전의 첫번째 노드를 가리키도록 한다
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n;     //생성된 노드의 link는 n을 가리키도록 한다
				trail->link = node; //n의 이전 순서에 존재하는 노드의 link는 생성된 노드를 가리키도록 한다
			}
			return 0;
		}
        /*key값을 비교할 노드를 다음 노드로 만듦*/
		trail = n;          //trail에 n값 저장
		n = n->link;        //n의 link가 가리키는 노드를 n에 저장(n의 다음 노드를 n으로 만듦)
	}

	/* 마지막 노드까지 key 값이 크거나 같은 노드를 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node;
	return 0;
}

/**
 * list에 마지막에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));   //노드 생성
	node->key = key;            //main함수에서 입력 받은 키 값을 생성된 노드의 key에 저장        
	node->link = NULL;          //다음 노드를 가리키는 link에 NULL 저장

	if (h->first == NULL)       //첫번째 노드가 없다면
	{
		h->first = node;        //head노드의 first가 생성된 노드를 가리키도록 함(첫번째 노드로 만듦)
		return 0;               //함수 종료
	}

	listNode* n = h->first;     
	while(n->link != NULL) {    //n 다음의 노드가 있다면
		n = n->link;            //n을 다음 노드로 만듦
	}
	n->link = node;             //n 다음의 노드가 없다면 n의 link가 생성된 노드를 가리키도록 한다 
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));   //노드 생성
	node->key = key;            //main함수에서 입력 받은 키 값을 생성된 노드의 key에 저장 

	node->link = h->first;      //생성된 노드가 기존의 첫번째 노드를 가리키도록 한다
	h->first = node;            //head노드의 first가 생성된 노드를 가리키도록 한다

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)       //첫번째 노드가 없다면
	{
		printf("nothing to delete.\n"); //에러문구 출력
		return 0;               //함수 종료
	}

	listNode* n = h->first;     //n은 삭제할 노드의 다음 노드     
	listNode* trail = NULL;     //trail은 삭제할 노드의 이전 노드

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {          //n의 다음 노드가 있다면 반복
		if(n->key == key) {     //n의 key값과 생성된 노드의 key값이 같다면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { //n이 첫번째 노드인경우
				h->first = n->link;         //n 다음의 노드를 head노드의 first가 가리키도록 만듦(기존의 두번째 노드를 첫번째 노드로 만듦)
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;      //n이전의 노드 trail의 link가 n의 다음 노드를 가리키도록 만듦
			}
			free(n);    //n에 할당된 메모리 해제
			return 0;   //함수 종료
		}

		trail = n;      //trail에 n값 저장
		n = n->link;    //n의 link가 가리키는 노드를 n에 저장(n의 다음 노드를 n으로 만듦)
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)   //첫번째 노드가 없을 경우
	{
		printf("nothing to delete.\n");
		return 0;           //함수 종료
	}

	listNode* n = h->first; //
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) {   //첫번째 노드의 다음 노드가 없는 경우
		h->first = NULL;    //첫번째 노드 삭제
		free(n);            //첫번째 노드에 할당된 메모리 해제
		return 0;           //함수 종료
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {    //n의 다음 노드가 없을 때까지 반복
		trail = n;              //trail에 n값 저장
		n = n->link;            //n의 link가 가리키는 노드를 n에 저장(n의 다음 노드를 n으로 만듦)
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL;
	free(n);            //마지막 노드에 할당된 메모리 해제

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)   //head노드의 first가 가리키는 노드가 없다면 (첫번째 노드가 없다면)
	{
		printf("nothing to delete.\n");
		return 0;           //함수 종료
	}
	listNode* n = h->first; //n은 head노드의 first가 가리키는 노드

	h->first = n->link;     //head노드의 first가 n의 다음 노드를 가리키도록 만듦
	free(n);                //n(첫번째 노드)에 할당된 메모리 해제

	return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) {  //첫번째 노드가 없다면
		printf("nothing to invert...\n");
		return 0;           //함수 종료
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){           //n이 존재한다면 반복
		trail = middle;         //trail에 middle의 값을 저장
		middle = n;             //middle에 n의 값을 저장
		n = n->link;            //n에 n의 다음 노드를 저장
		middle->link = trail;   //middle의 다음 노드(n)에 trail의 값을 저장
	}

	h->first = middle;          //middle은 재 배치 전의 마지막 노드이고 head노드의 first가 가리키도록 하여 첫번째 노드가 되도록 한다

	return 0;
}

void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {         //head노드가 생성되지 않았을 때
		printf("Nothing to print....\n");
		return;             //함수 종료
	}

	p = h->first;           //p는 첫번째 노드

	while(p != NULL) {      //p가 NULL일때까지 반복
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;        //p의 다음 노드를 p에 저장
		i++;
	}

	printf("  items = %d\n", i);
}

