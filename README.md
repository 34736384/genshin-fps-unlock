# Genshin Impact FPS Unlocker
 - This tool helps you to unlock the 60 fps limit in the game
 - This is an external program uses **WriteProcessMemory** to write the desired fps to  the game
 - Handle protection bypass is already included
 - Does not require a driver for R/W access
 - Supports OS and CN version
 - Should works for future updates
 - If the source needs to be updated, I'll try to do it as soon as possible
 - You can download the compiled binary over at 'Release' if you don't want to compile it yourself
 ## Compiling
 - Use  Visual Studio 2019 Community Edition to compile
 - Not required but I know it works on this version
 ## Usage
 - Place the compiled exe into one directory above the game (same folder as launcher.exe)
 - If your 'Genshin Impact Game' folder is not present in the same folder as launcher.exe, just place the exe to one directory above the game folder
 - Make sure your game is closed, the unlocker will automatically start the game for you
 - Run the exe as administrator, and leave the exe running
 >It requires adminstrator because the game needs to be started by the unlocker and the game requires such permission
 ### Default Keybinds
 - **END** to toggle on/off
 - **UP ARROW** to increase limit (+20)
 - **DOWN ARROW** to decrease limit (-20)
 - The default fps limit is set to 120
 ## Notes
 - Tested on a new account for two weeks and no bans so far (AR30), can't guaranteed it will be safe forever, But honestly though, I doubt they would ban you for this.
 - Modifying game memory with an unauthorized third party application is a violation of the ToS, so use it at your own risk
 - If you want to change keybinds or the default fps then you can edit the defines at the top of the source
 - [Here](http://cherrytree.at/misc/vk.htm) is a list of keycodes


# 原神解锁FPS限制

 - 工作原理类似于外部辅助，通过**WriteProcessMemory**把FPS数值写进游戏
 - 不需要通过驱动进行读写操作
 - 支持国服和外服
 - 理论上支持后续版本，不需要更新源码
 - 如果需要更新我会尽快更新

## 编译

 - 用VS2019编译，其他版本的也应该可以，没测试过
## 食用指南
 - 把解锁器放到游戏执行文件的上一个目录 （和启动器launcher.exe同一个目录）
 - 运行之前确保游戏是关闭的
 - 用管理员运行解锁器
 - 解锁器不能关掉
>使用管理员运行是因为游戏必须由解锁器启动，游戏本身就需要管理员权限了，所以负责启动的也是需要的
### 默认热键
- **END** 开/关
- **上方向键** 增大FPS上限 （+20）
- **下方向键** 减少FPS上限 （-20）
- 源里默认的FPS数值是120

## 注意
- 已经在新号上测试了两星期，目前并没有任何异常，冒险等级30
- 使用未认证的第三方软件修改游戏数据是违反了协议条款的，后果自负
- 想要更改热键的话，修改下源里开头的定义 （[热键码](http://cherrytree.at/misc/vk.htm)）
- 要转载的话随便，毕竟开源，可以的话就注明下出处
- 这么个破工具请不要拿去倒卖
