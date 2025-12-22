# Chapter 3: Char Drivers

## Major and Minor Numbers

using ls -l /dev command can see char type, block type devices, and major number, minor number

![alt text](image.png)

major number : 傳統上用來標示 device 所連接的 driver，現代 Linux kernel 允許多的 driver 共享 major number，但大部分 device 仍按照一個 major number 一個 driver來組織。

Major number — 識別 driver 類型（或 driver 的入口）

minor number : 被 kernel 用來決定要使用?(referred to)哪個 device。

Minor number — driver 內部定義的「裝置實例識別」

重點：major 是 kernel 路由 (dispatch) 的依據 — 當 user-space open(/dev/foo) 時，VFS 讀到 inode 的 device number (major, minor)，就用 major 找到要呼叫哪個 driver 的入口。

Kernel 對 minor 的理解非常淺：它只是個整數，kernel 不知道「這個 minor 代表什麼硬體」，除非是某些標準化的子系統（例如 block partitioning 有慣例）。

所以 driver 寫法通常會把 minor 當 index 去 lookup 自己維護的資料結構（或把 cdev 嵌入 device struct，open 時由 inode->i_cdev 反推 device pointer）。