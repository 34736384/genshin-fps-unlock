
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
 - Make sure you have the [Visual C++ 2019 Redistributable (x64)](https://aka.ms/vs/16/release/vc_redist.x64.exe) and [.NET Framework 4.8](https://dotnet.microsoft.com/en-us/download/dotnet-framework/net48) installed
 - If it is your first time running, unlocker will attemp to find your game through registry. If it failes then it will ask you to either browse or run the game.
 - Place the compiled exe anywhere you want
 - Make sure your game is closed, the unlocker will automatically start the game for you
 - Run the exe as administrator, and leave the exe running
 >It requires adminstrator because the game needs to be started by the unlocker and the game requires such permission
 - To inject other third party plugins (e.g. reshade), go to `Options->Settings->DLLs` and click add

## Version 2.0.0 Changes
 - Removed key binds
 - Added a GUI (should removed the need for keybinds)
 - Added interactable lauch option configurations (Located under `Options->Settings->Lauch Options`) 
 - Added some QoL features, such as start minimized, minimize to tray, game process priority, and power saving
 - **Minimize to tray**: Whenever you click minimize or have the `Start Minimized` option checked, the unlocker will automatically minimize to tray
 - **Game Process Priority**: Changes the process priority on start, and it will be saved in config too!
 - **Power Saving**: Automatically sets the fps limit to 10 and low process priority upon losing focus to the game (e.g. tabbing out of game)
 - Added a slider and an input box for changing fps cap
 - Added an icon
 - Added game path detection through registry, will fallback to old method if it fails with registry
 - You can choose different installation of the game in `Options->Setup`
 ## Notes
 - My test account is currently AR55, can't guaranteed it will be safe forever, But honestly though, I doubt they would ban you for this.
 - Modifying game memory with an unauthorized third party application is a violation of the ToS, so use it at your own risk (same thing applies for injecting reshade)
 ## Todo
 - idk maybe add localization or game predownload

# Desbloqueador de FPS de Genshin Impact
 - Esta herramienta te ayuda a desbloquear el límite de 60 FPS en el juego.
 - Este es un programa externo que usa **WriteProcessMemory** para escribir los fps deseados en el juego.
 - El bypass de protección ya está incluido
 - No requiere un controlador/driver para el acceso de escritura/lectura
 - Admite la versión OS y CN
 - Debería funcionar para futuras actualizaciones.
 - Si es necesario actualizar la fuente, intentaré hacerlo lo antes posible.
 - Puede descargar el binario compilado en '[Release](https://github.com/34736384/genshin-fps-unlock/releases)' si no desea compilarlo usted mismo
 ## Compilación
 - Use Visual Studio 2019 Community Edition para compilar
 - No es necesario, pero sé que funciona en esta versión
 ## Uso
 - Asegúrese de tener instalado [Visual C++ 2019 Redistributable (x64)](https://aka.ms/vs/16/release/vc_redist.x64.exe) y [.NET Framework 4.8](https://dotnet.microsoft.com/en-us/download/dotnet-framework/net48)
 - Si es la primera vez que lo ejecuta, el desbloqueador intentará encontrar su juego a través del registro. Si falla, te pedirá que navegues o ejecutes el juego.
 - Coloque el .exe compilado en cualquier lugar que desee
 - Asegúrate de que tu juego esté cerrado, el desbloqueador iniciará automáticamente el juego por ti
 - Ejecute el exe como administrador y deje el exe ejecutándose
 >Requiere administrador porque el desbloqueador debe iniciar el juego y el juego requiere dicho permiso
 - Para inyectar otros complementos de terceros (por ejemplo, reshade), vaya a `Options->Settings->DLLs` y haga clic en Agregar
## Cambios de la versión 2.0.0
 - Combinaciones de teclas eliminadas
 - Se agregó una GUI (debería eliminarse la necesidad de combinaciones de teclas)
 - Se agregaron configuraciones de opciones de inicio interactivas (ubicadas en `Options->Settings->Lauch Options`)
 - Se agregaron algunas funciones de QoL, como inicio minimizado, minimizar a la bandeja, prioridad del proceso del juego y ahorro de energía.
 - **Minimizar a la bandeja**: cada vez que haga clic en minimizar o tenga marcada la opción `Start Minimized`, el desbloqueador se minimizará automáticamente a la bandeja
 - **Prioridad del proceso del juego**: cambia la prioridad del proceso al inicio, ¡y también se guardará en la configuración!
 - **Ahorro de energía**: establece automáticamente el límite de FPS en 10 y una prioridad de proceso baja al perder el enfoque en el juego (por ejemplo, al cambiar a otro programa).
 - Se agregó un control deslizante y un cuadro de entrada para cambiar el límite de FPS
 - Se agregó un ícono
 - Se agregó detección de ruta de juego a través del registro, se recurrirá al método anterior si falla con el registro
 - Puedes elegir diferentes instalaciones del juego en `Options->Setup`
 ## Notas
 - Mi cuenta de prueba actualmente es AR55, no puedo garantizar que sea segura para siempre, pero, sinceramente, dudo que te baneen por esto.
 - Modificar la memoria del juego con una aplicación de terceros no autorizada es una violación de los Términos de servicio, así que utilícelo bajo su propio riesgo (lo mismo se aplica para inyectar reshade)
 ## Por hacer
 - No lo sé tal vez agregue traducciones o predescarga del juego

# 原神解锁FPS限制

 - 工作原理类似于外部辅助，通过**WriteProcessMemory**把FPS数值写进游戏
 - 不需要通过驱动进行读写操作
 - 支持国服和外服
 - 理论上支持后续版本，不需要更新源码
 - 如果需要更新我会尽快更新

## 编译

 - 用VS2019编译，其他版本的也应该可以，没测试过
## 食用指南
 - 运行前确保系统已安装[Visual C++ 2019 Redistributable (x64)](https://aka.ms/vs/16/release/vc_redist.x64.exe)和[.NET Framework 4.8](https://dotnet.microsoft.com/en-us/download/dotnet-framework/net48)
 - 第一次运行的话先以管理员运行，解锁器会尝试通过注册表寻找游戏路经，如果找不到的话会提示你浏览游戏位置或者开启游戏
 - 解锁器放哪都行
 - 运行之前确保游戏是关闭的
 - 用管理员运行解锁器
 - 解锁器不能关掉
>使用管理员运行是因为游戏必须由解锁器启动，游戏本身就需要管理员权限了，所以负责启动的也是需要的

## 2.0.0 版本更新
 - 看上面的英文版吧，我懒了

## 注意
- 目前我小号冒险等级55了
- 使用未认证的第三方软件修改游戏数据是违反了协议条款的，后果自负
- 要转载的话随便，毕竟开源，可以的话就注明下出处
- 这么个破工具请不要拿去倒卖

## Todo
- 本地化或者游戏预下载