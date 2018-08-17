# AnselCapture
Hack of the official Unreal Engine Ansel plugin for allowing continuous capturing (360 videos)

![Alt text](screenshots/CaptureAnsel.PNG?raw=true "AnselCapture Screenshot")

This plugin is a refactoring of the Epic's official one (https://docs.unrealengine.com/en-us/Engine/Plugins/Ansel/Overview) to allow multiple captures using Nvidia Ansel technology.

As the Ansel api does not allow to trigger 'snaps' programmatically, this plugin uses a brutal hack by sending raw input event (spacebar pressing) to fake the Ansel gui to generate a new screenshot (after the world tick has advanced):

```c
INPUT SpaceBar = { 0 };
SpaceBar.type = INPUT_KEYBOARD;
SpaceBar.ki.wVk = VK_SPACE;
SendInput(1, &SpaceBar, sizeof(INPUT));
SpaceBar.ki.dwFlags = KEYEVENTF_KEYUP;
SendInput(1, &SpaceBar, sizeof(INPUT));
```

## How to use it

You can download a binary release from https://github.com/rdeioris/AnselCapture/releases or just clone this repository in the Plugins directory of your project.

Ensure the official 'Ansel' plugin is disabled and then enable the 'AnselCapture' one (read: this one).

After having restarted the editor just setup your project for starting the Ansel session using a Blueprint:

![Alt text](screenshots/CaptureAnselBlueprint.PNG?raw=true "AnselCapture Level Blueprint Screenshot")

as you can note, forcing a fixed frame rate is highly suggested.

## Differences with the official 'Ansel' plugin

Contrary to the oficial one, this plugin does not enforce disabling of features (like the HUD, fading, and so on). This is mainly for leaving it super-simple (so users can easily hack it) and because technically there is little sense in not building an ad-hoc level for registering a 360 video.

The other big refactoring is the UpdateCamera() function: in this plugin it is heavy commented and refactored to be more clear (and again to simplify hacking of it)
