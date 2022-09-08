# ![logo](https://dbozenkai.com/img/LogoDBOZ.png) 

* [Requirements](#requirements)
* [Install](#install)
* [Client](#client)
* [Server](#server)
* [Client Options](#client-options)
* [Tools](#tools)
  

## Requirements

- [CMAKE](https://cmake.org/download/) 3.23.1 or superior to build solution.

- [Visual Studio](https://visualstudio.microsoft.com/) 2019 or superior version.

- [Boost](https://sourceforge.net/projects/boost/files/boost-binaries/) 1.73(Windows) 1.71(Linux) or superior version.

  - Windows: Download binaries and set "BOOST_ROOT" environment variable
    - Open environments window: `rundll32.exe sysdm.cpl,EditEnvironmentVariables`
    - Set by command: `setx BOOST_ROOT "c:\boost_path"`
  - Linux: Install with official repositories:
    - `apt-get install libboost-all-dev`

- [MariaDBConnector] (https://dlm.mariadb.com/2217837/Connectors/c/connector-c-3.2.6/mariadb-connector-c-3.2.6-win64.msi)
  - Windows: Download binaries and set "MYSQL_ROOT" environment variable
    - Open environments window: `rundll32.exe sysdm.cpl,EditEnvironmentVariables`
    - Set by command: `setx MYSQL_ROOT "c:\mysql_path"`
  - Linux: Install with official repositories:
    - `apt-get install libmariadbclient-dev libmariadb-client-lgpl-dev-compat`

## Install

- Create a folder with the name "**build**".

- Create 2 more folders inside build, "**client**" and "**server**".

- Open CMAKE and check `Grouped` and `Advanced`

- Select source and build folders, press `Configure` button.

- source folder is DBOZenkai_2.0 and build should be DBOZenkai_2.0/build/x (x can be client or server).

**Remember build folder are different for client and server**

- Select your VS version and platform:

- Win32 for client.

- x64 or empty for server.

### Client

- In CMAKE Expand `DBO`.

- Check `DBO_CLIENT` (Is checked by default) and (DBO_TOOLS) if you want add Tools.

- In `DBO_CLIENT_DIR` select your DBO client folder (this is the output path, where the .exe will be created).

- Press `Configure` again and `Generate`.

### Server

- In CMAKE Expand `DBO`.

- Check `DBO_SEVER` and uncheck others.

- Press `Generate`.

## Client options

**You can make a change and regenerate solution at any moment only pressing `Generate` button**

- Expand `OPTIONS` and select your configuration.

- `DATA_MODE`: Select data mode (XML, ENC, BIN), by default select BIN

- `NET_SERVER_SYNC`: Checked for normal mode, unchecked for virtual server.

- `NTL_WORLD_TOOL_MODE`: Checked for compile NtlWE tool (Saber), uncheck for compile client.

- `USE_MUTEX_CHECK`: Checked restrict the client to a single instance.

- `USE_PACK_DATA`: Checked use packed client, unchecked use a unpacket client.

## Tools

- Runing Tools

- `Chaoz`

- `GuiDevTool`

- `Launcher`

- `NtlWE`

- `PackEditor`

- `PathServerManager`

- `SimplePatcher`

- `Table Edior`

- `TSTool`

- `Venus`

- `MrPopo`

- `ModelTool2`

- `2DParticleEditor`

# Clang Format

To keep a consistent code style pattern, this project relies on LLVM Clang format tool.

Here are the instructions to make it work on your machine:

- Download and install LLVM latest version from [official GH repo](https://github.com/llvm/llvm-project/releases/tag/llvmorg-13.0.0):

![LLVM release repo page](./images/llvmRelease.JPG)

- Install "Clang Power Tools" extension in Visual Studio (ReSharper supports Clang format by default):

![Clang Power Tools extension](./images/ClangExtension.JPG)

- Restart Visual Studio and enable "Format on save option" from the Clang Power tools settings:

![Format on Save option](./images/FormatOnSave.JPG)

# DBO STL

- Lib to improve client performance
