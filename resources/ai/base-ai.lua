-- map cell values
BLOCK = 0
DESTROYABLE = 1
SAFE = 2
UNSAFE = 3
PLAYER = 4
BONUS = 5
UNKNOWN = 6

-- local variable to the file
-- allows ai to memorise the path
local route = {}
local attack = false

-- ai data table
-- aiAction is the function called at each frame
aiData = {
       name = "base-ai",
       aiAction = function(player, map)
       		if (player.isAlive == false)
		then
		   return
		end

		if (#route > 0 and player.x == route[1].x and route[1].y)
		then
		   table.remove(route, 1)
		end

		if (#route > 0 and isAdjacentCell(player.x, player.y, route[1].x, route[1].y) == false)
		then
--			print("route error", player.x, player.y, route[1].x, route[1].y)
			route = {}
		end

		if (map:getCell(player.x, player.y) == UNSAFE and attack == true or
		    map:getCell(player.x, player.y) == UNSAFE and #route == 0)
		then
			runAway(map, player)

			-- get nearest safe cell, and set to objective
		elseif (map:getCell(player.x, player.y) == SAFE and attack == false or
		        map:getCell(player.x, player.y) == SAFE and #route == 0)
		then
		     	attack = true

			-- get nearest enemy and set to objective
			route = findPath(map, player.x, player.y, map:getPlayerPosX(1), map:getPlayerPosY(1), { SAFE, BONUS, DESTROYABLE })
		end

		if (#route > 0)
		then
			print(player.x, player.y, route[1].x, route[1].y)
		   if (route[1].x > player.x)
		   then
			  if (map:getCell(player.x + 1, player.y) == DESTROYABLE)
			  then
				player:putBomb()
				runAway(map, player)
			  elseif (map:getCell(player.x + 1, player.y) == SAFE or
			  	  map:getCell(player.x + 1, player.y) == BONUS or
			  	  map:getCell(player.x, player.y) ~= SAFE)
			  then
				print("go x + 1")
			       	  player:moveLeft()
			  end
		   elseif (route[1].x < player.x)
		   then
			  if (map:getCell(player.x - 1, player.y) == DESTROYABLE)
			  then
				player:putBomb()
				runAway(map, player)
			  elseif (map:getCell(player.x - 1, player.y) == SAFE or
			  	  map:getCell(player.x - 1, player.y) == BONUS or
			  	  map:getCell(player.x, player.y) ~= SAFE)
			  then
				print("go x - 1")
			  	player:moveRight() -- left/right are switched ?
			  end
		   elseif (route[1].y > player.y)
		   then
			  if (map:getCell(player.x, player.y + 1) == DESTROYABLE)
			  then
				player:putBomb()
				runAway(map, player)
			  elseif (map:getCell(player.x, player.y + 1) == SAFE or
			  	  map:getCell(player.x, player.y + 1) == BONUS or
			  	  map:getCell(player.x, player.y) ~= SAFE)
			  then
				print("go y + 1")
			     	player:moveUp()
			  end
		   elseif (route[1].y < player.y)
		   then
			  if (map:getCell(player.x, player.y - 1) == DESTROYABLE)
			  then
				player:putBomb()
				runAway(map, player)
			  elseif (map:getCell(player.x, player.y - 1) == SAFE or
			  	  map:getCell(player.x, player.y - 1) == BONUS or
			  	  map:getCell(player.x, player.y) ~= SAFE)
			  then
				print("go y - 1")
			   	player:moveDown()
			  end
		   end
		end
	end
}

function runAway(map, player)
	 attack = false
	 local cell = findCellType(map, player.x, player.y, { SAFE, BONUS })

	 route = findPath(map, player.x, player.y, cell.x, cell.y, { UNSAFE, SAFE, BONUS })
end

-- find nearest cell of type 'type'
-- /!\ to refacto
function findCellType(map, xStart, yStart, tableType)
	 local i = 1
	 local cell = { x = -1, y = -1 }

	 while (cell.x == -1 and cell.y == -1)
	 do
		if (isInMap(map, xStart + i, yStart) and isTypeInTable(map:getCell(xStart + i, yStart), tableType)) then
			cell = { x = xStart + i, y = yStart }
		elseif (isInMap(map, xStart - i, yStart) and isTypeInTable(map:getCell(xStart - i, yStart), tableType)) then
			cell = { x = xStart - i, y = yStart }
		elseif (isInMap(map, xStart, yStart + i) and isTypeInTable(map:getCell(xStart, yStart + i), tableType)) then
			cell = { x = xStart, y = yStart + i }
		elseif (isInMap(map, xStart, yStart - i) and isTypeInTable(map:getCell(xStart, yStart - i), tableType)) then
			cell = { x = xStart, y = yStart - i }
		elseif (isInMap(map, xStart + i, yStart + i) and isTypeInTable(map:getCell(xStart + i, yStart + i), tableType)) then
			cell = { x = xStart + i, y = yStart + i }
		elseif (isInMap(map, xStart + i, yStart - i) and isTypeInTable(map:getCell(xStart + i, yStart - i), tableType)) then
			cell = { x = xStart + i, y = yStart - i }
		elseif (isInMap(map, xStart - i, yStart + i) and isTypeInTable(map:getCell(xStart - i, yStart + i), tableType)) then
			cell = { x = xStart - i, y = yStart + i }
		elseif (isInMap(map, xStart - i, yStart - i) and isTypeInTable(map:getCell(xStart - i, yStart - i), tableType)) then
			cell = { x = xStart - i, y = yStart - i }
		end

		i = i + 1
	 end

	 return cell
end

-- path finding
-- returns a table containing each coordinates of cells to follow
-- tableType is types where you can go through

function findPath(map, xStart, yStart, xEnd, yEnd, tableType)
	 local mainCoo = { { x = xEnd, y = yEnd, count = 0 } }
	 local i = 1

	 while (i <= #mainCoo)
	 do
		-- check i for 1000 and quit

		-- check rightside cell
		if (checkCell(map, mainCoo, mainCoo[i].x + 1, mainCoo[i].y, tableType) == true)
		then
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
		if (checkCell(map, mainCoo, mainCoo[i].x - 1, mainCoo[i].y, tableType) == true)
		then
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
		if (checkCell(map, mainCoo, mainCoo[i].x, mainCoo[i].y + 1, tableType) == true)
		then
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
		if (checkCell(map, mainCoo, mainCoo[i].x, mainCoo[i].y - 1, tableType) == true)
		then
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

	 local path = { { x = xStart, y = yStart } }
	 local count = mainCoo[#mainCoo].count - 1

	 local i = #mainCoo
	 while (i >= 1)
	 do
		if (isAdjacentCell(mainCoo[i].x, mainCoo[i].y,
		   		   path[#path].x, path[#path].y) == true and
		    mainCoo[i].count == count)
		then
			path[#path + 1] = { x = mainCoo[i].x, y = mainCoo[i].y }
			count = count - 1
		end

		i = i - 1
	 end

--[[
	 print "start"
	 for k, v in pairs(path)
	 do
		print(v.x, v.y)
	 end
	 print "end"
]]--
	return path
end

function checkCell(map, mainCoo, x, y, tableType)
	 if (isInMap(map, x, y) and
	     isCooInTable(mainCoo, x, y) == false and
	     isTypeInTable(map:getCell(x, y), tableType))
	 then
		return true
	 end

	 return false
end

-- checks whether x/y are in map range
function isInMap(map, x, y)
	 if (x < map.width and x >= 0 and y < map.height and y >= 0)
	 then
		return true
	end
	return false
end

-- checks whether a type is in table
function isTypeInTable(type, tableType)
	 for k, v in pairs(tableType)
	 do
	     if (v == type) then
	     	return true
	     end
	 end
	 return false
end

-- checks whether x1/y1 and x2/y2 are adjacents
function isAdjacentCell(x1, y1, x2, y2)
	 if ((x1 + 1 == x2 and y1 == y2) or
	     (x1 - 1 == x2 and y1 == y2) or
	     (x1 == x2 and y1 + 1 == y2) or
	     (x1 == x2 and y1 - 1 == y2))
	 then
		return true
	 end

	 return false
end

function isCooInTable(mainCoo, x, y)
	 local i = 1

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
