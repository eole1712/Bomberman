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
		if (map:getCell(player.x, player.y) == UNSAFE)
		then
			player:memoriseDefense()
			-- get nearest safe cell, and set to objective
			player:resetGoal()
		else
			player:resetGoal()
			player:memoriseAttack()
			-- get nearest enemy and set to objective
			findPath(map, player.x, player.y, map:getPlayerPosX(3), map:getPlayerPosY(3))
		end
	end
}

-- path finding
-- returns a table containing each coordinates of cells to follow

function findPath(map, xStart, yStart, xEnd, yEnd)
	 mainCoo = { { x = xEnd, y = yEnd, count = 0 } }
	 i = 1

	 while (i <= #mainCoo)
	 do
		-- check i for 1000 and quit

		-- check rightside cell
		if (checkCell(map, mainCoo, mainCoo[i].x + 1, mainCoo[i].y) == true)
		then
			print "break1"
			mainCoo[#mainCoo + 1] = {
					      	  x = mainCoo[i].x + 1,
						  y = mainCoo[i].y,
						  count = mainCoo[i].count + 1
						  }

			if (mainCoo[i].x + 1 == xStart and mainCoo[i].y == yStart)
			then
				break
			end
		end

		-- check leftside cell
		print("test", i, mainCoo[i].x)
		if (checkCell(map, mainCoo, mainCoo[i].x - 1, mainCoo[i].y) == true)
		then
			print("test2", i, mainCoo[i].x)
			mainCoo[#mainCoo + 1] = {
					      	  x = mainCoo[i].x - 1,
						  y = mainCoo[i].y,
						  count = mainCoo[i].count + 1
						  }

			if (mainCoo[i].x - 1 == xStart and mainCoo[i].y == yStart)
			then
				break
			end
		end

		-- check upside cell
		if (checkCell(map, mainCoo, mainCoo[i].x, mainCoo[i].y + 1) == true)
		then
			print "break3"
			mainCoo[#mainCoo + 1] = {
					      	  x = mainCoo[i].x,
						  y = mainCoo[i].y + 1,
						  count = mainCoo[i].count + 1
						  }

			if (mainCoo[i].x == xStart and mainCoo[i].y + 1 == yStart)
			then
				break
			end
		end

		-- check downside cell
		if (checkCell(map, mainCoo, mainCoo[i].x, mainCoo[i].y - 1) == true)
		then
			print "break4"
			mainCoo[#mainCoo + 1] = {
					      	  x = mainCoo[i].x,
						  y = mainCoo[i].y - 1,
						  count = mainCoo[i].count + 1
						  }

			if (mainCoo[i].x == xStart and mainCoo[i].y - 1 == yStart)
			then
				break
			end
		end

		i = i + 1
	 end

	 for k, v in pairs(mainCoo)
	 do
		print(v.x, v.y, v.count)
	 end
	 print "end"
end

function checkCell(map, mainCoo, x, y)
	 if (x < map.width and x >= 0 and y < map.height and y >= 0 and
	     isCooInTable(mainCoo, x, y) == false and
	     map:getCell(x, y) ~= BLOCK)
	 then
		return true
	 end

	 return false
end

function isCooInTable(mainCoo, x, y)
	 i = 1

	 while (i <= #mainCoo)
	 do
		if (mainCoo[i].x == x and mainCoo[i].y == y)
		then
			return true
		end
		i = i + 1
	 end
	 return false
end

--[[			for i=0,(map:getNbPlayers() -1)
			do
				print("coo ", map:getPlayerPosX(i), " ", map:getPlayerPosY(i))
			end
]]--
