#include "Game.h"
#include "Camera.h"

Game::Game()
{
	live_ = std::make_unique<Live>();
}

void Game::Initialize(Camera* camera)
{
	live_->Initialize(camera);
}

void Game::Update()
{

}

void Game::Draw(Camera* camera)
{
	
}


