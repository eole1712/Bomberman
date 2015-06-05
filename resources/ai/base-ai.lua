local test = 0
aiData = {
       name = "base-ai",
       aiAction = function(player, map, elapsedTime)
		if test == 0
		then
			print(map:toString())
			player:putBomb()
			test = 1
		else
			print(map:toString())
			player:moveLeft(elapsedTime)
		end
	end
}