<img src="https://github.com/user-attachments/assets/52fbb6c9-e85e-4aca-97df-7deb96e5d475" width="100">

# RHI Switcher

**RHI Switcher for Blueprint** is an Unreal Engine plugin that allows you to change the Render Hardware Interface (RHI) — such as **DirectX 11**, **DirectX 12**, or **Vulkan** — directly from **Blueprints**.

This plugin changes the RHI by updating the DefaultGraphicsRHI key in the WindowsTargetPlatform.WindowsTargetSettings section of DefaultEngine.ini using GConfig->SetString when SetDesiredRHI is called with an enum value (e.g., Vulkan).

[![Support me on Ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/aldertlake)

---

## 🎮 Features

- ✅ Switch between **D3D11**, **D3D12**, and **Vulkan** via Blueprints.
- ✅ Automatically updates the correct `.ini` configuration.
- ✅ Supports packaging for **Shipping**, **Development**, and **Test** builds.
- ✅ Minimal setup, no code required.
- ⚠️ Changes take effect **after restarting** the game/application (engine limitation).

---

## 🧩 How to Use
1. Always And I Meant it run `Initialize RHI` When your game start, i would advice puting it after `Event Int` in Your GameInstance.

<img src="https://github.com/user-attachments/assets/a0b84ea9-4e24-4166-9391-b65b7c4ef65f" width="400">

2. Add the plugin to your project `Plugins` Folder.
3. Open your Blueprint and search for the node: `Set Desired RHI`.

<img src="https://github.com/user-attachments/assets/85af187a-f599-48d7-8e71-094b90c7cd1b" width="400">

4. Choose from the following RHI options:
   - DirectX 11
   - DirectX 12
   - Vulkan
5. Use `Get Current RHI` to get the current active RHI

<img src="https://github.com/user-attachments/assets/bacc7d90-5ad1-4a7a-a236-b9a9145e7b24" width="400">

6. Use `Is Relaunch Required` To verify if RHI require restart to apply

<img src="https://github.com/user-attachments/assets/5635688d-d45c-40d0-a812-5ab36905ba1c" width="400">


---

## 🔧 Additional Info

This is `Windows Only`, D'ont be a tard and run it in a mac device cuz its not going to work.

Dont Clone The repo and build this from source, just download ready binnaries in the Relase Tab.

This Plugin Is Totaly Free, If you like it dont forget to support me with at least 1 dollar LOL.

[![Support me on Ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/aldertlake)

