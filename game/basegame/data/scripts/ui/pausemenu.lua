-- PAUSEMENU
-- Lua file for the pause menu

-- Create the panel
function init(index)
  panel = UI("Game Paused", index, 250, 500) 
  print("PauseMenu init function called")

  text = Text("Game Paused", 250 / 2, 0)
  panel.addText(panel, text)

  button = Button("Resume", 250 / 2, 500 / 4, "resume")
  panel.addButton(panel, button)
  return panel -- Return panel
end

function update()
end

function resume()
  -- Call Game.lua function
  resumeGame()
end