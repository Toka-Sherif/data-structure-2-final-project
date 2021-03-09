
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

int src,distination,count=0;   //starting vertex
int V,E,K;  //no of vertices ,edges and distance k

int MAXSIZE = 100;
int stack[100];
int top = -1;

int isempty()
{
    if(top == -1)
        return 1;
    else
        return 0;
}

int isfull()
{
    if(top == MAXSIZE)
        return 1;
    else
        return 0;
}

int pop()
{
    int data;

    if(!isempty())
    {
        data = stack[top];
        top = top - 1;
        return data;
    }
    else
    {
        printf("Could not retrieve data, Stack is empty.\n");
    }
}

int push(int data)
{

    if(!isfull())
    {
        top = top + 1;
        stack[top] = data;
    }
    else
    {
        printf("Could not insert data, Stack is full.\n");
    }
}

void intialize(int arr[][V]) //intializeialize matrix to zeros
{
    int i,j;
    for(i = 1; i <= V; i++)
        for(j = 1; j <= V; j++)
            arr[i][j] = 0;
}

void addEdge_3(int arr[][V],int src, int dest, int value)      //function to set arr[src][dest],arr[dest][src] to 1
{
    arr[src][dest] = value;
}

void addEdge_1(int arr[][V],int src, int dest)     //function to set arr[src][dest],arr[dest][src] to 1
{
    arr[src][dest] = 1;
    arr[dest][src] = 1;
}

void printAdjancyMatrix(int arr[][V])     //function to print adjancymatrix of the given edges
{
    int i, j;

    for(i = 1; i <= V; i++)
    {
        for(j = 1; j <= V; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int minDistance(int dist[],int visited[])    //function to find the vertex with minimum distance from set of vertices not yet included in shortest path
{

    // intializeialize min value
    int min = INFINITY, nextnode;

    for (int v = 1; v <= V; v++)
        if (visited[v] == 0 &&
                dist[v] <= min)
            min = dist[v], nextnode = v;

    return nextnode;
}


void printPath(int path[], int j)   //function to print shortest path from src to des j using path array
{


    if (path[j] == -1)   //base case if j is source
        return;

    printPath(path, path[j]);

    printf("%d ", j);
}


void print_3(int dist[], int n,int path[],int target ,int time[])   //function to print src ->dest distance shortest path
{

    printf("Vertex\t Distance\tPath");
    for (int i = 1; i <= V; i++)
    {
        if(src!=i && i==target)
        {
            printf("\n%d -> %d \t\t %d\t\t%d ",src, i, dist[i], src);
           // printf("\nTotal cost = %d$",dist[i]);
            printPath(path, i);
        }
    }
     for (int i = 1; i <= V; i++)
    {
        if(src!=i && i==target)
        {
            printf("\nTotal time %d hours",time[i]);
            printf("\nTotal cost = %d$",dist[i]);
        }
    }
}

void shortestPath_3(int graph_time[V][V],int graph_cost[V][V], int src, int target, int amount)             //function to get single shortest path for a graph represented using adjancy matrix
{
    int unique_path_arr[V],c_path=0;
    int overlay=0;

    int dist[V];
    int time[V];

    int visited[V];

    int path[V];


    for (int i = 1; i <= V; i++)            //intialize all distances as max int and flags 0
    {
        path[src] = -1;
        dist[i] = INFINITY;
        time[i]=INFINITY;
        visited[i] = 0;
    }


    dist[src] = 0;    //distance of src vertex from itself is 0
    time[src]=0;


    for (int count = 1; count <= V - 1; count++)     //find shortest path for all vertices
    {
        int nextnode = minDistance(dist, visited);     //pick min distance vertex from set of vertices not yet processed u is always equal src in first iteration

        printf("minimum distance is:%d\n",nextnode);
        visited[nextnode] = 1;             //mark picked vertex as processed
        if( path[nextnode] != src && nextnode != target)
        {
            dist[nextnode]=dist[nextnode]+amount;
            time[nextnode]++;
        }
        for (int v = 1; v <= V; v++)
        {
            // printf("overlay:%d,vistited[%d]:%d\n",overlay,v,visited[v]);
            if (!visited[v] && graph_cost[nextnode][v]  && graph_time[nextnode][v] )        //update dist[v] if it's not in flags there is an edge from u to v and total weight of path from src to v through u is smaller than current value of dist[v]
            {
                if(dist[nextnode]+ graph_cost[nextnode][v]+graph_time[nextnode][v]*amount < dist[v])
                {
                    path[v] = nextnode;
                    //printf("path[%d]=%d\n",v,path[v]);
                    dist[v] = dist[nextnode] + graph_cost[nextnode][v]+graph_time[nextnode][v]*amount;
                    time[v]=time[nextnode]+graph_time[nextnode][v];
                    //printf("time[%d]=%d\n",v,time[v]);
                    //printf("dist[%d]=%d\n",v,dist[v]);
                }
            }
        }
    }

    print_3(dist, V, path,target,time);
}

void main_part_3()
{
    int s,d,t,c,M;
    printf("please enter amount M:\n");
    scanf("%d",&M);
    printf("please enter number of cites:\n");
    scanf("%d",&V);
    printf("please enter number of routes:\n");
    scanf("%d",&E);
    int time_matrix[V][V];
    int cost_matrix[V][V];
    intialize(time_matrix);
    intialize(cost_matrix);
    int i;
    printf("please enter source,destination,time and cost for each route:\n in the form (src dis t c):\n");
    for(i=0; i<E; i++)
    {
        int a,b;
        scanf("%d %d %d %d",&s,&d,&t,&c);
        addEdge_3(time_matrix,s,d,t);
        addEdge_3(cost_matrix,s,d,c);

    }


    printf("The time matrix is \n");
    printAdjancyMatrix(time_matrix);
    printf("The cost matrix is \n");
    printAdjancyMatrix(cost_matrix);


    printf("please enter source city:\n");
    scanf("%d",&src);
    printf("please enter destination city:\n");
    scanf("%d",&distination);


    shortestPath_3(time_matrix,cost_matrix,src,distination,M);
}

void print_1(int dist[], int n,int path[])   //function to print src ->dest distance shortest path
{

    printf("Vertex\t Distance\tPath");
    for (int i = 1; i <= V; i++)
    {
        if(src!=i)
        {
            printf("\n%d -> %d \t\t %d\t\t%d ",src, i, dist[i], src);
            printPath(path, i);
        }
    }


    int sum=0;

    for (int i = 1; i <= V; i++)
    {
        if(dist[i]==K)
        {
            sum=sum+1;
        }
    }
    printf("\nThere are %d people with %d connections away starting from %d",sum,K,sum);

}

void shortestPath_1(int graph[V][V], int src)           //function to get single shortest path for a graph represented using adjancy matrix
{

    int dist[V];      //array store shortest distance from src to dest i

    int flags[V];             //array to store flags,flag will be 1 if vertex i is included in shortest path or shortest distance from src to i

    int path[V];          //array to store shortest path


    for (int i = 1; i <= V; i++)            //intialize all distances as max int and flags 0
    {
        path[src] = -1;
        dist[i] = INT_MAX;
        flags[i] = 0;
    }


    dist[src] = 0;    //distance of src vertex from itself is 0


    for (int count = 1; count <= V - 1; count++)     //find shortest path for all vertices
    {

        int u = minDistance(dist, flags);     //pick min distance vertex from set of vertices not yet processed u is always equal src in first iteration

        flags[u] = 1;             //mark picked vertex as processed


        for (int v = 1; v <= V; v++)         //update dist value of adjacent vertices of picked vertex


            if (!flags[v] && graph[u][v] &&dist[u] + graph[u][v] < dist[v])        //update dist[v] if it's not in flags there is an edge from u to v and total weight of path from src to v through u is smaller than current value of dist[v]
            {
                path[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    print_1(dist, V, path);
}



void main_part_1()
{
    printf("please enter number of vertices:\n");
    scanf("%d",&V);
    printf("please enter number of edges:\n");
    scanf("%d",&E);
    int adjMatrix[V][V];
    intialize(adjMatrix);
    int i;
    printf("please enter edges in the form (u v):\n");
    for(i=0; i<E; i++)
    {
        int a,b;
        scanf("%d",&a);
        scanf("%d",&b);
        addEdge_1(adjMatrix,a,b);
    }

    printf("The adjancy matrix:\n");
    printAdjancyMatrix(adjMatrix);


    printf("please enter starting vertex:\n");
    scanf("%d",&src);
    printf("please enter value K:\n");
    scanf("%d",&K);


    shortestPath_1(adjMatrix, src);


}

//Function to solve the maze by backtracking algorithm
//takes row, column, n (size of array), arr (input array), answer array (array to write the final path in)
//returns 1 if there is a path and 0 if there is no path
int solve(int row, int col,int n,int arr[n][n],int ansArr[n][n])
{
    if((row==n-1) && (col==n-1)) //check if the destination reached
    {
        push(col);
        push(row);
        ansArr[row][col] = 1;
        return 1;
    }
    //check if we can path through this block
    if(row>=0 && col>=0 && row<n && col<n && ansArr[row][col] == 0 && arr[row][col] == 0)
    {
        ansArr[row][col] = 1; //write it in the answer array
        if(solve(row, col+1,n,arr,ansArr))//check if there is a path right
        {
            push(col);
            push(row);
            return 1;
        }
        if(solve(row+1, col,n,arr,ansArr))//check if there is a path downward
        {
            push(col);
            push(row);
            return 1;
        }
        if(solve(row, col-1,n,arr,ansArr))//check if there is a path left
        {
            push(col);
            push(row);
            return 1;
        }
        if(solve(row-1, col,n,arr,ansArr))//check if there is a path upward
        {
            push(col);
            push(row);
            return 1;
        }
        ansArr[row][col] = 0;//backtrack if no path

        return 0;
    }
    return 0;

}

void print()
{
    while(!isempty())
    {
        int row = pop();
        int col = pop();
        printf("(%d-%d) ",row,col);
    }
}


void main_part_2()
{
    int n,i,j;
    printf("please enter N:\n");
    scanf("%d",&n);
    int arr[n][n],ansArr[n][n];
    printf("please enter values for maze: \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            ansArr[i][j] = 0;
        }
    }
    if (solve(0,0,n,arr,ansArr))
     print();
    else
        printf("no path found\n");
    return 0;
}



void main_menu()
{
    int c;
    printf("****WELCOME TO OUR PROJECT*****\n");
    printf("CHOOSE:\n");
    printf("1-part(1)\n2-part(2)\n3-part(3)\n4-exit\n");
    printf("enter your choice:\n");
    scanf("%d",&c);
    switch(c)
    {
    case 1:
        main_part_1();
        break;
    case 2:
        main_part_2();
        break;
    case 3:
        main_part_3();
        break;
    case 4:
        return;
        break;
    }
    printf("\npress any key to continue...");
    getch();
    system("CLS");
    main_menu();

}


int main()
{
   system("CLS");
   main_menu();


    return 0;
}
