#ifndef BESTFIRSTSEARCH_H
#define BESTFIRSTSEARCH_H

#include <vector>
#include <queue>

class BestFirstSearch
{
    public:
        BestFirstSearch(char *args[]);

    private:
        struct Item
        {
            int weight, profit;
            double profitPerUnitWeight;

            Item (int w, int p)
            {
            	weight = w;
            	profit = p;
            	profitPerUnitWeight = (double) p / (double) w;
            }

            friend bool operator<(const Item& a, const Item& b)
            {
                return a.profitPerUnitWeight > b.profitPerUnitWeight;
            }
        };

        struct Solution
        {
            std::vector<bool> toInclude;
            int currentWeight, currentProfit, totalProfit, currentElement;

            Solution (std::vector<bool> inc, int cweight, int cprofit, int tprofit, int celement) 
            {
                toInclude = inc;
                currentWeight = cweight;
                currentProfit = cprofit;
                totalProfit = tprofit;
                currentElement = currentElement;
           
            }

            friend bool operator<(const Solution& a, const Solution& b)
            {
                return a.totalProfit < b.totalProfit;
            }

        };

        bool parseInputs(char *args[]);
        bool writeOutputs(char *args[]);
        int solveFractionalKnapsack(int, int, int);

        std::vector<Item> allItems;
        std::priority_queue<Solution> allSolutions;
        std::vector<bool> includes;
        int maxProfit, numNodes, numLeafNodes, bestToAdd, nodesInSolution, totalItems, maxCapacity;

};

#endif 