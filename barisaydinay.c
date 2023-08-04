// BARIS AYDINAY 2452977

// ASSUMED THAT ALL BUILT-IN STRING OPERATIONS' COMPLEXITY IS CONSTANT O(1). (Instructor approved that)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct myData {
    int mailID;
    char sender[50];
    char receipt[50];
    int day;
    char content[200];
    int noOfWords;
};

struct myData* readMails(char *,int);
void heapSort(struct myData *,int,int);
void swap(struct myData *,struct myData *);
void heapify(struct myData *,int,int,int);
void buildHeap(struct myData *,int,int);
void printEmails(struct myData *,int);
void binSearch(struct myData *,int,int);
void menu();


int main()
{
    int number=0,option=-1;
    int searchKey;
    char filePath[50];
    printf("Enter data path: ");
    scanf("%s",filePath);
    fflush(stdin);
    printf("How many files: ");
    scanf("%d",&number);
    strcat(filePath,"/");

    struct myData *arr;

    arr = readMails(filePath, number);


   while(option!=5) {
       menu();
       printf("\n");
       printf("Command: ");
       scanf("%d",&option);
       printf("\n");
       // All the detailed time complexity explanations are below
       if(option == 1) {
       heapSort(arr,number,1); //O(NlogN)
       printEmails(arr,number); //O(N)
       }
       else if(option == 2) {
       heapSort(arr,number,2); //O(NlogN)
       printEmails(arr,number); //O(N)
       }
       else if(option == 3) {
       heapSort(arr,number,3); //O(NlogN)
       printEmails(arr,number); } //O(N)
       else if(option == 4) {
       printf("Enter the search key: ");
       scanf("%d",&searchKey);
       binSearch(arr,number,searchKey); //O(NlogN)
       }
       else printf("Goodbye!");

   }


}



void menu() { //O(1), since it just prints the messages for the menu one by one.
    printf("\nPlease choose one of the following options:\n");
    printf("(1) Display emails sorted by id\n");
    printf("(2) Display emails sorted by number of words\n");
    printf("(3) Display emails sorted by date\n");
    printf("(4) Search email by ID\n");
    printf("(5) Exit\n");
}


void binSearch(struct myData *mailInfos,int size,int key) {//heapSort is O(NlogN) (explained below), and the binary search algorithm is O(logN), so we can say this function is O(NlogN)
    heapSort(mailInfos,size,1);
    int l = 0;
    int r = size-1 ;
    int flag = 0;
    int m = -1;

    while(l <= r) {
         m = l + (r-l) / 2 ;

        if(mailInfos[m].mailID == key) {
            printf("Id: %d\n",mailInfos[m].mailID);
            printf("Sender: %s",mailInfos[m].sender);
            printf("Recipient: %s",mailInfos[m].receipt);
            printf("Date: %d\n",mailInfos[m].day);
            printf("Words: %d\n",mailInfos[m].noOfWords);

            flag = 1;
            break;
        }

        if(mailInfos[m].mailID < key) l = m + 1;
        else r = m - 1 ;

    }

    if(flag  == 0) printf("Mail ID Not Found!\n");


}


void heapSort(struct myData *mailInfos,int size,int criteria) {//heapSort is O(NlogN), since heapify is O(logN) and it executes N times.
    int i;
    for (i = size / 2 - 1; i >= 0; i--) {  //I'm actually doing BuildHeap here, it is O(N), but it is non-dominant term,so it does not affect the complexity.
        heapify(mailInfos,size, i,criteria);
    }


    for (i = size - 1; i >= 0; i--) {     // O(NlogN), with heapify operation

        swap(&mailInfos[0], &mailInfos[i]);


        heapify(mailInfos, i, 0,criteria);
    }

}



void swap(struct myData *a, struct myData *b) //Just swaps the struct values of the array, so it is O(1).
{
    struct myData tmp = *a;
      *a = *b;
      *b = tmp;
}

void heapify(struct myData *mailInfos, int size, int i,int criteria)//Heapify is O(logN), since it is related to the height of the tree, I just added if conditions but it does not change the complexity.
{



    if(criteria == 1)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;


    if (l < size && mailInfos[l].mailID > mailInfos[largest].mailID)
        largest = l;


    if (r < size && mailInfos[r].mailID > mailInfos[largest].mailID)
        largest = r;




    if (largest != i) {
        swap(&mailInfos[i], &mailInfos[largest]);


        heapify(mailInfos, size, largest,criteria);
    }

}




if(criteria == 2)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;


    if (l < size && mailInfos[l].noOfWords > mailInfos[largest].noOfWords)
        largest = l;


    if (r < size && mailInfos[r].noOfWords > mailInfos[largest].noOfWords)
        largest = r;




    if (largest != i) {
        swap(&mailInfos[i], &mailInfos[largest]);


        heapify(mailInfos, size, largest,criteria);
    }

}


if(criteria == 3)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;


    if (l < size && mailInfos[l].day > mailInfos[largest].day)
        largest = l;


    if (r < size && mailInfos[r].day > mailInfos[largest].day)
        largest = r;


    if (largest != i) {
        swap(&mailInfos[i], &mailInfos[largest]);


        heapify(mailInfos, size, largest,criteria);
    }

}


}


void buildHeap(struct myData *mailInfos, int size,int criteria) //Actually it looks like O(NlogN), but when we analize tightly it is Θ(N), it is the sum of the heights of all nodes.
{
    int i;

    int startIdx = (size / 2) - 1;


    for (i = startIdx; i >= 0; i--) {
        heapify(mailInfos, size, i,criteria);
    }
}

void printEmails(struct myData *mailInfos, int size) //It is O(N), since just for loop executes according to the size value
{
    int i;

    for(i = 0; i < size; i++) {
        printf("ID:%d \n",mailInfos[i].mailID);
        printf("Sender:%s",mailInfos[i].sender);
        printf("Recipient:%s",mailInfos[i].receipt);
        printf("Date:%d \n",mailInfos[i].day);
        printf("Words:%d\n\n",mailInfos[i].noOfWords);

    }

    printf("\n");
}


struct myData* readMails(char filePath[50],int number){//O(N^2), since it opens and reads N emails in the for loop, and for the last line it loops and counts the space characters.
                                                       //The inner while loop does not affect the complexity since we know how many times it read lines until the end of file, so we can consider it as a constant.
    FILE *inFile1;
    char fileName[50]="";
    char fileNumber[3] = "";
    int i;
    int validity=0;

    struct myData *arr = (struct myData*)malloc(number *sizeof(struct myData));

    int j=1;

    for(i=0; i < number; i++)
    {

        char str[200] = "";
        strcpy(fileName,filePath);

        itoa(i+1, fileNumber, 10);


        strcat(fileName,fileNumber);
        strcat(fileName,".txt");
        inFile1 = fopen(fileName,"r");

        if(inFile1 != NULL) { // By defining 'validity' , I let me know the folder is opened
            validity = 1;
        }

        if(inFile1 == NULL) { // If the validity is 1, but I can not open the files anymore, it means that user input excess number of emails
            if(validity == 1) { printf("Number of data files is not valid !"); exit(0);  }
            else { printf("Directory that contains the mails can not be found !"); exit(0); } // Otherwise, if validity is still 0, it means directly the datapath is incorrect
        }


        fseek(inFile1, 0, SEEK_SET);

        while(fgets(str,200,inFile1))
        {

            if(j==1)
                {
            int id = atoi(str);
            arr[i].mailID = id;
                }

            else if(j==2)
                {
                strcpy(arr[i].sender,str);
                }
            else if(j==3)
                {
                strcpy(arr[i].receipt,str);
                }

            else if(j==4) {
                int dayNo = atoi(str);
                arr[i].day = dayNo;
                }
            else if(j==5)
                {
                strcpy(arr[i].content,str);
                int k,words=0;

                for(k=0;k<strlen(str);k++) {
                    if(str[k] == ' ') words++;
                }
                arr[i].noOfWords = words+1;

                }

                j++;
                if(j==4) fseek(inFile1, 6, SEEK_CUR);
                if(j==2) fseek(inFile1, 6,SEEK_CUR);
                if(j==3) fseek(inFile1,4,SEEK_CUR);

        }

        j=1;
        strcpy(fileName,"");
        fclose(inFile1);
    }

    if(number)
    printf("%d Emails have been read successfully!\n",number);

    return arr;

}
