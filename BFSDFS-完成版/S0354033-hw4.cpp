#include <stdio.h>
#include <stdlib.h>


int data1[2500]={0},data2[2500]={0};
int stack[2500][3] = {0};
int tatal;
int ansstack[][3] = {0};

int adj[501][501];//是否連接 
int succed=0;
int que[2500][3] = {0};
int input=1,output = 0;
int point = 0; // stack 的 

void printAns(int ans){
    if(ans==-1){ return ;}    
    printf("%d ",que[ans][0]);
    printAns(que[ans][2]);
}
int check(int i,int depth,int sit){ // situation
    //printf("%d",input);         
    if(que[sit][0] == i){
        return 1;
    }
    else{
        if(depth!=1){
            return check(i,depth-1,que[sit][2]);
        }
        else{
            return 0;
        }
    }        
}

int checkstack(int i,int depth,int sit){ // situation
//    printf("%d ",sit);       
//	printf("%d ",ansstack[sit][0])  ;
//	printf("%d ", depth);
    if(ansstack[sit][0] == i){
        return 1;
    }
    else{
        if(depth!=1){
            return checkstack(i,depth-1,ansstack[sit][2]);
        }
        else{
            return 0;
        }
    }        
}

void DFS()
{	
	int okk=0; 
	input=1,output=0;
	while(output!=-1){		
    	printf("目前stack資料 : ");
		for(int u=output;u>=0;u--){
			printf("%d ",stack[u][0]);
		}
		printf("\n");
        int w = stack[output][0];
        int depth = stack[output][1] + 1;
        ansstack[point][0] = stack[output][0];
		ansstack[point][1] = stack[output][1];
		ansstack[point][2] = stack[output][2];
		point++;
		stack[output][0] = 0;
		stack[output][1] = 0;
		stack[output][2] = 0;
		input--;
		output--;
        //printf("w=%d\n",w);
        for(int i=tatal;i>=1;i--){
            if( adj[i][w]==1){
                //printf("i=%d %d %d\n",i,depth,w);
                //printf("input=%d",input);
                if(i==1 && depth-1==tatal){
                	printf("目前stack資料 : ");
					for(int u=output;u>=0;u--){
						printf("%d ",stack[u][0]);
					}
					printf("\n");
                	printf("%d ",ansstack[0][0]);
                	for(int m=tatal-1;m>0;m--){
                		printf("%d ", ansstack[point-m][0]);
					} 	
                    okk=1;
                    break;
                }
                if(checkstack(i,depth-1,point-1) == 0){
                    stack[input][0] = i;
                    stack[input][1] = depth;
                    stack[input][2] = point-1;
                    //printf("%d %d %d\n",i,depth,point-1);
                    input++;
                    output++;
                }
            }
        }
        if(okk==1){            
            break;
        }
    }
}

void BFS(){
    int okk=0;
    input=1;output=0;
    while(input != output ){
    	printf("目前queue資料 : ");
		for(int u=output;u<input;u++){
			printf("%d ",que[u][0]);
		}
		printf("\n");
        int w = que[output][0];
        int depth = que[output][1] + 1;
        //printf("w=%d\n",w);        
        for(int i=1;i<=tatal;i++){
            if( adj[i][w]==1){
                //printf("i=%d %d %d\n",i,depth,w);
                //printf("input=%d",input);
                if(i==1 && depth-1==tatal){
                	printf("目前queue資料 : ");
					for(int u=output+1;u<input;u++){
						printf("%d ",que[u][0]);
					}
					printf("\n");
			        printAns(output);
                    okk=1;
                    break;
                }
                if(check(i,depth-1,output) == 0){
                    que[input][0] = i;
                    que[input][1] = depth;
                    que[input][2] = output;
                    //printf("%d %d %d\n",i,depth,output);
                    input++;
                }
            }
        }
        if(okk==1){            
            break;
        }
        output++;
    }
}


int main()
{
    FILE *datain;
	int cnt=0;
	datain = fopen("input4.txt","r");
	if(!datain)
	{
		printf("data not exist");
        system("PAUSE");
        return 0;
	}
	fscanf(datain,"%d",&tatal);
	ansstack[tatal][3] = {0};
	do{		
		//cout<<data1[cnt]<<"  "<<data2[cnt]<<endl;
		cnt++;
	}while(fscanf(datain,"%d %d",&data1[cnt],&data2[cnt])!=EOF);
	//cout<<cnt;
	fclose(datain);
	
	for(int i=0;i<cnt;i++)
	{
		int d1,d2;
		d1=data1[i];
		d2=data2[i];
		adj[d1][d2]=1;
		adj[d2][d1]=1;
	}
	
	/*for(int k=1;k<=tatal;k++)
	{
		cout<<visit[k]<<endl;
	}*/
	stack[0][0] = 1;
	stack[0][1] = 1;
	stack[0][2] = -1;
	printf("DFS:\n");
	DFS();
	
	printf("\n");
	que[0][0] = 1;
	que[0][1] = 1;
	que[0][2] = -1;
	printf("BFS:\n");
	BFS();
	
	system("pause");
	return 0;
} 
