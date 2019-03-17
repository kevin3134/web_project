#!/usr/bin/env python
# -*- coding: utf-8 -*-
 
import requests
import json
import os

geturl = 'http://18.222.252.3/'
posturl = 'http://18.222.252.3/time_management/add-item'
headers = {'content-type': "application/json"}

#运行cmd,生成data.txt
cpptest="LogLib.exe"
print("python execute cpp program:")
os.system(cpptest)

#获取数据

#数据itemlist: [ {ClassName: <type>string, WindowText: <type>string, ProcessName: <type>string, topWindow: <type>int} ]
# topWindow 1:是   0:不是
#返回值: "item=" + json.dumps(itemlist) + "&" + "csrfmiddlewaretoken=xxxxxxx"
f = open("data.txt", "r", encoding = "ANSI")
linesdata = f.readlines()
lineslength = len(linesdata)
loc = 0

itemlist = []
sondict = {}
if(lineslength%4 == 0):
    while(loc < lineslength):
        sondict.update({"ClassName" : linesdata[loc].rstrip("ClassName:")[:-1]})
        loc = loc + 1
        sondict.update({"WindowText" : linesdata[loc].rstrip("WindowText:")[:-1]})
        loc = loc + 1
        sondict.update({"ProcessName" : linesdata[loc].rstrip("ProcessName:")[:-1]})
        loc = loc + 1
        if(linesdata[loc] == "topWindow"):
            sondict.update({"topWindow" : 1})
        else:
            sondict.update({"topWindow" : 0})
        loc = loc + 1
        itemlist.append(sondict)
postdata = "item=" + json.dumps(itemlist)
f.close()

#删除data.txt
os.remove("data.txt")

#GET
response = requests.get(geturl)
cookie_value = ''
for key,value in response.cookies.items():     #response.cookies其实只有一个
    cookie_value = value
headers['Cookie'] = key + '=' + cookie_value
# 返回信息
print(response.text)
# 返回响应头
print(response.status_code)

#POST
postdata = postdata + "&" + "csrfmiddlewaretoken=" + cookie_value
response = requests.post(posturl, data = postdata, headers = headers)
# 返回信息
print(response.text)
# 返回响应头
print(response.status_code)
