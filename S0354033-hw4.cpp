#include <stdio.h>
#include <stdlib.h>


int data1[2500]={0},data2[2500]={0};
int visit[501]={0};//點是否探訪 
int tatal;
int adj[501][501];//是否連接 
int succed=0;
int que[2500][3] = {0};
int input=1,output = 0;

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

void DFS(int x)
{
	int visi=0;
	for(int i=1;i<=tatal;i++)
	{
		visi=visi+visit[i];
		//cout<<visi<<endl;
	}
	//cout<<"///////////////"<<endl;
	if(succed==0)
	{
		if(visi!=tatal)
		{
			for(int j=1;j<=tatal;j++)
			{
				if( adj[j][x]==1 && visit[j]==0 )
				{
					visit[j]=1;
					DFS(j);					//往下搜尋 
					if(succed==1)
                        visit[j]=visi;
					else
					    visit[j]=0;
				}
			}
		}
		else
		{
            //cout<<"12365464987";
			if(adj[x][1]==1)
			{
				succed=1;
			}
			
		}
	}	
}

void BFS(){
    int okk=0; 
    while(input != output){
        int w = que[output][0];
        int depth = que[output][1] + 1;
        //printf("w=%d\n",w);        
        for(int i=1;i<=tatal;i++){
            if( adj[i][w]==1){
                //printf("i=%d %d %d\n",i,depth,w);
                //printf("input=%d",input);
                if(i==1 && depth-1==tatal){
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
	visit[1]=1;
	datain = fopen("input4.txt","r");
	if(!datain)
	{
		printf("data not exist");
        system("PAUSE");
        return 0;
	}
	fscanf(datain,"%d",&tatal);
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
	
	DFS(1);
	/*for(int k=1;k<=tatal;k++)
	{
		cout<<visit[k]<<endl;
	}*/
	printf("DFS:");
	for(int i=1;i<=tatal;i++)
	{
		for(int j=1;j<=tatal;j++)
		{
			if(visit[j]==i)
			printf("%d ",j);
		}
	}
	printf("\n");
	que[0][0] = 1;
	que[0][1] = 1;
	que[0][2] = -1;
	printf("BFS:");
	BFS();
	
	system("pause");
	return 0;
} 
