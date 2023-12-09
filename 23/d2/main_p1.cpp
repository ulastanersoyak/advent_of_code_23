#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct result{
  int green;
  int red;
  int blue;
  bool operator>=(const struct result &other){
    bool rs = (this->green >= other.green) && (this->red >= other.red) && (this->blue >= other.blue);
    return rs;
  }
};

int main(int argc, char **argv){
  if(argc < 2){
     std::cerr<<"usage: "<<argv[0]<<" <filename>\n";
    return -1; 
  }
  std::ifstream file{argv[1]};
  if(!file){
    std::cerr<<"failed to open file "<<argv[1];
    return -1;
  }
  std::vector<struct result> rsarr;
  struct result compare {.green = 13, .red = 12, .blue = 14};
  int rs = 0;
  int game_num = 1;
  std::string line;
  // Game 1: 1 green, 2 red, 6 blue; 4 red, 1 green, 3 blue; 7 blue, 5 green; 6 blue, 2 red, 1 green
  // Game 5: 3 green, 8 blue, 2 red; 11 red, 6 green, 11 blue; 8 red, 5 blue, 2 green
  while(std::getline(file, line)){
    int start = line.find(":") + 1;
    int game_count = std::count(line.begin(), line.end(), ';') + 1;
    int correct_game = 0;
    struct result local_rs{.green = 0, .red = 0, .blue = 0};
    for(int i = start; start < line.size(); i++){
      if(std::isdigit(line[i])){
        int first_digit = line[i] - '0';
        int second_digit = -1;
        if(std::isdigit(line[i + 1])){
          second_digit = line[i + 1] - '0';
          i+=1;
        }
        int num = (second_digit == -1) ? first_digit : first_digit * 10 + second_digit; 
        if(line[i + 2] == 'g'){
          local_rs.green = num;
          i+=6;
        }else if(line[i + 2] == 'r'){
          local_rs.red = num;
          i+=4;
        }else if(line[i + 2] == 'b'){
          local_rs.blue = num;
          i+=5;
        } 
      }else if(line[i] == ';' || line[i] == '\000'){
        if(compare >= local_rs){
          correct_game+=1;
        }
        local_rs.green = 0;
        local_rs.red = 0;
        local_rs.blue = 0;
        if(line[i] == '\000'){
          break;
        }
      }
    }
    if(game_count == correct_game){
      // std::cout<<game_num<<"\n";
      rs+=game_num;
    }
    game_num++;
  }
  std::cout<<rs;
  file.close();
  return 0;
}
