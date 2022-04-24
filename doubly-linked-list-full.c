/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>//standard input/output library, 표준 입출력 라이브러리
#include<stdlib.h>//c표준 유틸리티 함수들을 모아 놓은 헤더파일
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {//구조체 선언
	int key;//int 형 변수 key 멤버 선언
	struct Node* llink;//자기참조 구조체
	struct Node* rlink;//자기참조 구조체
} listNode;//구조체 별칭



typedef struct Head {//구조체 선언
	struct Node* first;//중첩 구조체
}headNode;//구조체 별칭

/* 함수 리스트 */
//함수 원형선언

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()//메인함수
{
	char command;//char형 변수 선언, 명령어
	int key;////int형 변수 선언, 키보드
	headNode* headnode=NULL;//headnode의 값을 NULL로 초기화

	printf("[----- [Yuseong Jin] [2018038022] -----]");//이름, 학번 출력

	do{//do-while문을 통하여 반복 출력
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
		//메뉴 출력
		printf("Command = ");
		scanf(" %c", &command);
		//명령어 입력받기

		switch(command) {//스위치문
		//소문자와 대문자 모두 입력 받기
		case 'z': case 'Z'://z키를 입력 받았을 때
			initialize(&headnode);//initialize함수 실행
			break;//스위치문 끝
		case 'p': case 'P'://p키를 입력 받았을 때
			printList(headnode);//printList함수 실행
			break;//스위치문 끝
		case 'i': case 'I'://i키를 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);
			//키 값 입력받기
			insertNode(headnode, key);//insertNode함수 실행
			break;//스위치문 끝
		case 'd': case 'D'://d키를 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);
			//키 값 입력받기
			deleteNode(headnode, key);//deleteNode 함수 실행
			break;//스위치문 끝
		case 'n': case 'N'://n키를 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);
			//키 값 입력받기
			insertLast(headnode, key);//insertLast 함수 실행
			break;//스위치문 끝
		case 'e': case 'E'://e키를 입력 받았을 때
			deleteLast(headnode);//deleteLast함수 실행
			break;//스위치문 끝
		case 'f': case 'F'://f키를 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);
			//키 값 입력받기
			insertFirst(headnode, key);//insertFirst함수 실행
			break;//스위치문 끝
		case 't': case 'T'://t키를 입력 받았을 때
			deleteFirst(headnode);//deleteFirst 함수 실행
			break;//스위치문 끝
		case 'r': case 'R'://r키를 입력 받았을 때
			invertList(headnode);//invertList 함수 실행
			break;//스위치문 끝
		case 'q': case 'Q'://q키를 입력 받았을 때
			freeList(headnode);//freeList 함수 실행
			break;//스위치문 끝
		default://이 외의 입력을 받았을 때 
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			//경고문 출력
			break;//스위치문 끝
		}

	}while(command != 'q' && command != 'Q');
	//q키를 사용하기 전까지 계속 반복

	return 1;//종료
}


int initialize(headNode** h) {//초기화 함수

	// headNode가 NULL이 아니면, 
	if(*h != NULL)
	//freeNode를 호출하여 할당된 메모리 모두 해제
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;//머리노드가 가르키는 값을 NULL로 초기화
	return 1;//종료
}

int freeList(headNode* h){//리스트 할당해제 함수
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;
	//listnode 포인트 변수 p 선언 후 머리노드가 가르키는 값 대입

	listNode* prev = NULL;
	//listnode 포인트 변수 prev 선언 후 NULL로 초기화
	while(p != NULL) {//p가 NULL값이 아니라면
		prev = p;//prev를 p로 초기화
		p = p->rlink;//p에 rlink값 대입
		free(prev);//prev 할당해제
	}
	free(h);//h 할당해제
	return 0;//종료
}


void printList(headNode* h) {//list출력 함수
	int i = 0;//int형 변수 i선언 후 0으로 초기화
	listNode* p;//listnode 포인트 변수 p 선언

	printf("\n---PRINT\n");

	if(h == NULL) {//headnode가 NULL이라면
		printf("Nothing to print....\n");
		//출력할 내용이 없음을 출력
		return;//종료
	}

	p = h->first;//p에 머리노드가 가르키는 값 대입

	while(p != NULL) {//p가 NULL이 아닐 때
		printf("[ [%d]=%d ] ", i, p->key);
		//i, 입력한 키 값 출력
		p = p->rlink;//다음 노드를 가르킴
		i++;//i값 증감
	}

	printf("  items = %d\n", i);//입력한 노드 수 출력
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {//마지막 삽입 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));
	//listnode 포인터 변수 node 선언후 동적 메모리 할당 
	node->key = key;
	//node의 key 값에 key값 대입
	node->rlink = NULL;
	node->llink = NULL;
	//rlink와 llink를 순서대로 NULL로 초기화

	if (h->first == NULL)
	//머리헤드가 가르키는 값이 NULL일 떄
	{
		h->first = node;
		//node 값을 머리헤드가 가르키는 값에 대입
		return 0;//종료
	}

	listNode* n = h->first;
	//listnode 포인터 변수 n 선언후 머리헤드가 가르키는 값 대입
	while(n->rlink != NULL) {
		//rlink값이 NULL이 아니라면
		n = n->rlink;//rlink를 n에 대입
	}
	n->rlink = node;//node를 rlink에 대입
	node->llink = n;//n을 link에 대입
	return 0;//종료
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {//마지막삭제 함수

	if (h->first == NULL)//머리헤드가 가르키는 값이 NULL일 떄
	{
		printf("nothing to delete.\n");
		//삭제할 내용이 없음을 출력
		return 0;//종료
	}

	listNode* n = h->first;
	//리스트노드 포인트변수 n 선언 후 머리헤드가 가르키는 값 대입
	listNode* trail = NULL;
	//리스트노드 포인트변수 trail 선언 후 NULL로 초기화

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) {
		h->first = NULL;//머리노드가 가르키는 값이 NULL로 초기화
		free(n);//n 할당해제
		return 0;//종료
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) {
		trail = n;//trail에 n대입  
		n = n->rlink;//rlink값 n에 대입
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL;
	free(n);//n 할당해제

	return 0;
	//종료
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	//list 처음에 key에 대한 노드하나를 추가함수

	listNode* node = (listNode*)malloc(sizeof(listNode));
	//listnode 포인터 변수 node 선언후 동적 메모리 할당 
	node->key = key;
	//node의 key 값에 key값 대입
	node->rlink = node->llink = NULL;
	//llink와 rlink를 순서대로 NULL로 초기화

	if(h->first == NULL)//머리노드가 가르키는 값이 NULL일 때
	{
		h->first = node;
		//머리노드가 가르키는 값에 node값 대입
		return 1;//종료
	}

	node->rlink = h->first;
	//rlink에  머리노드가 가르키는 값 대입
	node->llink = NULL;
	//llink를 NULL로 초기화

	listNode *p = h->first;
	//listnode 포인터 변수 p 선언후 머리노드가 가르키는 값 대입
	p->llink = node;
	//llink에 node값 대입
	h->first = node;
	//머리노드가 가르키는 값에 node값 대입

	return 0;//종료
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {//list의 첫번째 노드 삭제 함수

	if (h->first == NULL)
	//머리노드가 가르키는 값이 NULL 일떄
	{
		printf("nothing to delete.\n");
		//삭제할 것이 없음을 출력
		return 0;//종료
	}
	listNode* n = h->first;
	//listnode 포인터 변수 n 선언후 머리노드가 가르키는 값 대입
	h->first = n->rlink;
	//머리노드가 가르키는 값에 rlink값 대입

	free(n);//n 할당해제

	return 0;//종료
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {//리스트 역순배치 함수


	if(h->first == NULL) {//머리노드가 가르키는 값이 NULL일 때
		printf("nothing to invert...\n");
		//역순배치할 것이 없음을 출력
		return 0;
		//종료
	}
	listNode *n = h->first;
	//listnode 포인터 변수 n 선언후 머리노드가 가르키는 값 대입
	listNode *trail = NULL;
	//listnode 포인터 변수 trail 선언후 NULL로 초기화
	listNode *middle = NULL;
	//listnode 포인터 변수 middle 선언후 NULL로 초기화

	while(n != NULL){//n이 NULL과 다르다면
		trail = middle;//middle값을 trail에 대입
		middle = n;//n값을 middle에 대입
		n = n->rlink;//rlink값을 n에 대입
		middle->rlink = trail;//trail값을 middle의 rlink값에 대입
		middle->llink = n;//n값을 middle의 llink값에 대입
	}

	h->first = middle;//middle값을 머리노드가 가르키는 값에 대입

	return 0;//종료
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {//노드 삽입 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));
	//listnode 포인터 변수 node 선언후 동적메모리 할당
	node->key = key;
	//key값을 node의 key값에 대입
	node->llink = node->rlink = NULL;
	//노드의 r,l link 값을 순서대로 NULL로 초기화

	if (h->first == NULL)//머리노드가 가르키는 값이 NULL일 때
	{
		h->first = node;//node값을 머리노드가 가르키는 값에 대입
		return 0;//종료
	}

	listNode* n = h->first;
	//listnode 포인터 변수 n을 선언후 머리노드가 가르키는 값에 대입

	while(n != NULL) {//n이 NULL이 아니라면
	/* key를 기준으로 삽입할 위치를 찾는다 */
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				insertFirst(h, key);
				//insertFirst함수 실행
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;//rlink에 n값 대입
				node->llink = n->llink;
				//n의 llink값을 node에 link값에 대입
				n->llink->rlink = node;
				//node값을 이중 링크드리스트에 대입
			}
			return 0;//종료
		}

		n = n->rlink;//n에 rlink값 대입
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);//insertlast함수 실행
	return 0;//종료
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {//노드삭제 함수

	if (h->first == NULL)//머리헤드가 가르키는 값이 NULL일 때
	{
		printf("nothing to delete.\n");
		//삭제할 것이 없음을 출력
		return 1;//종료
	}

	listNode* n = h->first;
	//리스트노드 포인트변수 n 선언 후 머리헤드가 가르키는 값 대입

	while(n != NULL) {//n이 null값과 다르다면
		if(n->key == key) {//key값 비교
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);//deleteFirst 함수 실행
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h);//deleteLast 함수 실행
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				//이중링크드리스트를 이용하여 값 대입
				free(n);//n 할당해제
			}
			return 1;//종료
		}

		n = n->rlink;//n에 rlink값 대입
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	//키에 대한 노드를 찾을 수 없음을 출력
	return 1;//종료
}


