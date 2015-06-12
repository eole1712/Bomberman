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
local isDebug = false

-- ai data table
-- aiAction is the function called at each frame
aiData = {
   name = "base-ai",
   aiAction = function(player, map)

if (player.isAlive == false)
then
   return
end
debug("player at", player.x, player.y) 

if (#route > 0 and player.x == route[1].x and route[1].y)
then
   table.remove(route, 1)
end

if (#route > 0 and isAdjacentCell(player.x, player.y, route[1].x, route[1].y) == false)
then
   route = {}
end

if (map:getCell(player.x, player.y) == UNSAFE and attack == true or
    isTypeInTable(map:getCell(player.x, player.y), { UNSAFE, BLOCK }) and #route == 0)
then
   -- danger, run away to safe cell
   runAway(map, player)
elseif (map:getCell(player.x, player.y) == SAFE and attack == false or
	map:getCell(player.x, player.y) == SAFE and #route == 0)
then
   attack = true

   -- get enemy and set route to him
   local target = targetEnemy(map, player)

   if (target.x ~= -1 and target.y ~= -1) then
      route = findPath(map, player.x, player.y, target.x, target.y, { SAFE, BONUS, DESTROYABLE })
   else
      debug("AI: Error: player target not found")
   end
end

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

for k, v in pairs(adjCells)
do
   if (#route > 0 and isInMap(map, v.x, v.y) and v.shouldMove(player, route[1].x, route[1].y))
   then
      if ((map:getCell(v.x, v.y) == DESTROYABLE or isEnemy(map, v.x, v.y)) and attack)
      then
	 player:putBomb()
	 debug("putBomb at", player.x, player.y) 
	 route = {} -- clean route so the route will be set with an updated map
	 break
      elseif (map:getCell(v.x, v.y) == SAFE or map:getCell(v.x, v.y) == BONUS or
	      map:getCell(player.x, player.y) ~= SAFE)
      then
	 --	    debug(v.moveDesc)
	 v.move(player)
      end
   end
end
end
}

function runAway(map, player)
   attack = false

   local cell = findCell(map, player.x, player.y, { SAFE, BONUS }, { BLOCK, DESTROYABLE })

   if (cell.x ~= -1 and cell.y ~= -1) then
      route = findPath(map, player.x, player.y, cell.x, cell.y, { UNSAFE, SAFE, BONUS })
      debug("safe cell", cell.x, cell.y) 
      debugRoute()
   else
      route = {}
      debug("safe cell not found") 
   end
end

-- back tracking algorithm to seek a cell
local prevCells = {}

function findCell(map, x, y, targetCells, blocksCells)
   prevCells = {}
   return findCellByBackTracking(map, x, y, targetCells, blocksCells)
end

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
      debug("bt test", v.x, v.y)
      if (isInMap(map, v.x, v.y) and isTypeInTable(map:getCell(v.x, v.y), blocksCells) == false and
	  isCooInTable(prevCells, v.x, v.y) == false)
      then
	 debug("bt ok", v.x, v.y)
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
	 if (checkCell(map, mainCoo, v.x, v.y, tableType) == true or
		v.x == xStart and v.y == yStart)
	 then
	    mainCoo[#mainCoo + 1] = {
	       x = v.x,
	       y = v.y,
	       count = mainCoo[i].count + 1
	    }

	    if (v.x == xStart and v.y == yStart)
	    then
	       debug("start cell found") 
	       done = true
	       break
	    end
	 end
      end

      i = i + 1
   end

--[[
   debug "------- maincoo"
   for k, v in pairs(mainCoo)
   do
      debug(v.x, v.y, v.count)
   end
   debug "--------- end"
]]--

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

return path
end

function checkCell(map, mainCoo, x, y, tableType)
   if (isInMap(map, x, y) and isCooInTable(mainCoo, x, y) == false and
       isTypeInTable(map:getCell(x, y), tableType)) then
      return true
   end

   return false
end

-- target enemy
function targetEnemy(map, player)
   local idx = 0

   while (idx < map:getNbPlayers()
	     and map:getPlayerPosX(idx) == player.x
	     and map:getPlayerPosY(idx) == player.y)
   do
      idx = idx + 1
   end

   if (idx < map:getNbPlayers()) then
      return { x = map:getPlayerPosX(idx), y = map:getPlayerPosY(idx) }
   else
      return { x = -1, y = -1 }
   end
end

-- checks whether an enemy is on x and y
function isEnemy(map, x, y)
   local idx = 0

   while (idx < map:getNbPlayers())
   do
      if (x == map:getPlayerPosX(idx) and y == map:getPlayerPosY(idx)) then
	 return true
      end

      idx = idx + 1
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

function debugRoute()
   debug("--------- debug route")
   for k, v in pairs(route)
   do
      debug(v.x, v.y)
   end
   debug("--------- end")
end

function debug(...)
   local arg = {...}

   if (isDebug == false) then
      return
   end

   for i,v in ipairs(arg) do
      io.write(v, "\t")
   end
   io.write("\n")
end