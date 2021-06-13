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