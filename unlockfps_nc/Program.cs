using Microsoft.Extensions.DependencyInjection;
using System.Runtime.InteropServices;
using unlockfps_nc.Service;
using unlockfps_nc.Utility;

namespace unlockfps_nc
{
    internal static class Program
    {
        private static readonly string MutexName = "286B345F-A2EB-4FF3-83E9-2DD83B87694A";
        private static readonly string EventName = "B2ABB8F2-E6B2-4E31-8A11-15F969ADF755";
        public static IServiceProvider ServiceProvider { get; private set; }

        [STAThread]
        static void Main()
        {
            if (File.Exists("YuanShen.exe") || File.Exists("GenshinImpact.exe"))
            {
                MessageBox.Show(@"Do not place the unlocker in the game folder.", @"Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            bool isFirst;
            using var mutex = new Mutex(true, MutexName, out isFirst);

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

                        form.Invoke(() => {
                            Native.ShowWindow(form.Handle, 9); // SW_RESTORE
                            Native.SetForegroundWindow(form.Handle);
                        });

                    }

                }
            });

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