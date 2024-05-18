#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

sf::RenderWindow window(sf::VideoMode(100, 100), "Teste");

class Matrix {
public:
  int size_x;
  int size_y;
  int** matrix; 

  Matrix(int size_x, int size_y) {
    this->size_x = size_x;
    this->size_y = size_y;
    this->matrix = createMatrix(size_x, size_y);
  };
 


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


  sf::Color checkType(int x, int y) {
    switch(this->matrix[x][y]) {
        case 0:
            return sf::Color::White;
        case 1:
            return sf::Color::Black;
        case 2:
            return sf::Color::Cyan;
        case 3:
            return sf::Color::Green;
        case 4:
            return sf::Color::Red;
        default:
            return sf::Color::Magenta;
    }
  }

  void renderMatrix() {
    for (int x = 0; x < this->size_x; x++) {
      for (int y = 0; y < this->size_y; y++) {
        sf::RectangleShape rect(sf::Vector2f(10,10));
        rect.setPosition(x, y);
        rect.setFillColor(checkType(x,y));
        window.draw(rect);
      }
    }
  }

};

int main()
{
  bool is_start_placed = false;
  int start_x;
  int start_y;
  int end_x = 0;
  int end_y = 0;
  
  Matrix obj(100,100);

  window.setFramerateLimit(99999);
  
  //MAIN LOOP
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (sf::Event::MouseButtonPressed) {
        int index_x = sf::Mouse::getPosition(window).x / (1.0 * window.getSize().x / obj.size_x);
        int index_y = sf::Mouse::getPosition(window).y / (1.0 * window.getSize().y / obj.size_y);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
          obj.matrix[index_x][index_y] = 1;
          if (index_x == start_x && index_y == start_y) {
            is_start_placed = false;
          }
        } 
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
          obj.matrix[index_x][index_y] = 0;
          if (index_x == start_x && index_y == start_y) {
            is_start_placed = false;
          }
        }
        
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
          if (is_start_placed == false) {
            start_x = index_x;
            start_y = index_y;
            obj.matrix[index_x][index_y] = 3;
            is_start_placed = true;
          }
          else if(index_x != start_x || index_y != start_y){
            obj.matrix[end_x][end_y] = 0;
            end_x = index_x;
            end_y = index_y;
            obj.matrix[index_x][index_y] = 4;

          }
        }
      }
      
    }
  
  window.clear();
  obj.renderMatrix();
  window.display();

  }

  return 0;
}
