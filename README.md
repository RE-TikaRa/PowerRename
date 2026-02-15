- # PowerRename Standalone

    PowerRename Standalone 是一款从 Microsoft PowerToys 中提取并优化的轻量级批量重命名工具。它通过集成 Windows 资源管理器右键菜单，为用户提供强大且直观的文件命名解决方案，且无需安装完整的 PowerToys 套件。

    ------

    ## 核心功能

    -   **右键菜单集成**：无缝支持 Windows 10 经典菜单与 Windows 11 现代右键菜单。
    -   **智能搜索替换**：支持正则表达式（可切换标准库或 Boost.Regex 引擎）。
    -   **实时结果预览**：在执行操作前，通过双栏对照实时查看重命名后的效果。
    -   **灵活范围控制**：支持仅修改文件名、仅修改扩展名或两者同时修改。
    -   **丰富格式化选项**：支持大写、小写、标题格式及首字母大写等文本转换。
    -   **动态占位符**：
        -   **计数器**：支持自定义起始值、增量及补全位数。
        -   **时间戳**：可调用系统时间（如 $YYYY, $MM, $DD 等）。
        -   **随机值**：支持生成随机字符串或 UUID。
        -   **元数据**：支持提取图片 EXIF/XMP 信息（如相机品牌、拍摄日期等）。

    ------

    ## 快速上手

    ### 1. 安装与部署

    -   **下载**：从 Releases 页面下载 `PowerRename-Standalone-x64-Release.zip` 并解压。
    -   **注册菜单**：以管理员身份运行目录下的 `register.ps1` 脚本以启用右键菜单集成。
    -   **卸载菜单**：如需移除，运行目录下的 `unregister.ps1` 即可。

    ### 2. 使用模式

    -   **交互模式**：在资源管理器中选中文件，点击右键菜单中的 PowerRename 即可开始。
    -   **管理模式**：直接运行 `PowerToys.PowerRename.exe` 可进入设置界面，调整菜单显示、引擎偏好等配置。

    ------

    ## 语法参考

    | **类型**   | **示例语法**                         | **描述**                    |
    | ---------- | ------------------------------------ | --------------------------- |
    | **计数器** | `${start=1, increment=1, padding=3}` | 生成如 001, 002, 003 的序列 |
    | **随机值** | `${ruuidv4}`                         | 插入随机的 UUID 字符串      |
    | **时间**   | `$YYYY-$MM-$DD`                      | 插入当前年-月-日            |
    | **元数据** | `$CAMERA_MODEL`                      | 插入拍摄该照片的相机型号    |

    ------

    ## 开发者说明

    ### 构建环境

    -   Windows 10/11 (Target 10.0.19041+)
    -   Visual Studio 2022 与 MSVC v143
    -   Windows SDK 10.0.26100.0

    ### 编译命令

    DOS

    ```
    msbuild PowerRename.sln /t:Restore /p:RestorePackagesConfig=true
    msbuild PowerRename.sln /p:Configuration=Release /p:Platform=x64
    ```

    构建产物将位于 `x64\Release\WinUI3Apps` 目录下。

    ------

    ## 许可证与致谢

    -   **上游来源**：[Microsoft PowerToys](https://github.com/microsoft/PowerToys) (MIT License)。
    -   **适配维护**：[ALp Studio](https://re-tikara.fun/)。

    希望这个版本更符合你的需求。如果你需要针对特定的使用场景（比如专门针对摄影师的 EXIF 重命名）补充说明，请告诉我。
