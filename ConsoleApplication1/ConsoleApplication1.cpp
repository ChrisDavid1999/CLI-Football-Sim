#include "Competition.h"
int main(int argc, char* argv[])
{
    std::shared_ptr<TeamGenerator> team_generator = std::make_shared<TeamGenerator>();
    std::shared_ptr<PlayerGenerator> player_generator = std::make_shared<PlayerGenerator>();
    if(team_generator->Init("teams.txt") && player_generator->init("players/players.txt"))
    {
        std::vector<std::string> super_cup_names, champs_cup_names;
        
        {
            League league("WFL", "leagues/WFL.txt", true);
            league.Season("WFL");
            
            auto winners = league.TopTeams(6);
            auto teams = league.AllTeams();
            
            for(auto temp : winners)
            {
                champs_cup_names.push_back(temp);
                std::cout << temp << std::endl;
            }
            
            std::cout << "-----" << std::endl;
            
            for(auto temp : teams)
            {
                super_cup_names.push_back(temp);
                std::cout << temp << std::endl;
            }
        }

        {
            League league("EFL", "leagues/EFL.txt", true);
            league.Season("EFL");
            
            auto winners = league.TopTeams(6);
            auto teams = league.AllTeams();
            
            for(auto temp : winners)
            {
                champs_cup_names.push_back(temp);
                std::cout << temp << std::endl;
            }
            
            std::cout << "-----" << std::endl;
            
            for(auto temp : teams)
            {
                super_cup_names.push_back(temp);
                std::cout << temp << std::endl;
            }
        }

        {
            League league("SFL", "leagues/SFL.txt", true);
            league.Season("SFL");
            
            auto winners = league.TopTeams(6);
            auto teams = league.AllTeams();
            
            for(auto temp : winners)
            {
                champs_cup_names.push_back(temp);
                std::cout << temp << std::endl;
            }
            
            std::cout << "-----" << std::endl;
            
            for(auto temp : teams)
            {
                super_cup_names.push_back(temp);
                std::cout << temp << std::endl;
            }
        }

        {
            League league("NFL", "leagues/NFL.txt", true);
            league.Season("NFL");
            
            auto winners = league.TopTeams(6);
            auto teams = league.AllTeams();
            
            for(auto temp : winners)
            {
                champs_cup_names.push_back(temp);
                std::cout << temp << std::endl;
            }
            
            std::cout << "-----" << std::endl;
            
            for(auto temp : teams)
            {
                super_cup_names.push_back(temp);
                std::cout << temp << std::endl;
            }
        }

        //Cups, needs fixing up
        /*{
            Cup cup(super_cup_names);
            std::cout << "Type anything then press enter to continue-->" << std::endl;
            cup.CupGo();
            char a;
            std::cin >> a; 
        }

        {
            Cup cup(champs_cup_names);
            std::cout << "Type anything then press enter to continue-->" << std::endl;
            char a;
            std::cin >> a; 
        }*/
        
        /*League league_wfl("WFL", team_generator, player_generator, 16, false);
        League league_efl("EFL", team_generator, player_generator, 16, false);
        League league_sfl("SFL", team_generator, player_generator, 16, false);
        League league_nfl("NFL", team_generator, player_generator, 16, false);

        League leaguew("WFL", "leagues/NFL.txt", true);
        leaguew.Season("WFL");
        League leaguen("NFL", "leagues/NFL.txt", true);
        leaguen.Season("NFL");
        League leaguee("EFL", "leagues/EFL.txt", true);
        leaguee.Season("EFL");
        League leagues("SFL", "leagues/SFL.txt", true);
        leagues.Season("SFL");
        
        std::ofstream file_wfl("leagues/WFL.txt");
        file_wfl << league_wfl.SaveLeague();
        file_wfl.close();

        std::ofstream file_sfl("leagues/SFL.txt");
        file_sfl << league_sfl.SaveLeague();
        file_sfl.close();

        std::ofstream file_efl("leagues/EFL.txt");
        file_efl << league_efl.SaveLeague();
        file_efl.close();

        std::ofstream file_nfl("leagues/NFL.txt");
        file_nfl << league_nfl.SaveLeague();
        file_nfl.close();*/
        //generator->DebugPrintTeams();
        return 0;
    }
    else
        return 1;
}
