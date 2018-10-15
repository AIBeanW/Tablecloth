// 下载工具
const got = require("got")
// 文件工具
const fs = require("fs")
// 引入简单的进度条
var ProgressBar = require('./progressbar');

// 国际版下载地址
const url = "https://download.mozilla.org/?product=firefox-esr-latest&os=win&lang=zh-CN"
// 国内版下载地址
const ChineseEditonUrl = "https://download-ssl.firefox.com.cn/releases-sha2/full/62.0/zh-CN/Firefox-full-latest-win64.exe"

let bar = null;

console.log("连接中... ...");
got.stream(url)
    .on('response', response => {
        console.log("开始下载！结束程序请按Ctrl+C.");
        console.log("下载文件大小" + (parseInt(response.headers["content-length"]) / (1024 * 1024)).toFixed(2) + "MB");
        bar = new ProgressBar('下载进度');
    })
    .on('downloadProgress', progress => {
        bar.render(progress.percent);
    })
    .on('error', error => {
        console.log("下载失败，请检查！");
        console.log(error);
    })
    .pipe(fs.createWriteStream('firefox.exe'))
