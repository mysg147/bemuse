#include<iostream>
using namespace std;
struct queue{
    int x,y;
    struct queue *next;
};
int level=1,score=0;
int randoms(){  
        int num = rand() %5;
            return num;
}
void createBoard(char board[7][7]){
    int i,j;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++)board[i][j]=' ';
    }
    board[0][0]='S';
    board[6][6]='D';
    board[1][2]='o';
    board[2][1]='o';
    board[2][2]='o';
    board[6][1]='o';
    board[5][3]='o';
    board[5][4]='o';
    board[5][5]='o';
    board[4][4]='o';
    board[4][5]='o';
    board[1][6]='o';


}
void printBoard(char board[7][7]){
    int i,j;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++)cout<<board[i][j];
        cout<<"\n";
    }
}
struct queue *insertAtEnd(struct queue *start, int a, int b ){
    struct queue *n,*ptr=start;
    n=new queue;
    n->x=a;
    n->y=b;
    n->next=NULL;
    if(start==NULL){
            start=n;
    }
    else{
        while(ptr->next!=NULL)ptr=ptr->next;
        ptr->next=n;
    }
    return start;
}
struct queue *insertAtBegin(struct queue *start,int a,int b){
    struct queue *n=new queue;
    n->next=start;
    n->x=a;
    n->y=b;
    start=n;
    return start;
}
void addInQueue(struct queue *start, char board[7][7]){
    start=insertAtEnd(start,0,0);
    int flag=0;
    while(start!=NULL){
    board[start->x][start->y]='`';
    //left
    if((start->y)-1>=0){
        if(board[start->x][(start->y)-1]=='D'){
                flag++;
                break;
        }
        if(board[start->x][(start->y)-1]==' '){
            board[start->x][(start->y)-1]='.';//setting neighbours
            start=insertAtEnd(start,start->x,start->y-1);//adding in ll
        }
    }
    //right
    if((start->y)+1<=6){
            if(board[start->x][(start->y)+1]=='D'){
                flag++;
                break;
            }
            if(board[start->x][start->y+1]==' '){
                board[start->x][start->y+1]='.';
                start=insertAtEnd(start,start->x,start->y+1);//adding in ll
            }
    }
    //up
    if(start->x-1>=0){
        if(board[start->x-1][start->y]=='D'){
                flag++;
                break;
            }
        if(board[start->x-1][start->y]==' '){
            board[start->x-1][start->y]='.';
            start=insertAtEnd(start,start->x-1,start->y);//adding in ll
        }
    }
    //down
    if(start->x+1<=6){
            if(board[start->x+1][start->y]=='D'){
                flag++;
                break;
            }
            if(board[start->x+1][start->y]==' '){
                board[start->x+1][start->y]='.';
                start=insertAtEnd(start,start->x+1,start->y);//adding in ll
            }

    }
    start=start->next;
    }
    if(flag==0){cout<<"unreachable sorry\n";exit(0);}
        printBoard(board);
}
void move(char board1[7][7],char board2[7][7]){
    char m;
    int a=0,b=0,pa=0,pb=0,flag=0;
    printBoard(board2);
    while(1){
        cout<<"enter move ";
        cin>>m;
        if(m=='l'&&b-1>=0)b--;
        else if(m=='r'&&b+1<=6)b++;
        else if(m=='u'&&a-1>=0)a--;
        else if(m=='d'&&a+1<=6)a++;
        if(board2[a][b]=='D'){
            score++;
            flag++;
            break;
        }
        else if(board2[a][b]!='o'){
            board2[pa][pb]=' ';
            board2[a][b]='S';
            pa=a;
            pb=b;
        }
        else if(board2[a][b]=='o'){
            a=pa;
            b=pb;
        }
        if(board1[a][b]=='`')score++;
        else if(board1[a][b]==' ')score=score-4;
        else if(board1[a][b]=='?')score--;
        board1[a][b]='?';
        system("cls");
        printBoard(board2);
        cout<<"\nscore= "<<score<<"\n";
    }
    if(flag>0)cout<<"destination reached";
}
int main(){
    char board[7][7],board2[7][7];
    struct queue *head=NULL;
    createBoard(board);
    printBoard(board);
    addInQueue(head,board);
    createBoard(board2);
    move(board,board2);
}
