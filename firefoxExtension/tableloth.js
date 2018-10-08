document.title="桌布"
window.console.log("hello firefox")

// 性能要求会低一点
setInterval(()=>{document.title="桌布"},1000)

// 性能待测试，执行很频繁，不知道对性能影响几何
// function title() {
//     setTimeout(title, 0); 
//     console.log("更改名称到桌布");
//     if (document.title != "桌布") {
//         document.title = "桌布"
//     } else {
//     }
// };
// title();