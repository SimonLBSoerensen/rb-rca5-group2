#ifndef QLEARNING_H
#define QLEARNING_H
#include <vector>
#include <random>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <locale>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "json.h"

#define STATE_NAME_INDEX 0
#define STATE_X_INDEX 1
#define STATE_Y_INDEX 2
#define STATE_CONN_INDEX 3
#define STATE_MEAN_INDEX 4
#define STATE_STDDIV_INDEX 5

class QLearning
{
public:
    struct state
    {
        state() {
            name = "No name";
            actionStates = std::vector<state*>();
            qValues = std::vector<float>();
        }
        ~state(){}

        std::string name;
        std::vector<state*> actionStates;
        std::vector<float> qValues;

        float x, y;

        float stddev;
        float mean;
    };

    QLearning(std::string filename, std::string startState, float discount_rate, float stepSize, float greedy, float qInitValue, bool debug=false);

    state* getNewState();
    void giveReward(float r);
    void print_stats();

    void simulateActionReward();
    void wirteJSON(std::string filename);
    float runNormal_distribution(float neam, float stddev);
protected:
    std::default_random_engine generator;
    std::unordered_map<std::string, int> nameToIndexMap;
    std::vector<std::vector<std::vector<std::string>>> stringFromFile(std::string filename);

    std::vector<state> states;


    //[0,0,0,0,0,0]; std::vector<std::vector<state>> states;


    float getMaxQ(state* newState);
    float getReward(state* newState);
    int policy();//Returnerer det nye state index som også er den action man tager

    void stripWhitespace(std::string& s);

    int getMaxactionIndex();
    int getRandomactionIndex();
    bool debug;
    float discount_rate;
    float stepSize;
    float greedy;
    state* currentState;
    int nextStateActionIndex;
};

#endif // QLEARNING_H
