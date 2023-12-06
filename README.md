# 競プロするときのライブラリ郡

適当に書き連ねてるだけなので、あんまり信用性がありません  
まあ参考程度に見ていって下さい :3  

## 全般(?)
・競プロ用template(必ず張るやつ)

## データ構造
・SegmentTree(非再帰)  
・遅延SegmentTree(非再帰)  
・BinaryIndexedTree  
## グラフ
・Unionfind  
・重み付き Unionfind  
・部分永続 Unionfind  
・Bellman-Ford  
・Dijkstra  
・Ford-Fulkerson  
・Dinic  
・強連結成分分解(SCC)  
・LowLink (成分分解はしない)  
・彩色数(完全には理解してない)  
## 数学
・Matrix  
・拡張ユークリッド互除法(ちょっとまだよくわかってない)
## Mod
・Modint  
・二項係数  
## DP
・最大正方形  
・最大長方形  
## 文字列
・RollingHash(弱い)  
・RollingHash2D(かなり特殊な例しかつかえない)  
・Z-algorithm
## 幾何
・幾何template(Circleの交差判定と交点作成ができます)  
## 実装
・サイコロ(こわい)  
・転倒数(ジャンルがわからない)  
## 全探索系？
・ナップザック問題(重複なし) O(Nmin(価値のあり得る値の数, 重みのあり得る値の数)) あるいは O(2^(N/2)) 
## 木
・全方位木DP   
・根付き木(ダブリング・LCAによる u, v 区間のクエリ)  
・木の直径(パス)
