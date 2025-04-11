# MultiExtend

<style>
  .image-caption {
    font-size: 0.8em;
    font-style: italic;
  }
</style>

## 项目概述
Language: C++

Manager: PreMake

Status: Under Develop

MultiExtend是一个集成了SDL 2D框架、OpenGL和DirectX等3D框架、日常开发所需运算和功能的便捷拓展，目的是解决项目链接繁琐、编译繁琐等问题

内置timer clock trace log等一系列算法，也包含基本游戏主体框架（Object、Actor、Component、ActorComponent等），可以作为其他项目的拓展直接进行使用，同时也可以作为初学者理解游戏框架的入门

<p align="center">
  <img src="img/SDLTest.gif" alt="SDL组件示例">
  <br>
  <em class = "image-caption">SDL组件示例</em>
</p>

<p align="center">
  <img src="img/OpenGLTriangle.gif" alt="OpenGL简单三角形渲染示例">
  <br>
  <em class = "image-caption">OpenGL简单三角形渲染示例</em>
</p>

## Build

本项目使用`Premake`进行`solution`配置

克隆项目文件，打开`Script`文件夹，运行`.bat`文件将在跟目录获得`.sln`文件

![Snapshot](img/Untitled.png){ width=50% }
![Snapshot](img/solution.png){ width=50% }

案例运行

![Template](img/Snipaste_2024-04-10_16-08-03.png)


<aside>
✨ 部分项目GLFW的配置不同，可能在编译中会出现未定义引用的问题

本项目在GLFW.lua中修复了部分文件引用的问题

可以作为使用GLFW源码的参考

</aside>

![LOGO](img/Snipaste_2024-04-10_16-11-24.png)
