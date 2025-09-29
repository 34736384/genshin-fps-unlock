using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using unlockfps_nc.Model;

namespace unlockfps_nc.Service
{
    public class ConfigService
    {
        private static readonly string ConfigName = "fps_config.json";
        private object _lock = new();

        public Config Config { get; private set; } = new();

        public ConfigService()
        {
            Load();
            Sanitize();
        }

        private void Load()
        {
            var configPath = GetFullPath();

            if (!File.Exists(configPath))
                return;

            var json = File.ReadAllText(configPath);
            var config = JsonSerializer.Deserialize<Config>(json);

            if (config != null)
                Config = config;

        }

        private void Sanitize()
        {
            Config.FPSTarget = Math.Clamp(Config.FPSTarget, 1, 1000);
            Config.Priority = Math.Clamp(Config.Priority, 0, 5);
            Config.CustomResX = Math.Clamp(Config.CustomResX, 200, 7680);
            Config.CustomResY = Math.Clamp(Config.CustomResY, 200, 4320);
            Config.MonitorNum = Math.Clamp(Config.MonitorNum, 1, 100);
        }

        private string GetFullPath()
        {
            var currentPath = AppContext.BaseDirectory;
            return Path.Combine(currentPath, ConfigName);
        }

        public void Save()
        {
            lock (_lock) {
                var configPath = GetFullPath();
                var json = JsonSerializer.Serialize(Config, new JsonSerializerOptions { WriteIndented = true });

                bool wasHidden = false;
                if (File.Exists(configPath)) {
                    var attributes = File.GetAttributes(configPath);
                    if ((attributes & FileAttributes.Hidden) != 0) {
                        wasHidden = true;
                        File.SetAttributes(configPath, attributes & ~FileAttributes.Hidden);
                    }
                }

                try {
                    using var fs = new FileStream(configPath, FileMode.Create, FileAccess.Write, FileShare.None, 4096, FileOptions.WriteThrough);
                    using var sw = new StreamWriter(fs, Encoding.UTF8);
                    sw.Write(json);
                }
                finally {
                    if (wasHidden && File.Exists(configPath)) {
                        var attributes = File.GetAttributes(configPath);
                        File.SetAttributes(configPath, attributes | FileAttributes.Hidden);
                    }
                }
            }

        }

    }
}
