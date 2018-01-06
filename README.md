"# HXEngine note" 

configuration
================================================================================
visual studio 2015  x86  libfbxsdk-md.lib自行下载（超过100M GIT不让上传）

OpenGL RenderSystem:
================================================================================
FBX模型加载、骨骼动画、数学库、UI字体、DDS/PNG加载、相机系统、光照、材质、阴影、SKYBOX、FOG、场景可配置化

TODO:
编辑器、八叉树场景管理、OIT、HDR、PBS、deferred lighting、lighting map、GI

使用右手坐标系
列主序向量 列主序矩阵
FBX导出UV后V要翻转下：V = 1- V (HLSL #define UNITY_UV_STARTS_AT_TOP 1)

GDI RenderSystem:
================================================================================
游戏窗口创建及循环 GDI 数学库 相机 固定流水线 模型加载
使用左手坐标系     由 UVN N方向决定   背面裁剪三角形缠绕方向及法线方向
行主序向量 行主序矩阵	最后渲染X轴反转以保持与OPENGL方向一致
FBX导出UV后V要翻转下：V = 1- V (#define UNITY_UV_STARTS_AT_TOP 1)
世界空间背面消除

TODO:
渲染管道硬件加速
UI  
提升FPS

cpu:
	世界空间gameobject:
		四叉树、八叉树、BSP、PVS、PORTAL(不需要每帧更新变化，游戏开始时固定生成的数据结构)
		Frustum culling    CullSphere(只需把中心点转换到视图空间进行判断)
	renderlist:
		cull back
gpu:
	投影齐次裁剪空间renderlist:
		Frustum culling 
		Frustum cliping-->填充平底和平顶三角形时，丢弃屏幕外像素
		
		
逆矩阵求法  仿射矩阵判断  法线MV逆转置操作

D3D RenderSystem:
================================================================================

Vulkan RenderSystem:
================================================================================

<img class="shadow" src="./1.png" width="600">