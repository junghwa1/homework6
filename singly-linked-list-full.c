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
/* �ʿ��� ������� �߰� */

typedef struct Node {       //key ���� ���� ��带 ����Ű�� link�� ���� ����ü
	int key;
	struct Node* link;
} listNode;

typedef struct Head {       //ù��° ��带 ����Ű�� first�� ���� ����ü
	struct Node* first;
} headNode;


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h);      //head��忡 ���� �޸� �Ҵ��Ͽ� ���� �� ����
int freeList(headNode* h);              //���� �Ҵ� ����

int insertFirst(headNode* h, int key);  //����� ù��°�� ���ο� ��� ����
int insertNode(headNode* h, int key);   //�Է¹��� key������ ũ�ų� ���� ��� �տ� ���ο� ��� ����(ù��° ������ �˻�)
int insertLast(headNode* h, int key);   //����� �������� ���ο� ��� ����

int deleteFirst(headNode* h);           //ù��° ��� ����
int deleteNode(headNode* h, int key);   //�Է¹��� key���� �ִ� ��� ����(ù��° ������ �˻�)
int deleteLast(headNode* h);            //������ ��� ����
int invertList(headNode* h);            //����Ʈ�� ��ũ�� �������� �� ��ġ ex)[[0]=1] [[1]=2] [[2]=3] ---> [[2]=3] [[1]=2] [[0]=1]

void printList(headNode* h);            //����Ʈ ���

int main()
{
	char command;       //������ �޴��� ������ ����
	int key;            //key���� ������ �ӽ� ����
	headNode* headnode=NULL;    //����� �ʱ�ȭ
    printf("[----- [����ȭ] [2019062038] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");   //�޴� ���
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);     //�޴� �Է�

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);    //headnode����
			break;
		case 'p': case 'P':
			printList(headnode);                //����Ʈ ���
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);                  //������ key �� �Է�
			insertNode(headnode, key);          //�Է¹��� key������ ũ�ų� ���� ��� �տ� ���ο� ��� ����(ù��° ������ �˻�)
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);                  //������ key �� �Է�
			deleteNode(headnode, key);          //�Է¹��� key���� �ִ� ��� ����(ù��° ������ �˻�)
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);                  //������ key �� �Է�
			insertLast(headnode, key);          //����� �������� ���ο� ��� ����
			break;
		case 'e': case 'E':
			deleteLast(headnode);               //������ ��� ����
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);                  //������ key �� �Է�
			insertFirst(headnode, key);         //����� ù��°�� ���ο� ��� ����
			break;
		case 't': case 'T':
			deleteFirst(headnode);              //ù��° ��� ����
			break;
		case 'r': case 'R':
			invertList(headnode);               //����Ʈ�� ��ũ�� �������� �� ��ġ
			break;
		case 'q': case 'Q':
			freeList(headnode);                 //���� �Ҵ� ����
			break;
		default:                                //�޴��ܿ� �ٸ����� �Է¹����� �������� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');   //q �Ǵ� Q �Է½� �ݺ��� ����

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;         //head����� first �ʱ�ȭ
	return temp;    //head��� ����
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;     //head ��尡 ����Ű�� ù��° ��带 p�� ����

	listNode* prev = NULL;      //�Ҵ�� �޸𸮸� ������ ��带 �ӽ÷� ������ prev ��� ����
	while(p != NULL) {          //== head ��尡 ����Ű�� ù��° ��尡 ���� ������ �ݺ�
		prev = p;               //ù��° ��带 prev�� ����
		p = p->link;            //ù��° ��尡 ����Ű�� ���� ����� �ּҸ� p�� ����
		free(prev);             //�޸� ����
	}
	free(h);                    //head ��尡 �Ҵ���� �޸� ����
	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));   //��� ����
	node->key = key;            //main�Լ����� �Է� ���� Ű ���� ������ ����� key�� ����
	node->link = NULL;          //���� ��带 ����Ű�� link�� NULL ����

	if (h->first == NULL)       //ù��° ��尡 ���ٸ�
	{
		h->first = node;        //head����� first�� ������ ��带 ����Ű���� ��(ù��° ���� ����)
		return 0;               //�Լ� ����
	}

    /*n�� trail���̿� ������ ��带 ����*/
	listNode* n = h->first;     //n�� ������ ����� ���� ���
	listNode* trail = h->first; //trail�� ��� ������ n�� ���� ������ �ִ� ���

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {  //key���� ���� ��尡 �����ϸ� �ݺ�
		if(n->key >= key) {         //n�� key���� ������ ����� key������ ũ�ų� ���ٸ�
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {     //n�� ù��° ����̸�
				h->first = node;    //head����� first�� ������ ��带 ����Ű���� ��(ù��° ���� ����)
				node->link = n;     //������ ����� link�� ������ ù��° ��带 ����Ű���� �Ѵ�
			} else { /* �߰��̰ų� �������� ��� */
				node->link = n;     //������ ����� link�� n�� ����Ű���� �Ѵ�
				trail->link = node; //n�� ���� ������ �����ϴ� ����� link�� ������ ��带 ����Ű���� �Ѵ�
			}
			return 0;
		}
        /*key���� ���� ��带 ���� ���� ����*/
		trail = n;          //trail�� n�� ����
		n = n->link;        //n�� link�� ����Ű�� ��带 n�� ����(n�� ���� ��带 n���� ����)
	}

	/* ������ ������ key ���� ũ�ų� ���� ��带 ã�� ���� ��� , �������� ���� */
	trail->link = node;
	return 0;
}

/**
 * list�� �������� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));   //��� ����
	node->key = key;            //main�Լ����� �Է� ���� Ű ���� ������ ����� key�� ����        
	node->link = NULL;          //���� ��带 ����Ű�� link�� NULL ����

	if (h->first == NULL)       //ù��° ��尡 ���ٸ�
	{
		h->first = node;        //head����� first�� ������ ��带 ����Ű���� ��(ù��° ���� ����)
		return 0;               //�Լ� ����
	}

	listNode* n = h->first;     
	while(n->link != NULL) {    //n ������ ��尡 �ִٸ�
		n = n->link;            //n�� ���� ���� ����
	}
	n->link = node;             //n ������ ��尡 ���ٸ� n�� link�� ������ ��带 ����Ű���� �Ѵ� 
	return 0;
}

/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));   //��� ����
	node->key = key;            //main�Լ����� �Է� ���� Ű ���� ������ ����� key�� ���� 

	node->link = h->first;      //������ ��尡 ������ ù��° ��带 ����Ű���� �Ѵ�
	h->first = node;            //head����� first�� ������ ��带 ����Ű���� �Ѵ�

	return 0;
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)       //ù��° ��尡 ���ٸ�
	{
		printf("nothing to delete.\n"); //�������� ���
		return 0;               //�Լ� ����
	}

	listNode* n = h->first;     //n�� ������ ����� ���� ���     
	listNode* trail = NULL;     //trail�� ������ ����� ���� ���

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {          //n�� ���� ��尡 �ִٸ� �ݺ�
		if(n->key == key) {     //n�� key���� ������ ����� key���� ���ٸ�
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) { //n�� ù��° ����ΰ��
				h->first = n->link;         //n ������ ��带 head����� first�� ����Ű���� ����(������ �ι�° ��带 ù��° ���� ����)
			} else { /* �߰��� ���ų� �������� ��� */
				trail->link = n->link;      //n������ ��� trail�� link�� n�� ���� ��带 ����Ű���� ����
			}
			free(n);    //n�� �Ҵ�� �޸� ����
			return 0;   //�Լ� ����
		}

		trail = n;      //trail�� n�� ����
		n = n->link;    //n�� link�� ����Ű�� ��带 n�� ����(n�� ���� ��带 n���� ����)
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)   //ù��° ��尡 ���� ���
	{
		printf("nothing to delete.\n");
		return 0;           //�Լ� ����
	}

	listNode* n = h->first; //
	listNode* trail = NULL;

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->link == NULL) {   //ù��° ����� ���� ��尡 ���� ���
		h->first = NULL;    //ù��° ��� ����
		free(n);            //ù��° ��忡 �Ҵ�� �޸� ����
		return 0;           //�Լ� ����
	}

	/* ������ ������ �̵� */
	while(n->link != NULL) {    //n�� ���� ��尡 ���� ������ �ݺ�
		trail = n;              //trail�� n�� ����
		n = n->link;            //n�� link�� ����Ű�� ��带 n�� ����(n�� ���� ��带 n���� ����)
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->link = NULL;
	free(n);            //������ ��忡 �Ҵ�� �޸� ����

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)   //head����� first�� ����Ű�� ��尡 ���ٸ� (ù��° ��尡 ���ٸ�)
	{
		printf("nothing to delete.\n");
		return 0;           //�Լ� ����
	}
	listNode* n = h->first; //n�� head����� first�� ����Ű�� ���

	h->first = n->link;     //head����� first�� n�� ���� ��带 ����Ű���� ����
	free(n);                //n(ù��° ���)�� �Ҵ�� �޸� ����

	return 0;
}

/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {


	if(h->first == NULL) {  //ù��° ��尡 ���ٸ�
		printf("nothing to invert...\n");
		return 0;           //�Լ� ����
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){           //n�� �����Ѵٸ� �ݺ�
		trail = middle;         //trail�� middle�� ���� ����
		middle = n;             //middle�� n�� ���� ����
		n = n->link;            //n�� n�� ���� ��带 ����
		middle->link = trail;   //middle�� ���� ���(n)�� trail�� ���� ����
	}

	h->first = middle;          //middle�� �� ��ġ ���� ������ ����̰� head����� first�� ����Ű���� �Ͽ� ù��° ��尡 �ǵ��� �Ѵ�

	return 0;
}

void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {         //head��尡 �������� �ʾ��� ��
		printf("Nothing to print....\n");
		return;             //�Լ� ����
	}

	p = h->first;           //p�� ù��° ���

	while(p != NULL) {      //p�� NULL�϶����� �ݺ�
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;        //p�� ���� ��带 p�� ����
		i++;
	}

	printf("  items = %d\n", i);
}

