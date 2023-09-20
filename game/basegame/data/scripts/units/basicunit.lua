local damage = 1
local health = 50


-- What this does depends on what we're making the game like
-- Is it an RTS? if so then it needs to read the current state of the board
-- and make decisions on its own, since thats how RTS's work (wow)
-- On the other hand, you could make each unit be depenednt 
-- on player input, so it doesnt need to make decisions byitself
function update()
  -- Do something (cough cough logan cough cough)
  print("This is a basic unit.") -- debug
end

function takeDamage()
  health = health - 1
end

function attack()
  
end