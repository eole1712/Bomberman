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

local test = 0 -- tmppppppppppppppppppppppppppppppppp

-- ai data table
-- aiAction is the function called at each frame
aiData = {
   name = "base-ai",
   aiAction = function(player, map)

		 --[[       		if (test == 0) then
		 player:moveUp()
		 test = 1
		 return 0
	      else
		 return 0
	      end ]]-- tmpppppppppppppppppppppppppppppppp

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
elseif (map:getCell(player.x, player.y) == SAFE and attack == false or
	map:getCell(player.x, player.y) == SAFE and #route == 0)
then
   attack = true

   -- get nearest enemy and set to objective
   route = findPath(map, player.x, player.y, map:getPlayerPosX(1), map:getPlayerPosY(1), { SAFE, BONUS, DESTROYABLE })
end

if (#route > 0)
then
   local adjCells = {
      { x = player.x + 1, y = player.y, moveDesc = "AI: move right",
	 move = function (player) player:moveRight() end,
	 shouldMove = function (player, x, y) return x > player.x end },
      { x = player.x - 1, y = player.y, moveDesc = "AI: move left",
	 move = function (player) player:moveLeft() end,
	 shouldMove = function (player, x, y) return x < player.x end },
      { x = player.x, y = player.y + 1, moveDesc = "AI: move up",
	 move = function (player) player:moveUp() end,
	 shouldMove = function (player, x, y) return y > player.y end },
      { x = player.x, y = player.y - 1, moveDesc = "AI: move down",
	 move = function (player) player:moveDown() end,
	 shouldMove = function (player, x, y) return y < player.y end },
   }

--   print(player.x, player.y, route[1].x, route[1].y, map:getCell(route[1].x, route[1].y),
--	 route[#route].x, route[#route].y)
   for k, v in pairs(adjCells)
   do
      if (isInMap(map, v.x, v.y)) then
      end

      if (isInMap(map, v.x, v.y) and v.shouldMove(player, route[1].x, route[1].y))
      then
	 if (map:getCell(v.x, v.y) == DESTROYABLE and attack)
	 then
	    player:putBomb()
	    runAway(map, player)
	 elseif (map:getCell(v.x, v.y) == SAFE or map:getCell(v.x, v.y) == BONUS or
		 map:getCell(player.x, player.y) ~= SAFE)
	 then
--	    print(v.moveDesc)
	    v.move(player)
	 end
      end
   end
end
end
}

function runAway(map, player)
   attack = false

--   local cell = findCellType(map, player.x, player.y, { SAFE, BONUS })
   local cell = findCellByBackTracking(map, player.x, player.y, { SAFE, BONUS }, { BLOCK, DESTROYABLE, FIRE })

   if (cell.x == -1 or cell.y == -1) then
      print "safe cell not found"
   end

   print("safe cell: ", cell.x, cell.y) --
   print("player: ", player.x, player.y)
   route = findPath(map, player.x, player.y, cell.x, cell.y, { UNSAFE, SAFE, BONUS })
end

local prevCells = {}
function findCellByBackTracking(map, x, y, targetCells, blocksCells)
   local toTest = {
      { x = x + 1, y = y },
      { x = x - 1, y = y },
      { x = x, y = y + 1 },
      { x = x, y = y - 1 },
   }
   local res = {}

   for k, v in pairs(toTest)
   do
      if (isInMap(map, v.x, v.y) and isTypeInTable(map:getCell(v.x, v.y), blocksCells) == false and
	  isCooInTable(prevCells, v.x, v.y) == false)
      then
	 print(v.x, v.y, map:getCell(v.x, v.y))
	 if (isTypeInTable(map:getCell(v.x, v.y), targetCells)) then
	    prevCells = {}
	    return { x = v.x, y = v.y, valid = true }
	 end

	 prevCells[#prevCells + 1] = { x = v.x, y = v.y }
	 res = findCellByBackTracking(map, v.x, v.y, targetCells, blocksCells)
	 if (res.valid == true) then
	    return res
	 end
      end
   end

   return { x = -1, y = -1, valid = false }
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
   local done = false

   while (i <= #mainCoo and done == false)
   do
      local toTest = {
	 { x = mainCoo[i].x + 1, y = mainCoo[i].y },
	 { x = mainCoo[i].x - 1, y = mainCoo[i].y },
	 { x = mainCoo[i].x, y = mainCoo[i].y + 1 },
	 { x = mainCoo[i].x, y = mainCoo[i].y - 1 },
      }

      for k, v in pairs(toTest)
      do
	 if (checkCell(map, mainCoo, v.x, v.y, tableType) == true)
	 then
	    mainCoo[#mainCoo + 1] = {
	       x = v.x,
	       y = v.y,
	       count = mainCoo[i].count + 1
	    }

	    if (v.x == xStart and v.y == yStart)
	    then
	       done = true
	       break
	    end
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
   if (isInMap(map, x, y) and isCooInTable(mainCoo, x, y) == false and
       isTypeInTable(map:getCell(x, y), tableType)) then
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
   if ((x1 + 1 == x2 and y1 == y2) or (x1 - 1 == x2 and y1 == y2) or
       (x1 == x2 and y1 + 1 == y2) or (x1 == x2 and y1 - 1 == y2))
   then
      return true
   end

   return false
end

-- checks whether x and y are in mainCoo
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
