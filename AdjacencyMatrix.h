//
//  AdjacencyMatrix.h
//  Project 4
//
//  Created by Mai Pham on 5/26/18.
//  Copyright © 2018 Mai Pham. All rights reserved.
//

#ifndef AdjacencyMatrix_h
#define AdjacencyMatrix_h

//#include <vector>
//#include <stack>
//#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct vertices {
    int index;              // not neccessary
    string code;
    string name;
};

class AdjacencyMatrix   {
private:
    double **adjMatrix;
    vertices vertArray [20];
    int numVertex;
public:
    AdjacencyMatrix(string airportFile, string flightsFile){
        int i, j;
        double m;
        string c, f;
        
        ifstream myAirport;
        myAirport.open(airportFile);
        if(!myAirport.is_open())
            cout << "No text file found. " << endl;
        while (myAirport >> i)   {
            myAirport >> c;
            getline(myAirport, f);
            f = f.substr(4, f.length());
            //cout << i << "\n" << c<< "\n" << f << endl;
            vertArray[i].index = i;
            vertArray[i].code = c;
            vertArray[i].name = f;
            //cout << vertArray[i].name << endl;
        }
        
        numVertex = i+1;
        //cout << numVertex << endl;
        adjMatrix = new double*[numVertex];
        for (int i = 0; i < numVertex; i++) {
            adjMatrix[i] = new double[numVertex];
            for (int j = 0; j < numVertex; j++)
                adjMatrix[i][j] = false;
        }
        
        ifstream myFlights;
        myFlights.open(flightsFile);
        if(!myFlights.is_open())
            cout << "No text file found. " << endl;
        while (!myFlights.eof())   {
            myFlights >> i >> j >> m;
            //cout << i << "\n" << j << "\n" << m << endl;
            addEdge(i, j, m);
        }
    }
    
    AdjacencyMatrix(int v) {
        numVertex = v;
        adjMatrix = new double*[numVertex];
        for (int i = 0; i <= numVertex; i++) {
            adjMatrix[i] = new double[numVertex];
            for (int j = 0; j <= numVertex; j++)
                adjMatrix[i][j] = false;
        }
    }
    
    ~AdjacencyMatrix()  {
        for (int i = 0; i < numVertex; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
    }
    
    void addEdge(int i, int j, double w) {
        if (i == j)
            return;
        if (i >= 0 && i < numVertex && j >= 0 && j < numVertex)
            adjMatrix[i][j] = w;
    }
    
    void removeEdge(int i, int j) {
        if (i == j)
            return;
        if (i >= 0 && i < numVertex && j >=- 0 && j < numVertex)
            adjMatrix[i][j] = false;
    }
    
    int returnIndex(string code)    {
        int index = -1;                         // return -1 if not found
        for (int i = 0; i < numVertex; i++) {
            if (vertArray[i].code == code)
                index = i;
        }
        return index;
    }
    
    void addFlight(string source, string dest, double cost) {
        int s, d;
        s = returnIndex(source);
        d = returnIndex(dest);
        if (s != -1 && d != -1)
            addEdge(s, d, cost);
        else
            return;
    }
    
    void deleteFlight(string source, string dest) {
        int s, d;
        s = returnIndex(source);
        d = returnIndex(dest);
        if (s != -1 && d != -1)
            removeEdge(s, d);
        else
            return;
    }
    
    void printMatric()  {
        for(int i = 0; i < numVertex; i++)    {
            for(int j = 0; j < numVertex; j++)
                cout << adjMatrix[i][j] << "\t";
            cout<<endl;
        }
    }
    
    void printAllFlightInfor()    {
        for(int i = 0; i < numVertex; i++)   {
            cout << vertArray[i].code << " -->";
            for(int j = 0; j < numVertex; j++)
                if (adjMatrix[i][j])
                    cout << "\t" << vertArray[j].code << "($" << adjMatrix[i][j] << ")";
            cout<<endl;
        }
    }
    
    void print1Flight(string source)    {
        int src = returnIndex(source);
        if (src != -1)  {
            cout << vertArray[src].code << " -->";
            for(int j = 0; j < numVertex; j++)
                if (adjMatrix[src][j])
                    cout << "\t" << vertArray[j].code << "($" << adjMatrix[src][j] << ")";
            cout<<endl;
            cout << vertArray[src].code << " <--";
            for(int j = 0; j < numVertex; j++)
                if (adjMatrix[j][src])
                    cout << "\t" << vertArray[j].code << "($" << adjMatrix[j][src] << ")";
            cout<<endl;
        }
        else
            cout << "Found No Matching Airport" << endl;
    }
    
    double cheapestFlight(string source, string dest) {
        int src = returnIndex(source);
        int des = returnIndex(dest);
        int dist[numVertex];
        double cost[numVertex];
        bool sptSet[numVertex];
        int parent[numVertex];
        
        for (int i = 0; i < numVertex; i++) {
            parent[i] = -1;
            cost[i] = INT_MAX;
            sptSet[i] = false;
            dist[i] = 0;
        }
        
        cost[src] = 0;
        for (int count = 0; count < numVertex; count++) {
            int min = INT_MAX, min_index;
            for (int v = 0; v < numVertex; v++)
                if (sptSet[v] == false && cost[v] <= min)   {
                    min = cost[v];
                    min_index = v;
                }
            int u = min_index;
            sptSet[u] = true;
            for (int v = 0; v < numVertex; v++)
                if (!sptSet[v] && adjMatrix[u][v] && cost[u] + adjMatrix[u][v] < cost[v])   {
                    parent[v] = u;
                    cost[v] = cost[u] + adjMatrix[u][v];
                    dist[v] = dist[u] + 1;
                }
        }
        
        //for (int i = 0; i < numVertex; i++)
            //cout << parent[i] << endl;
        cout << "Cheapest Flight Route:" << endl;
        cout << "  " << vertArray[src].code;
        printPath(parent, des);
        cout << "\n\tTotal Stop = " << dist[des];
        cout << "\n\tTotal Cost = $" << cost[des] << endl;
        /*
        for (int i = 0; i < numVertex; i++)     {
            cout << src << " -> " << i << "\t\t" << dist[i] << "\t\t" << src << "  ";
            printPath(parent, i);
            cout << endl;
        }*/
        return cost[des];
    }
    
    void printPath(int parent[], int j) {
        if (parent[j] == - 1)
            return;
        printPath(parent, parent[j]);
        cout << " --> " << vertArray[j].code;
    }
    
    double shortestFlight(string source, string dest) {
        int src = returnIndex(source);
        int des = returnIndex(dest);
        double cost[numVertex];
        int dist[numVertex];
        bool sptSet[numVertex];
        int parent[numVertex];
        
        for (int i = 0; i < numVertex; i++) {
            parent[i] = -1;
            dist[i] = INT_MAX;
            sptSet[i] = false;
            cost[i] = 0;
        }
        
        dist[src] = 0;
        for (int count = 0; count < numVertex; count++) {
            int min = INT_MAX, min_index;
            for (int v = 0; v < numVertex; v++)
                if (sptSet[v] == false && dist[v] <= min)   {
                    min = dist[v];
                    min_index = v;
                }
            int u = min_index;
            sptSet[u] = true;
            for (int v = 0; v < numVertex; v++)
                if (!sptSet[v] && adjMatrix[u][v] && dist[u] < dist[v])   {
                    parent[v] = u;
                    dist[v] = dist[u] + 1;
                    cost[v] = cost[u] + adjMatrix[u][v];
                }
        }
        
        //for (int i = 0; i < numVertex; i++)
        //cout << parent[i] << endl;
        cout << "Shortest Flight Route:" << endl;
        cout << "  " << vertArray[src].code;
        printPath(parent, des);
        cout << "\n\tTotal Stop = " << dist[des];
        cout << "\n\tTotal Cost = $" << cost[des] << endl;
        /*
         for (int i = 0; i < numVertex; i++)     {
         cout << src << " -> " << i << "\t\t" << dist[i] << "\t\t" << src << "  ";
         printPath(parent, i);
         cout << endl;
         }*/
        return dist[des];
    }
    
    void outputFlight(){
        ofstream outFile("P4FlightsRev1.txt");
        for(int i = 0; i < numVertex; i++)   {
            for(int j = 0; j < numVertex; j++)
                if (adjMatrix[i][j])
                    outFile << i << "\t" << j << "\t" << fixed << setprecision(2) << adjMatrix[i][j] << endl;
        }
    }
    
    void outputAirports(){
        ofstream outFile("P4AirportRev1.txt");
        for(int i = 0; i < numVertex; i++)
            outFile << i << "\t"<< vertArray[i].code << "\t\t" << vertArray[i].name << endl;
    }
    
    void addNewAirport(string code, string name){
        //cout << "current numVertext size " << numVertex << endl;
        vertArray[numVertex].code = code;
        vertArray[numVertex].name = name;
        numVertex++;
        //cout << "current numVertext size " << numVertex << endl;
        double **temp = new double*[numVertex];
        for (int i = 0; i < numVertex; i++) {
            temp[i] = new double[numVertex];
            for (int j = 0; j < numVertex; j++)    {
                if (j == numVertex-1 || i == numVertex-1)
                    temp[i][j] = false;
                else
                    temp[i][j] = adjMatrix[i][j];
                //cout << "temp " << i << j << temp[i][j] << " ";
            }
        }
        delete [] adjMatrix;                    //destroy everything in here
        adjMatrix = temp;                       //reset with new size
    }
};

#endif /* AdjacencyMatrix_h */

