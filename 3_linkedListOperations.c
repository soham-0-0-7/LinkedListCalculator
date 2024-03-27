#include<stdio.h>
#include <limits.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct node {
    int value;
    struct node* next;
};

struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->value = data;
    newNode->next = NULL;
    return newNode;
}

struct node* insertAtHead(struct node* head, int data){
    struct node* newNode = createNode(data);
    newNode->value = data;
    newNode->next = head;
    return newNode; 
}

struct node* insertAtTail(struct node* head, int data) {
    struct node* newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }
    struct node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

struct node* numberToLinkedList (struct node* head,long num){
    long tempNum = num;
    int digit;
    while(tempNum > 0){
        digit = (tempNum)-((tempNum/10)*10);
        head = insertAtHead(head,digit);
        tempNum /= 10;
    }
    return head;
}

struct node* subtractLinkedList (struct node* head1,struct node* head2, bool toPrint){
    struct node* itr1stopper = (struct node*)malloc(sizeof(struct node));
    struct node* itr2stopper = (struct node*)malloc(sizeof(struct node));
    struct node* itr1 = (struct node*)malloc(sizeof(struct node));
    struct node* itr2 = (struct node*)malloc(sizeof(struct node));
    itr1stopper = NULL;
    itr2stopper = NULL;
    bool isNegative = false;
    if(!toPrint){
        isNegative = true;
    }
    bool borrow = false;
    struct node* result = (struct node*)malloc(sizeof(struct node));
        result = NULL;
    
    while(itr1stopper != head1 || itr2stopper != head2){
        itr1 = head1;
        itr2 = head2;
        
        if(itr2stopper == head2){
            while(itr1->next != itr1stopper){
                itr1 = itr1->next;
            }

            int difference;
            if(!borrow){
                difference = itr1->value;
                borrow = false;
            }
            else{
                if(itr1->value == 0){
                    borrow = true;
                    difference = 9;
                } else {
                    borrow = false;
                    difference = (itr1->value)-1;
                }            
            }
            result = insertAtHead(result,difference);
            itr1stopper = itr1;
        }
        else if(itr1stopper == head1){
           bool toPrint2 = false;
           return subtractLinkedList(head2,head1,toPrint2);
        }
        else{
            while(itr1->next != itr1stopper){
                itr1 = itr1->next;
            }
            while(itr2->next != itr2stopper){
                itr2 = itr2->next;
            }
            int difference;
            if(borrow){
                if((itr1->value)-1 < itr2->value){
                    borrow = true;
                    difference = (10+((itr1->value)-1)) - itr2->value;
                } else {
                    borrow = false;
                    difference = (itr1->value)- 1 - itr2->value;
                }
            } else{
                if(itr1->value < itr2->value){
                    borrow = true;
                    difference = (10+((itr1->value))) - itr2->value;
                } else {
                    borrow = false;
                    difference = (itr1->value) - itr2->value;
                }

            }    
            result = insertAtHead(result,difference);
            itr1stopper = itr1;
            itr2stopper = itr2;
        }
    }

    if(borrow ){
        bool toPrint2 = false;
        return subtractLinkedList(head2,head1,toPrint2);
    }

    if(toPrint){
        printf("\n");
        printf("  ");
        struct node* current1 = head1;
        while (current1 != NULL) {
            printf("%d", current1->value);
            current1 = current1->next;
        }
        printf("\n");
        printf("- ");
        struct node* current2 = head2;
        while (current2 != NULL) {
            printf("%d", current2->value);
            current2 = current2->next;
        }
        printf("\n");
        printf("-------------------");
        printf("\n");
        printf("  ");
        struct node* current3 = result;
        if(isNegative){
            printf("-");
        }
        while (current3 != NULL) {
            printf("%d", current3->value);
            current3 = current3->next;
        }
        printf("\n\n");
    } else {
        printf("\n  ");
        struct node* current2 = head2;
        while (current2 != NULL) {
            printf("%d", current2->value);
            current2 = current2->next;
        }
        printf("\n");
        printf("- ");
        struct node* current1 = head1;
        while (current1 != NULL) {
            printf("%d", current1->value);
            current1 = current1->next;
        }
        printf("\n");
        printf("-------------------");
        printf("\n ");
        struct node* current3 = result;
        if(isNegative){
            printf("-");
        } else {
            printf(" ");
        }
        while (current3 != NULL) {
            printf("%d", current3->value);
            current3 = current3->next;
        }
        printf("\n\n");
    }

    return result;  
}

 
struct node* addLinkedList (struct node* head1,struct node* head2, bool toPrint){
    struct node* itr1stopper = (struct node*)malloc(sizeof(struct node));
    struct node* itr2stopper = (struct node*)malloc(sizeof(struct node));
    struct node* itr1 = (struct node*)malloc(sizeof(struct node));
    struct node* itr2 = (struct node*)malloc(sizeof(struct node));
    itr1stopper = NULL;
    itr2stopper = NULL;
    int carry = 0;
    struct node* result = (struct node*)malloc(sizeof(struct node));
    result = NULL;
    
    while(itr1stopper != head1 || itr2stopper != head2){
        itr1 = head1;
        itr2 = head2;
        
        if(itr2stopper == head2){
            while(itr1->next != itr1stopper){
                itr1 = itr1->next;
            }
            int sum = ((itr1->value) + carry)%10;
            if((itr1->value) + carry>=10){
                carry =  ((itr1->value) + carry)/10;;
            } else { carry = 0;}
            result = insertAtHead(result,sum);
            itr1stopper = itr1;
        } else if(itr1stopper == head1){
            while(itr2->next != itr2stopper){
                itr2 = itr2->next;
            }
            int sum = ((itr2->value) + carry)%10;
            if((itr2->value) + carry>=10){
                carry = ((itr2->value) + carry)/10;
            } else { carry = 0;}
            result = insertAtHead(result,sum);
            itr2stopper = itr2;
        } else{
            while(itr1->next != itr1stopper){
                itr1 = itr1->next;
            }
            while(itr2->next != itr2stopper){
                itr2 = itr2->next;
            }
            int sum = (((itr1->value) + (itr2->value)) + carry)%10;
            if((itr1->value) + (itr2->value) + carry>=10){
                carry = ((itr1->value) + (itr2->value) + carry)/10;
            } else { carry = 0;}            
            result = insertAtHead(result,sum);
            itr1stopper = itr1;
            itr2stopper = itr2;
        }
    }

    if(carry != 0){
       result = insertAtHead(result,carry);
    }

    if(toPrint){
        printf("\n");
        printf("  ");
        struct node* current1 = head1;
        while (current1 != NULL) {
            printf("%d", current1->value);
            current1 = current1->next;
        }
        printf("\n");
        printf("+ ");
        struct node* current2 = head2;
        while (current2 != NULL) {
            printf("%d", current2->value);
            current2 = current2->next;
        }
        printf("\n");
        printf("-------------------");
        printf("\n");
        printf("  ");
        struct node* current3 = result;
        while (current3 != NULL) {
            printf("%d", current3->value);
            current3 = current3->next;
        }
        printf("\n\n");
    }

    return result;  
}

struct node* multiplyLinkedList (struct node* head1,struct node* head2, bool toPrint){
    struct node* itr1stopper = (struct node*)malloc(sizeof(struct node));
    struct node* itr2stopper = (struct node*)malloc(sizeof(struct node));
    struct node* itr1 = (struct node*)malloc(sizeof(struct node));
    struct node* itr2 = (struct node*)malloc(sizeof(struct node));
    itr1stopper = NULL;
    itr2stopper = NULL;
    int carry = 0;
    struct node* result = (struct node*)malloc(sizeof(struct node));
    result = NULL;
    int zeroes = 0;
    bool first = true;
    struct node* tempResult = (struct node*)malloc(sizeof(struct node));
    tempResult = NULL;

    if(toPrint){
        printf("\n");
        printf("  ");
        struct node* current1 = head1;
        while (current1 != NULL) {
            printf("%d", current1->value);
            current1 = current1->next;
        }
        printf("\n");
        printf("x ");
        struct node* current2 = head2;
        while (current2 != NULL) {
            printf("%d", current2->value);
            current2 = current2->next;
        }
        printf("\n");
        printf("-------------------");
    }    
    while(itr2stopper != head2){
        tempResult = NULL;
        itr1stopper = NULL;
        itr1 = head1;
        itr2 = head2;

        while(itr2->next != itr2stopper){
            itr2 = itr2->next;
        }    

        while(itr1stopper != head1){
            itr1 = head1;
            while(itr1->next != itr1stopper){
                itr1 = itr1->next;
            }
            int product;
            product = (((itr1->value)*(itr2->value) + carry) % 10);
            carry = ((itr1->value)*(itr2->value)+carry) / 10;
            tempResult = insertAtHead(tempResult,product);

            itr1stopper = itr1;
        }

        if(carry!=0){
            tempResult = insertAtHead(tempResult,carry); 
        }
        
        for(int i = 0; i<zeroes; i++){
            tempResult = insertAtTail(tempResult,0);
        }

        if(toPrint){
            struct node* current3 = tempResult;
            if(first){
                printf("\n  ");
                first = false;
            } else {
                printf("\n+ ");
            }
            while (current3 != NULL) {
                printf("%d", current3->value);
                current3 = current3->next;
            }
        }

        result = addLinkedList(result,tempResult,false);
        itr2stopper = itr2;
        carry = 0;
        zeroes++;
    }

    if(toPrint){
        printf("\n");
        printf("-------------------");
        printf("\n  ");
        struct node* current3 = result; 
        while (current3 != NULL) {
            printf("%d", current3->value);
            current3 = current3->next;
        }
        printf("\n");
        printf("\n");
    }
    return result; 
}

void printList(struct node* head){
    struct node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}


int main(){
    // printf("Soham Gandhi, 22BCP291, D4G8\n");
    // long i ;
    // long j ;

    // printf("LIMITS for proper operations - 0 to %ld\n",LONG_MAX);
    // printf("Enter first number - ");
    // scanf("%ld", &i);

    // printf("Enter second number - ");
    // scanf("%ld", &j);

     char num1_str[100], num2_str[100];
    printf("Enter the first number: ");
    scanf("%s", num1_str);
    printf("Enter the second number: ");
    scanf("%s", num2_str);

    int len1 = strlen(num1_str);
    int len2 = strlen(num2_str);

    struct node* head1 = NULL;
    struct node* head2 = NULL;

    // Create linked lists for the numbers in reverse order
    for (int i = len1 - 1; i >= 0; i--) {
        int digit = num1_str[i] - '0';
        head1 = insertAtHead(head1,digit);
    }

    for (int i = len2 - 1; i >= 0; i--) {
        int digit2 = num2_str[i] - '0';
        head2 = insertAtHead(head2,digit2);
    }

    // printf("\nLinked List Representation - \n");
    // printf("Number 1 - \n");
    // struct node* head = NULL;
    // head = numberToLinkedList(head,i);
    // printList(head);

    // printf("Number 2 - \n");
    // struct node* head2 = NULL;
    // head2 = numberToLinkedList(head2,j);
    // printList(head2);

    printf("\nSum - \n");
    struct node* sum = NULL;
    sum = addLinkedList(head1,head2,true);
    printList(sum);

    printf("\nDifference - \n");
    struct node* difference = NULL;
    difference = subtractLinkedList(head1,head2,true);
    printList(difference);

    printf("\nProduct - \n");
    struct node* product = NULL;
    product = multiplyLinkedList(head1,head2,true);
    printList(product);

    return 0;
}