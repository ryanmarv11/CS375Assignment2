#include "BestFirstSearch.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

BestFirstSearch::BestFirstSearch(char *args[]) 
{
    maxProfit = 0;
    numNodes = 0;
    numLeafNodes = 0;
    bestToAdd = 0;
    nodesInSolution = 0;
    totalItems = 0;
    parseInputs(args);
    allSolutions.push({includes, 0, 0, solveFractionalKnapsack(0, 0, 0), 0});

    while(!allSolutions.empty())
    {
        Solution current = allSolutions.top();
        allSolutions.pop();

        numNodes++;

        if(current.currentElement < totalItems)
        {
            if(current.totalProfit >= maxProfit && current.currentWeight < maxCapacity)
            {
                vector<bool> stayTrue = current.toInclude, stayFalse = current.toInclude;

                stayTrue.push_back(true);
                stayFalse.push_back(false);

                Item originalItem = allItems.at(current.currentElement);
                int currentAndOriginalWeight = current.currentWeight + originalItem.weight;
                int currentAndOriginalProfit = current.currentProfit + originalItem.profit;

                int doAddItem = solveFractionalKnapsack(current.currentElement+1, currentAndOriginalWeight, currentAndOriginalProfit);
                int dontAddItem = solveFractionalKnapsack(current.currentElement+1, current.currentWeight, current.currentProfit);

                if(doAddItem >= maxProfit)
                {
                    allSolutions.push({stayTrue, currentAndOriginalWeight, currentAndOriginalProfit, doAddItem, current.currentElement+1});
                    if(currentAndOriginalProfit > maxProfit && currentAndOriginalWeight <= maxCapacity)
                        maxProfit = currentAndOriginalProfit;
                    else if(currentAndOriginalWeight > maxCapacity)
                        bestToAdd++;
                }

                allSolutions.push({stayFalse, current.currentWeight, current.currentProfit, dontAddItem, current.currentElement+1});
            }
            else
                numLeafNodes++;
        }
        else
            numLeafNodes++;

        if(current.currentProfit == maxProfit)
            includes = current.toInclude;
    }
    writeOutputs(args);
}

bool BestFirstSearch::writeOutputs(char *args[])
{
    ofstream outputStream;

    outputStream.open(args[2], ios::out);
    if(!outputStream.is_open())
    {
        cerr << "No output file found with name: " << args[2] << endl;
        return false;
    }

    for(int i = 0; i < totalItems; i++)
    {
        if(includes.at(i))
            nodesInSolution++;
    }

    outputStream << totalItems << "," << maxProfit << "," << nodesInSolution << "\n";
    outputStream << numNodes << "," << numLeafNodes << "\n";
    for(int i = 0; i < totalItems; i++)
    {
        if(includes.at(i))
        {
            outputStream << allItems.at(i).weight << "," << allItems.at(i).profit << "\n";
        }
    }

    outputStream.close();
    return true;
}

bool BestFirstSearch::parseInputs(char *args[])
{
    // Tries to open a file with the name of (input file) args[1]
    ifstream input;
    input.open(args[1], ios::in);
    if(!input.is_open())
    {
        cerr << "No input file found with name: " << args[1] << endl;
        return false;
    }

    string line;
    bool isFirstLine = true;
    while(getline(input, line)) 
    {
        string profit;
        vector<int> profits;
        stringstream data(line);

        while(getline(data, profit, ',')) //converts it from string
            profits.push_back(stoi(profit));
        
        if(!isFirstLine)
            allItems.push_back({profits.at(0), profits.at(1)});
        else
        {
            totalItems = profits.at(0);
            maxCapacity = profits.at(1);
            isFirstLine = !isFirstLine;
        }
    }
    input.close();

    sort(allItems.begin(), allItems.end());
    return true;
}

int BestFirstSearch::solveFractionalKnapsack(int i, int weight, int profit)
{
    while(weight != maxCapacity && i < totalItems)
    {
        if((weight + allItems.at(i).weight) < maxCapacity)
        {
            weight += allItems.at(i).weight;
            profit += allItems.at(i).profit;
        }
        else
        {
            double remainder =(maxCapacity - weight);
            weight = maxCapacity;
            profit +=(int)(allItems.at(i).profitPerUnitWeight * remainder);
        }

        i++;
    }

    return profit;
}