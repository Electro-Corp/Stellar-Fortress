-- Test panel code
-- Use as an example for modders and devs.
-- Creates a UI panel and updates it with some basic things
-- Questions for right now:
--    > Should most functions that modders use be included from other
--      Lua files (which we make) that link to C++
--    > Or should they just directly work with C+


-- The init function should return a panel
function init(index)
  panel = UI("Test Panel", index) -- Create a new UIPanel with the name and index
  print("TestPanel UI init function called")
  -- Lets add a small peice of text
  text = Text("Hello World", 0, 0) -- create Text Text::Text(text, x, y)
  panel.addText(panel, text)
  return panel -- Return panel
end

-- Update function
-- Called whenever a script update is triggered
function update()
  print("This update call was called from Lua. sfscript sucked ass")
  return 0
end
-- What it returns depends on the script type