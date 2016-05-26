#include <iostream>
#include <cstdlib>
#include <stdio.h>
#define MAX_COLOR 10
#define MAX_VERTEX 10
#define FILE_NAME "data.txt"
using namespace std;

struct VERTEX{
    int step;
    int color;
    int denyColor[MAX_COLOR];
};

struct MAP{
    int totalVertex;
    VERTEX vertex[MAX_VERTEX];
    int edge[MAX_VERTEX][MAX_VERTEX];
};

void readFile(MAP &map);
//Check symmetry of input
int isSymmetry(int matrix[MAX_VERTEX][MAX_VERTEX],int N);
//calculate step of vertex
int calculateStep(int i,MAP map);
//Initialize all vertex of graph
void initVertices(MAP &map);
//check coloring. if not coloring return 1
int isNotColoring(int vertex,MAP map);
//find vertex not coloring is max step
int findVertex(MAP map);
//Find color don't deny
int findColor(int vertex,MAP map);
int coloring(int vertex,MAP &map);
void descStepEqualZero(int vertex,MAP &map);
void descStep(int vertex,MAP &map);
int isLinked(int vertex1,int vertex2,MAP &map);
void denyColoring(int vertex, int color,MAP &map);
void colorAllVertex(MAP &map);
void display(MAP map);

int main()
{
    MAP map;
    readFile(map);
    if(isSymmetry(map.edge,map.totalVertex)==1){
        initVertices(map);
        colorAllVertex(map);
        display(map);
    }
    return 0;
}
void readFile(MAP &map){
    FILE *f;
    f = fopen(FILE_NAME,"rt");
    if(f==NULL){
        printf("Can not open file %s",FILE_NAME);
        exit(1);
    }
    fscanf(f,"%d\n",&map.totalVertex);
    for(int i=0;i<map.totalVertex;i++){
        for(int j=0;j<map.totalVertex;j++){
            fscanf(f,"%d",&map.edge[i][j]);
        }
    }
    fclose(f);
}

int isSymmetry(int matrix[MAX_VERTEX][MAX_VERTEX],int N){
    for(int i=0;i<N;i++){
        for(int j=0;j<N/2;j++)
            if(matrix[i][j] !=  matrix[j][i])
                return 0;
    }
    return 1;
}

int calculateStep(int i,MAP map){
    int step=0;
    for(int j=0;j<map.totalVertex;j++){
        step += map.edge[i][j];
    }
    return step;
}

void initVertices(MAP &map){
    for(int i=0;i<map.totalVertex;i++){
        map.vertex[i].step = calculateStep(i,map);
        map.vertex[i].color=-1;
        for(int k = 0;k<MAX_COLOR;k++){
            map.vertex[i].denyColor[k] = 0;
        }
    }
}

//check coloring. if not coloring return 1
int isNotColoring(int vertex,MAP map){
    return (map.vertex[vertex].color > -1)?0:1;
}

//find vertex not coloring is max step
int findVertex(MAP map){
    int selectVertex = -1;
    int maxStep = 0;
    for(int i=0;i<map.totalVertex;i++){
        if(map.vertex[i].color==-1 && map.vertex[i].step>maxStep){
            selectVertex = i;
            maxStep = map.vertex[i].step;
        }
    }
    return selectVertex;
}

int findColor(int vertex,MAP map){
     for(int i=0;i<MAX_COLOR;i++){
            if(map.vertex[vertex].denyColor[i]==0)
            return i;
     }
}

int coloring(int vertex,MAP &map){
    int color =  findColor(vertex,map);
    map.vertex[vertex].color = color;
    return color;
}

void descStepEqualZero(int vertex,MAP &map){
    map.vertex[vertex].step=0;
}

void descStep(int vertex,MAP &map){
    map.vertex[vertex].step--;
}

int isLinked(int vertex1,int vertex2,MAP &map){
    if(map.edge[vertex1][vertex2]==1 ||map.edge[vertex2][vertex1]==1)
        return 1;
    return 0;
}

void denyColoring(int vertex, int color,MAP &map){
    map.vertex[vertex].denyColor[color] = 1;
}

void colorAllVertex(MAP &map){
    int N = map.totalVertex;
    int selectColor;
    int selectVertex = findVertex(map);
    while(selectVertex>=0){
        selectColor = coloring(selectVertex,map);
        descStepEqualZero(selectVertex,map);
        for(int i=0;i<N;i++){
            if(isLinked(i,selectVertex,map)){
                descStep(i,map);
                denyColoring(i,selectColor,map);
            }
        }
        selectVertex = findVertex(map);
    }
    for(int i =0;i< N;i++){
        if(isNotColoring(i,map))
            coloring(i,map);
    }
}

void display(MAP map){
    printf("Total vertex: %d\n",map.totalVertex);
    for(int i=0;i<map.totalVertex;i++){
        printf("Vertex %d --> color: %d\n",i,map.vertex[i].color+1);
    }
}
