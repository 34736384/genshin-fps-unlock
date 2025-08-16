using System.IO.Pipes;

namespace unlockfps_nc.Service
{
    public class ActivationService : IDisposable
    {
        private NamedPipeServerStream? _pipeServer;
        private CancellationTokenSource _cancellationTokenSource = new();
        private readonly MainForm _mainForm;

        public ActivationService(MainForm mainForm)
        {
            _mainForm = mainForm;
        }

        public void StartListening()
        {
            Task.Run(async () =>
            {
                while (!_cancellationTokenSource.Token.IsCancellationRequested)
                {
                    try
                    {
                        _pipeServer = new NamedPipeServerStream("GenshinFPSUnlockerActivation", PipeDirection.In, 1);
                        await _pipeServer.WaitForConnectionAsync(_cancellationTokenSource.Token);
                        
                        _mainForm.BringToForeground();
                        
                        _pipeServer.Disconnect();
                        _pipeServer.Dispose();
                    }
                    catch (OperationCanceledException)
                    {
                        break;
                    }
                    catch (Exception)
                    {
                        // Ignore pipe exceptions and continue listening
                    }
                }
            });
        }

        public static bool TryActivateExistingInstance()
        {
            try
            {
                using var pipeClient = new NamedPipeClientStream(".", "GenshinFPSUnlockerActivation", PipeDirection.Out);
                pipeClient.Connect(1000); // 1 second timeout
                return true;
            }
            catch
            {
                return false;
            }
        }

        public void Dispose()
        {
            _cancellationTokenSource.Cancel();
            _pipeServer?.Dispose();
            _cancellationTokenSource.Dispose();
        }
    }
}