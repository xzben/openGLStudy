1、GLFW  https://www.glfw.org/download.html
跨平台的窗口库
本地路径  3rd\glfw
编译方法 安装 cmake  在 3rdlib\glfw\build 目录使用命令
cd 3rdlib\glfw\build
cmake -S ..\..\..\3rd\glfw -B ./
指定 vs版本
cmake -S ..\..\..\3rd\glfw -B ./ -G "Visual Studio 12 2013"
打开工程 GLFW.sln 工程文件，构建工程即可在src\debug 下获得 glfw.lib 库