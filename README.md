# ![logo](https://hpscds.com/wp-content/uploads/2019/04/c-plus-plus-logo.png) 

* [Requirements](#requirements)
* [Install](#install)
* [Credits](#credits)
  

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

# Clang Format

To keep a consistent code style pattern, this project relies on LLVM Clang format tool.

Here are the instructions to make it work on your machine:

- Download and install LLVM latest version from [official GH repo](https://github.com/llvm/llvm-project/releases/tag/llvmorg-13.0.0):

![LLVM release repo page](./images/llvmRelease.JPG)

- Install "Clang Power Tools" extension in Visual Studio (ReSharper supports Clang format by default):

![Clang Power Tools extension](./images/ClangExtension.JPG)

- Restart Visual Studio and enable "Format on save option" from the Clang Power tools settings:

![Format on Save option](./images/FormatOnSave.JPG)

## Credits

Trinity Core
TheCherno