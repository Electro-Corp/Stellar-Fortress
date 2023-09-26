-- UIHelper.lua
-- Purpose:
--   Helper class for UI Panels
module(..., package.seeall)

-- Returns the panel from a given index
-- UIPanel Lua scripts should know the index
-- because its given to them during initlization
function getPanel(index)
  return UIManager:getPanel(index)
end