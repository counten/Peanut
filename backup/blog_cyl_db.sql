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
INSERT INTO `authors` VALUES ('author000','wbq813','wbq813@outlook.com','123456','https://github.com/wbq813',0);
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
INSERT INTO `blogs` VALUES ('blog1525781385','Ubuntu 安装docker并在里面安装MySQL','Ubuntu18.04离线安装docker，拉取mysql镜像，采用网易加速地址;创建用于挂载的目录;使用镜像创建容器;查看容器','1525781385','1525781385','author000','wbq813','tag1525781385','Docker','detial1525781385'),('blog1525781796','CLion 使用googleTest demo','创建C/C++项目;将googleTest克隆下来;将整个googleTest复制到项目里;配置CMakeLists.txt,下面是示范;实例代码','1522222243','1525781796','author000','wbq813','tag1525781796','GoogleTest','detial1522222243'),('blog1525781969','通用的Makefile实例','`g++ hello.cpp` 只能处理单个文件，但是大型项目文件成百上千，我们会想用shell写一个批处理脚本吧。Bingo， 这就是Makefile','1522208105','1525781969','author000','wbq813','tag1525781969','Makefile','detial1522208105'),('blog1525837406','MySQL基本操作语句','命令行登录MySQL，新建用户并授权，命令行基本操作，新建数据并指定编码','1525837406','1525837406','author000','wbq813','tag1525837406','MySQL','detial1525837406'),('blog1526294058','Ubuntu下修改MySQL数据存储位置','ubuntu中安装MySQL5.7后默认路径,创建目标文件,把默认安装的MySql数据库复制到指定目录并设置权限\n修改配置文件，修改启动文件，重启MySQL，登录MySql并验证数据目录','1526294058','1526294058','author000','wbq813','tag1525837406','MySQL','detial1526294058'),('blog1526366785','Peanut 简介','简单的web框架，高性能，模块独立，持续更新(C++)，唯一开源地址。文档目录，运行环境，特性','1522758962','1522758962','author000','wbq813','tag1526366785','Peanut','detial1522758962'),('blog1528718064','Ubuntu 构建Kvm环境','1. 硬件系统的配置，2. 安装宿主机 Linux 系统，3. 编译和安装 KVM，4. 编译和安装 qemu-kvm，5. 安装客户机','1528718064','1528718064','author000','wbq813','tag1528718063','Kvm','detial1528718063');
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
INSERT INTO `details` VALUES ('detial1522208105','# 通用的Makefile实例\n\n## 1. 什么是Makefile\n\nWindows平台的开发者或许不清楚Makefile是什么东西，因为你的开发大部分工作都是IDE在做。但是Linux平台上的开发者不知道就不太合格了。\n\n解释性语言我们不谈，我们以C/C++这样的编译性语言举例，一个`hello.cpp`文件需要经过在：`预处理`,`编译`,`汇编`,`链接`四个过程，简单一点你使用`g++ hello.cpp` 编译器会自动给你进行这四个过程，当然你可以带参数逐个执行。\n\n上述的`g++ hello.cpp` 只能处理单个文件，但是大型项目文件成百上千，我们会想用shell写一个批处理脚本吧。Bingo， 这就是Makefile。\n\n## 2. Demo\n\n```bash\n# dir\nDIR=$(shell pwd)\nSRC_DIR=$(DIR)/src\nINCLUDE_DIR=$(DIR)/include\nDEBUG_DIR=$(DIR)/debug\nOBJS=$(DEBUG_DIR)/*.o\n\n# setting\nCC=gcc\nCFLAGS=-g -c\nPROJNAME=build\nMODULE=main exercise\n\n# link\n$(PROJNAME):$(foreach i,$(MODULE),$(i).o)\n	$(CC) -o $(DEBUG_DIR)/$(PROJNAME) $(OBJS)\n\n# compile\ndefine funC\n$(1).o:$(INCLUDE_DIR)/*.h\n	$(CC) $(CFLAGS) -o $(DEBUG_DIR)/$(1).o $(SRC_DIR)/$(1).c\nendef\n\n$(foreach j,$(MODULE),$(eval $(call funC,$(j))))\n\n# make clean\nclean:\n	rm $(DEBUG_DIR)/*.o $(DEBUG_DIR)/$(PROJNAME)\n\n```'),('detial1522222243','# CLion 使用googleTest demo\n\n## 1. 基本步骤\n\n1. 创建C/C++项目\n\n1. 将googleTest克隆下来\n\n    ```bash\n    git clone https://github.com/google/googletest.git\n    ```\n\n1. 将整个googleTest复制到项目里\n\n1. 配置CMakeLists.txt,下面是示范\n\n    ```bash\n    cmake_minimum_required(VERSION 3.9)\n    project(GTest)\n\n    set(CMAKE_CXX_STANDARD 11)\n\n    set(googleTestDir ./googletest)\n\n    #Add the google test subdirectory\n    add_subdirectory(${googleTestDir})\n    #include googletest/include dir\n    include_directories(${googleTestDir}/googletest/include)\n    #include the googlemock/include dir\n    include_directories(${googleTestDir}/googlemock/include)\n\n    set(SOURCE_FILE\n            src/add.cpp\n            test/addTest.cpp\n            src/add.h\n            )\n    add_executable(GTest ${SOURCE_FILE})\n\n    # Link with GoogleTest\n    target_link_libraries(GTest gtest gtest_main)\n    #Link with GoogleMock\n    target_link_libraries(GTest gmock gmock_main)\n    ```\n1. 实例代码\n\n    ```c++\n    #include \"gtest/gtest.h\"\n\n    int add(int a, int b){\n        return a+b;\n    }\n\n    TEST(test1, c1){\n    EXPECT_EQ(3, add(1,2));\n    }\n\n    GTEST_API_ int main(int argc, char** argv){\n        testing::InitGoogleTest(&argc, argv);\n        return RUN_ALL_TESTS();\n    }\n    ```'),('detial1522758962','# Peanut 简介\n\n简单的web框架，高性能，模块独立，持续更新(C++)，唯一开源地址<https://github.com/wbq813/Peanut>.\n\nSimple web backend framework;\n\nHigh performace, indenpendent modules, updating daily!!\n\n\n## 文档目录\n\n    backup              // something old or useful\n    doc                 // document and design graph\n    Peanut              // C++ backend framework\n\n## 运行环境\n\n    CMake 3.4+\n    g++ 4.0+\n    GNU Make 4.0+\n\n\n## 特性\n\n1. 工具类:\n\n        字符串工具, \n        文件工具, \n        时间工具, \n        编码转换(solve \'@\' send to server change to \'$40\');\n\n\n1. 独立的配置模块;\n\n\n    ```\n    # mnServer config\n    <server>\n        port=8080\n        backlog=10\n        reqSize=1024\n        resSize=1050000\n    </server>\n\n    # static resource config\n    <static>\n        dir=blog_cyl/\n        home=index.html\n        fileSize=2097152\n    </static>\n\n    # database config\n    <database>\n        host=127.0.0.1\n        dbName=testdb\n        username=admin\n        password=admin\n        maxCon=100\n    </database>\n    ```\n1. Http;\n\n        epoll + Thread Pool(多路I/O复用加线程池);\n\n1. 数据库模块（MySQL和MariaDB）；\n\n        数据库连接池;\n        数据库连接事务；\n1. 日志模块\n\n        格式化的日志输出；\n        分等级的日志；\n        错误信息定位;\n1. 格式化返回（以来第三方json模块）；\n1. 简单的文件缓存；\n## TODO\n1. 优化框架的稳定性和性能；\n1. 实现session；\n1. 添加SSL套接层，支持HTTPS；\n1. 数据库模块实现ORM；\n1. 自行实现序列化和反序列功能。 '),('detial1525781385','# Ubuntu 安装docker并在里面安装MySQL\n\n很多人用docker做持续集成，个人也喜欢用来安装软件，少了很多配置而且安装和卸载方便。\n1. 安装docker\n\n    你可以采用APT仓库安装，但是Docker官方暂时没有支持Ubuntu18.04，我只能下载离线安装包安装，你的也可以，我觉得是最简单的方式。\n    \n    docker官网访问很慢，但是他的[下载地址](https://download.docker.com/linux/ubuntu/dists/)访问速度还不错,而且下载完只需要点击即可安装。\n1. 拉取mysql镜像，采用网易加速地址\n    ```bash\n    docker pull hub.c.163.com/library/mysql:5.7\n    ```\n1. 创建用于挂载的目录\n    ```bash\n    sudo mkdir /my/mysql/datadir #用于挂载mysql数据文件\n    sudo mkdir /my/mysql/conf.d #用于挂载mysql配置文件\n    sudo chown yaoren:docker /my #修改/my目录拥有者\n    ```\n\n1. 使用镜像创建容器\n    ```bash\n    docker run --name mysql5.7 -p 3306:3306 -v /my/mysql/datadir:/var/lib/mysql -v /my/mysql/conf.d:/etc/mysql/conf.d -e MYSQL_ROOT_PASSWORD=123456 -d hub.c.163.com/library/mysql:5.7\n    ```\n    相关参数：\n\n        --name：容器名\n        --p：映射宿主主机端口\n        -v：挂载宿主目录到容器目录\n        -e：设置环境变量，此处指定root密码\n        -d：后台运行容器\n1. 查看容器\n    ```bash\n    docker ps\n    ```'),('detial1525837406','# MySQL基本操作语句\n只是记录一些基本操作，做备忘吧。\n\n1. 命令行登录数据库\n    ```bash\n    mysql -h127.0.0.1 -uroot -p\n    ```\n    参数：\n    ```\n	-h +ip地址\n    -u +用户名\n    -p +密码\n    ```\n1. 命令行基本操作\n    ```sql\n	# 显示所有数据库\n    show databases;\n    # 选中某个数据库操作\n    use testdb;\n    # 显示当前数据库的所有表\n    show tables;\n    # 查看表结构\n    desc table1\n    # 退出访问\n    quit\n    ```\n1. 新建数据库，指定中文编码\n    ```sql\n    CREATE DATABASE `testdb` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;\n    ```\n1. 新建用户并授权\n    ```sql\n    # 创建用户，这里的‘%’表示远程用户，本地用户\'localhost\'\n    CREATE USER \'admin\'@\'%\' IDENTIFIED BY \'123456\';\n    # 将testdb的所有权限都给admin\n    GRANT ALL PRIVILEGES ON testdb.* TO \'admin\'@\'%\';\n    # 刷新\n    FLUSH PRIVILEGES;\n    ```'),('detial1526294058','# Ubuntu下修改MySQL数据存储位置\n本文参考了：<https://www.2cto.com/database/201803/729670.html>\n1. ubuntu中安装MySQL5.7后，默认路径如下：\n\n    数据库目录：/var/lib/mysql/\n\n    配置文件：/usr/share/mysql(命令及配置文件) ，/etc/mysql(如：my.cnf)\n\n    相关命令：/usr/bin(mysqladmin mysqldump等命令) 和/usr/sbin启动脚本：/etc/init.d/mysql(启动脚本文件mysql的目录)\n\n    数据库目录是在根目录下的，我们只需要将其修改为其他路径即可。\n\n1. 创建目标文件\n	```bash\n    mkdir /data/mysql\n    ```\n\n1. 把默认安装的MySql数据库复制到/data/mysql中并设置权限\n    ```bash\n    sudo cp -R /var/lib/mysql/* /data/mysql\n    sudo chown -R mysql:mysql /data/mysql\n    sudo service mysql stop\n    ```\n1. 修改/etc/mysql/mysql.conf.d/mysqld.cnf文件 :\n\n    datadir = /data/mysql\n\n1. 修改启动文件\n    ```bash\n    sudo vim /etc/apparmor.d/usr.sbin.mysqld\n    ```\n    将\n\n    /var/lib/mysql/ r\n\n    /var/lib/mysql/** rwk\n\n    改为\n\n    /data/mysql/ r\n\n    /data/mysql/** rwk\n1. 重启MySQL\n    ```bash\n    sudo /etc/init.d/apparmor restart\n    sudo /etc/init.d/mysql restart\n    ```\n1. 登录MySql并验证数据目录\n	```sql\n	mysql>show variables like \'百分号dir百分号\';\n    ```\n    当显示datadir 为/data/mysql时,修改成功。\n\n    将\"百分号\"替换为\"%\".'),('detial1528718063','# Ubuntu 构建Kvm环境\n\n## 1. 硬件系统的配置\n在 x86-64 架构的处理器中， KVM 必需的硬件虚拟化扩展分别为： Intel 的虚拟化技术（Intel VT） 和 AMD 的 AMD-V 技术。首先处理器（CPU） 要在硬件上支持 VT 技术， 还要在 BIOS 中将其功能打开， KVM 才能使用到。 目前， 多数流行的服务器和部分桌面处理器的 BIOS 都默认将 VT 打开了。\n\nLinux 系统中， 可以通过检查 /proc/cpuinfo 文件中的 CPU 特性标志（flags） 来查看 CPU 目\n前是否支持硬件虚拟化。 在 x86 和 x86-64 平台中， Intel 系列 CPU 支持虚拟化的标志为“vmx”，AMD 系列 CPU 的标志为“ svm”， 所以可以用如下命令行查看“ vmx” 或者“ svm” 标志。\n\n```bash\ngrep -E \'(vmx|svm)\' /proc/cpuinfo\n```\n\n## 2. 安装宿主机 Linux 系统\nKVM 是基于内核的虚拟化技术， 要运行 KVM 虚拟化环境， 安装一个 Linux 操作系统的宿主机（Host） 是必需的。下面将使用ubuntu18.04为例进行安装。\n\n## 3. 编译和安装 KVM\n### 3.1 download source code\n1. download Kvm\n\n	url: <https://git.kernel.org/pub/scm/virt/kvm/kvm.git/>\n\n	version: linux-4.16.tar.gz\n\n### 3.2 Config Kvm\n1. 使用可视化的配置选项，否则9k+的配置会让你崩溃。\n	```bash\n	make menuconfig\n	```\n1. 如果出现错误：`Unable to find the ncurses libraries`\n	```bash\n	sudo apt-get install ncurses-dev\n	```\n1. 选择了 Virtualization 之后， 进入其中进行详细配置， 包括选中 KVM、 选中对处理器的支持等。\n	```\n	CONFIG_HAVE_KVM=y\n	CONFIG_HAVE_KVM_IRQCHIP=y\n	CONFIG_HAVE_KVM_EVENTFD=y\n	CONFIG_KVM_APIC_ARCHITECTURE=y\n	CONFIG_KVM_MMIO=y\n	CONFIG_KVM_ASYNC_PF=y\n	CONFIG_HAVE_KVM_MSI=y\n	CONFIG_VIRTUALIZATION=y\n	CONFIG_KVM=m\n	CONFIG_KVM_INTEL=m\n	# CONFIG_KVM_AMD is not set\n	CONFIG_KVM_MMU_AUDIT=y\n	```\n	确保以上与Kvm相关的配置正确。\n\n### 3.3 Compile Kvm\n\n需要经过编译 kernel、 编译 bzImage 和编译 module 等三个步骤。\n\n1. 编译 kernel\n	```bash\n	make vmlinux -j 20\n	```\n	-j参数表示使用20个进程进行编译，不是必须。\n\n	遇到错误：`scripts/extract-cert.c:21:10: fatal error: openssl/bio.h: No such file or directory`\n	```bash\n	sudo apt install libssl-dev\n	```\n\n1. 编译 bzImage\n	```bash\n	make bzImage\n	```\n\n1. 编译 module\n	```bash\n	make modules -j 20\n	```\n\n### 3.4 Install Kvm\nKVM 的安装包括两个步骤： module 的安装、 kernel 与 initramfs 的安装。\n\n1. 安装 module\n	```bash\n	make modules_install\n	```\n	以上命令可以将编译好的 module 安装到相应的目录之中， 在默认情况下 module 被安装到 /lib/modules/$kernel_version/kernel 目录之中。\n\n	报错`Makefile:934: \"Cannot use CONFIG_STACK_VALIDATION=y, please install libelf-dev,libelf-devel or elfutils-libelf-devel\"`\n	在配置文件暂时去掉这个配置：\n	```\n	# CONFIG_STACK_VALIDATION  is not set\n	```\n\n	安装好 module 之后， 可以查看一下相应的安装路径， 可看到 kvm 模块也已经安装.\n	```bash\n	ls -l /lib/modules/4.15.0/kernel/\n	ls -l /lib/modules/4.15.0/kernel/arch/x86/kvm/\n	```\n\n1. 安装 kernel 和 initramfs\n	```bash\n	make install\n	```\n\n	报错：`gzip: stdout: No space left on device`\n	清理/boot分区或者调整/boot分区的大小。\n\n	```bash\n	ls -l /boot/\n	```\n	通过以上命令可见， 在 /boot 目录下生成了内核（vmlinuz） 和 initramfs 等内核启动所需的文件。\n\n	```bash\n	cat /boot/grub/grub.cfg\n	```\n	通过以上命令看到，在运行 make install 之后， grub 配置文件（如 ： /boot/grub/grub.cfg） 中也自动添加了一个 grub 选项。\n\n1. 重新启动系统， 选择刚才为了 KVM 而编译、 安装的内核启动。\n	\n	在通常情况下， 系统启动时默认已经加载了 kvm 和 kvm_intel 这两个模块； 如果没有加载， 请手动用 modprobe 命令依次加载 kvm 和 kvm_intel 模块。\n	```bash\n	# 查看是否加载\n	lsmod | grep kvm\n	# 如果没有就手动加载\n	modprobe kvm\n	modprobe kvm_intel\n	```\n\n1. 检查 /dev/kvm 文件\n\n	它是 kvm 内核模块提供给用户空间的 qemu-kvm 程序使用的一个控制接口， 它提供了客户机（Guest） 操作系统运行\n所需要的模拟和实际的硬件设备环境。\n\n	```bash\n	ls -l /dev/kvm\n	```\n\n## 4. 编译和安装 qemu-kvm\n除了在内核空间的 kvm 模块之外，在用户空间需要 QEMU 来模拟所需要 CPU 和设备模型以及用于启动客户机进程，这样才有了一个完整的 KVM 运行环境。 而 qemu-kvm 是为了针对 KVM专门做了修改和优化的 QEMU 分支。\n\n1. 下载 qemu-kvm 源码\n	\n	url: <https://git.kernel.org/pub/scm/virt/kvm/qemu-kvm.git>\n\n	version: qemu-kvm-2.3.0.tar.gz\n\n1. 配置 qemu-kvm\n	直接运行代码仓库中 configure 文件进行配置.\n	```bash\n	./configure\n	```\n\n	报错`ERROR: pkg-config binary \'pkg-config\' not found`\n	```bash\n	sudo apt install pkg-config\n	```\n\n	报错`ERROR: zlib check failed Make sure to have the zlib libs and headers installed.`\n	```bash\n	sudo apt-get install zlib1g-dev\n	```\n\n	报错`ERROR: glib-2.12 gthread-2.0 is required to compile QEMU`\n	```bash\n	sudo apt-get install libglib2.0-dev\n	```\n\n	报错`ERROR: pixman >= 0.21.8 not present.`\n	```bash\n	apt-get install libpixman-1-dev\n	```\n\n	报错`ERROR: DTC (libfdt) not present.`\n	```bash\n	apt-get install libfdt-dev\n	```\n\n	修正以上错误后还是会编译出错。\n\n	发现kernel.org下载的版本两年没更新了，到官网下载最新的稳定版：\n\n	url: <https://www.qemu.org/download/>\n	version: 2.12.0\n	\n	确保一下配置正确：\n	```\n	VNC support yes # 通常需要通过 VNC 连接到客户机中\n	KVM support yes # 这是对 KVM 的支持\n	```\n\n\n1. 编译 qemu-kvm\n	直接make进行安装：\n	```bash\n	make -j 20\n	```\n	可以看到， 最后有编译生成 qemu-system-x86_64 文件， 它就是我们常用的 qemu-kvm 的命令行工具\n\n1. 安装 qemu-kvm\n	编译完成之后， 运行`make install` 命令即可安装 qemu-kvm。\n\n	qemu-kvm 安装过程的主要任务有这几个 ： 创建 qemu 的一些目录， 复制一些配置文件到相应的目录下， 复制一些 firmware 文件（如 ： sgabios.bin, kvmvapic.bin） 到目录下以便 qemu-kvm 的命令行启动时可以找到对应的固件提供给客户机使用， 复制 keymaps 到相应的目录下以便在客户机中支持各种所需键盘类型， 复制 qemu-system-x86_64、 qemu-img 等可执行程序到对应的目录下。\n\n1. 检查 qemu-kvm 安装之后的系统状态\n	```bash\n	which qemu-system-x86_64\n	which qemu-img\n	ls /usr/local/share/qemu/\n	ls /usr/local/share/qemu/keymaps/\n	```\n\n1. 由于 qemu-kvm 是用户空间的程序， 安装之后不用重启系统， 直接用 qemu-systemx86_64、 qemu-img 这样的命令行工具即可使用 qemu-kvm 了。\n\n## 5. 安装客户机\n\n1. 创建一个镜像文件或者磁盘分区等来存储客户机的系统和文件\n	```bash\n	dd if=/dev/zero of=rhel6u3.img bs=1M count=40960\n	```\n\n1. 启动客户机\n	```bash\n	qemu-system-x86_64 -usbdevice tablet -m 4096 -smp 2 --enable-kvm -boot order=cd -hda /home/micle/Proj/VirtDemo/win7sp1.img -cdrom  /home/micle/Proj/VirtDemo/win7pro_sp1_x64_dvd_u_677031.iso\n	```\n\n1. 安装vncviewer 并连接客户机\n	```bash\n	sudo apt install vnc4server\n	sudo apt install xvnc4viewer\n	```\n\n	```bash\n	vncviewer ip:5900\n	```\n\n1. `Ctrl+Alt+2` 切换到 QEMU 监视器窗口\n	\n	在监视器窗口中可以执行一些命令， 比如执行`info kvm` 命令来查看当前 QEMU 是否使用着 KVM.\n	`Ctrl+Alt+1` 可以切换回原窗口。'),('system001','## wbq813\n\nBacherlor of SouthWest University.\n\nSkill: JavaEE, C++,Python, NLP\n\nEmail: wbq813@foxmail.com\n\nGithub: [https://github.com/wbq813](https://github.com/wbq813)\n## Nana\n\nBacherlor of SouthWest University.\n\nSkill: JavaEE, Jquery, BigData\n\nEmail: 2743587185@qq.com\n\nGitee: [https://gitee.com/xuexuexue1](https://gitee.com/xuexuexue1)\n'),('system002','## Peanut\n开源地址：[https://github.com/wbq813/Peanut](https://github.com/wbq813/Peanut)\n\n简单的web框架，高性能，模块独立，持续更新(C++实现). \n\nSimple web backend framework; High performace, indenpendent modules, updating daily!!\n## PeanutJson\n\n开源地址：[https://github.com/wbq813/PeanutJson](https://github.com/wbq813/PeanutJson)\n\n简单的 Json 处理工具（C++ 实现）\n\na simple json process tools for cpp;\n\n## CodeYourLife\n开源地址：[https://github.com/wbq813/CodeYourLife](https://github.com/wbq813/CodeYourLife)\n\n基于SSH的编程视频分享平台\n\nVideo for coding share platform\n\n## Documentary\n\n开源地址：[https://github.com/wbq813/Documentary](https://github.com/wbq813/Documentary)\n\n活动纪实平台（Documentary platform） springboot，hibernate， swagger，maven组合开发而成的活动纪实平台，包括以下主要功能。 活动上传 支持活动的文字图片上传，上级审批之后进行展示。 活动统计，数据导出excel 每个单位活动发布量，不同级别，划分维度活动发布量统计，excel实时导出。 多级用户管理 支持4级用户的管理。 pc，移动端自适应显示。'),('system003','## 徐阿衡的博客\n\n地址：[http://www.shuang0420.com/categories/](http://www.shuang0420.com/categories/)\n\n主要内容： 深度学习，自然语言处理，爬虫，搜索引擎，分布式系统');
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
INSERT INTO `tags` VALUES ('tag1525781385','Docker',1),('tag1525781796','GoogleTest',1),('tag1525781969','Makefile',1),('tag1525837406','MySQL',2),('tag1526366785','Peanut',2),('tag1528718063','Kvm',1);
/*!40000 ALTER TABLE `tags` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-07-14 15:30:59
