# PowerRename Standalone

从 Microsoft PowerToys 中拆分出的独立版批量重命名工具，保留核心重命名能力与资源管理器右键集成，并提供独立管理界面。

## 项目现状与定位

- **不是完整 PowerToys 仓库**：当前解决方案聚焦 `PowerRename` 相关组件。
- **核心目标**：独立运行 `PowerRename`，无需安装完整 PowerToys。
- **上游来源**：核心引擎、Shell 扩展与 UI 基于 PowerToys 实现演进。

## 核心能力

- 正则搜索/替换（可切换标准库/Boost.Regex 引擎）
- 实时预览重命名结果（原名 / 新名双栏）
- 文件名范围控制（仅文件名 / 仅扩展名 / 全名）
- 文本格式化（大写、小写、标题格式、首字母大写）
- 计数器与随机值替换（如 `${start=10}`、`${ruuidv4}`）
- 时间占位符替换（如 `$YYYY`、`$MM`、`$DD`）
- 元数据占位符替换（EXIF/XMP，支持切换数据源）
- 资源管理器右键集成（经典菜单 + Win11 现代菜单链路）

## 运行模式

### 1) 管理模式

直接运行 `PowerToys.PowerRename.exe`（无输入文件）：

- 首页：功能说明、快速入口
- 设置：右键菜单注册状态、扩展菜单显示、MRU、Boost 开关
- 关于：版本/来源/链接

### 2) 重命名模式

- 通过资源管理器右键触发（文件/文件夹/目录背景）
- 或命令行传入路径：

```bat
PowerToys.PowerRename.exe "C:\path\a.txt" "C:\path\b.txt"
```

## 架构概览

`PowerRename.sln` 主要包含以下工程：

- `src/modules/powerrename/lib/PowerRenameLib.vcxproj`：重命名核心逻辑（规则、枚举器、随机器、元数据提取、设置读写）
- `src/modules/powerrename/dll/PowerRenameExt.vcxproj`：经典 Shell 扩展（InProc COM）
- `src/modules/powerrename/PowerRenameContextMenu/PowerRenameContextMenu.vcxproj`：Win11 现代右键菜单组件 + MSIX 打包
- `src/modules/powerrename/PowerRenameUILib/PowerRenameUI.vcxproj`：WinUI 3 前端（主窗口 + 管理窗口）
- `src/common/*`：日志、主题、设置 API、工具函数、遥测等公共依赖

## 构建说明

### 环境要求

- Windows 10/11（工程最小平台版本配置为 `10.0.19041.0`）
- Visual Studio 2022 + MSVC v143
- Windows SDK 10.0.26100.0（项目配置目标）
- 可访问 NuGet 源（见 `nuget.config`）

### 编译（Release / x64）

在 VS 开发者命令行环境中执行：

```bat
msbuild PowerRename.sln /t:Restore /p:RestorePackagesConfig=true
msbuild PowerRename.sln /p:Configuration=Release /p:Platform=x64
```

## 主要输出（`x64\Release\WinUI3Apps`）

| 文件 | 作用 |
|---|---|
| `PowerToys.PowerRename.exe` | 主程序（管理模式/重命名模式入口） |
| `PowerToys.PowerRenameExt.dll` | 经典右键菜单扩展 |
| `PowerToys.PowerRenameContextMenu.dll` | Win11 现代菜单扩展组件 |
| `PowerRenameContextMenuPackage.msix` | 现代菜单 MSIX 包 |
| `register.ps1` / `unregister.ps1` | 右键菜单注册/卸载脚本（输出目录内） |

## 右键菜单注册

在输出目录执行（管理员 PowerShell）：

```powershell
.\register.ps1
.\unregister.ps1
```

## 替换语法速查

- **正则**：`^` `$` `\d` `\w` 等
- **时间**：`$YYYY` `$YY` `$MM` `$DD` `$hh` `$mm` `$ss` `$fff`
- **计数器**：`${}` `${start=10}` `${increment=5}` `${padding=4}`
- **随机**：`${rstringalnum=9}` `${rstringalpha=8}` `${rstringdigit=6}` `${ruuidv4}`
- **元数据（示例）**：`$CAMERA_MAKE` `$CAMERA_MODEL` `$DATE_TAKEN_YYYY` `$TITLE` `$CREATOR` `$CREATE_DATE_YYYY`

元数据匹配主要面向这些格式：`jpg/jpeg/png/tif/tiff/heic/heif/avif`。

## 设置与数据

- 模块设置文件位于 `%LOCALAPPDATA%\ALp_Studio\PowerRename\PowerRename\power-rename-settings.json`。
- 上次运行状态位于 `%LOCALAPPDATA%\ALp_Studio\PowerRename\PowerRename\power-rename-last-run-data.json`。
- 日志位于 `%LOCALAPPDATA%\ALp_Studio\PowerRename\PowerRename\Logs\<版本号>\log.log`。
- 如排查配置不生效，优先对照 `src/modules/powerrename/lib/Settings.cpp` 与 `src/modules/powerrename/PowerRenameUILib/PowerRenameXAML/SettingsPage.xaml.cpp`。

## 测试相关（补充）

仓库包含但未纳入当前 `PowerRename.sln` 的测试工程：

- `src/modules/powerrename/unittests/PowerRenameLibUnitTests.vcxproj`
- `src/modules/powerrename/PowerRenameUITest/PowerRename.UITests.csproj`
- `src/modules/powerrename/PowerRename.FuzzingTest/PowerRename.FuzzingTest.vcxproj`

## 许可证与致谢

- 上游项目：[Microsoft PowerToys](https://github.com/microsoft/PowerToys)（MIT）
- 适配来源：[ALp Studio](https://re-tikara.fun)
