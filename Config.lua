function add_rider_refreshconfig()
    local run_dir = ".run"
    os.mkdir(run_dir)
    
    local xml = string.format([[
<component name="ProjectRunConfigurationManager">
  <configuration default="false" name="RefreshConfig" type="ShConfigurationType">
    <option name="SCRIPT_TEXT" value="Scripts\Premake\premake5.exe --file=Build.lua vs2022" />
    <option name="INDEPENDENT_SCRIPT_PATH" value="true" />
    <option name="SCRIPT_PATH" value="" />
    <option name="SCRIPT_OPTIONS" value="" />
    <option name="INDEPENDENT_SCRIPT_WORKING_DIRECTORY" value="true" />
    <option name="SCRIPT_WORKING_DIRECTORY" value="$PROJECT_DIR$" />
    <option name="INDEPENDENT_INTERPRETER_PATH" value="true" />
    <option name="INTERPRETER_PATH" value="powershell.exe" />
    <option name="INTERPRETER_OPTIONS" value="" />
    <option name="EXECUTE_IN_TERMINAL" value="true" />
    <option name="EXECUTE_SCRIPT_FILE" value="false" />
    <envs />
    <method v="2" />
  </configuration>
</component>

]], bat_path)
    
    local file = io.open(run_dir .. "/RefreshConfig.run.xml", "w")
    file:write(xml)
    file:close()
end

function add_fork_custom_commands()
  local fork_dir = ".fork"
  os.mkdir(fork_dir)
  
  local json = [[
[
  {
    "version" : 2
  },
  {
    "action" : {
      "script" : "echo ${repo:name} status:\n\ncursor .",
      "showOutput" : true,
      "type" : "sh",
      "waitForExit" : true
    },
    "name" : "Open With Cursor",
    "target" : "repository"
  },
  {
    "action" : {
      "script" : "echo ${repo:name} status:\n\ncode .",
      "showOutput" : true,
      "type" : "sh",
      "waitForExit" : true
    },
    "name" : "Open With VSCode",
    "target" : "repository"
  },
  {
    "action" : {
      "script" : "echo ${repo:name} status:\n\nScripts/Premake/premake5.exe --file=Build.lua vs2022",
      "showOutput" : true,
      "type" : "sh",
      "waitForExit" : true
    },
    "name" : "Refresh Solution Settings",
    "target" : "repository"
  }
]
  ]]

  local file = io.open(fork_dir .. "/custom-commands.json", "w")
  file:write(json)
  file:close()
end