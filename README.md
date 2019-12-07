# gpack

<p align="center">"<i>NOthing or Everything</i>"</p>

<h4 align="center">一个自设计的web框架</h4>

<br>

<p align="center">
  <a href="https://github.com/gaoljhy/gpack/tree/master">
    <img src="https://img.shields.io/badge/Branch-master-green.svg?longCache=true"
        alt="Branch">
  </a>
  <a href="https://github.com/gaoljhy/gpack/pulls">
    <img src="https://img.shields.io/badge/PRs-welcome-brightgreen.svg?longCache=true"
        alt="Pull Requests">
  </a>
  <a href="https://github.com/gaoljhy/gpack/blob/master/LICENSE">
    <img src="https://img.shields.io/badge/License-MIT-blue.svg?longCache=true"
        alt="License">
  </a>
</p>

<div align="center">
  <sub>Created by
  <a href="http://grj321.com">gaoljhy</a> and
  <a href="https://github.com/gaoljhy/gpack/contributors">
    contributors
  </a>
</div>

<br>

## 设计

![设计图](https://github.com/gaoljhy/gpack/blob/master/gpack.png)

## 文件路径

```sh
  .
  ├── doc
  ├── gpack.png
  ├── src
  │   ├── Modules
  │   │   ├── API
  │   │   ├── Http
  │   │   └── Log
  │   ├── gpack.h
  │   └── makefile
  └── test
      ├── Map
      ├── main.cpp
      └── router.yaml
```

## Contributor && PR

感谢为此项目作出贡献的 Contributor，没有大家的贡献，就没有现在的项目进展，我们一起成长，共同实现。

详情参考 [CONTRIBUTOR](./CONTRUIBUTOR.md)

### Pull Request

步骤

1. 添加我的 wechat (目前只开放 WeChat)
2. 添加你的 GitHub 到 CONTRIBUTOR.md 中
3. 发起 PR，检验无冲突后合并

> QR CODE

![wechat](https://github.com/gaoljhy/gpack/blob/master/WechatIMG.jpeg)

## TODO

- [+] Http Module | socket | web socket

- [+] Log Module

- [+] Rout Mapping Module

- [+] setting | middleware | other

- [+] gpack.h(方便源码引用)

- [ ] makefile(源码 make)

## Usage

### json

```cpp
#include "gpack.h"

int main()
{
    Module::SimpleApp app;
    Module_ROUTE(app, "/json")
    ([]{
        Module::json::wvalue x;
        x["message"] = "Hello, World!";
        return x;
    });
    app.port(18080).multithreaded().run();
}
```

### context

```cpp
#include "Module.h"

int main()
{
    Module::SimpleApp app;

    Module_ROUTE(app, "/")([](){
        return "Hello world";
    });

    app.port(18080).multithreaded().run();
}
```
