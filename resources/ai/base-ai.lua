-- map cell values
BLOCK = 0
DESTROYABLE = 1
SAFE = 2
UNSAFE = 3
PLAYER = 4
UNKNOWN = 5

-- ai data table
-- aiAction is the function called at each frame
aiData = {
       name = "base-ai",
       aiAction = function(player, map)
		if map:getCell(player.x, player.y) == UNSAFE
		then
			player:memoriseMode()
			-- get nearest safe cell, and set to objective
		else
			player:resetGoal()
			player:memoriseAttack()
			-- get nearest enemy and set to enemy
		end
	end
}


--[[			for i=0,(map:getNbPlayers() -1)
			do
				print("coo ", map:getPlayerPosX(i), " ", map:getPlayerPosY(i))
			end
]]--
