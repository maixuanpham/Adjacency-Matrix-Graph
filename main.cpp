//
//  main.cpp
//  Project 4
//
//  Created by Mai Pham on 5/26/18.
//  Copyright © 2018 Mai Pham. All rights reserved.
//

#include "AdjacencyMatrix.h"
#include <iostream>
using namespace std;

int main() {
    AdjacencyMatrix graph("P4Airports.txt", "P4Flights.txt");
    /*
    graph.printMatric();
    cout << endl;
    graph.printAllFlightInfor();
    cout << endl;
    graph.print1Flight("JFK");
    cout << endl;
    double cost;
    
    cost = graph.cheapestFlight("LAX","JFK");
    cost += graph.cheapestFlight("JFK", "LAX");
    cout << "Round Trip Total Cost = $" << cost << endl;
    cout << endl;
    graph.shortestFlight("JFK", "LAX");
    cout << endl;
    graph.outputFlight();
    cout << endl;
    graph.outputAirports();
    cout << endl;
    
    graph.addFlight("DFW", "JFK", 200.00);
    graph.deleteFlight("LAX", "SEA");
    graph.printAllFlightInfor();
    
    graph.addNewAirport("MAI", "San Gabriel");
    cout << endl;
    graph.outputAirports();
    cout << endl;
    graph.printAllFlightInfor();
    cout << endl;
    graph.print1Flight("JFK");
    cout << endl;
    graph.printMatric();
    cout << endl;
    */
    
    char option;
    
    cout << "Airport Flights Selection\n";
    cout << "1. Display airport information\n";
    cout << "2. Find a cheapest flight from one airport to another airport\n";
    cout << "3. Add a flight from one airport to another airport\n";
    cout << "4. Delete a flight from one airport to another airport\n";
    cout << "5. Find a cheapest roundtrip from one airport to another airport\n";
    cout << "6. Find a flight with fewest stops from one airport to another airport\n";
    cout << "7. Find all flight from one airport to another airport\n";
    cout << "8. Find an order to visit all airports starting from an airport\n";
    cout << "9. Add a new airport\n";
    cout << "Q. Exit\n";
    cout << "Select an option ==> ";
    cin >> option;
    cout << endl;
    while (option != 'Q')  {
        string source, destination;
        double cost;
        switch (option) {
            case '0':
                cout << "Printing all airport information..." << endl;
                graph.printAllFlightInfor();
                cout << endl;
                break;
            case '1':
                cout << "Please enter the airport code = ";
                cin >> source;
                cout << source << " flight information..." << endl;
                graph.print1Flight(source);
                cout << endl;
                break;
            case '2':
                cout << "Please enter the departure airport code = ";
                cin >> source;
                cout << "Please enter the arrival airport code = ";
                cin >> destination;
                graph.cheapestFlight(source, destination);
                cout << endl;
                break;
            case '3':
                cout << "Please enter the departure airport code = ";
                cin >> source;
                cout << "Please enter the arrival airport code = ";
                cin >> destination;
                cout << "Please enter the total cost = ";
                cin >> cost;
                graph.addFlight(source, destination, cost);
                cout << endl;
                break;
            case '4':
                cout << "Please enter the departure airport code = ";
                cin >> source;
                cout << "Please enter the arrival airport code = ";
                cin >> destination;
                graph.deleteFlight(source, destination);
                cout << endl;
                break;
            case '5':
                cout << "Please enter the departure airport code = ";
                cin >> source;
                cout << "Please enter the arrival airport code = ";
                cin >> destination;
                double cost;
                cost = graph.cheapestFlight(source, destination);
                cost += graph.cheapestFlight(destination, source);
                cout << "Round Trip Total Cost = $" << cost << endl << endl;
                break;
            case '6':
                cout << "Please enter the departure airport code = ";
                cin >> source;
                cout << "Please enter the arrival airport code = ";
                cin >> destination;
                graph.shortestFlight(source, destination);
                cout << endl;
                break;
            case '7':
                cout << "Not Available" << endl;
                break;
            case '8':
                cout << "Not Available" << endl;
                break;
            case '9':
                char answer;
                string name, code;
                cout << "Please enter the airport code = ";
                cin >> code;
                cout << "Please enter the airport name = ";
                cin.ignore();
                getline(cin, name);
                graph.addNewAirport(code, name);
                cout << "\nWould you like to add flight(s) for the new airport (Y or N)? ";
                cin >> answer;
                while (answer == 'Y')  {
                    cout << "Please enter the departure airport code = ";
                    cin >> source;
                    cout << "Please enter the arrival airport code = ";
                    cin >> destination;
                    cout << "Please enter the total cost = ";
                    cin >> cost;
                    graph.addFlight(source, destination, cost);
                    cout << "\nAdd more flight(s) (Y or N)? ";
                    cin >> answer;
                }
                cout << endl;
                break;
        }
        cout << "Airport Flights Selection\n";
        cout << "1. Display airport information\n";
        cout << "2. Find a cheapest flight from one airport to another airport\n";
        cout << "3. Add a flight from one airport to another airport\n";
        cout << "4. Delete a flight from one airport to another airport\n";
        cout << "5. Find a cheapest roundtrip from one airport to another airport\n";
        cout << "6. Find a flight with fewest stops from one airport to another airport\n";
        cout << "7. Find all flight from one airport to another airport\n";
        cout << "8. Find an order to visit all airports starting from an airport\n";
        cout << "9. Add a new airport\n";
        cout << "Q. Exit\n";
        cout << "Select an option ==> ";
        cin >> option;
        cout << endl;
    }
    graph.outputAirports();
    graph.outputFlight();
    
    return 0;
}
