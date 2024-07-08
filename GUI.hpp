#ifndef TREESITERATORS_CPP_GUI_HPP
#define TREESITERATORS_CPP_GUI_HPP

#include <SFML/Graphics.hpp>
#include <typeinfo>  // For typeid
#include <string>  // For std::to_string
#include "Complex.hpp"  // For std::complex
#include "Tree.hpp"  // Include your tree structure header here

template<typename B>
inline std::string toString(B value) {
    return std::to_string(value);
}

template<>
inline std::string toString(Complex value) {
    return value.toString();
}

template<>
inline std::string toString(std::string value) {
    return value;
}

template<typename T, unsigned int D = 2>
class GUI {
private:
    sf::RenderWindow window;
    Tree<T, D> tree;  // Example assuming Tree<T, D> is your tree structure

    // SFML-related members
    sf::Font font;  // Example font for text rendering
    sf::CircleShape nodeShape;  // Example node shape for visualization
    sf::Text nodeText;  // Example text for node labels

public:
    GUI(Tree<T,D> t) : window(sf::VideoMode(1600, 1200), "Tree GUI"), tree(t) {
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
            // If loading fails, handle the error
            std::cerr << "Failed to load font file!" << std::endl;
            // Optionally, you could use a system font instead of loading from file
        }

        // Configure node shape
        nodeShape.setRadius(70);
        nodeShape.setFillColor(sf::Color::Black);

        // Configure node text
        nodeText.setFont(font);
        nodeText.setCharacterSize(10);
        nodeText.setFillColor(sf::Color::White);

        // Initialize other SFML-related components
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);

            // Example: Draw the tree nodes
             drawTree(tree.get_root(), 1200, 50, 600); // Assuming a method to draw nodes

            window.display();
        }
    }

    // Example method to draw tree nodes recursively
    void drawTree(typename Tree<T,D>::Node* node, float x, float y, float xOffset) {
        if (node) {
            // Draw current node
            nodeShape.setPosition(x, y);
            window.draw(nodeShape);

            nodeText.setString(toString(node->key));
            nodeText.setPosition(x, y + 60);
            nodeText.setFillColor(sf::Color::Magenta);  // Example text color (white
            window.draw(nodeText);

            // Recursively draw children nodes
            float nextLevelY = y + 300;
            float nextLevelXOffset = xOffset / D;
            for (size_t i = 0; i < node->children.size(); ++i) {
                sf::VertexArray line(sf::Lines, 5);
                line[0].position = sf::Vector2f(x + nodeShape.getRadius(), y + nodeShape.getRadius());
                line[1].position = sf::Vector2f(x - xOffset/2 + i * nextLevelXOffset + nodeShape.getRadius(), nextLevelY + nodeShape.getRadius());
                line[0].color = sf::Color::Red;
                line[1].color = sf::Color::Blue;
                window.draw(line);

                drawTree(node->children[i].get(), x - xOffset/2 + i * nextLevelXOffset, nextLevelY, nextLevelXOffset);
            }
        }
    }

    // Methods for interacting with the GUI and tree
};

#endif // TREESITERATORS_CPP_GUI_HPP
