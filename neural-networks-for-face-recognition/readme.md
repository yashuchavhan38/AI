# README

这是人工智能研讨课第一次作业的代码和源码。

基于人工神经网络和反向传播算法来识别人脸的特征。

算法和代码参考了《机器学习/ (美) 米歇尔(Mitchell, T. M.)著; 曾华军等译. ——北京: 机械工业出版社, 2003. 1》第四章的内容。

数据集来自
[Neural Networks for Face Recognition](http://www.cs.cmu.edu/afs/cs.cmu.edu/user/mitchell/ftp/faces.html)

数据集中包含20个子文件夹，每个文件夹包含1个人，一共20人。图片的名称包含了这张图片的userid, sunglass, pose, expression, scale的信息。

需要修改 **.list**文件中图片路径，以让程序能正确读取输入数据。

输入一张人脸图片，我们的ANN主要可以做5件事：

* specfic-person-recognizer 识别他是不是某个特定的人
* sunglass-recognizer 识别他有没有带眼睛
* face-recognizer 识别他是20个人中哪一个
* pose-recognizer 识别他脸的朝向
* expression-recognizer 识别他的表情

工程需要编译才能运行，cd进工程所在路径，输入make，会生成可执行文件facetrain，运行facetrain来执行上述功能。

当然，facetrain的功能也不止于此，它还可以输出分类失败的图片列表以及将隐藏层权值可视化等等。

facetrain的具体用法请参考 doc/ysjai01.pdf，同时这份文档也详细介绍我的实验过程、实验结果和心得体会。

：）