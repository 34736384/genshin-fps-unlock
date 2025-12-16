using unlockfps_nc.Utility;

namespace unlockfps_nc.Service;

public sealed class MainPageXInputService
{
    private enum InputState
    {
        Standby,
        FpsAdjustSlow,
        FpsAdjustFast,
    }
    private const int SCAN_DELAY_NOT_CONNECTED = 3000;
    private const int SCAN_DELAY_NORMAL_KEY = 100;
    private const int SCAN_DELAY_FPS_ADJUST_SLOW = 100;
    private const int SCAN_DELAY_FPS_ADJUST_FAST = 1;
    private const int FPS_ADJUST_FAST_STEPIN = 1;
    private const int FPS_ADJUST_SLOW_COUNT_THRESHOLD = 10;
    private void StartLoop(SynchronizationContext syncCtx, CancellationToken cancellationToken)
    {
        Task.Run(async () =>
        {
            var inputState = InputState.Standby;
            int fpsSlowCount = 0, fpsDirection = 1;
            do
            {
                try
                {
                    var keystrokeRes = Native.XInputGetKeystroke(XUserIndex.XUSER_INDEX_ANY, 0, out var keystroke);
                    if (keystrokeRes == XInputGetKeystrokeResult.ERROR_DEVICE_NOT_CONNECTED)
                    {
                        await Task.Delay(SCAN_DELAY_NOT_CONNECTED, cancellationToken);
                        continue;
                    }
                    int delay;
                    var isTrigger = keystroke.VirtualKey is XKeystrokeCode.VK_PAD_LTRIGGER or XKeystrokeCode.VK_PAD_RTRIGGER;
                    var isKeyDown = (keystroke.Flags & XKeystrokeFlags.XINPUT_KEYSTROKE_KEYDOWN) != 0;
                    var isKeyUp = (keystroke.Flags & XKeystrokeFlags.XINPUT_KEYSTROKE_KEYUP) != 0;
                    var isKeyRepeat = (keystroke.Flags & XKeystrokeFlags.XINPUT_KEYSTROKE_REPEAT) != 0;
                    switch ((inputState, isKeyDown, isKeyUp))
                    {
                        case (InputState.Standby, true, _) when !isKeyRepeat:
                            {
                                fpsSlowCount = 0;
                                switch (keystroke.VirtualKey)
                                {
                                    case XKeystrokeCode.VK_PAD_B:
                                        syncCtx.Post(_ => KeyBPressed?.Invoke(this, EventArgs.Empty), null);
                                        delay = SCAN_DELAY_NORMAL_KEY;
                                        break;
                                    case XKeystrokeCode.VK_PAD_Y:
                                        syncCtx.Post(_ => KeyYPressed?.Invoke(this, EventArgs.Empty), null);
                                        delay = SCAN_DELAY_NORMAL_KEY;
                                        break;
                                    case XKeystrokeCode.VK_PAD_LTHUMB_PRESS:
                                        syncCtx.Post(_ => KeyLCenterPressed?.Invoke(this, EventArgs.Empty), null);
                                        delay = SCAN_DELAY_NORMAL_KEY;
                                        break;
                                    case XKeystrokeCode.VK_PAD_LTRIGGER:
                                        syncCtx.Post(_ => FpsAdjustPressed?.Invoke(this, -1), null);
                                        delay = SCAN_DELAY_FPS_ADJUST_SLOW;
                                        inputState = InputState.FpsAdjustSlow;
                                        fpsDirection = -1;
                                        break;
                                    case XKeystrokeCode.VK_PAD_RTRIGGER:
                                        syncCtx.Post(_ => FpsAdjustPressed?.Invoke(this, 1), null);
                                        delay = SCAN_DELAY_FPS_ADJUST_SLOW;
                                        inputState = InputState.FpsAdjustSlow;
                                        fpsDirection = 1;
                                        break;
                                    default:
                                        delay = SCAN_DELAY_NORMAL_KEY;
                                        break;
                                }
                                break;
                            }
                        case (InputState.FpsAdjustSlow or InputState.FpsAdjustFast, _, true):
                        case (InputState.FpsAdjustSlow or InputState.FpsAdjustFast, true, _) when !isTrigger:
                            {
                                delay = SCAN_DELAY_NORMAL_KEY;
                                inputState = InputState.Standby;
                            }
                            break;
                        case (InputState.FpsAdjustSlow, _, false):
                            {
                                syncCtx.Post(_ => FpsAdjustPressed?.Invoke(this, fpsDirection), null);
                                fpsSlowCount++;
                                if (fpsSlowCount >= FPS_ADJUST_SLOW_COUNT_THRESHOLD)
                                {
                                    fpsSlowCount = FPS_ADJUST_SLOW_COUNT_THRESHOLD;
                                    inputState = InputState.FpsAdjustFast;
                                    delay = SCAN_DELAY_FPS_ADJUST_FAST;
                                }
                                else
                                {
                                    delay = SCAN_DELAY_FPS_ADJUST_SLOW;
                                }
                            }
                            break;
                        case (InputState.FpsAdjustFast, _, false):
                            {
                                syncCtx.Post(_ => FpsAdjustPressed?.Invoke(this, fpsDirection * FPS_ADJUST_FAST_STEPIN), null);
                                delay = SCAN_DELAY_FPS_ADJUST_FAST;
                            }
                            break;
                        default:
                            delay = SCAN_DELAY_NORMAL_KEY;
                            break;
                    }
                    await Task.Delay(delay, cancellationToken);
                }
                catch (OperationCanceledException)
                {
                    break;
                }
            }
            while (!cancellationToken.IsCancellationRequested);
        }, cancellationToken);
    }

    public event EventHandler? KeyBPressed;
    public event EventHandler? KeyYPressed;
    public event EventHandler? KeyLCenterPressed;
    public event EventHandler<int>? FpsAdjustPressed;

    private CancellationTokenSource? _loopCancel;

    public MainPageXInputService()
    {
        Native.XInputEnable(true);
    }
    public void PauseListening()
    {
        _loopCancel?.Cancel();
    }
    public void ResumeListening()
    {
        if (_loopCancel?.IsCancellationRequested is not false)
        {
            _loopCancel?.Cancel();
            _loopCancel = new();
            var syncCtx = SynchronizationContext.Current ?? throw new InvalidOperationException("No SynchronizationContext available");
            var token = _loopCancel.Token;
            StartLoop(syncCtx, token);
        }
    }
}
