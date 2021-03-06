簡介：

根據使用者輸入的各大專院校資料檔實作出一棵二員搜尋樹。延續上次的任務，除了建立以及搜尋外，多加入了刪除的功能以及分別輸出以學校名稱與畢業生人數為基準的"中序排序檔"，再將此兩個檔案重新讀入，並分別建立一棵新的平衡二元搜尋樹。
假設使用者欲刪除某一節點，若此節點沒有子孫，則直接刪除；若此節點有子孫則由中序排序的下一個資料遞補。
假設使用者欲重新建立一棵平衡二元搜尋樹，需先得到中序排序法的順序，在每次砍半取中點當作根並遞迴之。

說明自行設計的資料檔和實驗程序以觀察樹高對搜尋效率的影響，比較結果必須是
明確的量化數據，格式如下：
(校名樹高 = g1, 搜尋效率 = u1), (校名樹高 = g2, 搜尋效率 = u2), …
(人數樹高 = h1, 搜尋效率 = v1), (人數樹高 = h2, 搜尋效率 = v2), …

