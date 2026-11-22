# Tetris

基于 EasyX 的 Tetris 游戏（C++ / Visual Studio）。

## 目录结构

```
Tetris/
└── Tetris/                    项目目录（也是程序运行时的工作目录）
    ├── Tetris.vcxproj          VS 工程文件
    ├── src/                    全部源代码（.cpp / .h）
    ├── assets/
    │   ├── images/             美术资源（背景、方块贴图、界面图标）
    │   └── audio/              音效与背景音乐（.wav / .mp3）
    ├── data/                   运行时存档（最高分、按键设置，程序自动读写）
    └── x64/                    构建输出（不入库）
```

## 构建与运行

用 Visual Studio 打开 `Tetris.sln`，选择 Debug|x64 或 Release|x64 直接运行。
资源通过相对路径 `./assets/...`、`./data/...` 加载，工作目录需保持为项目目录（VS 默认即如此）。
