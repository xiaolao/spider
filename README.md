爬虫
----

## 环境准备
因为本项目依赖比较多，且仅支持在Linux系统下运行，故建议使用docker来运行。

1. 请查看官方文档安装[Docker](https://www.docker.com/get-started)
2. 本项目已经预先构建好了基于ubuntu的docker镜像，运行下面的命令直接进入容器内：
```bash
# Linux or Mac OS
sudo docker run --name cspider -it xiaolao/cspider:v1 /bin/bash
```
3. 进入镜像后，执行`ls`命令可以看到两个文件`main.c`和`test`，然后执行`./test`看看环境是否正常。