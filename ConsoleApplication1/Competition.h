#pragma once
#include <memory>
#include <stdbool.h>
#include <stdbool.h>
#include <string>
#include "TeamGenerator.h"

struct CompetitionString
{
    std::string name;
    int iteration;
};

struct CompetitionHistory
{
    int position;
    CompetitionString comp;
};

enum MatchResult
{
    home, away, draw
};

struct LeagueValues
{
    int wins = 0;
    int loses = 0;
    int draws = 0;
    int goalsFor = 0;
    int goalsAgainst = 0;
};

class Cup
{
public:
    Cup(std::vector<std::string> teamNames)
    {
        if(teamNames.size() % 2 == 0)
        {
            int i = 1;
            for(auto temp : teamNames)
            {
                Team team(temp);
                //std::ofstream teamFile("teams/" + line + ".txt");
                //teamFile << line << "\n";
                std::ifstream teamFile("teams/" + temp + ".txt");
                bool good = false;
                std::string newLine;
                while(std::getline(teamFile, newLine))
                {
                    if(!good)
                    {
                        if(temp == newLine)
                        {
                            good = true;
                        }
                        else
                        {
                            std::cout << "no players here" << std::endl;
                        }
                    }
                    else
                    {
                        std::string n;
                        int rating, games, goals, age;

                        std::stringstream stream(newLine);
                        stream >> n >> rating >> games >> goals >> age;
                        team.players.push_back(std::make_shared<Player>(n, rating, games, goals, age));
                    }
                }
                teamsNames.push_back(team.GetName());
                teams[team.GetName()] = team;
                teamFile.close();
            }
        }
        else
            std::cout << "ERROR" << std::endl;
    }

    void CupGo()
    {
        int size = teams.size();

        int rounds = 0;
        while(size != 1)
        {
            size /= 2;
            rounds++;
        }
        
        for(int i = 0; i < rounds; i++)
        {
                std::vector<int> v;

                for (int i = 0; i < teamsNames.size(); i++)
                    v.push_back(i);
            std::cout << "Names: " << teamsNames.size() << " vsize: " << v.size() << std::endl;
            std::vector<std::string> toRemove;
                int x = 1;
                while(v.size() != 0)
                {
                    int x1 = getNum(v);
                    int x2 = getNum(v);
                    std::cout << "1." << x1 << " 2." << x2 << std::endl;
                    auto one = teamsNames[x1];
                    auto two = teamsNames[x2];
                    std::cout << teams[one].GetName() << " VS " << teams[two].GetName() << std::endl;
                    toRemove.push_back(two);
                    x++;
                }

            for(auto rm : toRemove)
            {
                auto iterator = remove(teamsNames.begin(), teamsNames.end(), rm);
                teamsNames.erase(iterator);
            }
        }
    }
private:
    // From: https://www.geeksforgeeks.org/generate-a-random-permutation-of-1-to-n/
    int getNum(std::vector<int>& v)
    {
 
        // Size of the vector
        int n = v.size();
 
        // Generate a random number
        srand(time(NULL));
 
        // Make sure the number is within
        // the index range
        int index = rand() % n;
 
        // Get random number from the vector
        int num = v[index];
 
        // Remove the number from the vector
        std::swap(v[index], v[n - 1]);
        v.pop_back();
 
        // Return the removed number
        return num;
    }
    
    std::unordered_map<std::string, Team> teams;
    std::vector<std::string> teamsNames;
};

class League
{
public:
    League(std::string n, std::shared_ptr<TeamGenerator> team_generator, std::shared_ptr<PlayerGenerator> player_generator, int s, bool homeAndAway)
    {
        homeAway = homeAndAway;
        size = s;
        name = n;
        for(int i = 0; i < size; i++)
        {
            auto t = team_generator->MakeTeam();
            for(int i = 0; i < 3; i++)
            {
                std::string playername = player_generator->GetPlayerName();
                int rating = rand() % 18 + 63, games = 0, goals = 0, age = rand() %4 + 16;
                std::cout << t.GetName() << ": "<< playername << " " << rating << " " << games << " " << goals << " " << age << std::endl;
                t.players.push_back(std::make_shared<Player>(playername, rating, games, goals, age));   
            }
            teams.push_back(t);
            leagueValues[t.GetName()] = std::make_shared<LeagueValues>();
        }
    }

    League(std::string n, std::string file, bool homeAndAway)
    {
        homeAway = homeAndAway;
        name = n;

        std::ifstream openfile(file);
        if(openfile.is_open())
        {
            std::string line;
            bool correctFile = false;
            while(std::getline(openfile, line))
            {
                if(!correctFile)
                {
                    if(line.compare("TEAMS"))
                    {
                        correctFile = true;
                    }
                    else
                    {
                        std::cout << "LEAGUELOADERROR - File not found -> " << file << std::endl;
                    }
                }
                else
                {
                    Team team(line);
                    //std::ofstream teamFile("teams/" + line + ".txt");
                    //teamFile << line << "\n";
                    std::ifstream teamFile("teams/" + line + ".txt");
                    bool good = false;
                    std::string newLine;
                    
                    while(std::getline(teamFile, newLine))
                    {
                        if(!good)
                        {
                            if(line == newLine)
                            {
                                good = true;
                            }
                            else
                            {
                                std::cout << "no players here" << std::endl;
                            }
                        }
                        else
                        {
                            std::string n;
                            int rating, games, goals, age;

                            std::stringstream stream(newLine);
                            stream >> n >> rating >> games >> goals >> age;
                            team.players.push_back(std::make_shared<Player>(n, rating, games, goals, age));
                        }
                    }
                    
                    teams.push_back(team);
                    leagueValues[team.GetName()] = std::make_shared<LeagueValues>();
                    teamFile.close();
                }
            }
        }
        size = teams.size();
        openfile.close();
    }

    void Season(std::string outputfile)
    {
        std::unordered_map<int, Team> t;

        for(int i = 0; i < size; i++)
            t[i] = teams[i];
        std::ofstream openFile("outputs/" + outputfile + ".txt");
        IterateRound(t, openFile);
        
        if(homeAway)
            IterateRoundReverse(t, openFile);
        
        PrintLeagueTable(openFile);
        openFile.close();
    }
    
    std::string SaveLeague()
    {
        std::string value = "LEAGUE\n";
        for(int i = 0; i < teams.size();i++)
            value = value + teams[i].GetName() + "\n";

        
        for(auto t : teams)
        {
            std::ofstream teamFile("teams/" + t.GetName() + ".txt");
            teamFile << t.GetName() << "\n";
            for(auto player : t.players)
            {
                int games = player->games + player->overallGames;
                int goals = player->goals + player->overallGoals;
                int age = player->age + 1;
                teamFile << player->name << " " << player->rating << " " << games << " " << goals << " " << age << "\n";
            }
            teamFile.close();
        }
        
        return value;
    }

    std::vector<std::string> AllTeams()
    {
        std::vector<std::string> t;

        for(auto n : teams)
        {
            t.push_back(n.GetName());
        }

        return t;
    }

    std::vector<std::string> TopTeams(int amount)
    {
        std::vector<std::string> t;
        std::vector<std::pair<std::string, int>> teamToPoints;
        for(int i = 0; i < teams.size(); i++)
        {
            int points = (leagueValues[teams[i].GetName()]->wins * 3) + leagueValues[teams[i].GetName()]->draws;
            std::pair<std::string, int> temp;
            temp.first = teams[i].GetName();
            temp.second = points;
            teamToPoints.push_back(temp);
        }
        
        for(int i = 0; i < amount; i++)
        {
            std::pair<std::string, int> max;
            bool first = true;
            for(auto event : teamToPoints)
            {
                if(first)
                {
                    max = event;
                    first = false;
                }
                else
                {
                    if(max.second < event.second)
                    {
                        max = event;
                    }
                }
            }

            t.push_back(max.first);
            auto iterator = remove(teamToPoints.begin(), teamToPoints.end(), max);
            teamToPoints.erase(iterator);
        }

        return t;
    }
private:
    void IterateRound(std::unordered_map<int, Team> &t, std::ofstream &file)
    {
        for(int i = 0; i < size - 1; i++)
        {
            file << "----- Round " << i+1 << " ----- \n";
            for(int j = 0; j < size;j += 2)
            {
                int home = rand() % (t[j].TeamValue()+1);
                int away = rand() % t[j + 1].TeamValue();
                file << home << " - " << t[j].GetName() << " vs "<< t[j+1].GetName() << " - " << away << "\n";
                auto result = GetMatchResult(home, away);
                auto &homeValues = leagueValues[t[j].GetName()];
                auto &awayValues = leagueValues[t[j+1].GetName()];
                
                if(result == MatchResult::home)
                {
                    homeValues->wins++;
                    awayValues->loses ++;
                }
                else if(result == MatchResult::away)
                {
                    homeValues->loses++;
                    awayValues->wins++;
                }
                else if(result == MatchResult::draw)
                {
                    homeValues->draws++;
                    awayValues->draws++;
                }

                homeValues->goalsAgainst += away;
                homeValues->goalsFor += home;
                awayValues->goalsAgainst += home;
                awayValues->goalsFor += away;

                for(int z = 0; z < home; z++)
                {
                    int value =  (rand() % (t[j].players.size()));
                    
                        t[j].players[value]->goals++;
                }

                for(int z = 0; z < away; z++)
                {
                    int value =  (rand() % (t[j + 1].players.size()));
                    
                        t[j+1].players[value]->goals++;
                }

                for(auto p : t[j].players)
                    p->games++;

                for(auto p : t[j+1].players)
                    p->games++;
            }


            auto temp = t[1];
            
            for(int k = 1; k < size; k++)
            {
                t[k] = t[k+1];
            }

            t[size-1] = temp;
            file << "\n";
        }
    }

    void IterateRoundReverse(std::unordered_map<int, Team> &t, std::ofstream &file)
    {
        for(int i = 0; i < size - 1; i++)
        {
            file << "----- Round " << i+1 << " ----- \n";
            for(int j = 0; j < size;j += 2)
            {
                int home = rand() % (t[j + 1].TeamValue()+1);
                int away = rand() % t[j].TeamValue();
                file << home << " - " << t[j+1].GetName() << " vs "<< t[j].GetName() << " - " << away << "\n";
                auto result = GetMatchResult(home, away);
                auto &homeValues = leagueValues[t[j+1].GetName()];
                auto &awayValues = leagueValues[t[j].GetName()];
                
                if(result == MatchResult::home)
                {
                    homeValues->wins++;
                    awayValues->loses ++;
                }
                else if(result == MatchResult::away)
                {
                    homeValues->loses++;
                    awayValues->wins++;
                }
                else if(result == MatchResult::draw)
                {
                    homeValues->draws++;
                    awayValues->draws++;
                }

                homeValues->goalsAgainst += away;
                homeValues->goalsFor += home;
                awayValues->goalsAgainst += home;
                awayValues->goalsFor += away;

                for(int z = 0; z < away; z++)
                {
                    int value =  (rand() % (t[j].players.size()));

                        t[j].players[value]->goals++;
                }

                for(int z = 0; z < home; z++)
                {
                    int value =  (rand() % (t[j + 1].players.size()));
                    
                        t[j+1].players[value]->goals++;
                }

                for(auto p : t[j].players)
                    p->games++;

                for(auto p : t[j+1].players)
                    p->games++;
            }


            auto temp = t[1];
            
            for(int k = 1; k < size; k++)
            {
                t[k] = t[k+1];
            }

            t[size-1] = temp;
            file << "\n";
        }
    }

    MatchResult GetMatchResult(int home, int away)
    {
        if(home > away)
            return MatchResult::home;
        
        if(home < away)
            return MatchResult::away;
        
        return MatchResult::draw;
    }

    void PrintLeagueTable(std::ofstream &file)
    {
        file << "\n\nTeam Performance\n\n";
        std::vector<std::pair<std::string, int>> teamToPoints;
        for(int i = 0; i < teams.size(); i++)
        {
            int points = (leagueValues[teams[i].GetName()]->wins * 3) + leagueValues[teams[i].GetName()]->draws;
            file << teams[i].GetName() << " G:" << leagueValues[teams[i].GetName()]->wins+leagueValues[teams[i].GetName()]->loses+leagueValues[teams[i].GetName()]->draws << " PTS:" << points <<" W:" <<
                            leagueValues[teams[i].GetName()]->wins << " D:" << leagueValues[teams[i].GetName()]->draws << " L:" << leagueValues[teams[i].GetName()]->loses << " GF:" <<
                                leagueValues[teams[i].GetName()]->goalsFor << " GA:" << leagueValues[teams[i].GetName()]->goalsAgainst
                                << "\n--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

            std::pair<std::string, int> temp;
            temp.first = teams[i].GetName();
            temp.second = points;
            teamToPoints.push_back(temp);
        }
        std::cout << std::endl;
        file << "\n\nPlayers Goals\n\n";
        for(auto t : teams)
        {
            /*std::cout << t.GetName() << "\n";
            std::cout << t.PrintPlayers() << "\n";*/
            file << t.GetName() << "\n";
            file << t.PrintPlayers() << "\n";
            std::ofstream teamFile("teams/" + t.GetName() + ".txt");
            teamFile << t.GetName() << "\n";
            for(auto player : t.players)
            {
                int games = player->games + player->overallGames;
                int goals = player->goals + player->overallGoals;
                int age = player->age + 1;
                teamFile << player->name << " " << player->rating << " " << games << " " << goals << " " << age << "\n";
            }
            teamFile.close();
        }
        file << "\n\nLeague Table\n\n";
        for(int i = 0; i < teams.size(); i++)
        {
            std::pair<std::string, int> max;
            bool first = true;
            for(auto event : teamToPoints)
            {
                if(first)
                {
                    max = event;
                    first = false;
                }
                else
                {
                    if(max.second < event.second)
                    {
                        max = event;
                    }
                }
            }

            std::cout << i+1 << "." << max.first << " - " << max.second << std::endl;
            file << i+1 << "." << max.first << " - " << max.second << "\n";
            auto iterator = remove(teamToPoints.begin(), teamToPoints.end(), max);
            teamToPoints.erase(iterator);
        }
    }
    bool homeAway;
    std::vector<Team> teams;
    std::unordered_map<std::string, std::shared_ptr<LeagueValues>> leagueValues;
    int size;
    std::string name;
};
