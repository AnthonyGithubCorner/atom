#include "../common/gameObject.hpp"
#include <vector>
#include "../interactionFile/iFileParser.hpp"
#include "../common/sceneInterpretter.hpp"
// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
}; 

class Game
{
    public:
        ModelRenderer  *Renderer;

        std::vector<std::pair<gameObject*, iFileParser*>> activeInteractions;
        // game state
        GameState    State;	
        bool         Keys[1024];
        unsigned int Width, Height;
        // constructor/destructor
        Game();
        ~Game();
        // initialize game state (load all shaders/textures/levels)
        void Init();
        // game loop
        void ProcessInput(float dt);
        void Update(float dt);
        void Render();
        void parse_sprite_data(std::string data_path);
        void parse_setting_data(std::string data_path);

        std::vector<gameObject *> activeGameObjects;

    private:


};
