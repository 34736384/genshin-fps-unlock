using Microsoft.Extensions.DependencyInjection;
using System.Runtime.InteropServices;
using unlockfps_nc.Service;
using unlockfps_nc.Utility;

namespace unlockfps_nc
{
    internal static class Program
    {
        private static IntPtr MutexHandle = IntPtr.Zero;
        public static IServiceProvider ServiceProvider { get; private set; }

        [STAThread]
        static void Main()
        {
            if (File.Exists("YuanShen.exe") || File.Exists("GenshinImpact.exe"))
            {
                MessageBox.Show(@"Do not place the unlocker in the game folder.", @"Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            MutexHandle = Native.CreateMutex(IntPtr.Zero, true, @"GenshinFPSUnlocker");
            if (Marshal.GetLastWin32Error() == 183)
            {
                MessageBox.Show(@"Another unlocker is already running.", @"Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            
            var services = new ServiceCollection();
            services.AddTransient<MainForm>();
            services.AddTransient<SettingsForm>();
            services.AddTransient<SetupForm>();
            services.AddSingleton<ConfigService>();
            services.AddSingleton<ProcessService>();

            ServiceProvider = services.BuildServiceProvider();

            ApplicationConfiguration.Initialize();
            Application.Run(ServiceProvider.GetRequiredService<MainForm>());
        }


    }
}