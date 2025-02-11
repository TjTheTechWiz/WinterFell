
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
	audioSys.SoundPlay(1);

	//Load Texture
	graphicsSys.LoadTextureFromFile("WallTex", "../../../Assets/50x50Brick.png");
	graphicsSys.LoadTextureFromFile("Player1TexNorth", "../../../Assets/P1North.png");
	graphicsSys.LoadTextureFromFile("Player1TexEast", "../../../Assets/P1East.png");
	graphicsSys.LoadTextureFromFile("Player1TexSouth", "../../../Assets/P1South.png");
	graphicsSys.LoadTextureFromFile("Player1TexWest", "../../../Assets/P1West.png");
	graphicsSys.LoadTextureFromFile("Player1TexNortheast", "../../../Assets/P1Northeast.png");
	graphicsSys.LoadTextureFromFile("Player1TexNorthwest", "../../../Assets/P1Northwest.png");
	graphicsSys.LoadTextureFromFile("Player1TexSoutheast", "../../../Assets/P1Southeast.png");
	graphicsSys.LoadTextureFromFile("Player1TexSouthwest", "../../../Assets/P1Southwest.png");
	graphicsSys.LoadTextureFromFile("Player2TexNorth", "../../../Assets/P2North.png");
	graphicsSys.LoadTextureFromFile("Player2TexEast", "../../../Assets/P2East.png");
	graphicsSys.LoadTextureFromFile("Player2TexSouth", "../../../Assets/P2South.png");
	graphicsSys.LoadTextureFromFile("Player2TexWest", "../../../Assets/P2West.png");
	graphicsSys.LoadTextureFromFile("Player2TexNortheast", "../../../Assets/P2Northeast.png");
	graphicsSys.LoadTextureFromFile("Player2TexNorthwest", "../../../Assets/P2Northwest.png");
	graphicsSys.LoadTextureFromFile("Player2TexSoutheast", "../../../Assets/P2Southeast.png");
	graphicsSys.LoadTextureFromFile("Player2TexSouthwest", "../../../Assets/P2Southwest.png");
	graphicsSys.LoadTextureFromFile("BulletTex", "../../../Assets/bullet.png");
	graphicsSys.LoadTextureFromFile("ExplosionTex", "../../../Assets/Explosion.png");
	graphicsSys.LoadTextureFromFile("BeybladeTex", "../../../Assets/Beyblade.png");
	graphicsSys.LoadTextureFromFile("Player1VictoryTex", "../../../Assets/Player1Victory.png");
	graphicsSys.LoadTextureFromFile("Player2VictoryTex", "../../../Assets/Player2Victory.png");

	//Example
	//Instantiate() creates a new GameObject and stores it in an array. Instantiate() returns the index position so you can reference the object later on.
	//Note: It uses a unique pointer so you cannot have multiple references of the same object. So you access the object through allObjects[ObjIndex].get().
	//Instantiate("Ball", "BulletTex", 300, 200, 10, 10); //Creates a new GameObject and since it is the first one its index will be '0'
	//allObjects[getObjIndex["Ball"]].get()->GetPhysicsComponent()->SetVelocity(0.05f, 0.07f); //The GameObject will visually move diagonally. Use GetPhysicsComponent() to access Physics component properties.

	//Making the players
	//TODO: Currently, player 1 and 2 must be the first and second objects created to work. Change to be more modular in the future.

	Instantiate("Player1", "Player1TexNorth", 55, 168, 25, 25, TagType::Player);
	player1Key = "Player1";
	allObjects[getObjIndex["Player1"]].get()->tag = TagType::Player; 
	allObjects[getObjIndex["Player1"]].get()->isEnabled = true;
	initPlayer1Dir.x = 0;
	initPlayer1Dir.y = -1;
	//allObjects[getObjIndex["Player1"]].get()->AddComponent(ComponentType::Transform);

	Instantiate("Player2", "Player2TexNorth", 558, 168, 25, 25, TagType::Player);
	player2Key = "Player2";
	allObjects[getObjIndex["Player2"]].get()->tag = TagType::Player; 
	allObjects[getObjIndex["Player2"]].get()->isEnabled = true;
	initPlayer2Dir.x = 0;
	initPlayer2Dir.y = -1;

	//Create moving hazards
	Instantiate("Hazard A", "BeybladeTex", 190, 160, 50, 50, TagType::Hazard);
	allObjects[getObjIndex["Hazard A"]].get()->tag = TagType::Hazard;

	Instantiate("Hazard B", "BeybladeTex", 410, 160, 50, 50, TagType::Hazard);
	allObjects[getObjIndex["Hazard B"]].get()->tag = TagType::Hazard;

	//Making the walls
	//Use Instantiate(Object name, Texture name, x position, y position, width, height);
	//Note: The origin of a shape is at the top left.
	//Note: The origin of the world is at the top left. Positive x is rightward and positive y is downward.
	//Note: Collision only works with velocity; you can't change position in BlueRapsolEngine::GameUpdate() and expect it to collide.

	for (int i = 0; i < 25; i++) { 
		Instantiate("North Wall " + std::to_string(i), "WallTex", 0 + (i * 25), 0, TagType::Wall); 
		allObjects[getObjIndex["North Wall " + std::to_string(i)]].get()->tag = TagType::Wall;
	}

	for (int i = 0; i < 25; i++) { 
		Instantiate("South Wall " + std::to_string(i), "WallTex", 0 + (i * 25), 325, TagType::Wall);
		allObjects[getObjIndex["South Wall " + std::to_string(i)]].get()->tag = TagType::Wall;
	}

	for (int i = 1; i < 13; i++) { 
		Instantiate("West Wall " + std::to_string(i-1), "WallTex", 0, 0 + (i * 25), TagType::Wall);
		allObjects[getObjIndex["West Wall " + std::to_string(i-1)]].get()->tag = TagType::Wall;
	}
	
	for (int i = 1; i < 13; i++) { 
		Instantiate("East Wall " + std::to_string(i-1), "WallTex", 600, 0 + (i * 25), TagType::Wall);
		allObjects[getObjIndex["East Wall " + std::to_string(i-1)]].get()->tag = TagType::Wall;
	}

	Instantiate("Wall A", "WallTex", 300, 75, TagType::Wall);	
	Instantiate("Wall B", "WallTex", 300, 225, TagType::Wall);  
	Instantiate("Wall C", "WallTex", 300, 250, TagType::Wall);  
	Instantiate("Wall D", "WallTex", 300, 100, TagType::Wall);  
	Instantiate("Wall E", "WallTex", 450, 150, TagType::Wall);  
	Instantiate("Wall F", "WallTex", 450, 175, TagType::Wall);  
	Instantiate("Wall G", "WallTex", 150, 150, TagType::Wall);  
	Instantiate("Wall H", "WallTex", 150, 175, TagType::Wall);  
	Instantiate("Wall I", "WallTex", 225, 125, TagType::Wall);  
	Instantiate("Wall J", "WallTex", 225, 200, TagType::Wall);  
	Instantiate("Wall K", "WallTex", 375, 125, TagType::Wall); 
	Instantiate("Wall L", "WallTex", 375, 200, TagType::Wall); 
	Instantiate("Wall M", "WallTex", 50, 50, TagType::Wall);    
	Instantiate("Wall N", "WallTex", 50, 75, TagType::Wall);    
	Instantiate("Wall O", "WallTex", 50, 100, TagType::Wall);   
	Instantiate("Wall P", "WallTex", 550, 50, TagType::Wall);   
	Instantiate("Wall Q", "WallTex", 550, 75, TagType::Wall);   
	Instantiate("Wall R", "WallTex", 550, 100, TagType::Wall);  
	Instantiate("Wall S", "WallTex", 50, 225, TagType::Wall);   
	Instantiate("Wall T", "WallTex", 50, 250, TagType::Wall);   
	Instantiate("Wall U", "WallTex", 50, 275, TagType::Wall);   
	Instantiate("Wall V", "WallTex", 550, 225, TagType::Wall); 
	Instantiate("Wall W", "WallTex", 550, 250, TagType::Wall);  
	Instantiate("Wall X", "WallTex", 550, 275, TagType::Wall);  
	Instantiate("Wall Y", "WallTex", 125, 25, TagType::Wall);   
	Instantiate("Wall Z", "WallTex", 125, 300, TagType::Wall);  
	Instantiate("Wall AA", "WallTex", 475, 25, TagType::Wall);  
	Instantiate("Wall AB", "WallTex", 475, 300, TagType::Wall); 
	Instantiate("Wall AC", "WallTex", 125, 50, TagType::Wall);  
	Instantiate("Wall AD", "WallTex", 125, 75, TagType::Wall);  
	Instantiate("Wall AE", "WallTex", 475, 250, TagType::Wall); 
	Instantiate("Wall AF", "WallTex", 475, 275, TagType::Wall); 
	Instantiate("Wall AG", "WallTex", 175, 250, TagType::Wall);
	Instantiate("Wall AH", "WallTex", 200, 250, TagType::Wall); 
	Instantiate("Wall AI", "WallTex", 400, 75, TagType::Wall);  
	Instantiate("Wall AJ", "WallTex", 425, 75, TagType::Wall);  
	Instantiate("Wall AK", "WallTex", 200, 50, TagType::Wall);  
	Instantiate("Wall AL", "WallTex", 400, 275, TagType::Wall); 
	Instantiate("Wall AM", "WallTex", 350, 25, TagType::Wall);  
	Instantiate("Wall AN", "WallTex", 250, 300, TagType::Wall); 

	//Creating the recycled bullets
	for (int i = 0; i < maxBullets; i++) {
		Instantiate("Bullet " + std::to_string(i), "BulletTex", -100, -100, 20, 20, TagType::Bullet);
		allObjects[allObjects.size() - 1].get()->tag = TagType::Bullet;
		recycledBullets[i] = allObjects.size() - 1;
	}

	//Create victory text
	Instantiate("VictoryText1", "Player1VictoryTex", -600, -600, TagType::Aesthetic);
	Instantiate("VictoryText2", "Player2VictoryTex", -600, -600, TagType::Aesthetic);

	//Debugging Example
	//msg = L"Value of ObjIndex: " + std::to_wstring(ObjIndex) + L"\n";
	//OutputDebugString(msg.c_str());

}

void BlueRapsolApp::GameUpdate() {
	CheckVictory();
	TickCounters();
	CheckInput();

}

void BlueRapsolApp::TickCounters() {
	if (!player1ReadyToFire) {
		player1BulletCooldownTickCounter++;

		if (player1BulletCooldownTickCounter >= bulletCooldownInTicks) {
			player1BulletCooldownTickCounter = 0;
			player1ReadyToFire = true;
		}
	}

	if (!player2ReadyToFire) {
		player2BulletCooldownTickCounter++;

		if (player2BulletCooldownTickCounter >= bulletCooldownInTicks) {
			player2BulletCooldownTickCounter = 0;
			player2ReadyToFire = true;
		}
	}
}

void BlueRapsolApp::CheckVictory() {

	if (player1Victory || player2Victory) {
		return;
	}
	if (allObjects[1].get()->isDestroyed == true) {
		OutputDebugString(L"[Notice] Player 2 Destroyed.\n");
		player1Victory = true;
		PlayerVictory(1);
	}
	else if (allObjects[0].get()->isDestroyed == true) {
		OutputDebugString(L"[Notice] Player 1 Destroyed.\n");
		player2Victory = true;
		PlayerVictory(2);
	}
	
}

void BlueRapsolApp::PlayerVictory(int playerNum) {
	if (playerNum == 1) { //Player 1 Victory
		OutputDebugString(L"[Notice] Player 1 Victory.\n");
		audioSys.SoundPlay(3);
		allObjects[1].get()->GetRenderComponent()->renderObjPtr.get()->setTexture(graphicsSys.textureMap["ExplosionTex"]); 
		allObjects[getObjIndex["VictoryText1"]].get()->GetTransformComponent()->SetPosition(190,50); //Show victory text
	}
	else if (playerNum == 2) { //Player 2 Victory
		OutputDebugString(L"[Notice] Player 2 Victory.\n");
		audioSys.SoundPlay(3);
		allObjects[0].get()->GetRenderComponent()->renderObjPtr.get()->setTexture(graphicsSys.textureMap["ExplosionTex"]);
		allObjects[getObjIndex["VictoryText2"]].get()->GetTransformComponent()->SetPosition(190, 50); //Show victory text
	}
	else { //error
		OutputDebugString(L"[Error] Can't discern victor.\n");
	}
}

void BlueRapsolApp::Rematch() {
	isGameStarted = false;

	//disable players
	allObjects[getObjIndex["Player1"]].get()->isEnabled = false;
	allObjects[getObjIndex["Player2"]].get()->isEnabled = false;

	//stop players and hazards
	allObjects[getObjIndex["Player1"]].get()->GetPhysicsComponent()->SetVelocity(0, 0);
	allObjects[getObjIndex["Player2"]].get()->GetPhysicsComponent()->SetVelocity(0, 0);
	allObjects[getObjIndex["Hazard A"]].get()->GetPhysicsComponent()->SetVelocity(0, 0);
	allObjects[getObjIndex["Hazard B"]].get()->GetPhysicsComponent()->SetVelocity(0, 0);

	//Fix players
	allObjects[getObjIndex["Player1"]].get()->isDestroyed = false;
	allObjects[getObjIndex["Player2"]].get()->isDestroyed = false;

	//Revert sprite
	allObjects[getObjIndex["Player1"]].get()->GetRenderComponent()->renderObjPtr.get()->setTexture(graphicsSys.textureMap["Player1TexNorth"]);
	allObjects[getObjIndex["Player2"]].get()->GetRenderComponent()->renderObjPtr.get()->setTexture(graphicsSys.textureMap["Player2TexNorth"]);

	//Revert positions
	allObjects[getObjIndex["Player1"]].get()->GetTransformComponent()->SetPosition(55, 168);
	allObjects[getObjIndex["Player2"]].get()->GetTransformComponent()->SetPosition(558, 168);
	allObjects[getObjIndex["VictoryText1"]].get()->GetTransformComponent()->SetPosition(-600, -600);
	allObjects[getObjIndex["VictoryText2"]].get()->GetTransformComponent()->SetPosition(-600, -600);
	allObjects[getObjIndex["Hazard A"]].get()->GetTransformComponent()->SetPosition(190, 160);
	allObjects[getObjIndex["Hazard B"]].get()->GetTransformComponent()->SetPosition(410, 160);

	//TODO remove bullets

	//Reset victories
	player1Victory = false;
	player2Victory = false;

	//Reset hazard velocities
	allObjects[getObjIndex["Hazard A"]].get()->GetPhysicsComponent()->SetVelocity(0.7 * hazardSpeed, 0.3 * hazardSpeed);
	allObjects[getObjIndex["Hazard B"]].get()->GetPhysicsComponent()->SetVelocity(0.3 * hazardSpeed, 0.7 * hazardSpeed);

	//reenable players
	allObjects[getObjIndex["Player1"]].get()->isEnabled = true;
	allObjects[getObjIndex["Player2"]].get()->isEnabled = true;

}

void BlueRapsolApp::CheckInput() {
	Vector2 playerDir;

	if ( (player1Victory || player2Victory) && sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		Rematch();
	}

	if (!isGameStarted && isAnyKeyPressed()) {
		isGameStarted = true;
		allObjects[getObjIndex["Hazard A"]].get()->GetPhysicsComponent()->SetVelocity(0.7 * hazardSpeed, 0.3 * hazardSpeed);
		allObjects[getObjIndex["Hazard B"]].get()->GetPhysicsComponent()->SetVelocity(0.3 * hazardSpeed, 0.7 * hazardSpeed);
	}
	else if (!isGameStarted) {
		return;
	}

	//Remember: scene origin is top left, y positive is downwards, x positive is rightwards

	if (allObjects[getObjIndex["Player1"]].get()->isEnabled == true) {

		//Player 1 control
		// Northward
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			playerDir.x = 0;
			playerDir.y = -1;
			initPlayer1Dir = playerDir;
			player1CarDir = CardinalDirection::North;
			SetTexture("Player1", "Player1TexNorth");
		}
		// Northeastward
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			playerDir.x = 0.707;
			playerDir.y = -0.707;
			initPlayer1Dir = playerDir;
			player1CarDir = CardinalDirection::Northeast;
			SetTexture("Player1", "Player1TexNortheast");
		}
		// Eastward
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			playerDir.x = 1;
			playerDir.y = 0;
			initPlayer1Dir = playerDir;
			player1CarDir = CardinalDirection::East;
			SetTexture("Player1", "Player1TexEast");
		}
		// Southeastward
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			playerDir.x = 0.707;
			playerDir.y = 0.707;
			initPlayer1Dir = playerDir;
			player1CarDir = CardinalDirection::Southeast;
			SetTexture("Player1", "Player1TexSoutheast");
		}
		// Southward
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			playerDir.x = 0;
			playerDir.y = 1;
			initPlayer1Dir = playerDir;
			player1CarDir = CardinalDirection::South;
			SetTexture("Player1", "Player1TexSouth");
		}
		// Southwestward
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			playerDir.x = -0.707;
			playerDir.y = 0.707;
			initPlayer1Dir = playerDir;
			player1CarDir = CardinalDirection::Southwest;
			SetTexture("Player1", "Player1TexSouthwest");
		}
		// Westward
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			playerDir.x = -1;
			playerDir.y = 0;
			initPlayer1Dir = playerDir;
			player1CarDir = CardinalDirection::West;
			SetTexture("Player1", "Player1TexWest");
		}
		// Northwestward
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			playerDir.x = -0.707;
			playerDir.y = -0.707;
			initPlayer1Dir = playerDir;
			player1CarDir = CardinalDirection::Northwest;
			SetTexture("Player1", "Player1TexNorthwest");
		}
		else {
			playerDir.x = 0;
			playerDir.y = 0;
		}
		playerDir.x = playerDir.x * playerSpeed;
		playerDir.y = playerDir.y * playerSpeed;
		allObjects[getObjIndex[player1Key]].get()->GetPhysicsComponent()->SetVelocity(playerDir);

		//Shoot bullet
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player1ReadyToFire) {
			OutputDebugString(L"Player 1 Bullet Fired\n");
			audioSys.SoundPlay(2);
			player1ReadyToFire = false;

			//Spawn bullet at the appropriate side outside of the player's hitbox
			if (player1CarDir == CardinalDirection::North) {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[0].get()->GetTransformComponent()->GetPosition().x + 4, allObjects[0].get()->GetTransformComponent()->GetPosition().y - 10);
			}
			else if (player1CarDir == CardinalDirection::Northeast) {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[0].get()->GetTransformComponent()->GetPosition().x + 14, allObjects[0].get()->GetTransformComponent()->GetPosition().y - 6);
			}
			else if (player1CarDir == CardinalDirection::East) {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[0].get()->GetTransformComponent()->GetPosition().x + 14, allObjects[0].get()->GetTransformComponent()->GetPosition().y + 4);
			}
			else if (player1CarDir == CardinalDirection::Southeast) {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[0].get()->GetTransformComponent()->GetPosition().x + 14, allObjects[0].get()->GetTransformComponent()->GetPosition().y + 14);
			}
			else if (player1CarDir == CardinalDirection::South) {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[0].get()->GetTransformComponent()->GetPosition().x + 4, allObjects[0].get()->GetTransformComponent()->GetPosition().y + 14);
			}
			else if (player1CarDir == CardinalDirection::Southwest) {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[0].get()->GetTransformComponent()->GetPosition().x - 6, allObjects[0].get()->GetTransformComponent()->GetPosition().y + 14);
			}
			else if (player1CarDir == CardinalDirection::West) {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[0].get()->GetTransformComponent()->GetPosition().x - 10, allObjects[0].get()->GetTransformComponent()->GetPosition().y + 4);
			}
			else if (player1CarDir == CardinalDirection::Northwest) {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[0].get()->GetTransformComponent()->GetPosition().x - 10, allObjects[0].get()->GetTransformComponent()->GetPosition().y - 10);
			}
			else {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[0].get()->GetTransformComponent()->GetPosition().x + 4, allObjects[0].get()->GetTransformComponent()->GetPosition().y + 4);
			}

			allObjects[recycledBullets[nextBullet]].get()->isEnabled = true;
			allObjects[recycledBullets[nextBullet]].get()->GetPhysicsComponent()->SetVelocity(initPlayer1Dir.x * bulletSpeed, initPlayer1Dir.y * bulletSpeed); //TODO right now bullet speed is tied to player speed, rectify for future when player speed is variable
			//switch next bullet
			if ((nextBullet + 1) >= maxBullets) {
				nextBullet = 0;
			}
			else {
				nextBullet++;
			}
		}
	}

	if (allObjects[getObjIndex["Player2"]].get()->isEnabled == true) {

		//Player 2 control
		// Northward
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			playerDir.x = 0;
			playerDir.y = -1;
			initPlayer2Dir = playerDir;
			player2CarDir = CardinalDirection::North;
			SetTexture("Player2", "Player2TexNorth");
		}
		// Northeastward
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			playerDir.x = 0.707;
			playerDir.y = -0.707;
			initPlayer2Dir = playerDir;
			player2CarDir = CardinalDirection::Northeast;
			SetTexture("Player2", "Player2TexNortheast");
		}
		// Eastward
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			playerDir.x = 1;
			playerDir.y = 0;
			initPlayer2Dir = playerDir;
			player2CarDir = CardinalDirection::East;
			SetTexture("Player2", "Player2TexEast");
		}
		// Southeastward
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			playerDir.x = 0.707;
			playerDir.y = 0.707;
			initPlayer2Dir = playerDir;
			player2CarDir = CardinalDirection::Southeast;
			SetTexture("Player2", "Player2TexSoutheast");
		}
		// Southward
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			playerDir.x = 0;
			playerDir.y = 1;
			initPlayer2Dir = playerDir;
			player2CarDir = CardinalDirection::South;
			SetTexture("Player2", "Player2TexSouth");
		}
		// Southwestward
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			playerDir.x = -0.707;
			playerDir.y = 0.707;
			initPlayer2Dir = playerDir;
			player2CarDir = CardinalDirection::Southwest;
			SetTexture("Player2", "Player2TexSouthwest");
		}
		// Westward
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			playerDir.x = -1;
			playerDir.y = 0;
			initPlayer2Dir = playerDir;
			player2CarDir = CardinalDirection::West;
			SetTexture("Player2", "Player2TexWest");
		}
		// Northwestward
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			playerDir.x = -0.707;
			playerDir.y = -0.707;
			initPlayer2Dir = playerDir;
			player2CarDir = CardinalDirection::Northwest;
			SetTexture("Player2", "Player2TexNorthwest");
		}
		else {
			playerDir.x = 0;
			playerDir.y = 0;
		}
		playerDir.x = playerDir.x * playerSpeed;
		playerDir.y = playerDir.y * playerSpeed;
		allObjects[getObjIndex[player2Key]].get()->GetPhysicsComponent()->SetVelocity(playerDir);

		//Shoot bullet
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && player2ReadyToFire) {
			OutputDebugString(L"Player 2 Bullet Fired\n");
			audioSys.SoundPlay(2);
			player2ReadyToFire = false;

			//Spawn bullet at the appropriate side outside of the player's hitbox
			if (player2CarDir == CardinalDirection::North) {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[1].get()->GetTransformComponent()->GetPosition().x + 4, allObjects[1].get()->GetTransformComponent()->GetPosition().y - 10);
			}
			else if (player2CarDir == CardinalDirection::Northeast) {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[1].get()->GetTransformComponent()->GetPosition().x + 14, allObjects[1].get()->GetTransformComponent()->GetPosition().y - 6);
			}
			else if (player2CarDir == CardinalDirection::East) {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[1].get()->GetTransformComponent()->GetPosition().x + 14, allObjects[1].get()->GetTransformComponent()->GetPosition().y + 4);
			}
			else if (player2CarDir == CardinalDirection::Southeast) {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[1].get()->GetTransformComponent()->GetPosition().x + 14, allObjects[1].get()->GetTransformComponent()->GetPosition().y + 14);
			}
			else if (player2CarDir == CardinalDirection::South) {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[1].get()->GetTransformComponent()->GetPosition().x + 4, allObjects[1].get()->GetTransformComponent()->GetPosition().y + 14);
			}
			else if (player2CarDir == CardinalDirection::Southwest) {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[1].get()->GetTransformComponent()->GetPosition().x - 6, allObjects[1].get()->GetTransformComponent()->GetPosition().y + 14);
			}
			else if (player2CarDir == CardinalDirection::West) {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[1].get()->GetTransformComponent()->GetPosition().x - 10, allObjects[1].get()->GetTransformComponent()->GetPosition().y + 4);
			}
			else if (player2CarDir == CardinalDirection::Northwest) {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[1].get()->GetTransformComponent()->GetPosition().x - 10, allObjects[1].get()->GetTransformComponent()->GetPosition().y - 10);
			}
			else {
				allObjects[recycledBullets[nextBullet]].get()->GetTransformComponent()->SetPosition(allObjects[1].get()->GetTransformComponent()->GetPosition().x + 4, allObjects[1].get()->GetTransformComponent()->GetPosition().y + 4);
			}

			allObjects[recycledBullets[nextBullet]].get()->isEnabled = true;
			allObjects[recycledBullets[nextBullet]].get()->GetPhysicsComponent()->SetVelocity(initPlayer2Dir.x * bulletSpeed, initPlayer2Dir.y * bulletSpeed); //right now bullet direction is tied to player direction
			//switch next bullet
			if ((nextBullet + 1) >= maxBullets) {
				nextBullet = 0;
			}
			else {
				nextBullet++;
			}
		}
	}
}

bool BlueRapsolApp::isAnyKeyPressed(){
	for (int k = -1; k < sf::Keyboard::KeyCount; ++k){
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k)))
			return true;
	}
	return false;
}
