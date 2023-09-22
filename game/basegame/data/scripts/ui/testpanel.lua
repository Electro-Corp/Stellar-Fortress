-- Test panel code
-- Use as an example for modders and devs.
-- Creates a UI panel and updates it with some basic things
-- Questions for right now:
--    > Should most functions that modders use be included from other
--      Lua files (which we make) that link to C++
--    > Or should they just directly work with C+

-- require("API.UIHelper")

-- The init function should return a panel
function init(index)
  panel = UI("Test Panel", index, 100, 200) -- Create a new UIPanel with the name, index, height, and width
  print("TestPanel UI init function called")
  -- Lets add a small peice of text
  text = Text("Hello World", 0, 0) -- create Text 
  panel.addText(panel, text)
  -- Lets add a button
  button = Button("Click me", 50, 0, "clickMeOnClick")
  panel.addButton(panel, button)
  return panel -- Return panel
end

-- This function will be called when the button is pressed
function clickMeOnClick()
  print("I was clicked.")
end

-- Update function
-- Called whenever a script update is triggered
function update()
  print("This update call was called from Lua. sfscript sucked ass") -- temp
  return 0
end
-- What it returns depends on the script type ig