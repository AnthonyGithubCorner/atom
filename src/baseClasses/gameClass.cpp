#include "gameClass.hpp"
#include "../common/resourceManager.hpp"
#include "../load_asset/loadAsset.hpp"
#include <filesystem>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <SDL.h>
#include <fstream>
#include "../json/json.hpp"
#include "../interactionFile/actionLoader.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;
glm::mat4 proj = glm::ortho(0.0f, 1.0f, 1.0f, 0.0f, -255.0f, 0.0f);
//glm::mat4 proj = glm::frustum(0.0f, 1.0f, 1.0f, 0.0f, -10000.0f, -255.0f);

void Game::parse_sprite_data(std::string data_path){

		std::ifstream spirte_file(data_path + "/data.json");
	    if (spirte_file.fail())
	    {
	        SDL_Log("json data file not found");
	        return;
	    }

	    json sprite_data = json::parse(spirte_file);
//	    std::string tile_char_path;
//	    SDL_Texture *tile_texture;
	    std::string name = sprite_data["name"];

//	    ResourceManager::LoadShader((data_path + "/vertex").c_str(), (data_path + "/fragment").c_str(), nullptr, name.c_str());
//	    ResourceManager::GetShader(name.c_str()).Use().SetInteger("image", 0);
//
//
	     ResourceManager::GetShader(name.c_str()).SetMatrix4("projection", proj);
	     Shader myShader = ResourceManager::GetShader("sprite");
		 std::string type = sprite_data["type"];
		 SDL_FRect pos = {0.0f};
		 pos.x = sprite_data["x"];
		 pos.y = sprite_data["y"];
		 pos.w = sprite_data["w"];
		 pos.h = sprite_data["h"];

		 SDL_FRect trigRect = {0.0f};
		 if(sprite_data.contains("trigger"))
				 {
			 trigRect.x = sprite_data["trigger"]["x"];
			 trigRect.y = sprite_data["trigger"]["y"];
			 trigRect.w = sprite_data["trigger"]["w"];
			 trigRect.h = sprite_data["trigger"]["h"];
				 }

		 uint8_t level = sprite_data["level"];
		 bool anim = sprite_data["anim"];
	   ModelRenderer* DRenderer = ResourceManager::LoadModelRenderer(myShader, (data_path + "/" + name + ".obj").c_str(), name);
	   gameObject *newGo;
	   bool isUI = false;
	   if(type == "UI")
	   {
		   isUI = true;
	   }
	   if(anim)
	   {
	   std::map<std::string, std::vector<ModelRenderer*>> model_animations;

	   for (const auto& entry : fs::directory_iterator(data_path + "/anim"))
	   {

	           // Converting the path to const char * in the
	           // subsequent lines
	           std::filesystem::path outfilename = entry.path();
	           std::string outfilename_str = outfilename.string();
//	           const char* path = outfilename_str.c_str();
				std::ifstream anim_file(outfilename_str + "/anim.json");
				if (anim_file.fail())
				{
					SDL_Log("anim json data file not found");
					return;
				}

				json anim_data = json::parse(anim_file);
			    std::string anim_name = anim_data["name"];
			    int anim_num = 1;
			    char buffer[7];
			    // loop through each object only to find the number! of animations disregard the actual file names
	    	   for (const auto& entry : fs::directory_iterator(outfilename_str))
	    	   {
		           std::filesystem::path suboutfilename = entry.path();
		           std::string suboutfilename_str = suboutfilename.string();

		           // Testing whether the path points to a object file
		           if(suboutfilename_str.substr(suboutfilename_str.size() - 4, suboutfilename_str.size()) == ".obj")
		           {
			           snprintf (buffer, 7, "%06d", anim_num);
				       std::string s(buffer);

				       // remove numbers
			           suboutfilename_str.erase(suboutfilename_str.size() - 10, suboutfilename_str.size());

			           // path name + num 6 digits liuke blender + .obj
			           suboutfilename_str = suboutfilename_str + s + ".obj";

		        	   model_animations[anim_name].push_back(ResourceManager::LoadModelRenderer(myShader, suboutfilename_str.c_str(), anim_name + std::to_string(anim_num)));
		        	   anim_num++;
		           }
	    	   }

	   }
	   newGo = ResourceManager::LoadGameObject(DRenderer, model_animations, (data_path + "/" + name + ".png").c_str(), false,name.c_str(), pos, level, trigRect);
	   activeGameObjects.push_back(newGo);
	   }

	   else
	   {
	   newGo = ResourceManager::LoadGameObject(DRenderer,(data_path + "/" + name + ".png").c_str(), false,name.c_str(), pos, level);
	   activeGameObjects.push_back(newGo);
	   }
	   activeInteractions.push_back(LoadInteraction((data_path + "/" + name + ".i").c_str(), newGo, name));
//	    for (auto &sprite_tile : sprite_data["buildings"].items()){
//	        tile_char_path = sprite_tile.value()["file"];
//	    }
}


Game::Game(unsigned int width, unsigned int height) 
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{ 

}



Game::~Game()
{
    for (auto iter : interactions)
        delete (iter.second.second);
    delete Renderer;
}
  
void Game::Init()
{
    glEnable(GL_DEPTH_TEST);
    // This structure would distinguish a file from a
     // directory
     struct stat sb;

     // Init all the interaction File Functions
     actionLoader::registerAllActions();

     // Looping until all the items of the directory are
     // exhausted
     ResourceManager::LoadShader(load_asset("vertex").c_str(), load_asset("fragment").c_str(), nullptr, "sprite");
     // configure shaders
 //
     ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
     ResourceManager::GetShader("sprite").SetMatrix4("projection", proj);
     glm::mat4 view = glm::mat4(1.0f);
//     view = glm::translate(view, glm::vec3(0.5f,0.0f,0.0f));
     ResourceManager::GetShader("sprite").SetMatrix4("view", view);
     // set render-specific controls
     Shader myShader;
     myShader = ResourceManager::GetShader("sprite");
     for (const auto& entry : fs::directory_iterator(load_asset("/gameobjects"))) {

         // Converting the path to const char * in the
         // subsequent lines
         std::filesystem::path outfilename = entry.path();
         std::string outfilename_str = outfilename.string();
         const char* path = outfilename_str.c_str();

         // Testing whether the path points to a
         // non-directory or not If it does, displays path
         if(outfilename_str.substr(outfilename_str.size() - 2, outfilename_str.size()) == "go"){
	         	 parse_sprite_data(outfilename_str);
        	  }
         }
//         if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR))
//        	 SDL_Log("thing: %s", path);

//    // load shaders

    Renderer = new ModelRenderer(myShader, load_asset("2D.obj").c_str());
//
//    ResourceManager::LoadShader(load_asset("/shaders/model/vertexshader.vertex").c_str(), load_asset("/shaders/model/fragmentShader.fragment").c_str(), nullptr, "model");
//    ResourceManager::GetShader("model").Use().SetInteger("image", 0);
//
//    ResourceManager::GetShader("model").SetMatrix4("projection", proj);
//    myShader = ResourceManager::GetShader("model");
//    ModelRenderer* PlayerRender = new ModelRenderer(myShader, "player.obj");
//    glm::vec3 cameraPos = glm::vec3( 0, 0.0f, 100 );
//    float horizontalAngle = 3.14f;
//    // vertical angle : 0, look at the horizon
//    float verticalAngle = 0.0f;
//    // Initial Field of View
//    // Right vector
//    glm::vec3 right = glm::vec3(
//        sin(horizontalAngle - 3.14f/2.0f),
//        0,
//        cos(horizontalAngle - 3.14f/2.0f)
//    );
//    glm::vec3 direction(
//        cos(verticalAngle) * sin(horizontalAngle),
//        sin(verticalAngle),
//        cos(verticalAngle) * cos(horizontalAngle)
//    );
//
//    glm::vec3 up = glm::cross( right, direction );
//    glm::mat4 view = glm::lookAt(
//    cameraPos,
//    cameraPos+direction,
//    up);

//    ResourceManager::GetShader("sprite").SetMatrix4("view", view);
    // load textures
//    ResourceManager::LoadGameObject(Renderer, load_asset("/gameWallpaper1.png").c_str(),false,"bg", {0,0,2.0f,1.2f});
//    ResourceManager::LoadGameObject(Renderer,load_asset("/awesomeface.png").c_str(),true,"face", {0.1f,0.1f,0.1f,0.1f});
    ResourceManager::LoadGameObject(Renderer,load_asset("/textBox.png").c_str(),true,"textBox", {0.1f,0.1f,0.1f,0.1f}, 254);

    SDL_Color black;
    black.a = 0;
    black.r = 0;
    black.g = 0;
    black.b = 0;
    ResourceManager::LoadWordRenderer(Renderer, load_asset("/andaleAtlas.png").c_str(), true, "andaleInfo", 16, black);

    SDL_Color purple;
	purple.a = 0;
	purple.r = 100;
	purple.g = 0;
	purple.b = 100;

    ResourceManager::LoadWordRenderer(Renderer, load_asset("/andaleAtlas.png").c_str(), true, "andaleInfoPurple", 16, purple);

	SDL_Color red;
	red.a = 0;
	red.r = 200;
	red.g = 0;
	red.b = 0;

    ResourceManager::LoadWordRenderer(Renderer, load_asset("/andaleAtlas.png").c_str(), true, "andaleInfoRed", 16, red);

    ResourceManager::LoadDialogue(load_asset("/dialogue/idea.txt").c_str(), "test_idea");

    ResourceManager::LoadSound(load_asset("/sounds/hold-it.mp3").c_str(), "holdIt");

    ResourceManager::LoadMusic(load_asset("/song.mp3").c_str(), "testSong");

//    ResourceManager::LoadGameObject(Renderer,load_asset("/frogGuy.png").c_str(),true,"frog", {0.3f,0.1f,0.4f, 0.4f});
//
//    // load models
//    ResourceManager::LoadGameObject3D(PlayerRender, load_asset("/cowboy.png").c_str(), true, "testModel", {0.5f,0.5f,0.3f, 0.3f});


}

void Game::Update(float dt)
{
    
}

void Game::ProcessInput(float dt)
{
   
}

void Game::Render()
{
    for(auto o: ResourceManager::gameObjects){
        o.second->Render();
    }
} 
