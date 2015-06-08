-- map cell values
BLOCK = 0
DESTROYABLE = 1
SAFE = 2
UNSAFE = 3
PLAYER = 4
BONUS = 5
UNKNOWN = 6

-- ai data table
-- aiAction is the function called at each frame
aiData = {
       name = "base-ai",
       aiAction = function(player, map)
		if map:getCell(player.x, player.y) == UNSAFE
		then
			player:memoriseDefense()
			-- get nearest safe cell, and set to objective
			player:resetGoal()
			while player.goalX == -1
			do
			end
		else
			player:resetGoal()
			player:memoriseAttack()
			-- get nearest enemy and set to objective
		end
	end
}


--[[			for i=0,(map:getNbPlayers() -1)
			do
				print("coo ", map:getPlayerPosX(i), " ", map:getPlayerPosY(i))
			end
]]--
