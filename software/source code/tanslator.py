import os


dist = {
'Lcontrol':128,
'Lshift':129,
'Lmenu':130,
'Lwin':	131,
'Rcontrol':132,
'Rshift':133,
'Return':176,
'Rmenu':134,
'Space':32,
'Up':218,
'Down':217,
'Left':216,
'Right':215,
'Back':178,
'Tab':179,
'Escape':177,
'Insert':209,
'Delete':212,
'Prior':211,
'Next':214,
'Home':210,
'End':213,
'F1':194,
'F2':195,
'F3':196,
'F4':197,
'F5':198,
'F6':199,
'F7':200,
'F8':201,
'F9':202,
'F10':203,
'F11':204,
'F12':205,
}



def shutdown():
    print("指令错误！")
    print("回车键退出...")
    input()
    os._exit(0)

#键值转换
def keytrans(key):
    if len(key) >1:
        try:
            Asc = dist[key]
        except:
            shutdown()

    else:
        Asc = ord(key.lower())
    Asc =str(Asc) #按键转ASCII 分隔符
    return Asc

def ts(code):
    pcode = ""
    print(code, end="")
    str = code.split( )
    str_len = len(str)
    #起始段
    if str_len == 1:
        # if   str[0] == "开始":
        #     pcode="START\n"
        # elif str[0] == "START":
        #     pcode="START\n"

        if str [0]== "停止":
            pcode="!E"
        elif str [0]== "END":
            pcode="!E"
        else:
            shutdown()

    if str_len == 2:

        if   str[0] == "按下":
            pcode= "!A"+keytrans(str[1])+ ";"
        elif str[0] == "AN" :
            pcode= "!A"+keytrans(str[1])+ ";"


        elif str[0] == "等待":
            pcode = "!D" +str[1]+";"
        elif str[0] == "DEN":
            pcode = "!D" +str[1]+";"

        elif str[0] == "随机等待":
            pcode = "!P" +str[1]+";"
        elif str[0] == "SJD":
            pcode = "!P" +str[1]+";"

        elif str[0] == "随机按下" :
            pcode= "!J"+keytrans(str[1])+ ";"
        elif str[0] == "SJA":
            pcode= "!J"+keytrans(str[1])+ ";"

        else:
            shutdown()

    if str_len == 3:
        if str[0] == "按住":
             pcode = "!N" + keytrans(str[1]) + "&" + str[2] +";"
        elif str[0] == "ANZ":
             pcode = "!N" + keytrans(str[1]) + "&" + str[2] +";"
        else:
            shutdown()
    if str_len >3:
        shutdown()

    return pcode

f = open("K指令.txt",encoding='UTF-8')
s = open("KEYCODE.TXT",'w',encoding='UTF-8')
print("加载K指令...")
i = 0 #行数
line = f.readline()#读取第一行
while line :
    i = i + 1
    print("编译第%d行" % (i))
    if line[0] != "#": # 判断注释
        if i > 1: #避开第一行的读写错误
            p=(ts(line))
            s.write(p)
        # else:
        #     s.write("START\n")
        #     print("开始")
    line = f.readline()
f.close()
s.close()
print("完成！\n")


