#include "main.h"

void Game()
{
    std::string command;
    Parsing parse;

    while (!parse.f_exit)
    {
        std::getline(std::cin, command);

        // PING PONG

        if (command == "ping")
        {
            std::cout << "pong" << "\n";
        }

        // FINISHED

        else if (command == "finished")
        {
            if (parse.f_start == true)
                std::cout << "no" << "\n";
            else if (parse.f_start == false)
                std::cout << "yes" << "\n";
        }

        // LOSE|WIN

        else if (command == "win")
        {
            if (parse.count_ship_1 + parse.count_ship_2 + parse.count_ship_3 + parse.count_ship_4 == parse.counter_kill_ship_opp && parse.f_start == false)
                std::cout << "yes" << "\n";
            else
                std::cout << "no" << "\n";
        }
        else if (command == "lose")
        {
            if (parse.count_ship_1 + parse.count_ship_2 + parse.count_ship_3 + parse.count_ship_4 == parse.counter_kill_ship_comp && parse.f_start == false)
                std::cout << "yes" << "\n";
            else
                std::cout << "no" << "\n";
        }

        // CREATE

        else if (command == "create master")
        {
            std::cout << "ok" << "\n";
            parse.mode = "master";
            srand(time(0));

            parse.width = rand() % 11 + 10;
            parse.height = rand() % 10 + 10;

            parse.count_ship_1 = rand() % 5 + 1;
            parse.count_ship_2 = rand() % 4 + 1;
            parse.count_ship_3 = rand() % 3 + 1;
            parse.count_ship_4 = rand() % 2 + 1;

            ships.clear();

            Placement(parse.width, parse.height, parse.count_ship_1, parse.count_ship_2, parse.count_ship_3, parse.count_ship_4);
        }
        else if (command == "create slave")
        {
            std::cout << "ok" << "\n";
            parse.mode = "slave";
            ships.clear();
        }

        // EXIT

        else if (command == "exit")
        {
            std::cout << "ok" << "\n";
            parse.f_exit = true;
        }

        // START|STOP

        else if (command == "start")
        {
            if (parse.mode.empty())
            {
                std::cout << "failed\n";
            }
            else
            {
                parse.f_start = true;
                if (parse.mode == "slave"){
                    Placement(parse.width, parse.height, parse.count_ship_1, parse.count_ship_2, parse.count_ship_3, parse.count_ship_4);
                }
                std::cout << "ok" << "\n";
            }
        }

        else if (command == "stop" && parse.f_start)
        {
            parse.f_start = false;
            std::cout << "ok" << "\n";
        }

        // SHOT

        else if (command == "shot" && parse.f_start)
        {
            if (parse.strategy == "ordered")
            {
                Ordered_shot(parse.width, parse.height, parse.x_for_ordered, parse.y_for_ordered);
            }
            else if (parse.strategy == "custom")
            {
                if (parse.not_random_shot == false)
                {
                    Random_comp_shot(parse.width, parse.height, history_shot);
                }
                else if (parse.not_random_shot == true)
                {
                    if (parse.orient_hit_ship == 's'){
                        NOT_Random_comp_shot(parse.width, parse.height, parse.last_x_hit, parse.last_y_hit, history_shot);
                    }else{

                        NOT_Random_comp_shot_with_orient(parse.width, parse.height, parse.last_x_hit, parse.last_y_hit, history_shot, parse.orient_hit_ship);
                    }
                }
            }
        }

        // GET

        else if (command.substr(0, 3) == "get" && parse.f_start)
        {
            size_t pos = 4;

            std::string param_name = command.substr(pos, command.find(' ', pos) - pos);
            pos = command.find(' ', pos) + 1;

            if (param_name == "width")
            {
                std::cout << parse.width << "\n";
            }
            else if (param_name == "height")
            {
                std::cout << parse.height << "\n";
            }
            else if (param_name == "count")
            {
                size_t ship_type_end = command.find(' ', pos);
                std::string ship_type = command.substr(pos, ship_type_end - pos);
                pos = ship_type_end + 1;
                parse.type_ship = ship_type;
                if (ship_type == "1")
                {
                    std::cout << parse.count_ship_1 << "\n";
                }
                else if (ship_type == "2")
                {
                    std::cout << parse.count_ship_2 << "\n";
                }
                else if (ship_type == "3")
                {
                    std::cout << parse.count_ship_3 << "\n";
                }
                else if (ship_type == "4")
                {
                    std::cout << parse.count_ship_4 << "\n";
                }
                else
                {
                    std::cout << "failed\n";
                }
            }
            else
            {
                std::cout << "failed\n";
            }
        }

        // SET

        else if (command.substr(0, 3) == "set")
        {
            size_t pos = 4;

            std::string param_name = command.substr(pos, command.find(' ', pos) - pos);
            pos = command.find(' ', pos) + 1;

            if (param_name == "width")
            {
                std::string width_str = command.substr(pos);
                parse.width = std::stoull(width_str);
                std::cout << "ok" << "\n";
            }
            else if (param_name == "height")
            {
                std::string height_str = command.substr(pos);
                parse.height = std::stoull(height_str);
                std::cout << "ok" << "\n";
            }
            else if (param_name == "count")
            {
                size_t ship_type_end = command.find(' ', pos);
                std::string ship_type = command.substr(pos, ship_type_end - pos);
                pos = ship_type_end + 1;
                int64_t count = std::stoull(command.substr(pos));

                if (ship_type == "1")
                {
                    parse.count_ship_1 = count;
                }
                else if (ship_type == "2")
                {
                    parse.count_ship_2 = count;
                }
                else if (ship_type == "3")
                {
                    parse.count_ship_3 = count;
                }
                else if (ship_type == "4")
                {
                    parse.count_ship_4 = count;
                }
                else
                {
                    std::cout << "failed\n";
                    continue;
                }
                std::cout << "ok" << "\n";
            }
            else if (param_name == "strategy")
            {
                std::string strategy_value = command.substr(pos);
                parse.strategy = strategy_value;
                std::cout << "ok" << "\n";
            }
            else if (param_name == "result")
            {
                std::string result_value = command.substr(pos);
                parse.result = result_value;

                if (parse.result == "miss")
                {
                    if(parse.last_hits.empty())
                    {
                        parse.not_random_shot = false;
                    }
                }
                else if (parse.result == "hit")
                {
                    parse.not_random_shot = true;

                    if (parse.orient_hit_ship = 's'){

                        parse.last_hits.push_back(history_shot.back());
                        parse.last_x_hit = parse.last_hits.back().x;
                        parse.last_y_hit = parse.last_hits.back().y;

                        if (parse.last_hits.size() == 2){
                            if (parse.last_hits[0].x == parse.last_hits[1].x){
                                parse.orient_hit_ship = 'v';
                            }else if(parse.last_hits[0].y == parse.last_hits[1].y){
                                parse.orient_hit_ship = 'h';
                            }
                        }
                    }
                    parse.hits.push_back(history_shot.back());                 

                }
                else if (parse.result == "kill")
                {

                    parse.hits.push_back(history_shot.back());

                    Merge_vectors(history_shot, parse.hits);

                    parse.not_random_shot = false;

                    parse.counter_kill_ship_opp++;

                    if(parse.count_ship_1 + parse.count_ship_2 + parse.count_ship_3 + parse.count_ship_4 == parse.counter_kill_ship_opp){
                        parse.f_start = false;
                    }

                    parse.last_hits.clear();
                    parse.hits.clear();

                    parse.orient_hit_ship = 's';
                }

                std::cout << "ok\n";
            }
            else
            {
                std::cout << "failed\n";
            }

        }

        // SHOT X Y

        else if (command.substr(0, 4) == "shot" && parse.f_start)
        {
            size_t pos = 5;
            if (pos < command.size())
            {

                size_t space_pos = command.find(' ', pos);
                std::string shot_x_str = command.substr(pos, space_pos - pos);
                int64_t shot_x = std::stoull(shot_x_str);

                pos = space_pos + 1;
                std::string shot_y_str = command.substr(pos);
                int64_t shot_y = std::stoull(shot_y_str);

                int64_t count_ship = parse.count_ship_1 + parse.count_ship_2 + parse.count_ship_3 + parse.count_ship_4;
                bool flag = false;

                Shot(shot_x, shot_y, ships, parse.counter_kill_ship_comp, count_ship, flag);

                if (flag){
                    parse.f_start = false;
                }
            }
        }

        // DUMP

        else if (command.substr(0, 4) == "dump" && parse.f_start)
        {
            size_t pos = 5;
            std::string path_dump = command.substr(pos);
            parse.dump_path = path_dump;
            std::cout << "ok\n";

            std::ofstream outFile(parse.dump_path);
            if (!outFile.is_open())
            {
                std::cout << "failed\n";
                continue;
            }

            outFile << parse.width << " " << parse.height << "\n";

            for (const Ship &ship : ships)
            {
                outFile << ship.len_ship << " " << ship.orient << " " << ship.x << " " << ship.y << "\n";
            }

            outFile.close();
        }

        // LOAD

        else if (command.substr(0, 4) == "load")
        {
            size_t pos = 5; 
            std::string path_load = command.substr(pos);
            parse.load_path = path_load;
            parse.mode = "load";
            std::cout << "ok\n";

            if (!parse.load_path.empty())
            {
                std::ifstream file(parse.load_path);
                if (!file.is_open())
                {
                    std::cout << "failed\n"; 
                    continue;
                }

                std::string cell;

                int64_t width, height;
                if (!(file >> width >> height))
                {
                    std::cout << "failed\n"; 
                    file.close();
                    continue;
                }

                parse.width = width;
                parse.height = height;

                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

             
                while (getline(file, cell))
                {
                    std::stringstream ss(cell);

                    int16_t len_ship;
                    char orient;
                    int64_t x, y;

                    if (!(ss >> len_ship >> orient >> x >> y))
                    {
                        std::cout << "failed\n"; 
                        continue;
                    }

               
                    Ship ship(len_ship, x, y, orient);
                    ship.setCoordinates();

                    ships.push_back(ship);
                }

                file.close();
            }
        }

        // Обработка неизвестной команды
        else  
        {
            std::cout << "unknown command or game finisfed" << "\n";
        }
    }
}

void Placement(int64_t width, int64_t height, int64_t count_ship_1, int64_t count_ship_2, int64_t count_ship_3, int64_t count_ship_4)
{
    srand(time(0));

    std::vector<int> ship_sizes = {4, 3, 2, 1};
    std::vector<int64_t> ship_counts = {count_ship_4, count_ship_3, count_ship_2, count_ship_1};

    const int dx[8] = {-1, 0, 1, 0, -1, 1, -1, 1};  
    const int dy[8] = {0, 1, 0, -1, -1, -1, 1, 1};

    for (int idx = 0; idx < 4; ++idx)
    {
        for (int64_t i = 0; i < ship_counts[idx]; ++i)
        {
            bool placed = false;

            while (!placed)
            {
                int x = rand() % width;
                int y = rand() % height;
                char orient;
                if (rand() % 2 == 0)
                {
                    orient = 'h';
                }
                else
                {
                    orient = 'v';
                }
                Ship new_ship(ship_sizes[idx], x, y, orient);

                new_ship.setCoordinates();

                bool valid = true;
                for (int j = 0; j < new_ship.len_ship; ++j)
                {
                    if (new_ship.Coordinates[j].x < 0 || new_ship.Coordinates[j].y < 0 || new_ship.Coordinates[j].x >= width || new_ship.Coordinates[j].y >= height)
                    {
                        valid = false;
                        break;
                    }
                }

                if (valid)
                {
                    bool overlap_found = false;

                    for (const Ship& ship : ships)
                    {
                        for (const Shot_coord& new_coord : new_ship.Coordinates)
                        {
                            for (int i = 0; i < 8; ++i)
                            {
                                int nx = new_coord.x + dx[i];
                                int ny = new_coord.y + dy[i];

                                if (nx < 0 || ny < 0 || nx >= width || ny >= height)
                                {
                                    continue;
                                }

                                for (const Shot_coord& existing_coord : ship.Coordinates)
                                {
                                    if (nx == existing_coord.x && ny == existing_coord.y)
                                    {
                                        overlap_found = true;
                                        break;
                                    }
                                }
                                if (overlap_found) break;
                            }
                            if (overlap_found) break;
                        }
                        if (overlap_found) break;
                    }

                    if (!overlap_found)
                    {
                        ships.push_back(new_ship);  
                        placed = true;
                    }
                }
            }
        }
    }
}

void Shot(int64_t shot_x, int64_t shot_y, std::vector<Ship> &ships, int64_t &counter_kill_ship_comp, int64_t count_ship, bool &flag)
{
    bool shot_result = false;

    for (auto &ship : ships)
    {
        for (int i = 0; i < ship.Coordinates.size(); i++)
        {
            if (ship.Coordinates[i].x == shot_x && ship.Coordinates[i].y == shot_y)
            {
                shot_result = true;
                ship.count_shot--;

                if (ship.count_shot > 0)
                    std::cout << "hit\n";

                else if (ship.count_shot == 0)

                    counter_kill_ship_comp++;
                    if (counter_kill_ship_comp == count_ship){
                        flag = true;
                    }
                    std::cout << "kill\n";
                    

                ship.Coordinates[i].x = -1;
                ship.Coordinates[i].y = -1;
            }
        }
    }

    if (!shot_result)
        std::cout << "miss\n";
}

void Random_comp_shot(int64_t width, int64_t height, std::vector<Shot_coord> &history_shot)
{
    srand(time(0));

    int64_t x, y;
    bool unique_shot = false;

    while (!unique_shot)
    {
        x = rand() % width;
        y = rand() % height;

        bool shot_exists = false;
        for (const auto &shot : history_shot)
        {
            if (shot.x == x && shot.y == y)
            {
                shot_exists = true;
                break;
            }
        }

        if (!shot_exists)
        {
            history_shot.push_back(Shot_coord(x, y));
            std::cout << x << " " << y << "\n";
            unique_shot = true;
        }
    }
}

void NOT_Random_comp_shot(int64_t width, int64_t height, int64_t last_x_hit, int64_t last_y_hit, std::vector<Shot_coord> &history_shot)
{

    std::vector<Shot_coord> variants_shot;

    if (last_y_hit + 1 < height)
        variants_shot.push_back(Shot_coord(last_x_hit, last_y_hit + 1));
    if (last_y_hit - 1 >= 0)
        variants_shot.push_back(Shot_coord(last_x_hit, last_y_hit - 1));
    if (last_x_hit + 1 < width)
        variants_shot.push_back(Shot_coord(last_x_hit + 1, last_y_hit));
    if (last_x_hit - 1 >= 0)
        variants_shot.push_back(Shot_coord(last_x_hit - 1, last_y_hit));


    for (auto &variant_shot : variants_shot)
    {
        bool flag = false;

        for (auto &shot : history_shot)
        {
            if (variant_shot.x == shot.x && variant_shot.y == shot.y)
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            std::cout << variant_shot.x << " " << variant_shot.y << "\n";
            history_shot.push_back(Shot_coord(variant_shot.x, variant_shot.y));
            return;
        }
    }
}

void NOT_Random_comp_shot_with_orient(int64_t width, int64_t height, int64_t last_x_hit, int64_t last_y_hit, std::vector<Shot_coord> &history_shot, char orient){

    std::vector<Shot_coord> variants_shot;

    if (orient == 'v'){
        if (last_y_hit - 3 >= 0){
            variants_shot.push_back(Shot_coord(last_x_hit, last_y_hit - 3));
            variants_shot.push_back(Shot_coord(last_x_hit, last_y_hit - 2));
            variants_shot.push_back(Shot_coord(last_x_hit, last_y_hit - 1));
        }else{
            variants_shot.push_back(Shot_coord(last_x_hit, 0));
            variants_shot.push_back(Shot_coord(last_x_hit, 1));
            variants_shot.push_back(Shot_coord(last_x_hit, 2));
        }
        if (last_y_hit + 3 < height){
            variants_shot.push_back(Shot_coord(last_x_hit, last_y_hit + 1));
            variants_shot.push_back(Shot_coord(last_x_hit, last_y_hit + 2));
            variants_shot.push_back(Shot_coord(last_x_hit, last_y_hit + 3));
        }else{
            variants_shot.push_back(Shot_coord(last_x_hit, height - 1));
            variants_shot.push_back(Shot_coord(last_x_hit, height - 2));
            variants_shot.push_back(Shot_coord(last_x_hit, height - 3));            
        }
    }else if(orient == 'h'){
        if (last_x_hit - 3 >= 0){
            variants_shot.push_back(Shot_coord(last_x_hit - 3, last_y_hit));
            variants_shot.push_back(Shot_coord(last_x_hit - 2, last_y_hit));
            variants_shot.push_back(Shot_coord(last_x_hit - 1, last_y_hit));
        }else{
            variants_shot.push_back(Shot_coord(0, last_y_hit));
            variants_shot.push_back(Shot_coord(1, last_y_hit));
            variants_shot.push_back(Shot_coord(2, last_y_hit));
        }
        if (last_x_hit + 3 < width){
            variants_shot.push_back(Shot_coord(last_x_hit + 1, last_y_hit));
            variants_shot.push_back(Shot_coord(last_x_hit + 2, last_y_hit));
            variants_shot.push_back(Shot_coord(last_x_hit + 3, last_y_hit));
        }else{
            variants_shot.push_back(Shot_coord(width - 1, last_y_hit));
            variants_shot.push_back(Shot_coord(width - 2, last_y_hit));
            variants_shot.push_back(Shot_coord(width - 3, last_y_hit));
        }
    }

    for (auto &variant_shot : variants_shot)
    {
        bool flag = false;

        for (auto &shot : history_shot)
        {
            if (variant_shot.x == shot.x && variant_shot.y == shot.y)
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            std::cout << variant_shot.x << " " << variant_shot.y << "\n";
            history_shot.push_back(Shot_coord(variant_shot.x, variant_shot.y));
            return;
        }
    }
}

void Ordered_shot(int64_t width, int64_t height, int64_t &x_for_ordered, int64_t &y_for_ordered)
{
    if (x_for_ordered + 1 == width && y_for_ordered + 1 < height)
    {
        std::cout << x_for_ordered << " " << y_for_ordered << "\n";
        x_for_ordered = 0;
        y_for_ordered++;
    }
    else if (x_for_ordered < width)
    {
        std::cout << x_for_ordered << " " << y_for_ordered << "\n";
        x_for_ordered++;
    }
}

void Merge_vectors(std::vector<Shot_coord> &history_shot, std::vector<Shot_coord> &hits){

    for (auto &hits : hits)
    {
        history_shot.push_back(Shot_coord(hits.x + 1, hits.y));
        history_shot.push_back(Shot_coord(hits.x - 1, hits.y));
        history_shot.push_back(Shot_coord(hits.x, hits.y + 1));
        history_shot.push_back(Shot_coord(hits.x, hits.y - 1));
        history_shot.push_back(Shot_coord(hits.x + 1, hits.y + 1));
        history_shot.push_back(Shot_coord(hits.x + 1, hits.y - 1));
        history_shot.push_back(Shot_coord(hits.x - 1, hits.y + 1));
        history_shot.push_back(Shot_coord(hits.x - 1, hits.y - 1));
    }

}

int main(int argc, char *argv[])
{
    Game();
    return 0;
}