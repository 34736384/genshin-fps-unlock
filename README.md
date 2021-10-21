# Genshin Impact FPS Unlocker
 - This tool helps you to unlock the 60 fps limit in the game
 - This is an external program uses **WriteProcessMemory** to write the desired fps to  the game
 - Handle protection bypass is already included
 - Does not require a driver for R/W access
 - Supports OS and CN version
 - Should works for future updates
 - If the source needs to be updated, I'll try to do it as soon as possible
 - You can download the compiled binary over at '[Release](https://github.com/34736384/genshin-fps-unlock/releases)' if you don't want to compile it yourself
 ## Compiling
 - Use  Visual Studio 2019 Community Edition to compile
 - Not required but I know it works on this version
 ## Usage
 - Make sure you have the [Visual C++ 2019 Redistributable (x64)](https://aka.ms/vs/16/release/vc_redist.x64.exe) installed
 - If it is your first time running, run unlocker as admin, then the unlocker will ask you to open the game. This only need to be done once, it's used for acquiring the game path. Then it'll be saved to a config file. After the config is made you can start the game via the unlocker in future sessions.
 - Place the compiled exe anywhere you want
 - Make sure your game is closed, the unlocker will automatically start the game for you
 - Run the exe as administrator, and leave the exe running
 >It requires adminstrator because the game needs to be started by the unlocker and the game requires such permission
 - To inject reshade, place the reshade dll in the same folder as the unlocker
 ### Default Keybinds
 - **END** to toggle on/off
 - **HOME+UPARROW** to increase limit (+20)
 - **HOME+DOWNARROW** to decrease limit (-20)
 - **HOME+RIGHTARROW** to increase limit slightly (+2)
 - **HOME+LEFTARROW** to decrease limit slightly (-2)
 - The default fps limit is set to 120
 ## Notes
 - Tested on a new account for two weeks and no bans so far (AR30), can't guaranteed it will be safe forever, But honestly though, I doubt they would ban you for this.
 - Modifying game memory with an unauthorized third party application is a violation of the ToS, so use it at your own risk
 - If you want to change keybinds or the default fps then you can edit the defines at the top of the source
 - [Here](http://cherrytree.at/misc/vk.htm) is a list of keycodes
 - The reason that I didn't made it to be place in the same folder of the game exe is because the game will attempt to verify the files before logging on, and it will treat the unlocker as a game file too which will fail the file integrity check. Producing an 31-4302 error.
 ## Todo
 - idk maybe add keybinds and fps settings to config


# 原神解锁FPS限制

 - 工作原理类似于外部辅助，通过**WriteProcessMemory**把FPS数值写进游戏
 - 不需要通过驱动进行读写操作
 - 支持国服和外服
 - 理论上支持后续版本，不需要更新源码
 - 如果需要更新我会尽快更新

## 编译

 - 用VS2019编译，其他版本的也应该可以，没测试过
## 食用指南
 - 运行前确保系统已安装[Visual C++ 2019 Redistributable (x64)](https://aka.ms/vs/16/release/vc_redist.x64.exe)
 - 第一次运行的话先以管理员运行，然后手动打开游戏，这样解锁器能够获取到游戏路经并保存在配置文件里，这只需要执行一次，以后就可以直接用解锁器启动游戏了
 - 解锁器放哪都行
 - 运行之前确保游戏是关闭的
 - 用管理员运行解锁器
 - 解锁器不能关掉
>使用管理员运行是因为游戏必须由解锁器启动，游戏本身就需要管理员权限了，所以负责启动的也是需要的
### 默认热键
- **END** 开/关
- **HOME+上方向键** 增大FPS上限 （+20）
- **HOME+下方向键** 减少FPS上限 （-20）
- **HOME+左方向键** 减少FPS上限 （-2）
- **HOME+右方向键** 减少FPS上限 （-2）
- 源里默认的FPS数值是120

## 注意
- 已经在新号上测试了两星期，目前并没有任何异常，冒险等级30
- 使用未认证的第三方软件修改游戏数据是违反了协议条款的，后果自负
- 想要更改热键的话，修改下源里开头的定义 （[热键码](http://cherrytree.at/misc/vk.htm)）
- 至于为啥我没写成能在和游戏同一个目录下运行是因为游戏登录的时候会进行文件完整性检测，如果游戏目录内有其他文件也会当做是游戏的文件进行检测。如果把解锁器和游戏放一起的话游戏会把解锁器当成游戏文件检测，从而导致报错（31-4302）
- 要转载的话随便，毕竟开源，可以的话就注明下出处
- 这么个破工具请不要拿去倒卖
