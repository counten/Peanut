CREATE DATABASE  IF NOT EXISTS `blog_cyl` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `blog_cyl`;
-- MySQL dump 10.13  Distrib 5.7.22, for Linux (x86_64)
--
-- Host: 47.94.249.60    Database: blog_cyl
-- ------------------------------------------------------
-- Server version	5.5.5-10.2.11-MariaDB-10.2.11+maria~jessie

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `authors`
--

DROP TABLE IF EXISTS `authors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `authors` (
  `id` varchar(20) COLLATE utf8_bin NOT NULL COMMENT '作者id',
  `name` varchar(255) COLLATE utf8_bin DEFAULT NULL COMMENT '作者名',
  `email` varchar(255) COLLATE utf8_bin NOT NULL COMMENT '作者邮箱',
  `passwd` varchar(255) COLLATE utf8_bin NOT NULL COMMENT '登录密码',
  `git` varchar(255) COLLATE utf8_bin DEFAULT NULL COMMENT '代码托管',
  `role` int(11) NOT NULL DEFAULT 1 COMMENT '用户角色',
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`),
  UNIQUE KEY `email` (`email`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `authors`
--

LOCK TABLES `authors` WRITE;
/*!40000 ALTER TABLE `authors` DISABLE KEYS */;
INSERT INTO `authors` VALUES ('author000','MicleWang','miclewang@outlook.com','123456','http://gitee.com/miclewang',0);
/*!40000 ALTER TABLE `authors` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `blogs`
--

DROP TABLE IF EXISTS `blogs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `blogs` (
  `id` varchar(20) COLLATE utf8_bin NOT NULL COMMENT '博客id',
  `title` varchar(255) COLLATE utf8_bin NOT NULL COMMENT '博客标题',
  `abstract` text COLLATE utf8_bin NOT NULL COMMENT '博客概述',
  `create_time` varchar(255) COLLATE utf8_bin NOT NULL COMMENT '创建时间',
  `update_time` varchar(255) COLLATE utf8_bin NOT NULL COMMENT '更改时间',
  `author_id` varchar(20) COLLATE utf8_bin NOT NULL COMMENT '作者id',
  `author_name` varchar(255) COLLATE utf8_bin NOT NULL COMMENT '作者名',
  `tag_id` varchar(20) COLLATE utf8_bin NOT NULL COMMENT '标签id',
  `tag_name` varchar(255) COLLATE utf8_bin NOT NULL COMMENT '标签名',
  `detail_id` varchar(20) COLLATE utf8_bin NOT NULL COMMENT '博客内容',
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `blogs`
--

LOCK TABLES `blogs` WRITE;
/*!40000 ALTER TABLE `blogs` DISABLE KEYS */;
INSERT INTO `blogs` VALUES ('blog1525781385','Ubuntu 安装docker并在里面安装MySQL','Ubuntu18.04离线安装docker，拉取mysql镜像，采用网易加速地址;创建用于挂载的目录;使用镜像创建容器;查看容器','1525781385','1525781385','author000','MicleWang','tag1525781385','Docker','detial1525781385'),('blog1525781796','CLion 使用googleTest demo','创建C/C++项目;将googleTest克隆下来;将整个googleTest复制到项目里;配置CMakeLists.txt,下面是示范;实例代码','1522222243','1525781796','author000','MicleWang','tag1525781796','GoogleTest','detial1522222243'),('blog1525781969','通用的Makefile实例','`g++ hello.cpp` 只能处理单个文件，但是大型项目文件成百上千，我们会想用shell写一个批处理脚本吧。Bingo， 这就是Makefile','1522208105','1525781969','author000','MicleWang','tag1525781969','Makefile','detial1522208105'),('blog1525837406','MySQL基本操作语句','命令行登录MySQL，新建用户并授权，命令行基本操作，新建数据并指定编码','1525837406','1525837406','author000','MicleWang','tag1525837406','MySQL','detial1525837406'),('blog1526294058','Ubuntu下修改MySQL数据存储位置','ubuntu中安装MySQL5.7后默认路径,创建目标文件,把默认安装的MySql数据库复制到指定目录并设置权限\n修改配置文件，修改启动文件，重启MySQL，登录MySql并验证数据目录','1526294058','1526294058','author000','MicleWang','tag1525837406','MySQL','detial1526294058'),('blog1526366785','Peanut 简介','简单的web框架，高性能，模块独立，持续更新(C++)，唯一开源地址。文档目录，运行环境，特性','1522758962','1522758962','author000','MicleWang','tag1526366785','Peanut','detial1522758962');
/*!40000 ALTER TABLE `blogs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `details`
--

DROP TABLE IF EXISTS `details`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `details` (
  `id` varchar(20) COLLATE utf8_bin NOT NULL COMMENT '博客内容id',
  `detail` text COLLATE utf8_bin NOT NULL COMMENT '博客内容',
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `details`
--

LOCK TABLES `details` WRITE;
/*!40000 ALTER TABLE `details` DISABLE KEYS */;
INSERT INTO `details` VALUES ('detial1522208105','# 通用的Makefile实例\n\n## 1. 什么是Makefile\n\nWindows平台的开发者或许不清楚Makefile是什么东西，因为你的开发大部分工作都是IDE在做。但是Linux平台上的开发者不知道就不太合格了。\n\n解释性语言我们不谈，我们以C/C++这样的编译性语言举例，一个`hello.cpp`文件需要经过在：`预处理`,`编译`,`汇编`,`链接`四个过程，简单一点你使用`g++ hello.cpp` 编译器会自动给你进行这四个过程，当然你可以带参数逐个执行。\n\n上述的`g++ hello.cpp` 只能处理单个文件，但是大型项目文件成百上千，我们会想用shell写一个批处理脚本吧。Bingo， 这就是Makefile。\n\n## 2. Demo\n\n```bash\n# dir\nDIR=$(shell pwd)\nSRC_DIR=$(DIR)/src\nINCLUDE_DIR=$(DIR)/include\nDEBUG_DIR=$(DIR)/debug\nOBJS=$(DEBUG_DIR)/*.o\n\n# setting\nCC=gcc\nCFLAGS=-g -c\nPROJNAME=build\nMODULE=main exercise\n\n# link\n$(PROJNAME):$(foreach i,$(MODULE),$(i).o)\n	$(CC) -o $(DEBUG_DIR)/$(PROJNAME) $(OBJS)\n\n# compile\ndefine funC\n$(1).o:$(INCLUDE_DIR)/*.h\n	$(CC) $(CFLAGS) -o $(DEBUG_DIR)/$(1).o $(SRC_DIR)/$(1).c\nendef\n\n$(foreach j,$(MODULE),$(eval $(call funC,$(j))))\n\n# make clean\nclean:\n	rm $(DEBUG_DIR)/*.o $(DEBUG_DIR)/$(PROJNAME)\n\n```'),('detial1522222243','# CLion 使用googleTest demo\n\n## 1. 基本步骤\n\n1. 创建C/C++项目\n\n1. 将googleTest克隆下来\n\n    ```bash\n    git clone https://github.com/google/googletest.git\n    ```\n\n1. 将整个googleTest复制到项目里\n\n1. 配置CMakeLists.txt,下面是示范\n\n    ```bash\n    cmake_minimum_required(VERSION 3.9)\n    project(GTest)\n\n    set(CMAKE_CXX_STANDARD 11)\n\n    set(googleTestDir ./googletest)\n\n    #Add the google test subdirectory\n    add_subdirectory(${googleTestDir})\n    #include googletest/include dir\n    include_directories(${googleTestDir}/googletest/include)\n    #include the googlemock/include dir\n    include_directories(${googleTestDir}/googlemock/include)\n\n    set(SOURCE_FILE\n            src/add.cpp\n            test/addTest.cpp\n            src/add.h\n            )\n    add_executable(GTest ${SOURCE_FILE})\n\n    # Link with GoogleTest\n    target_link_libraries(GTest gtest gtest_main)\n    #Link with GoogleMock\n    target_link_libraries(GTest gmock gmock_main)\n    ```\n1. 实例代码\n\n    ```c++\n    #include \"gtest/gtest.h\"\n\n    int add(int a, int b){\n        return a+b;\n    }\n\n    TEST(test1, c1){\n    EXPECT_EQ(3, add(1,2));\n    }\n\n    GTEST_API_ int main(int argc, char** argv){\n        testing::InitGoogleTest(&argc, argv);\n        return RUN_ALL_TESTS();\n    }\n    ```'),('detial1522758962','# Peanut 简介\n\n简单的web框架，高性能，模块独立，持续更新(C++)，唯一开源地址<https://gitee.com/miclewang/mnServer>.\n\nSimple web backend framework;\n\nHigh performace, indenpendent modules, updating daily!!\n\n\n## 文档目录\n\n    backup              // something old or useful\n    doc                 // document and design graph\n    Peanut              // C++ backend framework\n\n## 运行环境\n\n    CMake 3.4+\n    g++ 4.0+\n    GNU Make 4.0+\n\n\n## 特性\n\n1. 工具类:\n\n        字符串工具, \n        文件工具, \n        时间工具, \n        编码转换(solve \'@\' send to server change to \'$40\');\n\n\n1. 独立的配置模块;\n\n\n    ```\n    # mnServer config\n    <server>\n        port=8080\n        backlog=10\n        reqSize=1024\n        resSize=1050000\n    </server>\n\n    # static resource config\n    <static>\n        dir=blog_cyl/\n        home=index.html\n        fileSize=2097152\n    </static>\n\n    # database config\n    <database>\n        host=127.0.0.1\n        dbName=testdb\n        username=admin\n        password=admin\n        maxCon=100\n    </database>\n    ```\n1. Http;\n\n        epoll + Thread Pool(多路I/O复用加线程池);\n\n1. 数据库模块（MySQL和MariaDB）；\n\n        数据库连接池;\n        数据库连接事务；\n1. 日志模块\n\n        格式化的日志输出；\n        分等级的日志；\n        错误信息定位;\n1. 格式化返回（以来第三方json模块）；\n1. 简单的文件缓存；\n## TODO\n1. 优化框架的稳定性和性能；\n1. 实现session；\n1. 添加SSL套接层，支持HTTPS；\n1. 数据库模块实现ORM；\n1. 自行实现序列化和反序列功能。 '),('detial1525781385','# Ubuntu 安装docker并在里面安装MySQL\n\n很多人用docker做持续集成，个人也喜欢用来安装软件，少了很多配置而且安装和卸载方便。\n1. 安装docker\n\n    你可以采用APT仓库安装，但是Docker官方暂时没有支持Ubuntu18.04，我只能下载离线安装包安装，你的也可以，我觉得是最简单的方式。\n    \n    docker官网访问很慢，但是他的[下载地址](https://download.docker.com/linux/ubuntu/dists/)访问速度还不错,而且下载完只需要点击即可安装。\n1. 拉取mysql镜像，采用网易加速地址\n    ```bash\n    docker pull hub.c.163.com/library/mysql:5.7\n    ```\n1. 创建用于挂载的目录\n    ```bash\n    sudo mkdir /my/mysql/datadir #用于挂载mysql数据文件\n    sudo mkdir /my/mysql/conf.d #用于挂载mysql配置文件\n    sudo chown yaoren:docker /my #修改/my目录拥有者\n    ```\n\n1. 使用镜像创建容器\n    ```bash\n    docker run --name mysql5.7 -p 3306:3306 -v /my/mysql/datadir:/var/lib/mysql -v /my/mysql/conf.d:/etc/mysql/conf.d -e MYSQL_ROOT_PASSWORD=123456 -d hub.c.163.com/library/mysql:5.7\n    ```\n    相关参数：\n\n        --name：容器名\n        --p：映射宿主主机端口\n        -v：挂载宿主目录到容器目录\n        -e：设置环境变量，此处指定root密码\n        -d：后台运行容器\n1. 查看容器\n    ```bash\n    docker ps\n    ```'),('detial1525837406','# MySQL基本操作语句\n只是记录一些基本操作，做备忘吧。\n\n1. 命令行登录数据库\n    ```bash\n    mysql -h127.0.0.1 -uroot -p\n    ```\n    参数：\n    ```\n	-h +ip地址\n    -u +用户名\n    -p +密码\n    ```\n1. 命令行基本操作\n    ```sql\n	# 显示所有数据库\n    show databases;\n    # 选中某个数据库操作\n    use testdb;\n    # 显示当前数据库的所有表\n    show tables;\n    # 查看表结构\n    desc table1\n    # 退出访问\n    quit\n    ```\n1. 新建数据库，指定中文编码\n    ```sql\n    CREATE DATABASE `testdb` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;\n    ```\n1. 新建用户并授权\n    ```sql\n    # 创建用户，这里的‘%’表示远程用户，本地用户\'localhost\'\n    CREATE USER \'admin\'@\'%\' IDENTIFIED BY \'123456\';\n    # 将testdb的所有权限都给admin\n    GRANT ALL PRIVILEGES ON testdb.* TO \'admin\'@\'%\';\n    # 刷新\n    FLUSH PRIVILEGES;\n    ```'),('detial1526294058','# Ubuntu下修改MySQL数据存储位置\n本文参考了：<https://www.2cto.com/database/201803/729670.html>\n1. ubuntu中安装MySQL5.7后，默认路径如下：\n\n    数据库目录：/var/lib/mysql/\n\n    配置文件：/usr/share/mysql(命令及配置文件) ，/etc/mysql(如：my.cnf)\n\n    相关命令：/usr/bin(mysqladmin mysqldump等命令) 和/usr/sbin启动脚本：/etc/init.d/mysql(启动脚本文件mysql的目录)\n\n    数据库目录是在根目录下的，我们只需要将其修改为其他路径即可。\n\n1. 创建目标文件\n	```bash\n    mkdir /data/mysql\n    ```\n\n1. 把默认安装的MySql数据库复制到/data/mysql中并设置权限\n    ```bash\n    sudo cp -R /var/lib/mysql/* /data/mysql\n    sudo chown -R mysql:mysql /data/mysql\n    sudo service mysql stop\n    ```\n1. 修改/etc/mysql/mysql.conf.d/mysqld.cnf文件 :\n\n    datadir = /data/mysql\n\n1. 修改启动文件\n    ```bash\n    sudo vim /etc/apparmor.d/usr.sbin.mysqld\n    ```\n    将\n\n    /var/lib/mysql/ r\n\n    /var/lib/mysql/** rwk\n\n    改为\n\n    /data/mysql/ r\n\n    /data/mysql/** rwk\n1. 重启MySQL\n    ```bash\n    sudo /etc/init.d/apparmor restart\n    sudo /etc/init.d/mysql restart\n    ```\n1. 登录MySql并验证数据目录\n	```sql\n	mysql>show variables like \'百分号dir百分号\';\n    ```\n    当显示datadir 为/data/mysql时,修改成功。\n\n    将\"百分号\"替换为\"%\".');
/*!40000 ALTER TABLE `details` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tags`
--

DROP TABLE IF EXISTS `tags`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tags` (
  `id` varchar(20) COLLATE utf8_bin NOT NULL COMMENT '标签id',
  `name` varchar(255) COLLATE utf8_bin NOT NULL COMMENT '标签名称',
  `blog_num` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`),
  UNIQUE KEY `id` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tags`
--

LOCK TABLES `tags` WRITE;
/*!40000 ALTER TABLE `tags` DISABLE KEYS */;
INSERT INTO `tags` VALUES ('tag1525781385','Docker',1),('tag1525781796','GoogleTest',1),('tag1525781969','Makefile',1),('tag1525837406','MySQL',2),('tag1526366785','Peanut',1);
/*!40000 ALTER TABLE `tags` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `test`
--

DROP TABLE IF EXISTS `test`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `test` (
  `td` varchar(20) COLLATE utf8_bin NOT NULL DEFAULT 'current_timestamp()',
  `url` varchar(255) COLLATE utf8_bin NOT NULL,
  `date` varchar(255) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`td`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `test`
--

LOCK TABLES `test` WRITE;
/*!40000 ALTER TABLE `test` DISABLE KEYS */;
/*!40000 ALTER TABLE `test` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-05-15 15:09:13
