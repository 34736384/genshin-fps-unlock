using Microsoft.Extensions.DependencyInjection;
using System.Runtime.InteropServices;
using unlockfps_nc.Service;
using unlockfps_nc.Utility;

namespace unlockfps_nc
{
    internal static class Program
    {
        private static Mutex MutexHandle = new(true, "GenshinFPSUnlocker");
        public static IServiceProvider ServiceProvider { get; private set; }

        [STAThread]
        static void Main()
        {
            if (File.Exists("YuanShen.exe") || File.Exists("GenshinImpact.exe"))
            {
                MessageBox.Show(@"Do not place the unlocker in the game folder.", @"Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (!MutexHandle.WaitOne(TimeSpan.Zero, true)) {
                
                var window = Native.FindWindow(null, "Genshin FPS Unlocker");
                if (window != IntPtr.Zero) {
                    Native.ShowWindow(window, 9); // SW_RESTORE
                    Native.SetForegroundWindow(window);
                    return;
                }

                MessageBox.Show(@"Another instance of the unlocker is already running.", @"Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            var services = new ServiceCollection();
            services.AddTransient<MainForm>();
            services.AddTransient<SettingsForm>();
            services.AddTransient<SetupForm>();
            services.AddSingleton<ConfigService>();
            services.AddSingleton<ProcessService>();
            services.AddSingleton<IpcService>();

            ServiceProvider = services.BuildServiceProvider();

            ApplicationConfiguration.Initialize();
            Application.Run(ServiceProvider.GetRequiredService<MainForm>());
        }


    }
}