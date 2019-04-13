#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem() {

}

void PhysicsSystem::UpdatePhysics() {

}

//TODO: Diameter is divided by 4 instead of 2 because apparently shape size in pixels differ in measurement from scene positions
void PhysicsSystem::UpdatePhysics(const std::vector<std::unique_ptr<GameObject>>& getObjRef, int player1Index, int player2Index) {
	std::wstring msg;

	sf::Vector2f newPosition;

	Vector2 playerVelocityHolder;
	Vector2 objVelocityHolder;
	Vector2 bulletVelocityHolder;

	BRDataType::AABB playerBounds;
	BRDataType::AABB wallBounds;
	BRDataType::AABB bulletBounds;

	float widthHolder;
	float heightHolder;
	float collisionPadding = 1; //must be higher than velocity value to work
	int startingIndexA = 0;
	int startingIndexB = 1;

	//Only compare players to walls
	//TODO change index from starting at 2 when player index will be variable in the future
	for (int i = 2; i < getObjRef.size(); i++) {

		//Skip object if it's not a wall
		if (getObjRef[i].get()->isWall == true || getObjRef[i].get()->isProjectile == true) {

			//Establish obj bounds and velocity
			widthHolder = abs(getObjRef[i].get()->GetPhysicsComponent()->GetBounds().min.x - getObjRef[i].get()->GetPhysicsComponent()->GetBounds().max.x) / 2;
			heightHolder = abs(getObjRef[i].get()->GetPhysicsComponent()->GetBounds().min.y - getObjRef[i].get()->GetPhysicsComponent()->GetBounds().max.y) / 2;

			wallBounds.min.x = getObjRef[i].get()->GetTransformComponent()->GetPosition().x;
			wallBounds.max.x = getObjRef[i].get()->GetTransformComponent()->GetPosition().x + widthHolder;
			wallBounds.min.y = getObjRef[i].get()->GetTransformComponent()->GetPosition().y + heightHolder; //Note: Remember, In this case Y positive is downwards
			wallBounds.max.y = getObjRef[i].get()->GetTransformComponent()->GetPosition().y; //and Y negative is upwards

			objVelocityHolder.x = getObjRef[i].get()->GetPhysicsComponent()->GetVelocity().x;
			objVelocityHolder.y = getObjRef[i].get()->GetPhysicsComponent()->GetVelocity().y;

			//Test player 1
			widthHolder = abs(getObjRef[0].get()->GetPhysicsComponent()->GetBounds().min.x - getObjRef[0].get()->GetPhysicsComponent()->GetBounds().max.x) / 2;
			heightHolder = abs(getObjRef[0].get()->GetPhysicsComponent()->GetBounds().min.y - getObjRef[0].get()->GetPhysicsComponent()->GetBounds().max.y) / 2;

			playerBounds.min.x = getObjRef[0].get()->GetTransformComponent()->GetPosition().x;
			playerBounds.max.x = getObjRef[0].get()->GetTransformComponent()->GetPosition().x + widthHolder;
			playerBounds.min.y = getObjRef[0].get()->GetTransformComponent()->GetPosition().y + heightHolder; //Note: Remember, In this case Y positive is downwards
			playerBounds.max.y = getObjRef[0].get()->GetTransformComponent()->GetPosition().y; //and Y negative is upwards

			playerVelocityHolder.x = getObjRef[0].get()->GetPhysicsComponent()->GetVelocity().x;
			playerVelocityHolder.y = getObjRef[0].get()->GetPhysicsComponent()->GetVelocity().y;

			//Check if there is overlap and that player 1 is moving velocity wise
			if (TestAABBOverlap(&playerBounds, &wallBounds) && !(playerVelocityHolder.x == 0 && playerVelocityHolder.y == 0 && objVelocityHolder.x == 0 && objVelocityHolder.y == 0) ) {

				//Prevent going further upon collision
				if ((playerBounds.max.x > wallBounds.min.x) && (playerBounds.max.x < wallBounds.min.x + collisionPadding)) { // Player collides with Wall from left
					OutputDebugString(L"[Notice] Player 1 collides with object from left.\n");
					if (getObjRef[i].get()->isWall && playerVelocityHolder.x > 0) { //prevent player 1 from moving further
						getObjRef[0].get()->GetPhysicsComponent()->SetVelocity(0, playerVelocityHolder.y);
					}
				
					//else allow current velocity
				}
				else if ((playerBounds.min.x < wallBounds.max.x) && (playerBounds.min.x > wallBounds.max.x - collisionPadding)) { // Player collides with Wall from right
					OutputDebugString(L"[Notice] Player 1 collides with object from right.\n");
					if (getObjRef[i].get()->isWall && playerVelocityHolder.x < 0) { //prevent player 1 from moving further
						getObjRef[0].get()->GetPhysicsComponent()->SetVelocity(0, playerVelocityHolder.y);
					}

					//else allow current velocity
				}
				else if ((playerBounds.max.y < wallBounds.min.y) && (playerBounds.max.y > wallBounds.min.y - collisionPadding)) { // Player collides with Wall from below
					OutputDebugString(L"[Notice] Player 1 collides with object from below.\n");
					if (getObjRef[i].get()->isWall && playerVelocityHolder.y < 0) { //prevent player 1 from moving further
						getObjRef[0].get()->GetPhysicsComponent()->SetVelocity(playerVelocityHolder.x, 0);
					}
					//else allow current velocity
				}
				else if ((playerBounds.min.y > wallBounds.max.y) && (playerBounds.min.y < wallBounds.max.y + collisionPadding)) { // Player collides with Wall from above
					OutputDebugString(L"[Notice] Player 1 collides with object from above.\n");
					if (getObjRef[i].get()->isWall && playerVelocityHolder.y > 0) { //prevent player 1 from moving further
						getObjRef[0].get()->GetPhysicsComponent()->SetVelocity(playerVelocityHolder.x, 0);
					}
					//else allow current velocity
				}

				if (getObjRef[i].get()->isProjectile) { //player death
					getObjRef[i].get()->isEnabled = false; //Disable the bullet
					getObjRef[i].get()->GetPhysicsComponent()->SetVelocity(0, 0); //Stop the bullet
					getObjRef[i].get()->GetTransformComponent()->SetPosition(-100, -100); //Hide the bullet away from the stage
				}
			}

			//Test player 2
			widthHolder = abs(getObjRef[1].get()->GetPhysicsComponent()->GetBounds().min.x - getObjRef[1].get()->GetPhysicsComponent()->GetBounds().max.x) / 2;
			heightHolder = abs(getObjRef[1].get()->GetPhysicsComponent()->GetBounds().min.y - getObjRef[1].get()->GetPhysicsComponent()->GetBounds().max.y) / 2;

			playerBounds.min.x = getObjRef[1].get()->GetTransformComponent()->GetPosition().x;
			playerBounds.max.x = getObjRef[1].get()->GetTransformComponent()->GetPosition().x + widthHolder;
			playerBounds.min.y = getObjRef[1].get()->GetTransformComponent()->GetPosition().y + heightHolder; //Note: Remember, In this case Y positive is downwards
			playerBounds.max.y = getObjRef[1].get()->GetTransformComponent()->GetPosition().y; //and Y negative is upwards

			playerVelocityHolder.x = getObjRef[1].get()->GetPhysicsComponent()->GetVelocity().x;
			playerVelocityHolder.y = getObjRef[1].get()->GetPhysicsComponent()->GetVelocity().y;

			//Check if there is overlap and that player 2 is moving velocity wise
			if (TestAABBOverlap(&playerBounds, &wallBounds)
				&& !(playerVelocityHolder.x == 0 && playerVelocityHolder.y == 0)) {

				//Prevent going further upon collision
				if ((playerBounds.max.x > wallBounds.min.x) && (playerBounds.max.x < wallBounds.min.x + collisionPadding)) { // Player collides with Wall from left
					OutputDebugString(L"[Notice] Horiontal Collision detected.\n");
					if (getObjRef[i].get()->isWall && playerVelocityHolder.x > 0) { //prevent player 1 from moving further
						getObjRef[1].get()->GetPhysicsComponent()->SetVelocity(0, playerVelocityHolder.y);
					}
					//else allow current velocity
				}
				else if ((playerBounds.min.x < wallBounds.max.x) && (playerBounds.min.x > wallBounds.max.x - collisionPadding)) { // Player collides with Wall from right
					OutputDebugString(L"[Notice] Horiontal Collision detected.\n");
					if (getObjRef[i].get()->isWall && playerVelocityHolder.x < 0) { //prevent player 1 from moving further
						getObjRef[1].get()->GetPhysicsComponent()->SetVelocity(0, playerVelocityHolder.y);
					}
					//else allow current velocity
				}
				else if ((playerBounds.max.y < wallBounds.min.y) && (playerBounds.max.y > wallBounds.min.y - collisionPadding)) { // Player collides with Wall from below
					OutputDebugString(L"[Notice] Vertical Collision detected.\n");
					if (getObjRef[i].get()->isWall && playerVelocityHolder.y < 0) { //prevent player 1 from moving further
						getObjRef[1].get()->GetPhysicsComponent()->SetVelocity(playerVelocityHolder.x, 0);
					}
					//else allow current velocity
				}
				else if ((playerBounds.min.y > wallBounds.max.y) && (playerBounds.min.y < wallBounds.max.y + collisionPadding)) { // Player collides with Wall from above
					OutputDebugString(L"[Notice] Vertical Collision detected.\n");
					if (getObjRef[i].get()->isWall && playerVelocityHolder.y > 0) { //prevent player 1 from moving further
						getObjRef[1].get()->GetPhysicsComponent()->SetVelocity(playerVelocityHolder.x, 0);
					}
					//else allow current velocity
				}

				if (getObjRef[i].get()->isProjectile) { //player death
					getObjRef[i].get()->isEnabled = false; //Disable the bullet
					getObjRef[i].get()->GetPhysicsComponent()->SetVelocity(0, 0); //Stop the bullet
					getObjRef[i].get()->GetTransformComponent()->SetPosition(-100, -100); //Hide the bullet away from the stage
				}
			}
		}


	}

	//handle bullet collision on walls
	//TODO make more elegant
	for (int ia = 0; ia < getObjRef.size(); ia++) {
		if (getObjRef[ia].get()->isProjectile == true && getObjRef[ia].get()->isEnabled) { //if object is bullet and is enabled

			for (int ib = 0; ib < getObjRef.size(); ib++) {
				if (getObjRef[ib].get()->isWall == true) { //if object is wall
					//Establish wall bounds and velocity
					widthHolder = abs(getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().min.x - getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().max.x) / 2;
					heightHolder = abs(getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().min.y - getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().max.y) / 2;

					wallBounds.min.x = getObjRef[ib].get()->GetTransformComponent()->GetPosition().x;
					wallBounds.max.x = getObjRef[ib].get()->GetTransformComponent()->GetPosition().x + widthHolder;
					wallBounds.min.y = getObjRef[ib].get()->GetTransformComponent()->GetPosition().y + heightHolder; //Note: Remember, In this case Y positive is downwards
					wallBounds.max.y = getObjRef[ib].get()->GetTransformComponent()->GetPosition().y; //and Y negative is upwards

					objVelocityHolder.x = getObjRef[ib].get()->GetPhysicsComponent()->GetVelocity().x;
					objVelocityHolder.y = getObjRef[ib].get()->GetPhysicsComponent()->GetVelocity().y;

					//Establish bullet bounds and velocity
					widthHolder = abs(getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().min.x - getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().max.x) / 2;
					heightHolder = abs(getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().min.y - getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().max.y) / 2;

					bulletBounds.min.x = getObjRef[ia].get()->GetTransformComponent()->GetPosition().x;
					bulletBounds.max.x = getObjRef[ia].get()->GetTransformComponent()->GetPosition().x + widthHolder;
					bulletBounds.min.y = getObjRef[ia].get()->GetTransformComponent()->GetPosition().y + heightHolder; //Note: Remember, In this case Y positive is downwards
					bulletBounds.max.y = getObjRef[ia].get()->GetTransformComponent()->GetPosition().y; //and Y negative is upwards

					bulletVelocityHolder.x = getObjRef[ia].get()->GetPhysicsComponent()->GetVelocity().x;
					bulletVelocityHolder.y = getObjRef[ia].get()->GetPhysicsComponent()->GetVelocity().y;

					//Check if there is overlap 
					if (TestAABBOverlap(&bulletBounds, &wallBounds)) {
						getObjRef[ia].get()->isEnabled = false; //Disable the bullet
						getObjRef[ia].get()->GetPhysicsComponent()->SetVelocity(0, 0); //Stop the bullet
						getObjRef[ia].get()->GetTransformComponent()->SetPosition(-100, -100); //Hide the bullet away from the stage

						//exit loop
						ib = getObjRef.size(); //redundancy in case break; doesnt work properly
						break;
					}

				}
			}
		}
	}

	//Loops through Objects and change their position based on velocity. We just add velocity to position.
	for (auto& obj : getObjRef) {
		newPosition.x = obj.get()->GetTransformComponent()->GetPosition().x + obj.get()->GetPhysicsComponent()->GetVelocity().x;
		newPosition.y = obj.get()->GetTransformComponent()->GetPosition().y + obj.get()->GetPhysicsComponent()->GetVelocity().y;
		obj.get()->GetTransformComponent()->SetPosition(newPosition);
	}

}

//check if object bounds collide
//Note: In this case the origin is at the top left of the screen, rightward is x positive, downward is y positive.
bool PhysicsSystem::TestAABBOverlap(AABB* a, AABB* b) {

	if ( (a->max.x > b->min.x && a->max.x <= b->max.x) || (a->min.x < b->max.x && a->min.x >= b->min.x) ) { //Check Horizontal overlap
		//OutputDebugString(L"[Notice] Horiontal Overlap detected.\n");

		if ( (a->max.y < b->min.y && a->max.y >= b->max.y) || (a->min.y > b->max.y && a->min.y <= b->min.y)) { //Check Vertical overlap. Note: Remember, In this case Y positive is downwards and Y negative is upwards
			//OutputDebugString(L"[Notice] Vertical Overlap detected.\n");
			return TRUE;
		}
	}

	return FALSE;
}

//Change object velocity to simulate deflection upon collision
void PhysicsSystem::DeflectObj(PhysicsComponent* physComponentRef, AxisType collisionType) {
	//Note: deflecting an object with(0, 0) velocity will not apply changes because anything multiplied by 0 is 0.

	if (collisionType == Diagonal) { //Diagonal
		physComponentRef->SetVelocity(physComponentRef->GetVelocity().x * -1, physComponentRef->GetVelocity().y * -1);
	}
	else if (collisionType == Vertical) { //Vertical
		physComponentRef->SetVelocity(physComponentRef->GetVelocity().x, physComponentRef->GetVelocity().y * -1);
	}
	else if (collisionType == Horizontal) { //Horizontal
		physComponentRef->SetVelocity(physComponentRef->GetVelocity().x * -1, physComponentRef->GetVelocity().y);
	}
}
