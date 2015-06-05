local test = 0
aiData = {
       name = "base-ai",
       aiAction = function(player, map, elapsedTime)
		if test == 0
		then
			print(map:toString())
			player:putBomb()
			test = 1
			for i=0,(map:getNbPlayers() -1)
			do
				print("coo ", map:getPlayerPosX(i), " ", map:getPlayerPosY(i))
			end
		else
			player:moveLeft(elapsedTime)
		end
	end
}