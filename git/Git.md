

# Git

## 1. 版本控制

### 1.1 什么是版本控制？

**版本控制**（Revision control）是一种在<u>开发的过程中用于管理我们对文件、目录或工程等内容的修改历史</u>，方便查看更改历史记录，备份以便恢复以前的版本的软件工程技术

- 实现跨区域多人协同开发
- 追踪和记载一个或者多个文件的历史记录
- 组织和保护你的源代码和文档
- 统计工作量
- 并行开发、提高开发效率
- 跟踪记录整个软件的开发过程

简单说就是用于**管理多人协同开发项目的技术**

### 1.2 常见的版本控制

主流的版本控制器有如下这些：

- **`Git`**
- **`SVN`**（Subversion）
- `CVS`（Concurrent Versions System）

### 1.3 版本控制分类

1. 本地版本控制

   记录文件每次的更新，可以对每个版本做一个快照，或是记录补丁文件，适合个人用，如`RCS`

2. 集中式版本控制`SVN`

   所有的版本数据都保存在服务器上，协同开发者从服务器上同步更新或上传自己的修改

   所有的版本数据都存在服务器上，用户的本地只有自己以前所同步的版本，如果不连网的话，用户就看不到历史版本，也无法切换版本验证问题，或在不同分支工作。而且，所有数据都保存在单一的服务器上，有很大的风险这个服务器会损坏，这样就会丢失所有的数据，当然可以定期备份。代表产品：`SVN`、`CVS`、`VSS`

3. **分布式版本控制 `Git`**

   每个人都拥有全部的代码！安全隐患！

   所有版本信息仓库全部同步到本地的每个用户，这样就可以在本地查看所有版本历史，可以离线在本地提交，只需在连网时push到相应的服务器或其他用户那里。由于每个用户那里保存的都是所有的版本数据，只要有一个用户的设备没有问题就可以恢复所有的数据，但这增加了本地存储空间的占用。

   不会因为服务器损坏或者网络问题，造成不能工作的情况！

### 1.4 Git 和 SVN 的区别【本质是集中式和分布式区别】

`SVN`是集中式版本控制系统，**版本库是集中放在中央服务器的**，而工作的时候，用的都是自己的电脑，所以首先要从中央服务器得到最新的版本，然后工作，完成工作后，需要把自己做完的活推送到中央服务器。集中式版本控制系统是必须联网才能工作，对网络带宽要求较高。

`Git`是分布式版本控制系统，没有中央服务器，**每个人的电脑就是一个完整的版本库**，工作的时候不需要联网了，因为版本都在自己电脑上。协同的方法是这样的：比如说自己在电脑上改了文件A，其他人也在电脑上改了文件A，这时，你们两之间只需把各自的修改推送给对方，就可以互相看到对方的修改了。Git可以直接看到更新了哪些代码和文件！

## 2. Git 的历史

Linux 内核开源项目有着为数众广的参与者。绝大多数的 Linux 内核维护工作都花在了提交补丁和保存归档的繁琐事务上(1991－2002年间)。到 2002 年，整个项目组开始启用一个专有的分布式版本控制系统 BitKeeper 来管理和维护代码。

Linux社区中存在很多的大佬！破解研究 BitKeeper ！

到了 2005 年，开发 BitKeeper 的商业公司同 Linux 内核开源社区的合作关系结束，他们收回了 Linux 内核社区免费使用 BitKeeper 的权力。这就迫使 Linux 开源社区(特别是 Linux 的缔造者 Linus Torvalds)基于使用 BitKeeper 时的经验教训，开发出自己的版本系统。（2周左右！） 也就是后来的 Git！

- **Git是目前世界上最先进的分布式版本控制系统**

## 3. 安装 Git

Windows 上使用`git`，直接从官网进行下载即可

![image-20240712150240391](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240712150240391.png)

**Git Bash：**Unix与Linux风格的命令行，使用最多，推荐最多【主流】

**Git CMD：**Windows风格的命令行

**Git GUI**：图形界面的Git，不建议初学者使用，尽量先熟悉常用命令

```
git --version		# 检查是否安装正确
```

![image-20240712151158394](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240712151158394.png)

## 4. 常用的 Linux 命令

- `cd` : 改变目录
- `pwd` : 显示当前所在的目录路径
- `ls(ll)`:  都是列出当前目录中的所有文件，只不过ll(两个ll)列出的内容更为详细
- `touch` : 新建一个文件 如 touch index.js 就会在当前目录下新建一个index.js文件
- `rm`:  删除一个文件, rm index.js 就会把index.js文件删除
- `mkdir`:  新建一个目录,就是新建一个文件夹
- `rm -r` :  删除一个文件夹, rm -r src 删除src目录
- `mv`：移动文件
- `reset`：重新初始化终端/清屏
- `clear`：清屏
- `history`：查看命令历史
- `help`：帮助
- `exit`：退出
- `#`：表示注释

### Git 配置

所有的配置文件，其实都保存在本地！

```bash
git config -l 	# 查看配置(系统级+全局级)
```

![image-20240712152931594](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240712152931594.png)

查看不同级别的配置文件：

```bash
git config --system --list	# 查看系统
git config --global --list	# 查看当前用户(global)配置
```

**Git 相关的配置文件**

>Git\etc\gitconfig  ：Git 安装目录下的 gitconfig     --system 系统级
>
>C:\Users\Administrator\ .gitconfig    只适用于当前登录用户的配置  --global 全局

**设置用户名和邮箱（初始化git必要！用户标识）**

`--global`为全局配置，会使用该信息来处理你在系统的一切操作；不加，则为某个项目的特定配置

```bash
git config --global user.name "lvqifeng"
git config --global user.email "lvqifeng376@126.com"
```

## 5. Git 基本理论

### 5.1 三个区域

![image-20240713162443878](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240713162443878.png)

Git本地有三个工作区域：**工作目录**（Working Directory）、**暂存区**(Stage/Index)、**资源库**(Repository或Git Directory)。如果在加上**远程的git仓库**(Remote Directory)就可以分为四个工作区域。文件在这四个区域之间的转换关系如下：

> - Workspace：工作区，就是你平时存放项目代码的地方
> - Index / Stage：暂存区，用于临时存放你的改动，事实上它只是一个文件，保存即将提交到文件列表信息
> - Repository：仓库区（或本地仓库），就是安全存放数据的位置，这里面有你提交到所有版本的数据。其中HEAD指向最新放入仓库的版本
> - Remote：远程仓库，托管代码的服务器，可以简单的认为是你项目组中的一台电脑用于远程数据交换

本地的三个区域确切的说应该是git仓库中HEAD指向的版本：

> - Directory：使用Git管理的一个目录，也就是一个仓库，包含我们的工作空间和Git的管理空间
> - WorkSpace：需要通过Git进行版本控制的目录和文件，这些目录和文件组成了工作空间
> - .git：存放Git管理信息的目录，初始化仓库的时候自动创建
> - Index/Stage：暂存区，或者叫待提交更新区，在提交进入repo之前，我们可以把所有的更新放在暂存区
> - Local Repo：本地仓库，一个存放在本地的版本库；HEAD会只是当前的开发分支（branch）
> - Stash：隐藏，是一个工作状态保存栈，用于保存/恢复WorkSpace中的临时状态

### 5.2 工作流程

git 的工作流程一般是这样的：

1. 在工作目录中添加、修改文件
2. 将需要进行版本管理的文件放入暂存区域  `git add <filename>`
3. 将暂存区域的全部文件提交到git仓库  `git commit -m <message>`

因此，git管理的文件有三种状态：**已修改**（modified）,**已暂存**（staged）,**已提交**(committed)

## 6. Git 项目搭建

### 6.1 创建工作目录与常用指令

工作目录（`WorkSpace`)一般就是你希望Git帮助你管理的文件夹，可以是你项目的目录，也可以是一个空目录，建议不要有中文

```bash
pwd    # 显示当前目录位置
mkdir gittest	# 创建文件夹
cd gittest   # 进入目录
touch gittest.txt	# 创建文本文件
```

### 6.2 仓库的搭建

创建本地仓库的方法有两种：1. 创建全新的仓库；2.克隆远程仓库

1. 创建全新的仓库

   创建完成后，项目目录下会多出一个`.git` 目录，记录版本等信息【项目不一定要是空目录】

```bash
git init	# 在当前目录新建一个 git 代码库
```

2. 克隆远程的仓库

   将远程服务器上的仓库完全镜像一份至本地！

```bash
git clone [url] # https://github.com/LQF376/Linux-arm-mystudy.git
```

## 7. Git 文件操作

### 7.1 文件的四种状态

版本控制就是对文件的版本控制，要对文件进行修改、提交等操作，首先要知道文件当前在什么状态，不然可能会提交了现在还不想提交的文件，或者要提交的文件没提交上

- `Untracked`: 未跟踪, 此文件在文件夹中, 但并没有加入到git库, 不参与版本控制. 通过git add 状态变为Staged.

  ![image-20240712160620463](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240712160620463.png)

- `Unmodify`: 文件已经入库, 未修改, 即版本库中的文件快照内容与文件夹中完全一致. 这种类型的文件有两种去处, 如果它被修改, 而变为Modified. 如果使用`git rm`移出版本库, 则成为`Untracked`文件

- `Modified`: 文件已修改, 仅仅是修改, 并没有进行其他的操作. 这个文件也有两个去处, 通过`git add`可进入暂存`staged`状态, 使用`git checkout` 则丢弃修改过, 返回到`unmodify`状态, 即从库中取出文件, 覆盖当前修改 !

- `Staged`: 暂存状态. 执行`git commit`则将修改同步到库中, 这时库中的文件和本地文件又变为一致, 文件为`Unmodify`状态. 执行git reset HEAD filename取消暂存, 文件状态为Modified

  ![image-20240712160754183](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240712160754183.png)

### 7.2 查看文件状态

```bash
git status [filename]	# 查看指定文件状态
git status				# 查看所有文件状态
```

```bash
git add . 		# 添加所有文件到暂存区
git commit -m "消息内存"	# 提交暂存区中的内容到本地仓库 -m 提交信息
```

### 7.3 忽略文件

有些时候我们不想把某些文件纳入版本控制中，比如数据库文件，临时文件，设计文件等

在主目录下建立`.gitignore`文件，此文件有如下规则：

1. 忽略文件中的空行或以井号`#`开始的行将会被忽略
2. 可以使用Linux通配符。例如：星号`*`代表任意多个字符，问号`？`代表一个字符，方括号`[abc]`代表可选字符范围，大括号`{string1,string2,...}`代表可选的字符串等
3. 如果名称的最前面有一个感叹号`!`，表示例外规则，将不被忽略
4. 如果名称的最前面是一个路径分隔符`/`，表示要忽略的文件在此目录下，而子目录中的文件不忽略
5. 如果名称的最后面是一个路径分隔符`/`，表示要忽略的是此目录下该名称的子目录，而非文件（默认文件或目录都忽略）

```bash
# 为注释
*.txt        #忽略所有 .txt结尾的文件,这样的话上传就不会被选中！
!lib.txt     #但lib.txt除外
/temp        #仅忽略项目根目录下的TODO文件,不包括其它目录temp
build/       #忽略build/目录下的所有文件
doc/*.txt    #会忽略 doc/notes.txt 但不包括 doc/server/arch.txt
```

## 8. 本地仓库命令

追踪文件，或者将某个文件备份到缓存中

```bash
git add <filename>	# 添加缓存
```

提交缓存区的记录

```bash
git commit -m "第一次提交";
```

查看 commit 记录【可以查看 `commit id`，用于版本回退】

```bash
git log			# 查看 commit 记录
```

### 8.1 版本回退

从当前提交版本回退到上一个版本，或者进行版本的回退【这里版本指的是`commit`结点】

```bash
git reset --hard HEAD^		# 回退到上一个版本
git reset --hard HEAD^^		# 回退到上上一个版本
git reset --hard HEAD~100	# 往上回退100个版本
```

返回未来版本，需要提前记住未来版本的`commit id`

```bash
git reset --hard <commit id>	# commit id 不需要打全，只需要打前几位即可
```

回退本质是由于 git 内部有一个指向当前版本的`HEAD`指针，回退就是改变`HEAD`指针的指向

若版本回退，出现忘记未来版本的`commit id`情况，可使用`git reflog`查看过往命令，找到对应版本的`commit id`

```bash
git reflog		# 查看过往命令，用于查看 commit id
```

----

### 8.2 管理修改

- git 管理的是文件的修改，只有通过`git add`添加到暂存区，才能`git commit`提交

`git diff HEAD -- readme.txt`查看工作区和版本库里面最新版本的区别

![image-20240713203036835](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240713203036835.png)

---

如果你对工作区的文件进行了修改，但是尚未`git add`添加到暂存区，若是希望撤销修改，回到暂存区的状态

```bash
git checkout -- readme.txt
```

这里有两种情况：【让文件回到最近一次`git commit`或`git add`时的状态】

- `readme.txt`修改后但还没放到暂存区，撤销修改就回到和版本库一摸一样的状态
- `readme.txt`已经添加到暂存区后，又作了修改，撤回修改回到添加到暂存区后的状态

----

`git add`添加到暂存区了，但是未`git commit`提交本地库

`git reset HEAD <file>`把暂存区的修改回退到工作区，`HEAD`表示最新版本

```
git reset HEAD <file>		# 暂存区的修改撤销，重新放回工作区
```

注意：回退到工作区！执行完暂存区是干净的，工作区有修改的，若需要撤销工作区的内容，还得`git checkout`

----

如果已经将修改通过`git commit`提交到本地版本库，那就只能使用**版本回退**【前提是未推送到远程】

---

**删除文件**

删除本质也是一种修改，将文件`<filename>`从版本库中进行删除

```bash
rm <filename>		# 手动本地删除文件

git rm <filename>	# 从暂存区删除文件     git rm <file> 和 git add <file> 效果一样

git commit -m "remove file"		# 提交到版本库
```

**误删本地文件，从版本库中恢复文件**

```bash
git checkout -- <filename>		# 用版本库里的版本替换工作区的版本，无论是修改还是删除，一键恢复
```



查看分支或者创建一个分支

`git init`初始化git仓库之后会默认生成一个主分支`master`【实际开发正式环境下的分支】，一般不会轻易在上面操作

```bash
git branch	# 查看当前分支情况
git branch branchA	# 创建一个分支 branchA
git chechout branchA # 切换到 branchA
git chechout -b branchB		# 创建并切换
```

![image-20240712164131875](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240712164131875.png)

- 合并分支操作

  需要切换到 master 主分支，然后进行合并操作

  ```bash
  git merge <branchName>		# 将 branchName 合并当前分支
  ```

- 分支合并成功后，删除已经合并的分支

  ```bash
  git branch -d <branchName>	# 删除分支
  ```

- 若分支未合并或者合并失败，强制删除分支

  ```bash
  git branch -D <branchName>	# 强制删除分支
  ```

## 9.同 Github 远程提交代码【远程仓库】

- Github 是基于SSH授权的，因此想要在Github提交代码，需要先添加 SSH key 配置

### 9.1 生成 SSH Key

检查是否安装了 SSH

```bash
# git bash 环境下
ssh		# 检查是否安装了 SSH
```

生成密钥和公钥

```bash
ssh-keygen -t rsa		# 指定rsa算法生成密钥和公钥
```

指定文件目录下生成两个文件：

- `id_rsa`：密钥
- `id_rsa.pub`：公钥

指定文件目录位置：

- `Linux`：`~/.ssh`
- `Window`：`/c/Users/Administrator/.ssh`

### 9.2 Github 上添加 SSH key

![image-20240712174804000](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240712174804000.png)

把`id_rsa.pub`公钥文件里的内容复制粘贴进去就可以了

![image-20240712174910842](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240712174910842.png)

测试是否添加成功

![image-20240712175245340](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240712175245340.png)

### 9.3 创建一个 github 仓库并关联

首先需要创建一个github仓库

![image-20240714103532428](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240714103532428.png)

![image-20240714103757495](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240714103757495.png)

与本地仓库进行关联，并将本地仓库的内容推送到Github仓库【关联没有问题，但是推送需要SSH连接】

- `origin`为远程仓库的名字，默认叫法，可以改成别的

```bash
git remote add origin git@github.com:LQF376/CodeTest.git	# 本地仓库与之关联
```

- 把当前分支`master`推送到远程，`-u`参数用于第一次关联，不但会把本地的`master`分支内容推送到远程新的`master`分支，还会把本地的`master`分支和远程的`master`分支关联起来，以后推送或者拉取时可以简化命令

```bash
git push -u origin master		# 把本地库内容推送到远程
```

**删除远程库**

查看远程库信息

```bash
git remote -v
```

根据名字删除远程库，本质是解除了本地和远程库的绑定关系，远程库仍存在，若要删除需要在github上操作

```bash
git remote rm origin
```

### 9.4 Push & Pull

`Push`：本地代码有更新，将本地代码推到远程仓库

```bash
git push origin master		# 将本地代码推到远程 master 分支
```

`Pull`：将远程仓库的最新代码拉下来

```bash
git pull origin master		# 将远程最新的代码更新到本地
```

一般在`push`之前都会先`pull`，这样不容易起冲突

## 9. 分支

### 9.1 分支的概念

git 的每次提交都会串成一条时间线，这条时间线就是一个分支

`HEAD`严格上来说不是指向提交，而是指向`master`，而`master`是指向提交的

- `HEAD`用来指示当前分支

![image-20240714111441043](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240714111441043.png)

每次提交，`master`分支都会向前移动一步，创建分支实质就是创建一个指向提交的新指针

当我们在`dev`分支上的工作完成了，就可以把`dev`合并到`master`上，最直接的方法就是把`master`指向`dev`的当前提交，完成合并

![image-20240714111853267](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240714111853267.png)

同理，删除`dev`分支本质就是删除`dev`指针

### 9.2 创建分支

**查看本地所有分支**

```bash
git branch		# 列出所有本地分支

git branch -r	# 列出所有远程分支
```

**新建一个分支**

```bash
git branch [branch-name]	# 新建一个分支，但依然停留在当前分支

git checkout [branch-name]	# 切换到某个分支上

git checkout -b [branch]	# 新建一个分支，并切换到该分支
```

**合并分支**

```bash
git merge [branch]	# 合并指定分支到当前分支，需要重新切换到 master 主干进行 merge
```

在`master`分支上创建一个`dev`分支，并在`dev`分支上修改添加暂存提交，切换到`master`分支进行合并

```bash
git checkout -b dev

vim <filename>
git add <filename>
git commit -m "changes filename"

git checkout master
git merge dev
```

![image-20240714113134781](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240714113134781.png)

![image-20240714113611517](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240714113611517.png)

![image-20240714113754720](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240714113754720.png)

`Fast-forward`指本次合并是”快进模式“，直接把`master`指向`dev`的当前提交

**删除分支**【合并到`master`之后记得删除分支】

```bash
git branch -d [branch-name]		# 删除分支，分支成功合并之后，删除已经合并的分支
```

**`switch`切换分支**

用`switch`命令来代替`checkout`

```bash
git switch master	# 切换到已有的分支
git switch -c dev	# 创建并切换到新的 dev 分支
```

### 9.3 解决分支合并冲突

新建一个分支`feature1`，分别在`master`分支和`feature1`分支上修改提交，并尝试将`feature1`分支合并到`master`分支中，产生冲突

![image-20240714121916972](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240714121916972.png)

![image-20240714173639981](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240714173639981.png)

`git status`也同样可以查看冲突的文件

![image-20240714173827295](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240714173827295.png)

查看冲突文件内容

![image-20240714173947427](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240714173947427.png)

`<<<<`、`====`、`>>>>`标识冲突，手动解决冲突之后，进行暂存提交

```bash
git add readme.txt
git commit -m "conflict fixed"
```

<img src="https://raw.githubusercontent.com/LQF376/image/main/img/image-20240714174650049.png" alt="image-20240714174650049" style="zoom: 80%;" />

`git log`查看分支情况

![image-20240714174810902](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240714174810902.png)

最后删除`feature1`分支

```bash
git branch -d feature1
```

----

**强制禁用`Fast forward`模式**

若`dev`分支在`master`分支上进行开发，对`dev`分支进行修改后提交，`master`分支尝试合并`dev`分支

- 采用`Fast forward`模式，直接将`master`指针移向`dev`所指提交

  ![image-20240714180254565](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240714180254565.png)

- 禁用`Fast forward`模式，将会在`merge`时产生一个新的`commit`

  ![image-20240714180147210](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240714180147210.png)

```bash
git merge --no-ff -m "merge with no-ff" dev		# master 分支合并 dev 分支
```

`--no-ff`：表示禁用`Fast forward`模式

`-m`：合并需要创建一个新的 commit，所以要加上`-m`参数

`git log`结果显示：

![image-20240714180711357](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240714180711357.png)

----

### 9.4 常用开发分支策略

<img src="https://raw.githubusercontent.com/LQF376/image/main/img/image-20240715180001796.png" alt="image-20240715180001796" style="zoom:80%;" />

- `master`：永远处在即将发布状态
- `develop`：最新的开发状态，通常与`master`保持一致，用于上线前的测试
- `feature`：开发新功能的分支，基于`develop`，完成后merge回`develop`和`master`
- `release`：准备要发布版本的分支，用来修复bug，基于`develop`
- `hotfix`：修复`master`上的问题，等不及`release`版本就必须马上上线，基于`master`

```bash
# 注意命名的规范性
git branch feature/A
git branch release/1.0
```

### 9.5 紧急修复bug分支

若工作开发中，手中的工作只进行到一半，还没法提交，又需要有紧急的bug处理，使用`stash`功能，保存当前工作现场，以便以后恢复现场继续工作

```bash
git stash	# 保存工作区

git checkout master		# 切换回主分支
git checkout -b issue-101	# 创建用于修补bug的分支
# ... 修复bug
git add <filename>		# 保存暂存区
git commit -m "fix bug 101"		# 提交

git switch master		# 返回主分支
git merge --no-ff -m "merged bug fix 101" issue-101

git switch dev	# 返回原来开发分支
```

```bash
git stash list		# 查看堆保存
### 1. 方法
git stash apply		# 恢复现场，但不在 stash 中删除
git stash drop		# 删除
### 2. 方法
git stash pop	# 恢复现场并删除
```

待我们开发完`dev`分支后，由于`master`主分支内修复过bug，同样这个bug也存在于`dev`分支

只需要将`4c805e2 fix bug 101`提交所作修改复制到`dev`分支

```bash
git cherry-pick 4c805e2		# 复制 4c805e2 提交所作修改
```

---

开发新功能时，每添加一个新功能，最好新建一个`feature`分支，在上面开发，完成后，合并，最后，删除

若开发到一般，功能取消了，`feature`分支尚未进行合并，需强行删除，即`-D`参数

```bash
git checkout -D feature/vulcan
```

### 9.6 多人协作

从远程仓库克隆时，实际上 git 自动把本地的`master`分支和远程的`master`分支对应起来了，并且，远程仓库的默认名称是`origin`

```bash
git remote		# 查看远程库的信息
git remote -v 	# 查看更详细信息
```

**推送分支**

把该分支上的所有本地提交到远程库，推送时，要指定本地分支

```bash
git push origin master		# 推送 master 分支
git push origin dev			# 推送 master 分支
```

但并不是所有分支需要提交

- `master`主分支，时时需要与远程同步
- `dev`开发分支，开发团队都要在上面工作，所以也需要与远程同步
- `bug`分支只用于本地修复bug，没必要推送到远程
- `feature`是否推送到远程，取决于是否协同开发

**查看远程分支/删除远程分支**

```bash
git branch -r	# 列出所有远程分支

# 删除远程分支
$ git push origin --delete [branch-name]
$ git branch -dr [remote/branch]
```

**抓取分支**

多人协作，大家都会往`master`和`dev`分支推送各自的修改；同伴clone远程仓库时，只能看到`master`分支

问题：存在你提交时，你的同伴已经在你的版本之后提交了一次，产生冲突

---

你同伴clone远程仓库，创建了`dev`分支进行开发，开发完向远程仓库进行提交

```bash
git clone [url]
git checkout -b dev origin/dev	# 创建远程 origin 的 dev 分支到本地
# 开发过程
git add <filename>
git commit -m "add file"

git push origin dev		# 推送 dev 分支至远程
```

你也在`dev`分支上对同样文件进行了开发，并尝试推送，产生冲突

```bash
git add <filename>
git commit -m "add file"

git push origin dev		# 产生冲突，推送失败
```

解决方法：需要先`git pull`把最新的提交从`origin/dev`抓下来，然后，再本地合并，解决冲突，再推送

```bash
git pull	# 会失败，没有指定本地`dev`分支与远程`origin/dev`分支的关联

## 方法1. git pull <remote> <branch>

## 方法2. 设置 dev 分支与远程 origin/dev 分支的连接
git branch --set-upstream-to=origin/<branch> dev	# 本地分支和远程分支的绑定
git pull
```

`pull`过程中，若是合并有冲突，需要手动解决，解决后，提交，再push

```bash
git commit -m "fix env conflict"
git push origin dev
```

----

总结，多人协作的工作模式通常流程：

- 试图用`git push origin <branch-name>`推送自己修改
- 如果推送失败，则因为远程分支比你的本地更新，需要先用`git pull`试图合并
- 如果合并有冲突，则解决冲突，并在本地提交
- 没有冲突或者解决冲突后，再用`git push origin <branch-name>`推送就能成功

## 10. Git 相关命令合集

![1687685698803](E:\typora\markdownImage\1687685698803.png)

```
/* 1.0 初始化一个项目 */
git init   # 本地初始化一个git项目
git clone [url]	# 从远程服务器上克隆一个项目

/* 2.0 文件被跟踪 */
git add <name>	# 文件被跟踪
git rm <name>	# 删掉文件使文件不被跟踪
git rm --cache <name>	# 保留在目录里但是不被跟踪
# 对跟踪的文件进行修改，修改完后 利用 git add 文件状态 已修改->缓存
git add <file-name>	# 设置成缓存状态
git reset HEAD <name> # 取消缓存状态 缓存->已修改

/* 3.0 上传本地，提交此次修改 */
git commit    # 会自动进入编辑器
git commit -m 'message'  # 本次提交的大致内容

git reset head~ --soft	# 来取消本次提交（不能撤销第一次提交）
--soft commit 提交的没有了，但文件还是暂存态

/* 4.0 查看文件状态 */
git status		# 查看文件状态
git diff 		# 查看文件哪里被修改了
git log			# 查看历史提交
git log --pretty=oneline 	# 美化输出，一行
git log --pretty=format:"%h- %an,%ar:%s" 	# 自定义格式
# %h 哈希值
# %an 作者名字
# %ar 修订日期（距今）
# %ad 修订日期
# %s 提交说明
git log --graph		# 图形化

/* 4.0 远程仓库 remote */
git remote add origin [url]		# 链接远程的一个仓库
git remote 		# 查看

git push origin master # 将本地的 master 推送到远程

/* 5.0 分支 */
git branch --list	# 查看分支
git branch [feature1]	# 创建分支 feature1
git checkout feature1	# 切换到 feature1
git checkout -b feature2 # 新建并切换到 feature2 分支
/* 5.1 合并分支 */
git merge feature1   # 当前的 master 分支和 feature1 分支合并

/* 5.2 推送分支至远程 */
git push -u origin feature1	# 将 feature1 推送到远程 -u 推送一次后下次默认

/* 6.0 储藏功能 */
git stash	# 切换分支前储藏现有的代码（保存功能）
git stash apply		# 切换分支完后，恢复储藏
git stash list 		# 查看储藏的列表
git stash apply stash@{2}	# 恢复指定的储藏次数
git stash pop 		# 恢复完后直接删掉，相当于弹出
git stash drop stash@{0 }	# 删除指定储藏

/* 7.0 重置 reset */
....
```

## 11. alias 设置别名

使用 alias 配置，可以简化命令行实现自定义

```bash
git config --global alias.co checkout		# 设置别名， git co 相当于 git checkout
git config --global alias.psm 'push origin master'		# 设置组合
```

实用小技巧：设置 查看提交日志

```bash
git config --global alias.lg "log --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit --date=relative"
```









https://www.runoob.com/git/git-install-setup.html