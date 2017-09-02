#include "stdafx.h"
#include "homework.h"
int main()
{
	//第一题
	int i = 10;
	HowMuchOne(&i);

	//第二题
	char *str = TenTo36(1679615);
	free(str);

	//第三题
	HForLF();

	//第四题
	i = 0x12345678;
	UpsideDownMem(&i);

	//第五题
	char str2[] = "hello world";
	printf("%s%s", "Question5 原式=", str2);
	UpsideDownStr(str2, sizeof(str2)-1);
	printf("%s%s\n", "，转换后=", str2);

	//第六题
	char str3[] = "hello world";
	StrRotate(str3, sizeof(str3) - 1, 3);

	//第七题

	//初始化
	PXorLinkedList list = initXorLinkedList();
	
	//在尾部插入
	insertNode(list, 'w', QUESTION7_RIGHT);
	insertNode(list, 'o', QUESTION7_RIGHT);
	insertNode(list, 'r', QUESTION7_RIGHT);
	insertNode(list, 'l', QUESTION7_RIGHT);
	insertNode(list, 'd', QUESTION7_RIGHT);

	//在头部插入
	insertNode(list, 'o', QUESTION7_LEFT);
	insertNode(list, 'l', QUESTION7_LEFT);
	insertNode(list, 'l', QUESTION7_LEFT);
	insertNode(list, 'e', QUESTION7_LEFT);
	insertNode(list, 'h', QUESTION7_LEFT);

	//从头部遍历
	showMyList(list, QUESTION7_LEFT, QUESTION7_SHOW_TRUE);

	//删除几个节点
	deleteNode(list, QUESTION7_LEFT);
	deleteNode(list, QUESTION7_LEFT);
	deleteNode(list, QUESTION7_LEFT);

	//从尾部遍历
	showMyList(list, QUESTION7_RIGHT, QUESTION7_SHOW_TRUE);

	//释放链表，内置删除
	freeXorLinkedList(list);

    return 0;
}

/***
 作业题1：计算一个整数的二进制中有多少个1。如10的二进制为1010,所以有2个1。

 解题思路：设该整数的二进制格式为x，则运算x-1可将x从右往左数的第一个的“1”消去，若x&=x-1，则在确保x其他位的“1”不受影响的前提下，
			消去了从右往左数的第一个1。
			（这里实际上利用了二进制的退位原理，因为若足够减1则消去了最低位的1，不足减1时，会向最近的高位借1，则最近的高位被消去1,
			在和原数做与运算时，则会将原数中对应位数的1按照逐位运算的法则变为0）
		   则不断执行x&=x-1，直到x所有的“1”均被消去（x<1）时，统计执行的次数，可得出x内“1”的个数。

		   拓展：其实利用该原理，我们可以做到数出一个10进制数的二进制格式中有多少个11，111，1111……很有趣的数学呢:)

		   试编码实现如下：
*/
void HowMuchOne(int *pNum) {
	printf("%s%d", "Question1 参数 : ",*pNum);
	int total = 0;//该值存储了入参的二进制格式内“1”的个数
	while (*pNum >= 1) {
		*pNum &= *pNum - 1;
		total++;
	}
	printf(",该参数具有 %d 个\"1\"\n",total);
}

/***
 作业题2：请设计一个函数，把十进制的正整数转化为4位定长的三十六进制字符串。
			三十六进制的规则为“0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"。比如： 
			1=“0001”，10=“000A”，20=“000K”，35=“000Z”，36=“0010”

 解题思路：设待转码的10进制数为x，则不断做x%36与x/=36，直到x/36的结果为0。
           一共进行n次运算。最后将x%36得到的n个数倒序排列，即为要求的36进制数。

		   此题中要求我们按照题目给定的“36进制数编码格式”返回字符串，因此先为编码格式编制一张哈希表，
		   每一次x%36获得的结果即为该表的下标，即可得到对应的字符。

		   在本题中，仅需要处理4位长度的正36进制整数，即数据最大可支持1679615，未超出int型表示范围，也无需考虑符号，可算作是出题者手下留情。
*/
char* TenTo36(unsigned int num) {
	//超过范围的数不处理
	if (num > QUESTION2_MAX) {
		printf("%s%d\n", "参数过大！QUESTION2_MAX=",QUESTION2_MAX);
		return NULL;
	}

	printf("%s%d\n", "Question2 参数 : ", num);

	//36进制数编码表
	static char hash[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
						   'G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V',
						   'W','X','Y','Z' };

	//返回结果
	char *result = (char*)malloc((QUESTION2_STR_SIZE_MAX + 1) * sizeof(char));
	if (result == NULL) {
		printf("%s\n", "函数 TenTo36(unsigned int *pNum) 为 [*result] 分配内存失败！");
		return NULL;
	}
	int i;
	//对内存进行初始化，不允许使用memset
	for (i = 0; i < QUESTION2_STR_SIZE_MAX; i++) {
		*(result + i) = '0';
	}
	//字符串末尾需以'\0'标识
	*(result + i--) = '\0';
	while (num != 0) {
		//转换结果倒序存入堆内存中
		*(result + i--) = hash[num % QUESTION2_RIDIX];
		num /= QUESTION2_RIDIX;
	}

	printf("原数的36进制形式为: %s\n",result);

	return result;

}

/***
作业题3：判断一个平台是低位优先还是高位优先
解题思路：对于一个四字节十六进制数0x00000001来说，01为该数最低位。
		高位优先存储时应为 00 00 00 01 即高地址存放低位数据，低地址存放高位数据，符合我们从左到右的书写习惯
		低位优先存储时应为 01 00 00 00 即高地址存放高位数据，低地址存放低位数据，符合古人从右到左的书写习惯

		所以windows一定是古中国人设计的，嗯……
*/
void HForLF() {
	static short flag = 1;
	char *pFlag = (char*)&flag;
	printf("%s:%s\n", "Question3 该平台的存储方式是", (*pFlag == 0 ? "高位优先":"低位优先"));
}

/***
作业题4：改变一个整数的存储方式(0x12345678->0x78563412)
解题思路：事实上，我们完全不关心该整数的存储方式，即该数究竟是高位优先存储还是低位优先存储，
		  只需将该整数逐字节逆序即可改变其存储方式，至于它以前到底是啥，谁在乎呢~
		  逆序时利用满足交换率的一种可逆运算，如加法，即可在无第三方参与的情况下交换两数之值。
*/
void UpsideDownMem(int *pNum) {
	printf("%s%p", "Question4 原数0x", *pNum);
	char *pNumByte = (char *)pNum;
	for (int i = 0; i < sizeof(*pNum)/2; i++) {
		*(pNumByte + i) ^= *(pNumByte + sizeof(*pNum) - i - 1);
		*(pNumByte + sizeof(*pNum) - i - 1) ^= *(pNumByte + i);
		*(pNumByte + i) ^= *(pNumByte + sizeof(*pNum) - i - 1);
	}
	printf("%s%p\n", "，转换后0x", *pNum);
}

/***
作业题5：将一个字符串按照单词逆置，如"hello world"->"world hello"
解题思路：该题思路与上一题一样，通过一种满足交换律的可逆运算，即可对原式进行逆序。
*/
void UpsideDownStr(char *arr,int arrSize) {
	for (int i = 0; i < arrSize / 2; i++) {
		*(arr + i) ^= *(arr + arrSize - i - 1);
		*(arr + arrSize - i - 1) ^= *(arr + i);
		*(arr + i) ^= *(arr + arrSize - i - 1);
	}
}

/***
作业题6：将一个字符串，左旋N个字符。如左旋3个字符："hello world"->"lo worldhel"
解题思路：所谓左旋N个字符，其实可以分解为如下三个子问题：
		  第一步，把冰箱门打开……
		  额……串词了，不好意思，重新来过！
		  第一步，将字符串的0~N-1位逆序
		  第二步，将字符串的N~Len-1位逆序
		  第三步，将整个字符串逆序

		  本题中可以使用上一题的字符串逆序函数，达到偷懒……不是，是达到代码复用的目的。
*/
void StrRotate(char *str, int strSize, int rotateSize) {
	printf("%s%s", "Question6 原式=", str);

	UpsideDownStr(str, rotateSize);

	UpsideDownStr(str + rotateSize, strSize - rotateSize);

	UpsideDownStr(str, strSize);

	printf("%s%s\n", "，转换后=", str);
}

/***
作业题7：通过异或实现一个只带一个指针域的双向链表
解题思路：双向链表即具备一个前驱和一个后继的链表，只允许使用一个指针的情况下，则只能利用异或链表的特性来实现。
		  这块要解释起来怕是注释区就不够写了，那就不解释了，反正是最后一题了，咱们直接起飞吧。
		  目标：
		  1、链表的初始化、动态扩容
		  2、链表的遍历
		  3、链表的插入
		  4、链表的删除
*/

/***
	计算两个节点的异或
*/
PLinkedNode XorPLinkedNode(PLinkedNode node1, PLinkedNode node2) {
	return (unsigned long)node1 ^ (unsigned long)node2;
}

/***
	异或链表初始化，返回该链表的地址
*/
PXorLinkedList initXorLinkedList() {
	printf("%s\n%s\n","Question7:", "链表初始化进行中……");
	
	PXorLinkedList pNewLinkedList = (PXorLinkedList)malloc(sizeof(XorLinkedList));

	PLinkedNode head = (PLinkedNode)malloc(sizeof(LinkedNode));
	pNewLinkedList->head = head;
	PLinkedNode tail = (PLinkedNode)malloc(sizeof(LinkedNode)); 
	pNewLinkedList->tail = tail;

	head->data = '\0';
	head->next = XorPLinkedNode(NULL, tail);

	tail->data = '\0';
	tail->next = XorPLinkedNode(head, NULL);

	printf("链表初始化成功，头部地址:%p,尾部地址:%p\n", head,tail);

	return pNewLinkedList;
}

/***
	遍历链表
*/
int showMyList(PXorLinkedList list,int D,int show){
	int i = 0;

	if (show == QUESTION7_SHOW_TRUE) {
		printf("链表遍历(%s)开始，表内数据如下：\n",(D==QUESTION7_LEFT?"从头部":"从尾部"));
	}

	PLinkedNode node = (D == QUESTION7_LEFT ? list->head : list->tail);

	PLinkedNode preNode = NULL;

	PLinkedNode nextNode = XorPLinkedNode(preNode, node->next);

	while (node!=NULL){
		if (show == QUESTION7_SHOW_TRUE) {
			printf("%c",node->data);
		}

		preNode = node;

		node = nextNode;

		if (node == NULL) {
			break;
		}

		nextNode = XorPLinkedNode(preNode, node->next);

	}

	if (show == QUESTION7_SHOW_TRUE) {
		printf("%s", "\n链表遍历结束\n");
	}

	return i;
}

/***
	插入新节点，其实不分左右，逻辑相同，区别只在于你愿意从哪里开始
*/
void insertNode(PXorLinkedList list,char data, int D) {
	PLinkedNode node = (D == QUESTION7_LEFT ? list->head : list->tail);

	PLinkedNode nextNode = XorPLinkedNode(NULL, node->next);

	PLinkedNode insertNode = (PLinkedNode)malloc(sizeof(LinkedNode));

	insertNode->data = data;
	insertNode->next = XorPLinkedNode(NULL, node);
	
	node->next = XorPLinkedNode(insertNode, nextNode);

	if (D == QUESTION7_LEFT) {
		list->head = insertNode;
	}
	else {
		list->tail = insertNode;
	}
	printf("插入节点(%s)成功！插入数据=%c\n", (D == QUESTION7_LEFT ? "从头部" : "从尾部"), insertNode->data);
}

/***
	删除一个节点，其实不分左右……是的，齐头并进，不分高低:)
*/
void deleteNode(PXorLinkedList list,int D) {
	PLinkedNode node = (D == QUESTION7_LEFT ? list->head : list->tail);

	PLinkedNode preNode = NULL;

	PLinkedNode nextNode = XorPLinkedNode(preNode, node->next);
	
	PLinkedNode nextNodeNext = XorPLinkedNode(preNode, XorPLinkedNode(node, nextNode->next));

	//链表最少要维护两个节点，否则不存在
	if (nextNodeNext == NULL) {
		return;
	}

	nextNode->next = XorPLinkedNode(preNode, nextNodeNext);

	if (D == QUESTION7_LEFT) {
		list->head = nextNode;
	}
	else {
		list->tail = nextNode;
	}
	char nodeDate = node->data;
	free(node);
	node = NULL;

	printf("删除节点(%s)成功！删除数据=%c\n", (D == QUESTION7_LEFT ? "从头部" : "从尾部"),nodeDate);
}


int _freeXorLinkedList(PXorLinkedList list) {
	
	if (showMyList(list, QUESTION7_LEFT, QUESTION7_SHOW_FALSE) > 2) {
		return QUESTION7_FREE_FAILED;
	}

	free(list->head);
	list->head = NULL;
	free(list->tail);
	list->tail = NULL;
	free(list);
	list = NULL;

	return QUESTION7_FREE_SUCCESS;
}

/***
	释放链表占用的堆内存
*/
void freeXorLinkedList(PXorLinkedList list) {
	while (_freeXorLinkedList(list) != QUESTION7_FREE_SUCCESS) {
		deleteNode(list, QUESTION7_LEFT);
	}
	printf("%s", "链表内存已释放\n");
}