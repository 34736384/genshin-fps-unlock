release : unlockfps_nc/bin/ReleaseMin/net8.0-windows/win-x64/publish/unlockfps_nc.exe

UnlockerStub/UnlockerStub.dll :
	make -C $(@D)

unlockfps_nc/Resources/%.dll : UnlockerStub/%.dll
	cp $^ $@

unlockfps_nc/bin/%/net8.0-windows/win-x64/publish/unlockfps_nc.exe : unlockfps_nc/unlockfps_nc.csproj unlockfps_nc/Resources/UnlockerStub.dll
	dotnet publish $< -c $* -r win-x64 -f net8.0-windows --self-contained false -p:PublishSingleFile=true -p:PublishReadyToRun=false

clean :
	rm -rf UnlockerStub/UnlockerStub.dll unlockfps_nc/Resources/UnlockerStub.dll.dll unlockfps_nc/bin
