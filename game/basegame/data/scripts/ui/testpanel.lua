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
isDown = false
drag = false
local mouseX = 0
local mouseY = 0
-- The init function should return a panel
function init(index)
  myindex = index
  panel = UI("Test Panel", index, 200, 300, 0, 0, true) -- Create a new UIPanel with the name, index, height, and width
  print("TestPanel UI init function called")
  -- Lets add a small peice of text
  text = Text("Hello World.", 0, 0) -- create Text 
  text2 = Text("This is one of", 0, 30) -- create Text (2)
  text3 = Text("the panels of", 0, 50) -- create Text (3)
  text4 = Text("all time.", 0, 70) -- create Text(4)
  text5 = Text("XYPOS", 0, 100)

  -- Add the text(s)
  panel.addText(panel, text)
  panel.addText(panel, text2)
  panel.addText(panel, text3)
  panel.addText(panel, text4)
  panel.addText(panel, text5)
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

  mouseX = Graphics:getMouseX()
  mouseY = Graphics:getMouseY()

  -- i would highly recommmend not to print anything during 
  -- update functions due to how often they will probabbly be called
  -- (frame) % (some number)
  
  -- Get the panel from the game
  tmp = UIManager:getPanel(myindex)

  -- Update text
  -- text_tmp = tmp.getText(panel, 4)
  -- text_tmp.text = "Mouse Pos: (" .. mouseX .. "," .. mouseY .. ")"
  -- tmp.setText(tmp, text_tmp, 4)
 
  
  -- Make draggable

  if not Graphics:isMouseDown() == isDown then
    if mouseX > tmp.x and mouseX < tmp.x + tmp.width and mouseY > tmp.y and mouseY < tmp.y + 20 then
      drag = true
    end
  end
  
  if Graphics:isMouseDown() == true then
    isDown = true
  else
    isDown = false
    drag = false
    count = 1
  end

  if drag == true then
    tmp.x = mouseX - (tmp.width / 2)
    tmp.y = mouseY
    tmp.x = tmp.x + math.sin(math.rad(count)) * 3
    tmp.y = tmp.y + math.cos(math.rad(count)) * 3
    count = count + 1
  end


  -- Modify the text (why not?)
  tmp.title = "X: " .. tmp.x .. " Y: " .. tmp.y
  
  UIManager:setPanel(tmp, myindex)
  
  
  return 0
end
-- What it returns depends on the script type ig  