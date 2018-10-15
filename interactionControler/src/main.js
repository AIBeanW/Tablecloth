
// 系统传来的全局变量，不要更改，所以用const
const electron = require('electron')


const app = electron.app
const Menu = electron.Menu;
const Tray = electron.Tray;
const dialog = electron.dialog;
const globalShortcut = electron.globalShortcut;
const shell = electron.shell

const path = require('path');
const trayIcon = path.join(__dirname, 'tray/tablecloth-32.ico');

//下面程序打包后不能这么使用 
// const firefoxInside = path.join(__dirname, 'putFirefoxInside/firefoxInside.exe');
// const firefox = path.join(__dirname, 'firefox/FirefoxPortable.exe');
const firefox = path.join(__dirname, '../../firefox/FirefoxPortable.exe');
const firefoxInside = path.join(__dirname, '../../newDesktop/Release/newDesktop.exe');

//托盘对象
var appTray = {};

app.on('ready', () => {

    //系统托盘右键菜单 
    var trayMenuTemplate = [{
        label: '帮助',
        click: function () {
            dialog.showMessageBox({
                type: 'info',
                message: '帮助!',
                detail: 'Ctrl+`打开火狐浏览器\nWin+`嵌入或还原火狐浏览器',
                buttons: []
            })
        }
    },
    {
        label: '退出',
        click: function () {
            //ipc.send('close-main-window'); 
            app.quit();
        }
    }];
    //托盘的上下文菜单
    const contextMenu = Menu.buildFromTemplate(trayMenuTemplate);
    //系统托盘图标
    appTray = new Tray(trayIcon);

    //设置此托盘图标的悬停提示内容
    appTray.setToolTip('这是桌布tablecloth的交互关注进程');

    //设置此图标的上下文菜单
    appTray.setContextMenu(contextMenu);


    //注册全局快捷键
    //win+`键
    globalShortcut.register('super+`', () => {
        // shell.openExternal('https://github.com')
        // 给里面放上嵌入的处理程序
        shell.openItem(firefoxInside)
    })

    globalShortcut.register('ctrl+`', () => {

        // 给里面放上嵌入的处理程序
        console.log(shell.openItem(firefox));
        
    })

    // 推出前注销全局快捷键
    app.on('will-quit', () => {
        globalShortcut.unregisterAll()
        // 默认情况下会退出，但是写上也不会扣工资
        // appTray.destroy()
    })

})