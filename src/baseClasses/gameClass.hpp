#include "../common/gameObject.hpp"
#include "../common/gameObject3D.hpp"
#include <vector>
// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
}; 

class Game
{
    public:
        SpriteRenderer  *Renderer;
        SpriteRenderer  *TextRenderer;
        ModelRenderer   *Renderer3D;
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
    private:
        std::vector<gameObject *> activeGameObjects;
};
