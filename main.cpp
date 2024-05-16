// Transformar matriz em uma assr e todas as funcoes para metodos

#include <SFML/Graphics.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

int **createMatrix( int size_x, int size_y) {
  int **matrix = new int*[size_x]; 
  for (int x = 0; x < size_x; x++) {
    matrix[x] = new int[size_y];
    for (int y = 0; y < size_y; y++) {
      matrix[x][y] = 0;
    }
  }
  return matrix;
}

void renderMatrix(sf::RenderWindow& window,int** matrix, int size_x, int size_y) {
  for (int x = 0; x < size_x; x++) {
    for (int y = 0; y < size_y; y++) {
      sf::RectangleShape rect(sf::Vector2f(10,10));
      rect.setPosition(x, y);
      if (matrix[x][y] == 0) {
        rect.setFillColor(sf::Color::White);
      }
      else if(matrix[x][y] == 1){
        rect.setFillColor(sf::Color::Black);
      }
      else if (matrix[x][y] == 2) {
        rect.setFillColor(sf::Color::Cyan);
      }
      else if ( matrix[x][y] == 3) {
        rect.setFillColor(sf::Color::Green);
      }
      else if (matrix[x][y] == 4) {
        rect.setFillColor(sf::Color::Red);
      }
      window.draw(rect);

    }
  }
}

void randomSearch(int** matrix, int index_x,int index_y, int start_x,int start_y) {
  matrix[start_x+1][start_y+1] = 2;
}


int main()
{
  bool is_start_placed = false;
  int start_x;
  int start_y;
  int end_x = 0;
  int end_y = 0;

  int size_x = 100;
  int size_y = 100;
  int** matrix;
  matrix = createMatrix(size_x, size_y);

  sf::RenderWindow window(sf::VideoMode(size_x, size_y), "Teste");
  window.setFramerateLimit(9999);
  
  //MAIN LOOP
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (sf::Event::MouseButtonPressed) {
        int index_x = sf::Mouse::getPosition(window).x / (1.0 * window.getSize().x / size_x);
        int index_y = sf::Mouse::getPosition(window).y / (1.0 * window.getSize().y / size_y);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
          matrix[index_x][index_y] = 1;
          if (index_x == start_x && index_y == start_y) {
            is_start_placed = false;
          }
        } 
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
          matrix[index_x][index_y] = 0;
          if (index_x == start_x && index_y == start_y) {
            is_start_placed = false;
          }
        }
        
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
          if (is_start_placed == false) {
            start_x = index_x;
            start_y = index_y;
            matrix[index_x][index_y] = 3;
            is_start_placed = true;
          }
          else if(index_x != start_x || index_y != start_y){
            matrix[end_x][end_y] = 0;
            end_x = index_x;
            end_y = index_y;
            matrix[index_x][index_y] = 4;

          }
          //sf::sleep(sf::milliseconds(100));
        }
      }
    }
  
  window.clear();
  renderMatrix(window, matrix, size_x, size_y);
  window.display();

  }

  return 0;
}
