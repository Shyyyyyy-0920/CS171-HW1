# HW1 项目实现口头自查

更新日期：2026-10-10  
共 32 题，8 个模块。题目依据当前项目代码，重点检查实际功能、实现方法和容易误解的关键步骤。

可以直接用语言回答，结合你使用的变量、函数或 shader 计算说明即可。每题围绕一个具体实现问题展开，不要求手算数值、逐项展开矩阵或背诵 API 参数。答不完整时，写出你已理解的部分和卡住的一步，之后按题号补讲。

## 1. 模型加载与实际绘制

对应代码：[src/Mesh.cpp](../src/Mesh.cpp)、[src/Shader.cpp](../src/Shader.cpp)、[src/Main.cpp](../src/Main.cpp)。

### Q01 模型文件怎样变成可绘制的顶点？

你的 .object 文件把位置和法线分开保存。Mesh 是怎样通过一条三角形记录把它们组合成 Vertex，并生成最终 indices_ 的？同一个位置配不同法线时，为什么不能只按位置索引处理？

回答：

### Q02 VAO、VBO、EBO 在一次绘制中怎样配合？

结合你写的 Mesh，说明顶点数据放在哪里、顶点的 position/normal 怎样被 shader 识别，以及 Draw 怎样通过索引画出三角形。重点说明 VAO 记录的是什么。

回答：

### Q03 你写的 Shader 类怎样让 GLSL 参与绘制？

从读取顶点与片元源码到得到可使用的 program，介绍编译、链接和 Use 的作用。Main 中的 Set 怎样把矩阵或灯光参数传过去，为什么要先激活对应的 program？

回答：

### Q04 多个对象为什么能使用同一套着色方式却显示在不同位置？

说明 MA、MB、MC、MD 怎样分别作用于各自对象。重点解释兔子的平移—缩放—平移顺序：为什么只放大模型后再随便平移，未必能把选定的中心放到 Bunny.Position？

回答：

## 2. 摄像机移动与旋转

对应代码：[src/Main.cpp](../src/Main.cpp)、[src/Math.cpp](../src/Math.cpp)。

### Q05 你是如何实现摄像机功能的？

从 Main 中的 eye、direction 和 lookAt 调用出发，分别说明移动与转头改变了什么。为什么摄像机运动可以通过改变 V 实现，而不用修改所有物体的顶点？

回答：

### Q06 前后、左右、上下移动的方向怎样确定？

分别解释 W/S、A/D、Space/Ctrl 使用的方向。为什么横移要计算 direction.Cross(up) 并归一化？抬头后按 W，摄像机会沿水平面前进还是沿视线前进？

回答：

### Q07 为什么键盘移动要乘 dt，鼠标坐标差却不采用相同处理？

说明这两类输入分别表示持续速度还是已经发生的位移。它们怎样影响不同帧率下的移动与转头行为？

回答：

### Q08 鼠标移动怎样转成视角变化？

结合 MouseCallback，说明上一帧鼠标坐标、dx/dy、灵敏度和 yaw/pitch 的关系。为什么第一次回调只保存坐标，dy 又采用上次 y 减当前 y？

回答：

### Q09 鼠标静止后，为什么视角不会继续转动，也不会自动回正？

说明你保存的是累计角度还是单次增量，以及为什么每帧从 forward 重建 direction。若把累计角度不断作用在上一帧 direction 上，会有什么问题？

回答：

### Q10 偏航与俯仰为什么使用不同的旋转轴？

说明 yaw 绕 up、pitch 绕当前 direction.Cross(up) 的含义。为什么还要把 pitch 限制在 ±89 度，限制的是哪一种退化？

回答：

## 3. 自写矩阵函数与坐标变换

对应代码：[src/Math.cpp](../src/Math.cpp)、[assets/shaders/model.vert](../assets/shaders/model.vert)。

### Q11 一个模型顶点怎样依次经过 M、V、P 到达屏幕？

用语言解释三个矩阵各自改变哪一个坐标空间，以及为什么当前写成 P*V*M 的顺序。位置的 w=1 与方向的 w=0 有什么实际区别？

回答：

### Q12 你的 rotate 怎样实现绕任意轴旋转？

解释旋转轴归一化的必要性，以及代码中轴方向投影、叉积矩阵和 sin/cos 三部分的几何作用。不需要逐项展开矩阵，但要说清这些部分怎样组成旋转。

回答：

### Q13 你的 lookAt 怎样建立摄像机坐标系？

说明 f、r、u 是怎样得到的，为什么使用 -f，以及最后一列的点积为什么能处理摄像机位置。为什么不能仅把 eye 的三个分量取负填进去？

回答：

### Q14 perspective 为什么能产生近大远小？

说明 fovY、aspect、near/far 分别控制什么，投影怎样借助 clip 的 w 和后续透视除法改变屏幕大小。为什么相机空间 z 不能直接当作深度缓冲值？

回答：

## 4. 光照的整体思路与关键计算

对应代码：[assets/shaders/model.vert](../assets/shaders/model.vert)、[assets/shaders/model.frag](../assets/shaders/model.frag)、[src/Main.cpp](../src/Main.cpp)。

### Q15 你的光照是怎样实现的？

先介绍环境、漫反射、镜面反射各模拟什么，再说明 Main 提供哪些参数、model.vert 传递哪些数据、model.frag 怎样通过 light 函数组合最终颜色。

回答：

### Q16 为什么光照的位置、方向和法线必须处于同一空间？

结合 worldPosition、worldNormal、eye 和光源位置说明你选择的空间。重点解释法线为什么不接受平移、插值后为什么重新归一化，以及当前 mat3(M)*n 对模型变换有什么适用限制。

回答：

### Q17 漫反射为什么使用法线与光照方向的点积？

说明 L 的方向、点积反映的夹角关系，以及为什么需要把负结果截为零。物体颜色与光源颜色怎样共同影响这一项？

回答：

### Q18 镜面反射为什么使用 reflect(-L,N) 和观察方向？

说明 -L、R、V 各自朝向，ks 与 s 分别控制什么，以及为什么背光时还要把镜面项设为零。摄像机移动时，高光为何会变化？

回答：

### Q19 聚光源怎样判断当前片元是否在光锥内？

说明 gDirection 与从光源指向片元的方向怎样比较，为什么上传 cosCutoff，而不是直接上传角度。当前写法会得到硬边还是平滑边缘？

回答：

### Q20 两种灯光怎样同时照亮对象，并体现颜色差异？

结合 pointColor、gColor 和最终颜色相加说明。为什么 ambient 放在 light 函数外面，只加一次，而不是每调用一个光源都加一遍？

回答：

## 5. 准星射线与对象命中判断

对应代码：[src/Math.cpp](../src/Math.cpp)、[src/Main.cpp](../src/Main.cpp)。

### Q21 准星瞄准怎样变成一条拾取射线？

说明射线起点、方向和参数 t 的含义。为什么 direction 与 eye+direction 不能混用？当方向不是单位向量时，t 是否仍等于物理距离？

回答：

### Q22 OnSphere 怎样判断命中，并选择交点？

用语言介绍求交得到两个根后如何选择正前方最近的交点。重点说明摄像机在球内、位于球心，以及接近相切时，你的代码分别怎样处理。

回答：

### Q23 OnPlane 怎样确认命中了有限正方形？

说明为什么求出射线与无限平面的交点后，还要检查 x/y 边界。当前判断为什么适用于你的平面，而不能仅修改 normal 就自动支持任意旋转的正方形？

回答：

### Q24 兔子为什么也能用 OnSphere 拾取？

说明你使用的球形代理与真正兔子网格有何区别，半径怎样与放大后的兔子对应。准星没有碰到兔子轮廓时，是否仍可能选中它？

回答：

## 6. 选中与按住移动对象

对应代码：[src/Main.cpp](../src/Main.cpp)、[src/Math.cpp](../src/Math.cpp)。

### Q25 鼠标按下时，程序怎样决定选中哪个对象？

说明 nearestHitIndex 如何从各对象的 t 中选择最近有效命中，leftPressed 与 leftReleased 怎样维持或结束 select。为什么按住期间不应每帧重新选中？

回答：

### Q26 为什么抓取时先保存相机空间位置，之后再转回世界空间？

说明 objectCatchPosition=V*物体中心与之后 V.Inverse()*objectCatchPosition 各自的用途。两次使用的 V 为什么可能不同，为什么这并不等于什么都没改变？

回答：

### Q27 按住后转头、移动和松开，各会怎样影响物体？

说明什么量在抓取期间保持不变，新的世界 Position 怎样进入模型矩阵，松开后为什么能留在新位置。当前保持的是相对位置，还是连物体朝向也一起保持？

回答：

## 7. 天空盒加载、采样与深度处理

对应代码：[src/Texture.cpp](../src/Texture.cpp)、[src/Main.cpp](../src/Main.cpp)、[assets/shaders/skybox.vert](../assets/shaders/skybox.vert)、[assets/shaders/skybox.frag](../assets/shaders/skybox.frag)。

### Q28 六张图片怎样成为一个能被 shader 采样的天空盒？

说明 Texture 如何把图片上传到同一个 cubemap 的六个面，绘制时怎样连接到 samplerCube。纹理对象 id、纹理单元 0 和 skyboxTexture 之间是什么关系？

回答：

### Q29 为什么天空盒保留相机旋转，却去掉平移？

结合 Vsky 与 sampleDirection=p 说明。摄像机移动和转头时，背景应该分别怎样表现？为什么采样使用方向，而不直接用投影后的 clipPosition？

回答：

### Q30 为什么把天空盒 clip 的 z 设为 w，并使用 GL_LEQUAL？

说明透视除法后的深度，以及已有物体位置和空白背景位置分别怎样通过或拒绝深度比较。若改成 z=1 或 GL_LESS，会破坏什么？

回答：

### Q31 天空盒的深度测试与深度写入有什么区别？

说明当前为什么保留测试、关闭写入并在结束后恢复。在先画物体、天空盒深度固定为最远的方案中，关闭写入是否决定显示正确性？

回答：

## 8. 屏幕中心准星

对应代码：[src/Main.cpp](../src/Main.cpp)、[assets/shaders/crosshair.vert](../assets/shaders/crosshair.vert)、[assets/shaders/crosshair.frag](../assets/shaders/crosshair.frag)。

### Q32 你怎样让绿色准星固定在屏幕中心，并始终显示在物体前面？

说明固定 gl_Position、单独 VAO、GL_POINTS 和关闭深度测试各自的作用。为什么准星不需要 M、V、P，画完后又必须恢复深度测试？

回答：

## 理解缺口记录

回答后只需记录需要补讲的题号和具体卡点。例如：知道鼠标会改变方向，但还说不清累计角度为什么要从 forward 重新计算。

| 题号 | 已理解的部分 | 还说不清的一步 |
|---|---|---|
|  |  |  |
