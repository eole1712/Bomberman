aiData = {
       name = "base-ai",
       aiAction = function(player, elapsedTime)
		print(player.aiName)
		player:moveUp(elapsedTime)
	end
}