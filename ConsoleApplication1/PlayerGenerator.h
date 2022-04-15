#pragma once
#include <unordered_map>
#include <string_view>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdbool.h>
#include <stdlib.h>
#include <vector>

enum Position
{
    FullFoward, LeftFoward, RightForward, CenterHalf, LeftHalf, RightHalf
};

/*struct PreviousTeam
{
    std::string name;
    int games;
    int goals;
};*/

struct Player
{
public:
    Player() = default;
    Player(std::string n, int r, int gam, int gol, int a)
    {
        name = n;
        rating = r;
        games = 0;
        goals = 0;
        overallGames = gam;
        overallGoals = gol;
        age = a;
    }
    
    int games;
    int goals;
    std::string name;
    int age;
    int rating;
    int overallGoals;
    int overallGames;
    //std::string team;
    //int age;
    //std::vector<PreviousTeam> history;
};

struct PlayerName
{
    PlayerName(std::string n, bool u = false) : name(n), used(u) {}
    std::string name;
    bool used;
};

class PlayerGenerator
{
public:
    PlayerGenerator() = default;
    ~PlayerGenerator() = default;

    bool init(std::string file)
    {
        srand(time(0));
        std::string line;
        std::ifstream players(file);
        bool correctFile = false;
        if(players.is_open())
        {
            while(std::getline(players, line))
            {
                if(!correctFile)
                {
                    if(line.compare("PLAYERS"))
                    {
                        std::cout << "PLAYER-GENERATOR:" << " File: " << file << " is a team file" << std::endl;
                        correctFile = true;
                    }
                    else
                    {
                        std::cout << "TEAM-GENERATOR:" << " File: " << file << " is not a team file" << std::endl;
                        return false;
                    }
                }
                else
                {
                    std::stringstream ss(line);
                    std::string name;
                    int used;

                    ss >> name >> used;
                    //std::cout << line << " ---- " << name << " " << used << std::endl;
                    playerNames.push_back(PlayerName(line, used));
                }
            }
            players.close();
            
            return true;
        }
        else
            return false;
    }

    std::string GetPlayerName()
    {
        return FindName();
    }

private:
    std::string FindName()
    {
        int i = 0;
        while(1)
        {
            int value = rand() % playerNames.size();
            if(!playerNames[value].used)
            {
                playerNames[value].used = true;
                return playerNames[value].name;
            }
            i++;
            if(i >= playerNames.size())
            {
                std::cout << "TEAM GENERATOR: Error, Incorrect iteration of string" << std::endl;
                return NULL;
            }
        }
    }
    
    std::vector<PlayerName> playerNames;
};