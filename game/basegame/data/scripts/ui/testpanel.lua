-- Test panel code
-- Use as an example for modders and devs.

local wack = 0

-- Update function
-- Called whenever a script update is triggered
function update()
  print("This update call was called from Lua. sfscript sucked ass")
  wack = wack + 1
  print(wack)
end
-- What it returns depends on the script type
