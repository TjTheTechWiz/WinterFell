
#include "BlueRapsolApp.h"

BlueRapsolApp::BlueRapsolApp(HINSTANCE hInstance) : BlueRapsolEngine::BlueRapsolEngine(hInstance){

}

bool BlueRapsolApp::Initialize() {
	//Insure it is the only instance
	if (!IsOnlyInstance(MUTEX_APP_NAME)) {
		return false;
	}

	return true;
}

void BlueRapsolApp::GameStart() {
	std::wstring msg; //Used for formatting debug messages
	int ObjIndex;
	//Load Sound
	audioSys.LoadBuffer();

	//Play Sound
	//audioSys.SoundPlay();

	//Load Texture
	graphicsSys.LoadTextureFromFile("WallTex", "../../../Assets/50x50Brick.png");
	graphicsSys.LoadTextureFromFile("Player1TexNorth", "../../../Assets/P1North.png");
	graphicsSys.LoadTextureFromFile("Player2TexNorth", "../../../Assets/P2North.png");
	graphicsSys.LoadTextureFromFile("BulletTex", "../../../Assets/bullet.png");

	//Example
	//Instantiate() creates a new GameObject and stores it in an array. Instantiate() returns the index position so you can reference the object later on.
	//Note: It uses a unique pointer so you cannot have multiple references of the same object. So you access the object through allObjects[ObjIndex].get().
	//Instantiate("Ball", "BulletTex", 300, 200, 10, 10); //Creates a new GameObject and since it is the first one its index will be '0'
	//allObjects[getObjIndex["Ball"]].get()->GetPhysicsComponent()->SetVelocity(0.05f, 0.07f); //The GameObject will visually move diagonally. Use GetPhysicsComponent() to access Physics component properties.


	//Making the players
	//TODO: Currently, player 1 and 2 must be the first and second objects created to work. Change to be more modular in the future.

	Instantiate("Player1", "Player1TexNorth", 150, 150, 25, 25);
	player1Key = "Player1";
	allObjects[getObjIndex["Player1"]].get()->isPlayer = true; //TEMP until ControllableComponent is implemented and tested.

	Instantiate("Player2", "Player2TexNorth", 200, 150, 25, 25);
	player2Key = "Player2";
	allObjects[getObjIndex["Player2"]].get()->isPlayer = true; //TEMP until ControllableComponent is implemented and tested.

	//Making the walls
	//Use Instantiate(Object name, Texture name, x position, y position, width, height);
	//Note: The origin of a shape is at the top left.
	//Note: The origin of the world is at the top left. Positive x is rightward and positive y is downward.
	//Note: Collision only works with velocity; you can't change position in BlueRapsolEngine::GameUpdate() and expect it to collide.

	for (int i = 0; i < 25; i++) {
		Instantiate("North Wall " + std::to_string(i), "WallTex", 0 + (i * 25), 0); 
		allObjects[getObjIndex["North Wall " + std::to_string(i)]].get()->isWall = true;
	}

	for (int i = 0; i < 25; i++) {
		Instantiate("South Wall " + std::to_string(i), "WallTex", 0 + (i * 25), 325);
		allObjects[getObjIndex["South Wall " + std::to_string(i)]].get()->isWall = true;
	}

	for (int i = 1; i < 13; i++) {
		Instantiate("West Wall " + std::to_string(i-1), "WallTex", 0, 0 + (i * 25));
		allObjects[getObjIndex["West Wall " + std::to_string(i-1)]].get()->isWall = true;
	}

	for (int i = 1; i < 13; i++) {
		Instantiate("East Wall " + std::to_string(i-1), "WallTex", 600, 0 + (i * 25));
		allObjects[getObjIndex["East Wall " + std::to_string(i-1)]].get()->isWall = true;
	}
	//Instantiate("Wall A", "WallTex", 450, 0); //Creates a second new GameObject and since it is the second one its index will be '1'
	//Instantiate("Wall B", "WallTex", 325, 275); //its index will be '2'
	//Instantiate("Wall C", "WallTex", 300, 275); //its index will be '3'
	//Instantiate("Wall D", "WallTex", 500, 50); //its index will be '4'

	

	//Debugging Example
	//msg = L"Value of ObjIndex: " + std::to_wstring(ObjIndex) + L"\n";
	//OutputDebugString(msg.c_str());
}

void BlueRapsolApp::GameUpdate() {

	CheckInput();

	//Example
	//This moves our second created object (index 1) towards the right by 0.2f every tick
	//float newPositionX = allObjects[1].get()->GetTransformComponent()->GetPosition().x + 0.05f; //The original x position + 0.2f
	//float newPositionY = allObjects[1].get()->GetTransformComponent()->GetPosition().y; //The original y position doesnt change
	//allObjects[1].get()->GetTransformComponent()->SetPosition(newPositionX, newPositionY); //We pass the values to the object with SetPosition()

}

void BlueRapsolApp::CheckInput() {
	Vector2 playerDir;

	//TODO Check if player 1's object exist
	if (false) {
		return;
	}

	//Remember: scene origin is top left, y positive is downwards, x positive is rightwards

	//Player 1 control
	// Northward
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerDir.x = 0;
		playerDir.y = -1;
	}
	// Northeastward
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerDir.x = 0.707;
		playerDir.y = -0.707;
	}
	// Eastward
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerDir.x = 1;
		playerDir.y = 0;
	}
	// Southeastward
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerDir.x = 0.707;
		playerDir.y = 0.707;
	}
	// Southward
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerDir.x = 0;
		playerDir.y = 1;
	}
	// Southwestward
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerDir.x = -0.707;
		playerDir.y = 0.707;
	}
	// Westward
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerDir.x = -1;
		playerDir.y = 0;
	}
	// Northwestward
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerDir.x = -0.707;
		playerDir.y = -0.707;
	}
	else {
		playerDir.x = 0;
		playerDir.y = 0;
	}
	playerDir.x = playerDir.x * 0.05;
	playerDir.y = playerDir.y * 0.05;
	allObjects[getObjIndex[player1Key]].get()->GetPhysicsComponent()->SetVelocity(playerDir);


	//TODO Check if player 2's object exist
	if (false) {
		return;
	}

	//Player 2 control
	// Northward
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		playerDir.x = 0;
		playerDir.y = -1;
	}
	// Northeastward
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		playerDir.x = 0.707;
		playerDir.y = -0.707;
	}
	// Eastward
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		playerDir.x = 1;
		playerDir.y = 0;
	}
	// Southeastward
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		playerDir.x = 0.707;
		playerDir.y = 0.707;
	}
	// Southward
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		playerDir.x = 0;
		playerDir.y = 1;
	}
	// Southwestward
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		playerDir.x = -0.707;
		playerDir.y = 0.707;
	}
	// Westward
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		playerDir.x = -1;
		playerDir.y = 0;
	}
	// Northwestward
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		playerDir.x = -0.707;
		playerDir.y = -0.707;
	}
	else {
		playerDir.x = 0;
		playerDir.y = 0;
	}
	playerDir.x = playerDir.x * 0.05;
	playerDir.y = playerDir.y * 0.05;
	allObjects[getObjIndex[player2Key]].get()->GetPhysicsComponent()->SetVelocity(playerDir);
}
