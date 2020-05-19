// Name : Neven Hossam Mohamed
// Track : SD (SW Architect)

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

typedef struct QueueNode Node;
typedef struct linkedList linkedList;
typedef struct ListNode listNode;

COORD coord = {0,0};
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}

//---------------------------------------------------------
//Queue implementation

struct QueueNode
{
    int enteringTime, transactionTime, waitingTime, endTime;
    char clientName[21];
    Node *next;
};

typedef struct Queue
{
    Node *front;
    Node *rear;
    int size;
} Queue;

void createQueue(Queue *q)
{
    q->front = q->rear = NULL;
    q->size = 0;
}

Node *createNode(Node client)
{
    Node *pNewNode = (Node *)malloc(sizeof(Node));
    strcpy(pNewNode->clientName, client.clientName);
    pNewNode->enteringTime = client.enteringTime;
    pNewNode->transactionTime = client.transactionTime;
    pNewNode->next = NULL;
//    pNewNode->previous = NULL;
    return pNewNode;
}

int isEmpty(Queue *q)
{
    return !q->front;
}

int queueSize(Queue *q)
{
    return q->size;
}

void enQueue(Node *pNewNode, Queue *q)
{
    if(!q->rear) // q->rear == NULL
        q->front = pNewNode;
    else
        q->rear->next = pNewNode;
    q->rear = pNewNode;
    q->size++;
}

Node *deQueue(Queue *q)
{
    Node *poppedNode = q->front;
    q->front = q->front->next;
    poppedNode->next = NULL;
    //free(poppedNode);
    if(!q->front)
        q->rear = NULL;
    q->size--;
    return poppedNode;
}

void DisplayAll(Queue *q)
{
    Node *pCurrentNode = q->front;
    int counter = queueSize(q);
    while(pCurrentNode!=NULL && counter > 0) //pCurrentNode!=NULL
    {
        printf("Client Name : ");
        puts(pCurrentNode->clientName);
        printf("Entering Time : %d\n",pCurrentNode->enteringTime);
        printf("Transaction Time : %d\n",pCurrentNode->transactionTime);
        if(counter != 1)
            printf("\n-------------------------\n");
        pCurrentNode = pCurrentNode->next;
        counter--;
    }
}

//---------------------------------------------------------
//list implementation

struct ListNode
{
    int enteringTime, transactionTime, waitingTime, endTime;
    char clientName[21];
    listNode *next, *previous;
};

struct linkedList
{
    listNode *first;
    listNode *last;
};

listNode *create(listNode client)
{
    listNode *pNode = (listNode *) malloc(sizeof(listNode));

    strcpy(pNode->clientName, client.clientName);
    pNode->enteringTime = client.enteringTime;
    pNode->transactionTime = client.transactionTime;
    pNode->waitingTime = client.waitingTime;
    pNode->endTime = client.endTime;

    pNode->previous = pNode->next = NULL;
    return pNode;
}

void addNode(listNode *pNewNode, linkedList *pLinkedList)
{
    if(pLinkedList->first == NULL)
        pLinkedList->first = pLinkedList->last = pNewNode;
    else
    {
        pNewNode->next = NULL;
        pNewNode->previous = pLinkedList->last;
        pLinkedList->last->next = pNewNode;
        pLinkedList->last = pNewNode;
    }
}

void displayAllListNodes(linkedList *pLinkedList)
{
    Node *pCurrentNode = pLinkedList->first;
    while(pCurrentNode)
    {
        printf("Client Name : ");
        puts(pCurrentNode->clientName);
        printf("Entering Time : %d\n",pCurrentNode->enteringTime);
        printf("Transaction Time : %d\n",pCurrentNode->transactionTime);
        if(pCurrentNode->next)
            printf("\n-------------------------\n");
        pCurrentNode = pCurrentNode->next;
    }
}

void createClient(listNode *client)
{
    int exit = 1;
    system("cls");

    gotoxy(50,5);
    printf("<<< Entering Data >>> ");
    gotoxy(40,7);
    printf("Client Name :");
    gotoxy(40,9);
    printf("Entering Time :");
    gotoxy(40,11);
    printf("Transaction Time :");

    _flushall();
    gotoxy(60,7);
    gets(client->clientName);

    _flushall();
    gotoxy(60,9);
    scanf("%d",&client->enteringTime);

    _flushall();
    gotoxy(60,11);
    scanf("%d",&client->transactionTime);
}

listNode *deleteNode(listNode *pNode, linkedList *pLinkedList)
{
    if(pLinkedList->first == pNode)
    {
        if(pLinkedList->last == pNode) // first node and only one
            pLinkedList->first = pLinkedList->last = NULL;
        else // first node but there are more nodes
        {
            pLinkedList->first = pNode->next;
            pNode->next->previous = NULL;
        }
    }
    else if(pLinkedList->last == pNode) // last node
    {
        pLinkedList->last = pNode->previous;
        pLinkedList->last->next = NULL;
        //pNode->previous->next = NULL;
    }
    else
    {
        pNode->next->previous = pNode->previous;
        pNode->previous->next = pNode->next;
        pNode->next = pNode->previous = NULL;
    }
    return pNode;
}

void insertBefore(listNode *nodeBefore, listNode *pNewNode, linkedList *pLinkedList)
{
    if(nodeBefore == pLinkedList->first)
    {
        pNewNode->next = nodeBefore;
        pNewNode->previous = NULL;
        nodeBefore->previous = pNewNode;
        pLinkedList->first = pNewNode;
    }
    else
    {
        pNewNode->next = nodeBefore;
        pNewNode->previous = nodeBefore->previous;
        nodeBefore->previous->next = pNewNode;
        nodeBefore->previous = pNewNode;
    }
}

//---------------------------------------------------------
//Sorting the list

void bubbleSort(linkedList *pLinkedList)
{
    Node *pCurrentNodeInBiggerLoop = pLinkedList->first;
    Node *pCurrentNodeInSmallerLoop = pLinkedList->first;
    int isSorted = 0;
    while(!isSorted)
    {
        isSorted = 1;
        while(pCurrentNodeInSmallerLoop->next != NULL)
        {
            if(pCurrentNodeInSmallerLoop->enteringTime > pCurrentNodeInSmallerLoop->next->enteringTime)
            {
                listNode *deletedNode;
                deletedNode = deleteNode(pCurrentNodeInSmallerLoop->next, pLinkedList);
                deletedNode->next = deletedNode->previous = NULL;
                insertBefore(pCurrentNodeInSmallerLoop, deletedNode, pLinkedList);
                isSorted = 0;
            }
            else
                pCurrentNodeInSmallerLoop = pCurrentNodeInSmallerLoop->next;

        }
        pCurrentNodeInSmallerLoop = pLinkedList->first;
    }
}

//---------------------------------------------------------
//bank functionality

Node *mappingNodeFromListToQueue(Node *oldNode)
{
    Node *mappedNode = (Node *) malloc(sizeof (Node));
    mappedNode->enteringTime = oldNode->enteringTime;
    strcpy(mappedNode->clientName, oldNode->clientName);
    mappedNode->transactionTime = oldNode->transactionTime;
    mappedNode->endTime = oldNode->endTime;
    mappedNode->waitingTime = oldNode->waitingTime;
    mappedNode->next = oldNode->next;

    return mappedNode;
}

//return the available queue
Queue *returnedQueue(Queue *teller1, Queue *teller2, Queue *teller3)
{
    if(queueSize(teller1) == 0 || queueSize(teller2) == 0 || queueSize(teller3) == 0)
    {
        if(queueSize(teller1) == 0)
            return teller1;
        else if(queueSize(teller2) == 0)
            return teller2;
        else if(queueSize(teller3) == 0)
            return teller3;
    }
    else if(queueSize(teller1) != 0 && queueSize(teller2) != 0 && queueSize(teller3) != 0)
    {
        //check on the least end time of the 3 queues
        if(teller1->rear->endTime < teller2->rear->endTime)
        {
            if(teller1->rear->endTime < teller3->rear->endTime) //teller 1 is the smallest
            {
                return teller1;
            }
            else if(teller3->rear->endTime < teller1->rear->endTime) //teller 3 is the smallest
            {
                return teller3;
            }
        }
        else if(teller2->rear->endTime < teller1->rear->endTime)
        {
            if(teller2->rear->endTime < teller3->rear->endTime) //teller 2 is the smallest
            {
                return teller2;
            }
            else if(teller3->rear->endTime < teller2->rear->endTime) //teller 3 is the smallest
            {
                return teller3;
            }
        }
        else //if(teller3->rear->endTime < teller1->rear->endTime)
        {
            if(teller3->rear->endTime < teller2->rear->endTime) //teller 3 is the smallest
            {
                return teller3;
            }
            else if(teller2->rear->endTime < teller3->rear->endTime) //teller 2 is the smallest
            {
                return teller2;
            }
        }
    }
    else
        return NULL;
}

void assignClients(Queue *teller1, Queue *teller2, Queue *teller3, linkedList *pLinkedList)
{
    Node *myClient =  pLinkedList->first;
    while(myClient)
    {
        Queue *queueReturned = returnedQueue(teller1, teller2, teller3);
        if(queueReturned != NULL)
        {
            if(queueSize(queueReturned) == 0)
            {
                //calculate waiting time
                myClient->waitingTime = 0;
                //calculate end time
                myClient->endTime = myClient->enteringTime + myClient->transactionTime;
            }
            else
            {
                //check if the last node of the teller still there
                if(teller1->rear->endTime > myClient->enteringTime)
                {
                    myClient->waitingTime = queueReturned->rear->endTime - myClient->enteringTime;
                    myClient->endTime = queueReturned->rear->endTime + myClient->waitingTime + myClient->transactionTime;
                }
                //if the last node has been finished her work
                else if(teller1->rear->endTime < myClient->enteringTime)
                {
                    myClient->waitingTime = 0;
                    myClient->endTime = myClient->waitingTime + myClient->transactionTime;
                }
            }
            Node *mappedNode = mappingNodeFromListToQueue(myClient);
            enQueue(mappedNode, queueReturned);
        }
        myClient = myClient->next;
    }
}

//---------------------------------------------------------
//calculations and the report

int totalTransactionTimeForTeller(Queue *q)
{
    Node *pCurrent = q->front;
    int counter = queueSize(q);
    int total = 0;
    while(counter > 0)
    {
        total += pCurrent->transactionTime;
        pCurrent = pCurrent->next;
        counter--;
    }
    return total;
}

float avgTransactionTimeForTeller(Queue *q)
{
    float avg = totalTransactionTimeForTeller(q)/queueSize(q);
    if(queueSize(q) != 0)
        return avg;
    else
        return -1;
}

int totalWaitingTimeForTeller(Queue *q)
{
    Node *pCurrent = q->front;
    int counter = queueSize(q);
    int total = 0;
    while(counter > 0)
    {
        total += pCurrent->waitingTime;
        pCurrent = pCurrent->next;
        counter--;
    }
    return total;
}

float avgWaitingTimeForTeller(Queue *q)
{
    float avg = totalWaitingTimeForTeller(q)/queueSize(q);
    if(queueSize(q) != 0)
        return avg;
    else
        return -1;
}

int totalTransactionTimeForBank(Queue *q1, Queue *q2, Queue *q3)
{
    int totalForBank = totalTransactionTimeForTeller(q1) + totalTransactionTimeForTeller(q2) + totalTransactionTimeForTeller(q3);
    return totalForBank;
}

float avgTransactionTimeForBank(Queue *q1, Queue *q2, Queue *q3)
{
    int sizeTeller1 = queueSize(q1);
    int sizeTeller2 = queueSize(q2);
    int sizeTeller3 = queueSize(q3);
    if((sizeTeller1 + sizeTeller2 + sizeTeller3) != 0)
    {
        float avgForBank = totalTransactionTimeForBank(q1,q2,q3) / (sizeTeller1 + sizeTeller2 + sizeTeller3);
        return avgForBank;
    }
    else
        return -1;
}

int totalWaitingTimeForBank(Queue *q1, Queue *q2, Queue *q3)
{
    int totalForBank = totalWaitingTimeForTeller(q1) + totalWaitingTimeForTeller(q2) + totalWaitingTimeForTeller(q3);
    return totalForBank;
}

float avgWaitingTimeForBank(Queue *q1, Queue *q2, Queue *q3)
{
    int sizeTeller1 = queueSize(q1);
    int sizeTeller2 = queueSize(q2);
    int sizeTeller3 = queueSize(q3);
    if((sizeTeller1 + sizeTeller2 + sizeTeller3) != 0)
    {
        float avgForBank = totalWaitingTimeForBank(q1,q2,q3) / (sizeTeller1 + sizeTeller2 + sizeTeller3);
        return avgForBank;
    }
    else
        return -1;
}

void printReport(Queue *q1, Queue *q2, Queue *q3)
{
    system("cls");
    printf("-------------------------------------\n");
    printf("| << For The Bank >>                 |\n");
    printf("|                                    |\n");
    printf("| Total Transaction Time :  %d       |\n", totalTransactionTimeForBank(q1, q2, q3));
    if(avgTransactionTimeForBank(q1, q2, q3) != -1)
        printf("| Avg Transaction Time :    %.2f     |\n", avgTransactionTimeForBank(q1, q2, q3));
    else
        printf("| Avg Transaction Time : 0            |\n");
    printf("|                                    |\n");
    printf("| Total Waiting Time :  %d           |\n", totalWaitingTimeForBank(q1, q2, q3));
    if(avgWaitingTimeForBank(q1, q2, q3) != -1)
    printf("| Avg Waiting Time :    %.2f         |\n", avgWaitingTimeForBank(q1, q2, q3));
    else
        printf("| Avg Waiting Time :       0        |\n");
    printf("|------------------------------------|\n");
    printf("|------------------------------------|\n");
    printf("| << For First Teller >>             |\n");
    printf("|                                    |\n");
    printf("| Total Transaction Time :   %d      |\n", totalTransactionTimeForTeller(q1));
    if(avgTransactionTimeForTeller(q1) != -1)
        printf("| Avg Transaction Time :     %.2f    |\n", avgTransactionTimeForTeller(q1));
    else
        printf("| Avg Transaction Time :     0        |\n");
    printf("|                                    |\n");
    printf("| Total Waiting Time :       %d      |\n", totalWaitingTimeForTeller(q1));
    if(avgWaitingTimeForTeller(q1) != -1)
        printf("| Avg Waiting Time :         %.2f    |\n", avgWaitingTimeForTeller(q1));
    else
        printf("| Avg Waiting Time :         0        |\n");
    printf("|------------------------------------|\n");
    printf("| << For second Teller >>            |\n");
    printf("|                                    |\n");
    printf("| Total Transaction Time :   %d      |\n", totalTransactionTimeForTeller(q2));
    if(avgTransactionTimeForTeller(q2) != -1)
        printf("| Avg Transaction Time :    %.2f     |\n", avgTransactionTimeForTeller(q2));
    else
        printf("| Avg Transaction Time :    0         |\n");
    printf("|                                    |\n");
    printf("| Total Waiting Time :      %d       |\n", totalWaitingTimeForTeller(q2));
    if(avgWaitingTimeForTeller(q2) != -1)
        printf("| Avg Waiting Time :        %.2f     |\n", avgWaitingTimeForTeller(q2));
    else
        printf("| Avg Waiting Time :         0        |\n");
    printf("|------------------------------------|\n");
    printf("| << For Third Teller >>             |\n");
    printf("|                                    |\n");
    printf("| Total Transaction Time :  %d       |\n", totalTransactionTimeForTeller(q3));
    if(avgTransactionTimeForTeller(q3) != -1)
    printf("| Avg Transaction Time :    %.2f     |\n", avgTransactionTimeForTeller(q3));
    else
        printf("| Avg Transaction Time :    0         |\n");
    printf("|                                    |\n");
    printf("| Total Waiting Time :      %d        |\n", totalWaitingTimeForTeller(q3));
    if(avgWaitingTimeForTeller(q3) != -1)
        printf("| Avg Waiting Time :        %.2f     |\n", avgWaitingTimeForTeller(q3));
    else
        printf("| Avg Waiting Time :         0        |\n");
    printf("-------------------------------------\n");
}

//---------------------------------------------------------
//main menu

void menu()
{
    char menuArr[4][30];
    strcpy(menuArr[0], "Display Tellers");
    strcpy(menuArr[1], "Display Bank");
    strcpy(menuArr[2], "Display Report");
    strcpy(menuArr[3], "Exit");

    int cursorPosition = 0;
    char input;
    int sizeOfMenu = sizeof(menuArr) / sizeof(menuArr[0]);

    Queue firstTeller;
    Queue secondTeller;
    Queue thirdTeller;

    createQueue(&firstTeller);
    createQueue(&secondTeller);
    createQueue(&thirdTeller);

    Node *newClient;
    int exit = 1;
    char ch;

    linkedList linkedListObj;
    linkedListObj.first = linkedListObj.last = NULL;

    do
    {
        listNode clientObj;
        newClient = create(clientObj);
        createClient(newClient);
        addNode(newClient, &linkedListObj);

        gotoxy(45,14);
        printf("Press 0 to go back to the menu..\n");
        ch = getch();
    }
    while(ch != '0');

    bubbleSort(&linkedListObj);
    assignClients(&firstTeller, &secondTeller, &thirdTeller, &linkedListObj);

    do
    {
        system("cls");
        _flushall();
        for(int i =0; i<sizeOfMenu; i++)
        {
            if(i == cursorPosition)
            {
                textattr(0x70);
                gotoxy(55,12+i);
                printf("%s",menuArr[i]);
                textattr(0x07);
            }
            else
            {
                gotoxy(55,12+i);
                printf("%s",menuArr[i]);
            }
        }

        input = getch();

        switch(input)
        {
        case 72: // up arrow
            cursorPosition--;
            if(cursorPosition == -1)
                cursorPosition = sizeOfMenu-1;
            break;
        case 80: // down arrow
            cursorPosition++;
            if(cursorPosition == sizeOfMenu)
                cursorPosition = 0;
            break;
        case 73:
        case 71: // page up button
            cursorPosition = 0;
            break;
        case 81:
        case 79: // page down button
            cursorPosition = sizeOfMenu-1;
            break;
        case 13:
            if(cursorPosition == 0) // display all
            {
                system("cls");
                if(!isEmpty(&firstTeller))
                {
                    printf("<< First Teller >>\n\n");
                    DisplayAll(&firstTeller);
                    printf("\n\n********************************\n\n");
                }
                else
                    printf("\nTeller 1 is Empty .. \n");
                if(!isEmpty(&secondTeller))
                {
                    printf("<< Second Teller >> \n\n");
                    DisplayAll(&secondTeller);
                    printf("\n\n********************************\n\n");
                }
                else
                    printf("\nTeller 2 is Empty .. \n");
                if(!isEmpty(&thirdTeller))
                {
                    printf("<< Third Teller >> \n\n");
                    DisplayAll(&thirdTeller);
                    printf("\n\n*********************************\n\n");
                }
                else
                    printf("\nTeller 3 is Empty .. \n");
                printf("\nPress any key to go back ..\n");
                ch = getch();
            }
            if(cursorPosition == 1) // display all list
            {
                system("cls");
                printf("<<< Bank Clients >>>\n\n");
                displayAllListNodes(&linkedListObj);
                printf("\nPress any key to go back ..\n");
                ch = getch();
            }
            if(cursorPosition == 2) // report
            {
                printf("<<<<          Report         >>>>\n\n");
                printReport(&firstTeller, &secondTeller, &thirdTeller);
                printf("\n\nPress any key to go back ..\n");
                ch = getch();
            }
            if(cursorPosition == 3) // exit
                exit = 0;
            break;
        }
    }
    while(exit != 0);
    system("cls");
    printf("\n\n<<< Thank You For Using Our App >>>\n\n");
}

int main()
{
    menu();
    return 0;
}
