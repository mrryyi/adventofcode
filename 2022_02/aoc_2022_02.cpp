#include <iostream>
#include <fstream>
#include <string>

// These are identifiers, as well as the scores for playing them. 
const int ROCK        = 1;
const int PAPER       = 2;
const int SCISSOR     = 3;

// clarifiers
const int DRAW_SCORE  = 3;
const int WIN_SCORE   = 6;

void part_one() {
  // Open file
  std::ifstream input_file("input.txt");

  if (!input_file.is_open()) {
    std::cout << "Error opening file" << std::endl;
  }

  int total_score = 0;

  { // Loop specific block
    std::string line;
    while (std::getline(input_file, line)) {
      
      // Split line into two strings
      const std::string first = line.substr(0, line.find(' '));
      const std::string second = line.substr(line.find(' ') + 1, line.size());
      
      const auto enemy_move = first  == "A" ? ROCK : first == "B" ? PAPER : SCISSOR;
      const auto our_move   = second == "X" ? ROCK : second == "Y" ? PAPER : SCISSOR;

      // draw (3 points)
      if (enemy_move == our_move)
        total_score += DRAW_SCORE;

      // win (6 points)
      else if (enemy_move == ROCK && our_move == PAPER)
        total_score += WIN_SCORE;
      else if (enemy_move == PAPER && our_move == SCISSOR)
        total_score += WIN_SCORE;
      else if (enemy_move == SCISSOR && our_move == ROCK)
        total_score += WIN_SCORE;

      // lose (0 points) (no condiitonals neded)

      total_score += our_move;
    }
  }

  input_file.close();

  std::cout << "part two total_score: " << total_score << std::endl;
}

int create_losing_move(const int enemy_move) {
  return enemy_move == ROCK ? SCISSOR : enemy_move == PAPER ? ROCK : PAPER;
}

int create_drawing_move(const int enemy_move) {
  return enemy_move;
}

int create_winning_move(const int enemy_move) {
  return enemy_move == ROCK ? PAPER : enemy_move == PAPER ? SCISSOR : ROCK;
}

void part_two() {
  // Open file
  std::ifstream input_file("input.txt");

  if (!input_file.is_open()) {
    std::cout << "Error opening file" << std::endl;
  }

  int total_score = 0;

  const int MUST_LOSE = 0;
  const int MUST_DRAW = 3;
  const int MUST_WIN = 6;

  { // Loop specific block
    std::string line;
    while (std::getline(input_file, line)) {
      
      // Split line into two strings
      std::string first = line.substr(0, line.find(' '));
      std::string second = line.substr(line.find(' ') + 1, line.size());
      
      auto enemy_move     = first  == "A" ? ROCK : first == "B" ? PAPER : SCISSOR;
      auto must_outcome   = second == "X" ? MUST_LOSE : second == "Y" ? MUST_DRAW : MUST_WIN;

      switch (must_outcome) {
        case MUST_LOSE:
          total_score += create_losing_move(enemy_move);
          break;
        case MUST_DRAW:
          total_score += create_drawing_move(enemy_move);
          total_score += DRAW_SCORE;
          break;
        case MUST_WIN:
          total_score += create_winning_move(enemy_move);
          total_score += WIN_SCORE;
          break;
      }
    }
  }

  input_file.close();

  std::cout << "part two total_score: " << total_score << std::endl;
}

int main()
{
  part_one();
  part_two();
  return 0;
}