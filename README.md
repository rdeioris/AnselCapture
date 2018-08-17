# AnselCapture
Hack of the official Unreal Engine Ansel plugin for allowing continuous capturing (360 videos)

![Alt text](screenshots/CaptureAnsel.PNG?raw=true "AnselCapture Screenshot")

This plugin is a refactoring of the Epic's official one (https://docs.unrealengine.com/en-us/Engine/Plugins/Ansel/Overview) to allow multiple captures using Nvidia Ansel technology.

Example here: https://youtu.be/e9jkIB9YLw8

As the Ansel api does not allow to trigger 'snaps' programmatically, this plugin uses a brutal hack by sending raw input event (spacebar pressing) to fake the Ansel gui to generate a new screenshot (after the world tick has advanced):

```c
INPUT SpaceBar = { 0 };
SpaceBar.type = INPUT_KEYBOARD;
SpaceBar.ki.wVk = VK_SPACE;
SendInput(1, &SpaceBar, sizeof(INPUT));
SpaceBar.ki.dwFlags = KEYEVENTF_KEYUP;
SendInput(1, &SpaceBar, sizeof(INPUT));
```

Currently only Unreal Engine 4.20 is supported.

## How to use it

You can download a binary release from https://github.com/rdeioris/AnselCapture/releases or just clone this repository in the Plugins directory of your project (in this second case you obviously need to compile it).

Ensure the official 'Ansel' plugin is disabled and then enable the 'AnselCapture' one (read: this one).

After having restarted the editor just setup your project for starting the Ansel session using a Blueprint:

![Alt text](screenshots/CaptureAnselBlueprint.PNG?raw=true "AnselCapture Level Blueprint Screenshot")

as you can note, forcing a fixed frame rate is highly suggested.

Two Blueprint UFunctions are exposed: "Start Ansel Capture" and "Stop Ansel Capture"

Note: the plugin uses the Nvidia libraries already included in the engine for the official 'Ansel' plugin.

## Differences with the official 'Ansel' plugin

Contrary to the oficial one, this plugin does not enforce disabling of features (like the HUD, fading, and so on). This is mainly for leaving it super-simple (so users can easily hack it) and because technically there is little sense in not building an ad-hoc level for registering a 360 video. Postprocessing effects disabled by the official plugin, are disabled here too.

The other big refactoring is the UpdateCamera() function: in this plugin it is heavy-commented and refactored to be more clear (and again to simplify hacking of it).
