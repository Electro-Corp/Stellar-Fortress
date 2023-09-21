-- Test panel code
-- Use as an example for modders and devs.

-- The init function should return a panel
function init(index)
  panel = UI("Wack", 2) -- Create a new UIPanel
  print("TestPanel UI init function called")
  -- Set tile of our panel
  panel.title = "Test Panel"
  -- Set index
  panel.index = index
  -- Lets add a small peice of text
  text = Text("Hello World", 0, 0) 
  panel.addText(panel, text)
  return panel -- Return panel
end

-- Update function
-- Called whenever a script update is triggered
function update()
  print("This update call was called from Lua. sfscript sucked ass")
end
-- What it returns depends on the script type