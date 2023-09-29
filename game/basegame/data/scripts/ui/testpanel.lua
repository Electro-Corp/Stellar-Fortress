-- Test panel code
-- Use as an example for modders and devs.
-- Creates a UI panel and updates it with some basic things
-- Questions for right now:
--    > Should most functions that modders use be included from other
--      Lua files (which we make) that link to C++
--    > Or should they just directly work with C++

-- UIHelper provides functions that could be useful such as 
-- getting variable values

myindex = 0
count = 0
-- The init function should return a panel
function init(index)
  myindex = index
  panel = UI("Test Panel", index, 200, 300, 0, 0) -- Create a new UIPanel with the name, index, height, and width
  print("TestPanel UI init function called")
  -- Lets add a small peice of text
  text = Text("Hello World.", 0, 0) -- create Text 
  text2 = Text("X Y POS", 0, 30) -- create Text (2)
  panel.addText(panel, text)
  panel.addText(panel, text2)
  -- Lets add a button
  --           Button Title | X | Y | OnClick function name
  button = Button("Click me", 50, 0, "clickMeOnClick")
  panel.addButton(panel, button)
  return panel -- Return panel
end

-- This function will be called when the button is pressed
function clickMeOnClick()
  print("TestUI Button pressed")
end

-- Update function
-- Called whenever a script update is triggered
function update()
  -- i would highly recommmend not to print anything during 
  -- update functions due to how often they will probabbly be called
  -- (frame) % (some number)
  
  -- Get the panel from the game
  tmp = UIManager:getPanel(myindex)
  
  -- Make it oscillate 
  tmp.x = (math.sin(math.rad(count)) * 100) + 400
  tmp.y = (math.tan(math.rad(count)) * 100) + 200
  -- Modify the text (why not?)
  tmp.title = math.sqrt(math.pow(tmp.x, 2) + math.pow(tmp.y, 2))
  
  UIManager:setPanel(tmp, myindex)
  count = count + 1
  
  return 0
end
-- What it returns depends on the script type ig  