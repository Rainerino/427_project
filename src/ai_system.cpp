// internal
#include "ai_system.hpp"
#include "world_init.hpp"


void AISystem::step(int height)
{
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// TODO A2: HANDLE FISH AI HERE
	// DON'T WORRY ABOUT THIS UNTIL ASSIGNMENT 2
	// You will likely want to write new functions and need to create
	// new data structures to implement a more sophisticated Fish AI.
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//(void)elapsed_ms; // placeholder to silence unused warning until implemented
	ComponentContainer<Motion>& motion_container = registry.motions;
	Entity player = registry.players.entities[0];
	Motion& player_m = registry.motions.get(player);
	for (uint i = 0; i < motion_container.components.size(); i++)
	{
		Motion& motion_i = motion_container.components[i];
		Entity entity_i = motion_container.entities[i];


		if (!registry.enemyAi.has(entity_i)) {
			continue;
		}
		float dist;
		dist = player_m.position.x - motion_i.position.x;
		if (dist > 0) {
			motion_i.velocity.x = 100;
		}
		if (dist == 0) {
			motion_i.velocity.x = 0;
		}
		if (dist < 0) {
			motion_i.velocity.x = -100;
		}
	}

	// AI turtle chasing salmon, velocity based on distance between turtle and salmon
	// when at a certain range velocity is faster
	
	// AI turtle chasing salmon, velocity based on distance between turtle and salmon
	// when at a certain range velocity is faster

	for (uint i = 0; i < motion_container.components.size(); i++)
	{
		Motion& motion_i = motion_container.components[i];
		Entity entity_i = motion_container.entities[i];


		if (!registry.block.has(entity_i)) {
			continue;
		}
		float playerScaleX = player_m.scale.x / 2;
		float playerScaleY = player_m.scale.y / 2;
		float blockScaleX = motion_i.scale.x / 2;
		float blockScaleY = motion_i.scale.y / 2;
		// collision when not jumping and sets the player jump to false
		if (player_m.position.y + playerScaleY > motion_i.position.y - blockScaleY) {
			// when player is left to block
				if (player_m.position.x <= motion_i.position.x - blockScaleX) {
					if (player_m.position.x + playerScaleX >= motion_i.position.x - blockScaleY) {
						player_m.position.x = motion_i.position.x - blockScaleX - playerScaleX;
						player_m.isJumping = false;
						player_m.notJumping = true;
					}
			}
				// right to block
				if (player_m.position.x > motion_i.position.x + blockScaleX) {
					if (player_m.position.x - playerScaleX <= motion_i.position.x + blockScaleX) {
						player_m.position.x = motion_i.position.x + blockScaleX + playerScaleX;
						player_m.isJumping = false;
						player_m.notJumping = true;
					}
				}
		}
		// when player is jumping
		if (player_m.position.y + playerScaleY <= (motion_i.position.y - blockScaleY)) {
			// in bound of block
			if ((player_m.position.x + playerScaleX) >= motion_i.position.x - blockScaleX) {
				if (player_m.position.x - playerScaleX <= motion_i.position.x + blockScaleX) {
					if (player_m.position.y + playerScaleY == motion_i.position.y - blockScaleY) {	
					player_m.position.y = motion_i.position.y - blockScaleY - playerScaleY;
					player_m.isJumping = false;
					player_m.notJumping = true;	
					}
				}
			}
		}
		if (player_m.isJumping) {
			player_m.position.y -= player_m.gravity;
		} else {
			if (player_m.position.y == 700) {
				player_m.isJumping = false;
				player_m.notJumping = true;	
			}
			player_m.position.y += player_m.gravity;
		}
	}
}
	
