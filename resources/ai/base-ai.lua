aiData = {
       name = "base-ai",
       aiAction = function(player, map)
		if player.y ~= 1
		then
			player:moveUp(elapsedTime)
		end
	end
}


--[[			for i=0,(map:getNbPlayers() -1)
			do
				print("coo ", map:getPlayerPosX(i), " ", map:getPlayerPosY(i))
			end
]]--
