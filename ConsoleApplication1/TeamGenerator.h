#pragma once
#include <unordered_map>
#include <string_view>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdbool.h>
#include <stdlib.h> 

#include "PlayerGenerator.h"

class Team
{
public:
    //Default Constructor creates a new team overall
    Team() = default;
    Team(std::string n) : name(n) {}
    ~Team() = default;

    void SetName(std::string n)
    {
        name = n;
    }

    std::string GetName()
    {
        return name;
    }

    std::string PrintPlayers()
    {
        std::string value;
        for(auto p : players)
        {
            value+= p->name + " Rating: " + std::to_string(p->rating) + " Games:" + std::to_string(p->games) + " Goals:" + std::to_string(p->goals) + "\n";
        }
        return value;
    }

    int TeamValue()
    {
        int total = 0;
        int i = 0;
        for(auto p : players)
        {
            total += p->rating;
            i++;
        }

        int avg = total/i;
        if(avg >= 80 && avg < 85)
            return 6;
        else if (avg >= 85)
            return 7;
        else
            return 5;
    }
    std::vector<std::shared_ptr<Player>> players;
private:
    //Maybe a pointer, not too sure just yet
    std::string name;
    
    /*std::vector<CompetitionString> currentCompetitions;
    std::vector<CompetitionHistory> pastCompetitions;*/
};

struct TeamNames
{
    TeamNames(std::string n) : name(n), used(false) {}
    std::string name;
    bool used;
};
class TeamGenerator
{
public:
    TeamGenerator() = default;
    ~TeamGenerator() = default;
    bool Init(std::string file)
    {
        srand(time(0));
        std::string line;
        std::ifstream teams(file);
        bool correctFile = false;
        if(teams.is_open())
        {
            while(std::getline(teams, line))
            {
                if(!correctFile)
                {
                    if(line.compare("TEAMS"))
                    {
                        std::cout << "TEAM-GENERATOR:" << " File: " << file << " is a team file" << std::endl;
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
                    teamNames.push_back(TeamNames(line));
                }
            }
            teams.close();
            
            return true;
        }
        else
            return false;
    }

    void DebugPrintTeams()
    {
        for(int i = 0; i < teamNames.size(); i++)
        {
            // Debug line for all teams std::cout << teamNames[i].name << " " << teamNames[i].used << std::endl;
            std::string temp = teamNames[i].name;

            for(int j = 0; j < teamNames.size(); j++)
            {
                if(i != j)
                {
                    if(!temp.compare(teamNames[j].name))
                    {
                        std::cout << temp << " has been found twice" << std::endl;
                    }
                }
            }
        }
    }

    Team MakeTeam()
    {
        return Team(FindName());
    }
private:

    std::string FindName()
    {
        int i = 0;
        while(1)
        {
            int value = rand() % teamNames.size();
            if(!teamNames[value].used)
            {
                teamNames[value].used = true;
                return teamNames[value].name;
            }
            i++;
            if(i >= teamNames.size())
            {
                std::cout << "TEAM GENERATOR: Error, Incorrect iteration of string" << std::endl;
                return NULL;
            }
        }
    }
    
    std::vector<TeamNames> teamNames;
};
