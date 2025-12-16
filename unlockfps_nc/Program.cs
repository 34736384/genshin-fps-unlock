using Microsoft.Extensions.DependencyInjection;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Security.Principal;
using unlockfps_nc.Service;
using unlockfps_nc.Utility;

namespace unlockfps_nc
{
    internal static class Program
    {
        private static readonly string MutexName = "286B345F-A2EB-4FF3-83E9-2DD83B87694A";
        private static readonly string EventName = "B2ABB8F2-E6B2-4E31-8A11-15F969ADF755";
        public static IServiceProvider ServiceProvider { get; private set; }
        public static int Version => 3500;

        [STAThread]
        static void Main()
        {
            if (File.Exists("YuanShen.exe") || File.Exists("GenshinImpact.exe"))
            {
                MessageBox.Show(@"Do not place the unlocker in the game folder.", @"Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            using var mutex = new Mutex(true, MutexName, out var isFirst);

            if (!isFirst) {
                // second instance
                try {
                    using var evt = EventWaitHandle.OpenExisting(EventName);
                    evt.Set();
                }
                catch { }
                return;
            }

            using var showEvent = new EventWaitHandle(false, EventResetMode.AutoReset, EventName);
            _ = Task.Run(() => {
                while (showEvent.WaitOne()) {

                    var form = Application.OpenForms
                        .OfType<MainForm>()
                        .FirstOrDefault();

                    if (form is { IsHandleCreated: true }) {
                        form.RestoreFromTray();
                    }

                }
            });

            if (!IsAdministrator()) {
                try {
                    ProcessStartInfo processInfo = new ProcessStartInfo
                    {
                        FileName = Application.ExecutablePath,
                        UseShellExecute = true,
                        Verb = "runas"
                    };
                    Process.Start(processInfo);
                }
                catch {
                    // ignored
                }

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

        static bool IsAdministrator()
        {
            using WindowsIdentity identity = WindowsIdentity.GetCurrent();
            WindowsPrincipal principal = new WindowsPrincipal(identity);
            return principal.IsInRole(WindowsBuiltInRole.Administrator);
        }

    }
}