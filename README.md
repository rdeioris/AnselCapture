# AnselCapture
Hack of the official Unreal Engine Ansel plugin for allowing continuous capturing (360 videos)

![Alt text](screenshots/CaptureAnsel.PNG?raw=true "AnselCapture Screenshot")

This plugin is a refactoring of the Epic's official one (https://docs.unrealengine.com/en-us/Engine/Plugins/Ansel/Overview) to allow multiple capturing using Nvidia Ansel technology.

As the Ansel api does not allow to trigger 'snaps' programmatically, i use a brutal hack sending raw input event (spacebar pressing) to fake the Ansel gui:

```c
INPUT SpaceBar = { 0 };
SpaceBar.type = INPUT_KEYBOARD;
SpaceBar.ki.wVk = VK_SPACE;
SendInput(1, &SpaceBar, sizeof(INPUT));
SpaceBar.ki.dwFlags = KEYEVENTF_KEYUP;
SendInput(1, &SpaceBar, sizeof(INPUT));
```
