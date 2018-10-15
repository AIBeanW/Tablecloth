// 这里用到一个很实用的 npm 模块，用以在同一行打印文本
var slog = require('single-line-log').stdout;

// 封装的 ProgressBar 工具
function ProgressBar(description){
  // 两个基本参数(属性)
  this.description = description || 'Progress';       // 命令行开头的文字信息
  this.length = 100;                     // 进度条的长度(单位：字符)，默认设为 25

  // 刷新进度条图案、文字的方法
  this.render = function (percent){
    var cell_num = Math.floor(percent * this.length);             // 计算需要多少个 █ 符号来拼凑图案

    // 拼接黑色条用buffer或数组可能更快一点，这么做开销比较大
    // 下次改进
    var cell = '';
    for (var i=0;i<cell_num;i++) {
      cell += '█';
    }

    // 拼接灰色条，用buffer或数组可能更快一点，这么做开销比较大
    // 下次改进
    var empty = '';
    for (var i=0;i<this.length-cell_num;i++) {
      empty += '░';
    }

    // 拼接最终文本
    var cmdText = this.description + ': ' + (100*percent).toFixed(2) + '% ' + cell + empty + ' ' + "100%";
    
    // 在单行输出文本
    slog(cmdText);
  };
}

// 模块导出
module.exports = ProgressBar;