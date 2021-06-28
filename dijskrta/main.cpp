#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int hillN ;
struct string
{
    char name[100];
    char name2[100];
};
int counter=0;

string unvisited[100],visited[100],startV;//gidilmeyen nodelar,gidilen ve baslangic nodeu(startV)
int unvisitedN = 0,visitedN = 0;

struct edge//baglantilar icin
{
    string v1;//mesela baslangic nodeu (A)
    string v2;// gidilen node ikinci node(B)
    int cost;//maliyeti

};

edge edges[100];//array cunku aradaki baglantilari yazabilmem gerekiyor
int EdgesN = 0;//arrayin 0.indexten basladigini gostermek icin

struct minPath
{
    string thisnode;//nodelar
    string Previous;//kendinden onceki node
    int dist;//baslangic nodeuna  olan uzaklik
    int dist2;
};
minPath minPaths[100];

void graph()
{

    printf("\n\nSTEP|     N'    |");

    for(int i=0; i<hillN-1; i++){
        printf("D(%s) |\t ",minPaths[i+1].thisnode.name);
    }
        printf("\n____________________________________________________________");

    }



void controller()
{
    int flag = 0;
    for(int i = 0 ; i<EdgesN; i++)
    {
        for(int j=0;j<i;j++){
            if((edges[i].v1.name[0] == edges[j].v1.name[0]) && (edges[i].v2.name[0] == edges[j].v2.name[0]) && i!= 0)
                flag=1;
        }

        if(edges[i].v1.name == NULL || edges[i].v2.name == NULL || edges[i].cost < 0 || edges[i].cost == NULL)
            flag=1;
        else if(strcmp(edges[i].v1.name,edges[i].v2.name) == 0)
            flag=1;

        // Stateler sayi olamaz ise aktif edilecek...
        /*else if((int)edges[i].v1.name[0]>122 ||(int)edges[i].v1.name[0]<65 || (int)edges[i].v2.name[0]>122 || (int)edges[i].v2.name[0]<65
                || (int)edges[i].v1.name[0] == 91 || (int)edges[i].v2.name[0] == 91
                || (int)edges[i].v1.name[0] == 92 || (int)edges[i].v2.name[0] == 92
                || (int)edges[i].v1.name[0] == 93 || (int)edges[i].v2.name[0] == 93
                || (int)edges[i].v1.name[0] == 94 || (int)edges[i].v2.name[0] == 94
                || (int)edges[i].v1.name[0] == 95 || (int)edges[i].v2.name[0] == 95
                || (int)edges[i].v1.name[0] == 96 || (int)edges[i].v2.name[0] == 96)
                flag=1;*/
        else if(edges[i].v1.name[1] != NULL || edges[i].v2.name[1] != NULL)
            flag=1;
        if(flag==1){
            printf("There is something missing in the file.");
            exit(1);
            break;
        }

    }
}
void getInput()
{
    FILE *input;
    char fname[10];
    printf("Please enter file name(with .txt): ");
    gets(fname);
    input=fopen(fname,"r+");
    if(input==NULL){
        printf("Dosya acilamadi");
        exit(1);
    }
fscanf(input,"%c",&startV.name[0]);
    while (!feof(input))
    {
        fscanf(input,"%s %s %d",edges[EdgesN].v1.name,edges[EdgesN].v2.name, &edges[EdgesN].cost);
        EdgesN++;//tum indexlerde gezmek icin
    }
    fclose(input);
}


int added(char name[])
{
    int i;
    for(i=0; i<unvisitedN; i++)
    {
        if(strcmp(name,unvisited[i].name) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void getUnvisitedNodes()
{
    int i;
    for(i=0; i<EdgesN; i++)
    {
        if(!added(edges[i].v1.name))
        {
            strcpy(unvisited[unvisitedN].name,edges[i].v1.name);
            unvisitedN++;
        }
        if(!added(edges[i].v2.name))
        {
            strcpy(unvisited[unvisitedN].name,edges[i].v2.name);
            unvisitedN++;
        }
    }
}

void initializeMinPathTable()
{
    int initialDist = 1;

    for(int i=0; i<EdgesN; i++)
    {
        initialDist = initialDist + edges[i].cost;
    }
    for(int i=0; i<hillN; i++)
    {
        strcpy(minPaths[i].thisnode.name,unvisited[i].name);
        strcpy(minPaths[i].Previous.name,"NULL");


        if(strcmp(minPaths[i].thisnode.name,startV.name) == 0)
        {
            minPaths[i].dist =0;
        }
        else
        {
            minPaths[i].dist = initialDist;
        }
    }

}

int printMinPathTable()
{

    printf("\n\n");
    string str;
    counter++;
    string temp;
    int temp1;
    char selected[10];

   // printf("\tdeneme:%d,%s",minPaths[1].dist,minPaths[1].Previous.name);

    printf(" %d    |",visitedN);
    for(int i=0; i<visitedN; i++)
    printf("%s",visited[i].name);
    for(int i=1; i<hillN; i++){
        if(strcmp(minPaths[i].Previous.name,"NULL")==0){
            printf("\t%4s","OO");
        }
        else{

            sprintf(str.name,"%d,",minPaths[i].dist);
            minPaths[i].dist2=minPaths[i].dist;
            strcat(str.name,minPaths[i].Previous.name);
            strcpy(minPaths[i].Previous.name2,minPaths[i].Previous.name);

            printf("\t%4s",str.name);

        }
    }
    for(int i=0; i<hillN-1; i++){
        for(int j=i+1; j<hillN; j++){
                if(minPaths[i].dist2>minPaths[j].dist2 && minPaths[j].dist2>0){
            temp1=minPaths[i].dist2;
            minPaths[i].dist2=minPaths[j].dist2;
            strcpy(minPaths[i].thisnode.name2,minPaths[j].thisnode.name2);
            strcpy(minPaths[i].Previous.name2,minPaths[j].Previous.name2);
            minPaths[j].dist2=temp1;
        }}
    }
   //printf("\nselected:%d,%s",minPaths[counter].dist2,minPaths[counter].Previous.name2);//en küçük maliyet
   sprintf(temp.name,"%d,",minPaths[counter].dist2);
   strcat(temp.name,minPaths[counter].Previous.name2);
   printf("deneme:%d",minPaths[counter].dist);
   printf("\nselected:%4s",temp.name);
    printf("\n");
    //system("Pause");

        printf("\n____________________________________________________________");
}
int edgeWeight(char s1[],char s2[])
{
    int i;
    for(i=0; i<EdgesN; i++)
    {
        if(strcmp(edges[i].v1.name,s1)==0 && strcmp(edges[i].v2.name,s2)==0)
        {
            return edges[i].cost;

        }
        if(strcmp(edges[i].v2.name,s1)==0 && strcmp(edges[i].v1.name,s2)==0)
        {
            return edges[i].cost;
        }
}
}
int unvisitedIndexInPath(char s[])
{
  for(int i=0; i<hillN; i++)
  {
      if(strcmp(s,minPaths[i].thisnode.name)== 0)
      {
          return i;
      }
  }
}
void dijkstra(char vName[])
{
    string vName_unvisited_neighbours[100];
    int N =0;
    //we add all vName neighbours to "vName_unvisited_neighbours[]" array..
    for(int i=0; i<EdgesN; i++)
    {
        if(strcmp(edges[i].v1.name, vName) == 0 )
        {
            strcpy(vName_unvisited_neighbours[N].name,edges[i].v2.name);
            N++;
        }
       else  if(strcmp(edges[i].v2.name, vName) == 0 )
        {
            strcpy(vName_unvisited_neighbours[N].name,edges[i].v1.name);
            N++;
        }
    }
    //now we remove vName neighbours that aren't in the unvisited array...
    string help[100];
    int x=0;
    bool isUnvisited;

    for(int i=0; i<N; i++)
    {
        isUnvisited = 0;
        for(int j=0; j<unvisitedN; j++)
        {
            if(strcmp(vName_unvisited_neighbours[i].name, unvisited[j].name) == 0)
            {
                isUnvisited = 1;
            }
        }
        if(isUnvisited == 1)
        {
            strcpy(help[x].name,vName_unvisited_neighbours[i].name);
            x++;
        }

    }
    N = x;
    for(int i=0; i<N; i++)
    {
        strcpy(vName_unvisited_neighbours[i].name ,help[i].name);
    }
    for(int i=0; i<N; i++)
    {
        //printf(" %s",vName_unvisited_neighbours[i].name);
    }
    int vNameDist;
    for(int i=0; i<hillN; i++)
    {
        if(strcmp(vName,minPaths[i].thisnode.name)==0)
        {
            vNameDist = minPaths[i].dist;
        }
    }
    int weight,distPlusWeight;
    for(int i=0; i<N; i++)
    {
        weight= edgeWeight(vName,vName_unvisited_neighbours[i].name);
        distPlusWeight = weight + vNameDist;
        for(int j=0; j<hillN; j++)
        {
            if(strcmp(vName_unvisited_neighbours[i].name,minPaths[j].thisnode.name)== 0)
            {
                if(minPaths[j].dist > distPlusWeight)
                {
                    minPaths[j].dist = distPlusWeight;
                    strcpy(minPaths[j].Previous.name,vName);



                }
            }
        }
    }
    strcpy(visited[visitedN].name, vName);
    //printf("select:%d,%s",minPaths[visitedN].dist,minPaths[visitedN].Previous.name);

    visitedN++;
    string help1[100];
    int x1=0;
    printMinPathTable();

    for(int i=0; i<unvisitedN; i++)
    {
        if(strcmp(vName,unvisited[i].name) != 0)
        {
            strcpy(help1[x1].name,unvisited[i].name);
            printf("%s",help1[x1].name);
            x1++;
        }
    }
    unvisitedN = x1;
    for(int i=0; i<unvisitedN; i++)
    {
        strcpy(unvisited[i].name,help1[i].name);
    }
    if(unvisitedN >0)
    {


        int index,i2,min;
        char minname;
        index = unvisitedIndexInPath(unvisited[0].name);
        min = minPaths[index].dist;
        for(int i=0; i<unvisitedN; i++)
        {
            i2 = unvisitedIndexInPath(unvisited[i].name);
            if(min > minPaths[i2].dist)
            {

                index = i2;
                min = minPaths[index].dist;
            }
        }
    dijkstra(minPaths[index].thisnode.name);
    }

}

void output()
{
    int i;
    FILE *out;
    out = fopen("out.txt","w");
    string str;
    int temp;
    fprintf(out,"Starting Node: %s",startV.name);

    for(i=0; i<hillN; i++)
    {
        fprintf(out,"\n%s %d %s",minPaths[i].thisnode.name, minPaths[i].dist,minPaths[i].Previous.name);

    }
    fclose(out);
   /* for(int i=0; i<hillN-1; i++){
        for(int j=i+1; j<hillN; j++){
                if(minPaths[i].dist>minPaths[j].dist){
            temp=minPaths[i].dist;
            minPaths[i].dist=minPaths[j].dist;
            strcpy(minPaths[i].thisnode.name,minPaths[j].thisnode.name);
            strcpy(minPaths[i].Previous.name,minPaths[j].Previous.name);
            minPaths[j].dist=temp;
        }}
    }
*/
}

int main ()
{
    getInput();
    controller();
    getUnvisitedNodes();
    hillN = unvisitedN;
    initializeMinPathTable();
    graph();
    dijkstra(startV.name);
    output();

    return 0;
}
