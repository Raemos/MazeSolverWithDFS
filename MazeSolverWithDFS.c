#include<stdio.h>
#include<stdlib.h>
#define maxsize 10
#define showallvalues 0
struct sinputlist{
 char symbol;
 struct sinputlist *next; 
};
struct graphnode{
 int pos;
 struct graphnode *link;	
};
char maze2d[maxsize][maxsize];
int width,height,noofspace=2,startpoint,endpoint;
int visitcheck[maxsize*maxsize][2];
struct graphnode *list[maxsize*maxsize];
struct graphnode *topstack;

int stacklength()
{
 struct graphnode *temp;
 int count=0;
 temp = topstack;
 while(temp!=NULL)
    {
	 count++;
	 temp=temp->link;
 	}
 return count;	
}	
void showstack()
{
 struct graphnode *temp;
 temp = topstack;
 printf("\n");
 while(temp!=NULL)
    {
	 printf("%d->",temp->pos);
	 temp=temp->link;
	}
}	
int popstack()
{
 int i;
 struct graphnode *temp;
 if(topstack==NULL)
    return -1;
 temp = topstack; 
 i = topstack->pos;
 topstack=topstack->link;
 free(temp);
 return i; 
}	
void pushstack(int value)
{
 struct graphnode *temp;	
 temp=(struct graphnode*) malloc(sizeof(struct graphnode));
 temp->pos = value;
 if(topstack==NULL)
	{
     topstack=temp;
	 temp->link=NULL;
    }	 
 else
	{
	 temp->link = topstack;
	 topstack=temp; 
	}
}
void displayvisits()
{
 int i;
 for(i=0;i<noofspace;i++)
    printf("\n%d:%d",visitcheck[i][0],visitcheck[i][1]); 	
}	
int isvisit(int po)
{
 int i;
 for(i=0;i<noofspace;i++)
    if(visitcheck[i][0]==po)
        return visitcheck[i][1];
 return 0;
}
void visit(int po)
{
 int i;
 for(i=0;i<noofspace;i++)
    if(visitcheck[i][0]==po)
	    {
		 visitcheck[i][1]=1;
	     return;	
		}
}	
void initializevisit()
{
 int i;	
 for(i=0;i<noofspace;i++)
	{
	 visitcheck[i][0]=list[i]->pos;
	 visitcheck[i][1]=0;
	}
}
void dfs(int v)
{
 int x;
 pushstack(v);
 if(showallvalues)
	showstack();
 if(topstack->pos == endpoint)
    return;
 int i,j;
 for(j=0;j<noofspace;j++)
     if(list[j]->pos==v)
		{
         i=j;
		}
 visit(v);
 struct graphnode *w;
 for(w=list[i]->link;w;w=w->link)
    if(topstack->pos !=endpoint)
	    if(!isvisit(w->pos)) 
	        {   
		     dfs(w->pos);
	        }
 if(topstack->pos!=endpoint)			
    x=popstack();
}
void showfinal()
{
 int len,i,j,n;
 char ch;
 len=stacklength();
 int solution[len];
 struct graphnode* temp;
 for(i=0;i<len;i++)
	{
	 n=popstack();
	 solution[i]=n;
	}
 for(i=1;i<len-1;i++)
	{
	 if(solution[i] == solution[i-1]+1	&& solution[i] == solution[i+1]-1)
	    ch = 196; //left -> right
	 else if(solution[i] == solution[i-1]-1 && solution[i] == solution[i+1]+1)	
		ch = 196; //right -> left
	 else if(solution[i] == solution[i-1]+width && solution[i] == solution[i+1]-width)	
        ch = 179; //top -> bottom
	 else if(solution[i] == solution[i-1]-width && solution[i] == solution[i+1]+width)	
	    ch = 179; //bottom -> top
	 else if(solution[i] == solution[i-1]+1 && solution[i] == solution[i+1]-width)
	    ch = 191; //left -> bottom
	 else if(solution[i] == solution[i-1]-width && solution[i] == solution[i+1]+1)
        ch = 191; //bottom -> left 
	 else if(solution[i] == solution[i-1]-1 && solution[i] == solution[i+1]-width)
		ch = 218; //right -> bottom
	 else if(solution[i] == solution[i-1]-width && solution[i] == solution[i+1]-1)
		ch = 218; //bottom -> right
	 else if(solution[i] == solution[i-1]+1 && solution[i] == solution[i+1]+width)
		ch = 217; //left -> top
	 else if(solution[i] == solution[i-1]+width && solution[i] == solution[i+1]+1)
		ch = 217; //top -> left
	 else if(solution[i] == solution[i-1]-1 && solution[i] == solution[i+1]+width)
		ch = 192; //right -> top
	 else if(solution[i] == solution[i-1]+width && solution[i] == solution[i+1]-1)
		ch = 192; //top -> right
	 maze2d[solution[i]/width][solution[i]%width]=ch;
	}
 maze2d[startpoint/width][startpoint%width]='x';
 maze2d[endpoint/width][endpoint%width]='y';
 printf("\nThe Soluton is:\n");
 for(i=0;i<height;i++) 
    {
	 for(j=0;j<width;j++)
	    printf("%c",maze2d[i][j]);
	 printf("\n");
    }	 
}	
void solvegraph()
{
 int x;
 initializevisit();
 if(showallvalues)
	{
	 printf("\n Start point: %d",startpoint);
	 printf("\n End point: %d",endpoint);
     printf("\n The State of The stack after every iteration: ");
	} 
 dfs(startpoint);
 if(showallvalues)
	{
	 printf("\n The Visited Nodes are: ");
	 displayvisits();
	} 
 int len;
 len=stacklength();
 if(len==0)
    {
	 printf("\n No solution Found!");
	 exit(0);
	} 
 else
    showfinal();
} 
void makegraph()
{
 int i,j,k;
 for(i=0;i<height;i++)
    for(j=0;j<width;j++)
        if(maze2d[i][j]==' ')
            noofspace++;
 k=0;			
 for(i=0;i<height;i++)	
    for(j=0;j<width;j++)
	    {
		 if(maze2d[i][j]==' ')
		    {
			 list[k] = (struct graphnode*)malloc(sizeof(struct graphnode));
             if(list[k]==NULL)
                printf("memory error");			 
			 list[k]->pos = j + i*width;
			 k++;
			}
	     else if(maze2d[i][j]=='x')
			{
			 list[k] = (struct graphnode*)malloc(sizeof(struct graphnode));
			 if(list[k]==NULL)
                printf("memory error");
			 list[k]->pos = j + i*width;
			 maze2d[i][j] = ' ';
			 startpoint = j+ i*width;
			 k++;
			}
		 else if(maze2d[i][j]=='y')
			{
			 list[k] = (struct graphnode*)malloc(sizeof(struct graphnode));
			 if(list[k]==NULL)
                printf("memory error");
			 list[k]->pos = j + i*width;
			 maze2d[i][j] = ' ';
			 endpoint = j+ i*width;
			 k++;
			}
		}		 
 int toppos=-1,rightpos=-1,bottompos=-1,leftpos=-1;
 struct graphnode *temp1,*temp2;			
 for(i=0;i<noofspace;i++)
	{		
	 toppos=-1;rightpos=-1;bottompos=-1;leftpos=-1;
	 if(list[i]->pos==0)
		{
		 if(maze2d[0][1] == ' ')
            rightpos= 1 + 0*width;	
         if(maze2d[1][0] == ' ')
            bottompos= 0 + 1*width;		 
	    }
	 else if(list[i]->pos==width *(height-1))
	    {
		 if(maze2d[height-2][0] == ' ')
            toppos = 0 + (height-2)*width;
		 if(maze2d[height-1][1] == ' ')
            rightpos = 1 + (height-1)*width;
        }
     else if(list[i]->pos == width-1)
	    {
		 if(maze2d[0][width-2]== ' ')
           	leftpos= width-2 + 0*width;
         if(maze2d[1][width-1]== ' ')
            bottompos=width-1 + 1*width;		 
		} 
	 else if(list[i]->pos == width*height-1)
	    {
         if(maze2d[height-2][width-1] == ' ')
		    toppos = width-1 + width*(height-2);
		 if(maze2d[height-1][width-2] == ' ')
            leftpos= width-2 + width*(height-1);		 
		}
     else if(list[i]->pos <width)
	    {
         if(maze2d[0][list[i]->pos+1] == ' ')
            rightpos = list[i]->pos + 1;
         if(maze2d[0][list[i]->pos-1] == ' ')
            leftpos = list[i]->pos - 1;
         if(maze2d[1][list[i]->pos] == ' ')
            bottompos = list[i]->pos + width*1;
		}
	 else if(list[i]->pos%width == 0)
		{
         if(maze2d[list[i]->pos/width -1][0] == ' ')
		    toppos = (list[i]->pos/width -1)*width;
         if(maze2d[list[i]->pos/width][1] == ' ')
		    rightpos = (list[i]->pos/width)*width +1;
		 if(maze2d[list[i]->pos/width +1][0] == ' ')
            bottompos = (list[i]->pos/width +1)*width;		 
		}
     else if(list[i]->pos >= width *(height-1))
		{
		 if(maze2d[height-2][list[i]->pos%width]==' ')
		    toppos = list[i]->pos%width + width*(height-2);
         if(maze2d[height-1][list[i]->pos%width+1]==' ')
            rightpos = list[i]->pos%width+1 + width*(height-1);
         if(maze2d[height-1][list[i]->pos%width-1]==' ')
            leftpos = list[i]->pos%width-1 + width*(height-1);
	    }
	 else if(list[i]->pos%width == width-1)
		{
		 if(maze2d[list[i]->pos/width -1][width-1]== ' ')
		    toppos = width -1 + (list[i]->pos/width-1)*width;
	     if(maze2d[list[i]->pos/width +1][width-1]== ' ')
		    bottompos = width -1 + (list[i]->pos/width+1)*width;
		 if(maze2d[list[i]->pos/width][width-2] == ' ')
            leftpos = width -2 +(list[i]->pos/width)*width;		
		}
     else
		{
         if(maze2d[list[i]->pos/width-1][list[i]->pos%width] == ' ')
            toppos = (list[i]->pos%width) +(list[i]->pos/width-1)*width;		 
		 if(maze2d[list[i]->pos/width][list[i]->pos%width+1] == ' ')
            rightpos = (list[i]->pos%width+1) +(list[i]->pos/width)*width;
		 if(maze2d[list[i]->pos/width+1][list[i]->pos%width] == ' ')
            bottompos = (list[i]->pos%width) +(list[i]->pos/width+1)*width;
         if(maze2d[list[i]->pos/width][list[i]->pos%width-1] == ' ')
            leftpos = (list[i]->pos%width-1) +(list[i]->pos/width)*width;
		}	
	temp1=list[i];
	if(toppos>-1)
		{
		 temp2= (struct graphnode*) malloc(sizeof(struct graphnode));
		 temp2->link=NULL;
		 temp2->pos = toppos;
		 temp1->link = temp2;
		 temp1= temp1->link;
		} 
	if(rightpos>-1)
		{
		 temp2= (struct graphnode*) malloc(sizeof(struct graphnode));
		 temp2->link=NULL;
		 temp2->pos = rightpos;
		 temp1->link = temp2;
		 temp1= temp1->link;
		}
	if(bottompos>-1)
		{
		 temp2= (struct graphnode*) malloc(sizeof(struct graphnode));
		 temp2->link=NULL;
		 temp2->pos = bottompos;
		 temp1->link = temp2;
		 temp1= temp1->link;
		}
    if(leftpos>-1)
		{
		 temp2= (struct graphnode*) malloc(sizeof(struct graphnode));
		 temp2->link=NULL;
		 temp2->pos = leftpos;
		 temp1->link = temp2;
		 temp1= temp1->link;
		}
    //printf("\n%d:%d %d,%d,%d,%d",i,list[i]->pos,toppos,rightpos,bottompos,leftpos);		
	}
 struct graphnode *temp;
 if(showallvalues)
	{
	 printf("\n The Adjacency List of Graph is: ");
	 for(i=0;i<noofspace;i++)
		{
		 temp = list[i];
		 printf("\n");
		 while(temp!=NULL)
			{
			 printf("%d ->",temp->pos);
			 temp = temp->link;
			}
		 printf("NULL");
   		}	 
	}
}	
void sinput()
{
 int size=0,i,j,k,nolines=1,linelen=0,big,countx=0,county=0;	
 char str;
 struct sinputlist *end,*start,*temp;
 start=NULL;
 end=NULL;
 printf("\n input the Maze: \n");
 do{
	 scanf("%c",&str);
	 size++;
	 temp = (struct sinputlist*) malloc(sizeof(struct sinputlist));
	 temp->symbol=str;
	 temp->next=NULL;
	 if(start==NULL)
		{
		 start=temp;
		 end=temp;
		}
     else
		{
         end->next=temp;
		 end=temp;
		} 	
   }while(str!='.');
 char maze[size];
 temp=start;
 for(i=0;i<size;i++)
    {
	 maze[i]=temp->symbol;
	 temp=temp->next;
	}
 maze[size-1]='\0';
 for(i=0;i<size;i++)
	if(maze[i]==10)
	    nolines++;
 int eachlinelen[nolines];
 for(i=0;i<nolines;i++)
    eachlinelen[i]=0;
 for(i=0,j=0;maze[i]!='\0';i++)
	{
	 if(maze[i]!=10)
		eachlinelen[j]++;
	 else
        j++;	 
	}
 big=eachlinelen[0];
 for(i=1;i<nolines;i++)
	if(eachlinelen[i]>big)
	    big=eachlinelen[i];
 for(i=0;i<nolines;i++)
    for(j=0;j<big;j++)
        maze2d[i][j]=' ';
 j=0;k=0;
 for(i=0;maze[i]!='\0';i++)
    {
	 if(maze[i]!=10)
	    {
		 maze2d[j][k]=maze[i];
         k++;
	    }
     else
	    {
      	 j++;
         k=0;
		}
	}
 for(i=0;i<nolines;i++)
    for(j=0;j<big;j++)
	{
     if(maze2d[i][j]!='#'&&maze2d[i][j]!=' '&&maze2d[i][j]!='x'&&maze2d[i][j]!='y')
	    {
		 printf("\n Invalid input type, restart");
         exit(0);		
		}
     else if(maze2d[i][j]=='x')
		{
		 if(countx==1)
			{
             printf("\n Invalid input type, restart");
             exit(0);		
			}
		 else
		    countx=1;
		}
     else if(maze2d[i][j]=='y')
		{
		 if(county==1)
			{
             printf("\n Invalid input type, restart");
             exit(0);		
			}
		 else
		    county=1;
		}		
    }
 if(!countx	|| !county)
    {
	 printf("\n Invalid input type, restart");
	 exit(0);
	} 
 width=big;
 height=nolines;
}
int main()
{
 int i,j;	
 sinput();
 if(showallvalues)
	printf("\n Input done! ");
 makegraph();
 if(showallvalues)
	printf("\n Graph made! ");
 solvegraph();
 if(showallvalues)
	printf("\n Graph Solved! ");
 return 0;
 
} 
 