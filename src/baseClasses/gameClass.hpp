#include "../common/gameObject.hpp"
#include <vector>
#include "../interactionFile/iFileParser.hpp"
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
        // game state
        GameState    State;	
        bool         Keys[1024];
        unsigned int Width, Height;
        // constructor/destructor
        Game(unsigned int width, unsigned int height);
        ~Game();
        // initialize game state (load all shaders/textures/levels)
        void Init();
        // game loop
        void ProcessInput(float dt);
        void Update(float dt);
        void Render();
        void parse_sprite_data(std::string data_path);
        std::vector<gameObject *> activeGameObjects;
        std::vector<std::pair<gameObject*, iFileParser*>> activeInteractions;

        // Interactions are the one dark horse their deletion is handled outside resourceManager because the conent of resource manager are ideally acessed by iFiles
        std::map<std::string, std::pair<gameObject*, iFileParser*>>       interactions;

        std::pair<gameObject*, iFileParser*> LoadInteraction(const char *iFile, gameObject *objectToAffect, std::string name)
        {
        	interactions[name] = {objectToAffect, new iFileParser(iFile)};
        	return interactions[name];
        }


    private:


};
