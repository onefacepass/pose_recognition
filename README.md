# pose_recognition

This project is based on [(CMU)openpose](https://github.com/CMU-Perceptual-Computing-Lab/openpose)
# OpenPose环境配置教程
### 1.安装CUDA10.1.0和Cudnn7.5.0
[cuda下载](https://developer.nvidia.com/cuda-downloads?target_os=Windows&target_arch=x86_64&target_version=10&target_type=exelocal)
![描述](https://img-blog.csdnimg.cn/20190621181146714.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2JhaXlhbmcxMDAxMA==,size_16,color_FFFFFF,t_70) 
下载完点击安装，解压在默认路径下<br />
第一步是检查系统兼容性，成功的话如下图<br />
![描述](https://img-blog.csdnimg.cn/20190621192035869.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2JhaXlhbmcxMDAxMA==,size_16,color_FFFFFF,t_70) 
没有这个阅读协议，而是其他提示，表明硬件不行！！！！。继续安装也没有意义！！！！！！！！！！<br />
Attention：cudnn需要注册NVIDIA账户<br />
Attention：显卡必须是NVIDIA显卡，[查看网址](https://developer.nvidia.com/cuda-gpus)<br />
### 2.Cudnn安装：
![描述](https://img-blog.csdnimg.cn/20190621183544990.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2JhaXlhbmcxMDAxMA==,size_16,color_FFFFFF,t_70) 
### 3.环境变量的变化（安装程序自动添加，好像不需要手动添加。没有的话手动添加）：
![描述](https://img-blog.csdnimg.cn/20190621192521578.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2JhaXlhbmcxMDAxMA==,size_16,color_FFFFFF,t_70) 
![描述](https://img-blog.csdnimg.cn/20190621192521578.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2JhaXlhbmcxMDAxMA==,size_16,color_FFFFFF,t_70) 
![描述](https://img-blog.csdnimg.cn/2019062119265369.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2JhaXlhbmcxMDAxMA==,size_16,color_FFFFFF,t_70) 
### 4.将cudnn中的文件复制到C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.1
### 5.github下载openpose到本地，解压。
### 6.移步到openpose\3rdparty\windows路径下，点击图片中的4个文件
![描述](https://img-blog.csdnimg.cn/20190621194236174.png) 
再次移步到openpose\models路径下，点击
![描述](https://img-blog.csdnimg.cn/20190621194446989.png) 
### 7.下面进行openpose的编译
### 8.在openpose里新建文件夹“build”,打开Cmake3.14.0（为了不必要的麻烦，请保持cmake版本一致）
![描述](https://img-blog.csdnimg.cn/20190621193642224.png) 
第一栏选中openpose,第二栏选中openpose中新建的build文件夹。<br />
点击configurate,选择VS 2015（或VS 2017），推荐VS2015。下拉栏里选中x64!!!<br />
点击 configurate会有红框出现，再次点击configurate就会消失。显式configurate done<br />
点击Generate。显式Generate done<br />
### 9.编译完后打开openpose\build文件夹，使用VS2015打开OpenPose.sln，调出VS解决方案资源管理器，如图所示点击生成（build）
![描述](https://img-blog.csdnimg.cn/2019062120041849.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2JhaXlhbmcxMDAxMA==,size_16,color_FFFFFF,t_70) 
编译完之后显式成功xx个，失败0个即OK！！！！！<br />
### 10.上述过程有问题联系我




