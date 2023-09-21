-- Test panel code
-- Use as an example for modders and devs.

local wack = 0


function debugText(panel)
  --for i = 1 do print(i) end -- change "print(i)" to panel.addText
end

-- The init function is given an empty panel with
-- slots for:
--   * Text
--   * Buttons
function init(panel)
  print("TestPanel UI init function called")
  print(panel.index)
  print(panel.title)
  -- Set tile of our panel
  panel.title = "Test Panel"
  -- Lets add a small peice of text
  -- How you do this is really up to you, i just made a 
  -- seperate helper function since the contents of the text doesnt matter
  -- debugText(panel)
  -- TODO: Expose Text class to Lua
  return panel
end

-- Update function
-- Called whenever a script update is triggered
function update()
  print("This update call was called from Lua. sfscript sucked ass")
end
-- What it returns depends on the script type