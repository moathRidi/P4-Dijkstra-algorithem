/*
 *
 * NAME: MOATH ABU RIDI
 * ID: 1201507
 *
 */



#include <stdio.h>
#include <process.h>
#include <string.h>
#include <stdlib.h>
#define INFINITY 999

typedef struct city{
    char cityName_from[40];
    char destination[40];
    int distance;
    int booked;
    int reached;
}city;
int static size=0;
int static row=0;
int static column=0;
int static flag=0;
char static lastRead[40];


void ReadCorse(city[][size]); // Reading the file
int NumberOfVertices();//find the number of vertices
void loadToMatrix(city [][size],char [40],char [40],int  );//fill the matrix from the file
void printMatrix(city [][size]);//print the matrix to see if it load correctly
int findStartpoint(city [][size],char [40]);//find the index of the source city in the matrix
int findendpoint(city cityMatrix[][size],char to[40]);//find the index of the source city in the matrix

void Dijkstra(city [][size],char [40],char [40],int ,int,FILE*);//finding the shortest bath by greedy algo to each city


int main() {
    int startIndex=0;
    size=NumberOfVertices();
    city cityMatrix[size][size];
    //initialize the first content of the array
    for (int z = 0; z < size; z++) {
        for (int x = 0; x < size; x++) {
            cityMatrix[z][x].distance=0;
            cityMatrix[z][x].reached=0;
            cityMatrix[z][x].booked=0;
        }

    }
    int choice;
    char sourse[40];
    char destination[40];
    FILE * out;
    out = fopen("shortest_path.txt", "w");//open the file for reading

    char ch;
    //print the user list to choose from
    do {

        printf("\n1. Load cities:\n"
               " 2. Enter source city:\n"
               " 3. Enter destination city: \n"
               " 4. Exit:\n"
               "Enter your choice:  ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                ReadCorse(cityMatrix);

                break;
            case 2:
                scanf("%c",&ch);
                gets(sourse);
                startIndex= findStartpoint(cityMatrix,sourse);

           //     printMatrix(cityMatrix);

                break;
            case 3:
                scanf("%c",&ch);
                gets(destination);
                int end=findendpoint(cityMatrix,destination);
                Dijkstra(cityMatrix,sourse,destination,startIndex,end,out);

                break;
            case 4:
                        free(cityMatrix);//clear the 2D array from the memory

                exit(1);
                break;

            default:
                printf("Please try again");
                break;
        }

    } while (choice != 5);




    return 0;
}


//read courses file.
void ReadCorse(city citymatrix[][size]){

    FILE * fin;
    fin = fopen("cities.txt", "r");//open the file for reading
    if (fin == NULL)
    {
        printf( "Error! File cannot be read");
        exit (1);
    }
    char line[300];
    char * sr;
    char* ret;
    printf("  City Name (from)          City Destination           Distance\n");
    while (fgets(line, 300, fin)) {//read until finishing the file
        char cityName_from[40];
        int distance;
        char city_Distnation[40];

        line[strcspn(line, "\n")] = 0;

        sr = strtok(line, " ");
        strcpy(cityName_from, sr);

        if (cityName_from[0] == ' ') {
            for (int e = 0; e < strlen(cityName_from); e++) {
                cityName_from[e] = cityName_from[e + 1];
            }
        }

        sr = strtok(NULL, " ");
        strcpy(city_Distnation, sr);
        if (city_Distnation[0] == ' ') {//cut and remove the spase
            for (int e = 0; e < strlen(city_Distnation); e++) {
                city_Distnation[e] = city_Distnation[e + 1];
            }
        }
        sr = strtok(NULL, " ");
        distance = atoi(sr);

        printf("*------------------------------------------------------------------------------------------------------*\n");
        printf("  %-20s     |   %-15s   |   %5dkm  \n",cityName_from,city_Distnation,distance);
        if(flag==0){
            strcpy(lastRead,cityName_from);
            flag=1;
        }

        loadToMatrix(citymatrix,cityName_from,city_Distnation,distance);//loading the data to the matrix
    }


    fclose(fin);

}

//finding the number of vertices
int NumberOfVertices() {
    FILE *fin;
    fin = fopen("cities.txt", "r");
    if (fin == NULL) {
        printf("Error! File cannot be read");
        exit(1);
    }
    char line[100];
    int counter = 0;
    while (fgets(line, 300, fin)) {//to the finish of the file

        line[strcspn(line, "\n")] = 0;
        counter++;
    }
    return counter;
}

//fill the matrix with the cities from file
void loadToMatrix(city cityMatrix[][size],char from[40],char to[40],int distance ){
    //if the from_city still the same fill the destination to hte same row ,else increment the row
    if(strcmp(lastRead,from)!=0) {
        row++;
        column=0;
    }
    cityMatrix[row][column].distance=distance;
    strcpy(cityMatrix[row][column].cityName_from,from);
    strcpy(cityMatrix[row][column].destination,to);
    cityMatrix[row][column].booked=1;
    column++;
    strcpy(lastRead,from);//change the last road city
}


//printing the matrix after filling
void printMatrix(city cityMatrix[][size]){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if(cityMatrix[i][j].booked==1){
                printf(" %s       %s       %d \n",cityMatrix[i][j].cityName_from,cityMatrix[i][j].destination,cityMatrix[i][j].distance);
            }

        }

    }
}
//find the shortest path from the source to each city
void Dijkstra(city cityMatrix[][size], char from[40], char to[40], int start_index, int end, FILE *out) {
//initializing variables
    int MAX=size;
    int n=size;
    int cost[MAX][MAX], distance[MAX], pred[MAX];
    int visited[MAX], count, mindistance, nextnode, i, j;

    // Creating cost matrix that has the distances
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++) {
            if (cityMatrix[i][j].distance == 0) {//if the distance is zero the n store inf
                cost[i][j] = INFINITY;
            } else {
                cost[i][j] = cityMatrix[i][j].distance;//else set the distance in that index
            }
        }
        }
    //this for loop will set the arrays of the shortest distance, and the path array
    for (i = 0; i < n; i++) {
        distance[i] = cost[start_index][i];
        pred[i] = start_index;
        visited[i] =-1;
    }

    //distance[start_index] = 0;
    visited[start_index] = 1;
    count = 1;


    //here we find the shortest distance from source to all vertices.
    while (count < n - 1) {
        mindistance = INFINITY;
//here we find the shortest path , and not visited .
        for (i = 0; i < n; i++)
            if (distance[i] < mindistance && !visited[i]) {
                mindistance = distance[i];
                nextnode = i;
            }

        visited[nextnode] = 1;

        // update the shortest distance array
        for (i = 0; i < n; i++)
                if (!visited[i]&&mindistance + cost[nextnode][i] < distance[i]&&mindistance!=INFINITY) {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }


    // Printing the distance
    if(end != start_index){
        printf("\nDistance from  node %s to node %s = %d",from,to  ,distance[end]);
         fprintf( out, "\nDistance from  node %d to node %d = %d",from,to  ,distance[end]);
        printf("\nPath=%s",cityMatrix[pred[end]][end].cityName_from);
        fprintf(out,"\nPath=%s",cityMatrix[pred[end]][end].cityName_from);
        j=end;
        do
        {
            j=pred[j];
            printf(" - >  %s",cityMatrix[pred[j]][j].cityName_from);

        }while(pred[j]!=start_index);
    }
}


//finding the index of the source
int findStartpoint(city cityMatrix[size][size],char from[40]){
    for (int i = 0; i < size; i++) {//loop to get to the all indexes at the matrix
        for (int j = 0; j < size; j++) {
            if(strcmp(cityMatrix[i][j].cityName_from,from)==0)
                return i;
        }


    }
}

//finding the index of the distenation

int findendpoint(city cityMatrix[][size],char to[40]){
    for (int i = 0; i < size; i++) {//loop to get to the all indexes at the matrix
        for (int j = 0; j < size; j++) {
            if(strcmp(cityMatrix[i][j].destination,to)==0)
                return j;
        }


    }
}